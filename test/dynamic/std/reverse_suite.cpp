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
// std::reverse
//-----------------------------------------------------------------------------

void reverse_null()
{
    variable data;
    std::reverse(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(data == null);
}

void reverse_boolean()
{
    variable data = true;
    std::reverse(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(data == true);
}

void reverse_integer()
{
    variable data = 2;
    std::reverse(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(data == 2);
}

void reverse_number()
{
    variable data = 3.0;
    std::reverse(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(data == 3.0);
}

void reverse_string()
{
    {
        variable data = "alpha";
        std::reverse(data.begin(), data.end());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    {
        variable data = L"bravo";
        std::reverse(data.begin(), data.end());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    {
        variable data = u"charlie";
        std::reverse(data.begin(), data.end());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    {
        variable data = U"delta";
        std::reverse(data.begin(), data.end());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void reverse_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    std::reverse(data.begin(), data.end());
    variable expect = array::make({ U"delta", u"charlie", L"bravo", "alpha", 3.0, 2, true, null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void reverse_map()
{
    variable data =
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 3.0 },
            { "echo", "hydrogen" },
            { "foxtrot", L"helium" },
            { "golf", u"lithium" },
            { "hotel", U"beryllium" }
        };
    std::reverse(data.begin(), data.end());
    variable expect =
        {
            { "alpha", U"beryllium" },
            { "bravo", u"lithium" },
            { "charlie", L"helium" },
            { "delta", "hydrogen" },
            { "echo", 3.0 },
            { "foxtrot", 2 },
            { "golf", true },
            { "hotel", null }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

int main()
{
    reverse_null();
    reverse_boolean();
    reverse_integer();
    reverse_number();
    reverse_string();
    reverse_array();
    reverse_map();

    return boost::report_errors();
}
