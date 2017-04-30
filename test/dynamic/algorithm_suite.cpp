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
#include <trial/protocol/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

auto is_boolean = [] (const variable& value) { return value.is<bool>(); };
auto is_integer = [] (const variable& value) { return value.is<int>(); };
auto is_number = [] (const variable& value) { return value.is<float>(); };
auto is_string = [] (const variable& value) { return value.is<string>(); };

//-----------------------------------------------------------------------------
// std::accumulate
//-----------------------------------------------------------------------------

namespace accumulate_suite
{

void accumulate_null()
{
    variable data;
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<null_type>(), true);
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

void accumulate_array_null()
{
    variable data = variable::array({ null, null });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<null_type>(), true);
}

void accumulate_array_null_with_boolean()
{
    variable data = variable::array({ null, null });
    variable result = std::accumulate(data.begin(), data.end(), variable(true));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_array_boolean()
{
    variable data = variable::array({ false, false, true, true });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void accumulate_array_integer()
{
    variable data = variable::array({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 55);
}

void accumulate_array_integer_with_number()
{
    variable data = variable::array({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    variable result = std::accumulate(data.begin(), data.end(), variable(0.0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 55.0);
}

void accumulate_array_number()
{
    variable data = variable::array({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 55.0);
}

void accumulate_array_number_with_integer()
{
    variable data = variable::array({ 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 });
    variable result = std::accumulate(data.begin(), data.end(), variable(0));
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 55);
}

void accumulate_array_string()
{
    variable data = variable::array({ "alpha", "bravo", "charlie" });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "alphabravocharlie");
}

void accumulate_array_array()
{
    // Array flattening
    variable data = variable::array({ variable::array({ "alpha", "bravo" }), variable::array({ "charlie", "delta" }) });
    variable result = std::accumulate(data.begin(), data.end(), variable());
    TRIAL_PROTOCOL_TEST_EQUAL(result.is<array>(), true);
    variable expect = variable::array({ "alpha", "bravo", "charlie", "delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void accumulate_map()
{
    // Iterates over values
    variable data = variable::map(
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

    accumulate_array_null();
    accumulate_array_null_with_boolean();
    accumulate_array_boolean();
    accumulate_array_integer();
    accumulate_array_integer_with_number();
    accumulate_array_number();
    accumulate_array_number_with_integer();
    accumulate_array_string();
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

void find_array_null()
{
    variable data = variable::array({ null, null, null });
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
    variable data = variable::array({ false, true, true });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_integer()
{
    variable data = variable::array({ 0, 1, 2, 3, 40, 40, 41, 41, 5 });
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
    variable data = variable::array({ 0.0, 1.0, 2.0, 3.0, 40.0, 40.0, 41.0, 41.0, 5.0 });
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
    variable data = variable::array({ "alpha", "bravo", "bravo" });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void find_array_mixed()
{
    variable data = variable::array({ true, true, 2, 2, 3.0, 3.0, "alpha", "alpha" });
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
    variable data = variable::map(
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
    variable data = variable::map(
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
    variable data = variable::map(
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
    variable data = variable::map(
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
    variable data = variable::map(
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

void find_map_mixed()
{
    variable data = variable::map(
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

    find_array_null();
    find_array_boolean();
    find_array_integer();
    find_array_number();
    find_array_string();
    find_array_mixed();

    find_map_null();
    find_map_boolean();
    find_map_integer();
    find_map_number();
    find_map_string();
    find_map_mixed();
}

} // namespace adjacent_find_suite

//-----------------------------------------------------------------------------
// std::all_of
//-----------------------------------------------------------------------------

namespace all_of_suite
{

auto is_true = [] (const variable& value) { return bool(value); };

void test_array_boolean()
{
    variable data = variable::array({ true, true, true });
    TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
}

void fail_array_boolean()
{
    variable data = variable::array({ true, false, true });
    TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
}

void run()
{
    test_array_boolean();
    fail_array_boolean();
}

} // namespace all_of_suite

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
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map()), false);
}

void search_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map()), false);
}

void search_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map()), false);
}

void search_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map()), false);
}

void search_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map()), false);
}

void search_array()
{
    variable data = variable::array({ null, true, 2, 3.0, "alpha", variable::array({ 5 }), variable::map({{ "alice", 6 }}) });
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 42), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 43.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "alpha"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "bravo"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array({ 5 })), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map({{ "alice", 6 }})), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map()), false);
}

void search_map()
{
    variable data = variable::map(
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 3.0 },
            { "echo", "hydrogen" },
            { "foxtrot", variable::array({ 5 }) },
            { "golf", variable::map({ {"alice", 6} }) }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), null), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), false), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), true), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 2), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 42), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 3.0), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), 43.0), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "hydrogen"), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), "lithium"), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array({ 5 })), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::array()), false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map({{ "alice", 6 }})), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::binary_search(data.begin(), data.end(), variable::map()), false);
}

void run()
{
    search_null();
    search_boolean();
    search_integer();
    search_number();
    search_string();
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
    variable result = variable::array(0, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void copy_boolean_to_array()
{
    variable data(true);
    variable result = variable::array(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == true);
}

void copy_integer_to_array()
{
    variable data(2);
    variable result = variable::array(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 2);
}

void copy_number_to_array()
{
    variable data(3.0);
    variable result = variable::array(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 3.0);
}

void copy_string_to_array()
{
    variable data("alpha");
    variable result = variable::array(1, null);
    std::copy(data.begin(), data.end(), result.begin());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == "alpha");
}

void copy_array_to_array()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    variable result = variable::array(data.size(), null);
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

void copy_array_to_vector()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
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
    copy_array_to_array();

    copy_null_to_vector();
    copy_boolean_to_vector();
    copy_integer_to_vector();
    copy_number_to_vector();
    copy_string_to_vector();
    copy_array_to_vector();
}

} // namespace copy_suite

//-----------------------------------------------------------------------------
// std::count
//-----------------------------------------------------------------------------

namespace count_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0), 0);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 1);
}

void test_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2), 0);
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1.0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2.0), 0);
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("alpha")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("bravo")), 0);
}

void test_array()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 3), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "alpha"), 1);

    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 42), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 42.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), ""), 0);
}

void test_array_arithmetic()
{
    variable data = variable::array({ true, 1, 1.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1.0), 3);
}

void test_map()
{
    variable data = variable::map(
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
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_array_arithmetic();
    test_map();
}

} // namespace count_suite

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

void test_array_null()
{
    variable alpha = variable::array({ null, null });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = variable::array({ null, null, null });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              true);
}

void test_array_boolean()
{
    variable alpha = variable::array({ true, true, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = variable::array({ false, true, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = variable::array({ false, false, false });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_integer()
{
    variable alpha = variable::array({ 2, 2, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = variable::array({ 0, 2, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = variable::array({ 0, 0, 0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_number()
{
    variable alpha = variable::array({ 3.0, 3.0, 3.0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = variable::array({ 0, 3.0, 3.0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = variable::array({ 0, 0, 0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void test_array_string()
{
    variable alpha = variable::array({ "alpha", "alpha", "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = variable::array({ "bravo", "alpha", "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = variable::array({ "bravo", "bravo", "bravo" });
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

    test_array_null();
    test_array_boolean();
    test_array_integer();
    test_array_number();
    test_array_string();
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
}

void find_array_boolean()
{
    // array must be sorted
    variable data = variable::array({ false, false, true, true, true });
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
    variable data = variable::array({ 0, 1, 1, 2, 3, 3, 3 });
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
    variable data = variable::array({ 0.0, 1.0, 1.0, 2.0, 3.0, 3.0, 3.0 });
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
    variable data = variable::array({ "alpha", "bravo", "bravo", "charlie", "delta", "delta", "delta" });
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

void find_array_value()
{
    // array must be sorted
    variable data = variable::array({ null, true, 2, 3.0, "alpha" });
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
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_array_boolean();
    find_array_integer();
    find_array_number();
    find_array_string();
    find_array_value();
}

} // namespace equal_range_suite

//-----------------------------------------------------------------------------
// std::find
//-----------------------------------------------------------------------------

namespace find_suite
{

void test_null()
{
    variable data;
    // Cannot iterate over null, so nothing is found
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), null) == data.end());
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), false) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), true) != data.end());
}

void test_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2) == data.end());
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0.0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1.0) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2.0) == data.end());
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "alpha") != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "bravo") == data.end());
}

void test_array()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });

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
}

void test_map()
{
    variable data = variable::map(
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

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_map();
}

} // namespace find_suite

//-----------------------------------------------------------------------------
// std::find_if
//-----------------------------------------------------------------------------

namespace find_if_suite
{

void test_null()
{
    variable data;
    // Cannot iterate over null, so nothing is found
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == null; }) == data.end());
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == false; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == true; }) != data.end());
}

void test_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 0; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 1; }) != data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 2; }) == data.end());
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 0.0; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 1.0; }) != data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 2.0; }) == data.end());
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == ""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "alpha"; }) != data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "bravo"; }) == data.end());
}

void test_array()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });

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
}

void test_map()
{
    variable data = variable::map(
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
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_map();
}

} // namespace find_if_suite

//-----------------------------------------------------------------------------
// std::iota
//-----------------------------------------------------------------------------

namespace iota_suite
{

void test_array_boolean()
{
    variable data = variable::array(4, null);
    std::iota(data.begin(), data.end(), false);
    variable result = variable::array({ false, true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void test_array_integer()
{
    variable data = variable::array(4, null);
    std::iota(data.begin(), data.end(), 1);
    variable result = variable::array({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void test_array_number()
{
    variable data = variable::array(4, null);
    std::iota(data.begin(), data.end(), 1.0);
    variable result = variable::array({ 1.0, 2.0, 3.0, 4.0 });
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
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_array_boolean()
{
    variable data = variable::array({ true, false, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_array_integer()
{
    variable data = variable::array({ 3, 2, 4 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_array_number()
{
    variable data = variable::array({ 3.0, 2.0, 4.0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_array_string()
{
    variable data = variable::array({ "bravo", "alpha", "charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
}

void test_array_arithmetic()
{
    {
        variable data = variable::array({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
    }
    {
        variable data = variable::array({ 2, 3.0, "alpha", true });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
    }
    {
        variable data = variable::array({ 3.0, "alpha", true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), false);
    }
    {
        variable data = variable::array({ "alpha", true, 2, 3.0 });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_boolean), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_integer), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_number), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is_string), true);
    }
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array_boolean();
    test_array_integer();
    test_array_number();
    test_array_string();
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
    variable sorted = variable::array({ null, null, null });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
}

void test_array_boolean()
{
    variable sorted = variable::array({ false, true, true, true });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = variable::array({ true, false, true, true });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_boolean_integer()
{
    variable sorted = variable::array({ true, 2 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = variable::array({ 2, true });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_integer()
{
    variable sorted = variable::array({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = variable::array({ 1, 2, 4, 3 });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_integer_number()
{
    variable sorted = variable::array({ 1, 2.0, 3, 4.0 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = variable::array({ 1, 2.0, 4.0, 3 });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_number()
{
    variable sorted = variable::array({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = variable::array({ 1.0, 2.0, 4.0, 3.0 });
    TRIAL_PROTOCOL_TEST(!std::is_sorted(unsorted.begin(), unsorted.end()));
}

void test_array_string()
{
    variable sorted = variable::array({ "alpha", "bravo", "charlie" });
    TRIAL_PROTOCOL_TEST(std::is_sorted(sorted.begin(), sorted.end()));
    variable unsorted = variable::array({ "alpha", "charlie", "bravo" });
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
}

void find_array()
{
    variable data = variable::array({true, 2, 3.0, "alpha"});
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
        auto where = std::lower_bound(data.begin(), data.end(), "bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
}

void find_map()
{
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
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
        auto where = std::lower_bound(data.begin(), data.end(), "lithium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_array();
    find_map();
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

void max_array_arithmetic()
{
    variable data = variable::array({false, 2, 3.0});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
}

void max_array_string()
{
    variable data = variable::array({"alpha", "bravo", "charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "charlie");
}

void max_array_value()
{
    variable data = variable::array({true, 2, 3.0, "alpha", "bravo", "charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "charlie");
}

void max_array_array()
{
    variable data = variable::array({true, 2, 3.0, variable::array({ 42 }), variable::array({ 41 }), "alpha"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<array>());
    TRIAL_PROTOCOL_TEST(*where == variable::array({ 42 }));
}

void max_array_map()
{
    variable data = variable::array({true, 2, 3.0, variable::map({{ "alpha", 117 }}), variable::array({ 42 }), "hydrogen"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<map>());
    TRIAL_PROTOCOL_TEST(*where == variable::map({{ "alpha", 117 }}));
}

void max_map_arithmetic()
{
    variable data = variable::map(
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
    variable data = variable::map(
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
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", variable::array({ 42 }) },
            { "delta", variable::array({ 41 }) },
            { "echo", 3.0 },
            { "foxtrot", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable::array({ 42 }));
}

void max_map_map()
{
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", variable::map({{ "alice", 117 }}) },
            { "delta", variable::array({ 42 }) },
            { "echo", 3.0 },
            { "foxtrot", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable::map({{ "alice" , 117 }}));
}

void run()
{
    max_null();
    max_boolean();
    max_integer();
    max_number();
    max_string();
    max_array_arithmetic();
    max_array_string();
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
    {
        variable first;
        variable second;
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first;
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first;
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first;
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first;
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first;
        variable second = variable::array({ true, 2, 3.0, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first;
        variable second = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
}

void test_boolean()
{
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
    {
        variable first(true);
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second = variable::array({ false, 2, 3.0, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second = variable::array({ true, 2, 3.0, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 1);
    }
    {
        variable first(true);
        variable second = variable::map(
        {
            { "alpha", false },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(true);
        variable second = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 1);
    }
}

void test_integer()
{
    {
        variable first(2);
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
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
    {
        variable first(2);
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(2);
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(2);
        variable second = variable::array({ true, 2, 3.0, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(2);
        variable second = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_number()
{
    {
        variable first(3.0);
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(3.0);
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
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
    {
        variable first(3.0);
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(3.0);
        variable second = variable::array({ true, 2, 3.0, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first(3.0);
        variable second = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_string()
{
    {
        variable first("alpha");
        variable second(true);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first("alpha");
        variable second(2);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first("alpha");
        variable second(3.0);
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first("alpha");
        variable second("alpha");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first("alpha");
        variable second("bravo");
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first("alpha");
        variable second = variable::array({ true, 2, 3.0, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
    {
        variable first("alpha");
        variable second = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 0);
    }
}

void test_array()
{
    {
        variable first = variable::array({ true, 2, 3.0, "alpha" });
        variable second = variable::array({ true, 2, 3.0, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first = variable::array({ true, 2, 3.0, "alpha" });
        variable second = variable::array({ 1, 2, 3, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first = variable::array({ true, 2, 3.0, "alpha" });
        variable second = variable::array({ true, 3.0, 2, "alpha" });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(first.begin(), range.first), 1);
    }
}

void test_map()
{
    {
        variable first = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        variable second = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        auto range = std::mismatch(first.begin(), first.end(), second.begin());
        TRIAL_PROTOCOL_TEST(range.first == first.end());
    }
    {
        variable first = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        variable second = variable::map(
            {
                { "alpha", true },
                { "bravo", 3.0 },
                { "charlie", 2 },
                { "delta", "hydrogen" }
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
    test_array();
    test_map();
}

} // namespace mismatch_suite

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
}

void find_array_boolean()
{
    variable data = variable::array({ false, true, null, 2, 3.0, "alpha" });
    auto where = std::partition_point(data.begin(), data.end(), is_boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_integer()
{
    variable data = variable::array({ 0, 2, null, true, 3.0, "alpha" });
    auto where = std::partition_point(data.begin(), data.end(), is_integer);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_number()
{
    variable data = variable::array({ 0.0, 3.0, null, true, 2, "alpha" });
    auto where = std::partition_point(data.begin(), data.end(), is_number);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_string()
{
    variable data = variable::array({ "", "alpha", null, true, 2, 3.0 });
    auto where = std::partition_point(data.begin(), data.end(), is_string);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
    find_array_boolean();
    find_array_integer();
    find_array_number();
    find_array_string();
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
    auto where = std::remove(data.begin(), data.end(), "bravo");
    TRIAL_PROTOCOL_TEST(where == data.end());
    where = std::remove(data.begin(), data.end(), "alpha");
    TRIAL_PROTOCOL_TEST(where == data.begin());
}

void remove_array_null()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    auto where = std::remove(data.begin(), data.end(), null);
    variable expect = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_boolean()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    auto where = std::remove(data.begin(), data.end(), true);
    variable expect = variable::array({ 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_integer()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    auto where = std::remove(data.begin(), data.end(), 2);
    variable expect = variable::array({ true, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_number()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    auto where = std::remove(data.begin(), data.end(), 3.0);
    variable expect = variable::array({ true, 2, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_array_string()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    auto where = std::remove(data.begin(), data.end(), "alpha");
    variable expect = variable::array({ true, 2, 3.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_boolean()
{
    // Remove by value but keep key order
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    auto where = std::remove(data.begin(), data.end(), false);
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), true);
    variable expect = variable::map(
        {
            { "alpha", 2 },
            { "bravo", 3.0 },
            { "charlie", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_integer()
{
    // Remove by value but keep key order
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    auto where = std::remove(data.begin(), data.end(), 0);
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), 2);
    variable expect = variable::map(
        {
            { "alpha", true },
            { "bravo", 3.0 },
            { "charlie", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_number()
{
    // Remove by value but keep key order
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    auto where = std::remove(data.begin(), data.end(), 0.0);
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), 3.0);
    variable expect = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), where,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void remove_map_string()
{
    // Remove by value but keep key order
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    auto where = std::remove(data.begin(), data.end(), "alpha");
    TRIAL_PROTOCOL_TEST(where == data.end());

    where = std::remove(data.begin(), data.end(), "hydrogen");
    variable expect = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 }
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
    remove_array_null();
    remove_array_boolean();
    remove_array_integer();
    remove_array_number();
    remove_array_string();
    remove_map_boolean();
    remove_map_integer();
    remove_map_number();
    remove_map_string();
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
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ true, 2, 3.0, "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_boolean()
{
    variable data(true);
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ true, 2, 3.0, "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_integer()
{
    variable data(2);
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ true, 2, 3.0, "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_number()
{
    variable data(3.0);
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ true, 2, 3.0, "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_string()
{
    variable data("alpha");
    {
        variable subsequence;
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        // Empty subsequence returns the first entry
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence(true);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(2);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence(3.0);
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence("alpha");
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = variable::array({ true, 2, 3.0, "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "hydrogen" }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void search_array()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
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
    // array - array
    {
        variable subsequence = variable::array({ false });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ true });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = variable::array({ 0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ 2 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = variable::array({ 0.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ 3.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable subsequence = variable::array({ "" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable subsequence = variable::array({ true, 3.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable subsequence = variable::array({ true, 2, "alpha" });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
    {
        variable subsequence = variable::map(
            {
                { "alpha", true }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = variable::map(
            {
                { "bravo", 2 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = variable::map(
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
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
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
    // map - array
    {
        variable subsequence = variable::array({ true });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = variable::array({ true, 2 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = variable::array({ 2 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = variable::array({ true, 3.0 });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
    {
        variable subsequence = variable::map(
            {
                { "alpha", true }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = variable::map(
            {
                { "alpha", true },
                { "bravo", 2 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable subsequence = variable::map(
            {
                { "bravo", 2 }
            });
        auto where = std::search(data.begin(), data.end(),
                                 subsequence.begin(), subsequence.end());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable subsequence = variable::map(
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

void test_array_null()
{
    variable data = variable::array({ null, null, null });
    auto end = std::unique(data.begin(), data.end());
    variable expect = variable::array({ null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_boolean()
{
    variable data = variable::array({ false, true, false, false, true });
    auto end = std::unique(data.begin(), data.end());
    variable expect = variable::array({ false, true, false, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_integer()
{
    variable data = variable::array({ 0, 0, 2, 1, 1 });
    auto end = std::unique(data.begin(), data.end());
    variable expect = variable::array({ 0, 2, 1 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_number()
{
    variable data = variable::array({ 0.0, 0.0, 2.0, 1.0, 1.0 });
    auto end = std::unique(data.begin(), data.end());
    variable expect = variable::array({ 0.0, 2.0, 1.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_arithmetic()
{
    variable data = variable::array({ false, 0, 0.0, 2, 1.0, 1 });
    auto end = std::unique(data.begin(), data.end());
    variable expect = variable::array({ false, 2, 1.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), end,
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array_string()
{
    variable data = variable::array({ "alpha", "alpha", "bravo", "bravo" });
    auto end = std::unique(data.begin(), data.end());
    variable expect = variable::array({ "alpha", "bravo" });
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
    test_array_null();
    test_array_boolean();
    test_array_integer();
    test_array_number();
    test_array_arithmetic();
    test_array_string();
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
}

void find_array()
{
    variable data = variable::array({true, 2, 3.0, "alpha"});
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
}

void find_map()
{
    variable data = variable::map(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
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
        auto where = std::upper_bound(data.begin(), data.end(), "lithium");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
}

void run()
{
    find_null();
    find_boolean();
    find_integer();
    find_number();
    find_string();
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
    binary_search_suite::run();
    copy_suite::run();
    count_suite::run();
    equal_suite::run();
    equal_range_suite::run();
    find_suite::run();
    find_if_suite::run();
    iota_suite::run();
    is_partitioned_suite::run();
    is_sorted_suite::run();
    lower_bound_suite::run();
    max_element_suite::run();
    mismatch_suite::run();
    partition_point_suite::run();
    remove_suite::run();
    search_suite::run();
    unique_suite::run();
    upper_bound_suite::run();

    return boost::report_errors();
}
