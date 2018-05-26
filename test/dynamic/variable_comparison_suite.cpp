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
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

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
    TRIAL_PROTOCOL_TEST_EQUAL(false == variable(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(true == variable(), false);
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

void compare_null_equal_real()
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

void compare_null_equal_real_literal()
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

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(L"bravo"), true);
}

void compare_null_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != L"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != L"bravo", true);
}

void compare_null_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(u""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(u"charlie"), true);
}

void compare_null_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != u"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != u"charlie", true);
}

void compare_null_equal_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(U""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != variable(U"delta"), true);
}

void compare_null_equal_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() == U"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != U"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable() == U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() != U"delta", true);
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

void compare_boolean_equal_real()
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

void compare_boolean_equal_real_literal()
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

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(L"bravo"), true);
}

void compare_boolean_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != L"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != L"bravo", true);
}

void compare_boolean_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(u""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(u"charlie"), true);
}

void compare_boolean_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != u"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != u"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != u"charlie", true);
}

void compare_boolean_equal_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(U""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(U""), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != variable(U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != variable(U"delta"), true);
}

void compare_boolean_equal_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == U"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != U"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == U"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != U"", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) == U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) != U"delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) == U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) != U"delta", true);
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

void compare_integer_equal_real()
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

void compare_integer_equal_real_literal()
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
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(L"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(L""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(L"bravo"), true);
    }
    // unsigned - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(L""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(L"bravo"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(L""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(L"bravo"), true);
    }
}

void compare_integer_equal_wstring_literal()
{
    // signed - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != L"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != L"bravo", true);
    }
    // unsigned - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != L"bravo", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != L"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != L"bravo", true);
    }
}

void compare_integer_equal_u16string()
{
    // signed - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(u"charlie"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(u"charlie"), true);
    }
    // unsigned - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(u"charlie"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(u""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(u"charlie"), true);
    }
}

void compare_integer_equal_u16string_literal()
{
    // signed - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != u"charlie", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != u"charlie", true);
    }
    // unsigned - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != u"charlie", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != u"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != u"charlie", true);
    }
}

void compare_integer_equal_u32string()
{
    // signed - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(U""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != variable(U"delta"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(U""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != variable(U"delta"), true);
    }
    // unsigned - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(U""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != variable(U"delta"), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(U""), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != variable(U"delta"), true);
    }
}

void compare_integer_equal_u32string_literal()
{
    // signed - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != U"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) != U"delta", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != U"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1) != U"delta", true);
    }
    // unsigned - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != U"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) != U"delta", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != U"", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1U) != U"delta", true);
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

void compare_real_equal_null()
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

void compare_real_equal_null_literal()
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

void compare_real_equal_boolean()
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

void compare_real_equal_boolean_literal()
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

void compare_real_equal_integer()
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

void compare_real_equal_integer_literal()
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

void compare_real_equal_real()
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

void compare_real_equal_real_literal()
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

void compare_real_equal_string()
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

void compare_real_equal_string_literal()
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

void compare_real_equal_wstring()
{
    // float - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != variable(L"bravo"), true);
    }
    // double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(L"bravo"), true);
    }
    // long double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != variable(L"bravo"), true);
    }
}

void compare_real_equal_wstring_literal()
{
    // float - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != L"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != L"bravo", true);
    }
    // double - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != L"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != L"bravo", true);
    }
    // long double - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != L"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != L"bravo", true);
    }
}

void compare_real_equal_u16string()
{
    // float - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != variable(u"charlie"), true);
    }
    // double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(u"charlie"), true);
    }
    // long double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != variable(u"charlie"), true);
    }
}

void compare_real_equal_u16string_literal()
{
    // float - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != u"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != u"charlie", true);
    }
    // double - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != u"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != u"charlie", true);
    }
    // long double - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != u"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != u"charlie", true);
    }
}

void compare_real_equal_u32string()
{
    // float - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != variable(U"delta"), true);
    }
    // double - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != variable(U"delta"), true);
    }
    // long double - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != variable(U"delta"), true);
    }
}

void compare_real_equal_u32string_literal()
{
    // float - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) != U"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0f) != U"delta", true);
    }
    // double - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) != U"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0) != U"delta", true);
    }
    // long double - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) != U"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(1.0L) != U"delta", true);
    }
}

void compare_real_equal_array()
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

void compare_real_equal_map()
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

void compare_string_equal_real()
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

void compare_string_equal_real_literal()
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
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable("zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable("zulu"), true);
    }
    // string - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(L""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(L"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(L"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(L"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(L"zulu"), true);
    }
    // string - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(u""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(u"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(u"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(u"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(u"zulu"), true);
    }
    // string - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == variable(U"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != variable(U"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(U""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(U"alpha"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(U"alpha"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == variable(U"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != variable(U"zulu"), true);
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
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == "zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != "zulu", true);
    }
    // string - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != L"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == L"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != L"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == L"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != L"zulu", true);
    }
    // string - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != u"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == u"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != u"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == u"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != u"zulu", true);
    }
    // string - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") == U"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("") != U"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != U"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == U"alpha", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != U"alpha", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") == U"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") != U"zulu", true);
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
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != null, true);
}

void compare_wstring_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(true), true);
}

void compare_wstring_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != true, true);
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

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(big), true);
    }
    // wstring - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(big), true);
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

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != big, true);
    }
    // wstring - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != big, true);
    }
}

void compare_wstring_equal_real()
{
    // wstring - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(big), true);
    }
    // wstring - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(big), true);
    }
    // wstring - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(big), true);
    }
}

void compare_wstring_equal_real_literal()
{
    // wstring - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != big, true);
    }
    // wstring - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != big, true);
    }
    // wstring - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != big, true);
    }
}

void compare_wstring_equal_string()
{
    // wstring - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable("bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable("bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable("bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable("bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable("zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable("zulu"), true);
    }
    // wstring - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(L""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(L"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(L"zulu"), true);
    }
    // wstring - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(u"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(u"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(u""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(u"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(u"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(u"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(u"zulu"), true);
    }
    // wstring - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == variable(U"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != variable(U"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(U""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(U"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(U"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == variable(U"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != variable(U"zulu"), true);
    }
}

void compare_wstring_equal_string_literal()
{
    // wstring - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == "bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != "bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != "", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == "bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != "bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == "zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != "zulu", true);
    }
    // wstring - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != L"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != L"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == L"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != L"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == L"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != L"zulu", true);
    }
    // wstring - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == u"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != u"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != u"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == u"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != u"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == u"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != u"zulu", true);
    }
    // wstring - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == U"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != U"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != U"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == U"bravo", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != U"bravo", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == U"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != U"zulu", true);
    }
}

void compare_wstring_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != array::make({ 1, 2, 3 }), true);
}

void compare_wstring_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") == map::make({ {"bravo", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") != map::make({ {"bravo", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") == map::make({ {"bravo", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") != map::make({ {"bravo", 1} }), true);
}

void compare_u16string_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(), true);
}

void compare_u16string_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != null, true);
}

void compare_u16string_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(true), true);
}

void compare_u16string_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != true, true);
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

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(big), true);
    }
    // u16string - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(big), true);
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

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != big, true);
    }
    // u16string - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != big, true);
    }
}

void compare_u16string_equal_real()
{
    // u16string - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(big), true);
    }
    // u16string - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(big), true);
    }
    // u16string - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(big), true);
    }
}

void compare_u16string_equal_real_literal()
{
    // u16string - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != big, true);
    }
    // u16string - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != big, true);
    }
    // u16string - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != big, true);
    }
}

void compare_u16string_equal_string()
{
    // u16string - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable("charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable("charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable("charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable("charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable("zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable("zulu"), true);
    }
    // u16string - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(L"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(L"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(L""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(L"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(L"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(L"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(L"zulu"), true);
    }
    // u16string - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(u""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(u"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(u"zulu"), true);
    }
    // u16string - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == variable(U"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != variable(U"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(U""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(U"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(U"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == variable(U"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != variable(U"zulu"), true);
    }
}

void compare_u16string_equal_string_literal()
{
    // u16string - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == "charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != "charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != "", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == "charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != "charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == "zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != "zulu", true);
    }
    // u16string - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == L"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != L"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != L"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == L"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != L"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == L"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != L"zulu", true);
    }
    // u16string - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != u"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != u"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == u"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != u"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == u"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != u"zulu", true);
    }
    // u16string - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == U"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != U"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != U"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == U"charlie", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != U"charlie", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == U"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != U"zulu", true);
    }
}

void compare_u16string_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != array::make({ 1, 2, 3 }), true);
}

void compare_u16string_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") == map::make({ {"charlie", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") != map::make({ {"charlie", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") == map::make({ {"charlie", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") != map::make({ {"charlie", 1} }), true);
}

void compare_u32string_equal_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(), true);
}

void compare_u32string_equal_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != null, true);
}

void compare_u32string_equal_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(true), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(true), true);
}

void compare_u32string_equal_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != true, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != true, true);
}

void compare_u32string_equal_integer()
{
    // u32string - signed
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(big), true);
    }
    // u32string - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(big), true);
    }
}

void compare_u32string_equal_integer_literal()
{
    // u32string - signed
    {
        const auto big = std::numeric_limits<signed int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == 0, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != 0, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != big, true);
    }
    // u32string - unsigned
    {
        const auto big = std::numeric_limits<unsigned int>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == 0U, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != 0U, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != big, true);
    }
}

void compare_u32string_equal_real()
{
    // u32string - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(big), true);
    }
    // u32string - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(big), true);
    }
    // u32string - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(big), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(zero), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(zero), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(big), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(big), true);
    }
}

void compare_u32string_equal_real_literal()
{
    // u32string - float
    {
        const auto zero = 0.0f;
        const auto big = std::numeric_limits<float>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != big, true);
    }
    // u32string - double
    {
        const auto zero = 0.0;
        const auto big = std::numeric_limits<double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != big, true);
    }
    // u32string - long double
    {
        const auto zero = 0.0L;
        const auto big = std::numeric_limits<long double>::max();

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != big, true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == zero, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != zero, true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == big, false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != big, true);
    }
}

void compare_u32string_equal_string()
{
    // u32string - string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable("delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable("delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable("delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable("delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable("zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable("zulu"), true);
    }
    // u32string - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(L"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(L"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(L""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(L""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(L"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(L"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(L"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(L"zulu"), true);
    }
    // u32string - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(u"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(u"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(u""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(u""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(u"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(u"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(u"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(u"zulu"), true);
    }
    // u32string - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(U""), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(U""), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == variable(U"zulu"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != variable(U"zulu"), true);
    }
}

void compare_u32string_equal_string_literal()
{
    // u32string - string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == "delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != "delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == "", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != "", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == "delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != "delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == "zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != "zulu", true);
    }
    // u32string - wstring literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == L"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != L"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == L"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != L"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == L"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != L"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == L"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != L"zulu", true);
    }
    // u32string - u16string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == u"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != u"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == u"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != u"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == u"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != u"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == u"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != u"zulu", true);
    }
    // u32string - u32string literal
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != U"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == U"", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != U"", true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == U"delta", true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != U"delta", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == U"zulu", false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != U"zulu", true);
    }
}

void compare_u32string_equal_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != array::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != array::make({ 1, 2, 3 }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == array::make({ 1, 2, 3 }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != array::make({ 1, 2, 3 }), true);
}

void compare_u32string_equal_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != map::make(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") == map::make({ {"delta", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") != map::make({ {"delta", 1} }), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") == map::make({ {"delta", 1} }), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") != map::make({ {"delta", 1} }), true);
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

void compare_array_equal_real()
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

void compare_array_equal_real_literal()
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
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(L"bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(L"bravo"), true);
}

void compare_array_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != L"bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != L"bravo", true);
}

void compare_array_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(u"charlie"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(u"charlie"), true);
}

void compare_array_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != u"charlie", true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != u"charlie", true);
}

void compare_array_equal_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(U""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != variable(U"delta"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(U""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != variable(U"delta"), true);
}

void compare_array_equal_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == U"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != U"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() == U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make() != U"delta", true);

    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == U"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != U"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) == U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(array::make({ 1, 2, 3 }) != U"delta", true);
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

void compare_map_real_equal_null()
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

void compare_map_equal_real()
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

void compare_map_equal_real_literal()
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
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(L"bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) == variable(L""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) != variable(L""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) == variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) != variable(L"bravo"), true);
}

void compare_map_equal_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != L"bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) == L"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) != L"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) == L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {L"bravo", 1} }) != L"bravo", true);
}

void compare_map_equal_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(u"charlie"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) == variable(u""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) != variable(u""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) == variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) != variable(u"charlie"), true);
}

void compare_map_equal_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != u"charlie", true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) == u"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) != u"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) == u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {u"charlie", 1} }) != u"charlie", true);
}

void compare_map_equal_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(U""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != variable(U"delta"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) == variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) != variable(U""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) == variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) != variable(U"delta"), true);
}

void compare_map_equal_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == U"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != U"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() == U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make() != U"delta", true);

    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) == U"", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) != U"", true);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) == U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(map::make({ {U"delta", 1} }) != U"delta", true);
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
    compare_null_equal_real();
    compare_null_equal_real_literal();
    compare_null_equal_string();
    compare_null_equal_string_literal();
    compare_null_equal_wstring();
    compare_null_equal_wstring_literal();
    compare_null_equal_u16string();
    compare_null_equal_u16string_literal();
    compare_null_equal_u32string();
    compare_null_equal_u32string_literal();
    compare_null_equal_array();
    compare_null_equal_map();

    compare_boolean_equal_null();
    compare_boolean_equal_null_literal();
    compare_boolean_equal_boolean();
    compare_boolean_equal_boolean_literal();
    compare_boolean_equal_integer();
    compare_boolean_equal_integer_literal();
    compare_boolean_equal_real();
    compare_boolean_equal_real_literal();
    compare_boolean_equal_string();
    compare_boolean_equal_string_literal();
    compare_boolean_equal_wstring();
    compare_boolean_equal_wstring_literal();
    compare_boolean_equal_u16string();
    compare_boolean_equal_u16string_literal();
    compare_boolean_equal_u32string();
    compare_boolean_equal_u32string_literal();
    compare_boolean_equal_array();
    compare_boolean_equal_map();

    compare_integer_equal_null();
    compare_integer_equal_null_literal();
    compare_integer_equal_boolean();
    compare_integer_equal_boolean_literal();
    compare_integer_equal_integer();
    compare_integer_equal_integer_literal();
    compare_integer_equal_real();
    compare_integer_equal_real_literal();
    compare_integer_equal_string();
    compare_integer_equal_string_literal();
    compare_integer_equal_wstring();
    compare_integer_equal_wstring_literal();
    compare_integer_equal_u16string();
    compare_integer_equal_u16string_literal();
    compare_integer_equal_u32string();
    compare_integer_equal_u32string_literal();
    compare_integer_equal_array();
    compare_integer_equal_map();

    compare_real_equal_null();
    compare_real_equal_null_literal();
    compare_real_equal_boolean();
    compare_real_equal_boolean_literal();
    compare_real_equal_integer();
    compare_real_equal_integer_literal();
    compare_real_equal_real();
    compare_real_equal_real_literal();
    compare_real_equal_string();
    compare_real_equal_string_literal();
    compare_real_equal_wstring();
    compare_real_equal_wstring_literal();
    compare_real_equal_u16string();
    compare_real_equal_u16string_literal();
    compare_real_equal_u32string();
    compare_real_equal_u32string_literal();
    compare_real_equal_array();
    compare_real_equal_map();

    compare_string_equal_null();
    compare_string_equal_null_literal();
    compare_string_equal_boolean();
    compare_string_equal_boolean_literal();
    compare_string_equal_integer();
    compare_string_equal_integer_literal();
    compare_string_equal_real();
    compare_string_equal_real_literal();
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
    compare_wstring_equal_real();
    compare_wstring_equal_real_literal();
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
    compare_u16string_equal_real();
    compare_u16string_equal_real_literal();
    compare_u16string_equal_string();
    compare_u16string_equal_string_literal();
    compare_u16string_equal_array();
    compare_u16string_equal_map();

    compare_u32string_equal_null();
    compare_u32string_equal_null_literal();
    compare_u32string_equal_boolean();
    compare_u32string_equal_boolean_literal();
    compare_u32string_equal_integer();
    compare_u32string_equal_integer_literal();
    compare_u32string_equal_real();
    compare_u32string_equal_real_literal();
    compare_u32string_equal_string();
    compare_u32string_equal_string_literal();
    compare_u32string_equal_array();
    compare_u32string_equal_map();

    compare_array_equal_null();
    compare_array_equal_null_literal();
    compare_array_equal_boolean();
    compare_array_equal_boolean_literal();
    compare_array_equal_integer();
    compare_array_equal_integer_literal();
    compare_array_equal_real();
    compare_array_equal_real_literal();
    compare_array_equal_string();
    compare_array_equal_string_literal();
    compare_array_equal_wstring();
    compare_array_equal_wstring_literal();
    compare_array_equal_u16string();
    compare_array_equal_u16string_literal();
    compare_array_equal_u32string();
    compare_array_equal_u32string_literal();
    compare_array_equal_array();
    compare_array_equal_map();

    compare_map_equal_null();
    compare_map_equal_null_literal();
    compare_map_null_equal_null();
    compare_map_boolean_equal_null();
    compare_map_integer_equal_null();
    compare_map_real_equal_null();
    compare_map_array_equal_null();
    compare_map_equal_boolean();
    compare_map_equal_boolean_literal();
    compare_map_equal_integer();
    compare_map_equal_integer_literal();
    compare_map_equal_real();
    compare_map_equal_real_literal();
    compare_map_equal_string();
    compare_map_equal_string_literal();
    compare_map_equal_wstring();
    compare_map_equal_wstring_literal();
    compare_map_equal_u16string();
    compare_map_equal_u16string_literal();
    compare_map_equal_u32string();
    compare_map_equal_u32string_literal();
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

void compare_null_with_real()
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

void compare_null_with_real_literal()
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

void compare_null_with_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable() < variable(U""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() <= variable(U""), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() > variable(U""), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable() >= variable(U""), false);
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

void compare_boolean_with_real()
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

void compare_boolean_with_real_literal()
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
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(L"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(L"bravo"), false);
}

void compare_boolean_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(u"charlie"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(u"charlie"), false);
}

void compare_boolean_with_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) < variable(U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) <= variable(U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) > variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(false) >= variable(U"delta"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) < variable(U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) <= variable(U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) > variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(true) >= variable(U"delta"), false);
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

void compare_integer_with_real()
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

void compare_integer_with_real_literal()
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
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(L"bravo"), false);
    }
    // unsigned - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(L"bravo"), false);
    }
}

void compare_integer_with_u16string()
{
    // signed - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(u"charlie"), false);
    }
    // unsigned - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(u"charlie"), false);
    }
}

void compare_integer_with_u32string()
{
    // signed - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) < variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) <= variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) > variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0) >= variable(U"delta"), false);
    }
    // unsigned - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) < variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) <= variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) > variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0U) >= variable(U"delta"), false);
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

void compare_real_with_null()
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

void compare_real_with_null_literal()
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

void compare_real_with_boolean()
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

void compare_real_with_boolean_literal()
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

void compare_real_with_integer()
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

void compare_real_with_integer_literal()
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

void compare_real_with_real()
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

void compare_real_with_real_literal()
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

void compare_real_with_string()
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

void compare_real_with_wstring()
{
    // float - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(L"bravo"), false);
    }
    // double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(L"bravo"), false);
    }
    // long double - wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(L"bravo"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(L"bravo"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(L"bravo"), false);
    }
}

void compare_real_with_u16string()
{
    // float - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(u"charlie"), false);
    }
    // double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(u"charlie"), false);
    }
    // long double - u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(u"charlie"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(u"charlie"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(u"charlie"), false);
    }
}

void compare_real_with_u32string()
{
    // float - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) < variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) <= variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) > variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0f) >= variable(U"delta"), false);
    }
    // double - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) < variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) <= variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) > variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0) >= variable(U"delta"), false);
    }
    // long double - u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) < variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) <= variable(U"delta"), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) > variable(U"delta"), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(0.0L) >= variable(U"delta"), false);
    }
}

void compare_real_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(3.0) >= array::make(), false);
}

void compare_real_with_map()
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

void compare_string_with_real()
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

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable("zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable("zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable("zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable("zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= variable("alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > variable("alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= variable("alpha"), true);
}

void compare_string_with_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= "alpha", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < "zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= "zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > "zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= "zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= "alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > "alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= "alpha", true);
}

void compare_string_with_wstring()
{
    // string is always lesser than wstring
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(L"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(L"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(L"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(L"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(L"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= variable(L"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > variable(L"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= variable(L"alpha"), false);
}

void compare_string_with_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= L"alpha", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < L"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= L"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > L"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= L"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= L"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > L"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= L"alpha", false);
}

void compare_string_with_u16string()
{
    // string is always lesser than u16string
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(u"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(u"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(u"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(u"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(u"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= variable(u"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > variable(u"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= variable(u"alpha"), false);
}

void compare_string_with_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= u"alpha", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < u"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= u"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > u"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= u"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= u"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > u"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= u"alpha", false);
}

void compare_string_with_u32string()
{
    // string is always lesser than u32string
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(U"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(U"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(U"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(U"alpha"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > variable(U"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= variable(U"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < variable(U"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= variable(U"alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > variable(U"alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= variable(U"alpha"), false);
}

void compare_string_with_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < U"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= U"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > U"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= U"alpha", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") < U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") <= U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") > U"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("alpha") >= U"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") < U"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") <= U"alpha", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") > U"alpha", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable("zulu") >= U"alpha", false);
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

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(), true);
}

void compare_wstring_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"") >= null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= null, true);
}

void compare_wstring_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(true), true);
}

void compare_wstring_with_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= true, true);
}

void compare_wstring_with_integer()
{
    // wstring - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(1), true);
    }
    // wstring - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(0U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(1U), true);
    }
}

void compare_wstring_with_real()
{
    // wstring - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(0.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(1.0f), true);
    }
    // wstring - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(0.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(1.0), true);
    }
    // wstring - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(0.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(1.0L), true);
    }
}

void compare_wstring_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable("bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable("bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable("zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable("zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable("zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable("zulu"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= variable("bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > variable("bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= variable("bravo"), true);
}

void compare_wstring_with_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= "bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < "zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= "zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > "zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= "zulu", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= "bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > "bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= "bravo", true);
}

void compare_wstring_with_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(L"bravo"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(L"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(L"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(L"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(L"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= variable(L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > variable(L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= variable(L"bravo"), true);
}

void compare_wstring_with_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= L"bravo", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < L"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= L"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > L"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= L"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= L"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > L"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= L"bravo", true);
}

void compare_wstring_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(u"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(u"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(u"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(u"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(u"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(u"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= variable(u"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > variable(u"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= variable(u"bravo"), false);
}

void compare_wstring_with_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > u"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= u"bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < u"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= u"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > u"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= u"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= u"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > u"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= u"bravo", false);
}

void compare_wstring_with_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(U"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(U"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(U"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(U"bravo"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > variable(U"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= variable(U"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < variable(U"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= variable(U"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > variable(U"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= variable(U"bravo"), false);
}

void compare_wstring_with_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < U"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= U"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > U"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= U"bravo", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > U"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= U"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") < U"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") <= U"bravo", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") > U"bravo", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"zulu") >= U"bravo", false);
}

void compare_wstring_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= array::make(), false);
}

void compare_wstring_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(L"bravo") >= map::make(), false);
}

void compare_u16string_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") >= variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(), true);
}

void compare_u16string_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"") >= null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= null, true);
}

void compare_u16string_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(true), true);
}

void compare_u16string_with_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= true, true);
}

void compare_u16string_with_integer()
{
    // u16string - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(1), true);
    }
    // u16string - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(0U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(1U), true);
    }
}

void compare_u16string_with_real()
{
    // u16string - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(0.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(1.0f), true);
    }
    // u16string - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(0.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(1.0), true);
    }
    // u16string - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(0.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(1.0L), true);
    }
}

void compare_u16string_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable("charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable("charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable("charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable("charlie"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable("zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable("zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable("zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable("zulu"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < variable("charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= variable("charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > variable("charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= variable("charlie"), true);
}

void compare_u16string_with_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < "charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= "charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > "charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= "charlie", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < "zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= "zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > "zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= "zulu", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < "charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= "charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > "charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= "charlie", true);
}

void compare_u16string_with_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(L"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(L"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(L"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(L"charlie"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(L"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(L"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(L"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(L"zulu"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < variable(L"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= variable(L"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > variable(L"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= variable(L"charlie"), true);
}

void compare_u16string_with_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < L"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= L"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > L"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= L"charlie", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < L"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= L"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > L"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= L"zulu", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < L"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= L"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > L"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= L"charlie", true);
}

void compare_u16string_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(u"charlie"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(u"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(u"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(u"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(u"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= variable(u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > variable(u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= variable(u"charlie"), true);
}

void compare_u16string_with_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= u"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= u"charlie", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < u"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= u"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > u"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= u"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= u"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > u"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= u"charlie", true);
}

void compare_u16string_with_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(U"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(U"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(U"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(U"charlie"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > variable(U"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= variable(U"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < variable(U"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= variable(U"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > variable(U"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= variable(U"charlie"), false);
}

void compare_u16string_with_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < U"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= U"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > U"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= U"charlie", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > U"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= U"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < U"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= U"charlie", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > U"charlie", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= U"charlie", false);
}

void compare_u16string_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= array::make(), false);
}

void compare_u16string_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"charlie") >= map::make(), false);
}

void compare_u32string_with_null()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") >= variable(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(), true);
}

void compare_u32string_with_null_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"") >= null, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= null, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > null, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= null, true);
}

void compare_u32string_with_boolean()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(false), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(false), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(true), true);
}

void compare_u32string_with_boolean_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= false, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > false, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= false, true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= true, false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > true, true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= true, true);
}

void compare_u32string_with_integer()
{
    // u32string - signed
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(1), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(1), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(1), true);
    }
    // u32string - unsigned
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(0U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(0U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(0U), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(1U), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(1U), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(1U), true);
    }
}

void compare_u32string_with_real()
{
    // u32string - float
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(0.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(0.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(0.0f), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(1.0f), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(1.0f), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(1.0f), true);
    }
    // u32string - double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(0.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(0.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(0.0), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(1.0), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(1.0), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(1.0), true);
    }
    // u32string - long double
    {
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(0.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(0.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(0.0L), true);

        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(1.0L), false);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(1.0L), true);
        TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(1.0L), true);
    }
}

void compare_u32string_with_string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable("delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable("delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable("delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable("delta"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable("zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable("zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable("zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable("zulu"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < variable("delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= variable("delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > variable("delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= variable("delta"), true);
}

void compare_u32string_with_string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < "delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= "delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > "delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= "delta", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < "zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= "zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > "zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= "zulu", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < "delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= "delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > "delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= "delta", true);
}

void compare_u32string_with_wstring()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(L"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(L"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(L"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(L"delta"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(L"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(L"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(L"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(L"zulu"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < variable(L"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= variable(L"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > variable(L"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= variable(L"delta"), true);
}

void compare_u32string_with_wstring_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < L"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= L"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > L"delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= L"delta", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < L"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= L"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > L"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= L"zulu", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < L"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= L"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > L"delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= L"delta", true);
}

void compare_u32string_with_u16string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(u"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(u"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(u"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(u"delta"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(u"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(u"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(u"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(u"zulu"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < variable(u"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= variable(u"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > variable(u"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= variable(u"delta"), true);
}

void compare_u32string_with_u16string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < u"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= u"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > u"delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= u"delta", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < u"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= u"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > u"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= u"zulu", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") < u"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") <= u"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") > u"delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(u"zulu") >= u"delta", true);
}

void compare_u32string_with_u32string()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(U"delta"), true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= variable(U"zulu"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > variable(U"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= variable(U"zulu"), false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") < variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") <= variable(U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") > variable(U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") >= variable(U"delta"), true);
}

void compare_u32string_with_u32string_literal()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= U"delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= U"delta", true);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= U"zulu", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > U"zulu", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= U"zulu", false);

    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") < U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") <= U"delta", false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") > U"delta", true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"zulu") >= U"delta", true);
}

void compare_u32string_with_array()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= array::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > array::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= array::make(), false);
}

void compare_u32string_with_map()
{
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") < map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") <= map::make(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") > map::make(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(variable(U"delta") >= map::make(), false);
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

void compare_map_with_map_real()
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
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{"alpha", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"zulu", 1}}) < map::make({{"alpha", 1}}), false);
    }
    // map string - map wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{L"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{L"alpha", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{L"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"zulu", 1}}) < map::make({{L"alpha", 1}}), true);
    }
    // map string - map u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{u"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{u"alpha", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{u"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"zulu", 1}}) < map::make({{u"alpha", 1}}), true);
    }
    // map string - map u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{U"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{U"alpha", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"alpha", 1}}) < map::make({{U"alpha", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{"zulu", 1}}) < map::make({{U"alpha", 1}}), true);
    }
}

void compare_map_with_map_wstring()
{
    // map wstring - map string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{"zulu", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{"bravo", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{"bravo", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"zulu", 1}}) < map::make({{"bravo", 1}}), false);
    }
    // map wstring - map wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{L"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{L"bravo", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{L"bravo", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"zulu", 1}}) < map::make({{L"bravo", 1}}), false);
    }
    // map wstring - map u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{u"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{u"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{u"bravo", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"zulu", 1}}) < map::make({{u"bravo", 1}}), true);
    }
    // map wstring - map u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{U"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{U"bravo", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"bravo", 1}}) < map::make({{U"bravo", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{L"zulu", 1}}) < map::make({{U"bravo", 1}}), true);
    }
}

void compare_map_with_map_u16string()
{
    // map u16string - map string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{"zulu", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{"charlie", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{"charlie", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"zulu", 1}}) < map::make({{"charlie", 1}}), false);
    }
    // map u16string - map wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{L"zulu", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{L"charlie", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{L"charlie", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"zulu", 1}}) < map::make({{L"charlie", 1}}), false);
    }
    // map u16string - map u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{u"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{u"charlie", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{u"charlie", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"zulu", 1}}) < map::make({{u"charlie", 1}}), false);
    }
    // map u16string - map u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{U"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{U"charlie", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"charlie", 1}}) < map::make({{U"charlie", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{u"zulu", 1}}) < map::make({{U"charlie", 1}}), true);
    }
}

void compare_map_with_map_u32string()
{
    // map u32string - map string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{"zulu", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{"delta", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{"delta", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"zulu", 1}}) < map::make({{"delta", 1}}), false);
    }
    // map u32string - map wstring
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{L"zulu", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{L"delta", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{L"delta", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"zulu", 1}}) < map::make({{L"delta", 1}}), false);
    }
    // map u32string - map u16string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{u"zulu", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{u"delta", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{u"delta", 2}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"zulu", 1}}) < map::make({{u"delta", 1}}), false);
    }
    // map u32string - map u32string
    {
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{U"zulu", 1}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{U"delta", 1}}), false);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"delta", 1}}) < map::make({{U"delta", 2}}), true);
        TRIAL_PROTOCOL_TEST_EQUAL(map::make({{U"zulu", 1}}) < map::make({{U"delta", 1}}), false);
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
    compare_null_with_real();
    compare_null_with_real_literal();
    compare_null_with_string();
    compare_null_with_wstring();
    compare_null_with_u16string();
    compare_null_with_u32string();
    compare_null_with_array();
    compare_null_with_map();

    compare_boolean_with_null();
    compare_boolean_with_null_literal();
    compare_boolean_with_boolean();
    compare_boolean_with_boolean_literal();
    compare_boolean_with_integer();
    compare_boolean_with_integer_literal();
    compare_boolean_with_real();
    compare_boolean_with_real_literal();
    compare_boolean_with_string();
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
    compare_boolean_with_u32string();
    compare_boolean_with_array();
    compare_boolean_with_map();

    compare_integer_with_null();
    compare_integer_with_null_literal();
    compare_integer_with_boolean();
    compare_integer_with_boolean_literal();
    compare_integer_with_integer();
    compare_integer_with_integer_literal();
    compare_integer_with_real();
    compare_integer_with_real_literal();
    compare_integer_with_string();
    compare_integer_with_wstring();
    compare_integer_with_u16string();
    compare_integer_with_u32string();
    compare_integer_with_array();
    compare_integer_with_map();

    // FIXME: Real with NaN etc.
    compare_real_with_null();
    compare_real_with_null_literal();
    compare_real_with_boolean();
    compare_real_with_boolean_literal();
    compare_real_with_integer();
    compare_real_with_integer_literal();
    compare_real_with_real();
    compare_real_with_real_literal();
    compare_real_with_string();
    compare_real_with_wstring();
    compare_real_with_u16string();
    compare_real_with_u32string();
    compare_real_with_array();
    compare_real_with_map();

    compare_string_with_null();
    compare_string_with_null_literal();
    compare_string_with_boolean();
    compare_string_with_boolean_literal();
    compare_string_with_integer();
    compare_string_with_real();
    compare_string_with_string();
    compare_string_with_string_literal();
    compare_string_with_wstring();
    compare_string_with_wstring_literal();
    compare_string_with_u16string();
    compare_string_with_u16string_literal();
    compare_string_with_u32string();
    compare_string_with_u32string_literal();
    compare_string_with_array();
    compare_string_with_map();

    compare_wstring_with_null();
    compare_wstring_with_null_literal();
    compare_wstring_with_boolean();
    compare_wstring_with_boolean_literal();
    compare_wstring_with_integer();
    compare_wstring_with_real();
    compare_wstring_with_string();
    compare_wstring_with_string_literal();
    compare_wstring_with_wstring();
    compare_wstring_with_wstring_literal();
    compare_wstring_with_u16string();
    compare_wstring_with_u16string_literal();
    compare_wstring_with_u32string();
    compare_wstring_with_u32string_literal();
    compare_wstring_with_array();
    compare_wstring_with_map();

    compare_u16string_with_null();
    compare_u16string_with_null_literal();
    compare_u16string_with_boolean();
    compare_u16string_with_boolean_literal();
    compare_u16string_with_integer();
    compare_u16string_with_real();
    compare_u16string_with_string();
    compare_u16string_with_string_literal();
    compare_u16string_with_wstring();
    compare_u16string_with_wstring_literal();
    compare_u16string_with_u16string();
    compare_u16string_with_u16string_literal();
    compare_u16string_with_u32string();
    compare_u16string_with_u32string_literal();
    compare_u16string_with_array();
    compare_u16string_with_map();

    compare_u32string_with_null();
    compare_u32string_with_null_literal();
    compare_u32string_with_boolean();
    compare_u32string_with_boolean_literal();
    compare_u32string_with_integer();
    compare_u32string_with_real();
    compare_u32string_with_string();
    compare_u32string_with_string_literal();
    compare_u32string_with_wstring();
    compare_u32string_with_wstring_literal();
    compare_u32string_with_u16string();
    compare_u32string_with_u16string_literal();
    compare_u32string_with_u32string();
    compare_u32string_with_u32string_literal();
    compare_u32string_with_array();
    compare_u32string_with_map();

    // FIXME: More
    compare_array_with_array();

    compare_map_with_null();
    compare_map_with_map_null();
    compare_map_with_map_boolean();
    compare_map_with_map_integer();
    compare_map_with_map_real();
    compare_map_with_map_string();
    compare_map_with_map_wstring();
    compare_map_with_map_u16string();
    compare_map_with_map_u32string();
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

void test_real()
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
    test_real();
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

void compare_null_with_real()
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
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(u"charlie")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), u"charlie"));
}

void compare_null_with_u32string()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), variable(U"delta")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(), U"delta"));
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

void compare_boolean_with_real()
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
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(u"charlie")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), u"charlie"));
}

void compare_boolean_with_u32string()
{
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), variable(U"delta")));
    TRIAL_PROTOCOL_TEST(!std::equal_to<variable>()(variable(true), U"delta"));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_real();
    compare_null_with_string();
    compare_null_with_wstring();
    compare_null_with_u16string();
    compare_null_with_u32string();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_real();
    compare_boolean_with_string();
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
    compare_boolean_with_u32string();
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

void compare_null_with_real()
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
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), u"charlie"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(u"charlie")));
}

void compare_null_with_u32string()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), U"delta"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(), variable(U"delta")));
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

void compare_boolean_with_real()
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
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), u"charlie"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), variable(u"charlie")));
}

void compare_boolean_with_u32string()
{
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), U"delta"));
    TRIAL_PROTOCOL_TEST(std::not_equal_to<variable>()(variable(false), variable(U"delta")));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_real();
    compare_null_with_string();
    compare_null_with_wstring();
    compare_null_with_u16string();
    compare_null_with_u32string();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_real();
    compare_boolean_with_string();
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
    compare_boolean_with_u32string();
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

void compare_null_with_real()
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
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), u"charlie"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(u"charlie")));
}

void compare_null_with_u32string()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), U"delta"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(), variable(U"delta")));
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

void compare_boolean_with_real()
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
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), u"charlie"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), variable(u"charlie")));
}

void compare_boolean_with_u32string()
{
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), U"delta"));
    TRIAL_PROTOCOL_TEST(std::less<variable>()(variable(false), variable(U"delta")));
}

void run()
{
    // FIXME: More
    compare_null_with_null();
    compare_null_with_boolean();
    compare_null_with_integer();
    compare_null_with_real();
    compare_null_with_string();
    compare_null_with_wstring();
    compare_null_with_u16string();
    compare_null_with_u32string();

    compare_boolean_with_null();
    compare_boolean_with_boolean();
    compare_boolean_with_integer();
    compare_boolean_with_real();
    compare_boolean_with_string();
    compare_boolean_with_wstring();
    compare_boolean_with_u16string();
    compare_boolean_with_u32string();
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
