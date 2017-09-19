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
#include <trial/protocol/core/detail/lightweight_test.hpp>
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

void compare_null_equal_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(L""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(L"alpha"), true);
}

void compare_null_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != L"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != L"alpha", true);
}

void compare_null_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(u""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(u"alpha"), true);
}

void compare_null_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != u"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != u"alpha", true);
}

void compare_null_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == array::make({ null }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != array::make({ null }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != array::make({ 1, 2, 3 }), true);
}

void compare_null_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != map::make({ {"alpha", 1} }), true);
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

void compare_boolean_equal_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(L""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(L"alpha"), true);
}

void compare_boolean_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != L"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != L"alpha", true);
}

void compare_boolean_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(u""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(u"alpha"), true);
}

void compare_boolean_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != u"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != u"alpha", true);
}

void compare_boolean_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != array::make({ 1, 2, 3 }), true);
}

void compare_boolean_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != map::make({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != map::make({ {"alpha", 1} }), true);
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
    // signed - string
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
    // unsigned - string
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
    // signed - string literal
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
    // unsigned - string literal
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

void compare_integer_equal_wstring()
{
    // signed - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(L""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(L"alpha"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(L""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(L"alpha"), true);
    }
    // unsigned - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(L""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(L"alpha"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(L""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(L"alpha"), true);
    }
}

void compare_integer_equal_wstring_literal()
{
    // signed - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != L"alpha", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != L"alpha", true);
    }
    // unsigned - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != L"alpha", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != L"alpha", true);
    }
}

void compare_integer_equal_u16string()
{
    // signed - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(u"alpha"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(u"alpha"), true);
    }
    // unsigned - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(u"alpha"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(u"alpha"), true);
    }
}

void compare_integer_equal_u16string_literal()
{
    // signed - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != u"alpha", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != u"alpha", true);
    }
    // unsigned - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != u"alpha", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != u"alpha", true);
    }
}

void compare_integer_equal_array()
{
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != array::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != array::make({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make({ 1, 2, 3 }), true);
    }
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != array::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != array::make({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make({ 1, 2, 3 }), true);
    }
}

void compare_integer_equal_map()
{
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != map::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != map::make({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make({ {"alpha", 1} }), true);
    }
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != map::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != map::make({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make({ {"alpha", 1} }), true);
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
    // float - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != variable("alpha"), true);
    }
    // double - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable("alpha"), true);
    }
    // long double - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != variable("alpha"), true);
    }
}

void compare_number_equal_string_literal()
{
    // float - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != "alpha", true);
    }
    // double - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != "alpha", true);
    }
    // long double - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != "alpha", true);
    }
}

void compare_number_equal_wstring()
{
    // float - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != variable(L"alpha"), true);
    }
    // double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(L"alpha"), true);
    }
    // long double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != variable(L"alpha"), true);
    }
}

void compare_number_equal_wstring_literal()
{
    // float - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != L"alpha", true);
    }
    // double - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != L"alpha", true);
    }
    // long double - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != L"alpha", true);
    }
}

void compare_number_equal_u16string()
{
    // float - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != variable(u"alpha"), true);
    }
    // double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(u"alpha"), true);
    }
    // long double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != variable(u"alpha"), true);
    }
}

void compare_number_equal_u16string_literal()
{
    // float - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != u"alpha", true);
    }
    // double - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != u"alpha", true);
    }
    // long double - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != u"alpha", true);
    }
}

void compare_number_equal_array()
{
    {
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != array::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != array::make({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make({ 1, 2, 3 }), true);
    }
    {
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != array::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != array::make({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make({ 1, 2, 3 }), true);
    }
    {
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != array::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != array::make({ 1, 2, 3 }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == array::make({ 1, 2, 3 }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != array::make({ 1, 2, 3 }), true);
    }
}

void compare_number_equal_map()
{
    {
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != map::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != map::make({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make({ {"alpha", 1} }), true);
    }
    {
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != map::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != map::make({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make({ {"alpha", 1} }), true);
    }
    {
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != map::make(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make(), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != map::make({ {"alpha", 1} }), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) == map::make({ {"alpha", 1} }), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(big) != map::make({ {"alpha", 1} }), true);
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
    // string - signed
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
    // string - unsigned
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
    // string - signed
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
    // string - unsigned
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
    // string - float
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
    // string - double
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
    // string - long double
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
    // string - float
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
    // string - double
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
    // string - long double
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
    // string - string
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
    // string - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(L""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(L"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != variable(L"bravo"), true);
    }
    // string - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(u""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(u"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(u"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == variable(u"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != variable(u"bravo"), true);
    }
}

void compare_string_equal_string_literal()
{
    // string - string literal
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
    // string - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != L"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != L"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != L"bravo", true);
    }
    // string - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != u"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == u"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != u"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") == u"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") != u"bravo", true);
    }
}

void compare_string_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != array::make({ 1, 2, 3 }), true);
}

void compare_string_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("") == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("") != map::make({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != map::make({ {"alpha", 1} }), true);
}

void compare_wstring_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(), true);
}

void compare_wstring_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != null, true);
}

void compare_wstring_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(true), true);
}

void compare_wstring_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != true, true);
}

void compare_wstring_equal_integer()
{
    // wstring - signed
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(big), true);
    }
    // wstring - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(big), true);
    }
}

void compare_wstring_equal_integer_literal()
{
    // wstring - signed
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != big, true);
    }
    // wstring - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != big, true);
    }
}

void compare_wstring_equal_number()
{
    // wstring - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(big), true);
    }
    // wstring - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(big), true);
    }
    // wstring - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(big), true);
    }
}

void compare_wstring_equal_number_literal()
{
    // wstring - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != big, true);
    }
    // wstring - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != big, true);
    }
    // wstring - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != big, true);
    }
}

void compare_wstring_equal_string()
{
    // wstring - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable("bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable("bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable("bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable("bravo"), true);
    }
    // wstring - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(L""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(L"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(L"bravo"), false);
    }
    // wstring - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(u""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == variable(u"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != variable(u"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(u"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(u"bravo"), true);
    }
}

void compare_wstring_equal_string_literal()
{
    // wstring - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != "", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == "bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != "bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == "bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != "bravo", true);
    }
    // wstring - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != L"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != L"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == L"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != L"bravo", false);
    }
    // wstring - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != u"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == u"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != u"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == u"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != u"bravo", true);
    }
}

void compare_wstring_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != array::make({ 1, 2, 3 }), true);
}

void compare_wstring_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != map::make({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") != map::make({ {"alpha", 1} }), true);
}

void compare_u16string_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(), true);
}

void compare_u16string_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != null, true);
}

void compare_u16string_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(true), true);
}

void compare_u16string_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != true, true);
}

void compare_u16string_equal_integer()
{
    // u16string - signed
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(big), true);
    }
    // u16string - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(big), true);
    }
}

void compare_u16string_equal_integer_literal()
{
    // u16string - signed
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != big, true);
    }
    // u16string - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != big, true);
    }
}

void compare_u16string_equal_number()
{
    // u16string - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(big), true);
    }
    // u16string - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(big), true);
    }
    // u16string - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(big), true);
    }
}

void compare_u16string_equal_number_literal()
{
    // u16string - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != big, true);
    }
    // u16string - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != big, true);
    }
    // u16string - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != big, true);
    }
}

void compare_u16string_equal_string()
{
    // u16string - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable("bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable("bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == variable("bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != variable("bravo"), true);
    }
    // u16string - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(L""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(L"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != variable(L"bravo"), true);
    }
    // u16string - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(u""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == variable(u"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != variable(u"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == variable(u"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != variable(u"bravo"), false);
    }
}

void compare_u16string_equal_string_literal()
{
    // u16string - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != "", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == "bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != "bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == "alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != "alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == "bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != "bravo", true);
    }
    // u16string - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != L"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != L"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != L"bravo", true);
    }
    // u16string - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != u"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == u"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != u"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") == u"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") != u"bravo", false);
    }
}

void compare_u16string_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != array::make({ 1, 2, 3 }), true);
}

void compare_u16string_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != map::make({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") != map::make({ {"alpha", 1} }), true);
}

void compare_array_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(), true);
}

void compare_array_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != null, true);
}

void compare_array_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(true), true);
}

void compare_array_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != true, true);
}

void compare_array_equal_integer()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(big), true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(big), true);
    }
}

void compare_array_equal_integer_literal()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != big, true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != big, true);
    }
}

void compare_array_equal_number()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(big), true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(big), true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(big), true);
    }
}

void compare_array_equal_number_literal()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != big, true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != big, true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != big, true);
    }
}

void compare_array_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable("alpha"), true);
}

void compare_array_equal_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != "alpha", true);
}

void compare_array_equal_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(L"alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(L"alpha"), true);
}

void compare_array_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != L"alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != L"alpha", true);
}

void compare_array_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(u"alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(u"alpha"), true);
}

void compare_array_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != u"alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != u"alpha", true);
}

void compare_array_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != array::make({ 1, 2, 3 }), false);

    // Different sizes
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == array::make({ 1, 2, 3, 4 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != array::make({ 1, 2, 3, 4 }), true);

    // Different content
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3, 5 }) == array::make({ 1, 2, 3, 4 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3, 5 }) != array::make({ 1, 2, 3, 4 }), true);
}

void compare_array_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != map::make({ {"alpha", 1} }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != map::make({ {"alpha", 1} }), true);
}

void compare_map_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(), true);
}

void compare_map_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != null, true);
}

void compare_map_boolean_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {true, 1} }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {true, 1} }) != variable(), true);
}

void compare_map_null_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {null, 1} }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {null, 1} }) != variable(), true);
}

void compare_map_integer_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {2, 1} }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {2, 1} }) != variable(), true);
}

void compare_map_number_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {3.0, 1} }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {3.0, 1} }) != variable(), true);
}

void compare_map_array_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {array::make(), 1} }) == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {array::make(), 1} }) != variable(), true);
}

void compare_map_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(true), true);
}

void compare_map_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != true, true);
}

void compare_map_equal_integer()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(big), true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(big), true);
    }
}

void compare_map_equal_integer_literal()
{
    {
        const auto zero = 0;
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != big, true);
    }
    {
        const auto zero = 0U;
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != big, true);
    }
}

void compare_map_equal_number()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(big), true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(big), true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(big), true);
    }
}

void compare_map_equal_number_literal()
{
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != big, true);
    }
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != big, true);
    }
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make() != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != big, true);
    }
}

void compare_map_equal_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable("alpha"), true);
}

void compare_map_equal_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == "", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != "", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != "alpha", true);
}

void compare_map_equal_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(L"alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(L"alpha"), true);
}

void compare_map_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != L"alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != L"alpha", true);
}

void compare_map_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(u"alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != variable(u"alpha"), true);
}

void compare_map_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != u"alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != u"alpha", true);
}

void compare_map_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != array::make({ 1, 2, 3 }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != array::make({ 1, 2, 3 }), true);
}

void compare_map_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != map::make({ {"alpha", 1} }), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == map::make({ {"alpha", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != map::make({ {"alpha", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) == map::make({ {"alpha", 1}, {"bravo", 2} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {"alpha", 1} }) != map::make({ {"alpha", 1}, {"bravo", 2} }), true);
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
    compare_null_equal_wstring();
    compare_null_equal_wstring_literal();
    compare_null_equal_u16string();
    compare_null_equal_u16string_literal();
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
    compare_boolean_equal_wstring();
    compare_boolean_equal_wstring_literal();
    compare_boolean_equal_u16string();
    compare_boolean_equal_u16string_literal();
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
    compare_integer_equal_wstring();
    compare_integer_equal_wstring_literal();
    compare_integer_equal_u16string();
    compare_integer_equal_u16string_literal();
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
    compare_number_equal_wstring();
    compare_number_equal_wstring_literal();
    compare_number_equal_u16string();
    compare_number_equal_u16string_literal();
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

    compare_wstring_equal_null();
    compare_wstring_equal_null_literal();
    compare_wstring_equal_boolean();
    compare_wstring_equal_boolean_literal();
    compare_wstring_equal_integer();
    compare_wstring_equal_integer_literal();
    compare_wstring_equal_number();
    compare_wstring_equal_number_literal();
    compare_wstring_equal_string();
    compare_wstring_equal_string_literal();
    compare_wstring_equal_array();
    compare_wstring_equal_map();

    compare_u16string_equal_null();
    compare_u16string_equal_null_literal();
    compare_u16string_equal_boolean();
    compare_u16string_equal_boolean_literal();
    compare_u16string_equal_integer();
    compare_u16string_equal_integer_literal();
    compare_u16string_equal_number();
    compare_u16string_equal_number_literal();
    compare_u16string_equal_string();
    compare_u16string_equal_string_literal();
    compare_u16string_equal_array();
    compare_u16string_equal_map();

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
    compare_array_equal_wstring();
    compare_array_equal_wstring_literal();
    compare_array_equal_u16string();
    compare_array_equal_u16string_literal();
    compare_array_equal_array();
    compare_array_equal_map();

    compare_map_equal_null();
    compare_map_equal_null_literal();
    compare_map_null_equal_null();
    compare_map_boolean_equal_null();
    compare_map_integer_equal_null();
    compare_map_number_equal_null();
    compare_map_array_equal_null();
    compare_map_equal_boolean();
    compare_map_equal_boolean_literal();
    compare_map_equal_integer();
    compare_map_equal_integer_literal();
    compare_map_equal_number();
    compare_map_equal_number_literal();
    compare_map_equal_string();
    compare_map_equal_string_literal();
    compare_map_equal_wstring();
    compare_map_equal_wstring_literal();
    compare_map_equal_u16string();
    compare_map_equal_u16string_literal();
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

void compare_null_with_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(L""), false);
}

void compare_null_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(u""), false);
}

void compare_null_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= array::make(), false);
}

void compare_null_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= map::make(), false);
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

void compare_boolean_with_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(L"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(L"alpha"), false);
}

void compare_boolean_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(u"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(u"alpha"), false);
}

void compare_boolean_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= array::make(), false);
}

void compare_boolean_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= map::make(), false);
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
    // signed - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable("alpha"), false);
    }
    // unsigned - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable("alpha"), false);
    }
}

void compare_integer_with_wstring()
{
    // signed - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(L"alpha"), false);
    }
    // unsigned - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(L"alpha"), false);
    }
}

void compare_integer_with_u16string()
{
    // signed - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(u"alpha"), false);
    }
    // unsigned - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(u"alpha"), false);
    }
}

void compare_integer_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) >= array::make(), false);
}

void compare_integer_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(2) >= map::make(), false);
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
    // float - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable("alpha"), false);
    }
    // double - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable("alpha"), false);
    }
    // long double - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable("alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable("alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable("alpha"), false);
    }
}

void compare_number_with_wstring()
{
    // float - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(L"alpha"), false);
    }
    // double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(L"alpha"), false);
    }
    // long double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(L"alpha"), false);
    }
}

void compare_number_with_u16string()
{
    // float - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(u"alpha"), false);
    }
    // double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(u"alpha"), false);
    }
    // long double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(u"alpha"), false);
    }
}

void compare_number_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) >= array::make(), false);
}

void compare_number_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) >= map::make(), false);
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
    // string - signed
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
    // string - unsigned
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
    // string - float
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
    // string - double
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
    // string - long double
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

void compare_string_with_wstring()
{
    // string is always lesser than wstring
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(L"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(L"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") < variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") <= variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") > variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") >= variable(L"alpha"), false);
}

void compare_string_with_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= L"alpha", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= L"bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") < L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") <= L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") > L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") >= L"alpha", false);
}

void compare_string_with_u16string()
{
    // string is always lesser than u16string
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(u"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(u"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(u"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") >= variable(u"alpha"), false);
}

void compare_string_with_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= u"alpha", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > u"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= u"bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") < u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") <= u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") > u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("bravo") >= u"alpha", false);
}

void compare_string_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= array::make(), false);
}

void compare_string_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= map::make(), false);
}

void compare_wstring_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") >= variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(), true);
}

void compare_wstring_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") >= null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= null, true);
}

void compare_wstring_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(true), true);
}

void compare_wstring_with_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= true, true);
}

void compare_wstring_with_integer()
{
    // wstring - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(1), true);
    }
    // wstring - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(0U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(1U), true);
    }
}

void compare_wstring_with_number()
{
    // wstring - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(0.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(1.0f), true);
    }
    // wstring - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(0.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(1.0), true);
    }
    // wstring - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(0.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(1.0L), true);
    }
}

void compare_wstring_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable("bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable("bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable("alpha"), true);
}

void compare_wstring_with_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= "bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= "alpha", true);
}

void compare_wstring_with_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(L"alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(L"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(L"alpha"), true);
}

void compare_wstring_with_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= L"alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= L"bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= L"alpha", true);
}

void compare_wstring_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(u"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > variable(u"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= variable(u"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(u"alpha"), false);
}

void compare_wstring_with_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= u"alpha", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > u"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= u"bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= u"alpha", false);
}

void compare_wstring_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= array::make(), false);
}

void compare_wstring_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"alpha") >= map::make(), false);
}

void compare_u16string_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") >= variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(), true);
}

void compare_u16string_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") >= null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= null, true);
}

void compare_u16string_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(true), true);
}

void compare_u16string_with_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= true, true);
}

void compare_u16string_with_integer()
{
    // u16string - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(1), true);
    }
    // u16string - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(0U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(1U), true);
    }
}

void compare_u16string_with_number()
{
    // u16string - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(0.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(1.0f), true);
    }
    // u16string - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(0.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(1.0), true);
    }
    // u16string - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(0.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(1.0L), true);
    }
}

void compare_u16string_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable("alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable("bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable("bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") < variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") <= variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") > variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") >= variable("alpha"), true);
}

void compare_u16string_with_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= "bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") <= "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") > "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") >= "alpha", true);
}

void compare_u16string_with_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(L"alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(L"bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") < variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") <= variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") > variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") >= variable(L"alpha"), true);
}

void compare_u16string_with_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= L"alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= L"bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") < L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") <= L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") > L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") >= L"alpha", true);
}

void compare_u16string_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(u"alpha"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > variable(u"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= variable(u"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") < variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") <= variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") > variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") >= variable(u"alpha"), true);
}

void compare_u16string_with_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= u"alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > u"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= u"bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") < u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") <= u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") > u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"bravo") >= u"alpha", true);
}

void compare_u16string_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= array::make(), false);
}

void compare_u16string_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"alpha") >= map::make(), false);
}

void compare_array_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({1, 2}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({0, 1}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({0, 2}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({1, 1}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({1, 0}), false);

    // Different sizes
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({0, 1, 2}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({0, 2, 3}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({1, 2, 3}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({0, 1}) < array::make({1}), false);
}

void compare_map_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) >= null, true);
}

void compare_map_with_map_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{null, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) <= map::make({{null, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) > map::make({{null, 1}}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) >= map::make({{null, 1}}), true);
}

void compare_map_with_map_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{true, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) <= map::make({{true, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) > map::make({{true, 1}}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) >= map::make({{true, 1}}), true);
}

void compare_map_with_map_integer()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{2, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) <= map::make({{2, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) > map::make({{2, 1}}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) >= map::make({{2, 1}}), true);
}

void compare_map_with_map_number()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{3.0, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) <= map::make({{3.0, 1}}), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) > map::make({{3.0, 1}}), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) >= map::make({{3.0, 1}}), true);
}

void compare_map_with_map_string()
{
    // map string - map string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{"alpha", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"bravo", 1}}) < map::make({{"alpha", 1}}), false);
    }
    // map string - map wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{L"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{L"alpha", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{L"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"bravo", 1}}) < map::make({{L"alpha", 1}}), true);
    }
    // map string - map u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{u"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{u"alpha", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{u"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"bravo", 1}}) < map::make({{u"alpha", 1}}), true);
    }
    // map wstring - map string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{"bravo", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{"alpha", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{"alpha", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{"alpha", 1}}), false);
    }
    // map wstring - map wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{L"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{L"alpha", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{L"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{L"alpha", 1}}), false);
    }
    // map wstring - map u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{u"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{u"alpha", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"alpha", 1}}) < map::make({{u"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{u"alpha", 1}}), true);
    }
    // map u16string - map string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{"bravo", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{"alpha", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{"alpha", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"bravo", 1}}) < map::make({{"alpha", 1}}), false);
    }
    // map u16string - map wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{L"bravo", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{L"alpha", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{L"alpha", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"bravo", 1}}) < map::make({{L"alpha", 1}}), false);
    }
    // map u16string - map u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{u"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{u"alpha", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"alpha", 1}}) < map::make({{u"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"bravo", 1}}) < map::make({{u"alpha", 1}}), false);
    }
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
    compare_null_with_wstring();
    compare_null_with_u16string();
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
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
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
    compare_integer_with_wstring();
    compare_integer_with_u16string();
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
    compare_number_with_wstring();
    compare_number_with_u16string();
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
    compare_string_with_wstring();
    compare_string_with_wstring_literal();
    compare_string_with_u16string();
    compare_string_with_u16string_literal();
    compare_string_with_array();
    compare_string_with_map();

    compare_wstring_with_null();
    compare_wstring_with_null_literal();
    compare_wstring_with_boolean();
    compare_wstring_with_boolean_literal();
    compare_wstring_with_integer();
    compare_wstring_with_number();
    compare_wstring_with_string();
    compare_wstring_with_string_literal();
    compare_wstring_with_wstring();
    compare_wstring_with_wstring_literal();
    compare_wstring_with_u16string();
    compare_wstring_with_u16string_literal();
    compare_wstring_with_array();
    compare_wstring_with_map();

    compare_u16string_with_null();
    compare_u16string_with_null_literal();
    compare_u16string_with_boolean();
    compare_u16string_with_boolean_literal();
    compare_u16string_with_integer();
    compare_u16string_with_number();
    compare_u16string_with_string();
    compare_u16string_with_string_literal();
    compare_u16string_with_wstring();
    compare_u16string_with_wstring_literal();
    compare_u16string_with_u16string();
    compare_u16string_with_u16string_literal();
    compare_u16string_with_array();
    compare_u16string_with_map();

    // FIXME: More
    compare_array_with_array();

    compare_map_with_null();
    compare_map_with_map_null();
    compare_map_with_map_boolean();
    compare_map_with_map_integer();
    compare_map_with_map_number();
    compare_map_with_map_string();
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

    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 2));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 2U));
}

void compare_null_with_number()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(3.0)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(3.0L)));

    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 3.0f));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 3.0));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), 3.0L));
}

void compare_null_with_string()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable("alpha")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), "alpha"));
}

void compare_null_with_wstring()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(L"bravo")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), L"bravo"));
}

void compare_null_with_u16string()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(u"bravo")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), u"bravo"));
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

    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 2));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 2U));
}

void compare_boolean_with_number()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(3.0)));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(3.0L)));

    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 3.0f));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 3.0));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), 3.0L));
}

void compare_boolean_with_string()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable("alpha")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), "alpha"));
}

void compare_boolean_with_wstring()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(L"bravo")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), L"bravo"));
}

void compare_boolean_with_u16string()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(u"bravo")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), u"bravo"));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_number();
    compare_null_with_string();
    compare_null_with_wstring();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_number();
    compare_boolean_with_string();
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
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

    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 2));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 2U));
}

void compare_null_with_number()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(3.0L)));

    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 3.0f));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 3.0));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), 3.0L));
}

void compare_null_with_string()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), "alpha"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable("alpha")));
}

void compare_null_with_wstring()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), L"bravo"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(L"bravo")));
}

void compare_null_with_u16string()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), u"bravo"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(u"bravo")));
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

    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 2));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 2U));
}

void compare_boolean_with_number()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), variable(3.0L)));

    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 3.0f));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 3.0));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(true), 3.0L));
}

void compare_boolean_with_string()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), "alpha"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), variable("alpha")));
}

void compare_boolean_with_wstring()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), L"bravo"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), variable(L"bravo")));
}

void compare_boolean_with_u16string()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), u"bravo"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), variable(u"bravo")));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_number();
    compare_null_with_string();
    compare_null_with_wstring();
    compare_null_with_u16string();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_number();
    compare_boolean_with_string();
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
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

    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 2));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 2U));
}

void compare_null_with_number()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(3.0L)));

    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 3.0f));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 3.0));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), 3.0L));
}

void compare_null_with_string()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), "alpha"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable("alpha")));
}

void compare_null_with_wstring()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), L"bravo"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(L"bravo")));
}

void compare_null_with_u16string()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), u"bravo"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(u"bravo")));
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

    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 2));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 2U));
}

void compare_boolean_with_number()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(3.0f)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(3.0)));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), variable(3.0L)));

    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 3.0f));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 3.0));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(true), 3.0L));
}

void compare_boolean_with_string()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), "alpha"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), variable("alpha")));
}

void compare_boolean_with_wstring()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), L"bravo"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), variable(L"bravo")));
}

void compare_boolean_with_u16string()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), u"alpha"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), variable(u"alpha")));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_number();
    compare_null_with_string();
    compare_null_with_wstring();
    compare_null_with_u16string();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_number();
    compare_boolean_with_string();
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
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
