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
// std::remove
//-----------------------------------------------------------------------------

void remove_null()
{
    variable data;
    auto where = std::remove(data.begin(), data.end(), null);
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_boolean()
{
    variable data(true);
    auto where = std::remove(data.begin(), data.end(), false);
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), true);
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_integer()
{
    variable data(2);
    auto where = std::remove(data.begin(), data.end(), 0);
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), 2);
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_real()
{
    variable data(3.0);
    auto where = std::remove(data.begin(), data.end(), 0.0);
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), 3.0);
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_string()
{
    variable data("alpha");
    auto where = std::remove(data.begin(), data.end(), "zulu");
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), "alpha");
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_wstring()
{
    variable data(L"bravo");
    auto where = std::remove(data.begin(), data.end(), L"zulu");
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), L"bravo");
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_u16string()
{
    variable data(u"charlie");
    auto where = std::remove(data.begin(), data.end(), u"zulu");
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), u"charlie");
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_u32string()
{
    variable data(U"delta");
    auto where = std::remove(data.begin(), data.end(), U"zulu");
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), U"delta");
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_array_null()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), null);
    variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_boolean()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), true);
    variable expect = array::make({ 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_integer()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), 2);
    variable expect = array::make({ true, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_real()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), 3.0);
    variable expect = array::make({ true, 2, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_string()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), "alpha");
    variable expect = array::make({ true, 2, 3.0, L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_wstring()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), L"bravo");
    variable expect = array::make({ true, 2, 3.0, "alpha", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_u16string()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), u"charlie");
    variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_u32string()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::remove(data.begin(), data.end(), U"delta");
    variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_boolean()
{
    // Remove by value but keep key order
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
    auto where = std::remove(data.begin(), data.end(), false);
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), true);
    variable expect = map::make(
        {
            { "alpha", 2 },
            { "bravo", 3.0 },
            { "charlie", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_integer()
{
    // Remove by value but keep key order
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
    auto where = std::remove(data.begin(), data.end(), 0);
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), 2);
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 3.0 },
            { "charlie", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_real()
{
    // Remove by value but keep key order
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
    auto where = std::remove(data.begin(), data.end(), 0.0);
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), 3.0);
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_string()
{
    // Remove by value but keep key order
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
    auto where = std::remove(data.begin(), data.end(), "delta");
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), "hydrogen");
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_wstring()
{
    // Remove by value but keep key order
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
    auto where = std::remove(data.begin(), data.end(), "echo");
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), L"helium");
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "foxtrot", u"lithium" },
            { "golf", U"beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_u16string()
{
    // Remove by value but keep key order
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
    auto where = std::remove(data.begin(), data.end(), "foxtrot");
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), u"lithium");
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "golf", U"beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_u32string()
{
    // Remove by value but keep key order
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
    auto where = std::remove(data.begin(), data.end(), "golf");
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), U"beryllium");
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "foxtrot", u"lithium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

int main()
{
    remove_null();
    remove_boolean();
    remove_integer();
    remove_real();
    remove_string();
    remove_wstring();
    remove_u16string();
    remove_u32string();
    remove_array_null();
    remove_array_boolean();
    remove_array_integer();
    remove_array_real();
    remove_array_string();
    remove_array_wstring();
    remove_array_u16string();
    remove_array_u32string();
    remove_map_boolean();
    remove_map_integer();
    remove_map_real();
    remove_map_string();
    remove_map_wstring();
    remove_map_u16string();
    remove_map_u32string();

    return boost::report_errors();
}
