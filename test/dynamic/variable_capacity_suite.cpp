///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// Empty
//-----------------------------------------------------------------------------

namespace empty_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(data.empty());
}

void test_boolean()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST(!data.empty());
}

void test_integer()
{
    {
        signed char value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        unsigned char value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        signed short int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        unsigned short int value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        signed int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        unsigned int value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        signed long int value = 1L;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        unsigned long int value = 1UL;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        signed long long int value = 1LL;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        unsigned long long int value = 1ULL;
        variable data(value);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
}

void test_number()
{
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
}

void test_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        variable data("");
        TRIAL_PROTOCOL_TEST(data.empty());
    }
}

void test_wstring()
{
    {
        variable data(L"bravo");
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        variable data(L"");
        TRIAL_PROTOCOL_TEST(data.empty());
    }
}

void test_u16string()
{
    {
        variable data(u"charlie");
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        variable data(u"");
        TRIAL_PROTOCOL_TEST(data.empty());
    }
}

void test_u32string()
{
    {
        variable data(U"delta");
        TRIAL_PROTOCOL_TEST(!data.empty());
    }
    {
        variable data(U"");
        TRIAL_PROTOCOL_TEST(data.empty());
    }
}

void test_array()
{
    variable data = array::make();
    TRIAL_PROTOCOL_TEST(data.empty());
    data = array::make({ 1, 2 });
    TRIAL_PROTOCOL_TEST(!data.empty());
}

void test_map()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST(data.empty());
    data = map::make({ {"alpha", 1} });
    TRIAL_PROTOCOL_TEST(!data.empty());
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_map();
}

} // namespace empty_suite

//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------

namespace size_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
}

void test_boolean()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
}

void test_integer()
{
    {
        signed char value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        unsigned char value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        signed short int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        unsigned short int value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        signed int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        unsigned int value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        signed long int value = 1L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        unsigned long int value = 1UL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        signed long long int value = 1LL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        unsigned long long int value = 1ULL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
}

void test_number()
{
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
}

void test_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        variable data("");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
}

void test_wstring()
{
    {
        variable data(L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        variable data(L"");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
}

void test_u16string()
{
    {
        variable data(u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        variable data(u"");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
}

void test_u32string()
{
    {
        variable data(U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
    {
        variable data(U"");
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    }
}

void test_array()
{
    variable data = array::make({ 1, 2, 3 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
}

void test_array_with_size()
{
    variable data = array::repeat(3, 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
}

void test_map()
{
    variable data = map::make({ {"alpha", 1} });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_array_with_size();
    test_map();
}

} // namespace size_suite

//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------

namespace max_size_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 0);
}

void test_boolean()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
}

void test_integer()
{
    {
        signed char value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        unsigned char value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        signed short int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        unsigned short int value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        signed int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        unsigned int value = 1U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        signed long int value = 1L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        unsigned long int value = 1UL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        signed long long int value = 1LL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        unsigned long long int value = 1ULL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
}

void test_number()
{
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
    }
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
}

void test_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
}

void test_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
}

void test_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), 1);
}

void test_array()
{
    variable::array_type value;
    variable data = array::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), value.max_size());
}

void test_map()
{
    variable::map_type value;
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.max_size(), value.max_size());
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_map();
}

} // namespace max_size_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    empty_suite::run();
    size_suite::run();
    max_size_suite::run();

    return boost::report_errors();
}
