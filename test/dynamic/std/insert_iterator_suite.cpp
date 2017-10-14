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
// std::insert_iterator
//-----------------------------------------------------------------------------

void insert_array()
{
    variable data = array::make();
    std::insert_iterator<variable> inserter(data, data.begin());

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    *inserter++ = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    *inserter++ = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    *inserter++ = 2;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    *inserter++ = 3;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    *inserter++ = "alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    *inserter++ = L"bravo";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 6);
    *inserter++ = u"charlie";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 7);
    *inserter++ = U"delta";
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 8);

    variable expect = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void insert_array_copy()
{
    variable data = array::make();
    variable expect = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    std::copy(expect.begin(), expect.end(), std::inserter(data, data.begin()));

    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void insert_map()
{
    variable data = map::make();
    std::insert_iterator<variable> inserter(data, data.begin());

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    *inserter++ = {"alpha", null};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    *inserter++ = {"bravo", true};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    *inserter++ = {"charlie", 2};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    *inserter++ = {"delta", 3.0};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    *inserter++ = {"echo", "hydrogen"};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    *inserter++ = {"foxtrot", L"helium"};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 6);
    *inserter++ = {"golf", u"lithium"};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 7);
    *inserter++ = {"hotel", U"beryllium"};
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 8);

    variable expect =
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2},
            { "delta", 3.0 },
            { "echo", "hydrogen" },
            { "foxtrot", L"helium" },
            { "golf", u"lithium" },
            { "hotel", U"beryllium" }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void fail_map()
{
    {
        variable data = map::make();
        std::insert_iterator<variable> inserter(data, data.begin());
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(*inserter = null,
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make();
        std::insert_iterator<variable> inserter(data, data.begin());
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(*inserter = "alpha",
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make();
        std::insert_iterator<variable> inserter(data, data.begin());
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((*inserter = { "alpha" }),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = map::make();
        std::insert_iterator<variable> inserter(data, data.begin());
        TRIAL_PROTOCOL_TEST_THROW_EQUAL((*inserter = { "alpha", "bravo", "charlie" }),
                                        error,
                                        "incompatible type");
    }
}

int main()
{
    insert_array();
    insert_array_copy();
    insert_map();
    fail_map();

    return boost::report_errors();
}
