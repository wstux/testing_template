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

#ifndef _TESTING_PERF_TESTER_H
#define _TESTING_PERF_TESTER_H

#include "testing/details/common_tester.h"
#include "testing/details/test_utils.h"

namespace testing {
namespace details {
namespace perf {

class tester final : public common_tester<itest_perf>
{
    using base = common_tester<itest_perf>;

public:
    void add_env(ienv::ptr p_env) { base::add_env(p_env); }

    static bool insert(const std::string& case_name, const std::string& test_name,
                       const itest_perf::ptr& p_suite)
    {
        return get_instance().insert_test(case_name, test_name, p_suite);
    }

    template<template<typename> class TCase, typename TTypes>
    static bool insert_typed_case(const std::string& case_name, const std::string& test_name)
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

private:
    static std::unique_ptr<tester> m_p_instance;
};

std::unique_ptr<tester> tester::m_p_instance = nullptr;

} // namespace perf
} // namespace details
} // namespace testing

#endif /* _TESTING_PERF_TESTER_H */
