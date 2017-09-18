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
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// Append
//-----------------------------------------------------------------------------

namespace append_suite
{

void append_null_with_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data += variable();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void append_null_with_boolean()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void append_null_with_integer()
{
    {
        signed char value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        unsigned char value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        signed short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        unsigned short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        signed int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        signed long int value = 2L;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void append_null_with_number()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 3.0f);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 3.0);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 3.0L);
    }
}

void append_null_with_string()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha");
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += variable(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha");
    }
}

void append_null_with_array()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void append_null_with_map()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable expect = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data += map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable expect = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void append_boolean_with_null()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
}

void append_boolean_with_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void append_boolean_with_integer()
{
    {
        signed char value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        unsigned char value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        signed short int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        unsigned short int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        signed int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        unsigned int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        signed long int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        unsigned long int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        signed long long int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        unsigned long long int value = 2;
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
}

void append_boolean_with_number()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        data += variable(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
}

void append_boolean_with_string()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=("alpha"),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(L"alpha"),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(L"alpha")),
                                        error,
                                        "incompatible type");
    }
}

void append_boolean_with_array()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=({ true, "alpha" }),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                        error,
                                        "incompatible type");
    }
}

void append_boolean_with_map()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=({{ "alpha", "hydrogen" }}),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                        error,
                                        "incompatible type");
    }
}

void append_signed_int_with_null()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
}

void append_signed_int_with_boolean()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 3);
}

void append_signed_int_with_integer()
{
    signed int input = 2;
    {
        signed char value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        unsigned char value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        signed short int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        unsigned short int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        signed int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        unsigned int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        signed long int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        unsigned long int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        signed long long int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        unsigned long long int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
}

void append_signed_int_with_number()
{
    signed int input = 2;
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
}

void append_signed_int_with_string()
{
    {
        signed int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                        error,
                                        "incompatible type");
    }
    {
        signed int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(L"alpha")),
                                        error,
                                        "incompatible type");
    }
}

void append_signed_int_with_array()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_signed_int_with_map()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_unsigned_int_with_null()
{
    unsigned int input = 2U;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
}

void append_unsigned_int_with_boolean()
{
    unsigned int input = 2U;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 3U);
}

void append_unsigned_int_with_integer()
{
    unsigned int input = 2U;
    {
        signed char value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        unsigned char value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        signed short int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        unsigned short int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        signed int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        unsigned int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        signed long int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        unsigned long int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        signed long long int value = 3;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        unsigned long long int value = 3U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
}

void append_unsigned_int_with_number()
{
    unsigned int input = 2U;
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data += variable(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 5U);
    }
}

void append_unsigned_int_with_string()
{
    {
        unsigned int input = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                        error,
                                        "incompatible type");
    }
    {
        unsigned int input = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(L"alpha")),
                                        error,
                                        "incompatible type");
    }
}

void append_unsigned_int_with_array()
{
    unsigned int input = 2U;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_unsigned_int_with_map()
{
    unsigned int input = 2U;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_float_with_null()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 3.0f);
}

void append_float_with_boolean()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 4.0f);
}

void append_float_with_integer()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data += variable(2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 5.0f);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data += variable(2U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 5.0f);
    }
}

void append_float_with_number()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data += variable(2.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 5.0f);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data += variable(2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 5.0f);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data += variable(2.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 5.0f);
    }
}

void append_float_with_string()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(L"alpha")),
                                        error,
                                        "incompatible type");
    }
}

void append_float_with_array()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_float_with_map()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_double_with_null()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 3.0);
}

void append_double_with_boolean()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 4.0);
}

void append_double_with_integer()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data += variable(2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 5.0);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data += variable(2U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 5.0);
    }
}

void append_double_with_number()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data += variable(2.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 5.0);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data += variable(2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 5.0);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data += variable(2.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 5.0);
    }
}

void append_double_with_string()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(L"alpha")),
                                        error,
                                        "incompatible type");
    }
}

void append_double_with_array()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_double_with_map()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_long_double_with_null()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 3.0L);
}

void append_long_double_with_boolean()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 4.0L);
}

void append_long_double_with_integer()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data += variable(2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 5.0L);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data += variable(2U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 5.0L);
    }
}

void append_long_double_with_number()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data += variable(2.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 5.0L);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data += variable(2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 5.0L);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data += variable(2.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 5.0L);
    }
}

void append_long_double_with_string()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(L"alpha")),
                                        error,
                                        "incompatible type");
    }
}

void append_long_double_with_array()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_long_double_with_map()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_string_with_null()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data += null;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data += null;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha");
    }
}

void append_string_with_boolean()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(true)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(true)),
                                        error,
                                        "incompatible type");
    }
}

void append_string_with_integer()
{
    // string - signed
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2)),
                                        error,
                                        "incompatible type");
    }
    // string - unsigned
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2U)),
                                        error,
                                        "incompatible type");
    }
    // wstring - signed
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2)),
                                        error,
                                        "incompatible type");
    }
    // wstring - unsigned
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2U)),
                                        error,
                                        "incompatible type");
    }
}

void append_string_with_number()
{
    // string - float
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0f)),
                                        error,
                                        "incompatible type");
    }
    // string - double
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0)),
                                        error,
                                        "incompatible type");
    }
    // string - long double
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0L)),
                                        error,
                                        "incompatible type");
    }
    // wstring - float
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0f)),
                                        error,
                                        "incompatible type");
    }
    // wstring - double
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0)),
                                        error,
                                        "incompatible type");
    }
    // wstring - long double
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0L)),
                                        error,
                                        "incompatible type");
    }
}

void append_string_with_string()
{
    // string - string literal
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data += "-bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha-bravo");
    }
    // string - string
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data += variable("-bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha-bravo");
    }
    // string - wstring literal
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((data += L"-bravo"),
                                        error,
                                        "incompatible type");
    }
    // string - wstring
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((data += variable(L"-bravo")),
                                        error,
                                        "incompatible type");
    }
    // wstring - string literal
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((data += "-bravo"),
                                        error,
                                        "incompatible type");
    }
    // wstring - string
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((data += variable("-bravo")),
                                        error,
                                        "incompatible type");
    }
    // wstring - wstring literal
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data += L"-bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha-bravo");
    }
    // wstring - wstring
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data += variable(L"-bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha-bravo");
    }
}

void append_string_with_array()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                        error,
                                        "incompatible type");
    }
}

void append_string_with_map()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                        error,
                                        "incompatible type");
    }
}

void append_array_with_null()
{
    variable data = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_boolean()
{
    variable data = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = array::make({ true, 2, 3.0, "alpha", true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_integer()
{
    {
        variable data = { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 4;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 4 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 4U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 4U });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void append_array_with_number()
{
    {
        variable data = { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 6.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0f });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 6.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 6.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0L });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void append_array_with_string()
{
    {
        variable data = { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += "bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", "bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = { true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += L"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void append_array_with_array()
{
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data += { 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data += array::make({ 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void append_array_with_map()
{
    variable data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_map_with_null()
{
    variable data =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
}

void append_map_with_boolean()
{
    variable data =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(true)),
                                    error,
                                    "incompatible type");
}

void append_map_with_integer()
{
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2U)),
                                        error,
                                        "incompatible type");
    }
}

void append_map_with_number()
{
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0f)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0L)),
                                        error,
                                        "incompatible type");
    }
}

void append_map_with_string()
{
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                        error,
                                        "incompatible type");
    }
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(L"alpha")),
                                        error,
                                        "incompatible type");
    }
}

void append_map_with_array()
{
    variable data =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, 2 })),
                                    error,
                                    "incompatible type");
}

void append_map_with_map()
{
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
        data += {{"charlie", "lithium"}};
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    }
    {
        variable data =
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            };
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
        data += map::make({{"charlie", "lithium"}});
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    }
}

void run()
{
    append_null_with_null();
    append_null_with_boolean();
    append_null_with_integer();
    append_null_with_number();
    append_null_with_string();
    append_null_with_array();
    append_null_with_map();

    append_boolean_with_null();
    append_boolean_with_boolean();
    append_boolean_with_integer();
    append_boolean_with_number();
    append_boolean_with_string();
    append_boolean_with_array();
    append_boolean_with_map();

    append_signed_int_with_null();
    append_signed_int_with_boolean();
    append_signed_int_with_integer();
    append_signed_int_with_number();
    append_signed_int_with_string();
    append_signed_int_with_array();
    append_signed_int_with_map();

    append_unsigned_int_with_null();
    append_unsigned_int_with_boolean();
    append_unsigned_int_with_integer();
    append_unsigned_int_with_number();
    append_unsigned_int_with_string();
    append_unsigned_int_with_array();
    append_unsigned_int_with_map();

    append_float_with_null();
    append_float_with_boolean();
    append_float_with_integer();
    append_float_with_number();
    append_float_with_string();
    append_float_with_array();
    append_float_with_map();

    append_double_with_null();
    append_double_with_boolean();
    append_double_with_integer();
    append_double_with_number();
    append_double_with_string();
    append_double_with_array();
    append_double_with_map();

    append_long_double_with_null();
    append_long_double_with_boolean();
    append_long_double_with_integer();
    append_long_double_with_number();
    append_long_double_with_string();
    append_long_double_with_array();
    append_long_double_with_map();

    append_string_with_null();
    append_string_with_boolean();
    append_string_with_integer();
    append_string_with_number();
    append_string_with_string();
    append_string_with_array();
    append_string_with_map();

    append_array_with_null();
    append_array_with_boolean();
    append_array_with_integer();
    append_array_with_number();
    append_array_with_string();
    append_array_with_array();
    append_array_with_map();

    append_map_with_null();
    append_map_with_boolean();
    append_map_with_integer();
    append_map_with_number();
    append_map_with_string();
    append_map_with_array();
    append_map_with_map();
}

} // namespace append_suite

//-----------------------------------------------------------------------------
// Addition
//-----------------------------------------------------------------------------

namespace addition_suite
{

void add_null_with_null()
{
    // Cannot do null + null
}

void add_null_with_boolean()
{
    auto data = null + variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void add_null_with_integer()
{
    {
        auto data = null + variable(2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
    }
    {
        auto data = null + variable(2U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
    }
}

void add_null_with_number()
{
    {
        auto data = null + variable(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 3.0f);
    }
    {
        auto data = null + variable(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 3.0);
    }
    {
        auto data = null + variable(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 3.0L);
    }
}

void add_null_with_string()
{
    {
        auto data = null + variable("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
    }
    {
        auto data = null + variable(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha");
    }
}

void add_null_with_array()
{
    auto data = null + array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_null_with_map()
{
    auto data = null + map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    variable expect = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_boolean_with_null()
{
    auto data = variable(true) + null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void add_boolean_with_boolean()
{
    auto data = variable(true) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void add_boolean_with_integer()
{
    {
        auto data = variable(true) + 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        auto data = variable(true) + 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
}

void add_boolean_with_number()
{
    {
        auto data = variable(true) + 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        auto data = variable(true) + 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        auto data = variable(true) + 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
}

void add_boolean_with_string()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(L"alpha"),
                                        error,
                                        "incompatible type");
    }
}

void add_boolean_with_array()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + array::make({ true, "alpha" }),
                                    error,
                                    "incompatible type");
}

void add_boolean_with_map()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + map::make({{ "alpha", "hydrogen" }}),
                                    error,
                                    "incompatible type");
}

void add_integer_with_null()
{
    auto data = variable(2) + null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
}

void add_integer_with_boolean()
{
    auto data = variable(2) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 3);
}

void add_integer_with_integer()
{
    {
        auto data = variable(2) + 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 4);
    }
    {
        auto data = variable(2) + 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 4);
    }
}

void add_integer_with_number()
{
    {
        auto data = variable(2) + 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        auto data = variable(2) + 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
    {
        auto data = variable(2) + 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 5);
    }
}

void add_integer_with_string()
{
    {
        variable data(2);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(2);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(L"alpha"),
                                        error,
                                        "incompatible type");
    }
}

void add_integer_with_array()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + array::make({ true, "alpha" }),
                                    error,
                                    "incompatible type");
}

void add_integer_with_map()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + map::make({{ "alpha", "hydrogen" }}),
                                    error,
                                    "incompatible type");
}

void add_number_with_null()
{
    auto data = variable(3.0) + null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 3.0);
}

void add_number_with_boolean()
{
    auto data = variable(3.0) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 4.0);
}

void add_number_with_integer()
{
    {
        auto data = variable(3.0) + 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 5.0);
    }
    {
        auto data = variable(3.0) + 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 5.0);
    }
}

void add_number_with_number()
{
    {
        auto data = variable(3.0) + 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 6.0);
    }
    {
        auto data = variable(3.0) + 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 6.0);
    }
    {
        auto data = variable(3.0) + 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 6.0);
    }
}

void add_number_with_string()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(L"alpha"),
                                        error,
                                        "incompatible type");
    }
}

void add_number_with_array()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + array::make({ true, "alpha" }),
                                    error,
                                    "incompatible type");
}

void add_number_with_map()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + map::make({{ "alpha", "hydrogen" }}),
                                    error,
                                    "incompatible type");
}

void add_string_with_null()
{
    {
        auto data = variable("alpha") + null;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
    }
    {
        auto data = variable(L"alpha") + null;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha");
    }
}

void add_string_with_boolean()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(true),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(true),
                                        error,
                                        "incompatible type");
    }
}

void add_string_with_integer()
{
    // string - signed
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2),
                                        error,
                                        "incompatible type");
    }
    // string - unsigned
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2U),
                                        error,
                                        "incompatible type");
    }
    // wstring - signed
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2),
                                        error,
                                        "incompatible type");
    }
    // wstring - unsigned
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2U),
                                        error,
                                        "incompatible type");
    }
}

void add_string_with_number()
{
    // string - float
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0f),
                                        error,
                                        "incompatible type");
    }
    // string - double
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0),
                                        error,
                                        "incompatible type");
    }
    // string - long double
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0L),
                                        error,
                                        "incompatible type");
    }
    // wstring - float
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0f),
                                        error,
                                        "incompatible type");
    }
    // wstring - double
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0),
                                        error,
                                        "incompatible type");
    }
    // wstring - long double
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0L),
                                        error,
                                        "incompatible type");
    }
}

void add_string_with_string()
{
    // string - string
    {
        auto data = variable("alpha") + variable("-bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha-bravo");
    }
    // string - wstring
    {
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((variable("alpha") + variable(L"-bravo")),
                                        error,
                                        "incompatible type");
    }
    // wstring - string
    {
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((variable(L"alpha") + variable("-bravo")),
                                        error,
                                        "incompatible type");
    }
    // wstring - wstring
    {
        auto data = variable(L"alpha") + variable(L"-bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha-bravo");
    }
}

void add_string_with_array()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + array::make({ true, "alpha" }),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + array::make({ true, "alpha" }),
                                        error,
                                        "incompatible type");
    }
}

void add_string_with_map()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + map::make({{ "alpha", "hydrogen" }}),
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + map::make({{ "alpha", "hydrogen" }}),
                                        error,
                                        "incompatible type");
    }
}

void add_array_with_null()
{
    variable data = array::make({ true, 2, 3.0, "alpha" }) + null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_boolean()
{
    variable data = array::make({ true, 2, 3.0, "alpha" }) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = array::make({ true, 2, 3.0, "alpha", true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_integer()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha" }) + 4;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 4 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha" }) + 4U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 4U });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void add_array_with_number()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha" }) + 6.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0f });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha" }) + 6.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha" }) + 6.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0L });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void add_array_with_string()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha" }) + "bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", "bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha" }) + L"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void add_array_with_array()
{
    variable data = array::make({ true, 2 }) + array::make({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_map()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + map::make({{ "alpha", "hydrogen" }}),
                                    error,
                                    "incompatible type");
}

void add_map_with_null()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        }) + null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
}

void add_map_with_boolean()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(true),
                                    error,
                                    "incompatible type");
}

void add_map_with_integer()
{
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2U),
                                        error,
                                        "incompatible type");
    }
}

void add_map_with_number()
{
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0f),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0L),
                                        error,
                                        "incompatible type");
    }
}

void add_map_with_string()
{
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(L"alpha"),
                                        error,
                                        "incompatible type");
    }
}

void add_map_with_array()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + array::make({ true, 2 }),
                                    error,
                                    "incompatible type");
}

void add_map_with_map()
{
    variable data =
        map::make({ { "alpha", "hydrogen" }, { "bravo", "helium" } })
        + map::make({ {"charlie", "lithium"} });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
}

void run()
{
    add_null_with_null();
    add_null_with_boolean();
    add_null_with_integer();
    add_null_with_number();
    add_null_with_string();
    add_null_with_array();
    add_null_with_map();

    add_boolean_with_null();
    add_boolean_with_boolean();
    add_boolean_with_integer();
    add_boolean_with_number();
    add_boolean_with_string();
    add_boolean_with_array();
    add_boolean_with_map();

    add_integer_with_null();
    add_integer_with_boolean();
    add_integer_with_integer();
    add_integer_with_number();
    add_integer_with_string();
    add_integer_with_array();
    add_integer_with_map();

    add_number_with_null();
    add_number_with_boolean();
    add_number_with_integer();
    add_number_with_number();
    add_number_with_string();
    add_number_with_array();
    add_number_with_map();

    add_string_with_null();
    add_string_with_boolean();
    add_string_with_integer();
    add_string_with_number();
    add_string_with_string();
    add_string_with_array();
    add_string_with_map();

    add_array_with_null();
    add_array_with_boolean();
    add_array_with_integer();
    add_array_with_number();
    add_array_with_string();
    add_array_with_array();
    add_array_with_map();

    add_map_with_null();
    add_map_with_boolean();
    add_map_with_integer();
    add_map_with_number();
    add_map_with_string();
    add_map_with_array();
    add_map_with_map();
}

} // namespace addition_suite

//-----------------------------------------------------------------------------
// Subscripting
//-----------------------------------------------------------------------------

namespace subscript_suite
{

void index_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                    error,
                                    "incompatible type");
}

void index_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                    error,
                                    "incompatible type");
}

void index_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                    error,
                                    "incompatible type");
}

void index_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                    error,
                                    "incompatible type");
}

void index_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                        error,
                                        "incompatible type");
    }
}

void index_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST(data[0] == true);
    TRIAL_PROTOCOL_TEST(data[1] == 2);
    TRIAL_PROTOCOL_TEST(data[2] == 3.0);
    TRIAL_PROTOCOL_TEST(data[3] == "alpha");
}

void index_array_const()
{
    const variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST(data[0] == true);
    TRIAL_PROTOCOL_TEST(data[1] == 2);
    TRIAL_PROTOCOL_TEST(data[2] == 3.0);
    TRIAL_PROTOCOL_TEST(data[3] == "alpha");
}

void index_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                    error,
                                    "incompatible type");
}

void key_null()
{
    variable data;
    // Special case: transforms null into map
    const auto& key = data["alpha"];
    TRIAL_PROTOCOL_TEST_EQUAL(key.is<nullable>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
}

void key_const_null()
{
    const variable data;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                    error,
                                    "incompatible type");
}

void key_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                    error,
                                    "incompatible type");
}

void key_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                    error,
                                    "incompatible type");
}

void key_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                    error,
                                    "incompatible type");
}

void key_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                        error,
                                        "incompatible type");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[L"alpha"],
                                        error,
                                        "incompatible type");
    }
}

void key_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                    error,
                                    "incompatible type");
}

void key_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST(data["alpha"] == true);
    TRIAL_PROTOCOL_TEST(data["bravo"] == 2);
    TRIAL_PROTOCOL_TEST(data["charlie"] == 3.0);
    TRIAL_PROTOCOL_TEST(data["delta"] == "beryllium");
    TRIAL_PROTOCOL_TEST(data["unknown"] == null);
}

void key_const_map()
{
    const variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST(data["alpha"] == true);
    TRIAL_PROTOCOL_TEST(data["bravo"] == 2);
    TRIAL_PROTOCOL_TEST(data["charlie"] == 3.0);
    TRIAL_PROTOCOL_TEST(data["delta"] == "beryllium");
    TRIAL_PROTOCOL_TEST_THROWS(data["unknown"],
                               std::out_of_range);
}

void create_map_key()
{
    variable data;
    data["alpha"] = true;
    TRIAL_PROTOCOL_TEST(data["alpha"] == true);
    data["bravo"] = 2;
    TRIAL_PROTOCOL_TEST(data["bravo"] == 2);
    data["charlie"] = 3.0;
    TRIAL_PROTOCOL_TEST(data["charlie"] == 3.0);
    data["delta"] = "beryllium";
    TRIAL_PROTOCOL_TEST(data["delta"] == "beryllium");
}

void run()
{
    index_null();
    index_boolean();
    index_integer();
    index_number();
    index_string();
    index_array();
    index_array_const();
    index_map();

    key_const_null();
    key_null();
    key_boolean();
    key_integer();
    key_number();
    key_string();
    key_array();
    key_map();
    key_const_map();

    create_map_key();
}

} // namespace subscript_suite

//-----------------------------------------------------------------------------
// operator R()
//-----------------------------------------------------------------------------

namespace conversion_operator_suite
{

void get_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(nullable(data) == null);
    TRIAL_PROTOCOL_TEST(bool(data) == false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator int(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator float(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::string_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::wstring_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::array_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::map_type(),
                                    error,
                                    "incompatible type");
}

void get_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator nullable(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST(bool(data) == true);
    TRIAL_PROTOCOL_TEST(int(data) == 1);
    TRIAL_PROTOCOL_TEST(float(data) == 1.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::string_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::wstring_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::array_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::map_type(),
                                    error,
                                    "incompatible type");
}

void get_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator nullable(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST(bool(data) == true);
    TRIAL_PROTOCOL_TEST(int(data) == 2);
    TRIAL_PROTOCOL_TEST(float(data) == 2.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::string_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::wstring_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::array_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::map_type(),
                                    error,
                                    "incompatible type");
}

void get_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator nullable(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST(bool(data) == true);
    TRIAL_PROTOCOL_TEST(int(data) == 3);
    TRIAL_PROTOCOL_TEST(float(data) == 3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::string_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::wstring_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::array_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::map_type(),
                                    error,
                                    "incompatible type");
}

void get_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator nullable(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator bool(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator int(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator float(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST(variable::string_type(data) == "alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::wstring_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::array_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::map_type(),
                                    error,
                                    "incompatible type");
}

void get_wstring()
{
    variable data(L"alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator nullable(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator bool(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator int(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator float(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::string_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST(variable::wstring_type(data) == L"alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::array_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::map_type(),
                                    error,
                                    "incompatible type");
}

void get_array()
{
    variable data = array::make();
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator nullable(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator bool(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator int(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator float(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::string_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST(variable::array_type(data).empty());
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::map_type(),
                                    error,
                                    "incompatible type");
}

void get_map()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator nullable(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator bool(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator int(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator float(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::string_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator variable::array_type(),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST(variable::map_type(data).empty());
}

void run()
{
    get_null();
    get_boolean();
    get_integer();
    get_number();
    get_string();
    get_wstring();
    get_array();
    get_map();
}

} // namespace conversion_operator_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    append_suite::run();
    addition_suite::run();

    subscript_suite::run();
    conversion_operator_suite::run();

    return boost::report_errors();
}
