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

#include <trial/protocol/json/reader.hpp>

using namespace trial::protocol;

BOOST_AUTO_TEST_SUITE(json_reader_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_null)
{
    const char input[] = "null";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::null);
    BOOST_REQUIRE_EQUAL(reader.literal(), "null");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
}

BOOST_AUTO_TEST_CASE(test_false)
{
    const char input[] = "false";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::boolean);
    BOOST_REQUIRE_EQUAL(reader.value<bool>(), false);
    BOOST_REQUIRE_EQUAL(reader.literal(), "false");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const char input[] = "true";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::boolean);
    BOOST_REQUIRE_EQUAL(reader.value<bool>(), true);
    BOOST_REQUIRE_EQUAL(reader.literal(), "true");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_integer)
{
    const char input[] = "1";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<double>(), 1.0);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_float)
{
    const char input[] = "1.0";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::floating);
    BOOST_REQUIRE_EQUAL(reader.value<float>(), 1.0);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1.0");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_double)
{
    const char input[] = "1.0";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::floating);
    BOOST_REQUIRE_EQUAL(reader.value<double>(), 1.0);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1.0");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_longdouble)
{
    const char input[] = "1.0";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::floating);
    BOOST_REQUIRE_EQUAL(reader.value<long double>(), 1.0);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1.0");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_string)
{
    const char input[] = "\"alpha\"";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.literal(), "\"alpha\"");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_integer_const)
{
    const char input[] = "1";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<const int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.literal(), "1");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(fail_true_true)
{
    const char input[] = "true,true";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::boolean);
    BOOST_REQUIRE_EQUAL(reader.value<bool>(), true);
    BOOST_REQUIRE_EQUAL(reader.literal(), "true");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_array_empty)
{
    const char input[] = "[]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(test_integer_array_one)
{
    const char input[] = "[1]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(test_integer_array_many)
{
    const char input[] = "[1,2,3]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 2);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 3);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(test_integer_array_nested_one)
{
    const char input[] = "[[1]]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(test_integer_array_nested_many_siblings)
{
    const char input[] = "[[1],[2]]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 2);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(fail_array_missing_value)
{
    const char input[] = "[,]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

BOOST_AUTO_TEST_CASE(fail_array_trailing_separator)
{
    const char input[] = "[1,]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

BOOST_AUTO_TEST_CASE(fail_array_empty_mismatched)
{
    const char input[] = "[}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::expected_array_end_bracket);
}

BOOST_AUTO_TEST_CASE(fail_integer_array_one_mismatched)
{
    const char input[] = "[1}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::expected_array_end_bracket);
}

BOOST_AUTO_TEST_CASE(fail_array_outer)
{
    const char input[] = "[],false";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::array_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

//-----------------------------------------------------------------------------
// Object
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_object_empty)
{
    const char input[] = "{}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(test_object_one)
{
    const char input[] = "{\"alpha\":1}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(test_object_many)
{
    const char input[] = "{\"alpha\":1,\"bravo\":2}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "bravo");
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 2);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(test_object_nested_one)
{
    const char input[] = "{\"alpha\":{\"helium\":2}}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "helium");
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 2);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 2);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::end);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
}

BOOST_AUTO_TEST_CASE(fail_object_missing_colon)
{
    const char input[] = "{\"key\"}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::error);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

BOOST_AUTO_TEST_CASE(fail_object_missing_value)
{
    const char input[] = "{\"key\":}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

BOOST_AUTO_TEST_CASE(fail_object_trailing_separator)
{
    const char input[] = "{\"key\":1,}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

BOOST_AUTO_TEST_CASE(fail_object_invalid_integer_key)
{
    const char input[] = "{1:1}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::error);
    BOOST_REQUIRE_EQUAL(reader.error(), json::invalid_key);
}

BOOST_AUTO_TEST_CASE(fail_object_invalid_null_key)
{
    const char input[] = "{null:1}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::error);
    BOOST_REQUIRE_EQUAL(reader.error(), json::invalid_key);
}

BOOST_AUTO_TEST_CASE(fail_object_invalid_true_key)
{
    const char input[] = "{true:1}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::error);
    BOOST_REQUIRE_EQUAL(reader.error(), json::invalid_key);
}

BOOST_AUTO_TEST_CASE(fail_object_invalid_object_key)
{
    const char input[] = "{{\"key\":1}:2}";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::error);
    BOOST_REQUIRE_EQUAL(reader.error(), json::invalid_key);
}

BOOST_AUTO_TEST_CASE(fail_object_empty_mismatched)
{
    const char input[] = "{]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::expected_object_end_bracket);
}

BOOST_AUTO_TEST_CASE(fail_object_one_mismatched)
{
    const char input[] = "{\"alpha\":1]";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "alpha");
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.error(), json::expected_object_end_bracket);
}

BOOST_AUTO_TEST_CASE(fail_object_outer)
{
    const char input[] = "{},true";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_open);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::object_close);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::error);
    BOOST_REQUIRE_EQUAL(reader.error(), json::unexpected_token);
}

//-----------------------------------------------------------------------------
// boost::get
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_get_bool)
{
    const char input[] = "true";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::boolean);
    BOOST_REQUIRE_EQUAL(boost::get<bool>(reader), true);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_get_integer)
{
    const char input[] = "1";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::integer);
    BOOST_REQUIRE_EQUAL(boost::get<int>(reader), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_get_float)
{
    const char input[] = "1.0";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::floating);
    BOOST_REQUIRE_EQUAL(boost::get<double>(reader), 1.0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_CASE(test_get_string)
{
    const char input[] = "\"alpha\"";
    json::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.type(), json::token::string);
    BOOST_REQUIRE_EQUAL(boost::get<std::string>(reader), "alpha");
    BOOST_REQUIRE_EQUAL(reader.next(), false);
}

BOOST_AUTO_TEST_SUITE_END()
