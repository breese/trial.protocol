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
// std::equal
//-----------------------------------------------------------------------------

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
    test_array_string();
    test_array_wstring();
    test_array_u16string();
    test_array_u32string();

    return boost::report_errors();
}
