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
// std::replace
//-----------------------------------------------------------------------------

void replace_null()
{
    // null - boolean
    {
        variable data;
        std::replace(data.begin(), data.end(), variable(), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
}

void replace_boolean()
{
    // boolean - null
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
    // boolean - boolean
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable(false));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable(false));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == false);
    }
    // boolean - integer
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
    // boolean - real
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    // boolean - string
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    // boolean - wstring
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    // boolean - u16string
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    // boolean - u32string
    {
        variable data(true);
        std::replace(data.begin(), data.end(), variable(false), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        std::replace(data.begin(), data.end(), variable(true), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void replace_integer()
{
    // integer - null
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
    // integer - boolean
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
    }
    // integer - integer
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable(22));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable(22));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 22);
    }
    // integer - real
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    // integer - string
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    // integer - wstring
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    // integer - u16string
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    // integer - u32string
    {
        variable data(2);
        std::replace(data.begin(), data.end(), variable(0), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        std::replace(data.begin(), data.end(), variable(2), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void replace_real()
{
    // real - null
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
    // real - boolean
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
    }
    // real - integer
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
    // real - real
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable(33.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable(33.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 33.0);
    }
    // real - string
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    // real - wstring
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    // real - u16string
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    // real - u32string
    {
        variable data(3.0);
        std::replace(data.begin(), data.end(), variable(0.0), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        std::replace(data.begin(), data.end(), variable(3.0), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void replace_string()
{
    // string - null
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
    // string - boolean
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
    }
    // string - integer
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
    // string - real
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    // string - string
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "hydrogen");
    }
    // string - wstring
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    // string - u16string
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    // string - u32string
    {
        variable data("alpha");
        std::replace(data.begin(), data.end(), variable("zulu"), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        std::replace(data.begin(), data.end(), variable("alpha"), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void replace_wstring()
{
    // wstring - null
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
    // wstring - boolean
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
    }
    // wstring - integer
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
    // wstring - real
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    // wstring - string
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    // wstring - wstring
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"hydrogen");
    }
    // wstring - u16string
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    // wstring - u32string
    {
        variable data(L"bravo");
        std::replace(data.begin(), data.end(), variable(L"zulu"), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        std::replace(data.begin(), data.end(), variable(L"bravo"), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void replace_u16string()
{
    // u16string - null
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
    // u16string - boolean
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
    }
    // u16string - integer
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
    // u16string - real
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    // u16string - string
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    // u16string - wstring
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    // u16string - u16string
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"hydrogen");
    }
    // u16string - u32string
    {
        variable data(u"charlie");
        std::replace(data.begin(), data.end(), variable(u"zulu"), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        std::replace(data.begin(), data.end(), variable(u"charlie"), variable(U"delta"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void replace_u32string()
{
    // u32string - null
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
    }
    // u32string - boolean
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable(true));
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
    }
    // u32string - integer
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable(2));
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
    // u32string - real
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable(3.0));
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    // u32string - string
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable("alpha"));
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    // u32string - wstring
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable(L"bravo"));
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    // u32string - u16string
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable(u"charlie"));
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    // u32string - u32string
    {
        variable data(U"delta");
        std::replace(data.begin(), data.end(), variable(U"zulu"), variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        std::replace(data.begin(), data.end(), variable(U"delta"), variable(U"hydrogen"));
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"hydrogen");
    }
}

void replace_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    std::replace(data.begin(), data.end(), variable(false), variable());
    {
        variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    std::replace(data.begin(), data.end(), variable(true), variable());
    {
        variable expect = array::make({ null, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    std::replace(data.begin(), data.end(), variable(2), variable());
    {
        variable expect = array::make({ null, null, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    std::replace(data.begin(), data.end(), variable(3.0), variable());
    {
        variable expect = array::make({ null, null, null, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    std::replace(data.begin(), data.end(), variable("alpha"), variable());
    {
        variable expect = array::make({ null, null, null, null, L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    std::replace(data.begin(), data.end(), variable(L"bravo"), variable());
    {
        variable expect = array::make({ null, null, null, null, null, u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    std::replace(data.begin(), data.end(), variable(u"charlie"), variable());
    {
        variable expect = array::make({ null, null, null, null, null, null, U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    std::replace(data.begin(), data.end(), variable(U"delta"), variable());
    {
        variable expect = array::make({ null, null, null, null, null, null, null });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void replace_array_repeated()
{
    variable data = array::repeat(3, null);
    std::replace(data.begin(), data.end(), variable(), variable(true));
    variable expect = array::repeat(3, true);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

int main()
{
    // Cannot replace with container as new value because iterators will be
    // changed during replacement.

    replace_null();
    replace_boolean();
    replace_integer();
    replace_real();
    replace_string();
    replace_wstring();
    replace_u16string();
    replace_u32string();
    replace_array();
    replace_array_repeated();

    return boost::report_errors();
}
