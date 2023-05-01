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
#include "testing/details/typed_test_utils.h"

namespace testing {

class Test
{
public:
    using ptr = std::shared_ptr<Test>;

    virtual ~Test() = default;

    void run()
    {
        testing::details::init_case();
        SetUp();
        if (! testing::details::is_case_failed()) {
            test_body();
        }
        TearDown();
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

} // namespace testing

#endif /* _TESTING_TESTING_INTERFACE_H */

