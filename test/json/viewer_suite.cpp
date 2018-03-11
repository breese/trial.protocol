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

void test_array_literal()
{
    const char input[] = "[null,true,2,3.0,\"alpha\"]";
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
    TRIAL_PROTOCOL_TEST_EQUAL(*it, "]");
    ++it;
    TRIAL_PROTOCOL_TEST(it == viewer.end());
}

void test_array_value()
{
    const char input[] = "[null,true,2,3.0,\"alpha\"]";
    json::viewer viewer(input);
    json::viewer::const_iterator it = viewer.begin();
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::begin_array);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::null);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<bool>(), true);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<int>(), 2);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<float>(), 3.0f);
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(it.value<std::string>(), "alpha");
    ++it;
    TRIAL_PROTOCOL_TEST_EQUAL(it.code(), json::token::code::end_array);
    ++it;
    TRIAL_PROTOCOL_TEST(it == viewer.end());
}

void run()
{
    test_array_literal();
    test_array_value();
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
