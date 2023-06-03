#ifndef _TESTING_UTILS_H
#define _TESTING_UTILS_H

#ifdef __unix__
    #include <sys/stat.h>
    #include <dirent.h>
    #include <errno.h>
#endif

#include <cstdio>
#if __cplusplus >= 201703L
    #include <filesystem>
    #include <string_view>
#endif
#include <system_error>
#include <string>

#include "testing/testdefs.h"

namespace testing {
namespace utils {
namespace details {

#if __cplusplus < 201703L
    void create_directory(const std::string& dir, std::error_code& err)
    {
    #ifdef __unix__
        struct ::stat s;
        if (::stat(dir.c_str(), &s) == -1) {
            ::mkdir(dir.c_str(), 0700);
        } else {
            err = std::make_error_code(std::errc::file_exists);
        }
    #else
        #error "is_directory_exists: platform not supported"
    #endif
    }
#endif

inline bool is_directory_exists(const std::string& dir)
{
#if __cplusplus >= 201703L
    return std::filesystem::exists(dir);
#else
    #ifdef __unix__
        ::DIR* dir = ::opendir(dir.c_str());
        if (dir) {
            ::closedir(dir);
            return true;
        } else if (::errno == ENOENT) {
            /* Directory does not exist. */
            return false;
        }
        /* opendir() failed for some other reason. */
        return false;
    #else
        #error "is_directory_exists: platform not supported"
    #endif
#endif
}

void remove_directory_recursively(const std::string& dir, std::error_code& err)
{
#if __cplusplus >= 201703L
    std::filesystem::remove_all(dir, err);
#else
    #ifdef __unix__
        ::DIR* dir = ::opendir(dir.c_str());
        if (! dir) {
            err = std::make_error_code(std::errc::no_such_file_or_directory);
            return;
        }
        struct dirent* ent;
        while (! err && (ent = ::readdir(dir))) {
            if (! ::strcmp(ent->d_name, ".") || ! ::strcmp(ent->d_name, "..")) {
                continue;
            }
            const std::string ent_path = dir + "/" + ent->d_name;
            struct ::stat s;
            if (::stat(ent_path.c_str(), &s) != 0) {
                err = std::make_error_code(std::errc::io_error);
                break;
            }
            if (S_ISDIR(s.st_mode)) {
                remove_directory_recursively(ent_path, err);
            } else {
                if (::unlink(ent_path.c_str()) != 0) {
                    err = std::make_error_code(std::errc::operation_not_permitted);
                }
            }
        }
        ::closedir(dir);
        if (! err) {
            if (::rmdir(dir.c_str()) != 0) {
                err = std::make_error_code(std::errc::operation_not_permitted);
            }
        }
    #else
        #error "remove_directory_recursively: platform not supported"
    #endif
#endif
}

#if __cplusplus < 201703L
    std::string temp_directory_path(std::error_code& err)
    {
    #ifdef __unix__
        const char* p_folder = ::getenv("TMPDIR");
        if (p_folder == NULL) {
            err = std::make_error_code(std::errc::no_such_file_or_directory);
        }
        return p_folder;
    #else
        #error "remove_directory_recursively: platform not supported"
    #endif
    }
#endif

} // namespace details

/*
 * Funstions.
 */

inline std::string create_tmp_dir(const std::string& prefix);
inline bool remove_dir(const std::filesystem::path& dir);
inline std::string unique_path(std::string prefix = std::string());

inline std::string create_tmp_dir(const std::string& prefix)
{
#if __cplusplus >= 201703L
    namespace fs = std::filesystem;
    using path_t = fs::path;
#else
    namespace fs = ::testing::utils::details;
    using path_t = std::string;
#endif

    std::error_code err;
    path_t tmp_dir = fs::temp_directory_path(err);
    if (err) {
        return {};
    }

    const std::string tmp_directory_name = unique_path(prefix);
    if (tmp_directory_name.empty()) {
        return {};
    }
#if __cplusplus >= 201703L
    tmp_dir /= tmp_directory_name;
#else
    tmp_dir += "/" + tmp_directory_name;
#endif
    fs::create_directory(tmp_dir, err);
    if (err) {
        return {};
    }
    return tmp_dir.string();
}

inline bool remove_dir(const std::string& dir)
{
    if (! details::is_directory_exists(dir)) {
        return false;
    }

    std::error_code err;
    details::remove_directory_recursively(dir, err);
    return (! err);
}

#ifdef __unix__
    inline int mem_usage()
    {
        static const std::string statm_path = "/proc/self/statm";
        unsigned long dummu;
        unsigned long resident;

        FILE *f = ::fopen(statm_path.c_str(), "r");
        if (!f) {
            return -1;
        }

        if (::fscanf(f,"%lu %lu", &dummu, &resident) != 2) {
            resident = -1;
        }
        ::fclose(f);
        return resident;
    }
#endif

inline std::string unique_path(std::string prefix)
{
    char tmp_name_buffer[L_tmpnam];
    char* p_tmp_name = ::tmpnam_r(tmp_name_buffer);
    if (! p_tmp_name) {
        return {};
    }

    std::string_view tmp_name = tmp_name_buffer;
    const size_t pos = tmp_name.rfind('/');
    if (pos == std::string_view::npos) {
        prefix += tmp_name;
    } else {
        prefix += tmp_name.substr(pos + 1, tmp_name.size() - pos - 1);
    }

    return prefix;
}

/*
 * Classes.
 */

class base_tester : public ::testing::Test
{
public:
    explicit base_tester(const std::string& test_name)
        : ::testing::Test()
        , m_test_name(test_name)
    {}

    virtual void SetUp() override
    {
        m_work_dir = create_tmp_dir(m_test_name + "_");
        ASSERT_TRUE(! m_work_dir.empty());
    }

    virtual void TearDown() override { remove_dir(m_work_dir); }

    const std::string& work_dir() const { return m_work_dir; }

private:
    const std::string m_test_name;
    std::string m_work_dir;
};

class base_env : public ::testing::Environment
{
public:
    explicit base_env(const std::string& test_name)
        : ::testing::Environment()
        , m_test_name(test_name)
    {}

    virtual void SetUp() override
    {
        m_work_dir = create_tmp_dir(m_test_name + "_");
        ASSERT_TRUE(! m_work_dir.empty());
    }

    virtual void TearDown() override { remove_dir(m_work_dir); }

    const std::string& work_dir() const { return m_work_dir; }

private:
    const std::string m_test_name;
    std::string m_work_dir;
};

} // namespace utils
} // namespace testing

#endif /* _TESTING_UTILS_H */
