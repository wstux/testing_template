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

#ifndef _TESTING_TEST_F_DEFS_IMPL_H
#define _TESTING_TEST_F_DEFS_IMPL_H

#include "testing/details/commondefs.h"

#define __TEST_F_IMPL(suite_name, test_name)                                \
    class __TEST_CLASS_NAME(suite_name, test_name) : public suite_name      \
    {                                                                       \
    public:                                                                 \
        using decorator = ::testing::details::suite_decorator<              \
                    __TEST_CLASS_NAME(suite_name, test_name)>;              \
        using suite_ptr = ::testing::details::itest_suite::ptr;             \
        __TEST_CLASS_NAME(suite_name, test_name)() {}                       \
        static suite_ptr make_suite_ptr()                                   \
        {                                                                   \
            std::shared_ptr<__TEST_CLASS_NAME(suite_name, test_name)> p_ =  \
                std::make_shared<__TEST_CLASS_NAME(suite_name,              \
                                                   test_name)>();           \
            return std::make_shared<decorator>(p_);                         \
        }                                                                   \
    private:                                                                \
        virtual void test_body();                                           \
    };                                                                      \
    [[maybe_unused]] static bool __TEST_INSERT_RES(suite_name, test_name) = \
        ::testing::details::tester::insert(                                 \
            __CVT_TO_STRING(suite_name), __CVT_TO_STRING(test_name),        \
            __TEST_CLASS_NAME(suite_name, test_name)::make_suite_ptr());    \
    void __TEST_CLASS_NAME(suite_name, test_name)::test_body()

#endif /* _TESTING_TEST_F_DEFS_IMPL_H */

