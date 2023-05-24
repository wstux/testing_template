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

#ifndef _TESTING_PERFDEFS_H
#define _TESTING_PERFDEFS_H

#include "testing/details/perfdefs_impl.h"
#include "testing/details/tester.h"
#include "testing/testing_interface.h"

/*
 */

#define MESSAGE()   __PERF_MESSAGE()

/*
 */

#define PERF_ASSERT_FALSE(cond)                     \
    if (! (cond)) ;                                 \
    else return __FATAL_PERF_MESSAGE(cond)

#define PERF_ASSERT_TRUE(cond)                      \
    if ((cond)) ;                                   \
    else return __FATAL_PERF_MESSAGE(cond)

/*
 */

#define PERF_TEST_F(fixture, test_name)             \
    __PERF_TEST_F_IMPL(fixture, test_name)

#define TYPED_PERF_TEST_SUITE(case_name, types)     \
    __INIT_TYPED_PERF_TEST_SUITE(case_name, types)

#define TYPED_PERF_TEST(case_name, types)           \
    __TYPED_PERF_TEST_IMPL(case_name, types)

#define RUN_ALL_PERF_TESTS() ::testing::details::tester::run_all_perf_tests()

#endif /* _TESTING_PERFDEFS_H */
