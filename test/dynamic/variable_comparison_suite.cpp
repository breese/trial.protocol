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
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::array(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::array({ variable::null }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::array({ variable::null }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::array({ 1, 2, 3 }), true);
}

void test_null_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::map(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::map({ {"alpha", 1} }), true);
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
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != "", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable("alpha"), true);
}

void test_boolean_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable::array(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable::array({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable::array({ 1, 2, 3 }), true);
}

void test_boolean_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable::map(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable::map({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable::map({ {"alpha", 1} }), true);
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

void test_integer_equal_array()
{
    const auto max = std::numeric_limits<variable::integer_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::array(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::array({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::array({ 1, 2, 3 }), true);
}

void test_integer_equal_map()
{
    const auto max = std::numeric_limits<variable::integer_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::map(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::map({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::map({ {"alpha", 1} }), true);
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

void test_number_equal_array()
{
    const auto max = std::numeric_limits<variable::number_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::array(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::array({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::array({ 1, 2, 3 }), true);
}

void test_number_equal_map()
{
    const auto max = std::numeric_limits<variable::number_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::map(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::map({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(max) != variable::map({ {"alpha", 1} }), true);
}

void test_string_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable::null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable::null, true);
}

void test_string_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(true), true);
}

void test_string_equal_integer()
{
    const auto max = std::numeric_limits<variable::integer_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != max, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(max), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(max), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != max, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(max), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(max), true);
}

void test_string_equal_number()
{
    const auto max = std::numeric_limits<variable::number_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != max, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(max), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(max), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != max, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(max), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(max), true);
}

void test_string_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != "", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != "bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != "bravo", false);
}

void test_string_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable::array(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable::array({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable::array({ 1, 2, 3 }), true);
}

void test_string_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable::map(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable::map({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable::map({ {"alpha", 1} }), true);
}

void test_array_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable::null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable::null, true);
}

void test_array_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != true, true);
}

void test_array_equal_integer()
{
    const auto max = std::numeric_limits<variable::integer_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != max, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != max, true);
}

void test_array_equal_number()
{
    const auto max = std::numeric_limits<variable::number_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != max, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != max, true);
}

void test_array_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != "alpha", true);
}

void test_array_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable::array({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable::array({ 1, 2, 3 }), false);

    // Different sizes
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable::array({ 1, 2, 3, 4 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable::array({ 1, 2, 3, 4 }), true);

    // Different content
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3, 5 }) == variable::array({ 1, 2, 3, 4 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3, 5 }) != variable::array({ 1, 2, 3, 4 }), true);
}

void test_array_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable::map({ {"alpha", 1} }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable::map({ {"alpha", 1} }), true);
}

void test_map_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable::null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::null, true);
}

void test_map_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != true, true);
}

void test_map_equal_integer()
{
    const auto max = std::numeric_limits<variable::integer_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != max, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != max, true);
}

void test_map_equal_number()
{
    const auto max = std::numeric_limits<variable::number_type>::max();

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != max, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == max, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != max, true);
}

void test_map_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != "alpha", true);
}

void test_map_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable::array({ 1, 2, 3 }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::array({ 1, 2, 3 }), true);
}

void test_map_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable::array({ {"alpha", 1} }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::map({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::map({ {"alpha", 1}, {"bravo", 2} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::map({ {"alpha", 1}, {"bravo", 2} }), true);
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

    test_boolean_equal_null();
    test_boolean_equal_boolean();
    test_boolean_equal_integer();
    test_boolean_equal_number();
    test_boolean_equal_string();
    test_boolean_equal_array();
    test_boolean_equal_map();

    test_integer_equal_null();
    test_integer_equal_boolean();
    test_integer_equal_integer();
    test_integer_equal_number();
    test_integer_equal_string();
    test_integer_equal_array();
    test_integer_equal_map();

    test_number_equal_null();
    test_number_equal_boolean();
    test_number_equal_integer();
    test_number_equal_number();
    test_number_equal_string();
    test_number_equal_array();
    test_number_equal_map();

    test_string_equal_null();
    test_string_equal_boolean();
    test_string_equal_integer();
    test_string_equal_number();
    test_string_equal_string();
    test_string_equal_array();
    test_string_equal_map();

    test_array_equal_null();
    test_array_equal_boolean();
    test_array_equal_integer();
    test_array_equal_number();
    test_array_equal_string();
    test_array_equal_array();
    test_array_equal_map();

    test_map_equal_null();
    test_map_equal_boolean();
    test_map_equal_integer();
    test_map_equal_number();
    test_map_equal_string();
    test_map_equal_array();
    test_map_equal_map();
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
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({1, 2}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({0, 1}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({0, 2}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({1, 1}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({1, 0}), false);

    // Different sizes
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({0, 1, 2}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({0, 2, 3}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({1, 2, 3}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({0, 1}) < variable::array({1}), false);
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
