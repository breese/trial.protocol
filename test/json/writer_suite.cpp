///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include <sstream>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/json/writer.hpp>
#include "is_system_error.hpp"

using namespace trial::protocol;
namespace token = json::token;

BOOST_AUTO_TEST_SUITE(json_writer_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(result.str(), "");
}

BOOST_AUTO_TEST_CASE(test_null)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::null>(), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null");
}

BOOST_AUTO_TEST_CASE(test_true)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(true), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "true");
}

BOOST_AUTO_TEST_CASE(test_false)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(result.str(), "false");
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int_literal_zero)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0");
}

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(int(0)), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0");
}

BOOST_AUTO_TEST_CASE(test_intmax_zero)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(boost::intmax_t(0)), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0");
}

BOOST_AUTO_TEST_CASE(test_int_literal_zero_one)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0), 1);
    BOOST_REQUIRE_EQUAL(writer.value(1), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0,1");
}

//-----------------------------------------------------------------------------
// Float
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float_literal_zero)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0.0), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0");
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_literal_empty)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(""), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_literal_alpha)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value("alpha"), 7);
    BOOST_REQUIRE_EQUAL(result.str(), "\"alpha\"");
}

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(std::string()), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(std::string("alpha")), 7);
    BOOST_REQUIRE_EQUAL(result.str(), "\"alpha\"");
}

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_array_empty)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(writer.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "[]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_one)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "[false]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_two)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value(true), 4);
    BOOST_REQUIRE_EQUAL(writer.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "[false,true]");
}

BOOST_AUTO_TEST_CASE(fail_array_missing_begin)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EXCEPTION(writer.value<token::end_array>(),
                            json::error,
                            test::is_system_error(json::unexpected_token));
}

//-----------------------------------------------------------------------------
// Object
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_object_empty)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::begin_object>(), 1);
    BOOST_REQUIRE_EQUAL(writer.value<token::end_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "{}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_one)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::begin_object>(), 1);
    BOOST_REQUIRE_EQUAL(writer.value("key1"), 6);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value<token::end_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "{\"key1\":false}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_two)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::begin_object>(), 1);
    BOOST_REQUIRE_EQUAL(writer.value("key1"), 6);
    BOOST_REQUIRE_EQUAL(writer.value(false), 5);
    BOOST_REQUIRE_EQUAL(writer.value("key2"), 6);
    BOOST_REQUIRE_EQUAL(writer.value(true), 4);
    BOOST_REQUIRE_EQUAL(writer.value<token::end_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "{\"key1\":false,\"key2\":true}");
}

BOOST_AUTO_TEST_CASE(fail_object_missing_begin)
{
    std::ostringstream result;
    json::writer writer(result);
    BOOST_REQUIRE_EXCEPTION(writer.value<token::end_object>(),
                            json::error,
                            test::is_system_error(json::unexpected_token));
}

BOOST_AUTO_TEST_SUITE_END()
