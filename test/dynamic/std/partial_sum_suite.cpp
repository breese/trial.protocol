///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <numeric>
#include <iterator>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::partial_sum
//-----------------------------------------------------------------------------

void sum_null()
{
    variable data;
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void sum_boolean()
{
    variable data(true);
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 1 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_integer()
{
    variable data(2);
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 2 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_number()
{
    variable data(3.0);
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 3.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_string()
{
    {
        variable data("alpha");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data(L"bravo");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ L"bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data(u"charlie");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ u"charlie" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data(U"delta");
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void sum_array_null()
{
    variable data = array::make({ null, null, null });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ null, null, null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_boolean()
{
    variable data = array::make({ true, false, true });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_integer()
{
    variable data = array::make({ 1, 20, 300 });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 1, 21, 321 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_number()
{
    variable data = array::make({ 1.0, 20.0, 300.0 });
    std::vector<variable> result;
    std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
    variable expect = array::make({ 1.0, 21.0, 321.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void sum_array_string()
{
    {
        variable data = array::make({ "one", "two", "three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ "one", "onetwo", "onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ L"one", L"two", L"three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ L"one", L"onetwo", L"onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ u"one", u"two", u"three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ u"one", u"onetwo", u"onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ U"one", U"two", U"three" });
        std::vector<variable> result;
        std::partial_sum(data.begin(), data.end(), std::back_inserter(result));
        variable expect = array::make({ U"one", U"onetwo", U"onetwothree" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void fail_array_string()
{
    variable data = array::make({ "alpha", L"bravo", u"charlie", U"delta" });
    std::vector<variable> result;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(std::partial_sum(data.begin(), data.end(), std::back_inserter(result)),
                                    error,
                                    "incompatible type");
}

int main()
{
    sum_null();
    sum_boolean();
    sum_integer();
    sum_number();
    sum_string();
    sum_array_null();
    sum_array_boolean();
    sum_array_integer();
    sum_array_number();
    sum_array_string();
    fail_array_string();

    return boost::report_errors();
}
