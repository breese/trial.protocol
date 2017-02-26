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
    std::vector<variable> array = { 1, 2 };
    variable data(array);
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
    variable data(array.begin(), array.end());
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

void test_map_with_map()
{
    std::map<std::string, variable> map{ {"alpha", 1} };
    variable data(map);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void test_map_with_string()
{
    variable data(std::string("alpha"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
}

void test_map_with_literal()
{
    variable data("alpha", 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
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
    test_array_with_size();

    test_map_with_map();
    test_map_with_string();
    test_map_with_literal();
    test_map_by_name();

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

void test_null_assign_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void test_null_assign_boolean()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void test_null_assign_integer()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void test_null_assign_number()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void test_null_assign_string()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void test_null_assign_string_literal()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
    data = "alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void test_boolean_assign_null()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void test_boolean_assign_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
}

void test_boolean_assign_integer()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = 1;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
}

void test_boolean_assign_number()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::number_type>(), true);
}

void test_boolean_assign_string()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::boolean_type>(), true);
    data = variable::string_type("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
}

void test_integer_assign_null()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::integer_type>(), true);
    data = variable::null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::null_type>(), true);
}

void run()
{
    // FIXME: More
    test_null_assign_null();
    test_null_assign_boolean();
    test_null_assign_integer();
    test_null_assign_number();
    test_null_assign_string();
    test_null_assign_string_literal();

    test_boolean_assign_null();
    test_boolean_assign_boolean();
    test_boolean_assign_integer();
    test_boolean_assign_number();
    test_boolean_assign_string();

    test_integer_assign_null();
}

} // namespace assign_suite

//-----------------------------------------------------------------------------
// Getter
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
    variable::array_type array = { 1, 2 };
    variable data(array);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void test_map()
{
    variable::map_type map{ {"alpha", 1} };
    variable data(map);
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
    variable::array_type array = { 1, 2 };
    variable data(array);
    TRIAL_PROTOCOL_TEST(!data.empty());
}

void test_map()
{
    variable::map_type map{ {"alpha", 1} };
    variable data(map);
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
    variable::map_type map{ {"alpha", 1} };
    variable data(map);
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

    value_suite::run();
    clear_suite::run();
    empty_suite::run();
    size_suite::run();

    return boost::report_errors();
}
