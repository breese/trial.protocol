///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/algorithm/count.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// key::count
//-----------------------------------------------------------------------------

namespace key_count_suite
{

void count_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", L"helium"},
            {"golf", u"lithium"},
            {"hotel", U"beryllium"}
        });

    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "alpha"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable("alpha")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "bravo"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "charlie"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "delta"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "echo"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "foxtrot"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "hotel"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, 2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, 3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "hydrogen"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable("hydrogen")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, L"helium"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable(L"helium")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, u"lithium"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable(u"lithium")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, U"beryllium"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable(U"beryllium")), 0);
}

void run()
{
    count_map();
}

} // namespace key_count_suite

//-----------------------------------------------------------------------------
// value::count
//-----------------------------------------------------------------------------

namespace value_count_suite
{

void count_null()
{
    // Null is always empty
    variable data;

    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
}

void count_boolean()
{
    variable data(true);

    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
}

void count_integer()
{
    variable data(2);

    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
}

void count_real()
{
    variable data(3.0);

    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
}

void count_string()
{
    {
        variable data("alpha");

        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "bravo"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("bravo")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
    }
    {
        variable data(L"alpha");

        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"bravo"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"bravo")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
    }
    {
        variable data(u"alpha");

        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"bravo"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"bravo")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
    }
    {
        variable data(U"alpha");

        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, L"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(L"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, u"bravo"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(u"bravo")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, U"alpha"), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(U"alpha")), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
    }
}

void count_array()
{
    variable data = array::make(
        { null, true, 2, 3.0, "hydrogen",
          null, true, 2, 3.0,
          null, true, 2,
          null, true,
          null });

    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("hydrogen")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make({ null })), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, data), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
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

    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, null), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(true)), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 2), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(2)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 3.0), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(3.0)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, 33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("hydrogen")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, data), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(value::count(data, map::make()), 0);
}

void run()
{
    count_null();
    count_boolean();
    count_integer();
    count_real();
    count_string();
    count_array();
    count_map();
}

} // namespace value_count_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    key_count_suite::run();
    value_count_suite::run();

    return boost::report_errors();
}
