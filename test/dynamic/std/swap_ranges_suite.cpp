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
// std::swap_ranges
//-----------------------------------------------------------------------------

void swap_null()
{
    // Nothing is swapped because null is an empty container

    // null - null
    {
        variable data;
        variable other;
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
    }
    // null - boolean
    {
        variable data;
        variable other(true);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.begin());
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
    }
}

void swap_boolean()
{
    // boolean - null
    {
        // Fails because null is an empty array, and no check against other.end()
        // is performed by std::swap_ranges (pre-C++17)
    }
    // boolean - boolean
    {
        variable data(true);
        variable other(false);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == false);
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(other == true);
    }
    // boolean - integer
    {
        variable data(true);
        variable other(2);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(other == true);
    }
    // boolean - real
    {
        variable data(true);
        variable other(3.0);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(other == true);
    }
    // boolean - string
    {
        variable data(true);
        variable other("alpha");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(other == true);
    }
    // boolean - wstring
    {
        variable data(true);
        variable other(L"bravo");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(other == true);
    }
    // boolean - u16string
    {
        variable data(true);
        variable other(u"charlie");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(other == true);
    }
    // boolean - u32string
    {
        variable data(true);
        variable other(U"delta");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(other == true);
    }
}

void swap_integer()
{
    // integer - null
    {
        // See swap_boolean
    }
    // integer - boolean
    {
        variable data(2);
        variable other(true);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(other == 2);
    }
    // integer - integer
    {
        variable data(2);
        variable other(22);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 22);
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(other == 2);
    }
    // integer - real
    {
        variable data(2);
        variable other(3.0);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(other == 2);
    }
    // integer - string
    {
        variable data(2);
        variable other("alpha");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(other == 2);
    }
    // integer - wstring
    {
        variable data(2);
        variable other(L"bravo");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(other == 2);
    }
    // integer - u16string
    {
        variable data(2);
        variable other(u"charlie");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(other == 2);
    }
    // integer - u32string
    {
        variable data(2);
        variable other(U"delta");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(other == 2);
    }
}

void swap_real()
{
    // real - null
    {
        // See swap_boolean
    }
    // real - boolean
    {
        variable data(3.0);
        variable other(true);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(other == 3.0);
    }
    // real - integer
    {
        variable data(3.0);
        variable other(2);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(other == 3.0);
    }
    // real - real
    {
        variable data(3.0);
        variable other(33.0);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 33.0);
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(other == 3.0);
    }
    // real - string
    {
        variable data(3.0);
        variable other("alpha");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(other == 3.0);
    }
    // real - wstring
    {
        variable data(3.0);
        variable other(L"bravo");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(other == 3.0);
    }
    // real - u16string
    {
        variable data(3.0);
        variable other(u"charlie");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(other == 3.0);
    }
    // real - u32string
    {
        variable data(3.0);
        variable other(U"delta");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(other == 3.0);
    }
}

void swap_string()
{
    // string - null
    {
        // See swap_boolean
    }
    // string - boolean
    {
        variable data("alpha");
        variable other(true);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(other == "alpha");
    }
    // string - integer
    {
        variable data("alpha");
        variable other(2);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(other == "alpha");
    }
    // string - real
    {
        variable data("alpha");
        variable other(3.0);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(other == "alpha");
    }
    // string - string
    {
        variable data("alpha");
        variable other("zulu");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "zulu");
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(other == "alpha");
    }
    // string - wstring
    {
        variable data("alpha");
        variable other(L"bravo");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(other == "alpha");
    }
    // string - u16string
    {
        variable data("alpha");
        variable other(u"charlie");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(other == "alpha");
    }
    // string - u32string
    {
        variable data("alpha");
        variable other(U"delta");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(other == "alpha");
    }
}

void swap_wstring()
{
    // wstring - null
    {
        // See swap_boolean
    }
    // wstring - boolean
    {
        variable data(L"bravo");
        variable other(true);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(other == L"bravo");
    }
    // wstring - integer
    {
        variable data(L"bravo");
        variable other(2);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(other == L"bravo");
    }
    // wstring - real
    {
        variable data(L"bravo");
        variable other(3.0);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(other == L"bravo");
    }
    // wstring - string
    {
        variable data(L"bravo");
        variable other("alpha");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(other == L"bravo");
    }
    // wstring - wstring
    {
        variable data(L"bravo");
        variable other(L"zulu");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"zulu");
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(other == L"bravo");
    }
    // wstring - u16string
    {
        variable data(L"bravo");
        variable other(u"charlie");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(other == L"bravo");
    }
    // wstring - u32string
    {
        variable data(L"bravo");
        variable other(U"delta");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(other == L"bravo");
    }
}

void swap_u16string()
{
    // u16string - null
    {
        // See swap_boolean
    }
    // u16string - boolean
    {
        variable data(u"charlie");
        variable other(true);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(other == u"charlie");
    }
    // u16string - integer
    {
        variable data(u"charlie");
        variable other(2);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(other == u"charlie");
    }
    // u16string - real
    {
        variable data(u"charlie");
        variable other(3.0);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(other == u"charlie");
    }
    // u16string - string
    {
        variable data(u"charlie");
        variable other("alpha");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(other == u"charlie");
    }
    // u16string - wstring
    {
        variable data(u"charlie");
        variable other(L"bravo");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(other == u"charlie");
    }
    // u16string - u16string
    {
        variable data(u"charlie");
        variable other(u"zulu");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"zulu");
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(other == u"charlie");
    }
    // u16string - u32string
    {
        variable data(u"charlie");
        variable other(U"delta");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"delta");
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(other == u"charlie");
    }
}

void swap_u32string()
{
    // u32string - null
    {
        // See swap_boolean
    }
    // u32string - boolean
    {
        variable data(U"delta");
        variable other(true);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(data == true);
        TRIAL_PROTOCOL_TEST(other.is<u32string>());
        TRIAL_PROTOCOL_TEST(other == U"delta");
    }
    // u32string - integer
    {
        variable data(U"delta");
        variable other(2);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(data == 2);
        TRIAL_PROTOCOL_TEST(other.is<u32string>());
        TRIAL_PROTOCOL_TEST(other == U"delta");
    }
    // u32string - real
    {
        variable data(U"delta");
        variable other(3.0);
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(data == 3.0);
        TRIAL_PROTOCOL_TEST(other.is<u32string>());
        TRIAL_PROTOCOL_TEST(other == U"delta");
    }
    // u32string - string
    {
        variable data(U"delta");
        variable other("alpha");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(data == "alpha");
        TRIAL_PROTOCOL_TEST(other.is<u32string>());
        TRIAL_PROTOCOL_TEST(other == U"delta");
    }
    // u32string - wstring
    {
        variable data(U"delta");
        variable other(L"bravo");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
        TRIAL_PROTOCOL_TEST(other.is<u32string>());
        TRIAL_PROTOCOL_TEST(other == U"delta");
    }
    // u32string - u16string
    {
        variable data(U"delta");
        variable other(u"charlie");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
        TRIAL_PROTOCOL_TEST(other.is<u32string>());
        TRIAL_PROTOCOL_TEST(other == U"delta");
    }
    // u32string - u32string
    {
        variable data(U"delta");
        variable other(U"zulu");
        auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
        TRIAL_PROTOCOL_TEST(where == other.end());
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(data == U"zulu");
        TRIAL_PROTOCOL_TEST(other.is<u32string>());
        TRIAL_PROTOCOL_TEST(other == U"delta");
    }
}

void swap_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    variable other = array::make({ U"delta", u"charlie", L"bravo", "alpha", 3.0, 2, true, null });
    auto where = std::swap_ranges(data.begin(), data.end(), other.begin());
    TRIAL_PROTOCOL_TEST(where == other.end());
    {
        TRIAL_PROTOCOL_TEST(data.is<array>());
        variable expect = array::make({ U"delta", u"charlie", L"bravo", "alpha", 3.0, 2, true, null });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        TRIAL_PROTOCOL_TEST(other.is<array>());
        variable expect = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(other.begin(), other.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_array_partial()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    variable other = array::make({ U"delta", u"charlie", L"bravo", "alpha", 3.0, 2, true, null });
    auto where = std::swap_ranges(++data.begin(), --data.end(), ++other.begin());
    TRIAL_PROTOCOL_TEST(where == --other.end());
    {
        TRIAL_PROTOCOL_TEST(data.is<array>());
        variable expect = array::make({ null, u"charlie", L"bravo", "alpha", 3.0, 2, true, U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        TRIAL_PROTOCOL_TEST(other.is<array>());
        variable expect = array::make({ U"delta", true, 2, 3.0, "alpha", L"bravo", u"charlie", null });
        TRIAL_PROTOCOL_TEST_ALL_WITH(other.begin(), other.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

int main()
{
    swap_null();
    swap_boolean();
    swap_integer();
    swap_real();
    swap_string();
    swap_wstring();
    swap_u16string();
    swap_u32string();

    swap_array();
    swap_array_partial();

    return boost::report_errors();
}
