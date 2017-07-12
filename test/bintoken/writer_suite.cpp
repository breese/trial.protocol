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
#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/bintoken/writer.hpp>
#include <trial/protocol/bintoken/error.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using output_type = std::uint8_t;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void test_null()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::null>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::null);
}

void test_false()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::false_value);
}

void test_true()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::true_value);
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
// Numbers
//-----------------------------------------------------------------------------

namespace number_suite
{

void test_zero()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0);
}

void test_int8()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(-128), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x80);
}

void test_uint8()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint8_t(0x00)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint8_t(0x7F)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint8_t(0xD0)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint8_t(0xFF)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x7F);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0xD0);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0xFF);
}

void test_int16()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0x100), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x01);
}

void test_uint16()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint16_t(0x7FFF)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint16_t(0x8000)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint16_t(0xFFFF)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x7F);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[5], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(result[6], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(result[7], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[8], 0xFF);
}

void test_int32()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0x1000000), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x01);
}

void test_uint32()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint32_t(0x7FFFFFFF)), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint32_t(0x80000000)), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint32_t(0xFFFFFFFF)), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 15);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x7F);
    TRIAL_PROTOCOL_TEST_EQUAL(result[5], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(result[6], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[7], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[8], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[9], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(result[10], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(result[11], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[12], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[13], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[14], 0xFF);
}

void test_int64()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(INT64_C(0x100000000000000)), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[5], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[6], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[7], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[8], 0x01);
}

void test_uint64()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint64_t(UINT64_C(0x7FFFFFFFFFFFFFFF))), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint64_t(UINT64_C(0x8000000000000000))), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(std::uint64_t(UINT64_C(0xFFFFFFFFFFFFFFFF))), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 27);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[5], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[6], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[7], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[8], 0x7F);
    TRIAL_PROTOCOL_TEST_EQUAL(result[9], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(result[10], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[11], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[12], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[13], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[14], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[15], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[16], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[17], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(result[18], token::code::int64);
    TRIAL_PROTOCOL_TEST_EQUAL(result[19], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[20], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[21], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[22], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[23], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[24], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[25], 0xFF);
    TRIAL_PROTOCOL_TEST_EQUAL(result[26], 0xFF);
}

void test_float()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0.0f), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::float32);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x00);
}

void test_double()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0.0), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 9);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::float64);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[5], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[6], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[7], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[8], 0x00);
}

void run()
{
    test_zero();
    test_int8();
    test_uint8();
    test_int16();
    test_uint16();
    test_int32();
    test_uint32();
    test_int64();
    test_uint64();
    test_float();
    test_double();
}

} // namespace number_suite

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_string()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::string data("ABC");
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(data), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x03);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x41);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x42);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x43);
}

void test_literal()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value("ABC"), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x03);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x41);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x42);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x43);
}

void test_view()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::string data("ABC");
    trial::protocol::detail::string_view view(data.data());
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(view), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::string8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x03);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x41);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x42);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x43);
}

void run()
{
    test_string();
    test_literal();
    test_view();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Compact
//-----------------------------------------------------------------------------

namespace compact_suite
{

void test_int8_empty()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::array<std::int8_t, 0> data;
    TRIAL_PROTOCOL_TEST_EQUAL(writer.array(data.data(), data.size()), 2);

    output_type expected[] = { token::code::array8_int8, 0 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int8()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::int8_t data[] = { 0x41, 0x42, 0x43 };
    TRIAL_PROTOCOL_TEST_EQUAL(writer.array(data, sizeof(data)), 5);

    output_type expected[] = { token::code::array8_int8, 3 * token::int8::size,
                               0x41,
                               0x42,
                               0x43 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int16()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::array<std::int16_t, 3> data = {{ 0x1101, 0x1202, 0x1303 }};
    TRIAL_PROTOCOL_TEST_EQUAL(writer.array(data.data(), data.size()), 8);

    output_type expected[] = { token::code::array8_int16, 3 * token::int16::size,
                               0x01, 0x11,
                               0x02, 0x12,
                               0x03, 0x13 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int32()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::array<std::int32_t, 3> data = {{ 0x31211101, 0x32221202, 0x33231303 }};
    TRIAL_PROTOCOL_TEST_EQUAL(writer.array(data.data(), data.size()), 14);

    output_type expected[] = { token::code::array8_int32, 3 * token::int32::size,
                               0x01, 0x11, 0x21, 0x31,
                               0x02, 0x12, 0x22, 0x32,
                               0x03, 0x13, 0x23, 0x33 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int64()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::array<std::int64_t, 3> data = {{ INT64_C(0x7161514131211101), INT64_C(0x7262524232221202), INT64_C(0x7363534333231303) }};
    TRIAL_PROTOCOL_TEST_EQUAL(writer.array(data.data(), data.size()), 26);

    output_type expected[] = { token::code::array8_int64, 3 * token::int64::size,
                               0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71,
                               0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72,
                               0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float32()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::array<token::float32::type, 3> data = {{ 0.0f, -1.0f, 1.0f }};
    TRIAL_PROTOCOL_TEST_EQUAL(writer.array(data.data(), data.size()), 14);

    output_type expected[] = { token::code::array8_float32, 3 * token::float32::size,
                               0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x80, 0xBF,
                               0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float64()
{
    std::vector<output_type> result;
    format::writer writer(result);
    std::array<token::float64::type, 3> data = {{ 0.0, -1.0, 1.0 }};
    TRIAL_PROTOCOL_TEST_EQUAL(writer.array(data.data(), data.size()), 26);

    output_type expected[] = { token::code::array8_float64, 3 * token::float64::size,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xBF,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_int8_empty();
    test_int8();
    test_int16();
    test_int32();
    test_int64();
    test_float32();
    test_float64();
}

} // namespace compact_suite

//-----------------------------------------------------------------------------
// Record
//-----------------------------------------------------------------------------

namespace record_suite
{

void test_one()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_record>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_record>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::begin_record);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], token::code::end_record);
}

void fail_missing_begin()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_record>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_array()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_record>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_array>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_assoc_array()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_record>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_assoc_array>(),
                                    format::error, "unexpected token");
}

void run()
{
    test_one();
    fail_missing_begin();
    fail_mismatched_end_array();
    fail_mismatched_end_assoc_array();
}

} // namespace record_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_one()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], token::code::end_array);
}

void fail_missing_begin()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_array>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_record()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_record>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_assoc_array()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_assoc_array>(),
                                    format::error, "unexpected token");
}

void run()
{
    test_one();
    fail_missing_begin();
    fail_mismatched_end_record();
    fail_mismatched_end_assoc_array();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Associative array
//-----------------------------------------------------------------------------

namespace assoc_array_suite
{

void test_one()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_assoc_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::end_assoc_array>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::begin_assoc_array);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x80);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], token::code::end_assoc_array);
}

void fail_missing_begin()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_assoc_array>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_record()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_assoc_array>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_record>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_array()
{
    std::vector<output_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_assoc_array>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_array>(),
                                    format::error, "unexpected token");
}

void run()
{
    test_one();
    fail_missing_begin();
    fail_mismatched_end_record();
    fail_mismatched_end_array();
}

} // namespace assoc_array_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    number_suite::run();
    string_suite::run();
    compact_suite::run();
    record_suite::run();
    array_suite::run();
    assoc_array_suite::run();

    return boost::report_errors();
}
