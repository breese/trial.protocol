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
// std::copy_backward
//-----------------------------------------------------------------------------

void copy_null_to_array()
{
    variable data;
    variable result = array::repeat(0, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void copy_boolean_to_array()
{
    variable data(true);
    variable result = array::repeat(1, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == true);
}

void copy_integer_to_array()
{
    variable data(2);
    variable result = array::repeat(1, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 2);
}

void copy_real_to_array()
{
    variable data(3.0);
    variable result = array::repeat(1, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == 3.0);
}

void copy_string_to_array()
{
    variable data("alpha");
    variable result = array::repeat(1, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == "alpha");
}

void copy_wstring_to_array()
{
    variable data(L"bravo");
    variable result = array::repeat(1, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == L"bravo");
}

void copy_u16string_to_array()
{
    variable data(u"charlie");
    variable result = array::repeat(1, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == u"charlie");
}

void copy_u32string_to_array()
{
    variable data(U"delta");
    variable result = array::repeat(1, null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST(result[0] == U"delta");
}

void copy_array_to_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    variable result = array::repeat(data.size(), null);
    std::copy_backward(data.begin(), data.end(), result.end());
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

int main()
{
    copy_null_to_array();
    copy_boolean_to_array();
    copy_integer_to_array();
    copy_real_to_array();
    copy_string_to_array();
    copy_wstring_to_array();
    copy_u16string_to_array();
    copy_u32string_to_array();
    copy_array_to_array();

    return boost::report_errors();
}
