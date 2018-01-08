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
// std::binary_search
//-----------------------------------------------------------------------------

void search_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_real()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", array::make({ 5 }), map::make({{ "alice", 6 }}) });
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 42), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 43.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"bravo"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"charlie"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), u"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"delta"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), U"zulu"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make({ 5 })), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make({{ "alice", 6 }})), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

void search_map()
{
    variable data = map::make(
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 3.0 },
            { "echo", "hydrogen" },
            { "foxtrot", L"helium" },
            { "golf", array::make({ 5 }) },
            { "hotel", map::make({ {"alice", 6} }) }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 42), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 43.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "hydrogen"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "helium"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"hydrogen"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), L"helium"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make({ 5 })), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), array::make()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make({{ "alice", 6 }})), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), map::make()), false);
}

int main()
{
    search_null();
    search_boolean();
    search_integer();
    search_real();
    search_string();
    search_wstring();
    search_u16string();
    search_u32string();
    search_array();
    search_map();

    return boost::report_errors();
}
