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
// std::count_if
//-----------------------------------------------------------------------------

void count_null()
{
    variable data;
    // Cannot iterate over null, so nothing is counted
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == null; }),
                              0);
}

void count_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == false; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == true; }),
                              1);
}

void count_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 0; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 2; }),
                              0);
}

void count_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 0.0; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1.0; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 2.0; }),
                              0);
}

void count_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == ""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "alpha"; }),
                              1);
}

void count_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"bravo"; }),
                              1);
}

void count_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"charlie"; }),
                              1);
}

void count_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U""; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"delta"; }),
                              1);
}

void count_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == true; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 2; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 3.0; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "alpha"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"bravo"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"charlie"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"delta"; }),
                              1);

    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == false; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 20; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 300.0; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == L"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == u"zulu"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == U"zulu"; }),
                              0);
}

void count_array_arithmetic()
{
    variable data = array::make({ true, 1, 1.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == true; }),
                              3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1; }),
                              3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == 1.0; }),
                              3);
}

void count_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences value, not key
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "alpha"; }),
                              0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "hydrogen"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "helium"; }),
                              1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count_if(data.begin(), data.end(),
                                            [] (const variable& value) { return value == "lithium"; }),
                              1);
}

int main()
{
    count_null();
    count_boolean();
    count_integer();
    count_number();
    count_string();
    count_wstring();
    count_u16string();
    count_u32string();
    count_array();
    count_array_arithmetic();
    count_map();

    return boost::report_errors();
}
