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
// std::any_of
//-----------------------------------------------------------------------------

auto is_true = [] (const variable& value) { return bool(value); };

void any_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
}

void any_boolean()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
}

void any_array_boolean()
{
    {
        variable data = array::make();
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ false, false, false });
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, false, true });
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, true, true });
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
}

void any_array_string()
{
    {
        variable data = { "alpha", "bravo", "charlie", "delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<string>()));
    }
    {
        variable data = { L"alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is<string>()));
    }
}

void any_array_wstring()
{
    {
        variable data = { L"alpha", L"bravo", L"charlie", L"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<wstring>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<wstring>()));
    }
    {
        variable data = { "alpha", "bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is<wstring>()));
    }
}

void any_array_u16string()
{
    {
        variable data = { u"alpha", u"bravo", u"charlie", u"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<u16string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<u16string>()));
    }
    {
        variable data = { "alpha", L"bravo", "charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is<u16string>()));
    }
}

void any_array_u32string()
{
    {
        variable data = { U"alpha", U"bravo", U"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<u32string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is<u32string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", "delta" };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is<u32string>()));
    }
}

void any_map_boolean()
{
    {
        variable data = map::make();
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", false },
                { "bravo", false },
                { "charlie", false }
            };
        TRIAL_PROTOCOL_TEST(!std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", false },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", true },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(std::any_of(data.begin(), data.end(), is_true));
    }
}

int main()
{
    any_null();
    any_boolean();
    any_array_boolean();
    any_array_string();
    any_array_wstring();
    any_array_u16string();
    any_array_u32string();
    any_map_boolean();

    return boost::report_errors();
}
