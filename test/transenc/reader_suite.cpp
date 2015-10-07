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

#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/transenc/reader.hpp>
#include "is_system_error.hpp"

namespace test = trial::protocol::test;
namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::reader::value_type value_type;

BOOST_AUTO_TEST_SUITE(transenc_reader_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    const boost::array<value_type, 0> input = {};
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::end);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::status);
}

BOOST_AUTO_TEST_CASE(test_false)
{
    const value_type input[] = { token::code::false_value };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::false_value);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::boolean);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    // Without conversion
    BOOST_REQUIRE_EQUAL(reader.value<token::boolean>(), false);
    BOOST_REQUIRE_THROW(reader.value<token::int8>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int16>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int64>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float64>(), format::error);
    // With conversion
    BOOST_REQUIRE_EQUAL(reader.value<bool>(), false);
    BOOST_REQUIRE_EXCEPTION(reader.value<int>(),
                            format::error,
                            test::is_system_error(format::invalid_value));
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const value_type input[] = { token::code::true_value };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::true_value);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::boolean);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(reader.value<token::boolean>(), true);
    BOOST_REQUIRE_EQUAL(reader.value<bool>(), true);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_null)
{
    const value_type input[] = { token::code::null };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::null);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::null);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::nullable);
    BOOST_REQUIRE_THROW(reader.value<token::boolean>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<bool>(), format::error);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int8)
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::int8);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    // Without conversion
    BOOST_REQUIRE_THROW(reader.value<token::boolean>(), format::error);
    BOOST_REQUIRE_EQUAL(reader.value<token::int8>(), 1);
    BOOST_REQUIRE_THROW(reader.value<token::int16>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int64>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float64>(), format::error);
    // With conversion
    BOOST_REQUIRE_EXCEPTION(reader.value<token::boolean::type>(),
                            format::error,
                            test::is_system_error(format::incompatible_type));
    BOOST_REQUIRE_EQUAL(reader.value<token::int8::type>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<token::int16::type>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<token::int32::type>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<token::int64::type>(), UINT64_C(1));
    BOOST_REQUIRE_EQUAL(reader.value<token::float32::type>(), 1.0f);
    BOOST_REQUIRE_EQUAL(reader.value<token::float64::type>(), 1.0);
    BOOST_REQUIRE_EQUAL(reader.value<int>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<boost::intmax_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int16)
{
    const value_type input[] = { token::code::int16, 0x00, 0x01 };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::int16);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    // Without conversion
    BOOST_REQUIRE_THROW(reader.value<token::boolean>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int8>(), format::error);
    BOOST_REQUIRE_EQUAL(reader.value<token::int16>(), 0x100);
    BOOST_REQUIRE_THROW(reader.value<token::int32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int64>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float64>(), format::error);
    // With conversion
    BOOST_REQUIRE_EXCEPTION(reader.value<boost::int8_t>(),
                            format::error,
                            test::is_system_error(format::overflow));
    BOOST_REQUIRE_EQUAL(reader.value<token::int16::type>(), 0x100);
    BOOST_REQUIRE_EQUAL(reader.value<token::int32::type>(), 0x100);
    BOOST_REQUIRE_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x0100));
    BOOST_REQUIRE_EQUAL(reader.value<token::float32::type>(), 256.0f);
    BOOST_REQUIRE_EQUAL(reader.value<token::float64::type>(), 256.0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int32)
{
    const value_type input[] = { token::code::int32, 0x00, 0x00, 0x01, 0x00 };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::int32);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    // Without conversion
    BOOST_REQUIRE_THROW(reader.value<token::boolean>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int8>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int16>(), format::error);
    BOOST_REQUIRE_EQUAL(reader.value<token::int32>(), 0x10000);
    BOOST_REQUIRE_THROW(reader.value<token::int64>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float64>(), format::error);
    // With conversion
    BOOST_REQUIRE_EXCEPTION(reader.value<boost::int8_t>(),
                            format::error,
                            test::is_system_error(format::overflow));
    BOOST_REQUIRE_EXCEPTION(reader.value<boost::int16_t>(),
                            format::error,
                            test::is_system_error(format::overflow));
    BOOST_REQUIRE_EQUAL(reader.value<token::int32::type>(), 0x10000);
    BOOST_REQUIRE_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x10000));
    BOOST_REQUIRE_EQUAL(reader.value<token::float32::type>(), 65536.0f);
    BOOST_REQUIRE_EQUAL(reader.value<token::float64::type>(), 65536.0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_int64)
{
    const value_type input[] = { token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::int64);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::integer);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    // Without conversion
    BOOST_REQUIRE_THROW(reader.value<token::boolean>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int8>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int16>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::int32>(), format::error);
    BOOST_REQUIRE_EQUAL(reader.value<token::int64>(), UINT64_C(0x100000000));
    BOOST_REQUIRE_THROW(reader.value<token::float32>(), format::error);
    BOOST_REQUIRE_THROW(reader.value<token::float64>(), format::error);
    // With conversion
    BOOST_REQUIRE_EXCEPTION(reader.value<boost::int8_t>(),
                            format::error,
                            test::is_system_error(format::overflow));
    BOOST_REQUIRE_EXCEPTION(reader.value<boost::int16_t>(),
                            format::error,
                            test::is_system_error(format::overflow));
    BOOST_REQUIRE_EXCEPTION(reader.value<boost::int32_t>(),
                            format::error,
                            test::is_system_error(format::overflow));
    BOOST_REQUIRE_EQUAL(reader.value<token::int64::type>(), UINT64_C(0x100000000));
    BOOST_REQUIRE_EQUAL(reader.value<token::float32::type>(), 4294967296.0f);
    BOOST_REQUIRE_EQUAL(reader.value<token::float64::type>(), 4294967296.0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float32)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::float32);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::floating);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int8_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int16_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int32_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int64_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<token::float32::type>(), 1.0f);
    BOOST_REQUIRE_EQUAL(reader.value<token::float64::type>(), 1.0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_float64)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::float64);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::floating);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int8_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int16_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int32_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<boost::int64_t>(), 1);
    BOOST_REQUIRE_EQUAL(reader.value<token::float32::type>(), 1.0f);
    BOOST_REQUIRE_EQUAL(reader.value<token::float64::type>(), 1.0);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_CASE(test_string8)
{
    const value_type input[] = { token::code::string8, 0x03, 0x41, 0x42, 0x43 };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::string8);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::string);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    BOOST_REQUIRE_EQUAL(reader.value<std::string>(), "ABC");
    const value_type expected[] = { 0x41, 0x42, 0x43 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(reader.literal().begin(), reader.literal().end(),
                                    expected, expected + sizeof(expected));
    BOOST_REQUIRE_THROW(reader.value<int>(), format::error);
}

BOOST_AUTO_TEST_CASE(test_binary8)
{
    const value_type input[] = { token::code::binary8, 0x03, 0x41, 0x42, 0x43 };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::binary8);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::binary);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::data);
    const value_type expected[] = { 0x41, 0x42, 0x43 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(reader.literal().begin(), reader.literal().end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Containers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_record_empty)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::end_record };
    format::reader reader(input);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::begin_record);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::begin_record);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::structural);
    BOOST_REQUIRE_EQUAL(reader.next(), true);
    BOOST_REQUIRE_EQUAL(reader.level(), 1);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end_record);
    BOOST_REQUIRE_EQUAL(reader.symbol(), token::symbol::end_record);
    BOOST_REQUIRE_EQUAL(reader.category(), token::category::structural);
    BOOST_REQUIRE_EQUAL(reader.next(), false);
    BOOST_REQUIRE_EQUAL(reader.level(), 0);
    BOOST_REQUIRE_EQUAL(reader.code(), token::code::end);
}

BOOST_AUTO_TEST_SUITE_END()
