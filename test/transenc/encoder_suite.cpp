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

#include <limits>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/transenc/token.hpp>
#include <trial/protocol/transenc/detail/encoder.hpp>

namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::detail::encoder::value_type value_type;

BOOST_AUTO_TEST_SUITE(transenc_encoder_suite)

//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_null)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::null>(), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::null);
}

BOOST_AUTO_TEST_CASE(fail_null_empty)
{
    boost::array<value_type, 0> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::null>(), 0);
}

BOOST_AUTO_TEST_CASE(test_false)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::false_value);
}

BOOST_AUTO_TEST_CASE(fail_false_empty)
{
    boost::array<value_type, 0> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(false), 0);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::true_value);
}

BOOST_AUTO_TEST_CASE(fail_true_empty)
{
    boost::array<value_type, 0> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(true), 0);
}

//-----------------------------------------------------------------------------
// Integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_small_zero)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(0)), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], 0x00);
}

BOOST_AUTO_TEST_CASE(test_small_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(1)), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], 0x01);
}

BOOST_AUTO_TEST_CASE(test_small_minus_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(-1)), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], 0xFF);
}

BOOST_AUTO_TEST_CASE(test_small_lower)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(-32)), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], 0xE0);
}

BOOST_AUTO_TEST_CASE(test_small_upper)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(127)), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], 0x7F);
}

BOOST_AUTO_TEST_CASE(fail_small_empty)
{
    boost::array<value_type, 0> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(0)), 0);
}

BOOST_AUTO_TEST_CASE(test_int8_negative_min)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(-33)), 2);
    BOOST_REQUIRE_EQUAL(buffer.size(), 2);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int8);
    BOOST_REQUIRE_EQUAL(buffer[1], 0xDF);
}

BOOST_AUTO_TEST_CASE(test_int8_negative_max)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(-128)), 2);
    BOOST_REQUIRE_EQUAL(buffer.size(), 2);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int8);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x80);
}

BOOST_AUTO_TEST_CASE(fail_int8_missing_one)
{
    boost::array<value_type, 1> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(-128)), 0);
}

BOOST_AUTO_TEST_CASE(fail_int8_missing_two)
{
    boost::array<value_type, 0> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int8_t(-128)), 0);
}

BOOST_AUTO_TEST_CASE(test_int16_zero)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int16_t(0)), 3);
    BOOST_REQUIRE_EQUAL(buffer.size(), 3);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int16);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
}

BOOST_AUTO_TEST_CASE(test_int16_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int16_t(1)), 3);
    BOOST_REQUIRE_EQUAL(buffer.size(), 3);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int16);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x01);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
}

BOOST_AUTO_TEST_CASE(test_int16_minus_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int16_t(-1)), 3);
    BOOST_REQUIRE_EQUAL(buffer.size(), 3);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int16);
    BOOST_REQUIRE_EQUAL(buffer[1], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[2], 0xFF);
}

BOOST_AUTO_TEST_CASE(test_int16_max)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::int16::type>::max()), 3);
    BOOST_REQUIRE_EQUAL(buffer.size(), 3);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int16);
    BOOST_REQUIRE_EQUAL(buffer[1], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x7F);
}

BOOST_AUTO_TEST_CASE(test_int16_min)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::int16::type>::min()), 3);
    BOOST_REQUIRE_EQUAL(buffer.size(), 3);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int16);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x80);
}

BOOST_AUTO_TEST_CASE(test_int32_zero)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int32_t(0)), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
}

BOOST_AUTO_TEST_CASE(test_int32_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int32_t(1)), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x01);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
}

BOOST_AUTO_TEST_CASE(test_int32_minus_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int32_t(-1)), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[2], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[3], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[4], 0xFF);
}

BOOST_AUTO_TEST_CASE(test_int32_max)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::int32::type>::max()), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[2], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[3], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x7F);
}

BOOST_AUTO_TEST_CASE(test_int32_min)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::int32::type>::min()), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x80);
}

BOOST_AUTO_TEST_CASE(test_int64_zero)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(0)), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x00);
}

BOOST_AUTO_TEST_CASE(test_int64_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(1)), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x01);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x00);
}

BOOST_AUTO_TEST_CASE(test_int64_minus_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(boost::int64_t(-1)), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[2], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[3], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[4], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[5], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[6], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[7], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[8], 0xFF);
}

BOOST_AUTO_TEST_CASE(test_int64_max)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::int64::type>::max()), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[2], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[3], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[4], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[5], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[6], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[7], 0xFF);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x7F);
}

BOOST_AUTO_TEST_CASE(test_int64_min)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::int64::type>::min()), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::int64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x80);
}

//-----------------------------------------------------------------------------
// Floating-point numbers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float32_zero)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(0.0f), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
}

BOOST_AUTO_TEST_CASE(test_float32_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(1.0f), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x80);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x3F);
}

BOOST_AUTO_TEST_CASE(test_float32_minus_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-1.0f), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x80);
    BOOST_REQUIRE_EQUAL(buffer[4], 0xBF);
}

BOOST_AUTO_TEST_CASE(test_float32_two)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(2.0f), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x40);
}

BOOST_AUTO_TEST_CASE(test_float32_minus_two)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-2.0f), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0xC0);
}

BOOST_AUTO_TEST_CASE(test_float32_infinity)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::float32::type>::infinity()), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x80);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x7F);
}

BOOST_AUTO_TEST_CASE(test_float32_minus_infinity)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-std::numeric_limits<token::float32::type>::infinity()), 5);
    BOOST_REQUIRE_EQUAL(buffer.size(), 5);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x80);
    BOOST_REQUIRE_EQUAL(buffer[4], 0xFF);
}

BOOST_AUTO_TEST_CASE(test_float64_zero)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(0.0), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x00);
}

BOOST_AUTO_TEST_CASE(test_float64_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(1.0), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0xF0);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x3F);
}

BOOST_AUTO_TEST_CASE(test_float64_minus_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-1.0), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0xF0);
    BOOST_REQUIRE_EQUAL(buffer[8], 0xBF);
}

BOOST_AUTO_TEST_CASE(test_float64_two)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(2.0), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x40);
}

BOOST_AUTO_TEST_CASE(test_float64_minus_two)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-2.0), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[8], 0xC0);
}

BOOST_AUTO_TEST_CASE(test_float64_infinity)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(std::numeric_limits<token::float64::type>::infinity()), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0xF0);
    BOOST_REQUIRE_EQUAL(buffer[8], 0x7F);
}

BOOST_AUTO_TEST_CASE(test_float64_minus_infinity)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(-std::numeric_limits<token::float64::type>::infinity()), 9);
    BOOST_REQUIRE_EQUAL(buffer.size(), 9);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[7], 0xF0);
    BOOST_REQUIRE_EQUAL(buffer[8], 0xFF);
}

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string8_empty)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value(""), buffer.size());
    BOOST_REQUIRE_EQUAL(buffer.size(), 2);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::string8);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
}

BOOST_AUTO_TEST_CASE(test_string8_abcde)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value("ABCDE"), buffer.size());
    BOOST_REQUIRE_EQUAL(buffer.size(), 7);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::string8);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x05);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x41);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x42);
    BOOST_REQUIRE_EQUAL(buffer[4], 0x43);
    BOOST_REQUIRE_EQUAL(buffer[5], 0x44);
    BOOST_REQUIRE_EQUAL(buffer[6], 0x45);
}

BOOST_AUTO_TEST_CASE(test_string16)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    std::string data(0x100, 'A');
    BOOST_REQUIRE_EQUAL(encoder.value(data), buffer.size());
    BOOST_REQUIRE_EQUAL(buffer.size(), 3 + data.size());
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::string16);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x01);
    BOOST_REQUIRE_EQUAL(buffer[3], 0x41);
    BOOST_REQUIRE_EQUAL(buffer[3 + data.size() - 1], 0x41);
}

//-----------------------------------------------------------------------------
// Binary data
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_binary8_empty)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    std::vector<value_type> data;
    BOOST_REQUIRE_EQUAL(encoder.binary(data.data(), data.size()), buffer.size());
    BOOST_REQUIRE_EQUAL(buffer.size(), 2);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::binary8);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x00);
}

BOOST_AUTO_TEST_CASE(test_binary8_one)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    std::vector<value_type> data;
    data.push_back(0x12);
    BOOST_REQUIRE_EQUAL(encoder.binary(data.data(), data.size()), buffer.size());
    BOOST_REQUIRE_EQUAL(buffer.size(), 3);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::binary8);
    BOOST_REQUIRE_EQUAL(buffer[1], 0x01);
    BOOST_REQUIRE_EQUAL(buffer[2], 0x12);
}

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_record_begin)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_record>(), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::begin_record);
}

BOOST_AUTO_TEST_CASE(test_record_end)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_record>(), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::end_record);
}

BOOST_AUTO_TEST_CASE(test_array_begin)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_array>(), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::begin_array);
}

BOOST_AUTO_TEST_CASE(test_array_end)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_array>(), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::end_array);
}

BOOST_AUTO_TEST_CASE(test_assoc_array_begin)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::begin_assoc_array>(), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::begin_assoc_array);
}

BOOST_AUTO_TEST_CASE(test_assoc_array_end)
{
    std::vector<value_type> buffer;
    format::detail::encoder encoder(buffer);
    BOOST_REQUIRE_EQUAL(encoder.value<token::end_assoc_array>(), 1);
    BOOST_REQUIRE_EQUAL(buffer.size(), 1);
    BOOST_REQUIRE_EQUAL(buffer[0], token::code::end_assoc_array);
}

BOOST_AUTO_TEST_SUITE_END()
