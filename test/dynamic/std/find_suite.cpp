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
// std::find
//-----------------------------------------------------------------------------

void find_null()
{
    variable data;
    // Cannot iterate over null, so nothing is found
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), null) == data.end());
}

void find_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), false) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), true) != data.end());
}

void find_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2) == data.end());
}

void find_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0.0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1.0) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2.0) == data.end());
}

void find_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "alpha") != data.end());
}

void find_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"bravo") != data.end());
}

void find_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"charlie") != data.end());
}

void find_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"zulu") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"delta") != data.end());
}

void find_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), false) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), true)),
                              0);

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 42) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), 2)),
                              1);

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 43.0) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), 3.0)),
                              2);

    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "alpha")),
                              3);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), L"") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), L"bravo")),
                              4);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), u"") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), u"charlie")),
                              5);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), U"") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), U"delta")),
                              6);
}

void find_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences value, not key
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "alpha") == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "hydrogen")),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "helium")),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find(data.begin(), data.end(), "lithium")),
                              2);
}

void find_key_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences key
    TRIAL_PROTOCOL_TEST(std::find(data.key_begin(), data.key_end(), "hydrogen") == data.key_end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(),
                                            std::find(data.key_begin(), data.key_end(), "alpha")),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(),
                                            std::find(data.key_begin(), data.key_end(), "bravo")),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(),
                                            std::find(data.key_begin(), data.key_end(), "charlie")),
                              2);
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
    find_array();
    find_map();
    find_key_map();

    return boost::report_errors();
}
