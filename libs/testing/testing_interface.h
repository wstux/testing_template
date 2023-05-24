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

#ifndef _TESTING_TESTING_INTERFACE_H
#define _TESTING_TESTING_INTERFACE_H

#include <memory>

#include "testing/details/test_utils.h"
#include "testing/details/tester.h"
#include "testing/details/timer.h"
#include "testing/details/typed_test_utils.h"

namespace testing {

class Environment
{
public:
    virtual ~Environment() = default;

    virtual void SetUp() {}

    virtual void TearDown() {}
};

inline Environment* AddGlobalTestEnvironment(Environment* p_env)
{
    namespace ut = ::testing::details;

    typename ut::env_decorator<Environment>::ptr p_env_dec =
        std::make_shared<ut::env_decorator<Environment>>(p_env);
    ut::tester::get_instance().add_env(p_env_dec);
    return p_env;
}

class Test
{
public:
    virtual ~Test() = default;

    void run()
    {
        namespace ut = ::testing::details;

        ut::init_case();
        SetUp();
        if (! ut::is_case_failed()) {
            test_body();
        }
        TearDown();
    }

    double run_perf()
    {
        namespace ut = ::testing::details;

        ut::init_case();
        SetUp();
        double msecs = 0.0;
        if (! ut::is_case_failed()) {
            ut::timer sw(true);
            test_body();
            msecs = sw.value_ms();
        }
        TearDown();
        return msecs;
    }

protected:
    Test() {}

    virtual void SetUp() {}

    virtual void TearDown() {}

private:
    virtual void test_body() = 0;
};

template<typename T1  = details::none_t, typename T2  = details::none_t,
         typename T3  = details::none_t, typename T4  = details::none_t,
         typename T5  = details::none_t, typename T6  = details::none_t,
         typename T7  = details::none_t, typename T8  = details::none_t,
         typename T9  = details::none_t, typename T10 = details::none_t,
         typename T11 = details::none_t, typename T12 = details::none_t,
         typename T13 = details::none_t, typename T14 = details::none_t,
         typename T15 = details::none_t>
struct Types
{
    typedef details::type_15<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11,
                             T12, T13, T14, T15> type;
};

template <>
struct Types<details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t>
{
    typedef details::type_0 type;
};
template <typename T1>
struct Types<T1, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t>
{
    typedef details::type_1<T1> type;
};
template <typename T1, typename T2>
struct Types<T1, T2, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t>
{
    typedef details::type_2<T1, T2> type;
};
template <typename T1, typename T2, typename T3>
struct Types<T1, T2, T3, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t>
{
    typedef details::type_3<T1, T2, T3> type;
};
template <typename T1, typename T2, typename T3, typename T4>
struct Types<T1, T2, T3, T4, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t>
{
    typedef details::type_4<T1, T2, T3, T4> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct Types<T1, T2, T3, T4, T5, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t>
{
    typedef details::type_5<T1, T2, T3, T4, T5> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6>
struct Types<T1, T2, T3, T4, T5, T6, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t>
{
    typedef details::type_6<T1, T2, T3, T4, T5, T6> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7>
struct Types<T1, T2, T3, T4, T5, T6, T7, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t, details::none_t>
{
    typedef details::type_7<T1, T2, T3, T4, T5, T6, T7> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, details::none_t, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t>
{
    typedef details::type_8<T1, T2, T3, T4, T5, T6, T7, T8> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t,
             details::none_t>
{
    typedef details::type_9<T1, T2, T3, T4, T5, T6, T7, T8, T9> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, details::none_t,
             details::none_t, details::none_t, details::none_t, details::none_t>
{
    typedef details::type_10<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10,
          typename T11>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, details::none_t,
             details::none_t, details::none_t, details::none_t>
{
    typedef details::type_11<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10,
          typename T11, typename T12>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
             details::none_t, details::none_t, details::none_t>
{
    typedef details::type_12<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10,
                             T11, T12> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10,
          typename T11, typename T12, typename T13>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
             details::none_t, details::none_t>
{
    typedef details::type_13<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10,
                             T11, T12, T13> type;
};
template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8, typename T9, typename T10,
          typename T11, typename T12, typename T13, typename T14>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14,
             details::none_t>
{
    typedef details::type_14<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10,
                             T11, T12, T13, T14> type;
};

} // namespace testing

#endif /* _TESTING_TESTING_INTERFACE_H */

