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

#include "testing/testdefs.h"

class test_fixture_1 : public ::testing::Test
{
public:
    virtual void SetUp() override
    {
        EXPECTED_TRUE(1 == 1);
    }
};

class test_fixture_2 : public ::testing::Test
{
public:
    virtual void SetUp() override
    {
        EXPECTED_TRUE(1 == 2);
    }
};

template<typename TType>
class typed_fixture_1 : public ::testing::Test
{
public:
    virtual void SetUp() override
    {
        EXPECTED_TRUE(1 == 1);
    }
};

template<typename TType>
class typed_fixture_2 : public ::testing::Test
{
public:
    virtual void SetUp() override
    {
        EXPECTED_TRUE(1 == 1);
    }
};

using types_1 = testing::Types<uint8_t, uint16_t, uint32_t>;
TYPED_TEST_SUITE(typed_fixture_1, types_1);

using types_2 = testing::Types<uint8_t, uint16_t, uint32_t>;
TYPED_TEST_SUITE(typed_fixture_2, types_2);

TEST(case_name_1, assert_true)
{
    ASSERT_TRUE(2 == 1);
    EXPECTED_TRUE(2 == 1);
}

TEST(case_name_1, assert_false)
{
    ASSERT_FALSE(1 == 1);
    EXPECTED_TRUE(2 == 1);
}

TEST(case_name_1, expected_false)
{
    EXPECTED_FALSE(1 == 2);
}

TEST(case_name_1, expected_true)
{
    EXPECTED_TRUE(1 == 1);
}

TEST(case_name_2, expected_false)
{
    EXPECTED_FALSE(1 == 2);
}

TEST(case_name_2, expected_eq)
{
    EXPECTED_EQ(1, 1);
}

TEST_F(test_fixture_1, expected_true)
{
    EXPECTED_TRUE(1 == 1);
}

TEST_F(test_fixture_1, expected_false)
{
    EXPECTED_FALSE(1 == 2);
}

TEST_F(test_fixture_2, expected_true)
{
    EXPECTED_TRUE(1 == 1);
}

TYPED_TEST(typed_fixture_1, expected_true)
{
    EXPECTED_TRUE(1 == 1);
}

TYPED_TEST(typed_fixture_1, expected_false)
{
    EXPECTED_FALSE(1 == 2);
}

TYPED_TEST(typed_fixture_2, test_name_1)
{
    EXPECTED_TRUE(1 == 1);
}

int main(int /*argc*/, char** /*argv*/)
{
    return RUN_ALL_TESTS();
}

