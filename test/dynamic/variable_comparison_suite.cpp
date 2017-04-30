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

void compare_null_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(), false);
}

void compare_null_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != null, false);
}

void compare_null_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(true), true);
}

void compare_null_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != true, true);
}

void compare_null_equal_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(1), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(1), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(0U), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(0U), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(1U), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(1U), true);
}

void compare_null_equal_integer_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 1, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 1, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 0U, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 0U, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 1U, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 1U, true);
}

void compare_null_equal_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(0.0f), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(0.0f), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(1.0f), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(1.0f), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(1.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(1.0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(0.0L), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(0.0L), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(1.0L), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(1.0L), true);
}

void compare_null_equal_number_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 0.0f, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 0.0f, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 1.0f, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 1.0f, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 1.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == 1.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != 1.0, true);
}

void compare_null_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable("alpha"), true);
}

void compare_null_equal_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != "", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != "alpha", true);
}

void compare_null_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::array(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::array({ null }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::array({ null }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::array({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::array({ 1, 2, 3 }), true);
}

void compare_null_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::map(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable::map({ {"alpha", 1} }), true);
}

void compare_boolean_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(), true);
}

void compare_boolean_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != null, true);
}

void compare_boolean_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(true), false);
}

void compare_boolean_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != true, false);
}

void compare_boolean_equal_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(0U), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(0U), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(0U), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(0U), true);
}

void compare_boolean_equal_integer_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == 0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == 0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != 0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == 0U, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != 0U, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == 0U, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != 0U, true);
}

void compare_boolean_equal_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(0.0f), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(0.0f), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(0.0f), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(0.0f), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(0.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(0.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(0.0), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(0.0L), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(0.0L), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(0.0L), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(0.0L), true);
}

void compare_boolean_equal_number_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == 0.0f, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != 0.0f, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == 0.0f, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != 0.0f, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == 0.0, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == 0.0, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != 0.0, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == 0.0L, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != 0.0L, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == 0.0L, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != 0.0L, true);
}

void compare_boolean_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable("alpha"), true);
}

void compare_boolean_equal_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != "", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != "alpha", true);
}

void compare_boolean_equal_array()
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

void compare_boolean_equal_map()
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

void compare_integer_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(), true);
}

void compare_integer_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != null, true);
}

void compare_integer_equal_boolean()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(true), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(true), false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(true), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(true), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(true), false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(true), true);
    }
}

void compare_integer_equal_boolean_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != true, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != true, false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != true, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != true, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != true, false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != true, true);
    }
}

void compare_integer_equal_integer()
{
    // signed - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(1), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(1), false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1), true);
    }
    // signed - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(1U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(1U), false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1U), true);
    }
    // unsigned - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(1), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(1), false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1), true);
    }
    // unsigned - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(1U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(1U), false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1U), true);
    }
}

void compare_integer_equal_integer_literal()
{
    // signed - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 1, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 1, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 1, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 1, false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1, true);
    }
    // signed - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 1U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 1U, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 1U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 1U, false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1U, true);
    }
    // unsigned - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 1, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 1, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 1, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 1, false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1, true);
    }
    // unsigned - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 1U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 1U, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 1U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 1U, false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1U, true);
    }
}

void compare_integer_equal_number()
{
    // signed - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(1.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(1.0f), false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1.0f), true);
    }
    // signed - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(1.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(1.0), false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1.0), true);
    }
    // signed - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(1.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(1.0L), false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1.0L), true);
    }
    // unsigned - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(1.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(1.0f), false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1.0f), true);
    }
    // unsigned - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(1.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(1.0), false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1.0), true);
    }
    // unsigned - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(1.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(1.0L), false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != variable(1.0L), true);
    }
}

void compare_integer_equal_number_literal()
{
    // signed - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 1.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 1.0f, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 1.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 1.0f, false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1.0f, true);
    }
    // signed - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 1.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 1.0, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 1.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 1.0, false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1.0, true);
    }
    // signed - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == 1.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != 1.0L, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == 1.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != 1.0L, false);

        const variable big(std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1.0L, true);
    }
    // unsigned - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 1.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 1.0f, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 1.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 1.0f, false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1.0f, true);
    }
    // unsigned - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 1.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 1.0, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 1.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 1.0, false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1.0, true);
    }
    // unsigned - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == 1.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != 1.0L, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == 1.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != 1.0L, false);

        const variable big(std::numeric_limits<unsigned int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(big == 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(big == 1.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(big != 1.0L, true);
    }
}

void compare_integer_equal_string()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable("alpha"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable("alpha"), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable("alpha"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable("alpha"), true);
    }
}

void compare_integer_equal_string_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != "", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != "alpha", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != "", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != "alpha", true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != "", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != "alpha", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != "", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != "alpha", true);
    }
}

void compare_integer_equal_array()
{
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::array(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::array({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array({ 1, 2, 3 }), true);
    }
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable::array(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable::array({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array({ 1, 2, 3 }), true);
    }
}

void compare_integer_equal_map()
{
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::map(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable::map({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map({ {"alpha", 1} }), true);
    }
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable::map(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable::map({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map({ {"alpha", 1} }), true);
    }
}

void compare_number_equal_null()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(), true);
    }
}

void compare_number_equal_null_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != null, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != null, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != null, true);
    }
}

void compare_number_equal_boolean()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(true), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(true), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(true), true);
    }
}

void compare_number_equal_boolean_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != true, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != true, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != true, true);
    }
}

void compare_number_equal_integer()
{
    // float - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(1), true);
    }
    // float - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(1U), true);
    }
    // double - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(1), true);
    }
    // double - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(1U), true);
    }
    // long double - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(1), true);
    }
    // long double - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(1U), true);
    }
}

void compare_number_equal_integer_literal()
{
    // float - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 1, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 1, true);
    }
    // float - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 1U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 1U, true);
    }
    // double - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 1, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 1, true);
    }
    // double - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 1U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 1U, true);
    }
    // long double - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 1, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 1, true);
    }
    // long double - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 1U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 1U, true);
    }
}

void compare_number_equal_number()
{
    // float - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(1.0f), true);
    }
    // float - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(1.0), true);
    }
    // float - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(1.0L), true);
    }
    // double - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(1.0f), true);
    }
    // double - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(1.0), true);
    }
    // double - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(1.0L), true);
    }
    // long double - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(1.0f), true);
    }
    // long double - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(1.0), true);
    }
    // long double - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(1.0L), true);
    }
}

void compare_number_equal_number_literal()
{
    // float - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 1.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 1.0f, true);
    }
    // float - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 1.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 1.0, true);
    }
    // float - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == 1.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != 1.0L, true);
    }
    // double - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 1.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 1.0f, true);
    }
    // double - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 1.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 1.0, true);
    }
    // double - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == 1.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != 1.0L, true);
    }
    // long double - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 0.0f, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 0.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 1.0f, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 1.0f, true);
    }
    // long double - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 0.0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 0.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 1.0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 1.0, true);
    }
    // long double - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 0.0L, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 0.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == 1.0L, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != 1.0L, true);
    }
}

void compare_number_equal_string()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != variable("alpha"), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable("alpha"), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != variable("alpha"), true);
    }
}

void compare_number_equal_string_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != "alpha", true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != "alpha", true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != "alpha", true);
    }
}

void compare_number_equal_array()
{
    {
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable::array(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable::array({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array({ 1, 2, 3 }), true);
    }
    {
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::array(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::array({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array({ 1, 2, 3 }), true);
    }
    {
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable::array(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable::array({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::array({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::array({ 1, 2, 3 }), true);
    }
}

void compare_number_equal_map()
{
    {
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable::map(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable::map({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map({ {"alpha", 1} }), true);
    }
    {
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::map(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable::map({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map({ {"alpha", 1} }), true);
    }
    {
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable::map(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable::map({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == variable::map({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != variable::map({ {"alpha", 1} }), true);
    }
}

void compare_string_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(), true);
}

void compare_string_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != null, true);
}

void compare_string_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(true), true);
}

void compare_string_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != true, true);
}

void compare_string_equal_integer()
{
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(big), true);
    }
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(big), true);
    }
}

void compare_string_equal_integer_literal()
{
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != big, true);
    }
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != big, true);
    }
}

void compare_string_equal_number()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(big), true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(big), true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(big), true);
    }
}

void compare_string_equal_number_literal()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != big, true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != big, true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != big, true);
    }
}

void compare_string_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable("bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == variable("bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != variable("bravo"), false);
}

void compare_string_equal_string_literal()
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

void compare_string_equal_array()
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

void compare_string_equal_map()
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

void compare_array_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(), true);
}

void compare_array_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != null, true);
}

void compare_array_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(true), true);
}

void compare_array_equal_boolean_literal()
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

void compare_array_equal_integer()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(big), true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(big), true);
    }
}

void compare_array_equal_integer_literal()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != big, true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != big, true);
    }
}

void compare_array_equal_number()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(big), true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(big), true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(big), true);
    }
}

void compare_array_equal_number_literal()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != big, true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != big, true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != big, true);
    }
}

void compare_array_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array() != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::array({ 1, 2, 3 }) != variable("alpha"), true);
}

void compare_array_equal_string_literal()
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

void compare_array_equal_array()
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

void compare_array_equal_map()
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

void compare_map_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(), true);
}

void compare_map_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != null, true);
}

void compare_map_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(true), true);
}

void compare_map_equal_boolean_literal()
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

void compare_map_equal_integer()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(big), true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(big), true);
    }
}

void compare_map_equal_integer_literal()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != big, true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != big, true);
    }
}

void compare_map_equal_number()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(big), true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(big), true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(big), true);
    }
}

void compare_map_equal_number_literal()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != big, true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != big, true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != big, true);
    }
}

void compare_map_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable("alpha"), true);
}

void compare_map_equal_string_literal()
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

void compare_map_equal_array()
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

void compare_map_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() == variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map() != variable::map({ {"alpha", 1} }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::map({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::map({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) == variable::map({ {"alpha", 1}, {"bravo", 2} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable::map({ {"alpha", 1} }) != variable::map({ {"alpha", 1}, {"bravo", 2} }), true);
}

void run()
{
    compare_null_equal_null();
    compare_null_equal_null_literal();
    compare_null_equal_boolean();
    compare_null_equal_boolean_literal();
    compare_null_equal_integer();
    compare_null_equal_integer_literal();
    compare_null_equal_number();
    compare_null_equal_number_literal();
    compare_null_equal_string();
    compare_null_equal_string_literal();
    compare_null_equal_array();
    compare_null_equal_map();

    compare_boolean_equal_null();
    compare_boolean_equal_null_literal();
    compare_boolean_equal_boolean();
    compare_boolean_equal_boolean_literal();
    compare_boolean_equal_integer();
    compare_boolean_equal_integer_literal();
    compare_boolean_equal_number();
    compare_boolean_equal_number_literal();
    compare_boolean_equal_string();
    compare_boolean_equal_string_literal();
    compare_boolean_equal_array();
    compare_boolean_equal_map();

    compare_integer_equal_null();
    compare_integer_equal_null_literal();
    compare_integer_equal_boolean();
    compare_integer_equal_boolean_literal();
    compare_integer_equal_integer();
    compare_integer_equal_integer_literal();
    compare_integer_equal_number();
    compare_integer_equal_number_literal();
    compare_integer_equal_string();
    compare_integer_equal_string_literal();
    compare_integer_equal_array();
    compare_integer_equal_map();

    compare_number_equal_null();
    compare_number_equal_null_literal();
    compare_number_equal_boolean();
    compare_number_equal_boolean_literal();
    compare_number_equal_integer();
    compare_number_equal_integer_literal();
    compare_number_equal_number();
    compare_number_equal_number_literal();
    compare_number_equal_string();
    compare_number_equal_string_literal();
    compare_number_equal_array();
    compare_number_equal_map();

    compare_string_equal_null();
    compare_string_equal_null_literal();
    compare_string_equal_boolean();
    compare_string_equal_boolean_literal();
    compare_string_equal_integer();
    compare_string_equal_integer_literal();
    compare_string_equal_number();
    compare_string_equal_number_literal();
    compare_string_equal_string();
    compare_string_equal_string_literal();
    compare_string_equal_array();
    compare_string_equal_map();

    compare_array_equal_null();
    compare_array_equal_null_literal();
    compare_array_equal_boolean();
    compare_array_equal_boolean_literal();
    compare_array_equal_integer();
    compare_array_equal_integer_literal();
    compare_array_equal_number();
    compare_array_equal_number_literal();
    compare_array_equal_string();
    compare_array_equal_string_literal();
    compare_array_equal_array();
    compare_array_equal_map();

    compare_map_equal_null();
    compare_map_equal_null_literal();
    compare_map_equal_boolean();
    compare_map_equal_boolean_literal();
    compare_map_equal_integer();
    compare_map_equal_integer_literal();
    compare_map_equal_number();
    compare_map_equal_number_literal();
    compare_map_equal_string();
    compare_map_equal_string_literal();
    compare_map_equal_array();
    compare_map_equal_map();
}

} // namespace equality_suite

//-----------------------------------------------------------------------------
// Relational
//-----------------------------------------------------------------------------

namespace relational_suite
{

void compare_null_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(), true);
}

void compare_null_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= null, true);
}

void compare_null_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(false), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(true), false);
}

void compare_null_with_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= false, false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() < true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= true, false);
}

void compare_null_with_integer()
{
    {
        const signed int zero = 0;
        const signed int one = 1;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(zero), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(one), false);
    }
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(zero), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(one), false);
    }
}

void compare_null_with_integer_literal()
{
    {
        const signed int zero = 0;
        const signed int one = 1;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= zero, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= one, false);
    }
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= zero, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= one, false);
    }
}

void compare_null_with_number()
{
    {
        const float zero = 0.0f;
        const float one = 1.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(zero), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(one), false);
    }
    {
        const double zero = 0.0;
        const double one = 1.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(zero), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(one), false);
    }
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(zero), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(one), false);
    }
}

void compare_null_with_number_literal()
{
    {
        const float zero = 0.0f;
        const float one = 1.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= zero, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= one, false);
    }
    {
        const double zero = 0.0;
        const double one = 1.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= zero, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= one, false);
    }
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= zero, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable() < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable() >= one, false);
    }
}

void compare_null_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(""), false);
}

void compare_null_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable::array(), false);
}

void compare_null_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable::map(), false);
}

void compare_boolean_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(), true);
}

void compare_boolean_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= null, true);
}

void compare_boolean_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(true), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(true), true);
}

void compare_boolean_with_boolean_literal()
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

void compare_boolean_with_integer()
{
    {
        const signed int zero = 0;
        const signed int one = 1;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(one), true);
    }
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(one), true);
    }
}

void compare_boolean_with_integer_literal()
{
    {
        const signed int zero = 0;
        const signed int one = 1;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= one, true);
    }
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= one, true);
    }
}

void compare_boolean_with_number()
{
    {
        const float zero = 0.0f;
        const float one = 1.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(one), true);
    }
    {
        const double zero = 0.0;
        const double one = 1.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(one), true);
    }
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(one), true);
    }
}

void compare_boolean_with_number_literal()
{
    {
        const float zero = 0.0f;
        const float one = 1.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= one, true);
    }
    {
        const double zero = 0.0;
        const double one = 1.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= one, true);
    }
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= one, true);
    }
}

void compare_boolean_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable("alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable("alpha"), false);
}

void compare_boolean_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable::array(), false);
}

void compare_boolean_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable::map(), false);
}

void compare_integer_with_null()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(), true);
    }
}

void compare_integer_with_null_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > null, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= null, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > null, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= null, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > null, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= null, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > null, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= null, true);
    }
}


void compare_integer_with_boolean()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(true), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(true), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(true), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(true), true);
    }
}

void compare_integer_with_boolean_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= true, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= true, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= true, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= true, true);
    }
}

void compare_integer_with_integer()
{
    // signed - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(two), false);
    }
    // signed - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(two), false);
    }
    // unsigned - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(two), false);
    }
    // unsigned - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(two), false);
    }
}

void compare_integer_with_integer_literal()
{
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= two, false);
    }
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= two, false);
    }
}

void compare_integer_with_number()
{
    // signed - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(two), false);
    }
    // signed - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(two), false);
    }
    // signed - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= variable(two), false);
    }
    // unsigned - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(two), false);
    }
    // unsigned - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(two), false);
    }
    // unsigned - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= variable(two), false);
    }
}

void compare_integer_with_number_literal()
{
    // signed - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= two, false);
    }
    // signed - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= two, false);
    }
    // signed - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) >= two, false);
    }
    // unsigned - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= two, false);
    }
    // unsigned - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= two, false);
    }
    // unsigned - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) >= two, false);
    }
}

void compare_integer_with_string()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable("alpha"), false);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable("alpha"), false);
    }
}

void compare_integer_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) < variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) <= variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) > variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) >= variable::array(), false);
}

void compare_integer_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) < variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) <= variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) > variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) >= variable::map(), false);
}

void compare_number_with_null()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(), true);
    }
}

void compare_number_with_null_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > null, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= null, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > null, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= null, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= null, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > null, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= null, true);
    }
}

void compare_number_with_boolean()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(true), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(true), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(true), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(true), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(true), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(false), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(false), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(false), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(true), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(true), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(true), true);
    }
}

void compare_number_with_boolean_literal()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= true, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= true, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= true, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= true, true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= true, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= false, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > false, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= false, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= true, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > true, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= true, true);
    }
}

void compare_number_with_integer()
{
    // float - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(two), false);
    }
    // float - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(two), false);
    }
    // double - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(two), false);
    }
    // double - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(two), false);
    }
    // long double - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(two), false);
    }
    // long double - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(two), false);
    }
}

void compare_number_with_integer_literal()
{
    // float - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= two, false);
    }
    // float - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= two, false);
    }
    // double - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= two, false);
    }
    // double - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= two, false);
    }
    // long double - signed
    {
        const signed int zero = 0;
        const signed int one = 1;
        const signed int two = 2;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= two, false);
    }
    // long double - unsigned
    {
        const unsigned int zero = 0U;
        const unsigned int one = 1U;
        const unsigned int two = 2U;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= two, false);
    }
}

void compare_number_with_number()
{
    // float - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(two), false);
    }
    // float - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(two), false);
    }
    // float - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= variable(two), false);
    }
    // double - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(two), false);
    }
    // double - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(two), false);
    }
    // double - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= variable(two), false);
    }
    // long double - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(two), false);
    }
    // long double - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(two), false);
    }
    // long double - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(one), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(two), false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(zero), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(one), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(one), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(one), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= variable(two), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > variable(two), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= variable(two), false);
    }
}

void compare_number_with_number_literal()
{
    // float - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= two, false);
    }
    // float - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= two, false);
    }
    // float - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) >= two, false);
    }
    // double - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= two, false);
    }
    // double - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= two, false);
    }
    // double - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) >= two, false);
    }
    // long double - float
    {
        const float zero = 0.0f;
        const float one = 1.0f;
        const float two = 2.0f;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= two, false);
    }
    // long double - double
    {
        const double zero = 0.0;
        const double one = 1.0;
        const double two = 2.0;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= two, false);
    }
    // long double - long double
    {
        const long double zero = 0.0L;
        const long double one = 1.0L;
        const long double two = 2.0L;

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= one, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= two, false);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= zero, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= one, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > one, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= one, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) < two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) <= two, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) > two, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) >= two, false);
    }
}

void compare_number_with_string()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable("alpha"), false);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable("alpha"), false);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable("alpha"), false);
    }
}

void compare_number_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) < variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) <= variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) > variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) >= variable::array(), false);
}

void compare_number_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) < variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) <= variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) > variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) >= variable::map(), false);
}

void compare_string_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") >= variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(), true);
}

void compare_string_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") >= null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= null, true);
}

void compare_string_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(true), true);
}

void compare_string_with_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= true, true);
}

void compare_string_with_integer()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(1), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(0U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(1U), true);
    }
}

void compare_string_with_number()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(0.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(1.0f), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(0.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(1.0), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(0.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(1.0L), true);
    }
}

void compare_string_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable("bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable("bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable("bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") < variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") <= variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") > variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") >= variable("alpha"), true);
}

void compare_string_with_string_literal()
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

void compare_string_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable::array(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable::array(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable::array(), false);
}

void compare_string_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable::map(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable::map(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable::map(), false);
}

void compare_array_with_array()
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
    compare_null_with_null();
    compare_null_with_null_literal();
    compare_null_with_boolean();
    compare_null_with_boolean_literal();
    compare_null_with_integer();
    compare_null_with_integer_literal();
    compare_null_with_number();
    compare_null_with_number_literal();
    compare_null_with_string();
    compare_null_with_array();
    compare_null_with_map();

    compare_boolean_with_null();
    compare_boolean_with_null_literal();
    compare_boolean_with_boolean();
    compare_boolean_with_boolean_literal();
    compare_boolean_with_integer();
    compare_boolean_with_integer_literal();
    compare_boolean_with_number();
    compare_boolean_with_number_literal();
    compare_boolean_with_string();
    compare_boolean_with_array();
    compare_boolean_with_map();

    compare_integer_with_null();
    compare_integer_with_null_literal();
    compare_integer_with_boolean();
    compare_integer_with_boolean_literal();
    compare_integer_with_integer();
    compare_integer_with_integer_literal();
    compare_integer_with_number();
    compare_integer_with_number_literal();
    compare_integer_with_string();
    compare_integer_with_array();
    compare_integer_with_map();

    // FIXME: Number with NaN etc.
    compare_number_with_null();
    compare_number_with_null_literal();
    compare_number_with_boolean();
    compare_number_with_boolean_literal();
    compare_number_with_integer();
    compare_number_with_integer_literal();
    compare_number_with_number();
    compare_number_with_number_literal();
    compare_number_with_string();
    compare_number_with_array();
    compare_number_with_map();

    compare_string_with_null();
    compare_string_with_null_literal();
    compare_string_with_boolean();
    compare_string_with_boolean_literal();
    compare_string_with_integer();
    compare_string_with_number();
    compare_string_with_string();
    compare_string_with_string_literal();
    compare_string_with_array();
    compare_string_with_map();

    // FIXME: More
    compare_array_with_array();
}

} // namespace relational_suite

//-----------------------------------------------------------------------------
// operator bool()
//-----------------------------------------------------------------------------

namespace operator_bool_suite
{

void test_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(bool(null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable()), false);
}

void test_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(false)), false);
    TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(true)), true);
}

void test_integer()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(0)), false);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(1)), true);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(std::numeric_limits<signed int>::max())), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(0U)), false);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(1U)), true);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(std::numeric_limits<unsigned int>::max())), true);
    }
}

void test_number()
{
    {
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(0.0f)), false);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(1.0f)), true);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(std::numeric_limits<float>::max())), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(0.0)), false);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(1.0)), true);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(std::numeric_limits<double>::max())), true);
    }
    {
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(0.0L)), false);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(1.0L)), true);
        TRIAL_PROTOCOL_TEST_EQUAL(bool(variable(std::numeric_limits<long double>::max())), true);
    }
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

void compare_null_with_null()
{
    TRIAL_PROTOCOL_TEST(std::equal_to<variable>()(variable(), null));
    TRIAL_PROTOCOL_TEST(std::equal_to<variable>()(variable(), variable()));
}

void compare_null_with_boolean()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), false));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(false)));
}

void compare_null_with_integer()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(2)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(2U)));
}

void compare_null_with_integer_literal()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 2));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 2U));
}

void compare_null_with_number()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(3.0)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(3.0L)));
}

void compare_null_with_number_literal()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 3.0f));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 3.0));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 3.0L));
}

void compare_boolean_with_null()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(false), null));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(false), variable()));
}

void compare_boolean_with_boolean()
{
    TRIAL_PROTOCOL_TEST(std::equal_to<variable>()(true, true));
    TRIAL_PROTOCOL_TEST(std::equal_to<variable>()(variable(true), variable(true)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(false), variable(true)));
}

void compare_boolean_with_integer()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(2)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(2U)));
}

void compare_boolean_with_integer_literal()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 2));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 2U));
}

void compare_boolean_with_number()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(3.0)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(3.0L)));
}

void compare_boolean_with_number_literal()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 3.0f));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 3.0));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 3.0L));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_integer_literal();
    compare_null_with_number();
    compare_null_with_number_literal();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_integer_literal();
    compare_boolean_with_number();
    compare_boolean_with_number_literal();
}

} // namespace equal_to_suite

//-----------------------------------------------------------------------------
// std::not_equal_to
//-----------------------------------------------------------------------------

namespace not_equal_to_suite
{

void compare_null_with_null()
{
    TRIAL_PROTOCOL_TEST(!std::not_equal_to<variable>()(variable(), null));
    TRIAL_PROTOCOL_TEST(!std::not_equal_to<variable>()(variable(), variable()));
}

void compare_null_with_boolean()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), false));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(false)));
}

void compare_null_with_integer()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(2)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(2U)));
}

void compare_null_with_integer_literal()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 2));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 2U));
}

void compare_null_with_number()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(3.0L)));
}

void compare_null_with_number_literal()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 3.0f));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 3.0));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 3.0L));
}

void compare_boolean_with_null()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), null));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), variable()));
}

void compare_boolean_with_boolean()
{
    TRIAL_PROTOCOL_TEST(!std::not_equal_to<variable>()(true, true));
    TRIAL_PROTOCOL_TEST(!std::not_equal_to<variable>()(variable(true), variable(true)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), variable(true)));
}

void compare_boolean_with_integer()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(2)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(2U)));
}

void compare_boolean_with_integer_literal()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 2));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 2U));
}

void compare_boolean_with_number()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(3.0L)));
}

void compare_boolean_with_number_literal()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 3.0f));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 3.0));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 3.0L));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_integer_literal();
    compare_null_with_number();
    compare_null_with_number_literal();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_integer_literal();
    compare_boolean_with_number();
    compare_boolean_with_number_literal();
}

} // namespace not_equal_to_suite

//-----------------------------------------------------------------------------
// std::less
//-----------------------------------------------------------------------------

namespace less_suite
{

void compare_null_with_null()
{
    TRIAL_PROTOCOL_TEST(!std::less<variable>()(variable(), null));
    TRIAL_PROTOCOL_TEST(!std::less<variable>()(variable(), variable()));
}

void compare_null_with_boolean()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), false));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(false)));
}

void compare_null_with_integer()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(2)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(2U)));
}

void compare_null_with_integer_literal()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 2));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 2U));
}

void compare_null_with_number()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(3.0L)));
}

void compare_null_with_number_literal()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 3.0f));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 3.0));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 3.0L));
}

void compare_boolean_with_null()
{
    TRIAL_PROTOCOL_TEST(!std::less<variable>()(variable(false), null));
    TRIAL_PROTOCOL_TEST(!std::less<variable>()(variable(false), variable()));
}

void compare_boolean_with_boolean()
{
    TRIAL_PROTOCOL_TEST(!std::less<variable>()(true, true));
    TRIAL_PROTOCOL_TEST(!std::less<variable>()(variable(true), variable(true)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), variable(true)));
}

void compare_boolean_with_integer()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(2)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(2U)));
}

void compare_boolean_with_integer_literal()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 2));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 2U));
}

void compare_boolean_with_number()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(3.0L)));
}

void compare_boolean_with_number_literal()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 3.0f));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 3.0));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 3.0L));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_integer_literal();
    compare_null_with_number();
    compare_null_with_number_literal();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_integer_literal();
    compare_boolean_with_number();
    compare_boolean_with_number_literal();
}

} // namespace less_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    equality_suite::run();
    relational_suite::run();

    operator_bool_suite::run();

    equal_to_suite::run();
    not_equal_to_suite::run();
    less_suite::run();

    return boost::report_errors();
}
