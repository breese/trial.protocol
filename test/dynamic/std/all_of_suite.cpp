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
// std::all_of
//-----------------------------------------------------------------------------

auto is_true = [] (const variable& value) { return bool(value); };

void all_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
}

void all_boolean()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_integer()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(2);
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_number()
{
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_array_boolean()
{
    {
        variable data = array::make();
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ false, false, false });
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, false, true });
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data = array::make({ true, true, true });
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

void all_array_string()
{
    {
        variable data = { "alpha", "bravo", "charlie", "delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is<string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<string>()));
    }
    {
        variable data = { L"alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<string>()));
    }
}

void all_array_wstring()
{
    {
        variable data = { L"alpha", L"bravo", L"charlie", L"delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is<wstring>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<wstring>()));
    }
    {
        variable data = { "alpha", "bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<wstring>()));
    }
}

void all_array_u16string()
{
    {
        variable data = { u"alpha", u"bravo", u"charlie", u"delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is<u16string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<u16string>()));
    }
    {
        variable data = { "alpha", L"bravo", "charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<u16string>()));
    }
}

void all_array_u32string()
{
    {
        variable data = { U"alpha", U"bravo", U"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is<u32string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", U"delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<u32string>()));
    }
    {
        variable data = { "alpha", L"bravo", u"charlie", "delta" };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is<u32string>()));
    }
}

void all_map_boolean()
{
    {
        variable data = map::make();
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", false },
                { "bravo", false },
                { "charlie", false }
            };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", false },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
    }
    {
        variable data =
            {
                { "alpha", true },
                { "bravo", true },
                { "charlie", true }
            };
        TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
    }
}

int main()
{
    all_null();
    all_boolean();
    all_integer();
    all_number();
    all_array_boolean();
    all_array_string();
    all_array_wstring();
    all_array_u16string();
    all_array_u32string();
    all_map_boolean();

    return boost::report_errors();
}
