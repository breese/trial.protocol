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
#include <trial/protocol/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

namespace ctor_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_integer_with_int()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long long>(), true);
}

void test_integer_with_unsigned_int()
{
    variable data(1U);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long long>(), true);
}

void test_integer_with_long()
{
    variable data(1L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long long>(), true);
}

void test_integer_with_long_long()
{
    variable data(1LL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long long>(), true);
}

void test_number_with_float()
{
    variable data(1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
}

void test_number_with_double()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
}

void test_string_with_string()
{
    variable data(std::string("alpha"));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_string_with_literal()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_array_with_vector()
{
    std::vector<int> input = { 1, 2 };
    variable data = variable::array(input.begin(), input.end());
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_array_with_iterator()
{
    variable::array_type array = { 1, 2 };
    variable data = variable::array(array.begin(), array.end());
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_array_by_name()
{
    variable data = variable::array({false, 1, 2.0, "alpha"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_array_by_name_empty()
{
    variable data = variable::array();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_array_with_size()
{
    variable data = variable::array(4, true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), false);
}

void test_map_by_name()
{
    variable data = variable::map(
        {
            {"alpha", 1}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void test_map_by_name_empty()
{
    variable data = variable::map();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void test_mixed_by_name()
{
    variable data = variable::map(
        {
            {"alpha", variable::array({1, 2})}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void run()
{
    test_null();

    test_boolean();

    test_integer_with_int();
    test_integer_with_unsigned_int();
    test_integer_with_long();
    test_integer_with_long_long();

    test_number_with_float();
    test_number_with_double();

    test_string_with_string();
    test_string_with_literal();

    test_array_with_vector();
    test_array_with_iterator();
    test_array_by_name();
    test_array_by_name_empty();
    test_array_with_size();

    test_map_by_name();
    test_map_by_name_empty();

    test_mixed_by_name();
}

} // namespace ctor_suite

//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

namespace copy_suite
{

void test_boolean()
{
    variable boolean(false);
    variable data(boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void test_integer()
{
    variable integer(0);
    variable data(integer);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void test_number()
{
    variable number(0.0);
    variable data(number);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void test_string()
{
    variable string("alpha");
    variable data(string);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void run()
{
    test_boolean();
    test_integer();
    test_number();
    test_string();
}

} // namespace copy_suite

//-----------------------------------------------------------------------------
// Move
//-----------------------------------------------------------------------------

namespace move_suite
{

void test_boolean()
{
    variable boolean(true);
    variable data(std::move(boolean));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void test_integer()
{
    variable integer(1);
    variable data(std::move(integer));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 1);
}

void test_number()
{
    variable number(1.0);
    variable data(std::move(number));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 1.0);
}

void test_string()
{
    variable string("alpha");
    variable data(std::move(string));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha");
}

void run()
{
    test_boolean();
    test_integer();
    test_number();
    test_string();
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
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void assign_null_with_boolean()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void assign_null_with_integer()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void assign_null_with_number()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void assign_null_with_string()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_null_with_string_literal()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = "alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_null_with_array()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
}

void assign_null_with_map()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void assign_boolean_with_null()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void assign_boolean_with_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void assign_boolean_with_integer()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void assign_boolean_with_number()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void assign_boolean_with_string()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_boolean_with_array()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
}

void assign_boolean_with_map()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void assign_integer_with_null()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void assign_integer_with_boolean()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void assign_integer_with_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void assign_integer_with_number()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void assign_integer_with_string()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_integer_with_array()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
}

void assign_integer_with_map()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void assign_number_with_null()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void assign_number_with_boolean()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void assign_number_with_integer()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void assign_number_with_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void assign_number_with_string()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_number_with_array()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
}

void assign_number_with_map()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void assign_string_with_null()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void assign_string_with_boolean()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void assign_string_with_integer()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void assign_string_with_number()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void assign_string_with_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_string_with_array()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
}

void assign_string_with_map()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void assign_array_with_null()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void assign_array_with_boolean()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void assign_array_with_integer()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void assign_array_with_number()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void assign_array_with_string()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_array_with_array()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data = variable::array({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
}

void assign_array_with_map()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void assign_map_with_null()
{
    variable data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void assign_map_with_boolean()
{
    variable data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void assign_map_with_integer()
{
    variable data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void assign_map_with_number()
{
    variable data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void assign_map_with_string()
{
    variable data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void assign_map_with_array()
{
    variable data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
}

void assign_map_with_map()
{
    variable data = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    data = variable::map({{ "bravo", "helium" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
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

    assign_integer_with_null();
    assign_integer_with_boolean();
    assign_integer_with_integer();
    assign_integer_with_number();
    assign_integer_with_string();
    assign_integer_with_array();
    assign_integer_with_map();

    assign_number_with_null();
    assign_number_with_boolean();
    assign_number_with_integer();
    assign_number_with_number();
    assign_number_with_string();
    assign_number_with_array();
    assign_number_with_map();

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
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data += variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void append_null_with_boolean()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void append_null_with_integer()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data += variable(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 2);
}

void append_null_with_number()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data += variable(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 3.0);
}

void append_null_with_string()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data += variable("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha");
}

void append_null_with_array()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data += variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_null_with_map()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data += variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    variable expect = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_boolean_with_null()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data += variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), false);
}

void append_boolean_with_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void append_boolean_with_integer()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), false);
    data += variable(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void append_boolean_with_number()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), false);
    data += variable(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void append_boolean_with_string()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
}

void append_boolean_with_array()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_boolean_with_map()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_integer_with_null()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data += variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 2);
}

void append_integer_with_boolean()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 3);
}

void append_integer_with_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data += variable(3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 5);
}

void append_integer_with_number()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data += variable(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 5);
}

void append_integer_with_string()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
}

void append_integer_with_array()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_integer_with_map()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_number_with_null()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data += variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 3.0);
}

void append_number_with_boolean()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data += variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 4.0);
}

void append_number_with_integer()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data += variable(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 5.0);
}

void append_number_with_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data += variable(2.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 5.0);
}

void append_number_with_string()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable("alpha")),
                                    error,
                                    "incompatible type");
}

void append_number_with_array()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_number_with_map()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_string_with_null()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data += variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha");
}

void append_string_with_boolean()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(true)),
                                    error,
                                    "incompatible type");
}

void append_string_with_integer()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2)),
                                    error,
                                    "incompatible type");
}

void append_string_with_number()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0)),
                                    error,
                                    "incompatible type");
}

void append_string_with_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    data += variable("-bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha-bravo");
}

void append_string_with_array()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void append_string_with_map()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_array_with_null()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_boolean()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_integer()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += 4;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_number()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += 6.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", 6.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_string()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    data += "bravo";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_array()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data += { 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_array_by_name()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    data += variable::array({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void append_array_with_map()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void append_map_with_null()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    data += variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
}

void append_map_with_boolean()
{
    variable data = variable::map(
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
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(2)),
                                    error,
                                    "incompatible type");
}

void append_map_with_number()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable(3.0)),
                                    error,
                                    "incompatible type");
}

void append_map_with_string()
{
    variable data = variable::map(
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
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.operator+=(variable::array({ true, 2 })),
                                    error,
                                    "incompatible type");
}

void append_map_with_map()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    data += variable::map({{"charlie", "lithium"}});
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

    append_integer_with_null();
    append_integer_with_boolean();
    append_integer_with_integer();
    append_integer_with_number();
    append_integer_with_string();
    append_integer_with_array();
    append_integer_with_map();

    append_number_with_null();
    append_number_with_boolean();
    append_number_with_integer();
    append_number_with_number();
    append_number_with_string();
    append_number_with_array();
    append_number_with_map();

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
    auto data = variable::null + variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void add_null_with_boolean()
{
    auto data = variable::null + variable(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void add_null_with_integer()
{
    auto data = variable::null + variable(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 2);
}

void add_null_with_number()
{
    auto data = variable::null + variable(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 3.0);
}

void add_null_with_string()
{
    auto data = variable::null + variable("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha");
}

void add_null_with_array()
{
    auto data = variable::null + variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_null_with_map()
{
    auto data = variable::null + variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    variable expect = variable::map({{ "alpha", "hydrogen" }});
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_boolean_with_null()
{
    auto data = variable(true) + variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void add_boolean_with_boolean()
{
    auto data = variable(true) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void add_boolean_with_integer()
{
    auto data = variable(true) + 2;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void add_boolean_with_number()
{
    auto data = variable(true) + 3.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void add_boolean_with_string()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable("alpha")),
                                    error,
                                    "incompatible type");
}

void add_boolean_with_array()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void add_boolean_with_map()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void add_integer_with_null()
{
    auto data = variable(2) + variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 2);
}

void add_integer_with_boolean()
{
    auto data = variable(2) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 3);
}

void add_integer_with_integer()
{
    auto data = variable(2) + 2;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 4);
}

void add_integer_with_number()
{
    auto data = variable(2) + 3.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 5);
}

void add_integer_with_string()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable("alpha")),
                                    error,
                                    "incompatible type");
}

void add_integer_with_array()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void add_integer_with_map()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void add_number_with_null()
{
    auto data = variable(3.0) + variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 3.0);
}

void add_number_with_boolean()
{
    auto data = variable(3.0) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 4.0);
}

void add_number_with_integer()
{
    auto data = variable(3.0) + 2;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 5.0);
}

void add_number_with_number()
{
    auto data = variable(3.0) + 3.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 6.0);
}

void add_number_with_string()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable("alpha")),
                                    error,
                                    "incompatible type");
}

void add_number_with_array()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void add_number_with_map()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void add_string_with_null()
{
    auto data = variable("alpha") + variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha");
}

void add_string_with_boolean()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable(true)),
                                    error,
                                    "incompatible type");
}

void add_string_with_integer()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable(2)),
                                    error,
                                    "incompatible type");
}

void add_string_with_number()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable(3.0)),
                                    error,
                                    "incompatible type");
}

void add_string_with_string()
{
    auto data = variable("alpha") + variable("-bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha-bravo");
}

void add_string_with_array()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::array({ true, "alpha" })),
                                    error,
                                    "incompatible type");
}

void add_string_with_map()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void add_array_with_null()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" }) + variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_boolean()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" }) + true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_integer()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" }) + 4;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_number()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" }) + 6.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", 6.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_string()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" }) + "bravo";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    variable expect = variable::array({ true, 2, 3.0, "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_array()
{
    variable data = variable::array({ true, 2 }) + variable::array({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void add_array_with_map()
{
    variable data = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::map({{ "alpha", "hydrogen" }})),
                                    error,
                                    "incompatible type");
}

void add_map_with_null()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        }) + variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
}

void add_map_with_boolean()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable(true)),
                                    error,
                                    "incompatible type");
}

void add_map_with_integer()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable(2)),
                                    error,
                                    "incompatible type");
}

void add_map_with_number()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable(3.0)),
                                    error,
                                    "incompatible type");
}

void add_map_with_string()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable("alpha")),
                                    error,
                                    "incompatible type");
}

void add_map_with_array()
{
    variable data = variable::map(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(operator+(data, variable::array({ true, 2 })),
                                    error,
                                    "incompatible type");
}

void add_map_with_map()
{
    variable data = operator+
        (variable::map(
            {
                { "alpha", "hydrogen" },
                { "bravo", "helium" }
            }),
         variable::map(
             {
                 {"charlie", "lithium"}
             }));
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
    data.value<variable::null_type>(error);
    TRIAL_PROTOCOL_TEST(!error);
}

void fail_null_as_boolean()
{
    variable data;
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(error), variable::boolean_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_integer()
{
    variable data;
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(error), variable::integer_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_number()
{
    variable data;
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(error), variable::number_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_string()
{
    variable data;
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), variable::string_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_array()
{
    variable data;
    std::error_code error;
    data.value<variable::array_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_map()
{
    variable data;
    std::error_code error;
    data.value<variable::map_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_null()
{
    variable data(false);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(error), false);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<variable::null_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_boolean_as_boolean()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));

    data = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void test_boolean_as_integer()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), variable::integer_type(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<short>(), 0);

    data = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 1);
}

void test_boolean_as_number()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), variable::number_type(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);

    data = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 1.0);
}

void fail_boolean_as_string()
{
    variable data(false);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), false);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), variable::string_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_array()
{
    variable data(false);
    std::error_code error;
    data.value<variable::array_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_map()
{
    variable data(false);
    std::error_code error;
    data.value<variable::map_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_null()
{
    variable data(0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(error), 0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<variable::null_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_integer_as_boolean()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), variable::boolean_type(data));

    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);

    data = std::numeric_limits<variable::integer_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void test_integer_as_integer()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), variable::integer_type(data));

    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 1);

    data = std::numeric_limits<variable::integer_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(),
                              std::numeric_limits<variable::integer_type>::max());
}

void test_integer_as_number()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), variable::number_type(data));

    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 1.0);

    data = std::numeric_limits<variable::integer_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(),
                              std::numeric_limits<variable::integer_type>::max());
}

void fail_integer_as_string()
{
    variable data(0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(error), 0);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), variable::string_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_array()
{
    variable data(0);
    std::error_code error;
    data.value<variable::array_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_map()
{
    variable data(0);
    std::error_code error;
    data.value<variable::map_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_number_as_null()
{
    variable data(0.0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<variable::null_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_number_as_boolean()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), variable::boolean_type(data));

    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);

    data = std::numeric_limits<variable::number_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), true);
}

void test_number_as_integer()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), variable::integer_type(data));

    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 1);

    data = 2.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), 2);
}

void test_number_as_number()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), variable::number_type(data));

    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), 1.0);

    data = std::numeric_limits<variable::number_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(),
                              std::numeric_limits<variable::number_type>::max());
}

void fail_number_as_string()
{
    variable data(0.0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), variable::string_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_number_as_array()
{
    variable data(0.0);
    std::error_code error;
    data.value<variable::array_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_number_as_map()
{
    variable data(0.0);
    std::error_code error;
    data.value<variable::map_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_null()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    data.value<variable::null_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_boolean()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(error), variable::boolean_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_integer()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(error), variable::integer_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_number()
{
    variable data("alpha");
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(error), "alpha");
    TRIAL_PROTOCOL_TEST(!error);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(error), variable::number_type{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_string_as_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "alpha");

    data = "bravo";
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::string_type>(), "bravo");
}

void fail_string_as_array()
{
    variable data("alpha");
    std::error_code error;
    data.value<variable::array_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_map()
{
    variable data("alpha");
    std::error_code error;
    data.value<variable::map_type>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_array_as_array()
{
    variable data = variable::array({ 1, 2, 3 });
    auto result = data.value<variable::array_type>();
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 data.begin(), data.end(),
                                 std::equal_to<variable>());
}

void test_array_with_size()
{
    variable data = variable::array(4, true);
    variable result = variable::array({ true, true, true, true });
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

    fail_number_as_null();
    test_number_as_boolean();
    test_number_as_integer();
    test_number_as_number();
    fail_number_as_string();
    fail_number_as_array();
    fail_number_as_map();

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
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST(data[0] == true);
    TRIAL_PROTOCOL_TEST(data[1] == 2);
    TRIAL_PROTOCOL_TEST(data[2] == 3.0);
    TRIAL_PROTOCOL_TEST(data[3] == "alpha");
}

void index_array_const()
{
    const variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST(data[0] == true);
    TRIAL_PROTOCOL_TEST(data[1] == 2);
    TRIAL_PROTOCOL_TEST(data[2] == 3.0);
    TRIAL_PROTOCOL_TEST(data[3] == "alpha");
}

void index_map()
{
    variable data = variable::map(
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
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data["alpha"],
                                    error,
                                    "incompatible type");
}

void key_map()
{
    variable data = variable::map(
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
    TRIAL_PROTOCOL_TEST(data["unknown"] == variable::null);
}

void key_map_const()
{
    const variable data = variable::map(
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

    key_null();
    key_boolean();
    key_integer();
    key_number();
    key_string();
    key_array();
    key_map();
    key_map_const();
}

} // namespace subscript_suite

//-----------------------------------------------------------------------------
// Clear
//-----------------------------------------------------------------------------

namespace clear_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::boolean_type>(), variable::boolean_type{});
}

void test_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::integer_type>(), variable::integer_type{});
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<variable::number_type>(), variable::integer_type{});
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void test_array()
{
    variable data = variable::array({ 1, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void test_map()
{
    variable data = variable::map({ {"alpha", 1} });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
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
    variable data(1);
    TRIAL_PROTOCOL_TEST(!data.empty());
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(!data.empty());
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
    variable data = variable::array();
    TRIAL_PROTOCOL_TEST(data.empty());
    data = variable::array({ 1, 2 });
    TRIAL_PROTOCOL_TEST(!data.empty());
}

void test_map()
{
    variable data = variable::map();
    TRIAL_PROTOCOL_TEST(data.empty());
    data = variable::map({ {"alpha", 1} });
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
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
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
    variable data = variable::array({ 1, 2, 3 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
}

void test_array_with_size()
{
    variable data = variable::array(3, 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
}

void test_map()
{
    variable data = variable::map({ {"alpha", 1} });
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
// main
//-----------------------------------------------------------------------------

int main()
{
    ctor_suite::run();
    copy_suite::run();
    move_suite::run();
    assign_suite::run();
    append_suite::run();
    addition_suite::run();

    value_suite::run();
    subscript_suite::run();

    clear_suite::run();
    empty_suite::run();
    size_suite::run();

    return boost::report_errors();
}
