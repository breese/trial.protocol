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
// std::max_element
//-----------------------------------------------------------------------------

void max_null()
{
    variable data;
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void max_boolean()
{
    variable data(true);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == true);
}

void max_integer()
{
    variable data(1);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 1);
}

void max_number()
{
    variable data(1.0);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 1.0);
}

void max_string()
{
    variable data("alpha");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "alpha");
}

void max_wstring()
{
    variable data(L"bravo");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == L"bravo");
}

void max_u16string()
{
    variable data(u"charlie");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == u"charlie");
}

void max_u32string()
{
    variable data(U"delta");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == U"delta");
}

void max_array_arithmetic()
{
    variable data = array::make({false, 2, 3.0});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
}

void max_array_string()
{
    variable data = array::make({"alpha", "bravo", "charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "charlie");
}

void max_array_wstring()
{
    variable data = array::make({L"alpha", L"bravo", L"charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == L"charlie");
}

void max_array_u16string()
{
    variable data = array::make({u"alpha", u"bravo", u"charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == u"charlie");
}

void max_array_u32string()
{
    variable data = array::make({U"alpha", U"bravo", U"charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == U"charlie");
}

void max_array_value()
{
    variable data = array::make({true, 2, 3.0, "alpha", "bravo", "charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "charlie");
}

void max_array_array()
{
    variable data = array::make({true, 2, 3.0, array::make({ 42 }), array::make({ 41 }), "alpha"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<array>());
    TRIAL_PROTOCOL_TEST(*where == array::make({ 42 }));
}

void max_array_map()
{
    variable data = array::make({true, 2, 3.0, map::make({{ "alpha", 117 }}), array::make({ 42 }), "hydrogen"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<map>());
    TRIAL_PROTOCOL_TEST(*where == map::make({{ "alpha", 117 }}));
}

void max_map_arithmetic()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
}

void max_map_value()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "hydrogen");
}

void max_map_array()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", array::make({ 42 }) },
            { "delta", array::make({ 41 }) },
            { "echo", 3.0 },
            { "foxtrot", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == array::make({ 42 }));
}

void max_map_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", map::make({{ "alice", 117 }}) },
            { "delta", array::make({ 42 }) },
            { "echo", 3.0 },
            { "foxtrot", "hydrogen" }
        });
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == map::make({{ "alice" , 117 }}));
}

int main()
{
    max_null();
    max_boolean();
    max_integer();
    max_number();
    max_string();
    max_wstring();
    max_u16string();
    max_u32string();
    max_array_arithmetic();
    max_array_string();
    max_array_wstring();
    max_array_u16string();
    max_array_u32string();
    max_array_value();
    max_array_array();
    max_array_map();
    max_map_arithmetic();
    max_map_value();
    max_map_array();
    max_map_map();

    return boost::report_errors();
}
