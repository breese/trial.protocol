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
#include <trial/dynamic/functional.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::is_partitioned
//-----------------------------------------------------------------------------

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_number()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_boolean()
{
    variable data = array::make({ true, false, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_integer()
{
    variable data = array::make({ 3, 2, 4 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_number()
{
    variable data = array::make({ 3.0, 2.0, 4.0 });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_string()
{
    variable data = array::make({ "bravo", "alpha", "charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_wstring()
{
    variable data = array::make({ L"bravo", L"alpha", L"charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_u16string()
{
    variable data = array::make({ u"bravo", u"alpha", u"charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_u32string()
{
    variable data = array::make({ U"bravo", U"alpha", U"charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
}

void test_array_arithmetic()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), false);
    }
    {
        variable data = array::make({ 2, 3.0, "alpha", L"bravo", u"charlie", U"delta", true });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), false);
    }
    {
        variable data = array::make({ 3.0, "alpha", L"bravo", u"charlie", U"delta", true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), false);
    }
    {
        variable data = array::make({ "alpha", L"bravo", u"charlie", U"delta", true, 2, 3.0 });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), false);
    }
    {
        variable data = array::make({ L"bravo", u"charlie", U"delta", true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), false);
    }
    {
        variable data = array::make({ u"charlie", U"delta", true, 2, 3.0, "alpha", L"bravo" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), false);
    }
    {
        variable data = array::make({ U"delta", true, 2, 3.0, "alpha", L"bravo", u"charlie" });
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<number>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), false);
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
    }
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
    test_array_boolean();
    test_array_integer();
    test_array_number();
    test_array_string();
    test_array_wstring();
    test_array_u16string();
    test_array_u32string();
    test_array_arithmetic();

    return boost::report_errors();
}
