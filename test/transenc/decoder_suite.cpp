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
#include <algorithm> // std::fill_n
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/transenc/detail/decoder.hpp>

namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::detail::decoder::value_type value_type;

BOOST_AUTO_TEST_SUITE(transenc_decoder_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    const boost::array<value_type, 0> input = {};
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::end);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::status);
}

BOOST_AUTO_TEST_CASE(test_null)
{
    const value_type input[] = { token::code::null };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::null);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::null);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::nullable);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_false)
{
    const value_type input[] = { token::code::false_value };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::false_value);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::boolean);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const value_type input[] = { token::code::true_value };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::true_value);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::boolean);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// Small integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_small_zero)
{
    const value_type input[] = { 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_small_one)
{
    const value_type input[] = { 0x01 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_small_max)
{
    const value_type input[] = { 0x7F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), 127);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_small_minus_one)
{
    const value_type input[] = { 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), -1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_small_minus_max)
{
    const value_type input[] = { 0xE0 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), -32);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// 8-bit integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int8_zero)
{
    const value_type input[] = { token::code::int8, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int8_one)
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int8_max)
{
    const value_type input[] = { token::code::int8, 0x7F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(),
                        std::numeric_limits<token::int8::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int8_min)
{
    const value_type input[] = { token::code::int8, 0x80 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(),
                        std::numeric_limits<token::int8::type>::min());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int8_minus_min_plus_one)
{
    const value_type input[] = { token::code::int8, 0x81 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(),
                        std::numeric_limits<token::int8::type>::min() + 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int8_minus_one)
{
    const value_type input[] = { token::code::int8, 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int8>(), -1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int8_missing_one)
{
    const value_type input[] = { token::code::int8 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// 16-bit integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int16_zero)
{
    const value_type input[] = { token::code::int16, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int16);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int16>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int16_one)
{
    const value_type input[] = { token::code::int16, 0x01, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int16);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int16>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int16_endian)
{
    const value_type input[] = { token::code::int16, 0x22, 0x11 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int16);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int16>(), 0x1122);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int16_minus_one)
{
    const value_type input[] = { token::code::int16, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int16);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int16>(), -1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int16_max)
{
    const value_type input[] = { token::code::int16, 0xFF, 0x7F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int16);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int16>(),
                        std::numeric_limits<token::int16::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int16_min)
{
    const value_type input[] = { token::code::int16, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int16);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int16>(),
                        std::numeric_limits<token::int16::type>::min());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int16_missing_one)
{
    const value_type input[] = { token::code::int16, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int16_missing_two)
{
    const value_type input[] = { token::code::int16 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// 32-bit integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int32_zero)
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32_one)
{
    const value_type input[] = { token::code::int32, 0x01, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32_minus_one)
{
    const value_type input[] = { token::code::int32, 0xFF, 0xFF, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(), -1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32_two)
{
    const value_type input[] = { token::code::int32, 0x02, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(), 2);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32_minus_two)
{
    const value_type input[] = { token::code::int32, 0xFE, 0xFF, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(), -2);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32_endian)
{
    const value_type input[] = { token::code::int32, 0x44, 0x33, 0x22, 0x11 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(), 0x11223344);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32_max)
{
    const value_type input[] = { token::code::int32, 0xFF, 0xFF, 0xFF, 0x7F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(),
                        std::numeric_limits<token::int32::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32_min)
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int32>(),
                        std::numeric_limits<token::int32::type>::min());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int32_missing_one)
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int32_missing_two)
{
    const value_type input[] = { token::code::int32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int32_missing_three)
{
    const value_type input[] = { token::code::int32, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int32_missing_four)
{
    const value_type input[] = { token::code::int32 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// 64-bit integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int64_zero)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int64);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int64>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int64_one)
{
    const value_type input[] = { token::code::int64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int64>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int64_minus_one)
{
    const value_type input[] = { token::code::int64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int64>(), -1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int64_endian)
{
    const value_type input[] = { token::code::int64, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int64>(), INT64_C(0x1122334455667788));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int64_max)
{
    const value_type input[] = { token::code::int64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int64>(),
                        std::numeric_limits<token::int64::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int64_min)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::int64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::int64>(),
                        std::numeric_limits<token::int64::type>::min());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_one)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_two)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_three)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_four)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_five)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_six)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_seven)
{
    const value_type input[] = { token::code::int64, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_int64_missing_eight)
{
    const value_type input[] = { token::code::int64 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// 32-bit floating-point
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float32_zero)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::floating);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(), 0.0f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_one)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(), 1.0f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_minus_one)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0xBF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(), -1.0f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_two)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0x40 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(), 2.0f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_minus_two)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0xC0 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(), -2.0f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_half)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0x3F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(), 0.5f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_minus_half)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0xBF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(), -0.5f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_max)
{
    const value_type input[] = { token::code::float32, 0xFF, 0xFF, 0x7F, 0x7F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(),
                        std::numeric_limits<token::float32::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_minus_max)
{
    const value_type input[] = { token::code::float32, 0xFF, 0xFF, 0x7F, 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(),
                        -std::numeric_limits<token::float32::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32_min)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float32>(),
                        std::numeric_limits<token::float32::type>::min());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float32_missing_one)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float32_missing_two)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float32_missing_three)
{
    const value_type input[] = { token::code::float32, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float32_missing_four)
{
    const value_type input[] = { token::code::float32 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// 64-bit floating-point
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float64_zero)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::floating);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(), 0.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_one)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(), 1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_minus_one)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xBF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(), -1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_two)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(), 2.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_minus_two)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(), -2.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_half)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(), 0.5);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_minus_half)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xBF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(), -0.5);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_max)
{
    const value_type input[] = { token::code::float64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x7F };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(),
                        std::numeric_limits<token::float64::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_minus_max)
{
    const value_type input[] = { token::code::float64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(),
                        -std::numeric_limits<token::float64::type>::max());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64_min)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::float64>(),
                        std::numeric_limits<token::float64::type>::min());
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_one)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_two)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_three)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_four)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_five)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_six)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_seven)
{
    const value_type input[] = { token::code::float64, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_float64_missing_eight)
{
    const value_type input[] = { token::code::float64 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// Containers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_record)
{
    const value_type input[] = { token::code::begin_record, token::code::end_record };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::begin_record);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::begin_record);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end_record);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::end_record);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_array)
{
    const value_type input[] = { token::code::begin_array, token::code::end_array };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::begin_array);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::begin_array);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end_array);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::end_array);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_assoc_array)
{
    const value_type input[] = { token::code::begin_assoc_array, token::code::end_assoc_array };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::begin_assoc_array);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::begin_assoc_array);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end_assoc_array);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::end_assoc_array);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string8_empty)
{
    const value_type input[] = { token::code::string8, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string8);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::string);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string16_empty)
{
    const value_type input[] = { token::code::string16, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string16);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::string);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string32_empty)
{
    const value_type input[] = { token::code::string32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string32);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::string);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string64_empty)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string64);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::string);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string8_one)
{
    const value_type input[] = { token::code::string8, 0x01, 0x41 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string16_one)
{
    const value_type input[] = { token::code::string16, 0x01, 0x00, 0x41 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string16);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string32_one)
{
    const value_type input[] = { token::code::string32, 0x01, 0x00, 0x00, 0x00, 0x41 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string64_one)
{
    const value_type input[] = { token::code::string64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string8_two)
{
    const value_type input[] = { token::code::string8, 0x02, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string8);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string16_two)
{
    const value_type input[] = { token::code::string16, 0x02, 0x00, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string16);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string32_two)
{
    const value_type input[] = { token::code::string32, 0x02, 0x00, 0x00, 0x00, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string32);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string64_two)
{
    const value_type input[] = { token::code::string64, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::string64);
    BOOST_REQUIRE_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string8_missing_length_one)
{
    const value_type input[] = { token::code::string8 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string16_missing_length_one)
{
    const value_type input[] = { token::code::string16, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string16_missing_length_two)
{
    const value_type input[] = { token::code::string16 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string32_missing_length_one)
{
    const value_type input[] = { token::code::string32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string32_missing_length_two)
{
    const value_type input[] = { token::code::string32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string32_missing_length_three)
{
    const value_type input[] = { token::code::string32, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string32_missing_length_four)
{
    const value_type input[] = { token::code::string32 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_one)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_two)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_three)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_four)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_five)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_six)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_seven)
{
    const value_type input[] = { token::code::string64, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string64_missing_length_eight)
{
    const value_type input[] = { token::code::string64 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_string_negative_length)
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::error_negative_length);
}

//-----------------------------------------------------------------------------
// Binary data
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_binary8_empty)
{
    const value_type input[] = { token::code::binary8, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary8);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::binary);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary16_empty)
{
    const value_type input[] = { token::code::binary16, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary16);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::binary);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary32_empty)
{
    const value_type input[] = { token::code::binary32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary32);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::binary);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary64_empty)
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary64);
    BOOST_REQUIRE_EQUAL(decoder.symbol(), token::symbol::binary);
    BOOST_REQUIRE_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary8_one)
{
    const value_type input[] = { token::code::binary8, 0x01, 0x12 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary8);
    const value_type expected[] = {
        0x12
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary16_one)
{
    const value_type input[] = { token::code::binary16, 0x01, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary16);
    const value_type expected[] = {
        0x12
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary32_one)
{
    const value_type input[] = { token::code::binary32, 0x01, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary32);
    const value_type expected[] = {
        0x12
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary64_one)
{
    const value_type input[] = { token::code::binary64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary64);
    const value_type expected[] = {
        0x12
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary8_two)
{
    const value_type input[] = { token::code::binary8, 0x02, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary8);
    const value_type expected[] = {
        0x12, 0x34
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary16_two)
{
    const value_type input[] = { token::code::binary16, 0x02, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary16);
    const value_type expected[] = {
        0x12, 0x34
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary32_two)
{
    const value_type input[] = { token::code::binary32, 0x02, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary32);
    const value_type expected[] = {
        0x12, 0x34
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary64_two)
{
    const value_type input[] = { token::code::binary64, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary64);
    const value_type expected[] = {
        0x12, 0x34
    };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_binary8_128)
{
    value_type input[2 + 0x80] = { token::code::binary8, 0x80 };
    std::fill_n(&input[2], sizeof(input) - 2, 0x12);
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::binary8);
    value_type expected[0x80];
    std::fill_n(&expected[0], sizeof(expected), 0x12);
    BOOST_REQUIRE_EQUAL_COLLECTIONS(decoder.literal().begin(), decoder.literal().end(),
                                    expected, expected + sizeof(expected));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary8_missing_length_one)
{
    const value_type input[] = { token::code::binary8 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary16_missing_length_one)
{
    const value_type input[] = { token::code::binary16, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary16_missing_length_two)
{
    const value_type input[] = { token::code::binary16 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary32_missing_length_one)
{
    const value_type input[] = { token::code::binary32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary32_missing_length_two)
{
    const value_type input[] = { token::code::binary32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary32_missing_length_three)
{
    const value_type input[] = { token::code::binary32, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary32_missing_length_four)
{
    const value_type input[] = { token::code::binary32 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_one)
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_two)
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_three)
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_four)
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_five)
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_six)
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_seven)
{
    const value_type input[] = { token::code::binary64, 0x00 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(fail_binary64_missing_length_eight)
{
    const value_type input[] = { token::code::binary64 };
    format::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.code(), token::code::end);
}

BOOST_AUTO_TEST_SUITE_END()
