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
// std::is_sorted
//-----------------------------------------------------------------------------

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

int main()
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

    return boost::report_errors();
}
