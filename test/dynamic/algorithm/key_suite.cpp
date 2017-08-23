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
#include <trial/protocol/dynamic/algorithm/key.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// key::count
//-----------------------------------------------------------------------------

namespace count_suite
{

void count_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"}
        });

    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "alpha"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, variable("alpha")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "bravo"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "charlie"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "delta"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(key::count(data, "echo"), 1);
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
}

void run()
{
    count_map();
}

} // namespace count_suite

//-----------------------------------------------------------------------------
// key::find
//-----------------------------------------------------------------------------

namespace find_suite
{

void find_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"}
        });
    {
        variable::key_iterator where = key::find(data, "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 0);
    }
    {
        variable::key_iterator where = key::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = key::find(data, "bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 1);
    }
    {
        variable::key_iterator where = key::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = key::find(data, "charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 2);
    }
    {
        variable::key_iterator where = key::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = key::find(data, "delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 3);
    }
    {
        variable::key_iterator where = key::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = key::find(data, "echo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 4);
    }
    {
        variable::key_iterator where = key::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
}

void run()
{
    find_map();
}

} // namespace find_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    count_suite::run();
    find_suite::run();

    return boost::report_errors();
}
