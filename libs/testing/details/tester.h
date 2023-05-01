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

#ifndef _TESTING_TESTER_H
#define _TESTING_TESTER_H

#include <algorithm>
#include <map>
#include <memory>
#include <numeric>
#include <vector>

#include "testing/details/test_utils.h"
#include "testing/details/typed_test_utils.h"

namespace testing {
namespace details {

class tester final
{
public:
    bool insert_test(const case_name_t& case_name, const test_name_t& test_name,
                     const itest_suite::ptr& p_suite)
    {
        std::map<case_name_t, size_t>::iterator it = m_case_names.find(case_name);
        if (it == m_case_names.cend()) {
            it = m_case_names.emplace(case_name, m_tests.size()).first;
            m_tests.emplace_back(std::make_shared<test_case>(case_name));
        }

        const size_t idx = it->second;
        return m_tests[idx]->insert_case(test_name, p_suite);
    }

    int run_tests() const
    {
        const size_t tests_cnt = tests_count();
        size_t failed_count = 0;

        std::cout << "[==========] Running " << tests_cnt << " tests from "
                  << m_tests.size() << " test suits." << std::endl;
        timer total_sw(true);
        for (const test_case::ptr& p_test : m_tests) {
            failed_count += p_test->run_all_cases();
        }

        const double total_ms = total_sw.value_ms();
        std::cout << "[==========] " << tests_cnt << " tests from " << m_tests.size()
                  << " test suits ran (" << total_ms << " ms)." << std::endl;
        if (failed_count != 0) {
            std::cout << "[  FAILED  ] " << failed_count << " tests." << std::endl;
        }
        std::cout << "[  PASSED  ] " << tests_cnt << " tests." << std::endl;

        return (failed_count == 0) ? 0 : 1;
    }

    static bool insert(const case_name_t& case_name, const test_name_t& test_name,
                       const itest_suite::ptr& p_suite)
    {
        return get_instance().insert_test(case_name, test_name, p_suite);
    }

    template<template<typename> class TCase, typename TTypes>
    static bool insert_typed_case(const case_name_t& case_name,
                                  const test_name_t& test_name)
    {
        return typed_test_inserter<tester, TCase, TTypes>::insert(get_instance(),
                                case_name, test_name, 0);
    }

    static tester& get_instance()
    {
        static bool is_once = true;
        if (is_once) {
            is_once = false;
            m_p_instance.reset(new tester());
        }
        return *m_p_instance.get();
    }

    static int run_all_tests() { return get_instance().run_tests(); }

private:
    tester() = default;

    size_t tests_count() const
    {
        return std::accumulate(m_tests.cbegin(), m_tests.cend(), 0,
            [](size_t a, const test_case::ptr& b) -> size_t { return a + b->tests_count(); });
    }

private:
    std::map<case_name_t, size_t> m_case_names;
    std::vector<test_case::ptr> m_tests;

    static std::unique_ptr<tester> m_p_instance;
};

std::unique_ptr<tester> tester::m_p_instance = nullptr;

std::ostream& fail()
{
    test_failer::get_instance().fail();
    return std::cerr;
}

} // namespace details
} // namespace testing

#endif /* _TESTING_TESTER_H */

