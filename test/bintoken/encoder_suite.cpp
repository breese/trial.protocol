///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/bintoken/token.hpp>
#include <trial/protocol/bintoken/detail/encoder.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = bintoken::token;

using output_type = std::uint8_t;
using encoder_type = bintoken::detail::basic_encoder<sizeof(buffer::array<char, 1>)>;

//-----------------------------------------------------------------------------
// Basic
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_null()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::null>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::null);
}

void fail_null_empty()
{
    std::array<output_type, 0> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::null>(), 0);
}

void test_false()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(false), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::false_value);
}

void fail_false_empty()
{
    std::array<output_type, 0> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(false), 0);
}

void test_true()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::true_value);
}

void fail_true_empty()
{
    std::array<output_type, 0> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(true), 0);
}

void run()
{
    test_null();
    fail_null_empty();
    test_false();
    fail_false_empty();
    test_true();
    fail_true_empty();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Small integers
//-----------------------------------------------------------------------------

namespace small_suite
{

void test_zero()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(0)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(1)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], 0x01);
}

void test_minus_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(-1)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], 0xFF);
}

void test_lower()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(-32)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], 0xE0);
}

void test_upper()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(127)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], 0x7F);
}

void fail_empty()
{
    std::array<output_type, 0> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(0)), 0);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_lower();
    test_upper();
    fail_empty();
}

} // namespace small_suite

//-----------------------------------------------------------------------------
// 8-bit integers
//-----------------------------------------------------------------------------

namespace int8_suite
{

void test_negative_min()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(-33)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xDF);
}

void test_negative_max()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(-128)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x80);
}

void fail_missing_one()
{
    std::array<output_type, 1> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(-128)), 0);
}

void fail_missing_two()
{
    std::array<output_type, 0> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int8_t(-128)), 0);
}

void run()
{
    test_negative_min();
    test_negative_max();
    fail_missing_one();
    fail_missing_two();
}

} // namespace int8_suite

//-----------------------------------------------------------------------------
// 16-bit integers
//-----------------------------------------------------------------------------

namespace int16_suite
{

void test_zero()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int16_t(0)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int16_t(1)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x01);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
}

void test_minus_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int16_t(-1)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0xFF);
}

void test_max()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::int16::type>::max()), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x7F);
}

void test_min()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::int16::type>::min()), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x80);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_max();
    test_min();
}

} // namespace int16_suite

//-----------------------------------------------------------------------------
// 32-bit integers
//-----------------------------------------------------------------------------

namespace int32_suite
{

void test_zero()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int32_t(0)), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int32_t(1)), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x01);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x00);
}

void test_minus_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int32_t(-1)), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0xFF);
}

void test_max()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::int32::type>::max()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x7F);
}

void test_min()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::int32::type>::min()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x80);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_max();
    test_min();
}

} // namespace int32_suite

//-----------------------------------------------------------------------------
// 64-bit integers
//-----------------------------------------------------------------------------

namespace int64_suite
{

void test_zero()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int64_t(0)), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[5], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[6], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[7], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[8], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int64_t(1)), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x01);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[5], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[6], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[7], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[8], 0x00);
}

void test_minus_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::int64_t(-1)), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[5], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[6], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[7], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[8], 0xFF);
}

void test_max()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::int64::type>::max()), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[5], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[6], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[7], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[8], 0x7F);
}

void test_min()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::int64::type>::min()), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[5], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[6], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[7], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[8], 0x80);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_max();
    test_min();
}

} // namespace int64_suite

//-----------------------------------------------------------------------------
// Floating-point numbers
//-----------------------------------------------------------------------------

namespace float32_suite
{

void test_zero()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(0.0f), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(1.0f), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x3F);
}

void test_minus_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(-1.0f), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0xBF);
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(2.0f), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x40);
}

void test_minus_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(-2.0f), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0xC0);
}

void test_min()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::float32::type>::min()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x00);
}

void test_max()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::float32::type>::max()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x7F);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x7F);
}

void test_infinity()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::float32::type>::infinity()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x7F);
}

void test_minus_infinity()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(-std::numeric_limits<token::float32::type>::infinity()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0xFF);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_two();
    test_minus_two();
    test_min();
    test_max();
    test_infinity();
    test_minus_infinity();
}

} // namespace float32_suite

namespace float64_suite
{

void test_zero()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(0.0), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(1.0), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_minus_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(-1.0), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xBF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(2.0), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_minus_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(-2.0), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_min()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::float64::type>::min()), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_max()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::float64::type>::max()), 9);

    output_type expected[] = { token::code::float64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_infinity()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(std::numeric_limits<token::float64::type>::infinity()), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_minus_infinity()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(-std::numeric_limits<token::float64::type>::infinity()), 9);

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_two();
    test_minus_two();
    test_min();
    test_max();
    test_infinity();
    test_minus_infinity();
}

} // namespace float64_suite

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_string8_empty()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(""), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
}

void test_string8_abcde()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value("ABCDE"), 7);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 7);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x05);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x41);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x42);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[4], 0x43);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[5], 0x44);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[6], 0x45);
}

void test_string16()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::string data(0x100, 'A');
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value(data), 3 + data.size());
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 3 + data.size());
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::string16);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[2], 0x01);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3], 0x41);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[3 + data.size() - 1], 0x41);
}

void run()
{
    test_string8_empty();
    test_string8_abcde();
    test_string16();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

namespace container_suite
{

void test_record_begin()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::begin_record>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::begin_record);
}

void test_record_end()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::end_record>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::end_record);
}

void test_array_begin()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::begin_array);
}

void test_array_end()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::end_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::end_array);
}

void test_assoc_array_begin()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::begin_assoc_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::begin_assoc_array);
}

void test_assoc_array_end()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.value<token::end_assoc_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::end_assoc_array);
}

void run()
{
    test_record_begin();
    test_record_end();
    test_array_begin();
    test_array_end();
    test_assoc_array_begin();
    test_assoc_array_end();
}

} // namespace container_suite

//-----------------------------------------------------------------------------
// int8_t[N]
//-----------------------------------------------------------------------------

namespace compact_int8_suite
{

void test_empty()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::vector<std::int8_t> data;
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::array8_int8);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int8::type, 1> data{{0x12}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 3);
    const output_type expected[] = {
        token::code::array8_int8, 0x01, 0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int8::type, 2> data{{0x12, 0x34}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 4);
    const output_type expected[] = {
        token::code::array8_int8, 0x02, 0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_empty();
    test_one();
    test_two();
}

} // namespace compact_int8_suite

//-----------------------------------------------------------------------------
// int16_t[N]
//-----------------------------------------------------------------------------

namespace compact_int16_suite
{

void test_empty()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::vector<token::int16::type> data;
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::array8_int16);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int16::type, 1> data{{0x0201}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 4);
    const output_type expected[] = {
        token::code::array8_int16, 0x02,
        0x01, 0x02
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int16::type, 2> data{{0x0201, 0x1211}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 6);
    const output_type expected[] = {
        token::code::array8_int16, 0x04,
        0x01, 0x02,
        0x11, 0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_empty();
    test_one();
    test_two();
}

} // namespace compact_int16_suite

//-----------------------------------------------------------------------------
// int32_t[N]
//-----------------------------------------------------------------------------

namespace compact_int32_suite
{

void test_empty()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::vector<token::int32::type> data;
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::array8_int32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int32::type, 1> data{{0x04030201}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 6);
    const output_type expected[] = {
        token::code::array8_int32, 0x04,
        0x01, 0x02, 0x03, 0x04
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int32::type, 2> data{{0x04030201, 0x14131211}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 10);
    const output_type expected[] = {
        token::code::array8_int32, 0x08,
        0x01, 0x02, 0x03, 0x04,
        0x11, 0x12, 0x13, 0x14
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_empty();
    test_one();
    test_two();
}

} // namespace compact_int32_suite

//-----------------------------------------------------------------------------
// int64_t[N]
//-----------------------------------------------------------------------------

namespace compact_int64_suite
{

void test_empty()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::vector<token::int64::type> data;
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::array8_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int64::type, 1> data{{0x0807060504030201}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 10);
    const output_type expected[] = {
        token::code::array8_int64, 0x08,
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::int64::type, 2> data{{0x0807060504030201, 0x1817161514131211}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 18);
    const output_type expected[] = {
        token::code::array8_int64, 0x10,
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_empty();
    test_one();
    test_two();
}

} // namespace compact_int64_suite

//-----------------------------------------------------------------------------
// float32[N]
//-----------------------------------------------------------------------------

namespace compact_float32_suite
{

void test_empty()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::vector<token::float32::type> data;
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::array8_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::float32::type, 1> data{{1.0}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 6);
    const output_type expected[] = {
        token::code::array8_float32, 0x04,
        0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::float32::type, 2> data{{0.0, 1.0}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 10);
    const output_type expected[] = {
        token::code::array8_float32, 0x08,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_empty();
    test_one();
    test_two();
}

} // namespace compact_float32_suite

//-----------------------------------------------------------------------------
// float64[N]
//-----------------------------------------------------------------------------

namespace compact_float64_suite
{

void test_empty()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::vector<token::float64::type> data;
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[0], token::code::array8_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(buffer[1], 0x00);
}

void test_one()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::float64::type, 1> data{{1.0}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 10);
    const output_type expected[] = {
        token::code::array8_float64, 0x08,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_two()
{
    std::vector<output_type> buffer;
    encoder_type encoder(buffer);
    std::array<token::float64::type, 2> data{{0.0, 1.0}};
    TRIAL_PROTOCOL_TEST_EQUAL(encoder.array(data.data(), data.size()), 18);
    const output_type expected[] = {
        token::code::array8_float64, 0x10,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_empty();
    test_one();
    test_two();
}

} // namespace compact_float64_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    small_suite::run();
    int8_suite::run();
    int16_suite::run();
    int32_suite::run();
    int64_suite::run();
    float32_suite::run();
    float64_suite::run();
    string_suite::run();
    container_suite::run();
    compact_int8_suite::run();
    compact_int16_suite::run();
    compact_int32_suite::run();
    compact_int64_suite::run();
    compact_float32_suite::run();
    compact_float64_suite::run();

    return boost::report_errors();
}
