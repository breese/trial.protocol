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
// std::find_if
//-----------------------------------------------------------------------------

void find_null()
{
    variable data;
    // Cannot iterate over null, so nothing is found
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == null; }) == data.end());
}

void find_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == false; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == true; }) != data.end());
}

void find_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 0; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 1; }) != data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 2; }) == data.end());
}

void find_real()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 0.0; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 1.0; }) != data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 2.0; }) == data.end());
}

void find_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == ""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "alpha"; }) != data.end());
}

void find_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L"zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L"bravo"; }) != data.end());
}

void find_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u"zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u"charlie"; }) != data.end());
}

void find_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U""; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U"zulu"; }) == data.end());
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U"delta"; }) != data.end());
}

void find_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == false; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == true; })),
                              0);

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 42; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == 2; })),
                              1);

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == 43.0; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == 3.0; })),
                              2);

    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == ""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "alpha"; })),
                              3);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == L""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == L"bravo"; })),
                              4);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == u""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == u"charlie"; })),
                              5);
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == U""; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == U"delta"; })),
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
    TRIAL_PROTOCOL_TEST(std::find_if(data.begin(), data.end(),
                                     [] (const variable& value) { return value == "alpha"; }) == data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "hydrogen"; })),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "helium"; })),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(),
                                            std::find_if(data.begin(), data.end(),
                                                         [] (const variable& value) { return value == "lithium"; })),
                              2);
}

int main()
{
    find_null();
    find_boolean();
    find_integer();
    find_real();
    find_string();
    find_wstring();
    find_u16string();
    find_u32string();
    find_array();
    find_map();

    return boost::report_errors();
}
