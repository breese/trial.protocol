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
// std::search
//-----------------------------------------------------------------------------

void search_null()
{
    variable data;
    // null - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_boolean()
{
    variable data(true);
    // boolean - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // boolean - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // boolean - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_integer()
{
    variable data(2);
    // integer - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // integer - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // integer - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_number()
{
    variable data(3.0);
    // number - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // number - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // number - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_string()
{
    variable data("alpha");
    // string - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // string - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // string - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", u"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_wstring()
{
    variable data(L"bravo");
    // wstring - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // wstring - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // wstring - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_u16string()
{
    variable data(u"charlie");
    // u16string - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // u16string - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // u16string - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_u32string()
{
    variable data(U"delta");
    // u32string - null
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // u32string - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // u32string - array
    {
        variable subsequence = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u32string - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    // array - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    // array - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    // array - string
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    // array - wstring
    {
        variable subsequence(L"bravo");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    // array - u16string
    {
        variable subsequence(u"charlie");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    // array - u32string
    {
        variable subsequence(U"delta");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    // array - array
    {
        variable subsequence = array::make({ false });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = array::make({ true });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = array::make({ 0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = array::make({ 2 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = array::make({ 0.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = array::make({ 3.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable subsequence = array::make({ "" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = array::make({ "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable subsequence = array::make({ L"bravo" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable subsequence = array::make({ u"charlie" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        variable subsequence = array::make({ U"delta" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        variable subsequence = array::make({ true, 3.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = array::make({ true, 2, "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = map::make(
            {
                { "bravo", 2 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "charlie", 3.0 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
    // map - boolean
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - integer
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    // map - number
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    // map - string
    {
        variable subsequence("hydrogen");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    // map - wstring
    {
        variable subsequence(L"helium");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    // map - u16string
    {
        variable subsequence(u"lithium");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    // map - u32string
    {
        variable subsequence(U"beryllium");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    // map - array
    {
        variable subsequence = array::make({ true });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = array::make({ true, 2 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = array::make({ 2 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = array::make({ true, 3.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
    {
        variable subsequence = map::make(
            {
                { "alpha", true }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "bravo", 2 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = map::make(
            {
                { "bravo", 2 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = map::make(
            {
                { "alpha", true },
                { "charlie", 3.0 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

int main()
{
    search_null();
    search_boolean();
    search_integer();
    search_number();
    search_string();
    search_wstring();
    search_u16string();
    search_u32string();
    search_array();
    search_map();

    return boost::report_errors();
}
