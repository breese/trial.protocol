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
// std::move
//-----------------------------------------------------------------------------

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

int main()
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

    return boost::report_errors();
}
