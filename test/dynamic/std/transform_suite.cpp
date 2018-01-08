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
// std::transform
//-----------------------------------------------------------------------------

auto identity = [] (const variable& value) -> variable { return value; };

void transform_null()
{
    variable data;
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void transform_boolean()
{
    variable data(true);
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<boolean>());
    TRIAL_PROTOCOL_TEST(data == true);
}

void transform_integer()
{
    variable data(2);
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<integer>());
    TRIAL_PROTOCOL_TEST(data == 2);
}

void transform_real()
{
    variable data(3.0);
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<real>());
    TRIAL_PROTOCOL_TEST(data == 3.0);
}

void transform_string()
{
    variable data("alpha");
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<string>());
    TRIAL_PROTOCOL_TEST(data == "alpha");
}

void transform_wstring()
{
    variable data(L"bravo");
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<wstring>());
    TRIAL_PROTOCOL_TEST(data == L"bravo");
}

void transform_u16string()
{
    variable data(u"charlie");
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<u16string>());
    TRIAL_PROTOCOL_TEST(data == u"charlie");
}

void transform_u32string()
{
    variable data(U"delta");
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<u32string>());
    TRIAL_PROTOCOL_TEST(data == U"delta");
}

void transform_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = std::transform(data.begin(), data.end(), data.begin(), identity);
    TRIAL_PROTOCOL_TEST(where == data.end());
    TRIAL_PROTOCOL_TEST(data.is<array>());
    variable expect = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

int main()
{
    transform_null();
    transform_boolean();
    transform_integer();
    transform_real();
    transform_string();
    transform_wstring();
    transform_u16string();
    transform_u32string();
    transform_array();

    return boost::report_errors();
}
