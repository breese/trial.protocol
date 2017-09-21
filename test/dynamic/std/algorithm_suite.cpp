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
#include <iterator>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

auto is_boolean = [] (const variable& value) { return value.is<boolean>(); };
auto is_integer = [] (const variable& value) { return value.is<integer>(); };
auto is_number = [] (const variable& value) { return value.is<number>(); };
auto is_string = [] (const variable& value) { return value.is<string>(); };
auto is_wstring = [] (const variable& value) { return value.is<wstring>(); };
auto is_u16string = [] (const variable& value) { return value.is<u16string>(); };
auto is_u32string = [] (const variable& value) { return value.is<u32string>(); };

//-----------------------------------------------------------------------------
// std::accumulate
//-----------------------------------------------------------------------------

namespace accumulate_suite
{

void accumulate_null()
{
    variable data;
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<nullable>(), true);
}

void accumulate_null_with_boolean()
{
    variable data;
    variable result = std::accumulate(data.begin(), data.end(), variable(true));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_boolean()
{
    variable data(true);
    variable result = std::accumulate(data.begin(), data.end(), variable(false));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_integer()
{
    variable data(2);
    variable result = std::accumulate(data.begin(), data.end(), variable(0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
}

void accumulate_number()
{
    variable data(3.0);
    variable result = std::accumulate(data.begin(), data.end(), variable(0.0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
}

void accumulate_string()
{
    variable data("alpha");
    variable result = std::accumulate(data.begin(), data.end(), variable("prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "prefixalpha");
}

void accumulate_wstring()
{
    variable data(L"bravo");
    variable result = std::accumulate(data.begin(), data.end(), variable(L"prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<wstring>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"prefixbravo");
}

void accumulate_u16string()
{
    variable data(u"charlie");
    variable result = std::accumulate(data.begin(), data.end(), variable(u"prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u16string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"prefixcharlie");
}

void accumulate_u32string()
{
    variable data(U"delta");
    variable result = std::accumulate(data.begin(), data.end(), variable(U"prefix"));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u32string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u32string>() == U"prefixdelta");
}

void accumulate_array_null()
{
    variable data = array::make({ null, null });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<nullable>(), true);
}

void accumulate_array_null_with_boolean()
{
    variable data = array::make({ null, null });
    variable result = std::accumulate(data.begin(), data.end(), variable(true));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_array_boolean()
{
    variable data = array::make({ false, false, true, true });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_array_integer()
{
    variable data = array::make({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 55);
}

void accumulate_array_integer_with_number()
{
    variable data = array::make({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    variable result = std::accumulate(data.begin(), data.end(), variable(0.0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 55.0);
}

void accumulate_array_number()
{
    variable data = array::make({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 55.0);
}

void accumulate_array_number_with_integer()
{
    variable data = array::make({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 });
    variable result = std::accumulate(data.begin(), data.end(), variable(0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 55);
}

void accumulate_array_string()
{
    variable data = array::make({ "alpha", "bravo", "charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "alphabravocharlie");
}

void accumulate_array_wstring()
{
    variable data = array::make({ L"alpha", L"bravo", L"charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<wstring>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"alphabravocharlie");
}

void accumulate_array_u16string()
{
    variable data = array::make({ u"alpha", u"bravo", u"charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u16string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"alphabravocharlie");
}

void accumulate_array_u32string()
{
    variable data = array::make({ U"alpha", U"bravo", U"charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<u32string>(), true);
    TRIAL_PROTOCOL_TEST(result.value<std::u32string>() == U"alphabravocharlie");
}

void accumulate_array_array()
{
    // Array flattening
    variable data = array::make({ array::make({ "alpha", "bravo" }), array::make({ "charlie", "delta" }) });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<array>(), true);
    variable expect = array::make({ "alpha", "bravo", "charlie", "delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void accumulate_map()
{
    // Iterates over values
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "hydrogenhelium");
}

void run()
{
    accumulate_null();
    accumulate_null_with_boolean();
    accumulate_boolean();
    accumulate_integer();
    accumulate_number();
    accumulate_string();
    accumulate_wstring();
    accumulate_u16string();
    accumulate_u32string();

    accumulate_array_null();
    accumulate_array_null_with_boolean();
    accumulate_array_boolean();
    accumulate_array_integer();
    accumulate_array_integer_with_number();
    accumulate_array_number();
    accumulate_array_number_with_integer();
    accumulate_array_string();
    accumulate_array_wstring();
    accumulate_array_u16string();
    accumulate_array_u32string();
    accumulate_array_array();

    accumulate_map();
}

} // namespace accumulate_suite

//-----------------------------------------------------------------------------
// std::adjacent_find
//-----------------------------------------------------------------------------

namespace adjacent_find_suite
{

void find_null()
{
    variable data;
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_boolean()
{
    variable data(true);
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_integer()
{
    variable data(2);
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_number()
{
    variable data(3.0);
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_string()
{
    variable data("alpha");
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_wstring()
{
    variable data(L"bravo");
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_u16string()
{
    variable data(u"charlie");
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_u32string()
{
    variable data(U"delta");
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_null()
{
    variable data = array::make({ null, null, null });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_boolean()
{
    variable data = array::make({ false, true, true });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_integer()
{
    variable data = array::make({ 0, 1, 2, 3, 40, 40, 41, 41, 5 });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_number()
{
    variable data = array::make({ 0.0, 1.0, 2.0, 3.0, 40.0, 40.0, 41.0, 41.0, 5.0 });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_string()
{
    variable data = array::make({ "alpha", "bravo", "bravo" });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_wstring()
{
    variable data = array::make({ L"alpha", L"bravo", L"bravo" });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_u16string()
{
    variable data = array::make({ u"alpha", u"bravo", u"bravo" });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_u32string()
{
    variable data = array::make({ U"alpha", U"bravo", U"bravo" });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_mixed()
{
    variable data = array::make({ true, true, 2, 2, 3.0, 3.0, "alpha", "alpha" });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_null()
{
    // Only searches values
    variable data = map::make(
        {
            { "alpha", null },
            { "bravo", null },
            { "charlie", null }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_boolean()
{
    variable data = map::make(
        {
            { "alpha", false },
            { "bravo", true },
            { "charlie", true }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_integer()
{
    variable data = map::make(
        {
            { "alpha", 0 },
            { "bravo", 2 },
            { "charlie", 2 }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_number()
{
    variable data = map::make(
        {
            { "alpha", 3.0 },
            { "bravo", 3.0 },
            { "charlie", 0.0 }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_string()
{
    variable data = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" },
            { "charlie", "helium" }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_wstring()
{
    variable data = map::make(
        {
            { "alpha", L"hydrogen" },
            { "bravo", L"helium" },
            { "charlie", L"helium" }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_u16string()
{
    variable data = map::make(
        {
            { "alpha", u"hydrogen" },
            { "bravo", u"helium" },
            { "charlie", u"helium" }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_u32string()
{
    variable data = map::make(
        {
            { "alpha", U"hydrogen" },
            { "bravo", U"helium" },
            { "charlie", U"helium" }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_map_mixed()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 2 },
            { "echo", 3.0 },
            { "foxtrot", 3.0 },
            { "golf", "hydrogen" },
            { "hotel", "hydrogen" }
        });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();

    find_array_null();
    find_array_boolean();
    find_array_integer();
    find_array_number();
    find_array_string();
    find_array_wstring();
    find_array_u16string();
    find_array_u32string();
    find_array_mixed();

    find_map_null();
    find_map_boolean();
    find_map_integer();
    find_map_number();
    find_map_string();
    find_map_wstring();
    find_map_u16string();
    find_map_u32string();
    find_map_mixed();
}

} // namespace adjacent_find_suite

//-----------------------------------------------------------------------------
// std::all_of
//-----------------------------------------------------------------------------

namespace all_of_suite
{

auto is_true = [] (const variable& value) { return bool(value); };

void all_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
}

void all_boolean()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_integer()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(2);
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_number()
{
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_array_boolean()
{
    {
        variable data = array::make();
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ false, false, false });
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, false, true });
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, true, true });
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_array_string()
{
    {
        variable data = { "alpha", "bravo", "charlie", "delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_string));
    }
    {
        variable data = { L"alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_string));
    }
}

void all_array_wstring()
{
    {
        variable data = { L"alpha", L"bravo", L"charlie", L"delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_wstring));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_wstring));
    }
    {
        variable data = { "alpha", "bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_wstring));
    }
}

void all_array_u16string()
{
    {
        variable data = { u"alpha", u"bravo", u"charlie", u"delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_u16string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_u16string));
    }
    {
        variable data = { "alpha", L"bravo", "charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_u16string));
    }
}

void all_array_u32string()
{
    {
        variable data = { U"alpha", U"bravo", U"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_u32string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_u32string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", "delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_u32string));
    }
}

void all_map_boolean()
{
    {
        variable data = map::make();
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", false },
                { "bravo", false },
                { "charlie", false }
            };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", false },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", true },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void run()
{
    all_null();
    all_boolean();
    all_integer();
    all_number();
    all_array_boolean();
    all_array_string();
    all_array_wstring();
    all_array_u16string();
    all_array_u32string();
    all_map_boolean();
}

} // namespace all_of_suite

//-----------------------------------------------------------------------------
// std::any_of
//-----------------------------------------------------------------------------

namespace any_of_suite
{

auto is_true = [] (const variable& value) { return bool(value); };

void any_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
}

void any_boolean()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
}

void any_array_boolean()
{
    {
        variable data = array::make();
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ false, false, false });
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, false, true });
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, true, true });
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
}

void any_array_string()
{
    {
        variable data = { "alpha", "bravo", "charlie", "delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_string));
    }
    {
        variable data = { L"alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_string));
    }
}

void any_array_wstring()
{
    {
        variable data = { L"alpha", L"bravo", L"charlie", L"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_wstring));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_wstring));
    }
    {
        variable data = { "alpha", "bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_wstring));
    }
}

void any_array_u16string()
{
    {
        variable data = { u"alpha", u"bravo", u"charlie", u"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_u16string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_u16string));
    }
    {
        variable data = { "alpha", L"bravo", "charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_u16string));
    }
}

void any_array_u32string()
{
    {
        variable data = { U"alpha", U"bravo", U"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_u32string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_u32string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", "delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_u32string));
    }
}

void any_map_boolean()
{
    {
        variable data = map::make();
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", false },
                { "bravo", false },
                { "charlie", false }
            };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", false },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", true },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
}

void run()
{
    any_null();
    any_boolean();
    any_array_boolean();
    any_array_string();
    any_array_wstring();
    any_array_u16string();
    any_array_u32string();
    any_map_boolean();
}

} // namespace any_of_suite

//-----------------------------------------------------------------------------
// std::binary_search
//-----------------------------------------------------------------------------

namespace binary_search_suite
{

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

void search_number()
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

void run()
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
}

} // namespace binary_search_suite

//-----------------------------------------------------------------------------
// std::copy
//-----------------------------------------------------------------------------

namespace copy_suite
{

void copy_null_to_array()
{
    variable data;
    variable result = array::repeat(0, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void copy_boolean_to_array()
{
    variable data(true);
    variable result = array::repeat(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == true);
}

void copy_integer_to_array()
{
    variable data(2);
    variable result = array::repeat(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 2);
}

void copy_number_to_array()
{
    variable data(3.0);
    variable result = array::repeat(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 3.0);
}

void copy_string_to_array()
{
    variable data("alpha");
    variable result = array::repeat(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == "alpha");
}

void copy_wstring_to_array()
{
    variable data(L"bravo");
    variable result = array::repeat(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == L"bravo");
}

void copy_u16string_to_array()
{
    variable data(u"charlie");
    variable result = array::repeat(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == u"charlie");
}

void copy_u32string_to_array()
{
    variable data(U"delta");
    variable result = array::repeat(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == U"delta");
}

void copy_array_to_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    variable result = array::repeat(data.size(), null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void copy_null_to_vector()
{
    variable data;
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void copy_boolean_to_vector()
{
    variable data(true);
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == true);
}

void copy_integer_to_vector()
{
    variable data(2);
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 2);
}

void copy_number_to_vector()
{
    variable data(3.0);
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 3.0);
}

void copy_string_to_vector()
{
    variable data("alpha");
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == "alpha");
}

void copy_wstring_to_vector()
{
    variable data(L"bravo");
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == L"bravo");
}

void copy_u16string_to_vector()
{
    variable data(u"charlie");
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == u"charlie");
}

void copy_u32string_to_vector()
{
    variable data(U"delta");
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == U"delta");
}

void copy_array_to_vector()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    std::vector<variable> result;
    std::copy(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void run()
{
    copy_null_to_array();
    copy_boolean_to_array();
    copy_integer_to_array();
    copy_number_to_array();
    copy_string_to_array();
    copy_wstring_to_array();
    copy_u16string_to_array();
    copy_u32string_to_array();
    copy_array_to_array();

    copy_null_to_vector();
    copy_boolean_to_vector();
    copy_integer_to_vector();
    copy_number_to_vector();
    copy_string_to_vector();
    copy_wstring_to_vector();
    copy_u16string_to_vector();
    copy_u32string_to_vector();
    copy_array_to_vector();
}

} // namespace copy_suite

//-----------------------------------------------------------------------------
// std::count
//-----------------------------------------------------------------------------

namespace count_suite
{

void count_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0), 0);
}

void count_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 1);
}

void count_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2), 0);
}

void count_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1.0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2.0), 0);
}

void count_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("zulu")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("alpha")), 1);
}

void count_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::wstring(L"")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::wstring(L"zulu")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::wstring(L"bravo")), 1);
}

void count_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::u16string(u"")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::u16string(u"zulu")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::u16string(u"charlie")), 1);
}

void count_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::u32string(U"")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::u32string(U"zulu")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::u32string(U"delta")), 1);
}

void count_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 3), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "alpha"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), L"bravo"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), u"charlie"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), U"delta"), 1);

    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 42), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 42.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), ""), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), L""), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), u""), 0);
}

void count_array_arithmetic()
{
    variable data = array::make({ true, 1, 1.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1.0), 3);
}

void count_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences value, not key
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "helium"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "lithium"), 1);
}

void run()
{
    count_null();
    count_boolean();
    count_integer();
    count_number();
    count_string();
    count_wstring();
    count_u16string();
    count_u32string();
    count_array();
    count_array_arithmetic();
    count_map();
}

} // namespace count_suite

//-----------------------------------------------------------------------------
// std::count_if
//-----------------------------------------------------------------------------

namespace count_if_suite
{

void count_null()
{
    variable data;
    // Cannot iterate over null, so nothing is counted
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == null; }),
                              0);
}

void count_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == false; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == true; }),
                              1);
}

void count_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 0; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 2; }),
                              0);
}

void count_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 0.0; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1.0; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 2.0; }),
                              0);
}

void count_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == ""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "alpha"; }),
                              1);
}

void count_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"bravo"; }),
                              1);
}

void count_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"charlie"; }),
                              1);
}

void count_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"delta"; }),
                              1);
}

void count_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == true; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 2; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 3.0; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "alpha"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"bravo"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"charlie"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"delta"; }),
                              1);

    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == false; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 20; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 300.0; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"zulu"; }),
                              0);
}

void count_array_arithmetic()
{
    variable data = array::make({ true, 1, 1.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == true; }),
                              3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1; }),
                              3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1.0; }),
                              3);
}

void count_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences value, not key
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "alpha"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "hydrogen"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "helium"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "lithium"; }),
                              1);
}

void run()
{
    count_null();
    count_boolean();
    count_integer();
    count_number();
    count_string();
    count_wstring();
    count_u16string();
    count_u32string();
    count_array();
    count_array_arithmetic();
    count_map();
}

} // namespace count_if_suite

//-----------------------------------------------------------------------------
// std::equal
//-----------------------------------------------------------------------------

namespace equal_suite
{

void test_null()
{
    // null has zero length, so std::equal always returns true regardless of the
    // second range.
    variable data;
    variable alpha(1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(data.begin(), data.end(), alpha.begin()),
                              true);
}

void test_boolean()
{
    variable alpha(false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_integer()
{
    variable alpha(2);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo(0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_number()
{
    variable alpha(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_string()
{
    variable alpha("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo("bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_wstring()
{
    variable alpha(L"alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_u16string()
{
    variable alpha(u"alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo(u"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_u32string()
{
    variable alpha(U"alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo(U"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_array_null()
{
    variable alpha = array::make({ null, null });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ null, null, null });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              true);
}

void test_array_boolean()
{
    variable alpha = array::make({ true, true, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ false, true, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = array::make({ false, false, false });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_integer()
{
    variable alpha = array::make({ 2, 2, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ 0, 2, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = array::make({ 0, 0, 0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_number()
{
    variable alpha = array::make({ 3.0, 3.0, 3.0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ 0, 3.0, 3.0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = array::make({ 0, 0, 0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_string()
{
    variable alpha = array::make({ "alpha", "alpha", "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ "bravo", "alpha", "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = array::make({ "bravo", "bravo", "bravo" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_wstring()
{
    variable alpha = array::make({ L"alpha", L"alpha", L"alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ L"bravo", L"alpha", L"alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = array::make({ L"bravo", L"bravo", L"bravo" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_u16string()
{
    variable alpha = array::make({ u"alpha", u"alpha", u"alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ u"bravo", u"alpha", u"alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = array::make({ u"bravo", u"bravo", u"bravo" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_u32string()
{
    variable alpha = array::make({ U"alpha", U"alpha", U"alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = array::make({ U"bravo", U"alpha", U"alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = array::make({ U"bravo", U"bravo", U"bravo" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();

    test_array_null();
    test_array_boolean();
    test_array_integer();
    test_array_number();
    test_array_string();
    test_array_wstring();
    test_array_u16string();
    test_array_u32string();
}

} // namespace equal_suite

//-----------------------------------------------------------------------------
// std::equal_range
//-----------------------------------------------------------------------------

namespace equal_range_suite
{

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

void find_number()
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

void find_array_number()
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

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array_boolean();
    find_array_integer();
    find_array_number();
    find_array_string();
    find_array_wstring();
    find_array_u16string();
    find_array_u32string();
    find_array_value();
}

} // namespace equal_range_suite

//-----------------------------------------------------------------------------
// std::find
//-----------------------------------------------------------------------------

namespace find_suite
{

void find_null()
{
    variable data;
    // Cannot iterate over null, so nothing is found
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), null) == data.end());
}

void find_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), false) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), true) != data.end());
}

void find_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2) == data.end());
}

void find_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0.0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1.0) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2.0) == data.end());
}

void find_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "alpha") != data.end());
}

void find_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"bravo") != data.end());
}

void find_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"charlie") != data.end());
}

void find_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"delta") != data.end());
}

void find_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), false) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), true)),
                              0);

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 42) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), 2)),
                              1);

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 43.0) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), 3.0)),
                              2);

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "alpha")),
                              3);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), L"bravo")),
                              4);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), u"charlie")),
                              5);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), U"delta")),
                              6);
}

void find_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences value, not key
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "alpha") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "hydrogen")),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "helium")),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "lithium")),
                              2);
}

void find_key_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences key
    TRIAL_PROTOCOL_TEST(std::find(data.key_begin(), data.key_end(), "hydrogen") == data.key_end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(),
                                            std::find(data.key_begin(), data.key_end(), "alpha")),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(),
                                            std::find(data.key_begin(), data.key_end(), "bravo")),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(),
                                            std::find(data.key_begin(), data.key_end(), "charlie")),
                              2);
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array();
    find_map();
    find_key_map();
}

} // namespace find_suite

//-----------------------------------------------------------------------------
// std::find_if
//-----------------------------------------------------------------------------

namespace find_if_suite
{

void find_null()
{
    variable data;
    // Cannot iterate over null, so nothing is found
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == null; }) == data.end());
}

void find_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == false; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == true; }) != data.end());
}

void find_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 0; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 1; }) != data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 2; }) == data.end());
}

void find_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 0.0; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 1.0; }) != data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 2.0; }) == data.end());
}

void find_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == ""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "alpha"; }) != data.end());
}

void find_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L"zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L"bravo"; }) != data.end());
}

void find_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u"zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u"charlie"; }) != data.end());
}

void find_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U"zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U"delta"; }) != data.end());
}

void find_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == false; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == true; })),
                              0);

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 42; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == 2; })),
                              1);

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 43.0; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == 3.0; })),
                              2);

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == ""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "alpha"; })),
                              3);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == L"bravo"; })),
                              4);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == u"charlie"; })),
                              5);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == U"delta"; })),
                              6);
}

void find_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences value, not key
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "alpha"; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "hydrogen"; })),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "helium"; })),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "lithium"; })),
                              2);
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array();
    find_map();
}

} // namespace find_if_suite

//-----------------------------------------------------------------------------
// std::insert_iterator
//-----------------------------------------------------------------------------

namespace insert_iterator_suite
{

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

void run()
{
    insert_array();
    insert_array_copy();
    insert_map();
    fail_map();
}

} // namespace insert_iterator_suite

//-----------------------------------------------------------------------------
// std::iota
//-----------------------------------------------------------------------------

namespace iota_suite
{

void test_array_boolean()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), false);
    variable result = array::make({ false, true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void test_array_integer()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), 1);
    variable result = array::make({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void test_array_number()
{
    variable data = array::repeat(4, null);
    std::iota(data.begin(), data.end(), 1.0);
    variable result = array::make({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void run()
{
    test_array_boolean();
    test_array_integer();
    test_array_number();
}

} // namespace iota_suite

//-----------------------------------------------------------------------------
// std::is_partitioned
//-----------------------------------------------------------------------------

namespace is_partitioned_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_boolean()
{
    variable data = array::make({ true, false, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_integer()
{
    variable data = array::make({ 3, 2, 4 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_number()
{
    variable data = array::make({ 3.0, 2.0, 4.0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_string()
{
    variable data = array::make({ "bravo", "alpha", "charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_wstring()
{
    variable data = array::make({ L"bravo", L"alpha", L"charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_u16string()
{
    variable data = array::make({ u"bravo", u"alpha", u"charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_u32string()
{
    variable data = array::make({ U"bravo", U"alpha", U"charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
}

void test_array_arithmetic()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), false);
    }
    {
        variable data = array::make({ 2, 3.0, "alpha", L"bravo", u"charlie", U"delta", true });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), false);
    }
    {
        variable data = array::make({ 3.0, "alpha", L"bravo", u"charlie", U"delta", true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), false);
    }
    {
        variable data = array::make({ "alpha", L"bravo", u"charlie", U"delta", true, 2, 3.0 });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), false);
    }
    {
        variable data = array::make({ L"bravo", u"charlie", U"delta", true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), false);
    }
    {
        variable data = array::make({ u"charlie", U"delta", true, 2, 3.0, "alpha", L"bravo" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), false);
    }
    {
        variable data = array::make({ U"delta", true, 2, 3.0, "alpha", L"bravo", u"charlie" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_wstring), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u16string), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_u32string), true);
    }
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array_boolean();
    test_array_integer();
    test_array_number();
    test_array_string();
    test_array_wstring();
    test_array_u16string();
    test_array_u32string();
    test_array_arithmetic();
}

} // namespace is_partitioned_suite

//-----------------------------------------------------------------------------
// std::is_sorted
//-----------------------------------------------------------------------------

namespace is_sorted_suite
{

void test_array_null()
{
    variable sorted = array::make({ null, null, null });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
}

void test_array_boolean()
{
    variable sorted = array::make({ false, true, true, true });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ true, false, true, true });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_boolean_integer()
{
    variable sorted = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ 2, true });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_integer()
{
    variable sorted = array::make({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ 1, 2, 4, 3 });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_integer_number()
{
    variable sorted = array::make({ 1, 2.0, 3, 4.0 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ 1, 2.0, 4.0, 3 });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_number()
{
    variable sorted = array::make({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ 1.0, 2.0, 4.0, 3.0 });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_string()
{
    variable sorted = array::make({ "alpha", "bravo", "charlie" });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ "alpha", "charlie", "bravo" });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_wstring()
{
    variable sorted = array::make({ L"alpha", L"bravo", L"charlie" });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ L"alpha", L"charlie", L"bravo" });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_u16string()
{
    variable sorted = array::make({ u"alpha", u"bravo", u"charlie" });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ u"alpha", u"charlie", u"bravo" });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_u32string()
{
    variable sorted = array::make({ U"alpha", U"bravo", U"charlie" });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = array::make({ U"alpha", U"charlie", U"bravo" });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void run()
{
    test_array_null();
    test_array_boolean();
    test_array_boolean_integer();
    test_array_integer();
    test_array_integer_number();
    test_array_number();
    test_array_string();
    test_array_wstring();
    test_array_u16string();
    test_array_u32string();
}

} // namespace is_sorted_suite

//-----------------------------------------------------------------------------
// std::lower_bound
//-----------------------------------------------------------------------------

namespace lower_bound_suite
{

void find_null()
{
    variable data;
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_boolean()
{
    variable data(true);
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_integer()
{
    variable data(2);
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_number()
{
    variable data(3.0);
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_string()
{
    variable data("alpha");
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_wstring()
{
    variable data(L"bravo");
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_u16string()
{
    variable data(u"charlie");
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_u32string()
{
    variable data(U"delta");
    {
        auto where = std::lower_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_array()
{
    variable data = array::make({true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta"});
    {
        auto where = std::lower_bound(data.begin(), data.end(), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "zulu");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"zulu");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"zulu");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"zulu");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 7);
    }
}

void find_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" },
            { "echo", L"helium" },
            { "golf", u"lithium" },
            { "hotel", U"beryllium" }
        });
    {
        auto where = std::lower_bound(data.begin(), data.end(), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), "tungsten");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"helium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), L"tungsten");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"lithium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), u"tungsten");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"beryllium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::lower_bound(data.begin(), data.end(), U"tungsten");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_key_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    {
        auto where = std::lower_bound(data.key_begin(), data.key_end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 0);
    }
    {
        auto where = std::lower_bound(data.key_begin(), data.key_end(), "bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 1);
    }
    {
        auto where = std::lower_bound(data.key_begin(), data.key_end(), "charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 2);
    }
    {
        auto where = std::lower_bound(data.key_begin(), data.key_end(), "delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 3);
    }
    {
        auto where = std::lower_bound(data.key_begin(), data.key_end(), "hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array();
    find_map();
    find_key_map();
}

} // namespace lower_bound_suite

//-----------------------------------------------------------------------------
// std::max_element
//-----------------------------------------------------------------------------

namespace max_element_suite
{

void max_null()
{
    variable data;
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void max_boolean()
{
    variable data(true);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == true);
}

void max_integer()
{
    variable data(1);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 1);
}

void max_number()
{
    variable data(1.0);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 1.0);
}

void max_string()
{
    variable data("alpha");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "alpha");
}

void max_wstring()
{
    variable data(L"bravo");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == L"bravo");
}

void max_u16string()
{
    variable data(u"charlie");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == u"charlie");
}

void max_u32string()
{
    variable data(U"delta");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == U"delta");
}

void max_array_arithmetic()
{
    variable data = array::make({false, 2, 3.0});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
}

void max_array_string()
{
    variable data = array::make({"alpha", "bravo", "charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "charlie");
}

void max_array_wstring()
{
    variable data = array::make({L"alpha", L"bravo", L"charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == L"charlie");
}

void max_array_u16string()
{
    variable data = array::make({u"alpha", u"bravo", u"charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == u"charlie");
}

void max_array_u32string()
{
    variable data = array::make({U"alpha", U"bravo", U"charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == U"charlie");
}

void max_array_value()
{
    variable data = array::make({true, 2, 3.0, "alpha", "bravo", "charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "charlie");
}

void max_array_array()
{
    variable data = array::make({true, 2, 3.0, array::make({ 42 }), array::make({ 41 }), "alpha"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<array>());
    TRIAL_PROTOCOL_TEST(*where == array::make({ 42 }));
}

void max_array_map()
{
    variable data = array::make({true, 2, 3.0, map::make({{ "alpha", 117 }}), array::make({ 42 }), "hydrogen"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<map>());
    TRIAL_PROTOCOL_TEST(*where == map::make({{ "alpha", 117 }}));
}

void max_map_arithmetic()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
}

void max_map_value()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "hydrogen");
}

void max_map_array()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", array::make({ 42 }) },
            { "delta", array::make({ 41 }) },
            { "echo", 3.0 },
            { "foxtrot", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == array::make({ 42 }));
}

void max_map_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", map::make({{ "alice", 117 }}) },
            { "delta", array::make({ 42 }) },
            { "echo", 3.0 },
            { "foxtrot", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == map::make({{ "alice" , 117 }}));
}

void run()
{
    max_null();
    max_boolean();
    max_integer();
    max_number();
    max_string();
    max_wstring();
    max_u16string();
    max_u32string();
    max_array_arithmetic();
    max_array_string();
    max_array_wstring();
    max_array_u16string();
    max_array_u32string();
    max_array_value();
    max_array_array();
    max_array_map();
    max_map_arithmetic();
    max_map_value();
    max_map_array();
    max_map_map();
}

} // namespace max_element_suite

//-----------------------------------------------------------------------------
// std::mismatch
//-----------------------------------------------------------------------------

namespace mismatch_suite
{

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
    // null - number
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
    // boolean - number
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
    // integer - number
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

void test_number()
{
    // number - boolean
    {
        variable first(3.0);
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // number - integer
    {
        variable first(3.0);
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // number - number
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
    // number - string
    {
        variable first(3.0);
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // number - wstring
    {
        variable first(3.0);
        variable second(L"bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // number - u16string
    {
        variable first(3.0);
        variable second(u"charlie");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // number - u32string
    {
        variable first(3.0);
        variable second(U"delta");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // number - array
    {
        variable first(3.0);
        variable second = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    // number - map
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
    // string - number
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
    // wstring - number
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
    // u16string - number
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
    // u32string - number
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

void run()
{
    // Illegal to compare larger container with smaller container, so
    // comparing null with any other type is fine, but comparing any other
    // type with null is illegal.

    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_map();
}

} // namespace mismatch_suite

//-----------------------------------------------------------------------------
// std::move
//-----------------------------------------------------------------------------

namespace move_suite
{

void move_null_to_array()
{
    variable data;
    variable result = array::repeat(0, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void move_boolean_to_array()
{
    variable data(true);
    variable result = array::repeat(1, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == true);
}

void move_integer_to_array()
{
    variable data(2);
    variable result = array::repeat(1, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 2);
}

void move_number_to_array()
{
    variable data(3.0);
    variable result = array::repeat(1, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 3.0);
}

void move_string_to_array()
{
    variable data("alpha");
    variable result = array::repeat(1, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == "alpha");
}

void move_wstring_to_array()
{
    variable data(L"bravo");
    variable result = array::repeat(1, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == L"bravo");
}

void move_u16string_to_array()
{
    variable data(u"charlie");
    variable result = array::repeat(1, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == u"charlie");
}

void move_u32string_to_array()
{
    variable data(U"delta");
    variable result = array::repeat(1, null);
    std::move(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == U"delta");
}

void move_array_to_array()
{
    variable data = { true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" };
    variable result = array::repeat(data.size(), null);
    std::move(data.begin(), data.end(), result.begin());

    variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void move_null_to_vector()
{
    variable data;
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void move_boolean_to_vector()
{
    variable data(true);
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == true);
}

void move_integer_to_vector()
{
    variable data(2);
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 2);
}

void move_number_to_vector()
{
    variable data(3.0);
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 3.0);
}

void move_string_to_vector()
{
    variable data("alpha");
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == "alpha");
}

void move_wstring_to_vector()
{
    variable data(L"bravo");
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == L"bravo");
}

void move_u16string_to_vector()
{
    variable data(u"charlie");
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == u"charlie");
}

void move_u32string_to_vector()
{
    variable data(U"delta");
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == U"delta");
}

void move_array_to_vector()
{
    variable data = { true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" };
    std::vector<variable> result;
    std::move(data.begin(), data.end(), std::back_inserter(result));

    variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    move_null_to_array();
    move_boolean_to_array();
    move_integer_to_array();
    move_number_to_array();
    move_string_to_array();
    move_wstring_to_array();
    move_u16string_to_array();
    move_u32string_to_array();
    move_array_to_array();

    move_null_to_vector();
    move_boolean_to_vector();
    move_integer_to_vector();
    move_number_to_vector();
    move_string_to_vector();
    move_wstring_to_vector();
    move_u16string_to_vector();
    move_u32string_to_vector();
    move_array_to_vector();
}

} // namespace move_suite

//-----------------------------------------------------------------------------
// std::none_of
//-----------------------------------------------------------------------------

namespace none_of_suite
{

auto is_true = [] (const variable& value) { return bool(value); };

void none_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_true));
}

void none_boolean()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_true));
    }
}

void none_array_boolean()
{
    {
        variable data = array::make();
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ false, false, false });
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, false, true });
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, true, true });
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_true));
    }
}

void none_array_string()
{
    {
        variable data = { "alpha", "bravo", "charlie", "delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_string));
    }
    {
        variable data = { L"alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_string));
    }
}

void none_array_wstring()
{
    {
        variable data = { L"alpha", L"bravo", L"charlie", L"delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_wstring));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_wstring));
    }
    {
        variable data = { "alpha", "bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_wstring));
    }
}

void none_array_u16string()
{
    {
        variable data = { u"alpha", u"bravo", u"charlie", u"delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_u16string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_u16string));
    }
    {
        variable data = { "alpha", L"bravo", "charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_u16string));
    }
}

void none_array_u32string()
{
    {
        variable data = { U"alpha", U"bravo", U"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_u32string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_u32string));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", "delta" };
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_u32string));
    }
}

void none_map_boolean()
{
    {
        variable data = map::make();
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", false },
                { "bravo", false },
                { "charlie", false }
            };
        TRIAL_PROTOCOL_TEST(std::none_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", false },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", true },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(!std::none_of(data.begin(), data.end(), is_true));
    }
}

void run()
{
    none_null();
    none_boolean();
    none_array_boolean();
    none_array_string();
    none_array_wstring();
    none_array_u16string();
    none_array_u32string();
    none_map_boolean();
}

} // namespace none_of_suite

//-----------------------------------------------------------------------------
// std::partition_point
//-----------------------------------------------------------------------------

namespace partition_point_suite
{

void find_null()
{
    variable data;
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_boolean()
{
    variable data(true);
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_integer()
{
    variable data(2);
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_number()
{
    variable data(3.0);
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_string()
{
    variable data("alpha");
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_wstring()
{
    variable data(L"bravo");
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_u16string()
{
    variable data(u"charlie");
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_u32string()
{
    variable data(U"delta");
    {
        auto where = std::partition_point(data.begin(), data.end(), is_boolean);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_number);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is_u32string);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_array_boolean()
{
    variable data = array::make({ false, true, null, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is_boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_integer()
{
    variable data = array::make({ 0, 2, null, true, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is_integer);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_number()
{
    variable data = array::make({ 0.0, 3.0, null, true, 2, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is_number);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_string()
{
    variable data = array::make({ "", "alpha", null, true, 2, 3.0, L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is_string);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_wstring()
{
    variable data = array::make({ L"", L"bravo", null, true, 2, 3.0, "alpha", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is_wstring);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_u16string()
{
    variable data = array::make({ u"", u"charlie", null, true, 2, 3.0, "alpha", L"bravo", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is_u16string);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_u32string()
{
    variable data = array::make({ U"", U"delta", null, true, 2, 3.0, "alpha", L"bravo", u"charlie" });
    auto where = std::partition_point(data.begin(), data.end(), is_u32string);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array_boolean();
    find_array_integer();
    find_array_number();
    find_array_string();
    find_array_wstring();
    find_array_u16string();
    find_array_u32string();
}

} // namespace partition_point_suite

//-----------------------------------------------------------------------------
// std::remove
//-----------------------------------------------------------------------------

namespace remove_suite
{

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

void remove_number()
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

void remove_array_number()
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

void remove_map_number()
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

void run()
{
    remove_null();
    remove_boolean();
    remove_integer();
    remove_number();
    remove_string();
    remove_wstring();
    remove_u16string();
    remove_u32string();
    remove_array_null();
    remove_array_boolean();
    remove_array_integer();
    remove_array_number();
    remove_array_string();
    remove_array_wstring();
    remove_array_u16string();
    remove_array_u32string();
    remove_map_boolean();
    remove_map_integer();
    remove_map_number();
    remove_map_string();
    remove_map_wstring();
    remove_map_u16string();
    remove_map_u32string();
}

} // namespace remove_suite

//-----------------------------------------------------------------------------
// std::search
//-----------------------------------------------------------------------------

namespace search_suite
{

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

void run()
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
}

} // namespace search_suite

//-----------------------------------------------------------------------------
// std::unique
//-----------------------------------------------------------------------------

namespace unique_suite
{

void test_null()
{
    variable data;
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 0);
}

void test_boolean()
{
    variable data(true);
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 1);
}

void test_integer()
{
    variable data(2);
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 1);
}

void test_number()
{
    variable data(3.0);
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 1);
}

void test_string()
{
    variable data("alpha");
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 1);
}

void test_wstring()
{
    variable data(L"bravo");
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 1);
}

void test_u16string()
{
    variable data(u"charlie");
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 1);
}

void test_u32string()
{
    variable data(U"delta");
    auto end = std::unique(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), end), 1);
}

void test_array_null()
{
    variable data = array::make({ null, null, null });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_boolean()
{
    variable data = array::make({ false, true, false, false, true });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ false, true, false, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_integer()
{
    variable data = array::make({ 0, 0, 2, 1, 1 });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ 0, 2, 1 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_number()
{
    variable data = array::make({ 0.0, 0.0, 2.0, 1.0, 1.0 });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ 0.0, 2.0, 1.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_arithmetic()
{
    variable data = array::make({ false, 0, 0.0, 2, 1.0, 1 });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ false, 2, 1.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_string()
{
    variable data = array::make({ "alpha", "alpha", "bravo", "bravo" });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_wstring()
{
    variable data = array::make({ L"alpha", L"alpha", L"bravo", L"bravo" });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ L"alpha", L"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_u16string()
{
    variable data = array::make({ u"alpha", u"alpha", u"bravo", u"bravo" });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ u"alpha", u"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_u32string()
{
    variable data = array::make({ U"alpha", U"alpha", U"bravo", U"bravo" });
    auto end = std::unique(data.begin(), data.end());
    variable expect = array::make({ U"alpha", U"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array_null();
    test_array_boolean();
    test_array_integer();
    test_array_number();
    test_array_arithmetic();
    test_array_string();
    test_array_wstring();
    test_array_u16string();
    test_array_u32string();
}

} // namespace unique_suite

//-----------------------------------------------------------------------------
// std::upper_bound
//-----------------------------------------------------------------------------

namespace upper_bound_suite
{

void find_null()
{
    variable data;
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_boolean()
{
    variable data(true);
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_integer()
{
    variable data(2);
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_number()
{
    variable data(3.0);
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_string()
{
    variable data("alpha");
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_wstring()
{
    variable data(L"bravo");
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_u16string()
{
    variable data(u"charlie");
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_u32string()
{
    variable data(U"delta");
    {
        auto where = std::upper_bound(data.begin(), data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_array()
{
    variable data = array::make({true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta"});
    {
        auto where = std::upper_bound(data.begin(), data.end(), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 7);
    }
}

void find_map()
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
    {
        auto where = std::upper_bound(data.begin(), data.end(), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), 4);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), "tungsten");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"helium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), L"tungsten");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"lithium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), u"tungsten");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"beryllium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 7);
    }
    {
        auto where = std::upper_bound(data.begin(), data.end(), U"tungsten");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 7);
    }
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array();
    find_map();
}

} // namespace upper_bound_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    accumulate_suite::run();
    adjacent_find_suite::run();
    all_of_suite::run();
    any_of_suite::run();
    binary_search_suite::run();
    copy_suite::run();
    count_suite::run();
    count_if_suite::run();
    equal_suite::run();
    equal_range_suite::run();
    find_suite::run();
    find_if_suite::run();
    insert_iterator_suite::run();
    iota_suite::run();
    is_partitioned_suite::run();
    is_sorted_suite::run();
    lower_bound_suite::run();
    max_element_suite::run();
    mismatch_suite::run();
    move_suite::run();
    none_of_suite::run();
    partition_point_suite::run();
    remove_suite::run();
    search_suite::run();
    unique_suite::run();
    upper_bound_suite::run();

    return boost::report_errors();
}
