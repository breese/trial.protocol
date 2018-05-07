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
#include <memory> // std::uninitialized_fill_n
#include <functional>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/bintoken/detail/decoder.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

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
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::real);
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
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::real);
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

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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
// int8[N]
//-----------------------------------------------------------------------------

namespace compact_int8_suite
{

void test_array8_int8_empty()
{
    const value_type input[] = { token::code::array8_int8, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_int8_one()
{
    const value_type input[] = { token::code::array8_int8, 0x01, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int8);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_int8_two()
{
    const value_type input[] = { token::code::array8_int8, 0x02, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int8);
    {
        const value_type expected_literal[] = {
            0x12, 0x34
        };
        TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        std::array<std::int8_t, 2> value = {{ 0, 0 }};
        TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 2);
        const std::array<std::int8_t, 2> expected = {{
                0x12,
                0x34 }};
        TRIAL_PROTOCOL_TEST_ALL_WITH(value.begin(), value.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<value_type>());
    }
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_int8_128()
{
    value_type input[2 + 0x80] = { token::code::array8_int8, 0x80 };
    std::uninitialized_fill_n(&input[2], sizeof(input) - 2, 0x12);
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int8);
    value_type expected[0x80];
    std::uninitialized_fill_n(&expected[0], sizeof(expected), 0x12);
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int8_missing_one()
{
    const value_type input[] = { token::code::array8_int8, 0x01 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int8_missing_length()
{
    const value_type input[] = { token::code::array8_int8 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int8_overflow()
{
    const value_type input[] = { token::code::array8_int8, 0x02, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    std::array<std::int8_t, 1> value = {};
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 1);
}

//-----------------------------------------------------------------------------

void test_array16_int8_empty()
{
    const value_type input[] = { token::code::array16_int8, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_int8_one()
{
    const value_type input[] = { token::code::array16_int8, 0x01, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int8);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_int8_two()
{
    const value_type input[] = { token::code::array16_int8, 0x02, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int8);
    const value_type expected[] = {
        0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int8_missing_one()
{
    const value_type input[] = { token::code::array16_int8, 0x01, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int8_missing_length_one()
{
    const value_type input[] = { token::code::array16_int8, 0x01 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int8_missing_length_two()
{
    const value_type input[] = { token::code::array16_int8 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------

void test_array32_int8_empty()
{
    const value_type input[] = { token::code::array32_int8, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_int8_one()
{
    const value_type input[] = { token::code::array32_int8, 0x01, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int8);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_int8_two()
{
    const value_type input[] = { token::code::array32_int8, 0x02, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int8);
    const value_type expected[] = {
        0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int8_missing_one()
{
    const value_type input[] = { token::code::array32_int8, 0x01, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int8_missing_length_one()
{
    const value_type input[] = { token::code::array32_int8, 0x01, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int8_missing_length_two()
{
    const value_type input[] = { token::code::array32_int8, 0x01, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int8_missing_length_three()
{
    const value_type input[] = { token::code::array32_int8, 0x01 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int8_missing_length_four()
{
    const value_type input[] = { token::code::array32_int8 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

//-----------------------------------------------------------------------------

void test_array64_int8_empty()
{
    const value_type input[] = { token::code::array64_int8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int8);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_int8_one()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int8);
    const value_type expected[] = {
        0x12
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_int8_two()
{
    const value_type input[] = { token::code::array64_int8, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int8);
    const value_type expected[] = {
        0x12, 0x34
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_one()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_one()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_two()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_three()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_four()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_five()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_six()
{
    const value_type input[] = { token::code::array64_int8, 0x01, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_seven()
{
    const value_type input[] = { token::code::array64_int8, 0x01 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int8_missing_length_eight()
{
    const value_type input[] = { token::code::array64_int8 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_array8_int8_empty();
    test_array8_int8_one();
    test_array8_int8_two();
    test_array8_int8_128();
    fail_array8_int8_missing_one();
    fail_array8_int8_missing_length();
    fail_array8_int8_overflow();

    test_array16_int8_empty();
    test_array16_int8_one();
    test_array16_int8_two();
    fail_array16_int8_missing_one();
    fail_array16_int8_missing_length_one();
    fail_array16_int8_missing_length_two();

    test_array32_int8_empty();
    test_array32_int8_one();
    test_array32_int8_two();
    fail_array32_int8_missing_one();
    fail_array32_int8_missing_length_one();
    fail_array32_int8_missing_length_two();
    fail_array32_int8_missing_length_three();
    fail_array32_int8_missing_length_four();

    test_array64_int8_empty();
    test_array64_int8_one();
    test_array64_int8_two();
    fail_array64_int8_missing_one();
    fail_array64_int8_missing_length_one();
    fail_array64_int8_missing_length_two();
    fail_array64_int8_missing_length_three();
    fail_array64_int8_missing_length_four();
    fail_array64_int8_missing_length_five();
    fail_array64_int8_missing_length_six();
    fail_array64_int8_missing_length_seven();
    fail_array64_int8_missing_length_eight();
}

} // namespace compact_int8_suite

//-----------------------------------------------------------------------------
// int16[N]
//-----------------------------------------------------------------------------

namespace compact_int16_suite
{

void test_array8_int16()
{
    const value_type input[] = { token::code::array8_int16, 0x04, 0x12, 0x34, 0x56, 0x78 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    {
        const value_type expected_literal[] = {
            0x12, 0x34, 0x56, 0x78
        };
        TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        std::array<std::int16_t, 2> value = {{ 0, 0 }};
        TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 2);
        const std::array<std::int16_t, 2> expected = {{
                0x3412,
                0x7856 }};
        TRIAL_PROTOCOL_TEST_ALL_WITH(value.begin(), value.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<std::int16_t>());
    }
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int16_missing_one()
{
    const value_type input[] = { token::code::array8_int16, 0x04, 0x12, 0x34, 0x56 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int16_missing_two()
{
    const value_type input[] = { token::code::array8_int16, 0x04, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int16_missing_three()
{
    const value_type input[] = { token::code::array8_int16, 0x04, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int16_missing_four()
{
    const value_type input[] = { token::code::array8_int16, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int16_missing_length()
{
    const value_type input[] = { token::code::array8_int16 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int16_invalid_length()
{
    const value_type input[] = { token::code::array8_int16, 0x03, 0x12, 0x34, 0x56 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void fail_array8_int16_overflow()
{
    const value_type input[] = { token::code::array8_int16, 0x04, 0x12, 0x34, 0x56, 0x78 };
    format::detail::decoder decoder(input);
    std::array<std::int16_t, 1> value = {};
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 1);
}

//-----------------------------------------------------------------------------

void test_array16_int16()
{
    const value_type input[] = { token::code::array16_int16, 0x04, 0x00, 0x12, 0x34, 0x56, 0x78 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x12, 0x34, 0x56, 0x78
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int16_missing_one()
{
    const value_type input[] = { token::code::array16_int16, 0x04, 0x00, 0x12, 0x34, 0x56 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int16_missing_two()
{
    const value_type input[] = { token::code::array16_int16, 0x04, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int16_missing_three()
{
    const value_type input[] = { token::code::array16_int16, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int16_missing_four()
{
    const value_type input[] = { token::code::array16_int16, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int16_missing_length_one()
{
    const value_type input[] = { token::code::array16_int16, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int16_missing_length_two()
{
    const value_type input[] = { token::code::array16_int16 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int16_invalid_length()
{
    const value_type input[] = { token::code::array16_int16, 0x03, 0x00, 0x12, 0x34, 0x56 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array32_int16()
{
    const value_type input[] = { token::code::array32_int16, 0x04, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x12, 0x34, 0x56, 0x78
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_one()
{
    const value_type input[] = { token::code::array32_int16, 0x04, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_two()
{
    const value_type input[] = { token::code::array32_int16, 0x04, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_three()
{
    const value_type input[] = { token::code::array32_int16, 0x04, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_four()
{
    const value_type input[] = { token::code::array32_int16, 0x04, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_length_one()
{
    const value_type input[] = { token::code::array32_int16, 0x04, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_length_two()
{
    const value_type input[] = { token::code::array32_int16, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_length_three()
{
    const value_type input[] = { token::code::array32_int16, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_missing_length_four()
{
    const value_type input[] = { token::code::array32_int16 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int16_invalid_length()
{
    const value_type input[] = { token::code::array32_int16, 0x03, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array64_int16()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int16);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x12, 0x34, 0x56, 0x78
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_one()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_two()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_three()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_four()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_one()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_two()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_three()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_four()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_five()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_six()
{
    const value_type input[] = { token::code::array64_int16, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_seven()
{
    const value_type input[] = { token::code::array64_int16, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_missing_length_eight()
{
    const value_type input[] = { token::code::array64_int16 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int16_invalid_length()
{
    const value_type input[] = { token::code::array64_int16, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x34, 0x56, 0x78 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void run()
{
    test_array8_int16();
    fail_array8_int16_missing_one();
    fail_array8_int16_missing_two();
    fail_array8_int16_missing_three();
    fail_array8_int16_missing_four();
    fail_array8_int16_missing_length();
    fail_array8_int16_invalid_length();
    fail_array8_int16_overflow();

    test_array16_int16();
    fail_array16_int16_missing_one();
    fail_array16_int16_missing_two();
    fail_array16_int16_missing_three();
    fail_array16_int16_missing_four();
    fail_array16_int16_missing_length_one();
    fail_array16_int16_missing_length_two();
    fail_array16_int16_invalid_length();

    test_array32_int16();
    fail_array32_int16_missing_one();
    fail_array32_int16_missing_two();
    fail_array32_int16_missing_three();
    fail_array32_int16_missing_four();
    fail_array32_int16_missing_length_one();
    fail_array32_int16_missing_length_two();
    fail_array32_int16_missing_length_three();
    fail_array32_int16_missing_length_four();
    fail_array32_int16_invalid_length();

    test_array64_int16();
    fail_array64_int16_missing_one();
    fail_array64_int16_missing_two();
    fail_array64_int16_missing_three();
    fail_array64_int16_missing_four();
    fail_array64_int16_missing_length_one();
    fail_array64_int16_missing_length_two();
    fail_array64_int16_missing_length_three();
    fail_array64_int16_missing_length_four();
    fail_array64_int16_missing_length_five();
    fail_array64_int16_missing_length_six();
    fail_array64_int16_missing_length_seven();
    fail_array64_int16_missing_length_eight();
    fail_array64_int16_invalid_length();
}

} // namespace compact_int16_suite

//-----------------------------------------------------------------------------
// int32[N]
//-----------------------------------------------------------------------------

namespace compact_int32_suite
{

void test_array8_int32()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_one()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_two()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_three()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_four()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_five()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_six()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_seven()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_eight()
{
    const value_type input[] = { token::code::array8_int32, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_missing_length()
{
    const value_type input[] = { token::code::array8_int32, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int32_invalid_length()
{
    const value_type input[] = { token::code::array8_int32, 0x07, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void fail_array8_int32_overflow()
{
    const value_type input[] = { token::code::array8_int32, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    std::array<std::int32_t, 1> value = {};
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 1);
}

//-----------------------------------------------------------------------------

void test_array16_int32()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_one()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_two()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_three()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_four()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_five()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_six()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_seven()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_eight()
{
    const value_type input[] = { token::code::array16_int32, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_length_one()
{
    const value_type input[] = { token::code::array16_int32, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_missing_length_two()
{
    const value_type input[] = { token::code::array16_int32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int32_invalid_length()
{
    const value_type input[] = { token::code::array16_int32, 0x07, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array32_int32()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_one()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_two()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_three()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_four()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_five()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_six()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_seven()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_eight()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_length_one()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_length_two()
{
    const value_type input[] = { token::code::array32_int32, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_length_three()
{
    const value_type input[] = { token::code::array32_int32, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_missing_length_four()
{
    const value_type input[] = { token::code::array32_int32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int32_invalid_length()
{
    const value_type input[] = { token::code::array32_int32, 0x07, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array64_int32()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44,
        0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_one()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_two()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_three()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_four()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_five()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_six()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_seven()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_eight()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_one()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_two()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_three()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_four()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_five()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_six()
{
    const value_type input[] = { token::code::array64_int32, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_seven()
{
    const value_type input[] = { token::code::array64_int32, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_missing_length_eight()
{
    const value_type input[] = { token::code::array64_int32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int32_invalid_length()
{
    const value_type input[] = { token::code::array64_int32, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void run()
{
    test_array8_int32();
    fail_array8_int32_missing_one();
    fail_array8_int32_missing_two();
    fail_array8_int32_missing_three();
    fail_array8_int32_missing_four();
    fail_array8_int32_missing_five();
    fail_array8_int32_missing_six();
    fail_array8_int32_missing_seven();
    fail_array8_int32_missing_eight();
    fail_array8_int32_missing_length();
    fail_array8_int32_invalid_length();
    fail_array8_int32_overflow();

    test_array16_int32();
    fail_array16_int32_missing_one();
    fail_array16_int32_missing_two();
    fail_array16_int32_missing_three();
    fail_array16_int32_missing_four();
    fail_array16_int32_missing_five();
    fail_array16_int32_missing_six();
    fail_array16_int32_missing_seven();
    fail_array16_int32_missing_eight();
    fail_array16_int32_missing_length_one();
    fail_array16_int32_missing_length_two();
    fail_array16_int32_invalid_length();

    test_array32_int32();
    fail_array32_int32_missing_one();
    fail_array32_int32_missing_two();
    fail_array32_int32_missing_three();
    fail_array32_int32_missing_four();
    fail_array32_int32_missing_five();
    fail_array32_int32_missing_six();
    fail_array32_int32_missing_seven();
    fail_array32_int32_missing_eight();
    fail_array32_int32_missing_length_one();
    fail_array32_int32_missing_length_two();
    fail_array32_int32_missing_length_three();
    fail_array32_int32_missing_length_four();
    fail_array32_int32_invalid_length();

    test_array64_int32();
    fail_array64_int32_missing_one();
    fail_array64_int32_missing_two();
    fail_array64_int32_missing_three();
    fail_array64_int32_missing_four();
    fail_array64_int32_missing_five();
    fail_array64_int32_missing_six();
    fail_array64_int32_missing_seven();
    fail_array64_int32_missing_eight();
    fail_array64_int32_missing_length_one();
    fail_array64_int32_missing_length_two();
    fail_array64_int32_missing_length_three();
    fail_array64_int32_missing_length_four();
    fail_array64_int32_missing_length_five();
    fail_array64_int32_missing_length_six();
    fail_array64_int32_missing_length_seven();
    fail_array64_int32_missing_length_eight();
    fail_array64_int32_invalid_length();
}

} // namespace compact_int32_suite

//-----------------------------------------------------------------------------
// int64[N]
//-----------------------------------------------------------------------------

namespace compact_int64_suite
{

void test_array8_int64_empty()
{
    const value_type input[] = { token::code::array8_int64, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_int64_one()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_int64_two()
{
    const value_type input[] = { token::code::array8_int64, 0x10, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_one()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_two()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_three()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_four()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_five()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_six()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_seven()
{
    const value_type input[] = { token::code::array8_int64, 0x08, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_eight()
{
    const value_type input[] = { token::code::array8_int64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_missing_length_one()
{
    const value_type input[] = { token::code::array8_int64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_int64_invalid_length()
{
    const value_type input[] = { token::code::array8_int64, 0x07, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void fail_array8_int64_overflow()
{
    const value_type input[] = { token::code::array8_int64, 0x10, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };
    format::detail::decoder decoder(input);
    std::array<std::int64_t, 1> value = {};
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 1);
}

//-----------------------------------------------------------------------------

void test_array16_int64_empty()
{
    const value_type input[] = { token::code::array16_int64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_int64_one()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_int64_two()
{
    const value_type input[] = { token::code::array16_int64, 0x10, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_one()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_two()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_three()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_four()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_five()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_six()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_seven()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_eight()
{
    const value_type input[] = { token::code::array16_int64, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_length_one()
{
    const value_type input[] = { token::code::array16_int64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_missing_length_two()
{
    const value_type input[] = { token::code::array16_int64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_int64_invalid_length()
{
    const value_type input[] = { token::code::array16_int64, 0x07, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array32_int64_empty()
{
    const value_type input[] = { token::code::array32_int64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_int64_one()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_int64_two()
{
    const value_type input[] = { token::code::array32_int64, 0x10, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_one()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_two()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_three()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_four()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_five()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_six()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_seven()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_eight()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_length_one()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_length_two()
{
    const value_type input[] = { token::code::array32_int64, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_length_three()
{
    const value_type input[] = { token::code::array32_int64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_missing_length_four()
{
    const value_type input[] = { token::code::array32_int64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_int64_invalid_length()
{
    const value_type input[] = { token::code::array32_int64, 0x0F, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array64_int64_empty()
{
    const value_type input[] = { token::code::array64_int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_int64_one()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_int64_two()
{
    const value_type input[] = { token::code::array64_int64, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88,
        0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_one()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_two()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_three()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_four()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_five()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_six()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_seven()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_eight()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_one()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_two()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_three()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_four()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_five()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_six()
{
    const value_type input[] = { token::code::array64_int64, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_seven()
{
    const value_type input[] = { token::code::array64_int64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_missing_length_eight()
{
    const value_type input[] = { token::code::array64_int64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_int64_invalid_length()
{
    const value_type input[] = { token::code::array64_int64, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void run()
{
    test_array8_int64_empty();
    test_array8_int64_one();
    test_array8_int64_two();
    fail_array8_int64_missing_one();
    fail_array8_int64_missing_two();
    fail_array8_int64_missing_three();
    fail_array8_int64_missing_four();
    fail_array8_int64_missing_five();
    fail_array8_int64_missing_six();
    fail_array8_int64_missing_seven();
    fail_array8_int64_missing_eight();
    fail_array8_int64_missing_length_one();
    fail_array8_int64_invalid_length();
    fail_array8_int64_overflow();

    test_array16_int64_empty();
    test_array16_int64_one();
    test_array16_int64_two();
    fail_array16_int64_missing_one();
    fail_array16_int64_missing_two();
    fail_array16_int64_missing_three();
    fail_array16_int64_missing_four();
    fail_array16_int64_missing_five();
    fail_array16_int64_missing_six();
    fail_array16_int64_missing_seven();
    fail_array16_int64_missing_eight();
    fail_array16_int64_missing_length_one();
    fail_array16_int64_missing_length_two();
    fail_array16_int64_invalid_length();

    test_array32_int64_empty();
    test_array32_int64_one();
    test_array32_int64_two();
    fail_array32_int64_missing_one();
    fail_array32_int64_missing_two();
    fail_array32_int64_missing_three();
    fail_array32_int64_missing_four();
    fail_array32_int64_missing_five();
    fail_array32_int64_missing_six();
    fail_array32_int64_missing_seven();
    fail_array32_int64_missing_eight();
    fail_array32_int64_missing_length_one();
    fail_array32_int64_missing_length_two();
    fail_array32_int64_missing_length_three();
    fail_array32_int64_missing_length_four();
    fail_array32_int64_invalid_length();

    test_array64_int64_empty();
    test_array64_int64_one();
    test_array64_int64_two();
    fail_array64_int64_missing_one();
    fail_array64_int64_missing_two();
    fail_array64_int64_missing_three();
    fail_array64_int64_missing_four();
    fail_array64_int64_missing_five();
    fail_array64_int64_missing_six();
    fail_array64_int64_missing_seven();
    fail_array64_int64_missing_eight();
    fail_array64_int64_missing_length_one();
    fail_array64_int64_missing_length_two();
    fail_array64_int64_missing_length_three();
    fail_array64_int64_missing_length_four();
    fail_array64_int64_missing_length_five();
    fail_array64_int64_missing_length_six();
    fail_array64_int64_missing_length_seven();
    fail_array64_int64_missing_length_eight();
    fail_array64_int64_invalid_length();
}

} // namespace compact_int64_suite

//-----------------------------------------------------------------------------
// float32[N]
//-----------------------------------------------------------------------------

namespace compact_float32_suite
{

void test_array8_float32_empty()
{
    const value_type input[] = { token::code::array8_float32, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_float32_one()
{
    const value_type input[] = { token::code::array8_float32, 0x04, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_float32_two()
{
    const value_type input[] = { token::code::array8_float32, 0x08, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float32_missing_one()
{
    const value_type input[] = { token::code::array8_float32, 0x04, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float32_missing_two()
{
    const value_type input[] = { token::code::array8_float32, 0x04, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float32_missing_three()
{
    const value_type input[] = { token::code::array8_float32, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float32_missing_four()
{
    const value_type input[] = { token::code::array8_float32, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float32_missing_length_one()
{
    const value_type input[] = { token::code::array8_float32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float32_invalid_length()
{
    const value_type input[] = { token::code::array8_float32, 0x03, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void fail_array8_float32_overflow()
{
    const value_type input[] = { token::code::array8_float32, 0x08, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    std::array<token::float32::type, 1> value = {};
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 1);
}

//-----------------------------------------------------------------------------

void test_array16_float32_empty()
{
    const value_type input[] = { token::code::array16_float32, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_float32_one()
{
    const value_type input[] = { token::code::array16_float32, 0x04, 0x00, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_float32_two()
{
    const value_type input[] = { token::code::array16_float32, 0x08, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float32_missing_one()
{
    const value_type input[] = { token::code::array16_float32, 0x04, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float32_missing_two()
{
    const value_type input[] = { token::code::array16_float32, 0x04, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float32_missing_three()
{
    const value_type input[] = { token::code::array16_float32, 0x04, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float32_missing_four()
{
    const value_type input[] = { token::code::array16_float32, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float32_missing_length_one()
{
    const value_type input[] = { token::code::array16_float32, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float32_missing_length_two()
{
    const value_type input[] = { token::code::array16_float32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float32_invalid_length()
{
    const value_type input[] = { token::code::array16_float32, 0x03, 0x00, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array32_float32_empty()
{
    const value_type input[] = { token::code::array32_float32, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_float32_one()
{
    const value_type input[] = { token::code::array32_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_float32_two()
{
    const value_type input[] = { token::code::array32_float32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_one()
{
    const value_type input[] = { token::code::array32_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_two()
{
    const value_type input[] = { token::code::array32_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_three()
{
    const value_type input[] = { token::code::array32_float32, 0x04, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_four()
{
    const value_type input[] = { token::code::array32_float32, 0x04, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_length_one()
{
    const value_type input[] = { token::code::array32_float32, 0x04, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_length_two()
{
    const value_type input[] = { token::code::array32_float32, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_length_three()
{
    const value_type input[] = { token::code::array32_float32, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_missing_length_four()
{
    const value_type input[] = { token::code::array32_float32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float32_invalid_length()
{
    const value_type input[] = { token::code::array32_float32, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array64_float32_empty()
{
    const value_type input[] = { token::code::array64_float32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_float32_one()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_float32_two()
{
    const value_type input[] = { token::code::array64_float32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x80, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_one()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_two()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_three()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_four()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_one()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_two()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_three()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_four()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_five()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_six()
{
    const value_type input[] = { token::code::array64_float32, 0x04, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_seven()
{
    const value_type input[] = { token::code::array64_float32, 0x04 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_missing_length_eight()
{
    const value_type input[] = { token::code::array64_float32 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float32_invalid_length()
{
    const value_type input[] = { token::code::array64_float32, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void run()
{
    test_array8_float32_empty();
    test_array8_float32_one();
    test_array8_float32_two();
    fail_array8_float32_missing_one();
    fail_array8_float32_missing_two();
    fail_array8_float32_missing_three();
    fail_array8_float32_missing_four();
    fail_array8_float32_missing_length_one();
    fail_array8_float32_invalid_length();
    fail_array8_float32_overflow();

    test_array16_float32_empty();
    test_array16_float32_one();
    test_array16_float32_two();
    fail_array16_float32_missing_one();
    fail_array16_float32_missing_two();
    fail_array16_float32_missing_three();
    fail_array16_float32_missing_four();
    fail_array16_float32_missing_length_one();
    fail_array16_float32_missing_length_two();
    fail_array16_float32_invalid_length();

    test_array32_float32_empty();
    test_array32_float32_one();
    test_array32_float32_two();
    fail_array32_float32_missing_one();
    fail_array32_float32_missing_two();
    fail_array32_float32_missing_three();
    fail_array32_float32_missing_four();
    fail_array32_float32_missing_length_one();
    fail_array32_float32_missing_length_two();
    fail_array32_float32_missing_length_three();
    fail_array32_float32_missing_length_four();
    fail_array32_float32_invalid_length();

    test_array64_float32_empty();
    test_array64_float32_one();
    test_array64_float32_two();
    fail_array64_float32_missing_one();
    fail_array64_float32_missing_two();
    fail_array64_float32_missing_three();
    fail_array64_float32_missing_four();
    fail_array64_float32_missing_length_one();
    fail_array64_float32_missing_length_two();
    fail_array64_float32_missing_length_three();
    fail_array64_float32_missing_length_four();
    fail_array64_float32_missing_length_five();
    fail_array64_float32_missing_length_six();
    fail_array64_float32_missing_length_seven();
    fail_array64_float32_missing_length_eight();
    fail_array64_float32_invalid_length();
}

} // namespace compact_float32_suite

//-----------------------------------------------------------------------------
// float64[N]
//-----------------------------------------------------------------------------

namespace compact_float64_suite
{

void test_array8_float64_empty()
{
    const value_type input[] = { token::code::array8_float64, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_float64_one()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array8_float64_two()
{
    const value_type input[] = { token::code::array8_float64, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array8_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_one()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_two()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_three()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_four()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_five()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_six()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_seven()
{
    const value_type input[] = { token::code::array8_float64, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_eight()
{
    const value_type input[] = { token::code::array8_float64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_missing_length_one()
{
    const value_type input[] = { token::code::array8_float64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array8_float64_invalid_length()
{
    const value_type input[] = { token::code::array8_float64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void fail_array8_float64_overflow()
{
    const value_type input[] = { token::code::array8_float64, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    std::array<token::float64::type, 1> value = {};
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.array(value.data(), value.size()), 1);
}

//-----------------------------------------------------------------------------

void test_array16_float64_empty()
{
    const value_type input[] = { token::code::array16_float64, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_float64_one()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array16_float64_two()
{
    const value_type input[] = { token::code::array16_float64, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array16_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_one()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_two()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_three()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_four()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_five()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_six()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_seven()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_eight()
{
    const value_type input[] = { token::code::array16_float64, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_length_one()
{
    const value_type input[] = { token::code::array16_float64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_missing_length_two()
{
    const value_type input[] = { token::code::array16_float64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array16_float64_invalid_length()
{
    const value_type input[] = { token::code::array16_float64, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array32_float64_empty()
{
    const value_type input[] = { token::code::array32_float64, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_float64_one()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array32_float64_two()
{
    const value_type input[] = { token::code::array32_float64, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array32_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_one()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_two()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_three()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_four()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_five()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_six()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_seven()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_eight()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_length_one()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_length_two()
{
    const value_type input[] = { token::code::array32_float64, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_length_three()
{
    const value_type input[] = { token::code::array32_float64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_missing_length_four()
{
    const value_type input[] = { token::code::array32_float64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array32_float64_invalid_length()
{
    const value_type input[] = { token::code::array32_float64, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

//-----------------------------------------------------------------------------

void test_array64_float64_empty()
{
    const value_type input[] = { token::code::array64_float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(decoder.literal().empty());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_float64_one()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array64_float64_two()
{
    const value_type input[] = { token::code::array64_float64, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::array64_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.category(), token::category::data);
    const value_type expected[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(decoder.literal().begin(), decoder.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_one()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_two()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_three()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_four()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_five()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_six()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_seven()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_eight()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_one()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_two()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_three()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_four()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_five()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_six()
{
    const value_type input[] = { token::code::array64_float64, 0x08, 0x00 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_seven()
{
    const value_type input[] = { token::code::array64_float64, 0x08 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_missing_length_eight()
{
    const value_type input[] = { token::code::array64_float64 };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_array64_float64_invalid_length()
{
    const value_type input[] = { token::code::array64_float64, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_invalid_length);
}

void run()
{
    test_array8_float64_empty();
    test_array8_float64_one();
    test_array8_float64_two();
    fail_array8_float64_missing_one();
    fail_array8_float64_missing_two();
    fail_array8_float64_missing_three();
    fail_array8_float64_missing_four();
    fail_array8_float64_missing_five();
    fail_array8_float64_missing_six();
    fail_array8_float64_missing_seven();
    fail_array8_float64_missing_eight();
    fail_array8_float64_missing_length_one();
    fail_array8_float64_invalid_length();
    fail_array8_float64_overflow();

    test_array16_float64_empty();
    test_array16_float64_one();
    test_array16_float64_two();
    fail_array16_float64_missing_one();
    fail_array16_float64_missing_two();
    fail_array16_float64_missing_three();
    fail_array16_float64_missing_four();
    fail_array16_float64_missing_five();
    fail_array16_float64_missing_six();
    fail_array16_float64_missing_seven();
    fail_array16_float64_missing_eight();
    fail_array16_float64_missing_length_one();
    fail_array16_float64_missing_length_two();
    fail_array16_float64_invalid_length();

    test_array32_float64_empty();
    test_array32_float64_one();
    test_array32_float64_two();
    fail_array32_float64_missing_one();
    fail_array32_float64_missing_two();
    fail_array32_float64_missing_three();
    fail_array32_float64_missing_four();
    fail_array32_float64_missing_five();
    fail_array32_float64_missing_six();
    fail_array32_float64_missing_seven();
    fail_array32_float64_missing_eight();
    fail_array32_float64_missing_length_one();
    fail_array32_float64_missing_length_two();
    fail_array32_float64_missing_length_three();
    fail_array32_float64_missing_length_four();
    fail_array32_float64_invalid_length();

    test_array64_float64_empty();
    test_array64_float64_one();
    test_array64_float64_two();
    fail_array64_float64_missing_one();
    fail_array64_float64_missing_two();
    fail_array64_float64_missing_three();
    fail_array64_float64_missing_four();
    fail_array64_float64_missing_five();
    fail_array64_float64_missing_six();
    fail_array64_float64_missing_seven();
    fail_array64_float64_missing_eight();
    fail_array64_float64_missing_length_one();
    fail_array64_float64_missing_length_two();
    fail_array64_float64_missing_length_three();
    fail_array64_float64_missing_length_four();
    fail_array64_float64_missing_length_five();
    fail_array64_float64_missing_length_six();
    fail_array64_float64_missing_length_seven();
    fail_array64_float64_missing_length_eight();
    fail_array64_float64_invalid_length();
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
    container_suite::run();
    string8_suite::run();
    string16_suite::run();
    string32_suite::run();
    string64_suite::run();
    compact_int8_suite::run();
    compact_int16_suite::run();
    compact_int32_suite::run();
    compact_int64_suite::run();
    compact_float32_suite::run();
    compact_float64_suite::run();

    return boost::report_errors();
}
