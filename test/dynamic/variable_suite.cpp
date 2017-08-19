///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <functional>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

namespace ctor_suite
{

void construct_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void construct_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<boolean>(), true);
}

void construct_signed_short_int()
{
    signed short int value = 0;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_short_int()
{
    unsigned short int value = 0;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_signed_int()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_int()
{
    variable data(0U);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_signed_long_int()
{
    variable data(0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_long_int()
{
    variable data(0UL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_signed_long_long_int()
{
    variable data(0LL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_long_long_int()
{
    variable data(0ULL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_float()
{
    variable data(1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);
}

void construct_double()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);
}

void construct_long_double()
{
    variable data(1.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);
}

void construct_string_with_string()
{
    variable data(std::string("alpha"));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void construct_string_with_literal()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void construct_array_with_vector()
{
    std::vector<int> input = { 1, 2 };
    variable data = array::make(input.begin(), input.end());
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array_with_iterator()
{
    std::vector<variable> input = { 1, 2 };
    variable data = array::make(input.begin(), input.end());
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array()
{
    variable data = array::make({false, 1, 2.0, "alpha"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array_empty()
{
    variable data = array::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array_with_size()
{
    variable data = array::repeat(4, true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_map_by_null()
{
    variable data = map::make(
        {
            {null, 1}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_by_boolean()
{
    variable data = map::make(
        {
            {false, 1},
            {true, 2}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_by_integer()
{
    variable data = map::make(
        {
            {1, 1},
            {2, 2}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_by_string()
{
    variable data = map::make(
        {
            {"alpha", 1}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_by_string_empty()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_by_implicit_pair()
{
    variable data = map::make({"alpha", "hydrogen"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_by_explicit_pair()
{
    variable data = map::make(std::pair<std::string, std::string>("alpha", "hydrogen"));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_by_make_pair()
{
    variable data = map::make(std::make_pair("alpha", "hydrogen"));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_make_by_string()
{
    variable data = map::make(std::string("alpha"), "hydrogen");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_make_by_string_literal()
{
    variable data = map::make("alpha", "hydrogen");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_make_by_initializer()
{
    variable data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_mixed_by_string()
{
    variable data = map::make(
        {
            {"alpha", array::make({1, 2})}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void run()
{
    construct_null();

    construct_boolean();

    construct_signed_short_int();
    construct_unsigned_short_int();
    construct_signed_int();
    construct_unsigned_int();
    construct_signed_long_int();
    construct_unsigned_long_int();
    construct_signed_long_long_int();
    construct_unsigned_long_long_int();

    construct_float();
    construct_double();
    construct_long_double();

    construct_string_with_string();
    construct_string_with_literal();

    construct_array_with_vector();
    construct_array_with_iterator();
    construct_array();
    construct_array_empty();
    construct_array_with_size();

    construct_map_by_null();
    construct_map_by_boolean();
    construct_map_by_integer();
    construct_map_by_string();
    construct_map_by_string_empty();
    construct_map_by_implicit_pair();
    construct_map_by_explicit_pair();
    construct_map_by_make_pair();
    construct_map_make_by_string();
    construct_map_make_by_string_literal();
    construct_map_make_by_initializer();

    construct_mixed_by_string();
}

} // namespace ctor_suite

//-----------------------------------------------------------------------------
// variable::is<T>
//-----------------------------------------------------------------------------

namespace is_suite
{

void is_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void is_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<boolean>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void is_integer_with_signed_short_int()
{
    signed short int value = 2;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed short int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed short int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);
}

void is_integer_with_unsigned_short_int()
{
    unsigned short int value = 2;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned short int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed short int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);
}

void is_integer_with_signed_int()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);
}

void is_integer_with_unsigned_int()
{
    variable data(2U);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);
}

void is_integer_with_signed_long_int()
{
    variable data(2L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);
}

void is_integer_with_unsigned_long_int()
{
    variable data(2UL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);
}

void is_integer_with_signed_long_long_int()
{
    variable data(2LL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long long int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);
}

void is_integer_with_unsigned_long_long_int()
{
    variable data(2ULL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long long int&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
}

void is_number_with_float()
{
    variable data(1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile float&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const float&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile float&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), false);
}

void is_number_with_double()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile double&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), false);
}

void is_number_with_long_double()
{
    variable data(1.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile long double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const long double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const long double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile long double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile long double&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), false);
}

void run()
{
    is_null();

    is_boolean();

    is_integer_with_signed_short_int();
    is_integer_with_unsigned_short_int();
    is_integer_with_signed_int();
    is_integer_with_unsigned_int();
    is_integer_with_signed_long_int();
    is_integer_with_unsigned_long_int();
    is_integer_with_signed_long_long_int();
    is_integer_with_unsigned_long_long_int();

    is_number_with_float();
    is_number_with_double();
    is_number_with_long_double();
}

} // namespace is_suite

//-----------------------------------------------------------------------------
// Tokens
//-----------------------------------------------------------------------------

namespace token_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::null);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::boolean);
}

void test_integer()
{
    {
        const signed short int value = 0;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::signed_short_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
    {
        const unsigned short int value = 0U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::unsigned_short_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
    {
        const signed int value = 0;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::signed_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
    {
        const unsigned int value = 0U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::unsigned_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
    {
        const signed long int value = 0L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::signed_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
    {
        const unsigned long int value = 0UL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::unsigned_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
    {
        const signed long long int value = 0LL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::signed_long_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
    {
        const unsigned long long int value = 0ULL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::unsigned_long_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::integer);
    }
}

void test_number()
{
    {
        const float value = 0.0f;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::float_number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::number);
    }
    {
        const double value = 0.0;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::double_number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::number);
    }
    {
        const long double value = 0.0L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::long_double_number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::number);
    }
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::string);
}

void test_array()
{
    variable data = array::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::array);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::array);
}

void test_map()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), token::code::map);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), token::symbol::map);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_map();
}

} // namespace token_suite

//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

namespace copy_suite
{

void copy_null()
{
    variable data;
    variable copy(data);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<nullable>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<nullable>(), null);
}

void copy_boolean()
{
    variable data(true);
    variable copy(data);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<bool>(), true);
}

void copy_integer()
{
    {
        signed short int value = 2;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned short int>(), value);
    }
    {
        signed int value = 2;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long long int>(), value);
    }
}

void copy_number()
{
    {
        float value = 3.0f;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<float>(), value);
    }
    {
        double value = 3.0;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<double>(), value);
    }
    {
        long double value = 3.0L;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<long double>(), value);
    }
}

void copy_string()
{
    variable data("alpha");
    variable copy(data);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<string>(), true);
}

void copy_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(data);

    variable expect = array::make({ true, 2, 3.0, "alpha" });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void copy_array_nested()
{
    variable data = array::make({ true, array::make({ 2, 3.0 }), "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(data);

    variable expect = array::make({ true, array::make({ 2, 3.0 }), "alpha" });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void copy_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(data);

    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void copy_map_nested()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(data);

    variable expect = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    copy_null();
    copy_boolean();
    copy_integer();
    copy_number();
    copy_string();
    copy_array();
    copy_array_nested();
    copy_map();
    copy_map_nested();
}

} // namespace copy_suite

//-----------------------------------------------------------------------------
// Move
//-----------------------------------------------------------------------------

namespace move_suite
{

void move_null()
{
    variable data;
    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<nullable>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<nullable>(), null);
}

void move_boolean()
{
    variable data(true);
    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<bool>(), true);
}

void move_integer()
{
    {
        signed short int value = 2;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned short int>(), value);
    }
    {
        signed int value = 2;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long long int>(), value);
    }
}

void move_number()
{
    {
        float value = 3.0f;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<float>(), value);
    }
    {
        double value = 3.0;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<double>(), value);
    }
    {
        long double value = 3.0L;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<long double>(), value);
    }
}

void move_string()
{
    variable data("alpha");
    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<string>(), "alpha");
}

void move_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);

    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void move_array_nested()
{
    variable data = array::make({ true, array::make({ 2, 3.0 }), "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);

    variable expect = array::make({ true, array::make({ 2, 3.0 }), "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void move_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);

    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void move_map_nested()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);

    variable expect = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    move_null();
    move_boolean();
    move_integer();
    move_number();
    move_string();
    move_array();
    move_array_nested();
    move_map();
    move_map_nested();
}

} // namespace move_suite

//-----------------------------------------------------------------------------
// Assignment
//-----------------------------------------------------------------------------

namespace assign_suite
{

void assign_null_with_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_null_with_boolean()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_null_with_integer()
{
    // signed short int
    {
        signed short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_null_with_number()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_null_with_string()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_null_with_string_literal()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = "alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_null_with_array()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_null_with_map()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_boolean_with_null()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_boolean_with_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_boolean_with_integer()
{
    // signed short int
    {
        signed short int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_boolean_with_number()
{
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_boolean_with_string()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_boolean_with_array()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_boolean_with_map()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_signed_int_with_null()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_signed_int_with_boolean()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_signed_int_with_integer()
{
    signed int input = 2;

    // signed short int
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_signed_int_with_number()
{
    signed int input = 2;
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_signed_int_with_string()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_signed_int_with_array()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_signed_int_with_map()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_unsigned_int_with_null()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_unsigned_int_with_boolean()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_unsigned_int_with_integer()
{
    unsigned int input = 2;

    // signed short int
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_unsigned_int_with_number()
{
    unsigned int input = 2;
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_unsigned_int_with_string()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_unsigned_int_with_array()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_unsigned_int_with_map()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_float_with_null()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_float_with_boolean()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_float_with_integer()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 1;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 1U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_float_with_number()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 1.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 1.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_float_with_string()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_float_with_array()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_float_with_map()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_double_with_null()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_double_with_boolean()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_double_with_integer()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 1;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 1U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_double_with_number()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 1.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 1.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_double_with_string()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_double_with_array()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_double_with_map()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_long_double_with_null()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_long_double_with_boolean()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_long_double_with_integer()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 1;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 1U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_long_double_with_number()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 1.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 1.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
}

void assign_long_double_with_string()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_long_double_with_array()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_long_double_with_map()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_string_with_null()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_string_with_boolean()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_string_with_integer()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
}

void assign_string_with_number()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = 1.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(1.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(1.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = 1.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(1.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(1.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = 1.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(1.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(1.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_string_with_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_string_with_array()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_string_with_map()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_array_with_null()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_array_with_boolean()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_array_with_integer()
{
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 1;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 1U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_array_with_number()
{
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 1.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(1.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(1.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 1.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(1.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(1.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 1.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(1.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(1.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_array_with_string()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_array_with_array()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = array::make({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_array_with_map()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_map_with_null()
{
    variable data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_map_with_boolean()
{
    variable data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_map_with_integer()
{
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 1;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 1U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_map_with_number()
{
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 1.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(1.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(1.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 1.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(1.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(1.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 1.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(1.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(1.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_map_with_string()
{
    variable data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = std::string("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
}

void assign_map_with_array()
{
    variable data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_map_with_map()
{
    variable data = map::make({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = map::make({{ "bravo", "helium" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void run()
{
    assign_null_with_null();
    assign_null_with_boolean();
    assign_null_with_integer();
    assign_null_with_number();
    assign_null_with_string();
    assign_null_with_string_literal();
    assign_null_with_array();
    assign_null_with_map();

    assign_boolean_with_null();
    assign_boolean_with_boolean();
    assign_boolean_with_integer();
    assign_boolean_with_number();
    assign_boolean_with_string();
    assign_boolean_with_array();
    assign_boolean_with_map();

    assign_signed_int_with_null();
    assign_signed_int_with_boolean();
    assign_signed_int_with_integer();
    assign_signed_int_with_number();
    assign_signed_int_with_string();
    assign_signed_int_with_array();
    assign_signed_int_with_map();

    assign_unsigned_int_with_null();
    assign_unsigned_int_with_boolean();
    assign_unsigned_int_with_integer();
    assign_unsigned_int_with_number();
    assign_unsigned_int_with_string();
    assign_unsigned_int_with_array();
    assign_unsigned_int_with_map();

    assign_float_with_null();
    assign_float_with_boolean();
    assign_float_with_integer();
    assign_float_with_number();
    assign_float_with_string();
    assign_float_with_array();
    assign_float_with_map();

    assign_double_with_null();
    assign_double_with_boolean();
    assign_double_with_integer();
    assign_double_with_number();
    assign_double_with_string();
    assign_double_with_array();
    assign_double_with_map();

    assign_long_double_with_null();
    assign_long_double_with_boolean();
    assign_long_double_with_integer();
    assign_long_double_with_number();
    assign_long_double_with_string();
    assign_long_double_with_array();
    assign_long_double_with_map();

    assign_string_with_null();
    assign_string_with_boolean();
    assign_string_with_integer();
    assign_string_with_number();
    assign_string_with_string();
    assign_string_with_array();
    assign_string_with_map();

    assign_array_with_null();
    assign_array_with_boolean();
    assign_array_with_integer();
    assign_array_with_number();
    assign_array_with_string();
    assign_array_with_array();
    assign_array_with_map();

    assign_map_with_null();
    assign_map_with_boolean();
    assign_map_with_integer();
    assign_map_with_number();
    assign_map_with_string();
    assign_map_with_array();
    assign_map_with_map();
}

} // namespace assign_suite

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
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data += variable("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
}

void append_null_with_array()
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

void append_null_with_map()
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
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
}

void append_boolean_with_array()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_boolean_with_map()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
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
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
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
    unsigned int input = 2U;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
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
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
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
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
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
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
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
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
}

void append_string_with_boolean()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(true)),
                                    error,
                                    "incompatible type");
}

void append_string_with_integer()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2U)),
                                        error,
                                        "incompatible type");
    }
}

void append_string_with_number()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0f)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0L)),
                                        error,
                                        "incompatible type");
    }
}

void append_string_with_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data += variable("-bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha-bravo");
}

void append_string_with_array()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_string_with_map()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_array_with_null()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
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
    variable data = array::make({ true, 2, 3.0, "alpha" });
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
        variable data = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 4;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 4 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha" });
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
        variable data = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 6.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0f });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
        data += 6.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
        variable expect = array::make({ true, 2, 3.0, "alpha", 6.0 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha" });
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
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += "bravo";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = array::make({ true, 2, 3.0, "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_array()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data += { 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_array_by_name()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data += array::make({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_map()
{
    variable data = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(map::make({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_map_with_null()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    data += null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
}

void append_map_with_boolean()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(true)),
                                    error,
                                    "incompatible type");
}

void append_map_with_integer()
{
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2U)),
                                        error,
                                        "incompatible type");
    }
}

void append_map_with_number()
{
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0f)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0)),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            });
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0L)),
                                        error,
                                        "incompatible type");
    }
}

void append_map_with_string()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
}

void append_map_with_array()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(array::make({ true, 2 })),
                                    error,
                                    "incompatible type");
}

void append_map_with_map()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    data += map::make({{"charlie", "lithium"}});
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
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
    append_array_with_array_by_name();
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
    auto data = null + variable("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
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
    variable data(false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                    error,
                                    "incompatible type");
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
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                    error,
                                    "incompatible type");
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
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                    error,
                                    "incompatible type");
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
    auto data = variable("alpha") + null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");
}

void add_string_with_boolean()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(true),
                                    error,
                                    "incompatible type");
}

void add_string_with_integer()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2),
                                        error,
                                        "incompatible type");
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(2U),
                                        error,
                                        "incompatible type");
    }
}

void add_string_with_number()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0f),
                                        error,
                                        "incompatible type");
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0),
                                        error,
                                        "incompatible type");
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable(3.0L),
                                        error,
                                        "incompatible type");
    }
}

void add_string_with_string()
{
    auto data = variable("alpha") + variable("-bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha-bravo");
}

void add_string_with_array()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + array::make({ true, "alpha" }),
                                    error,
                                    "incompatible type");
}

void add_string_with_map()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + map::make({{ "alpha", "hydrogen" }}),
                                    error,
                                    "incompatible type");
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
    variable data = array::make({ true, 2, 3.0, "alpha" }) + "bravo";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = array::make({ true, 2, 3.0, "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
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
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data + variable("alpha"),
                                    error,
                                    "incompatible type");
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
// Accessor
//-----------------------------------------------------------------------------

namespace value_suite
{

void test_null_as_null()
{
    variable data;
    std::error_code error;
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST(!error);
}

void fail_null_as_boolean()
{
    variable data;
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), bool{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_integer()
{
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(error), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(error), 0U);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_null_as_number()
{
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_null_as_string()
{
    variable data;
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), std::string{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_array()
{
    variable data;
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_map()
{
    variable data;
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_null()
{
    variable data(false);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), false);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_boolean_as_boolean()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
}

void test_boolean_as_integer()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), int(data));
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), int(data));
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1);
    }
}

void test_boolean_as_number()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 1.0L);
    }
}

void fail_boolean_as_string()
{
    variable data(false);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), false);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), std::string{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_array()
{
    variable data(false);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_map()
{
    variable data(false);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_null()
{
    variable data(0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), 0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_integer_as_boolean()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
    {
        variable data(1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data = std::numeric_limits<signed int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data(0U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
    {
        variable data(1U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data = std::numeric_limits<unsigned int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
}

void test_integer_as_integer()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data = std::numeric_limits<signed int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(),
                                  std::numeric_limits<signed int>::max());
    }
    {
        variable data(0U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        variable data(1U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data = std::numeric_limits<unsigned int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(),
                                  std::numeric_limits<unsigned int>::max());
    }
}

void test_integer_as_number()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    }
    {
        variable data(1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 1.0L);
    }
    {
        variable data = std::numeric_limits<signed int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(),
                                  std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(),
                                  std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(),
                                  std::numeric_limits<signed int>::max());
    }
}

void fail_integer_as_string()
{
    variable data(0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), 0);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), std::string{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_array()
{
    variable data(0);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_map()
{
    variable data(0);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_float_as_null()
{
    variable data(0.0f);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_float_as_boolean()
{
    variable data(0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));

    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);

    data = std::numeric_limits<float>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void test_float_as_integer()
{
    {
        variable data(0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data(2.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
    }
    {
        variable data(0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data(2.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
    }
}

void test_float_as_number()
{
    variable data(0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), float(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), double(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), (long double)(data));

    data = std::numeric_limits<float>::min();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::min());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<float>::min());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<float>::min());

    data = std::numeric_limits<float>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::max());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<float>::max());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<float>::max());
}

void fail_float_as_string()
{
    variable data(0.0f);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), std::string{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_float_as_array()
{
    variable data(0.0f);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_float_as_map()
{
    variable data(0.0f);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_double_as_null()
{
    variable data(0.0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_double_as_boolean()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));

    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);

    data = std::numeric_limits<double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void test_double_as_integer()
{
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data(2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
    }
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0u);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data(2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
    }
}

void test_double_as_number()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), float(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), double(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), (long double)(data));

    data = std::numeric_limits<double>::min();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f); // Underflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<double>::min());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<double>::min());

    data = std::numeric_limits<double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::infinity()); // Overflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<double>::max());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<double>::max());
}

void fail_double_as_string()
{
    variable data(0.0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), std::string{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_double_as_array()
{
    variable data(0.0);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_double_as_map()
{
    variable data(0.0);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_long_double_as_null()
{
    variable data(0.0L);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_long_double_as_boolean()
{
    variable data(0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));

    data = 1.0L;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);

    data = std::numeric_limits<long double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void test_long_double_as_integer()
{
    {
        variable data(0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data(2.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
    }
    {
        variable data(0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data(2.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
    }
}

void test_long_double_as_number()
{
    variable data(0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), float(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), double(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), (long double)(data));

    data = std::numeric_limits<long double>::min();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f); // Underflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0); // Underflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<long double>::min());

    data = std::numeric_limits<long double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::infinity()); // Overflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<double>::infinity()); // Overflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<long double>::max());
}

void fail_long_double_as_string()
{
    variable data(0.0L);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), std::string{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_long_double_as_array()
{
    variable data(0.0L);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_long_double_as_map()
{
    variable data(0.0L);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_null()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_boolean()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), bool{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_integer()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), int{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_number()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    error = {};
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    error = {};
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_string_as_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");

    data = "bravo";
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "bravo");
}

void fail_string_as_array()
{
    variable data("alpha");
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_map()
{
    variable data("alpha");
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_array_as_array()
{
    variable data = array::make({ 1, 2, 3 });
    auto result = data.value<array>();
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 data.begin(), data.end(),
                                 std::equal_to<variable>());
}

void test_array_with_size()
{
    variable data = array::repeat(4, true);
    variable result = array::make({ true, true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 data.begin(), data.end(),
                                 std::equal_to<variable>());
}

void run()
{
    test_null_as_null();
    fail_null_as_boolean();
    fail_null_as_integer();
    fail_null_as_number();
    fail_null_as_string();
    fail_null_as_array();
    fail_null_as_map();

    fail_boolean_as_null();
    test_boolean_as_boolean();
    test_boolean_as_integer();
    test_boolean_as_number();
    fail_boolean_as_string();
    fail_boolean_as_array();
    fail_boolean_as_map();

    fail_integer_as_null();
    test_integer_as_boolean();
    test_integer_as_integer();
    test_integer_as_number();
    fail_integer_as_string();
    fail_integer_as_array();
    fail_integer_as_map();

    fail_float_as_null();
    test_float_as_boolean();
    test_float_as_integer();
    test_float_as_number();
    fail_float_as_string();
    fail_float_as_array();
    fail_float_as_map();

    fail_double_as_null();
    test_double_as_boolean();
    test_double_as_integer();
    test_double_as_number();
    fail_double_as_string();
    fail_double_as_array();
    fail_double_as_map();

    fail_long_double_as_null();
    test_long_double_as_boolean();
    test_long_double_as_integer();
    test_long_double_as_number();
    fail_long_double_as_string();
    fail_long_double_as_array();
    fail_long_double_as_map();

    fail_string_as_null();
    fail_string_as_boolean();
    fail_string_as_integer();
    fail_string_as_number();
    test_string_as_string();
    fail_string_as_array();
    fail_string_as_map();

    test_array_as_array();
    test_array_with_size();
}

} // namespace value_suite

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
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data[0],
                                    error,
                                    "incompatible type");
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
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                    error,
                                    "incompatible type");
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
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(!data.empty());

    data = "";
    TRIAL_PROTOCOL_TEST(data.empty());
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
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);

    data = "";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
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
    test_array();
    test_array_with_size();
    test_map();
}

} // namespace size_suite

//-----------------------------------------------------------------------------
// Count
//-----------------------------------------------------------------------------

namespace count_suite
{

void count_null()
{
    // Null is always empty
    variable data;

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_boolean()
{
    variable data(true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_integer()
{
    variable data(2);

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_number()
{
    variable data(3.0);

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_string()
{
    variable data("alpha");

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("bravo"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("bravo")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_array()
{
    variable data = array::make(
        { null, true, 2, 3.0, "hydrogen",
          null, true, 2, 3.0,
          null, true, 2,
          null, true,
          null });

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("hydrogen")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make({ null })), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(data), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", null},
            {"golf", true},
            {"hotel", 2},
            {"india", 3.0},
            {"juliet", null},
            {"kilo", true},
            {"lima", 2},
            {"mike", null},
            {"november", true},
            {"oscar", null}
        });

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("hydrogen")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(data), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void run()
{
    count_null();
    count_boolean();
    count_integer();
    count_number();
    count_string();
    count_array();
    count_map();
}

} // namespace count_suite

//-----------------------------------------------------------------------------
// Clear
//-----------------------------------------------------------------------------

namespace clear_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool{});
}

void test_integer()
{
    {
        signed short int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), 0);
    }
    {
        unsigned short int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), 0U);
    }
    {
        signed int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        unsigned int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        signed long int value = 1L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), 0L);
    }
    {
        unsigned long int value = 1UL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), 0UL);
    }
    {
        signed long long int value = 1LL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), 0LL);
    }
    {
        unsigned long long int value = 1ULL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), 0ULL);
    }
}

void test_number()
{
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    }
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void test_array()
{
    variable data = array::make({ 1, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void test_map()
{
    variable data = map::make({ {"alpha", 1} });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_map();
}

} // namespace clear_suite

//-----------------------------------------------------------------------------
// Erase
//-----------------------------------------------------------------------------

namespace erase_suite
{

void erase_null()
{
    variable data;
    auto where = data.erase(data.begin());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == null);
}

void erase_boolean()
{
    variable data(true);
    auto where = data.erase(data.begin());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == true);
}

void erase_integer()
{
    variable data(2);
    auto where = data.erase(data.begin());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == 2);
}

void erase_number()
{
    variable data(3.0);
    auto where = data.erase(data.begin());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == 3.0);
}

void erase_string()
{
    variable data("alpha");
    auto where = data.erase(data.begin());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == "alpha");
}

void erase_array_first()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin());
    variable expect = array::make({ 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_array_second()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(std::next(data.begin()));
    variable expect = array::make({ true, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_array_third()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(std::next(data.begin(), 2));
    variable expect = array::make({ true, 2, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_array_fourth()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(std::next(data.begin(), 3));
    variable expect = array::make({ true, 2, 3.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_array_all()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin());
    variable expect = array::make({ 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make({ "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_map_all()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    auto where = data.erase(data.begin());
    variable expect = map::make(
        {
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = map::make(
        {
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = map::make(
        {
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = map::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_null()
{
    variable data;
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == null);
}

void erase_range_boolean()
{
    variable data(true);
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == true);
}

void erase_range_integer()
{
    variable data(2);
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == 2);
}

void erase_range_number()
{
    variable data(3.0);
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == 3.0);
}

void erase_range_string()
{
    variable data("alpha");
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == "alpha");
}

void erase_range_array_first_first()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), data.begin());
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_second()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), ++data.begin());
    variable expect = array::make({ 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_third()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), ++(++data.begin()));
    variable expect = array::make({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_fourth()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), ++(++(++data.begin())));
    variable expect = array::make({ "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_last()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), data.end());
    variable expect = array::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_second_fourth()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(++data.begin(), ++(++(++data.begin())));
    variable expect = array::make({ true, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_first()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), data.begin());
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_second()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), ++data.begin());
    variable expect = map::make(
        {
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_third()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), ++(++data.begin()));
    variable expect = map::make(
        {
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_fourth()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), ++(++(++data.begin())));
    variable expect = map::make(
        {
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_last()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), data.end());
    variable expect = map::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_second_fourth()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(++data.begin(), ++(++(++data.begin())));
    variable expect = map::make(
        {
            { "alpha", true },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    erase_null();
    erase_boolean();
    erase_integer();
    erase_number();
    erase_string();
    erase_array_first();
    erase_array_second();
    erase_array_third();
    erase_array_fourth();
    erase_array_all();
    erase_map_all();

    erase_range_null();
    erase_range_boolean();
    erase_range_integer();
    erase_range_number();
    erase_range_string();
    erase_range_array_first_first();
    erase_range_array_first_second();
    erase_range_array_first_third();
    erase_range_array_first_fourth();
    erase_range_array_first_last();
    erase_range_array_second_fourth();
    erase_range_map_first_first();
    erase_range_map_first_second();
    erase_range_map_first_third();
    erase_range_map_first_fourth();
    erase_range_map_first_last();
    erase_range_map_second_fourth();
}

} // namespace erase_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    ctor_suite::run();
    is_suite::run();
    token_suite::run();

    copy_suite::run();
    move_suite::run();
    assign_suite::run();
    append_suite::run();
    addition_suite::run();

    value_suite::run();
    subscript_suite::run();

    empty_suite::run();
    size_suite::run();
    count_suite::run();
    // find_suite is in variable_iterator_suite.cpp

    clear_suite::run();
    erase_suite::run();

    return boost::report_errors();
}
