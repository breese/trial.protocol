///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/transenc/reader.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::reader::value_type value_type;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    const boost::array<value_type, 0> input = {};
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::status);
}

void test_false()
{
    const value_type input[] = { token::code::false_value };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::false_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
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

void test_true()
{
    const value_type input[] = { token::code::true_value };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::boolean>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_null()
{
    const value_type input[] = { token::code::null };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::nullable);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<token::boolean>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<bool>(),
                                    format::error, "incompatible type");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    test_empty();
    test_false();
    test_true();
    test_null();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Numbers
//-----------------------------------------------------------------------------

namespace number_suite
{

void test_int8()
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::intmax_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_uint8()
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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint8_t>(), 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint16_t>(), 0x0000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x00000000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x0000000000000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint8_t>(), 0x7F);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint16_t>(), 0x007F);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x0000007F);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x000000000000007F));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint8_t>(), 0xD0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint16_t>(), 0x00D0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x000000D0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x00000000000000D0));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint8_t>(), 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint16_t>(), 0x00FF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x000000FF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x00000000000000FF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_int16()
{
    const value_type input[] = { token::code::int16, 0x00, 0x01 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
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
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::int8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int16::type>(), 0x100);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int32::type>(), 0x100);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x0100));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 256.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 256.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_uint16()
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
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint16_t>(), 0x7FFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x00007FFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x0000000000007FFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint16_t>(), 0x8000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x00008000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint16_t>(), 0xFFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x0000FFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_int32()
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x01, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
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
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::int8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::int16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int32::type>(), 0x10000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x10000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 65536.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 65536.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_uint32()
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
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x7FFFFFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x000000007FFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0x80000000);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x0000000080000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint32_t>(), 0xFFFFFFFF);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x00000000FFFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_int64()
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
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
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::int8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::int16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::int32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x100000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 4294967296.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 4294967296.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_uint64()
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
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x7FFFFFFFFFFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0x8000000000000000));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint8_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint16_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<boost::uint32_t>(),
                                    format::error, "overflow");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::uint64_t>(), UINT64_C(0xFFFFFFFFFFFFFFFF));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_float32()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int8_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int16_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int32_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int64_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_float64()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int8_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int16_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int32_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<boost::int64_t>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float32::type>(), 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<token::float64::type>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    test_int8();
    test_uint8();
    test_int16();
    test_uint16();
    test_int32();
    test_uint32();
    test_int64();
    test_uint64();
    test_float32();
    test_float64();
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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "ABC");
    const value_type expected[] = { 0x41, 0x42, 0x43 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(reader.literal().begin(), reader.literal().end(),
                                          expected, expected + sizeof(expected));
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<int>(),
                                    format::error, "invalid value");
}

void run()
{
    test_string8();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Binary
//-----------------------------------------------------------------------------

namespace binary_suite
{

void test_binary8()
{
    const value_type input[] = { token::code::binary8, 0x03, 0x41, 0x42, 0x43 };
    format::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::binary8);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::binary);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    const value_type expected[] = { 0x41, 0x42, 0x43 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(reader.literal().begin(), reader.literal().end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_binary8();
}

} // namespace binary_suite

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
    binary_suite::run();
    container_suite::run();

    return boost::report_errors();
}
