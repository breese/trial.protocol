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
// std::partition_point
//-----------------------------------------------------------------------------

void find_null()
{
    variable data;
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_boolean()
{
    variable data(true);
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_integer()
{
    variable data(2);
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_number()
{
    variable data(3.0);
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_string()
{
    variable data("alpha");
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_wstring()
{
    variable data(L"bravo");
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_u16string()
{
    variable data(u"charlie");
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void find_u32string()
{
    variable data(U"delta");
    {
        auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<number>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
}

void find_array_boolean()
{
    variable data = array::make({ false, true, null, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is<boolean>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_integer()
{
    variable data = array::make({ 0, 2, null, true, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is<integer>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_number()
{
    variable data = array::make({ 0.0, 3.0, null, true, 2, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is<number>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_string()
{
    variable data = array::make({ "", "alpha", null, true, 2, 3.0, L"bravo", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is<string>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_wstring()
{
    variable data = array::make({ L"", L"bravo", null, true, 2, 3.0, "alpha", u"charlie", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is<wstring>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_u16string()
{
    variable data = array::make({ u"", u"charlie", null, true, 2, 3.0, "alpha", L"bravo", U"delta" });
    auto where = std::partition_point(data.begin(), data.end(), is<u16string>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void find_array_u32string()
{
    variable data = array::make({ U"", U"delta", null, true, 2, 3.0, "alpha", L"bravo", u"charlie" });
    auto where = std::partition_point(data.begin(), data.end(), is<u32string>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

int main()
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

    return boost::report_errors();
}
