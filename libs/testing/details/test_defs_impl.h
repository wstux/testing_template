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

#ifndef _TESTING_TEST_DEFS_IMPL_H
#define _TESTING_TEST_DEFS_IMPL_H

#include "testing/details/commondefs.h"

#define __TEST_IMPL(case_name, test_name)                                   \
    class __TEST_CLASS_NAME(case_name, test_name)                           \
        : public ::testing::details::itest_suite                            \
    {                                                                       \
    public:                                                                 \
        virtual void test_body() override final;                            \
    };                                                                      \
    [[maybe_unused]] static bool __TEST_INSERT_RES(case_name, test_name) =  \
        ::testing::details::tester::insert(                                 \
            __CVT_TO_STRING(case_name), __CVT_TO_STRING(test_name),         \
            std::make_shared<__TEST_CLASS_NAME(case_name, test_name)>());   \
    void __TEST_CLASS_NAME(case_name, test_name)::test_body()

#endif /* _TESTING_TEST_DEFS_IMPL_H */

