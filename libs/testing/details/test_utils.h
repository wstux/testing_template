/*
 * The MIT License
 *
 * Copyright 2023 Chistyakov Alexander.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _TESTING_TEST_UTILS_H
#define _TESTING_TEST_UTILS_H

#include <iostream>
#include <memory>

#include "testing/details/timer.h"

namespace testing {
namespace details {

class itest_suite
{
public:
    using ptr = std::shared_ptr<itest_suite>;

    virtual void test_body() = 0;
};

template<typename TType>
class suite_decorator final : public itest_suite
{
public:
    using ptr = std::shared_ptr<suite_decorator>;

    explicit suite_decorator(const typename TType::ptr& p_test)
        : m_p_test(p_test)
    {}

    virtual void test_body() override { m_p_test->run(); }

private:
    typename TType::ptr m_p_test;
};

class test_failer final
{
public:
    using ptr = std::shared_ptr<test_failer>;

    void init_case() { m_is_ut_failed = false; }

    bool is_case_failed() { return m_is_ut_failed; }

    void fail() { m_is_ut_failed = true; }

    static test_failer& get_instance()
    {
        static bool is_once = true;
        if (is_once) {
            is_once = false;
            m_p_instance.reset(new test_failer());
        }
        return *m_p_instance.get();
    }

private:
    bool m_is_ut_failed = false;

    static std::unique_ptr<test_failer> m_p_instance;
};

std::unique_ptr<test_failer> test_failer::m_p_instance = nullptr;

using case_name_t = std::string;
using test_name_t = std::string;
using type_name_t = std::string;
using test_descr_t = std::pair<test_name_t, itest_suite::ptr>;
using test_list_t = std::vector<test_descr_t>;

inline void init_case() { test_failer::get_instance().init_case(); }

inline bool is_case_failed() { return test_failer::get_instance().is_case_failed(); }

class test_case final
{
public:
    using ptr = std::shared_ptr<test_case>;

    explicit test_case(const case_name_t& case_name)
        : m_case_name(case_name)
    {}

    bool insert_case(const test_name_t& test_name, const itest_suite::ptr& p_suite)
    {
        m_tests.emplace_back(test_name, p_suite);
        return true;
    }

    int run_all_cases() const
    {
        const std::string prefix = std::to_string(m_tests.size()) + " tests from " + m_case_name;
    
        std::cout << "[----------] " << prefix << std::endl;
        timer suite_sw(true);
        const int failed_count = run_tests();
        const double suite_ms = suite_sw.value_ms();
        std::cout << "[----------] " << prefix << " (" << suite_ms << " ms)" << std::endl << std::endl;

        return failed_count;
    }

    size_t tests_count() const { return m_tests.size(); }

private:
    static bool is_disabled(const std::string& test_name)
    {
        return test_name.rfind("DISABLED", 0) == 0;
    }

    int run_tests() const
    {
        int failed_count = 0;
        for (const test_descr_t& descr : m_tests) {
            const test_name_t& test_name = descr.first;
            const itest_suite::ptr& p_suite = descr.second;

            if (is_disabled(test_name)) {
                std::cout << "[DISABLED  ] " << m_case_name << "." << test_name << std::endl;
                continue;
            }

            init_case();
            std::cout << "[RUN       ] " << m_case_name << "." << test_name << std::endl;

            timer test_sw(true);
            p_suite->test_body();
            const double test_ms = test_sw.value_ms();

            failed_count += (is_case_failed() != 0) ? 1 : 0;
            const std::string res_str = (is_case_failed() == 0) ? "[       OK ] " : "[   FAILED ] ";
            std::cout << res_str << m_case_name << "." << test_name << " (" << test_ms << " ms)" << std::endl;
        }

        return failed_count;
    }

private:
    const case_name_t m_case_name;
    test_list_t m_tests;
};

} // namespace details
} // namespace testing

#endif /* _TESTING_TEST_UTILS_H */

