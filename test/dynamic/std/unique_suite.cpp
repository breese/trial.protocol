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
// std::unique
//-----------------------------------------------------------------------------

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

int main()
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

    return boost::report_errors();
}
