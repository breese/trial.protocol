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
#include <limits>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/json/detail/encoder.hpp>

using namespace trial::protocol;
namespace token = json::token;

BOOST_AUTO_TEST_SUITE(json_encoder_suite)

//-----------------------------------------------------------------------------
// Buffer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_boost_array)
{
    boost::array<char, 2> result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(42), 2);
    BOOST_REQUIRE_EQUAL(std::string(result.begin(), result.size()), "42");
}

BOOST_AUTO_TEST_CASE(test_ostringstream)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(42), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "42");
}

BOOST_AUTO_TEST_CASE(test_vector)
{
    std::vector<char> result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(42), 2);
    std::string expected("42");
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(test_string)
{
    std::string result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(42), 2);
    BOOST_REQUIRE_EQUAL(result, "42");
}

//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_comma)
{
    boost::array<char, 1> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 1);
    BOOST_REQUIRE_EQUAL(std::string(buffer.begin(), buffer.size()), ",");
}

BOOST_AUTO_TEST_CASE(test_fail_comma)
{
    boost::array<char, 0> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 0);
}

BOOST_AUTO_TEST_CASE(test_colon)
{
    boost::array<char, 1> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::name_separator>(), 1);
    BOOST_REQUIRE_EQUAL(std::string(buffer.begin(), buffer.size()), ":");
}

BOOST_AUTO_TEST_CASE(test_fail_colon)
{
    boost::array<char, 0> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::name_separator>(), 0);
}

BOOST_AUTO_TEST_CASE(test_null)
{
    boost::array<char, 4> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::null>(), 4);
    BOOST_REQUIRE_EQUAL(std::string(buffer.begin(), buffer.size()), "null");
}

BOOST_AUTO_TEST_CASE(test_fail_null)
{
    boost::array<char, 3> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::null>(), 0);
}

BOOST_AUTO_TEST_CASE(test_null_null)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::null>(), 4);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value<token::null>(), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null,null");
}

BOOST_AUTO_TEST_CASE(test_true)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "true");
}

BOOST_AUTO_TEST_CASE(test_true_true)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "true,true");
}

BOOST_AUTO_TEST_CASE(test_false)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(result.str(), "false");
}

BOOST_AUTO_TEST_CASE(test_false_false)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(result.str(), "false,false");
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(0)), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0");
}

BOOST_AUTO_TEST_CASE(test_int_zero_zero)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(0)), 1);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(0)), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0,0");
}

BOOST_AUTO_TEST_CASE(test_int_one)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(1)), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "1");
}

BOOST_AUTO_TEST_CASE(test_int_minus_one)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-1)), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "-1");
}

BOOST_AUTO_TEST_CASE(test_int_nine)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(9)), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "9");
}

BOOST_AUTO_TEST_CASE(test_int_minus_nine)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-9)), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "-9");
}

BOOST_AUTO_TEST_CASE(test_int_ten)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(10)), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "10");
}

BOOST_AUTO_TEST_CASE(test_int_minus_ten)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-10)), 3);
    BOOST_REQUIRE_EQUAL(result.str(), "-10");
}

BOOST_AUTO_TEST_CASE(test_int_almost_hundred)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(99)), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "99");
}

BOOST_AUTO_TEST_CASE(test_int_hundred)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(100)), 3);
    BOOST_REQUIRE_EQUAL(result.str(), "100");
}

BOOST_AUTO_TEST_CASE(test_int_almost_minus_hundred)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-99)), 3);
    BOOST_REQUIRE_EQUAL(result.str(), "-99");
}

BOOST_AUTO_TEST_CASE(test_int_minus_hundred)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-100)), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "-100");
}

BOOST_AUTO_TEST_CASE(test_int_max)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<boost::int64_t>::max()), 19);
    BOOST_REQUIRE_EQUAL(result.str(), "9223372036854775807");
}

BOOST_AUTO_TEST_CASE(test_int_almost_min)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<boost::int64_t>::min() + 1), 20);
    BOOST_REQUIRE_EQUAL(result.str(), "-9223372036854775807");
}

BOOST_AUTO_TEST_CASE(test_int_min)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<boost::int64_t>::min()), 20);
    BOOST_REQUIRE_EQUAL(result.str(), "-9223372036854775808");
}

BOOST_AUTO_TEST_CASE(regress_digits10)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(1561718168), 10);
    BOOST_REQUIRE_EQUAL(result.str(), "1561718168");
}

//-----------------------------------------------------------------------------
// Floating-point
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float_zero)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(0.0f), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0");
}

BOOST_AUTO_TEST_CASE(test_double_zero)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(0.0), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "0");
}

BOOST_AUTO_TEST_CASE(test_double_one)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(1.0), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "1");
}

BOOST_AUTO_TEST_CASE(test_double_minus_one)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(-1.0), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "-1");
}

BOOST_AUTO_TEST_CASE(test_double_dot_five)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(0.5), 3);
    BOOST_REQUIRE_EQUAL(result.str(), "0.5");
}

BOOST_AUTO_TEST_CASE(test_double_minus_dot_five)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(-0.5), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "-0.5");
}

BOOST_AUTO_TEST_CASE(test_double_e_100)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(1e100), 6);
    BOOST_REQUIRE_EQUAL(result.str(), "1e+100");
}

BOOST_AUTO_TEST_CASE(test_double_e_minus_100)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(1e-100), 6);
    BOOST_REQUIRE_EQUAL(result.str(), "1e-100");
}

BOOST_AUTO_TEST_CASE(test_float_max)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::max()), 14);
    BOOST_REQUIRE_EQUAL(result.str(), "3.40282347e+38");
}

BOOST_AUTO_TEST_CASE(test_double_max)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::max()), 23);
    BOOST_REQUIRE_EQUAL(result.str(), "1.7976931348623157e+308");
}

BOOST_AUTO_TEST_CASE(test_float_min)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::min()), 14);
    BOOST_REQUIRE_EQUAL(result.str(), "1.17549435e-38");
}

BOOST_AUTO_TEST_CASE(test_double_min)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::min()), 23);
    BOOST_REQUIRE_EQUAL(result.str(), "2.2250738585072014e-308");
}

BOOST_AUTO_TEST_CASE(test_float_infinity)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_infinity)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null");
}

BOOST_AUTO_TEST_CASE(test_float_minus_infinity)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(-std::numeric_limits<float>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_minus_infinity)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(-std::numeric_limits<double>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null");
}

BOOST_AUTO_TEST_CASE(test_float_nan)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::quiet_NaN()), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_nan)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::quiet_NaN()), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "null");
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_literal_empty)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(""), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    std::ostringstream result;
    std::string text("");
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(text), 2);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_space)
{
    std::ostringstream result;
    std::string text(" ");
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value(text), 3);
    BOOST_REQUIRE_EQUAL(result.str(), "\" \"");
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("alpha"), 7);
    BOOST_REQUIRE_EQUAL(result.str(), "\"alpha\"");
}

BOOST_AUTO_TEST_CASE(test_string_alpha_bravo)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("alpha bravo"), 13);
    BOOST_REQUIRE_EQUAL(result.str(), "\"alpha bravo\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_quote)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("\""), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_reverse_solidus)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("\\"), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\\\\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_solidus)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("/"), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\/\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_backspace)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("\b"), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\b\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_formfeed)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("\f"), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\f\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_newline)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("\n"), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\n\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_carriage_return)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("\r"), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\r\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_tab)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value("\t"), 4);
    BOOST_REQUIRE_EQUAL(result.str(), "\"\\t\"");
}

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_array_begin)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "[");
}

BOOST_AUTO_TEST_CASE(test_array_end)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "]");
}

BOOST_AUTO_TEST_CASE(test_array_empty)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "[]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_one)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "[false]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_two)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "[false,true]");
}

BOOST_AUTO_TEST_CASE(test_object_begin)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "{");
}

BOOST_AUTO_TEST_CASE(test_object_end)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "}");
}

BOOST_AUTO_TEST_CASE(test_object_empty)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_object>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "{}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_one)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_object>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value("false"), 7);
    BOOST_REQUIRE_EQUAL(encoder.value<token::name_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "{\"false\":false}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_two)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_object>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value("false"), 7);
    BOOST_REQUIRE_EQUAL(encoder.value<token::name_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value<token::value_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value("true"), 6);
    BOOST_REQUIRE_EQUAL(encoder.value<token::name_separator>(), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_object>(), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "{\"false\":false,\"true\":true}");
}

//-----------------------------------------------------------------------------
// Literal
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_literal_string)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.literal("alpha"), 5);
    BOOST_REQUIRE_EQUAL(result.str(), "alpha");
}

BOOST_AUTO_TEST_CASE(test_literal_quote)
{
    std::ostringstream result;
    json::detail::encoder encoder(result);
    BOOST_REQUIRE_EQUAL(encoder.literal("\""), 1);
    BOOST_REQUIRE_EQUAL(result.str(), "\"");
}

BOOST_AUTO_TEST_SUITE_END()
