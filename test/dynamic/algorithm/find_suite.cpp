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
#include <trial/dynamic/algorithm/find.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// key::find
//-----------------------------------------------------------------------------

namespace key_find_suite
{

void find_map()
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
    {
        variable::key_iterator where = key::find(data, "foxtrot");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 5);
    }
    {
        variable::key_iterator where = key::find(data, L"helium");
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = key::find(data, "golf");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 6);
    }
    {
        variable::key_iterator where = key::find(data, u"lithium");
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = key::find(data, "hotel");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 7);
    }
    {
        variable::key_iterator where = key::find(data, U"beryllium");
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
}

void run()
{
    find_map();
}

} // namespace key_find_suite

//-----------------------------------------------------------------------------
// value::find()
//-----------------------------------------------------------------------------

namespace value_find_suite
{

void find_null()
{
    // Null is a zero-sized container, so find always returns end()
    variable data;
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - array
    {
        variable::iterator where = value::find(data, array::make());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - map
    {
        variable::iterator where = value::find(data, map::make());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_boolean()
{
    variable data(true);
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // boolean - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - boolean
    {
        variable::iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // boolean - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - array
    {
        variable::iterator where = value::find(data, array::make({true}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - map
    {
        variable::iterator where = value::find(data, map::make("alpha", true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_boolean()
{
    const variable data(true);
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // boolean - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - boolean
    {
        variable::const_iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // boolean - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - wstring
    {
        variable::const_iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u16string
    {
        variable::const_iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u32string
    {
        variable::const_iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - array
    {
        variable::const_iterator where = value::find(data, array::make({true}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_integer()
{
    variable data(2);
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // integer - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - array
    {
        variable::iterator where = value::find(data, array::make({2}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - map
    {
        variable::iterator where = value::find(data, map::make("alpha", 2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_integer()
{
    const variable data(2);
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // integer - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - wstring
    {
        variable::const_iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u16string
    {
        variable::const_iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u32string
    {
        variable::const_iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - array
    {
        variable::const_iterator where = value::find(data, array::make({2}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", 2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_real()
{
    variable data(3.0);
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // real - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - array
    {
        variable::iterator where = value::find(data, array::make({3.0}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - map
    {
        variable::iterator where = value::find(data, map::make("alpha", 3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_real()
{
    const variable data(3.0);
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // real - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - wstring
    {
        variable::const_iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - u16string
    {
        variable::const_iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - u32string
    {
        variable::const_iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - array
    {
        variable::const_iterator where = value::find(data, array::make({3.0}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // real - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", 3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_string()
{
    variable data("hydrogen");
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // string - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_string()
{
    const variable data("hydrogen");
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // string - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - wstring
    {
        variable::const_iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u16string
    {
        variable::const_iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u32string
    {
        variable::const_iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - array
    {
        variable::const_iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_wstring()
{
    variable data(L"hydrogen");
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // wstring - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, L"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_wstring()
{
    const variable data(L"hydrogen");
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // wstring - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - wstring
    {
        variable::const_iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, L"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - u16string
    {
        variable::const_iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - u32string
    {
        variable::const_iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - array
    {
        variable::const_iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_u16string()
{
    variable data(u"hydrogen");
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // u16string - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, u"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_u16string()
{
    const variable data(u"hydrogen");
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // u16string - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - wstring
    {
        variable::const_iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - u16string
    {
        variable::const_iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, u"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - u32string
    {
        variable::const_iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - array
    {
        variable::const_iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_u32string()
{
    variable data(U"hydrogen");
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // u32string - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - wstring
    {
        variable::iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - u16string
    {
        variable::iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - u32string
    {
        variable::iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, U"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, std::u32string(U"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = value::find(data, variable(U"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_u32string()
{
    const variable data(U"hydrogen");
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // u32string - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - wstring
    {
        variable::const_iterator where = value::find(data, L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - u16string
    {
        variable::const_iterator where = value::find(data, u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - u32string
    {
        variable::const_iterator where = value::find(data, U"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, U"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, std::u32string(U"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(U"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - array
    {
        variable::const_iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_array()
{
    variable data = array::make({ null, true, 2, 3.0, "hydrogen" });
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_array()
{
    const variable data = array::make({ null, true, 2, 3.0, "hydrogen" });
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - array
    {
        variable::const_iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_array_with_array()
{
    variable data = array::make({ null, true, 2, 3.0, "hydrogen", array::make({ "helium" }) });
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, "helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, array::make({"helium"}));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    // array - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_array_with_map()
{
    variable data = array::make({ null, true, 2, 3.0, "hydrogen", map::make("bravo", "helium") });
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, "helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, array::make({"helium"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, map::make("bravo", "helium"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
}

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
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_map()
{
    const variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"}
        });
    {
        variable::const_iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - null
    {
        variable::const_iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
    {
        variable::const_iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - integer
    {
        variable::const_iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - real
    {
        variable::const_iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - string
    {
        variable::const_iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - array
    {
        variable::const_iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
    {
        variable::const_iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_map_with_array()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", array::make({ "helium" })}
        });
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, "helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, array::make({"helium"}));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    // map - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_map_with_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", map::make("golf", "helium")}
        });
    {
        variable::iterator where = value::find(data, data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - null
    {
        variable::iterator where = value::find(data, null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = value::find(data, variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
    {
        variable::iterator where = value::find(data, true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = value::find(data, false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - integer
    {
        variable::iterator where = value::find(data, 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = value::find(data, 22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - real
    {
        variable::iterator where = value::find(data, 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = value::find(data, 33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - string
    {
        variable::iterator where = value::find(data, "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = value::find(data, "helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, "alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - array
    {
        variable::iterator where = value::find(data, array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, array::make({"helium"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
    {
        variable::iterator where = value::find(data, map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = value::find(data, map::make("golf", "helium"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
}

void run()
{
    find_null();
    find_boolean();
    find_const_boolean();
    find_integer();
    find_const_integer();
    find_real();
    find_const_real();
    find_string();
    find_const_string();
    find_wstring();
    find_const_wstring();
    find_u16string();
    find_const_u16string();
    find_u32string();
    find_const_u32string();
    find_array();
    find_const_array();
    find_array_with_array();
    find_array_with_map();
    find_map();
    find_const_map();
    find_map_with_array();
    find_map_with_map();
}

} // namespace value_find_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    key_find_suite::run();
    value_find_suite::run();

    return boost::report_errors();
}
