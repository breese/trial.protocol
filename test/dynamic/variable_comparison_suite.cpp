///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <trial/protocol/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// Equality
//-----------------------------------------------------------------------------

namespace equality_suite
{

void test_null_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::null, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(), false);
}

void test_null_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(true), true);
}

void test_null_equal_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 1, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(1), true);
}

void test_null_equal_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 0.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 1.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(0.0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(1.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(1.0), true);
}

void test_null_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != "", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable("alpha"), true);
}

void test_null_equal_array()
{
    variable::array_type param = { 1, 2, 3 };
    variable array(param);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == array, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != array, true);

    array.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == array, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != array, true);
}

void test_null_equal_map()
{
    variable::map_type param{ {"alpha", 1} };
    variable map(param);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == map, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != map, true);

    map.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == map, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != map, true);
}

void test_boolean_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable::null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable::null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(), true);
}

void test_boolean_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != false, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(false), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != true, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(true), false);
}

void test_boolean_equal_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != 0, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(0), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != 0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(0), true);
}

void test_boolean_equal_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != 0.0, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(0.0), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != 0.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(0.0), true);
}

void test_boolean_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable("alpha"), true);
}

void test_integer_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable::null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(), true);
}

void test_integer_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != false, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(false), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != true, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(true), false);

    const variable max(std::numeric_limits<variable::integer_type>::max());

    TRIAL_PROTOCOL_TEST_EQUAL(max == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != variable(true), true);
}

void test_integer_equal_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 0, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 1, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(0), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(1), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 1, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(1), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(1), false);

    const variable max(std::numeric_limits<variable::integer_type>::max());

    TRIAL_PROTOCOL_TEST_EQUAL(max == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != 0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != 1, true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != variable(0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != variable(1), true);
}

void test_integer_equal_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 0.0, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 1.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(0.0), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(1.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(1.0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 0.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 1.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 1.0, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(0.0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(1.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(1.0), false);

    const variable max(std::numeric_limits<variable::integer_type>::max());

    TRIAL_PROTOCOL_TEST_EQUAL(max == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != 0.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != 1.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != variable(0.0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(max == variable(1.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(max != variable(1.0), true);
}

void test_integer_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != "", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != "", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable("alpha"), true);
}

void test_number_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable::null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(), true);
}

void test_number_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(true), false);

    auto big = std::numeric_limits<variable::integer_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable(true), true);
}

void test_number_equal_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(1), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(1), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(1), false);

    auto big = std::numeric_limits<variable::number_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable(1), true);
}

void test_number_equal_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 1.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(1.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(1.0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == 1.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(1.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(1.0), false);

    auto big = std::numeric_limits<variable::number_type>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != 1.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable(1.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable(1.0), true);
}

void test_number_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable("alpha"), true);
}

void test_string_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != "bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != "bravo", false);
}

void test_array_equal_array()
{
    variable::array_type data_param = { 1, 2, 3 };
    variable data(data_param);
    variable::array_type array_param = { 1, 2, 3 };
    variable array(array_param);
    TRIAL_PROTOCOL_TEST_EQUAL(data == array, true);
    TRIAL_PROTOCOL_TEST_EQUAL(data != array, false);

    // Different sizes
    array_param.push_back(4);
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data == array, false);
    TRIAL_PROTOCOL_TEST_EQUAL(data != array, true);

    // Different content
    data_param.push_back(5);
    data = data_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data == array, false);
    TRIAL_PROTOCOL_TEST_EQUAL(data != array, true);
}

void run()
{
    test_null_equal_null();
    test_null_equal_boolean();
    test_null_equal_integer();
    test_null_equal_number();
    test_null_equal_string();
    test_null_equal_array();
    test_null_equal_map();

    // FIXME: More
    test_boolean_equal_null();
    test_boolean_equal_boolean();
    test_boolean_equal_integer();
    test_boolean_equal_number();
    test_boolean_equal_string();

    test_integer_equal_null();
    test_integer_equal_boolean();
    test_integer_equal_integer();
    test_integer_equal_number();
    test_integer_equal_string();

    test_number_equal_null();
    test_number_equal_boolean();
    test_number_equal_integer();
    test_number_equal_number();
    test_number_equal_string();

    test_string_equal_string();

    test_array_equal_array();
}

} // namespace equality_suite

//-----------------------------------------------------------------------------
// Relational
//-----------------------------------------------------------------------------

namespace relational_suite
{

void test_null_less_null()
{
    variable null;
    TRIAL_PROTOCOL_TEST_EQUAL(null < variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(null <= variable::null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(null > variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(null >= variable::null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(null < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(null <= variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(null > variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(null >= variable(), true);
}

void test_null_less_boolean()
{
    variable null;
    TRIAL_PROTOCOL_TEST_EQUAL(null < false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(null < variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(null < true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(null < variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(null <= false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(null <= variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(null <= true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(null <= variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(null > false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(null > variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(null > true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(null > variable(true), false);

    TRIAL_PROTOCOL_TEST_EQUAL(null >= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(null >= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(null >= true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(null >= variable(true), false);
}

void test_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= true, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= true, true);
}

void test_boolean_less_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(true), false);
}

void test_boolean_less_integer()
{
    variable data(false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(1), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(1), false);
}

void test_integer_less_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(true), false);
}

void test_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(1), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(1), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < 2, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= 2, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > 2, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= 2, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(2), false);
}

void test_integer_less_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < 1, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < 2, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(1), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(2), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < 2, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(2), true);
}

void test_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= "bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") <= "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") > "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") >= "alpha", true);
}

void test_array_less_array()
{
    variable::array_type data_param = { 0, 1 };
    variable data(data_param);
    variable::array_type array_param = { 1, 2 };
    variable array(array_param);
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, true);

    array_param.assign({0, 1});
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, false);

    array_param.assign({0, 2});
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, false);

    array_param.assign({1, 1});
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, false);

    array_param.assign({1, 0});
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, false);

    // Different sizes
    array_param.assign({1, 2, 3});
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, true);

    array_param.assign({0, 2, 3});
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, false);

    array_param.assign({1});
    array = array_param;
    TRIAL_PROTOCOL_TEST_EQUAL(data < array, false);
}

void run()
{
    // FIXME: Check all relational operators
    // FIXME: More
    test_null_less_null();
    test_null_less_boolean();

    test_boolean();
    test_boolean_less_boolean();
    test_boolean_less_integer();

    test_integer();
    test_integer_less_boolean();
    test_integer_less_integer();

    // FIXME: Number with NaN etc.

    test_string();

    test_array_less_array();
}

} // namespace relational_suite

//-----------------------------------------------------------------------------
// operator bool()
//-----------------------------------------------------------------------------

namespace operator_bool_suite
{

void test_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable()), false);
}

void test_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(false)), false);
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(true)), true);
}

void test_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(0)), false);
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(1)), true);
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(std::numeric_limits<variable::integer_type>::max())), true);
}

void test_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(0.0)), false);
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(1.0)), true);
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(std::numeric_limits<variable::number_type>::max())), true);
}

void run()
{
    // FIXME: More
    test_null();
    test_boolean();
    test_integer();
    test_number();
}

} // namespace operator_bool_suite

//-----------------------------------------------------------------------------
// std::equal_to
//-----------------------------------------------------------------------------

namespace equal_to_suite
{

void test_boolean()
{
    TRIAL_PROTOCOL_TEST(std::equal_to<variable>()(true, true));
    TRIAL_PROTOCOL_TEST(std::equal_to<variable>()(variable(true), variable(true)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(false), variable(true)));
}

void run()
{
    // FIXME: More
    test_boolean();
}

} // namespace equal_to_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    equality_suite::run();
    relational_suite::run();

    operator_bool_suite::run();

    equal_to_suite::run();
    // FIXME: Other comparison function objects

    return boost::report_errors();
}
