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
// std::mismatch
//-----------------------------------------------------------------------------

void test_null()
{
    // null - null
    {
        variable first;
        variable second;
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - boolean
    {
        variable first;
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - integer
    {
        variable first;
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - real
    {
        variable first;
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - string
    {
        variable first;
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - wstring
    {
        variable first;
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - u16string
    {
        variable first;
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - u32string
    {
        variable first;
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - array
    {
        variable first;
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // null - map
    {
        variable first;
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
}

void test_boolean()
{
    // boolean - boolean
    {
        variable first(true);
        variable second(false);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // boolean - integer
    {
        variable first(true);
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // boolean - real
    {
        variable first(true);
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // boolean - string
    {
        variable first(true);
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // boolean - wstring
    {
        variable first(true);
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // boolean - u16string
    {
        variable first(true);
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // boolean - u32string
    {
        variable first(true);
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // boolean - array
    {
        variable first(true);
        variable second = array::make({ false, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 1);
    }
    // boolean - map
    {
        variable first(true);
        variable second = map::make(
        {
            { "alpha", false },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 1);
    }
}

void test_integer()
{
    // integer - boolean
    {
        variable first(2);
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // integer - integer
    {
        variable first(2);
        variable second(1);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(2);
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // integer - real
    {
        variable first(2);
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // integer - string
    {
        variable first(2);
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // integer - wstring
    {
        variable first(2);
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // integer - u16string
    {
        variable first(2);
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // integer - u32string
    {
        variable first(2);
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // integer - array
    {
        variable first(2);
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // integer - map
    {
        variable first(2);
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_real()
{
    // real - boolean
    {
        variable first(3.0);
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // real - integer
    {
        variable first(3.0);
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // real - real
    {
        variable first(3.0);
        variable second(1.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(3.0);
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    // real - string
    {
        variable first(3.0);
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // real - wstring
    {
        variable first(3.0);
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // real - u16string
    {
        variable first(3.0);
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // real - u32string
    {
        variable first(3.0);
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // real - array
    {
        variable first(3.0);
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // real - map
    {
        variable first(3.0);
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_string()
{
    // string - boolean
    {
        variable first("alpha");
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - integer
    {
        variable first("alpha");
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - real
    {
        variable first("alpha");
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - string
    {
        variable first("alpha");
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first("alpha");
        variable second("zulu");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - wstring
    {
        variable first("alpha");
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - u16string
    {
        variable first("alpha");
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - u32string
    {
        variable first("alpha");
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - array
    {
        variable first("alpha");
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // string - map
    {
        variable first("alpha");
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_wstring()
{
    // wstring - boolean
    {
        variable first(L"bravo");
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - integer
    {
        variable first(L"bravo");
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - real
    {
        variable first(L"bravo");
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - string
    {
        variable first(L"bravo");
        variable second("zulu");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - wstring
    {
        variable first(L"bravo");
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first(L"bravo");
        variable second(L"zulu");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - u16string
    {
        variable first(L"bravo");
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - u32string
    {
        variable first(L"bravo");
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - array
    {
        variable first(L"bravo");
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // wstring - map
    {
        variable first(L"bravo");
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", u"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_u16string()
{
    // u16string - boolean
    {
        variable first(u"charlie");
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - integer
    {
        variable first(u"charlie");
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - real
    {
        variable first(u"charlie");
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - string
    {
        variable first(u"charlie");
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - wstring
    {
        variable first(u"charlie");
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - u16string
    {
        variable first(u"charlie");
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first(u"charlie");
        variable second(u"zulu");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - u32string
    {
        variable first(u"charlie");
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - array
    {
        variable first(u"charlie");
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u16string - map
    {
        variable first(u"charlie");
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_u32string()
{
    // u32string - boolean
    {
        variable first(U"delta");
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - integer
    {
        variable first(U"delta");
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - real
    {
        variable first(U"delta");
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - string
    {
        variable first(U"delta");
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - wstring
    {
        variable first(U"delta");
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - u16string
    {
        variable first(U"delta");
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - u32string
    {
        variable first(U"delta");
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first(U"delta");
        variable second(U"zulu");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - array
    {
        variable first(U"delta");
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // u32string - map
    {
        variable first(U"delta");
        variable second = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_array()
{
    {
        variable first = array::make({ true, 2, 3.0, "alpha", L"bravo" });
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first = array::make({ true, 2, 3.0, "alpha", L"bravo" });
        variable second = array::make({ 1, 2, 3, "alpha", L"bravo" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first = array::make({ true, 2, 3.0, "alpha", L"bravo" });
        variable second = array::make({ true, 3.0, 2, "alpha", L"bravo" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 1);
    }
}

void test_map()
{
    {
        variable first = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        variable second = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        variable second = map::make(
            {
                { "alpha", true },
                { "bravo", 3.0 },
                { "charlie", 2 },
                { "delta", "hydrogen" },
                { "echo", L"helium" },
                { "foxtrot", u"lithium" },
                { "golf", U"beryllium" }
            });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 1);
    }
}

int main()
{
    // Illegal to compare larger container with smaller container, so
    // comparing null with any other type is fine, but comparing any other
    // type with null is illegal.

    test_null();
    test_boolean();
    test_integer();
    test_real();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_map();

    return boost::report_errors();
}
