///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/std/map.hpp>
#include <trial/protocol/dynamic/std/vector.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// std::vector
//-----------------------------------------------------------------------------

namespace vector_suite
{

void convert_int()
{
    std::vector<int> input = { 1, 2, 3, 4 };
    variable result = convert<variable>(input);

    variable expect = array::make({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_double()
{
    std::vector<double> input = { 1.0, 2.0, 3.0, 4.0 };
    variable result = convert<variable>(input);

    variable expect = array::make({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_string()
{
    std::vector<std::string> input = { "alpha", "bravo" };
    variable result = convert<variable>(input);

    variable expect = array::make({ "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    convert_int();
    convert_double();
    convert_string();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// std::map
//-----------------------------------------------------------------------------

namespace map_suite
{

void convert_int_int()
{
    std::map<int, int> input =
        {
            { 1, 2 },
            { 3, 4 }
        };
    variable result = convert<variable>(input);

    variable expect = map::make(
        {
            { 1, 2 },
            { 3, 4 }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_string_int()
{
    std::map<std::string, int> input =
        {
            { "alpha", 2 },
            { "bravo", 4 }
        };
    variable result = convert<variable>(input);

    variable expect = map::make(
        {
            { "alpha", 2 },
            { "bravo", 4 }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_string_string()
{
    std::map<std::string, std::string> input =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    variable result = convert<variable>(input);

    variable expect = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    convert_int_int();
    convert_string_int();
    convert_string_string();
}

} // namespace map_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    vector_suite::run();
    map_suite::run();

    return boost::report_errors();
}
