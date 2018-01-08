///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <limits>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/bintoken/reader.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using value_type = format::reader::value_type;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void value_empty()
{
    const std::array<value_type, 0> input = {};
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::status);
    TRIAL_PROTOCOL_TEST(reader.length() == 0);
}

void value_false()
{
    const value_type input[] = { token::code::false_value };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::false_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    // Without conversion
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::boolean>(), false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int8>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int16>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int64>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float64>(),
                                    format::error, "incompatible type");
    // With conversion
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<int>(),
                                    format::error, "invalid value");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_false()
{
    const value_type input[] = { token::code::false_value };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_NO_THROW(reader.array(&result, 1));
        TRIAL_PROTOCOL_TEST_EQUAL(result, false);
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_true()
{
    const value_type input[] = { token::code::true_value };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::boolean>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_null()
{
    const value_type input[] = { token::code::null };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::nullable);
    TRIAL_PROTOCOL_TEST(reader.length() == 0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::boolean>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<bool>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_null()
{
    const value_type input[] = { token::code::null };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 0);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    value_empty();
    value_false();
    output_false();
    value_true();
    value_null();
    output_null();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Numbers
//-----------------------------------------------------------------------------

namespace number_suite
{

void value_int8()
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    // Without conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::boolean>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int8>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int16>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int64>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float64>(),
                                    format::error, "incompatible type");
    // With conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::boolean::type>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int8::type>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int16::type>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int32::type>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64::type>(), UINT64_C(1));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::intmax_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_int8()
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_NO_THROW(reader.array(&result, 1));
        TRIAL_PROTOCOL_TEST_EQUAL(result, 1);
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_uint8()
{
    const value_type input[] = {
        0x00,
        0x7F,
        token::code::int8, 0xD0,
        0xFF
    };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint8_t>(), 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint16_t>(), 0x0000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x00000000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x0000000000000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint8_t>(), 0x7F);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint16_t>(), 0x007F);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x0000007F);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x000000000000007F));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint8_t>(), 0xD0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint16_t>(), 0x00D0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x000000D0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x00000000000000D0));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint8_t>(), 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint16_t>(), 0x00FF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x000000FF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x00000000000000FF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_int16()
{
    const value_type input[] = { token::code::int16, 0x00, 0x01 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    // Without conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::boolean>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int8>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int16>(), 0x100);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int64>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float64>(),
                                    format::error, "incompatible type");
    // With conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::int8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int16::type>(), 0x100);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int32::type>(), 0x100);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x0100));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 256.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 256.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_int16()
{
    const value_type input[] = { token::code::int16, 0x00, 0x01 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_NO_THROW(reader.array(&result, 1));
        TRIAL_PROTOCOL_TEST_EQUAL(result, INT16_C(0x0100));
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_uint16()
{
    const value_type input[] = {
        token::code::int16, 0xFF, 0x7F,
        token::code::int16, 0x00, 0x80,
        token::code::int16, 0xFF, 0xFF
    };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint16_t>(), 0x7FFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x00007FFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x0000000000007FFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint16_t>(), 0x8000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x00008000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint16_t>(), 0xFFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x0000FFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_int32()
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x01, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    // Without conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::boolean>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int8>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int16>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int32>(), 0x10000);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int64>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float64>(),
                                    format::error, "incompatible type");
    // With conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::int8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::int16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int32::type>(), 0x10000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x10000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 65536.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 65536.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_int32()
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x01, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_NO_THROW(reader.array(&result, 1));
        TRIAL_PROTOCOL_TEST_EQUAL(result, INT32_C(0x010000));
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_uint32()
{
    const value_type input[] = {
        token::code::int32, 0xFF, 0xFF, 0xFF, 0x7F,
        token::code::int32, 0x00, 0x00, 0x00, 0x80,
        token::code::int32, 0xFF, 0xFF, 0xFF, 0xFF
    };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x7FFFFFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x000000007FFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0x80000000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x0000000080000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint32_t>(), 0xFFFFFFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x00000000FFFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_int64()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    // Without conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::boolean>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int8>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int16>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::int32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64>(), UINT64_C(0x100000000));
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float32>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::float64>(),
                                    format::error, "incompatible type");
    // With conversion
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::int8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::int16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::int32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x100000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 4294967296.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 4294967296.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_int64()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_NO_THROW(reader.array(&result, 1));
        TRIAL_PROTOCOL_TEST_EQUAL(result, INT64_C(0x0100000000));
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_uint64()
{
    const value_type input[] = {
        token::code::int64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
        token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
        token::code::int64, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x7FFFFFFFFFFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0x8000000000000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<std::uint32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::uint64_t>(), UINT64_C(0xFFFFFFFFFFFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_float32()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int8_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int16_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int32_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int64_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_float32()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_NO_THROW(reader.array(&result, 1));
        TRIAL_PROTOCOL_TEST_EQUAL(result, 1.0f);
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void value_float64()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int8_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int16_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int32_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::int64_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void output_float64()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 1);
    {
        auto result = std::numeric_limits<token::boolean::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "incompatible type");
    }
    {
        auto result = std::numeric_limits<token::int8::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int16::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::int64::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float32::type>::max();
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array(&result, 1),
                                        format::error, "invalid value");
    }
    {
        auto result = std::numeric_limits<token::float64::type>::max();
        TRIAL_PROTOCOL_TEST_NO_THROW(reader.array(&result, 1));
        TRIAL_PROTOCOL_TEST_EQUAL(result, 1.0);
    }
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    value_int8();
    output_int8();
    value_uint8();
    value_int16();
    output_int16();
    value_uint16();
    value_int32();
    output_int32();
    value_uint32();
    value_int64();
    output_int64();
    value_uint64();
    value_float32();
    output_float32();
    value_float64();
    output_float64();
}

} // namespace number_suite

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_string8()
{
    const value_type input[] = { token::code::string8, 0x03, 0x41, 0x42, 0x43 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "ABC");
    const value_type expected[] = { 0x41, 0x42, 0x43 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<int>(),
                                    format::error, "invalid value");
}

void test_string16()
{
    const value_type input[] = { token::code::string16, 0x03, 0x00, 0x41, 0x42, 0x43 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "ABC");
    const value_type expected[] = { 0x41, 0x42, 0x43 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<int>(),
                                    format::error, "invalid value");
}

void run()
{
    test_string8();
    test_string16();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Compact arrays
//-----------------------------------------------------------------------------

namespace compact_suite
{

void test_int8()
{
    const value_type input[] = {
        token::code::array8_int8, 3 * token::int8::size,
        0x41,
        0x42,
        0x43 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::array8_int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    {
        const value_type expected_literal[] = {
            0x41,
            0x42,
            0x43 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        const std::int8_t expected[] = {
            0x41,
            0x42,
            0x43 };
        std::array<std::int8_t, sizeof(expected)> buffer = {};
        TRIAL_PROTOCOL_TEST_EQUAL(reader.array<std::int8_t>(buffer.data(), buffer.size()), buffer.size());
        TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
}

void fail_int8_overflow()
{
    const value_type input[] = {
        token::code::array8_int8, 3 * token::int8::size,
        0x41,
        0x42,
        0x43 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    std::array<std::int8_t, 1> buffer = {};
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array<std::int8_t>(buffer.data(), buffer.size()),
                                    format::error, "overflow");
}

void test_int16()
{
    const value_type input[] = {
        token::code::array8_int16, 3 * token::int16::size,
        0x41, 0x00,
        0x42, 0x00,
        0x43, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::array8_int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    {
        const value_type expected_literal[] = {
            0x41, 0x00,
            0x42, 0x00,
            0x43, 0x00 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        const std::array<std::int16_t, 3> expected = {{
                0x41,
                0x42,
                0x43 }};
        std::array<std::int16_t, expected.size()> buffer = {};
        TRIAL_PROTOCOL_TEST_EQUAL(reader.array<std::int16_t>(buffer.data(), buffer.size()), buffer.size());
        TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<value_type>());
    }
}

void fail_int16_overflow()
{
    const value_type input[] = {
        token::code::array8_int16, 3 * token::int16::size,
        0x41, 0x00,
        0x42, 0x00,
        0x43, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    std::array<std::int16_t, 1> buffer = {};
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array<std::int16_t>(buffer.data(), buffer.size()),
                                    format::error, "overflow");
}

void test_int32()
{
    const value_type input[] = {
        token::code::array8_int32, 3 * token::int32::size,
        0x41, 0x00, 0x00, 0x00,
        0x42, 0x00, 0x00, 0x00,
        0x43, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::array8_int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    {
        const value_type expected_literal[] = {
            0x41, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        const std::array<std::int32_t, 3> expected = {{
                0x41,
                0x42,
                0x43 }};
        std::array<std::int32_t, expected.size()> buffer = {};
        TRIAL_PROTOCOL_TEST_EQUAL(reader.array<std::int32_t>(buffer.data(), buffer.size()), buffer.size());
        TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<value_type>());
    }
}

void fail_int32_overflow()
{
    const value_type input[] = {
        token::code::array8_int32, 3 * token::int32::size,
        0x41, 0x00, 0x00, 0x00,
        0x42, 0x00, 0x00, 0x00,
        0x43, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    std::array<std::int32_t, 1> buffer = {};
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array<std::int32_t>(buffer.data(), buffer.size()),
                                    format::error, "overflow");
}

void test_int64()
{
    const value_type input[] = {
        token::code::array8_int64, 3 * token::int64::size,
        0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::array8_int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    {
        const value_type expected_literal[] = {
            0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        const std::array<std::int64_t, 3> expected = {{
                UINT64_C(0x41),
                UINT64_C(0x42),
                UINT64_C(0x43) }};
        std::array<std::int64_t, expected.size()> buffer = {};
        TRIAL_PROTOCOL_TEST_EQUAL(reader.array<std::int64_t>(buffer.data(), buffer.size()), buffer.size());
        TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<value_type>());
    }
}

void fail_int64_overflow()
{
    const value_type input[] = {
        token::code::array8_int64, 3 * token::int64::size,
        0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    std::array<std::int64_t, 1> buffer = {};
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array<std::int64_t>(buffer.data(), buffer.size()),
                                    format::error, "overflow");
}

void test_float32()
{
    const value_type input[] = {
        token::code::array8_float32, 3 * token::float32::size,
        0x00, 0x00, 0x80, 0x3F,
        0x00, 0x00, 0x00, 0x40,
        0x00, 0x00, 0x40, 0x40 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::array8_float32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    {
        const value_type expected_literal[] = {
            0x00, 0x00, 0x80, 0x3F,
            0x00, 0x00, 0x00, 0x40,
            0x00, 0x00, 0x40, 0x40 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        const std::array<token::float32::type, 3> expected = {{
                1.0f,
                2.0f,
                3.0f }};
        std::array<token::float32::type, expected.size()> buffer = {};
        TRIAL_PROTOCOL_TEST_EQUAL(reader.array<token::float32::type>(buffer.data(), buffer.size()), buffer.size());
        TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<value_type>());
    }
}

void fail_float32_overflow()
{
    const value_type input[] = {
        token::code::array8_float32, 3 * token::float32::size,
        0x00, 0x00, 0x80, 0x3F,
        0x00, 0x00, 0x00, 0x40,
        0x00, 0x00, 0x40, 0x40 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    std::array<token::float32::type, 1> buffer = {};
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array<token::float32::type>(buffer.data(), buffer.size()),
                                    format::error, "overflow");
}

void test_float64()
{
    const value_type input[] = {
        token::code::array8_float64, 3 * token::float64::size,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::array8_float64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    {
        const value_type expected_literal[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(reader.literal().begin(), reader.literal().end(),
                                     expected_literal, expected_literal + sizeof(expected_literal),
                                     std::equal_to<value_type>());
    }
    {
        const std::array<token::float64::type, 3> expected = {{
                1.0,
                2.0,
                3.0 }};
        std::array<token::float64::type, expected.size()> buffer = {};
        TRIAL_PROTOCOL_TEST_EQUAL(reader.array<token::float64::type>(buffer.data(), buffer.size()), buffer.size());
        TRIAL_PROTOCOL_TEST_ALL_WITH(buffer.begin(), buffer.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<value_type>());
    }
}

void fail_float64_overflow()
{
    const value_type input[] = {
        token::code::array8_float64, 3 * token::float64::size,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST(reader.length() == 3);
    std::array<token::float64::type, 1> buffer = {};
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.array<token::float64::type>(buffer.data(), buffer.size()),
                                    format::error, "overflow");
}

void run()
{
    test_int8();
    fail_int8_overflow();
    test_int16();
    fail_int16_overflow();
    test_int32();
    fail_int32_overflow();
    test_int64();
    fail_int64_overflow();
    test_float32();
    fail_float32_overflow();
    test_float64();
    fail_float64_overflow();
}

} // namespace compact_suite

//-----------------------------------------------------------------------------
// Containers
//-----------------------------------------------------------------------------

namespace container_suite
{

void test_record_empty()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::end_record };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_record);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::begin_record);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.length(),
                                    format::error, "unknown token");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_record);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_record);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_array_empty()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::end_array };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.length(),
                                    format::error, "unknown token");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_assoc_array_empty()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::end_assoc_array };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::begin_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.length(),
                                    format::error, "unknown token");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    test_record_empty();
    test_array_empty();
    test_assoc_array_empty();
}

} // namespace container_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    number_suite::run();
    string_suite::run();
    compact_suite::run();
    container_suite::run();

    return boost::report_errors();
}
