#ifndef _TESTING_UTILS_H
#define _TESTING_UTILS_H

#include <cstdio>
#if __cplusplus >= 201703L
    #include <filesystem>
#endif
#include <string_view>
#include <system_error>
#include <string>

#include "testing/testdefs.h"

namespace testing {
namespace utils {

/*
 * Funstions.
 */

#if __cplusplus >= 201703L
inline std::filesystem::path create_tmp_dir(const std::string& prefix);
inline bool remove_dir(const std::filesystem::path& dir);
#endif
inline std::string unique_path(std::string prefix = std::string());

#if __cplusplus >= 201703L
inline std::filesystem::path create_tmp_dir(const std::string& prefix)
{
    std::error_code err;
    std::filesystem::path tmp_dir = std::filesystem::temp_directory_path(err);
    if (! err) {
        return {};
    }

    const std::string tmp_directory_name = unique_path(prefix);
    if (tmp_directory_name.empty()) {
        return {};
    }
    tmp_dir /= tmp_directory_name;
    std::filesystem::create_directory(tmp_dir, err);
    if (! err) {
        return {};
    }
    return tmp_dir;
}

inline bool remove_dir(const std::filesystem::path& dir)
{
    if (! std::filesystem::exists(dir)) {
        return false;
    }

    std::error_code err;
    std::filesystem::remove_all(dir, err);
    return (! err);
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

#if __cplusplus >= 201703L
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

    const std::filesystem::path& WorkDir() const { return m_work_dir; }

private:
    const std::string m_test_name;
    std::filesystem::path m_work_dir;
};
#endif

} // namespace utils
} // namespace testing

#endif /* _TESTING_UTILS_H */
