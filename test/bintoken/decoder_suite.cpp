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
#include <algorithm> // std::fill_n
#include <functional>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/bintoken/detail/decoder.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using value_type = format::detail::decoder::value_type;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    const std::array<value_type, 0> input = {};
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::status);
}

void test_null()
{
    const value_type input[] = { token::code::null };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::null);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::nullable);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_false()
{
    const value_type input[] = { token::code::false_value };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::false_value);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_true()
{
    const value_type input[] = { token::code::true_value };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_null();
    test_false();
    test_true();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Small integers
//-----------------------------------------------------------------------------

namespace small_suite
{

void test_zero()
{
    const value_type input[] = { 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { 0x01 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const value_type input[] = { 0x7F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), 127);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const value_type input[] = { 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), -1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_max()
{
    const value_type input[] = { 0xE0 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), -32);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_zero();
    test_one();
    test_max();
    test_minus_one();
    test_minus_max();
}

} // namespace small_suite

//-----------------------------------------------------------------------------
// 8-bit integers
//-----------------------------------------------------------------------------

namespace int8_suite
{

void test_zero()
{
    const value_type input[] = { token::code::int8, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const value_type input[] = { token::code::int8, 0x7F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(),
                        std::numeric_limits<token::int8::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_min()
{
    const value_type input[] = { token::code::int8, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(),
                        std::numeric_limits<token::int8::type>::min());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_min_plus_one()
{
    const value_type input[] = { token::code::int8, 0x81 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(),
                        std::numeric_limits<token::int8::type>::min() + 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const value_type input[] = { token::code::int8, 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int8>(), -1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_one()
{
    const value_type input[] = { token::code::int8 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_zero();
    test_one();
    test_max();
    test_min();
    test_minus_min_plus_one();
    test_minus_one();
    fail_missing_one();
}

} // namespace int8_suite

//-----------------------------------------------------------------------------
// 16-bit integers
//-----------------------------------------------------------------------------

namespace int16_suite
{

void test_zero()
{
    const value_type input[] = { token::code::int16, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int16>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::int16, 0x01, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int16>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_endian()
{
    const value_type input[] = { token::code::int16, 0x22, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int16>(), 0x1122);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const value_type input[] = { token::code::int16, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int16>(), -1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const value_type input[] = { token::code::int16, 0xFF, 0x7F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int16>(),
                              std::numeric_limits<token::int16::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_min()
{
    const value_type input[] = { token::code::int16, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int16>(),
                              std::numeric_limits<token::int16::type>::min());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_one()
{
    const value_type input[] = { token::code::int16, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_two()
{
    const value_type input[] = { token::code::int16 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_zero();
    test_one();
    test_endian();
    test_minus_one();
    test_max();
    test_min();
    fail_missing_one();
    fail_missing_two();
}

} // namespace int16_suite

//-----------------------------------------------------------------------------
// 32-bit integers
//-----------------------------------------------------------------------------

namespace int32_suite
{

void test_zero()
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::int32, 0x01, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const value_type input[] = { token::code::int32, 0xFF, 0xFF, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(), -1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::int32, 0x02, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(), 2);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_two()
{
    const value_type input[] = { token::code::int32, 0xFE, 0xFF, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(), -2);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_endian()
{
    const value_type input[] = { token::code::int32, 0x44, 0x33, 0x22, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(), 0x11223344);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const value_type input[] = { token::code::int32, 0xFF, 0xFF, 0xFF, 0x7F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(),
                              std::numeric_limits<token::int32::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_min()
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int32>(),
                              std::numeric_limits<token::int32::type>::min());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_one()
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_two()
{
    const value_type input[] = { token::code::int32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_three()
{
    const value_type input[] = { token::code::int32, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_four()
{
    const value_type input[] = { token::code::int32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_two();
    test_minus_two();
    test_endian();
    test_max();
    test_min();
    fail_missing_one();
    fail_missing_two();
    fail_missing_three();
    fail_missing_four();
}

} // namespace int32_suite

//-----------------------------------------------------------------------------
// 64-bit integers
//-----------------------------------------------------------------------------

namespace int64_suite
{

void test_zero()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int64>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::int64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int64>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const value_type input[] = { token::code::int64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int64>(), -1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_endian()
{
    const value_type input[] = { token::code::int64, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int64>(), INT64_C(0x1122334455667788));
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const value_type input[] = { token::code::int64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int64>(),
                              std::numeric_limits<token::int64::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_min()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::int64>(),
                              std::numeric_limits<token::int64::type>::min());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_one()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_two()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_three()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_four()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_five()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_six()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_seven()
{
    const value_type input[] = { token::code::int64, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_eight()
{
    const value_type input[] = { token::code::int64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_endian();
    test_max();
    test_min();
    fail_missing_one();
    fail_missing_two();
    fail_missing_three();
    fail_missing_four();
    fail_missing_five();
    fail_missing_six();
    fail_missing_seven();
    fail_missing_eight();
}

} // namespace int64_suite

//-----------------------------------------------------------------------------
// 32-bit floating-point
//-----------------------------------------------------------------------------

namespace float32_suite
{

void test_zero()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(), 0.0f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(), 1.0f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0xBF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(), -1.0f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0x40 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(), 2.0f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_two()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0xC0 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(), -2.0f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_half()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(), 0.5f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_half()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00, 0xBF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(), -0.5f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const value_type input[] = { token::code::float32, 0xFF, 0xFF, 0x7F, 0x7F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(),
                              std::numeric_limits<token::float32::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_max()
{
    const value_type input[] = { token::code::float32, 0xFF, 0xFF, 0x7F, 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(),
                              -std::numeric_limits<token::float32::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_min()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float32>(),
                              std::numeric_limits<token::float32::type>::min());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_one()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_two()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_three()
{
    const value_type input[] = { token::code::float32, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_four()
{
    const value_type input[] = { token::code::float32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_two();
    test_minus_two();
    test_half();
    test_minus_half();
    test_max();
    test_minus_max();
    test_min();
    fail_missing_one();
    fail_missing_two();
    fail_missing_three();
    fail_missing_four();
}

} // namespace float32_suite

//-----------------------------------------------------------------------------
// 64-bit floating-point
//-----------------------------------------------------------------------------

namespace float64_suite
{

void test_zero()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(), 0.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(), 1.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xBF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(), -1.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(), 2.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_two()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(), -2.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_half()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(), 0.5);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_half()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xBF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(), -0.5);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const value_type input[] = { token::code::float64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0x7F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(),
                              std::numeric_limits<token::float64::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_max()
{
    const value_type input[] = { token::code::float64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEF, 0xFF };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(),
                              -std::numeric_limits<token::float64::type>::max());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_min()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::float64>(),
                              std::numeric_limits<token::float64::type>::min());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_one()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_two()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_three()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_four()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_five()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_six()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_seven()
{
    const value_type input[] = { token::code::float64, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_eight()
{
    const value_type input[] = { token::code::float64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_two();
    test_minus_two();
    test_half();
    test_minus_half();
    test_max();
    test_minus_max();
    test_min();
    fail_missing_one();
    fail_missing_two();
    fail_missing_three();
    fail_missing_four();
    fail_missing_five();
    fail_missing_six();
    fail_missing_seven();
    fail_missing_eight();
}

} // namespace float64_suite

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

namespace container_suite
{

void test_record()
{
    const value_type input[] = { token::code::begin_record, token::code::end_record };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_record);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::begin_record);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_record);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::end_record);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array()
{
    const value_type input[] = { token::code::begin_array, token::code::end_array };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_assoc_array()
{
    const value_type input[] = { token::code::begin_assoc_array, token::code::end_assoc_array };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::begin_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::end_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::structural);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_record();
    test_array();
    test_assoc_array();
}

} // namespace container_suite

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

namespace string8_suite
{

void test_empty()
{
    const value_type input[] = { token::code::string8, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}


void test_one()
{
    const value_type input[] = { token::code::string8, 0x01, 0x41 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::string8, 0x02, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::string8 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    fail_missing_length_one();
}

} // namespace string8_suite

namespace string16_suite
{

void test_empty()
{
    const value_type input[] = { token::code::string16, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::string16, 0x01, 0x00, 0x41 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::string16, 0x02, 0x00, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::string16, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_two()
{
    const value_type input[] = { token::code::string16 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    fail_missing_length_one();
    fail_missing_length_two();
}

} // namespace string16_suite

namespace string32_suite
{

void test_empty()
{
    const value_type input[] = { token::code::string32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::string32, 0x01, 0x00, 0x00, 0x00, 0x41 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::string32, 0x02, 0x00, 0x00, 0x00, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::string32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_two()
{
    const value_type input[] = { token::code::string32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_three()
{
    const value_type input[] = { token::code::string32, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_four()
{
    const value_type input[] = { token::code::string32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    fail_missing_length_one();
    fail_missing_length_two();
    fail_missing_length_three();
    fail_missing_length_four();
}

} // namespace string32_suite

namespace string64_suite
{

void test_empty()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::string64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "A");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::string64, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x42 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<token::string>(), "AB");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_two()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_three()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_four()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_five()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_six()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_seven()
{
    const value_type input[] = { token::code::string64, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_eight()
{
    const value_type input[] = { token::code::string64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_negative_length()
{
    const value_type input[] = { token::code::string64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_negative_length);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    fail_missing_length_one();
    fail_missing_length_two();
    fail_missing_length_three();
    fail_missing_length_four();
    fail_missing_length_five();
    fail_missing_length_six();
    fail_missing_length_seven();
    fail_missing_length_eight();
    fail_negative_length();
}

} // namespace string64_suite

//-----------------------------------------------------------------------------
// Binary data
//-----------------------------------------------------------------------------

namespace binary8_suite
{

void test_empty()
{
    const value_type input[] = { token::code::binary8, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::binary);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::binary8, 0x01, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary8);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::binary8, 0x02, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary8);
    const value_type expected[] = {
        0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_128()
{
    value_type input[2 + 0x80] = { token::code::binary8, 0x80 };
    std::fill_n(&input[2], sizeof(input) - 2, 0x12);
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary8);
    value_type expected[0x80];
    std::fill_n(&expected[0], sizeof(expected), 0x12);
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::binary8 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    test_128();
    fail_missing_length_one();
}

} // namespace binary8_suite

namespace binary16_suite
{

void test_empty()
{
    const value_type input[] = { token::code::binary16, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::binary);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::binary16, 0x01, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary16);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::binary16, 0x02, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary16);
    const value_type expected[] = {
        0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::binary16, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_two()
{
    const value_type input[] = { token::code::binary16 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    fail_missing_length_one();
    fail_missing_length_two();
}

} // namespace binary16_suite

namespace binary32_suite
{

void test_empty()
{
    const value_type input[] = { token::code::binary32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::binary);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::binary32, 0x01, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary32);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::binary32, 0x02, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary32);
    const value_type expected[] = {
        0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::binary32, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_two()
{
    const value_type input[] = { token::code::binary32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_three()
{
    const value_type input[] = { token::code::binary32, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_four()
{
    const value_type input[] = { token::code::binary32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    fail_missing_length_one();
    fail_missing_length_two();
    fail_missing_length_three();
    fail_missing_length_four();
}

} // namespace binary32_suite

namespace binary64_suite
{

void test_empty()
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::binary);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {};
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const value_type input[] = { token::code::binary64, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary64);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_two()
{
    const value_type input[] = { token::code::binary64, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::binary64);
    const value_type expected[] = {
        0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_one()
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_two()
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_three()
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_four()
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_five()
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_six()
{
    const value_type input[] = { token::code::binary64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_seven()
{
    const value_type input[] = { token::code::binary64, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_length_eight()
{
    const value_type input[] = { token::code::binary64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_empty();
    test_one();
    test_two();
    fail_missing_length_one();
    fail_missing_length_two();
    fail_missing_length_three();
    fail_missing_length_four();
    fail_missing_length_five();
    fail_missing_length_six();
    fail_missing_length_seven();
    fail_missing_length_eight();
}

} // namespace binary64_suite

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
    container_suite::run();
    string8_suite::run();
    string16_suite::run();
    string32_suite::run();
    string64_suite::run();
    binary8_suite::run();
    binary16_suite::run();
    binary32_suite::run();
    binary64_suite::run();

    return boost::report_errors();
}
