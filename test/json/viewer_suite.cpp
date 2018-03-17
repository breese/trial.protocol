///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <trial/protocol/json/viewer.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;

//-----------------------------------------------------------------------------

namespace iterator_suite
{

void test_token()
{
    const char input[] = "[null,true,2,3.0,\"alpha\",[42],{\"bravo\":42.0}]";
    json::viewer viewer(input);
    json::viewer::const_iterator it = viewer.begin();
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::structural);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::null);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::nullable);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::data);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::data);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::data);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::data);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::structural);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::data);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::structural);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::structural);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::data);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::data);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::structural);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::structural);
    ++it;
    TRIAL_PROTOCOL_TEST(it == viewer.end());
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end);
    TRIAL_PROTOCOL_TEST_EQUAL(it.category(), json::token::category::status);
}

void test_value()
{
    const char input[] = "[null,true,2,3.0,\"alpha\",[42],{\"bravo\":42.0}]";
    json::viewer viewer(input);
    json::viewer::const_iterator it = viewer.begin();
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::null);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<bool>(), true);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<int>(), 2);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<float>(), 3.0f);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<std::string>(), "alpha");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<int>(), 42);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_object);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<std::string>(), "bravo");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<float>(), 42.0f);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_object);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    ++it;
    TRIAL_PROTOCOL_TEST(it == viewer.end());
}

void test_dereference()
{
    const char input[] = "[null,true,2,3.0,\"alpha\",[42],{\"bravo\":42.0}]";
    json::viewer viewer(input);
    json::viewer::const_iterator it = viewer.begin();
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "[");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "null");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "true");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "2");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "3.0");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "\"alpha\"");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "[");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "42");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "]");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "{");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "\"bravo\"");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "42.0");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "}");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "]");
    ++it;
    TRIAL_PROTOCOL_TEST(it == viewer.end());
}

void test_level()
{
    const char input[] = "[null,[true,[2,[3.0,[\"alpha\"]]]]]";
    json::viewer viewer(input);
    json::viewer::const_iterator it = viewer.begin();
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 0);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::null);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 1);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 1);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 2);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 2);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 3);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 3);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 4);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 4);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 5);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 5);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 4);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 3);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 2);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 1);
    ++it;
    TRIAL_PROTOCOL_TEST(it == viewer.end());
    TRIAL_PROTOCOL_TEST_EQUAL(it.symbol(), json::token::symbol::end);
    TRIAL_PROTOCOL_TEST_EQUAL(it.level(), 0);
}

void run()
{
    test_token();
    test_value();
    test_dereference();
    test_level();
}

} // namespace iterator_suite

//-----------------------------------------------------------------------------

namespace algorithm_suite
{

void find_boolean()
{
    const char input[] = "[false,true]";
    json::viewer viewer(input);
    auto where = std::find(viewer.begin(), viewer.end(), "true");
    TRIAL_PROTOCOL_TEST_EQUAL(*where, "true");    
}

void run()
{
    find_boolean();
}

} // namespace algorithm_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    iterator_suite::run();
    algorithm_suite::run();

    return boost::report_errors();
}
