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
#include <trial/protocol/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// std::adjacent_find
//-----------------------------------------------------------------------------

namespace adjacent_find_suite
{

void test_null()
{
    variable data;
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_array_integer()
{
    variable data = variable::array({ 0, 1, 2, 3, 40, 40, 41, 41, 5 });
    auto where = std::adjacent_find(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 6);
    where = std::adjacent_find(++where, data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void run()
{
    test_null();
    test_array_integer();
}

} // namespace adjacent_find_suite

//-----------------------------------------------------------------------------
// std::all_of
//-----------------------------------------------------------------------------

namespace all_of_suite
{

auto is_true = [] (const variable& value) { return bool(value); };

void test_array_boolean()
{
    variable data = variable::array({ true, true, true });
    TRIAL_PROTOCOL_TEST(std::all_of(data.begin(), data.end(), is_true));
}

void fail_array_boolean()
{
    variable data = variable::array({ true, false, true });
    TRIAL_PROTOCOL_TEST(!std::all_of(data.begin(), data.end(), is_true));
}

void run()
{
    test_array_boolean();
    fail_array_boolean();
}

} // namespace all_of_suite

//-----------------------------------------------------------------------------
// std::count
//-----------------------------------------------------------------------------

namespace count_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0), 0);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 1);
}

void test_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2), 0);
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 0.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1.0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2.0), 0);
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("alpha")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), std::string("bravo")), 0);
}

void test_array()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 2), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 3), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "alpha"), 1);

    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 42), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 42.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), ""), 0);
}

void test_array_arithmetic()
{
    variable data = variable::array({ true, 1, 1.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), true), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), 1.0), 3);
}

void test_map()
{
    variable data = variable::map(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    // Iterator dereferences value, not key
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "helium"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::count(data.begin(), data.end(), "lithium"), 1);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_array_arithmetic();
    test_map();
}

} // namespace count_suite

//-----------------------------------------------------------------------------
// std::equal
//-----------------------------------------------------------------------------

namespace equal_suite
{

void test_null()
{
    // null has zero length, so std::equal always returns true regardless of the
    // second range.
    variable null;
    variable alpha(1);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(null.begin(), null.end(), alpha.begin()),
                              true);
}

void test_boolean()
{
    variable alpha(false);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
}

void test_array_boolean()
{
    variable alpha = variable::array({ true, true, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), alpha.begin()),
                              true);
    variable bravo = variable::array({ false, true, true });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), bravo.begin()),
                              false);
    variable charlie = variable::array({ false, false, false });
    TRIAL_PROTOCOL_TEST_EQUAL(std::equal(alpha.begin(), alpha.end(), charlie.begin()),
                              false);
}

void run()
{
    test_null();
    test_boolean();
    test_array_boolean();
}

} // namespace equal_suite

//-----------------------------------------------------------------------------
// std::find
//-----------------------------------------------------------------------------

namespace find_suite
{

void test_null()
{
    variable data;
    // Cannot iterate over null, so nothing is found
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), variable::null) == data.end());
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), false) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), true) != data.end());
}

void test_integer()
{
    variable data(1);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2) == data.end());
}

void test_number()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 0.0) == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 1.0) != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), 2.0) == data.end());
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "") == data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "alpha") != data.end());
    TRIAL_PROTOCOL_TEST(std::find(data.begin(), data.end(), "bravo") == data.end());
}

void test_array()
{
    variable data = variable::array({ true, 2, 3.0, "alpha" });

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
}

void test_map()
{
    variable data = variable::map(
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

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_map();
}

} // namespace find_suite

//-----------------------------------------------------------------------------
// std::iota
//-----------------------------------------------------------------------------

namespace iota_suite
{

void test_array()
{
    variable data = variable::array(4, 0);
    std::iota(data.begin(), data.end(), 1);
    variable result = variable::array({1, 2, 3, 4});
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 result.begin(), result.end(),
                                 std::equal_to<variable>());
}

void run()
{
    test_array();
}

} // namespace iota_suite

//-----------------------------------------------------------------------------
// std::max_element
//-----------------------------------------------------------------------------

namespace max_element_suite
{

void test_null()
{
    variable data;
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_boolean()
{
    variable data(true);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == true);
}

void test_integer()
{
    variable data(1);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 1);
}

void test_number()
{
    variable data(1.0);
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 1.0);
}

void test_string()
{
    variable data("alpha");
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "alpha");
}

void test_array_arithmetic()
{
    variable data = variable::array({false, 2, 3.0});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
}

void test_array_string()
{
    variable data = variable::array({"alpha", "bravo", "charlie"});
    auto where = std::max_element(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(*where == "charlie");
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array_arithmetic();
    test_array_string();
    // FIXME: map
}

} // namespace max_element_suite

//-----------------------------------------------------------------------------
// std::search
//-----------------------------------------------------------------------------

namespace search_suite
{

void test_array()
{
#if 0 // FIXME: Cannot currently construct end iterator with default constructor
    variable haystack = variable::array({false, 2, 3.0, "alpha"});

    variable needle = variable::array({"alpha"});
    auto where = std::search(haystack.begin(), haystack.end(),
                             needle.begin(), needle.end());
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(haystack.end(), where), 3);
#endif
}

void run()
{
    test_array();
}

} // namespace search_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    adjacent_find_suite::run();
    all_of_suite::run();
    count_suite::run();
    equal_suite::run();
    find_suite::run();
    iota_suite::run();
    max_element_suite::run();
    search_suite::run();

    return boost::report_errors();
}
