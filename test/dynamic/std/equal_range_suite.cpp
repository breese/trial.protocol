///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::equal_range
//-----------------------------------------------------------------------------

void find_null()
{
    variable data;
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
}

void find_boolean()
{
    variable data(true);
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
}

void find_integer()
{
    variable data(2);
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
}

void find_real()
{
    variable data(3.0);
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
}

void find_string()
{
    variable data("alpha");
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
}

void find_wstring()
{
    variable data(L"bravo");
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
}

void find_u16string()
{
    variable data(u"charlie");
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
}

void find_u32string()
{
    variable data(U"delta");
    {
        auto result = std::equal_range(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 0);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
}

void find_array_boolean()
{
    // array must be sorted
    variable data = array::make({ false, false, true, true, true });
    {
        auto result = std::equal_range(data.begin(), data.end(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 2);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 5);
    }
}

void find_array_integer()
{
    // array must be sorted
    variable data = array::make({ 0, 1, 1, 2, 3, 3, 3 });
    {
        auto result = std::equal_range(data.begin(), data.end(), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 3);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 4);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 7);
    }
}

void find_array_real()
{
    // array must be sorted
    variable data = array::make({ 0.0, 1.0, 1.0, 2.0, 3.0, 3.0, 3.0 });
    {
        auto result = std::equal_range(data.begin(), data.end(), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 3);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 4);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 7);
    }
}

void find_array_string()
{
    // array must be sorted
    variable data = array::make({ "alpha", "bravo", "bravo", "charlie", "delta", "delta", "delta" });
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 3);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 4);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 7);
    }
}

void find_array_wstring()
{
    // array must be sorted
    variable data = array::make({ L"alpha", L"bravo", L"bravo", L"charlie", L"delta", L"delta", L"delta" });
    {
        auto result = std::equal_range(data.begin(), data.end(), L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 3);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 4);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 7);
    }
}

void find_array_u16string()
{
    // array must be sorted
    variable data = array::make({ u"alpha", u"bravo", u"bravo", u"charlie", u"delta", u"delta", u"delta" });
    {
        auto result = std::equal_range(data.begin(), data.end(), u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 3);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 4);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 7);
    }
}

void find_array_u32string()
{
    // array must be sorted
    variable data = array::make({ U"alpha", U"bravo", U"bravo", U"charlie", U"delta", U"delta", U"delta" });
    {
        auto result = std::equal_range(data.begin(), data.end(), U"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 1);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 3);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 4);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 7);
    }
}

void find_array_value()
{
    // array must be sorted
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    {
        auto result = std::equal_range(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 2);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 3);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 3);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 4);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 5);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 5);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 6);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 6);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 7);
    }
    {
        auto result = std::equal_range(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.first), 7);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), result.second), 8);
    }
}

int main()
{
    find_null();
    find_boolean();
    find_integer();
    find_real();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array_boolean();
    find_array_integer();
    find_array_real();
    find_array_string();
    find_array_wstring();
    find_array_u16string();
    find_array_u32string();
    find_array_value();

    return boost::report_errors();
}
