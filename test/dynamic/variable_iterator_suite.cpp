///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <trial/protocol/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// std::begin
//-----------------------------------------------------------------------------

namespace begin_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(data.begin() == data.end());
}

void test_const_null()
{
    const variable data;
    TRIAL_PROTOCOL_TEST(data.begin() == data.end());
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_boolean()
{
    const variable data(true);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_integer()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_integer()
{
    const variable data(0);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_number()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_number()
{
    const variable data(0.0);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_string()
{
    const variable data("alpha");
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_array()
{
    variable::array_type array = { true, 1, 2.0, "alpha" };
    variable data(array);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_array()
{
    variable::array_type array = { true, 1, 2.0, "alpha" };
    const variable data(array);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_map()
{
    variable data = variable::map(
        {
            {"key", "alpha"}
        });
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_map()
{
    const variable data = variable::map(
        {
            {"key", "alpha"}
        });
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void run()
{
    test_null();
    test_const_null();
    test_boolean();
    test_const_boolean();
    test_integer();
    test_const_integer();
    test_number();
    test_const_number();
    test_string();
    test_const_string();
    test_array();
    test_const_array();
    test_map();
    test_const_map();
}

} // namespace begin_suite

//-----------------------------------------------------------------------------
// operator++()
//-----------------------------------------------------------------------------

namespace pre_increment_suite
{

void test_array()
{
    variable::array_type array = { true, 1, 2.0, "alpha" };
    variable data(array);
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(*where == variable(true));
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable(1));
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable(2.0));
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void run()
{
    test_array();
}

} // namespace pre_increment_suite

//-----------------------------------------------------------------------------
// operator++(int)
//-----------------------------------------------------------------------------

namespace post_increment_suite
{

void test_array()
{
    variable::array_type array = { true, 1, 2.0, "alpha" };
    variable data(array);
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(*where == variable(true));
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(true));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable(1));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(1));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable(2.0));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(2.0));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable("alpha"));
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void run()
{
    test_array();
}

} // namespace post_increment_suite

//-----------------------------------------------------------------------------
// std::distance
//-----------------------------------------------------------------------------

namespace distance_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 0);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_integer()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_number()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_array()
{
    variable::array_type array = { true, 1, 2.0, "alpha" };
    variable data(array);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 4);
}

void test_array_nulls()
{
    variable::array_type array = { variable::null, variable::null, variable::null };
    variable data(array);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 3);
}

void test_map()
{
    variable data = variable::map(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 3);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_array_nulls();
    test_map();
}

} // namespace distance_suite

//-----------------------------------------------------------------------------
// Range-based for loop
//-----------------------------------------------------------------------------

namespace range_for_suite
{

void test_null()
{
    variable data;
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 0);
}

void test_boolean()
{
    variable data(true);
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void test_integer()
{
    variable data(0);
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void test_number()
{
    variable data(0.0);
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void test_string()
{
    variable data("alpha");
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 5);
}

void test_array()
{
    variable::array_type array = { true, 1, 2.0, "alpha" };
    variable data(array);
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1 + 1 + 1 + 5);
}

void test_array_nulls()
{
    variable::array_type array = { variable::null, variable::null, variable::null };
    variable data(array);
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 0 + 0 + 0);
}

void test_map()
{
    variable data = variable::map(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 8 + 6 + 7);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_array_nulls();
}

} // namespace range_for_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    begin_suite::run();
    pre_increment_suite::run();
    post_increment_suite::run();
    distance_suite::run();
    range_for_suite::run();

    return boost::report_errors();
}
