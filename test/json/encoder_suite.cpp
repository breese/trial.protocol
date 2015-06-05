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
#include <trial/protocol/json/detail/encoder.hpp>

using namespace trial::protocol;

template<std::size_t N>
struct test_array : public buffer::array<char, N>
{
};

struct test_stream : public buffer::ostream
{
    test_stream(std::ostream& stream) : buffer::ostream(stream) {}
};

BOOST_AUTO_TEST_SUITE(json_encoder_suite)

//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_comma)
{
    test_array<1> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 1);
    BOOST_REQUIRE_EQUAL(std::string(buffer.begin(), buffer.size()), ",");
}

BOOST_AUTO_TEST_CASE(test_fail_comma)
{
    test_array<0> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 0);
}

BOOST_AUTO_TEST_CASE(test_colon)
{
    test_array<1> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::colon), 1);
    BOOST_REQUIRE_EQUAL(std::string(buffer.begin(), buffer.size()), ":");
}

BOOST_AUTO_TEST_CASE(test_fail_colon)
{
    test_array<0> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::colon), 0);
}

BOOST_AUTO_TEST_CASE(test_null)
{
    test_array<4> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::null), 4);
    BOOST_REQUIRE_EQUAL(std::string(buffer.begin(), buffer.size()), "null");
}

BOOST_AUTO_TEST_CASE(test_fail_null)
{
    test_array<3> buffer;
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::null), 0);
}

BOOST_AUTO_TEST_CASE(test_null_null)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::null), 4);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(json::null), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null,null");
}

BOOST_AUTO_TEST_CASE(test_true)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "true");
}

BOOST_AUTO_TEST_CASE(test_true_true)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "true,true");
}

BOOST_AUTO_TEST_CASE(test_false)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(result.str().data(), "false");
}

BOOST_AUTO_TEST_CASE(test_false_false)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(result.str().data(), "false,false");
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(0)), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0");
}

BOOST_AUTO_TEST_CASE(test_int_zero_zero)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(0)), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(0)), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0,0");
}

BOOST_AUTO_TEST_CASE(test_int_one)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(1)), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1");
}

BOOST_AUTO_TEST_CASE(test_int_minus_one)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-1)), 2);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-1");
}

BOOST_AUTO_TEST_CASE(test_int_nine)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(9)), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "9");
}

BOOST_AUTO_TEST_CASE(test_int_minus_nine)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-9)), 2);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-9");
}

BOOST_AUTO_TEST_CASE(test_int_ten)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(10)), 2);
    BOOST_REQUIRE_EQUAL(result.str().data(), "10");
}

BOOST_AUTO_TEST_CASE(test_int_minus_ten)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-10)), 3);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-10");
}

BOOST_AUTO_TEST_CASE(test_int_almost_hundred)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(99)), 2);
    BOOST_REQUIRE_EQUAL(result.str().data(), "99");
}

BOOST_AUTO_TEST_CASE(test_int_hundred)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(100)), 3);
    BOOST_REQUIRE_EQUAL(result.str().data(), "100");
}

BOOST_AUTO_TEST_CASE(test_int_almost_minus_hundred)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-99)), 3);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-99");
}

BOOST_AUTO_TEST_CASE(test_int_minus_hundred)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-100)), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-100");
}

BOOST_AUTO_TEST_CASE(test_int_max)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<boost::int64_t>::max()), 19);
    BOOST_REQUIRE_EQUAL(result.str().data(), "9223372036854775807");
}

BOOST_AUTO_TEST_CASE(test_int_almost_min)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<boost::int64_t>::min() + 1), 20);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-9223372036854775807");
}

BOOST_AUTO_TEST_CASE(test_int_min)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<boost::int64_t>::min()), 20);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-9223372036854775808");
}

//-----------------------------------------------------------------------------
// Floating-point
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float_zero)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(0.0f), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0");
}

BOOST_AUTO_TEST_CASE(test_double_zero)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(0.0), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0");
}

BOOST_AUTO_TEST_CASE(test_double_one)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(1.0), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1");
}

BOOST_AUTO_TEST_CASE(test_double_minus_one)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-1.0), 2);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-1");
}

BOOST_AUTO_TEST_CASE(test_double_dot_five)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(0.5), 3);
    BOOST_REQUIRE_EQUAL(result.str().data(), "0.5");
}

BOOST_AUTO_TEST_CASE(test_double_minus_dot_five)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-0.5), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "-0.5");
}

BOOST_AUTO_TEST_CASE(test_double_e_100)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(1e100), 6);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1e+100");
}

BOOST_AUTO_TEST_CASE(test_double_e_minus_100)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(1e-100), 6);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1e-100");
}

BOOST_AUTO_TEST_CASE(test_float_max)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::max()), 14);
    BOOST_REQUIRE_EQUAL(result.str().data(), "3.40282347e+38");
}

BOOST_AUTO_TEST_CASE(test_double_max)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::max()), 23);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1.7976931348623157e+308");
}

BOOST_AUTO_TEST_CASE(test_float_min)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::min()), 14);
    BOOST_REQUIRE_EQUAL(result.str().data(), "1.17549435e-38");
}

BOOST_AUTO_TEST_CASE(test_double_min)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::min()), 23);
    BOOST_REQUIRE_EQUAL(result.str().data(), "2.2250738585072014e-308");
}

BOOST_AUTO_TEST_CASE(test_float_infinity)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_infinity)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

BOOST_AUTO_TEST_CASE(test_float_minus_infinity)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-std::numeric_limits<float>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_minus_infinity)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-std::numeric_limits<double>::infinity()), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

BOOST_AUTO_TEST_CASE(test_float_nan)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<float>::quiet_NaN()), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

BOOST_AUTO_TEST_CASE(test_double_nan)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<double>::quiet_NaN()), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "null");
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_literal_empty)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(""), 2);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    std::ostringstream result;
    test_stream buffer(result);
    std::string text("");
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(text), 2);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("alpha"), 7);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"alpha\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_quote)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("\""), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\\"\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_reverse_solidus)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("\\"), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\\\\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_solidus)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("/"), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\/\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_backspace)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("\b"), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\b\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_formfeed)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("\f"), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\f\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_newline)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("\n"), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\n\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_carriage_return)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("\r"), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\r\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_tab)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("\t"), 4);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"\\t\"");
}

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_array_open)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_open), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[");
}

BOOST_AUTO_TEST_CASE(test_array_close)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "]");
}

BOOST_AUTO_TEST_CASE(test_array_empty)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_open), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_one)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_open), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[false]");
}

BOOST_AUTO_TEST_CASE(test_array_bool_two)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_open), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(encoder.value(json::array_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "[false,true]");
}

BOOST_AUTO_TEST_CASE(test_object_open)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_open), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "{");
}

BOOST_AUTO_TEST_CASE(test_object_close)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "}");
}

BOOST_AUTO_TEST_CASE(test_object_empty)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_open), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "{}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_one)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_open), 1);
    BOOST_REQUIRE_EQUAL(encoder.value("false"), 7);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::colon), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "{\"false\":false}");
}

BOOST_AUTO_TEST_CASE(test_object_bool_two)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_open), 1);
    BOOST_REQUIRE_EQUAL(encoder.value("false"), 7);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::colon), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 5);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::comma), 1);
    BOOST_REQUIRE_EQUAL(encoder.value("true"), 6);
    BOOST_REQUIRE_EQUAL(encoder.value(json::detail::colon), 1);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 4);
    BOOST_REQUIRE_EQUAL(encoder.value(json::object_close), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "{\"false\":false,\"true\":true}");
}

//-----------------------------------------------------------------------------
// Literal
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_literal_string)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.literal("alpha"), 5);
    BOOST_REQUIRE_EQUAL(result.str().data(), "alpha");
}

BOOST_AUTO_TEST_CASE(test_literal_quote)
{
    std::ostringstream result;
    test_stream buffer(result);
    json::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.literal("\""), 1);
    BOOST_REQUIRE_EQUAL(result.str().data(), "\"");
}

BOOST_AUTO_TEST_SUITE_END()
