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
#include <functional>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::lexicographical_compare
//-----------------------------------------------------------------------------

void compare_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end()));
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end(),
                                                      std::less<variable>()));

    // null - boolean
    {
        variable other(true);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // null - integer
    {
        variable other(2);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // null - real
    {
        variable other(3.0);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // null - string
    {
        variable other("alpha");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // null - wstring
    {
        variable other(L"bravo");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // null - u16string
    {
        variable other(u"charlie");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // null - u32string
    {
        variable other(U"delta");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
}

void compare_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end()));
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end(),
                                                      std::less<variable>()));
    // boolean - null
    {
        // nullable is an empty container and an empty range is lexicographically
        // less than a non-empty range.

        variable other;
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // boolean - boolean
    {
        variable other(false);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // boolean - integer
    {
        variable other(2);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // boolean - real
    {
        variable other(3.0);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // boolean - string
    {
        variable other("alpha");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // boolean - wstring
    {
        variable other(L"bravo");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // boolean - u16string
    {
        variable other(u"charlie");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // boolean - u32string
    {
        variable other(U"delta");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
}

void compare_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end()));
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end(),
                                                      std::less<variable>()));
    // integer - null
    {
        // See boolean - null comparison

        variable other;
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // integer - boolean
    {
        variable other(true);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // integer - integer
    {
        variable smaller(0);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger(22);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                          larger.begin(), larger.end()));
    }
    // integer - real
    {
        variable smaller(0.0);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger(3.0);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
    // integer - string
    {
        variable other("alpha");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // integer - wstring
    {
        variable other(L"bravo");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // integer - u16string
    {
        variable other(u"charlie");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // integer - u32string
    {
        variable other(U"delta");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
}

void compare_real()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end()));
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end(),
                                                      std::less<variable>()));
    // real - null
    {
        // See boolean - null comparison

        variable other;
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // real - boolean
    {
        variable other(true);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // real - integer
    {
        variable smaller(0);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger(22);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                          larger.begin(), larger.end()));
    }
    // real - real
    {
        variable smaller(0.0);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger(33.0);
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
    // real - string
    {
        variable other("alpha");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // real - wstring
    {
        variable other(L"bravo");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // real - u16string
    {
        variable other(u"charlie");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // real - u32string
    {
        variable other(U"delta");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
}

void compare_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end()));
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end(),
                                                      std::less<variable>()));
    // string - null
    {
        // See boolean - null comparison

        variable other;
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // string - boolean
    {
        variable other(true);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // string - integer
    {
        variable other(2);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // string - real
    {
        variable other(3.0);
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          other.begin(), other.end()));
    }
    // string - string
    {
        variable other("zulu");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // string - wstring
    {
        variable other(L"bravo");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // string - u16string
    {
        variable other(u"charlie");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
    // string - u32string
    {
        variable other(U"delta");
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         other.begin(), other.end()));
    }
}

void compare_array_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end()));
    TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                      data.begin(), data.end(),
                                                      std::less<variable>()));

    // boolean
    {
        variable smaller = array::make({ null, false, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
    }
    // integer
    {
        variable smaller = array::make({ null, true, 0, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger = array::make({ null, true, 22, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
    // real
    {
        variable smaller = array::make({ null, true, 2, 0.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger = array::make({ null, true, 2, 33.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
    // string
    {
        variable smaller = array::make({ null, true, 2, 3.0, "", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger = array::make({ null, true, 2, 3.0, "zulu", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
    // wstring
    {
        variable smaller = array::make({ null, true, 2, 3.0, "alpha", L"", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger = array::make({ null, true, 2, 3.0, "alpha", L"zulu", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
    // u16string
    {
        variable smaller = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"", U"delta" });
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"zulu", U"delta" });
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
    // u32string
    {
        variable smaller = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"" });
        TRIAL_PROTOCOL_TEST(!std::lexicographical_compare(data.begin(), data.end(),
                                                          smaller.begin(), smaller.end()));
        variable larger = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"zulu" });
        TRIAL_PROTOCOL_TEST(std::lexicographical_compare(data.begin(), data.end(),
                                                         larger.begin(), larger.end()));
    }
}

int main()
{
    compare_null();
    compare_boolean();
    compare_integer();
    compare_real();
    compare_string();
    compare_array_array();

    return boost::report_errors();
}
