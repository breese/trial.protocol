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
#include <trial/protocol/bintoken/serialization.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace format = trial::protocol::bintoken;
namespace token = format::token;
using value_type = format::reader::value_type;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_false()
{
    const value_type input[] = { token::code::false_value };
    format::iarchive in(input);
    bool value = true;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, false);
}

void test_true()
{
    const value_type input[] = { token::code::true_value };
    format::iarchive in(input);
    bool value = false;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, true);
}

void test_bool_junk()
{
    const value_type input[] = { token::code::null }; // Null cannot be deserialized as bool (only as optional<bool>)
    format::iarchive in(input);
    bool value = true;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void run()
{
    test_false();
    test_true();
    test_bool_junk();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Integers
//-----------------------------------------------------------------------------

namespace integer_suite
{

void test_zero()
{
    const value_type input[] = { 0x00 };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0);
}

void test_one()
{
    const value_type input[] = { 0x01 };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 1);
}

void test_minus_one()
{
    const value_type input[] = { 0xFF };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, -1);
}

void test_int8_one()
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 1);
}

void test_int8_minus_one()
{
    const value_type input[] = { token::code::int8, 0xFF };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, -1);
}

void test_int16_one()
{
    const value_type input[] = { token::code::int16, 0x01, 0x00 };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 1);
}

void test_int16_minus_one()
{
    const value_type input[] = { token::code::int16, 0xFF, 0xFF };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, -1);
}

void test_int32_one()
{
    const value_type input[] = { token::code::int32, 0x01, 0x00, 0x00, 0x00 };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 1);
}

void test_int32_minus_one()
{
    const value_type input[] = { token::code::int32, 0xFF, 0xFF, 0xFF, 0xFF };
    format::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, -1);
}

void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_int8_one();
    test_int8_minus_one();
    test_int16_one();
    test_int16_minus_one();
    test_int32_one();
    test_int32_minus_one();
}

} // namespace integer_suite

//-----------------------------------------------------------------------------
// Floating-point
//-----------------------------------------------------------------------------

namespace number_suite
{

void test_float()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::iarchive in(input);
    token::float32::type value = 0.0f;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 1.0f);
}

void test_double()
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::iarchive in(input);
    token::float64::type value = 0.0;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 1.0);
}

void test_float_as_double()
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::iarchive in(input);
    token::float64::type value = 0.0;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 1.0);
}

void run()
{
    test_float();
    test_double();
    test_float_as_double();
}

} // namespace number_suite

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_empty()
{
    const value_type input[] = { token::code::string8, 0x00 };
    format::iarchive in(input);
    std::string value("replace");
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, "");
}

void test_alpha()
{
    const value_type input[] = { token::code::string8, 0x05, 'a', 'l', 'p', 'h', 'a' };
    format::iarchive in(input);
    std::string value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, "alpha");
}

void run()
{
    test_empty();
    test_alpha();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_four()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x80, 0x81, 0x80, 0x81,
                                 token::code::end_array };
    format::iarchive in(input);
    bool value[4] = { false, false, false, false };
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], false);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], false);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], true);
}

void fail_too_short()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x80, 0x81, 0x80,
                                 token::code::end_array };
    format::iarchive in(input);
    bool value[4] = { false, false, false, false };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_too_long()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x80, 0x81, 0x80, 0x81, 0x80,
                                 token::code::end_array };
    format::iarchive in(input);
    bool value[4] = { false, false, false, false };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "expected end array bracket");
}

void fail_missing_end()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x80, 0x81, 0x80, 0x81 };
    format::iarchive in(input);
    bool value[4] = { false, false, false, false };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "expected end array bracket");
}

void fail_missing_begin()
{
    const value_type input[] = { 0x04,
                                 0x80, 0x81, 0x80, 0x81,
                                 token::code::end_array };
    format::iarchive in(input);
    bool value[4] = { false, false, false, false };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_array_too_short()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x80, 0x81, 0x80, 0x81,
                                 token::code::end_array };
    format::iarchive in(input);
    bool value[3] = { false, false, false };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_array_too_long()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x80, 0x81, 0x80, 0x81,
                                 token::code::end_array };
    format::iarchive in(input);
    bool value[5] = { false, false, false, false, false };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void run()
{
    test_four();
    fail_too_short();
    fail_too_long();
    fail_missing_end();
    fail_missing_begin();
    fail_array_too_short();
    fail_array_too_long();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Compact array
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
    std::int8_t value[4] = { std::numeric_limits<std::int8_t>::max(),
                             std::numeric_limits<std::int8_t>::max(),
                             std::numeric_limits<std::int8_t>::max(),
                             std::numeric_limits<std::int8_t>::max() };
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
    std::uint8_t value[4] = { std::numeric_limits<std::uint8_t>::max(),
                              std::numeric_limits<std::uint8_t>::max(),
                              std::numeric_limits<std::uint8_t>::max(),
                              std::numeric_limits<std::uint8_t>::max() };
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
    std::int16_t value[4] = { std::numeric_limits<std::int16_t>::max(),
                              std::numeric_limits<std::int16_t>::max(),
                              std::numeric_limits<std::int16_t>::max(),
                              std::numeric_limits<std::int16_t>::max() };
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
    std::uint16_t value[4] = { std::numeric_limits<std::uint16_t>::max(),
                               std::numeric_limits<std::uint16_t>::max(),
                               std::numeric_limits<std::uint16_t>::max(),
                               std::numeric_limits<std::uint16_t>::max() };
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
    std::int32_t value[4] = { std::numeric_limits<std::int32_t>::max(),
                              std::numeric_limits<std::int32_t>::max(),
                              std::numeric_limits<std::int32_t>::max(),
                              std::numeric_limits<std::int32_t>::max() };
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
    std::uint32_t value[4] = { std::numeric_limits<std::uint32_t>::max(),
                               std::numeric_limits<std::uint32_t>::max(),
                               std::numeric_limits<std::uint32_t>::max(),
                               std::numeric_limits<std::uint32_t>::max() };
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
    std::int64_t value[4] = { std::numeric_limits<std::int64_t>::max(),
                              std::numeric_limits<std::int64_t>::max(),
                              std::numeric_limits<std::int64_t>::max(),
                              std::numeric_limits<std::int64_t>::max() };
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
    std::uint64_t value[4] = { std::numeric_limits<std::uint64_t>::max(),
                               std::numeric_limits<std::uint64_t>::max(),
                               std::numeric_limits<std::uint64_t>::max(),
                               std::numeric_limits<std::uint64_t>::max() };
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
    token::float32::type value[4] = { std::numeric_limits<token::float32::type>::max(),
                                      std::numeric_limits<token::float32::type>::max(),
                                      std::numeric_limits<token::float32::type>::max(),
                                      std::numeric_limits<token::float32::type>::max() };
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
    token::float64::type value[4] = { std::numeric_limits<token::float64::type>::max(),
                                      std::numeric_limits<token::float64::type>::max(),
                                      std::numeric_limits<token::float64::type>::max(),
                                      std::numeric_limits<token::float64::type>::max() };
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], 2.0);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], 3.0);
}

void fail_overflow()
{
    const value_type input[] = { token::code::array8_int8, 4 * token::int8::size,
                                 0x01,
                                 0x02,
                                 0x03,
                                 0x04 };
    format::iarchive in(input);
    std::int8_t value[3] = { std::numeric_limits<std::int8_t>::max(),
                             std::numeric_limits<std::int8_t>::max(),
                             std::numeric_limits<std::int8_t>::max() };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "overflow");
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
    fail_overflow();
}

} // namespace compact_array_suite

//-----------------------------------------------------------------------------
// Struct
//-----------------------------------------------------------------------------

namespace struct_suite
{

struct person
{
    person(std::string name, int age)
        : name(std::move(name)),
          age(age)
    {}

    template<typename T>
    void serialize(T& archive, const unsigned int)
    {
        archive & name;
        archive & age;
    }

    std::string name;
    int age;
};

void test_person()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.name, "ABC");
    TRIAL_PROTOCOL_TEST_EQUAL(value.age, 127);
}

void fail_missing_begin()
{
    const value_type input[] = { token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_end()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00 };
    format::iarchive in(input);
    person value("", 99);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_missing_second()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43 };
    format::iarchive in(input);
    person value("", 99);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_missing_first()
{
    const value_type input[] = { token::code::begin_record };
    format::iarchive in(input);
    person value("", 99);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_invalid_second()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_invalid_first()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void run()
{
    test_person();
    fail_missing_begin();
    fail_missing_end();
    fail_missing_second();
    fail_missing_first();
    fail_invalid_second();
    fail_invalid_first();
}

} // namespace struct_suite

//-----------------------------------------------------------------------------
// Split struct
//-----------------------------------------------------------------------------

namespace split_struct_suite
{

struct split_person
{
    split_person(std::string name, int age)
        : name(std::move(name)),
          age(age)
    {}

    template<typename T>
    void load(T& archive, const unsigned int)
    {
        archive >> name;
        archive >> age;
    }

    template<typename T>
    void save(T& archive, const unsigned int) const
    {
        archive << name;
        archive << age;
    }

    std::string name;
    int age;

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

void test_person()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00,
                                 token::code::end_record };
    format::iarchive in(input);
    split_person value("", 99);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.name, "ABC");
    TRIAL_PROTOCOL_TEST_EQUAL(value.age, 127);
}

void run()
{
    test_person();
}

} // namespace split_struct_suite

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

void test_map_one()
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
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
    test_map_empty();
    test_map_one();
}

} // namespace container_suite

//-----------------------------------------------------------------------------
// dynamic::variable
//-----------------------------------------------------------------------------

namespace dynamic_suite
{

using namespace trial::dynamic;

void test_null()
{
    const value_type input[] = { bintoken::token::code::null };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<nullable>(), true);
}

void test_boolean()
{
    const value_type input[] = { bintoken::token::code::true_value };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<boolean>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(value.value<bool>(), true);
}

void test_integer_small()
{
    const value_type input[] = { 0x02 };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<integer>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(value.value<signed int>(), 2);
}

void test_integer()
{
    const value_type input[] = { bintoken::token::code::int16, 0x02, 0x00 };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<integer>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(value.value<int>(), 2);
}

void test_number()
{
    const value_type input[] = { bintoken::token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<real>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(value.value<float>(), 1.0f);
}

void test_string()
{
    const value_type input[] = { bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43 };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(value.value<string>(), "ABC");
}

void test_array_empty()
{
    const value_type input[] = { bintoken::token::code::begin_array,
                                 0x00,
                                 bintoken::token::code::end_array };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<array>(), true);
    variable expect = array::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(value.begin(), value.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_array()
{
    const value_type input[] = { bintoken::token::code::begin_array,
                                 0x02,
                                 bintoken::token::code::true_value,
                                 0x02,
                                 bintoken::token::code::end_array };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<array>(), true);
    variable expect = array::make({ true, 2 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(value.begin(), value.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_map_empty()
{
    const value_type input[] = { bintoken::token::code::begin_assoc_array,
                                 bintoken::token::code::null,
                                 bintoken::token::code::end_assoc_array };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<map>(), true);
    variable expect = map::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(value.begin(), value.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void test_map()
{
    const value_type input[] = { bintoken::token::code::begin_assoc_array,
                                 bintoken::token::code::null,
                                 bintoken::token::code::begin_record,
                                 bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 bintoken::token::code::true_value,
                                 bintoken::token::code::end_record,
                                 bintoken::token::code::end_assoc_array };
    format::iarchive in(input);
    variable value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.is<map>(), true);
    variable expect = map::make({{ "ABC", true }});
    TRIAL_PROTOCOL_TEST_ALL_WITH(value.begin(), value.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    test_null();
    test_boolean();
    test_integer_small();
    test_integer();
    test_number();
    test_string();
    test_array_empty();
    test_array();
    test_map_empty();
    test_map();
}

} // namespace dynamic_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    integer_suite::run();
    number_suite::run();
    string_suite::run();
    array_suite::run();
    compact_array_suite::run();
    struct_suite::run();
    split_struct_suite::run();
    container_suite::run();
    dynamic_suite::run();

    return boost::report_errors();
}
