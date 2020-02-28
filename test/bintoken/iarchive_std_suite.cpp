///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/bintoken/serialization.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using value_type = format::reader::value_type;

//-----------------------------------------------------------------------------
// std::array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_bool()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x80, 0x81, 0x80, 0x81,
                                 token::code::end_array };
    format::iarchive in(input);
    std::array<bool, 4> value = {{ false, false, false, false }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], false);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], false);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], true);
}

void test_string()
{
    const value_type input[] = { token::code::begin_array,
                                 0x02,
                                 token::code::string8, 0x02, 0x41, 0x42,
                                 token::code::string8, 0x02, 0x43, 0x44,
                                 token::code::end_array };
    format::iarchive in(input);
    std::array<std::string, 2> value = {{ "", "" }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], "AB");
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], "CD");
}

void run()
{
    test_bool();
    test_string();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Compact std::array
//-----------------------------------------------------------------------------

namespace compact_array_suite
{

void test_int8()
{
    const value_type input[] = { token::code::array8_int8, 4 * token::int8::size,
                                 0x01,
                                 0x02,
                                 0x03,
                                 0x04 };
    format::iarchive in(input);
    std::array<std::int8_t, 4> value = {{ std::numeric_limits<std::int8_t>::max(),
                                          std::numeric_limits<std::int8_t>::max(),
                                          std::numeric_limits<std::int8_t>::max(),
                                          std::numeric_limits<std::int8_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT8_C(0x01));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT8_C(0x02));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT8_C(0x03));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT8_C(0x04));
}

void test_uint8()
{
    const value_type input[] = { token::code::array8_int8, 4 * token::int8::size,
                                 0x01,
                                 0x02,
                                 0x03,
                                 0x04 };
    format::iarchive in(input);
    std::array<std::uint8_t, 4> value = {{ std::numeric_limits<std::uint8_t>::max(),
                                           std::numeric_limits<std::uint8_t>::max(),
                                           std::numeric_limits<std::uint8_t>::max(),
                                           std::numeric_limits<std::uint8_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT8_C(0x01));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT8_C(0x02));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT8_C(0x03));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT8_C(0x04));
}

void test_int16()
{
    const value_type input[] = { token::code::array8_int16, 4 * token::int16::size,
                                 0x01, 0x11,
                                 0x02, 0x12,
                                 0x03, 0x13,
                                 0x04, 0x14 };
    format::iarchive in(input);
    std::array<std::int16_t, 4> value = {{ std::numeric_limits<std::int16_t>::max(),
                                           std::numeric_limits<std::int16_t>::max(),
                                           std::numeric_limits<std::int16_t>::max(),
                                           std::numeric_limits<std::int16_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT16_C(0x1101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT16_C(0x1202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT16_C(0x1303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT16_C(0x1404));
}

void test_uint16()
{
    const value_type input[] = { token::code::array8_int16, 4 * token::int16::size,
                                 0x01, 0x11,
                                 0x02, 0x12,
                                 0x03, 0x13,
                                 0x04, 0x14 };
    format::iarchive in(input);
    std::array<std::uint16_t, 4> value = {{ std::numeric_limits<std::uint16_t>::max(),
                                            std::numeric_limits<std::uint16_t>::max(),
                                            std::numeric_limits<std::uint16_t>::max(),
                                            std::numeric_limits<std::uint16_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT16_C(0x1101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT16_C(0x1202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT16_C(0x1303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT16_C(0x1404));
}

void test_int32()
{
    const value_type input[] = { token::code::array8_int32, 4 * token::int32::size,
                                 0x01, 0x11, 0x21, 0x31,
                                 0x02, 0x12, 0x22, 0x32,
                                 0x03, 0x13, 0x23, 0x33,
                                 0x04, 0x14, 0x24, 0x34 };
    format::iarchive in(input);
    std::array<std::int32_t, 4> value = {{ std::numeric_limits<std::int32_t>::max(),
                                           std::numeric_limits<std::int32_t>::max(),
                                           std::numeric_limits<std::int32_t>::max(),
                                           std::numeric_limits<std::int32_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT32_C(0x31211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT32_C(0x32221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT32_C(0x33231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT32_C(0x34241404));
}

void test_uint32()
{
    const value_type input[] = { token::code::array8_int32, 4 * token::int32::size,
                                 0x01, 0x11, 0x21, 0x31,
                                 0x02, 0x12, 0x22, 0x32,
                                 0x03, 0x13, 0x23, 0x33,
                                 0x04, 0x14, 0x24, 0x34 };
    format::iarchive in(input);
    std::array<std::uint32_t, 4> value = {{ std::numeric_limits<std::uint32_t>::max(),
                                            std::numeric_limits<std::uint32_t>::max(),
                                            std::numeric_limits<std::uint32_t>::max(),
                                            std::numeric_limits<std::uint32_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT32_C(0x31211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT32_C(0x32221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT32_C(0x33231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT32_C(0x34241404));
}

void test_int64()
{
    const value_type input[] = { token::code::array8_int64, 4 * token::int64::size,
                                 0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71,
                                 0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72,
                                 0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73,
                                 0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74 };
    format::iarchive in(input);
    std::array<std::int64_t, 4> value = {{ std::numeric_limits<std::int64_t>::max(),
                                           std::numeric_limits<std::int64_t>::max(),
                                           std::numeric_limits<std::int64_t>::max(),
                                           std::numeric_limits<std::int64_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT64_C(0x7161514131211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT64_C(0x7262524232221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT64_C(0x7363534333231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT64_C(0x7464544434241404));
}

void test_uint64()
{
    const value_type input[] = { token::code::array8_int64, 4 * token::int64::size,
                                 0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71,
                                 0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72,
                                 0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73,
                                 0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74 };
    format::iarchive in(input);
    std::array<std::uint64_t, 4> value = {{ std::numeric_limits<std::uint64_t>::max(),
                                            std::numeric_limits<std::uint64_t>::max(),
                                            std::numeric_limits<std::uint64_t>::max(),
                                            std::numeric_limits<std::uint64_t>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT64_C(0x7161514131211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT64_C(0x7262524232221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT64_C(0x7363534333231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT64_C(0x7464544434241404));
}

void test_float32()
{
    const value_type input[] = { token::code::array8_float32, 4 * token::float32::size,
                                 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x80, 0x3F,
                                 0x00, 0x00, 0x00, 0x40,
                                 0x00, 0x00, 0x40, 0x40 };
    format::iarchive in(input);
    std::array<token::float32::type, 4> value = {{ std::numeric_limits<token::float32::type>::max(),
                                                   std::numeric_limits<token::float32::type>::max(),
                                                   std::numeric_limits<token::float32::type>::max(),
                                                   std::numeric_limits<token::float32::type>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], 2.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], 3.0f);
}

void test_float64()
{
    const value_type input[] = { token::code::array8_float64, 4 * token::float64::size,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40 };
    format::iarchive in(input);
    std::array<token::float64::type, 4> value = {{ std::numeric_limits<token::float64::type>::max(),
                                                   std::numeric_limits<token::float64::type>::max(),
                                                   std::numeric_limits<token::float64::type>::max(),
                                                   std::numeric_limits<token::float64::type>::max() }};
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], 2.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], 3.0);
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

} // namespace compact_array_suite

//-----------------------------------------------------------------------------
// std::pair
//-----------------------------------------------------------------------------

namespace pair_suite
{

void test_string_bool()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value("replace", false);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.first, "A");
    TRIAL_PROTOCOL_TEST_EQUAL(value.second, true);
}

void fail_too_short()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_too_long()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::true_value,
                                 token::code::false_value,
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_end()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::true_value };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_second_end()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A' };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_missing_first_second_end()
{
    const value_type input[] = { token::code::begin_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_missing_begin()
{
    const value_type input[] = { token::code::string8, 0x01, 'A',
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void run()
{
    test_string_bool();
    fail_too_short();
    fail_too_long();
    fail_missing_end();
    fail_missing_second_end();
    fail_missing_first_second_end();
    fail_missing_begin();
}

} // namespace pair_suite

//-----------------------------------------------------------------------------
// std::vector
//-----------------------------------------------------------------------------

namespace vector_suite
{

void test_bool_empty()
{
    const value_type input[] = { token::code::begin_array,
                                 0x00,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_bool_one()
{
    const value_type input[] = { token::code::begin_array,
                                 0x01,
                                 token::code::true_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], true);
}

void test_bool_two()
{
    const value_type input[] = { token::code::begin_array,
                                 0x02,
                                 token::code::true_value,
                                 token::code::false_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], false);
}

void test_bool_two_uncounted()
{
    const value_type input[] = { token::code::begin_array,
                                 0x82,
                                 token::code::true_value,
                                 token::code::false_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], false);
}

void fail_unexpected_float()
{
    // FIXME: No exception because of implicit conversion from float to int
    const value_type input[] = { token::code::begin_array,
                                 token::code::float32, 0x00, 0x00, 0x00, 0x00,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_unexpected_begin()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::begin_array,
                                 0x00,
                                 token::code::end_array,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_mixed()
{
    const value_type input[] = { token::code::begin_array,
                                 0x02,
                                 token::code::true_value,
                                 0x00,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_missing_end()
{
    const value_type input[] = { token::code::begin_array,
                                 0x01,
                                 token::code::true_value };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_missing_begin()
{
    const value_type input[] = { 0x01,
                                 token::code::true_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_count()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void run()
{
    test_bool_empty();
    test_bool_one();
    test_bool_two();
    test_bool_two_uncounted();
    // fail_unexpected_float();  // FIXME
    fail_unexpected_begin();
    fail_mixed();
    fail_missing_end();
    fail_missing_begin();
    fail_missing_count();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// Compact vector
//-----------------------------------------------------------------------------

namespace compact_vector_suite
{

void test_empty()
{
    const value_type input[] = { token::code::array8_int8, 0x00 };
    format::iarchive in(input);
    std::vector<std::int8_t> value(4, std::numeric_limits<std::int8_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_int8()
{
    const value_type input[] = { token::code::array8_int8, 4 * token::int8::size,
                                 0x01,
                                 0x02,
                                 0x03,
                                 0x04 };
    format::iarchive in(input);
    std::vector<std::int8_t> value(4, std::numeric_limits<std::int8_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT8_C(0x01));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT8_C(0x02));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT8_C(0x03));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT8_C(0x04));
}

void test_uint8()
{
    const value_type input[] = { token::code::array8_int8, 4 * token::int8::size,
                                 0x01,
                                 0x02,
                                 0x03,
                                 0x04 };
    format::iarchive in(input);
    std::vector<std::uint8_t> value(4, std::numeric_limits<std::uint8_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT8_C(0x01));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT8_C(0x02));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT8_C(0x03));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT8_C(0x04));
}

void test_int16()
{
    const value_type input[] = { token::code::array8_int16, 4 * token::int16::size,
                                 0x01, 0x11,
                                 0x02, 0x12,
                                 0x03, 0x13,
                                 0x04, 0x14 };
    format::iarchive in(input);
    std::vector<std::int16_t> value(4, std::numeric_limits<std::int16_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT16_C(0x1101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT16_C(0x1202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT16_C(0x1303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT16_C(0x1404));
}

void test_uint16()
{
    const value_type input[] = { token::code::array8_int16, 4 * token::int16::size,
                                 0x01, 0x11,
                                 0x02, 0x12,
                                 0x03, 0x13,
                                 0x04, 0x14 };
    format::iarchive in(input);
    std::vector<std::uint16_t> value(4, std::numeric_limits<std::uint16_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT16_C(0x1101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT16_C(0x1202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT16_C(0x1303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT16_C(0x1404));
}

void test_int32()
{
    const value_type input[] = { token::code::array8_int32, 4 * token::int32::size,
                                 0x01, 0x11, 0x21, 0x31,
                                 0x02, 0x12, 0x22, 0x32,
                                 0x03, 0x13, 0x23, 0x33,
                                 0x04, 0x14, 0x24, 0x34 };
    format::iarchive in(input);
    std::vector<std::int32_t> value(4, std::numeric_limits<std::int32_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT32_C(0x31211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT32_C(0x32221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT32_C(0x33231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT32_C(0x34241404));
}

void test_uint32()
{
    const value_type input[] = { token::code::array8_int32, 4 * token::int32::size,
                                 0x01, 0x11, 0x21, 0x31,
                                 0x02, 0x12, 0x22, 0x32,
                                 0x03, 0x13, 0x23, 0x33,
                                 0x04, 0x14, 0x24, 0x34 };
    format::iarchive in(input);
    std::vector<std::uint32_t> value(4, std::numeric_limits<std::uint32_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT32_C(0x31211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT32_C(0x32221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT32_C(0x33231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT32_C(0x34241404));
}

void test_int64()
{
    const value_type input[] = { token::code::array8_int64, 4 * token::int64::size,
                                 0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71,
                                 0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72,
                                 0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73,
                                 0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74 };
    format::iarchive in(input);
    std::vector<std::int64_t> value(4, std::numeric_limits<std::int64_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], INT64_C(0x7161514131211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], INT64_C(0x7262524232221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], INT64_C(0x7363534333231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], INT64_C(0x7464544434241404));
}

void test_uint64()
{
    const value_type input[] = { token::code::array8_int64, 4 * token::int64::size,
                                 0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71,
                                 0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72,
                                 0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73,
                                 0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74 };
    format::iarchive in(input);
    std::vector<std::uint64_t> value(4, std::numeric_limits<std::uint64_t>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], UINT64_C(0x7161514131211101));
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], UINT64_C(0x7262524232221202));
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], UINT64_C(0x7363534333231303));
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], UINT64_C(0x7464544434241404));
}

void test_float32()
{
    const value_type input[] = { token::code::array8_float32, 4 * token::float32::size,
                                 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x80, 0x3F,
                                 0x00, 0x00, 0x00, 0x40,
                                 0x00, 0x00, 0x40, 0x40 };
    format::iarchive in(input);
    std::vector<token::float32::type> value(4, std::numeric_limits<token::float32::type>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], 2.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], 3.0f);
}

void test_float64()
{
    const value_type input[] = { token::code::array8_float64, 4 * token::float64::size,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40 };
    format::iarchive in(input);
    std::vector<token::float64::type> value(4, std::numeric_limits<token::float64::type>::max());
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], 2.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], 3.0);
}

void run()
{
    test_empty();
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

} // namespace compact_vector_suite

//-----------------------------------------------------------------------------
// std::set
//-----------------------------------------------------------------------------

namespace set_suite
{

void test_int_empty()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_int_one()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null,
                                 0x11,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value.count(0x11), 1);
}

void test_int_two()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null,
                                 0x11,
                                 0x22,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value.count(0x11), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value.count(0x22), 1);
}

void fail_missing_begin()
{
    const value_type input[] = { token::code::null,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_end()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null };
    format::iarchive in(input);
    std::set<int> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_missing_count()
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void run()
{
    test_int_empty();
    test_int_one();
    test_int_two();
    fail_missing_begin();
    fail_missing_end();
    fail_missing_count();
}

} // namespace set_suite

//-----------------------------------------------------------------------------
// std::map
//-----------------------------------------------------------------------------

namespace map_suite
{

void deprecated_test_bool_empty()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 0x00,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_bool_empty()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 0x00,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void deprecated_test_bool_empty_uncounted()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_bool_empty_uncounted()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void deprecated_test_bool_one()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value["A"], true);
}

void test_bool_one()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value["A"], true);
}

void deprecated_test_bool_two()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x42,
                                 token::code::false_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value["A"], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value["B"], false);
}

void test_bool_two()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::string8, 0x01, 0x42,
                                 token::code::false_value,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value["A"], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value["B"], false);
}

void fail_missing_end()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_missing_begin()
{
    const value_type input[] = { token::code::null,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_count()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_missing_pair_end()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_pair_second()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41 };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_missing_pair_first()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_key_int()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 0x00,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_key_null()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::null,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_value_int()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 0x00,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_unexpected_value_null()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::null,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void run()
{
    deprecated_test_bool_empty();
    test_bool_empty();
    deprecated_test_bool_empty_uncounted();
    test_bool_empty_uncounted();
    deprecated_test_bool_one();
    test_bool_one();
    deprecated_test_bool_two();
    test_bool_two();
    fail_missing_end();
    fail_missing_begin();
    fail_missing_count();
    fail_missing_pair_end();
    fail_missing_pair_second();
    fail_missing_pair_first();
    fail_unexpected_key_int();
    fail_unexpected_key_null();
    fail_unexpected_value_int();
    fail_unexpected_value_null();
}

} // namespace map_suite

namespace deprecated_map_suite
{

void test_bool_empty()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 0x00,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_bool_empty_uncounted()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_bool_one()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value["A"], true);
}

void test_bool_two()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x42,
                                 token::code::false_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(value["A"], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value["B"], false);
}

void fail_missing_end()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_begin()
{
    const value_type input[] = { token::code::null,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_count()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_missing_pair_end()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_pair_second()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41 };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_missing_pair_first()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_key_int()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 0x00,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_key_null()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::null,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_value_int()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 0x00,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_unexpected_value_null()
{
    const value_type input[] = { token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::null,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void run()
{
    test_bool_empty();
    test_bool_empty_uncounted();
    test_bool_one();
    test_bool_two();
    fail_missing_end();
    fail_missing_begin();
    fail_missing_count();
    fail_missing_pair_end();
    fail_missing_pair_second();
    fail_missing_pair_first();
    fail_unexpected_key_int();
    fail_unexpected_key_null();
    fail_unexpected_value_int();
    fail_unexpected_value_null();
}

} // namespace deprecated_map_suite

//-----------------------------------------------------------------------------
// Container struct
//-----------------------------------------------------------------------------

namespace container_suite
{

template <typename Type>
struct type_struct
{
    template<typename T>
    void serialize(T& archive, const unsigned int)
    {
        archive & data;
    }

    Type data;
};

void test_vector_empty()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::vector<bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 0);
}

void test_vector_one()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 token::code::true_value,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::vector<bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data[0], true);
}

void test_set_empty()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::set<int> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 0);
}

void test_set_one()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 0x12,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::set<int> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.count(0x12), 1);
}

void deprecated_test_map_empty()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::deprecated_end_assoc_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::map<std::string, bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 0);
}

void test_map_empty()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::end_assoc_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::map<std::string, bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 0);
}

void deprecated_test_map_one()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::deprecated_begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::deprecated_end_assoc_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::map<std::string, bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data["A"], true);
}

void test_map_one()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_assoc_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::map<std::string, bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value.data["A"], true);
}

void run()
{
    test_vector_empty();
    test_vector_one();
    test_set_empty();
    test_set_one();
    deprecated_test_map_empty();
    test_map_empty();
    deprecated_test_map_one();
    test_map_one();
}

} // namespace container_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    array_suite::run();
    compact_array_suite::run();
    pair_suite::run();
    vector_suite::run();
    compact_vector_suite::run();
    set_suite::run();
    map_suite::run();
    deprecated_map_suite::run();
    container_suite::run();

    return boost::report_errors();
}
