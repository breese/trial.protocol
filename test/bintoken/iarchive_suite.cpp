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
#include <trial/protocol/bintoken/serialization.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

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

namespace floating_suite
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

} // namespace floating_suite

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
// Binary
//-----------------------------------------------------------------------------

namespace binary_suite
{

void test_empty()
{
    const value_type input[] = { token::code::binary8, 0x00 };
    format::iarchive in(input);
    std::vector<std::uint8_t> value(4, 0xFF);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0);
}

void test_many()
{
    const value_type input[] = { token::code::binary8, 0x04, 0x11, 0x22, 0x33, 0x44 };
    format::iarchive in(input);
    std::vector<std::uint8_t> value(4, 0xFF);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], 0x11);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], 0x22);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], 0x33);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], 0x44);
}

void run()
{
    test_empty();
    test_many();
}

} // namespace binary_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_four()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x01, 0x02, 0x03, 0x04,
                                 token::code::end_array };
    format::iarchive in(input);
    value_type value[4] = { 0x10, 0x20, 0x30, 0x40 };
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], 0x01);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], 0x02);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], 0x03);
    TRIAL_PROTOCOL_TEST_EQUAL(value[3], 0x04);
}

void fail_too_short()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x01, 0x02, 0x03,
                                 token::code::end_array };
    format::iarchive in(input);
    value_type value[4] = { 0x10, 0x20, 0x30, 0x40 };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_too_long()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x01, 0x02, 0x03, 0x04, 0x05,
                                 token::code::end_array };
    format::iarchive in(input);
    value_type value[4] = { 0x10, 0x20, 0x30, 0x40 };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "expected end array bracket");
}

void fail_missing_end()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x01, 0x02, 0x03, 0x04 };
    format::iarchive in(input);
    value_type value[4] = { 0x10, 0x20, 0x30, 0x40 };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "expected end array bracket");
}

void fail_missing_begin()
{
    const value_type input[] = { 0x04,
                                 0x01, 0x02, 0x03, 0x04,
                                 token::code::end_array };
    format::iarchive in(input);
    value_type value[4] = { 0x10, 0x20, 0x30, 0x40 };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "unexpected token");
}

void fail_array_too_short()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x01, 0x02, 0x03, 0x04,
                                 token::code::end_array };
    format::iarchive in(input);
    value_type value[3] = { 0x10, 0x20, 0x30 };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_array_too_long()
{
    const value_type input[] = { token::code::begin_array,
                                 0x04,
                                 0x01, 0x02, 0x03, 0x04,
                                 token::code::end_array };
    format::iarchive in(input);
    value_type value[5] = { 0x10, 0x20, 0x30, 0x40, 0x50 };
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
// Pair
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
// Optional
//-----------------------------------------------------------------------------

namespace optional_suite
{

void test_value()
{
    const value_type input[] = { token::code::string8, 0x01, 'A' };
    format::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(value);
    TRIAL_PROTOCOL_TEST_EQUAL(*value, "A");
}

void test_null()
{
    const value_type input[] = { token::code::null };
    format::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(!value);
}

void test_null_value()
{
    const value_type input[] = { token::code::null,
                                 token::code::true_value };
    format::iarchive in(input);
    boost::optional<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(!value);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(value);
    TRIAL_PROTOCOL_TEST_EQUAL(*value, true);
}

void fail_wrong_type()
{
    const value_type input[] = { token::code::true_value };
    format::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void run()
{
    test_value();
    test_null();
    test_null_value();
    fail_wrong_type();
}

} // namespace optional_suite

//-----------------------------------------------------------------------------
// Vector
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
// Set
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
// Map
//-----------------------------------------------------------------------------

namespace map_suite
{

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

void test_bool_one()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(value["A"], true);
}

void test_bool_two()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x42,
                                 token::code::false_value,
                                 token::code::end_record,
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
                                    format::error, "unexpected token");
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
    const value_type input[] = { token::code::begin_assoc_array,
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
    const value_type input[] = { token::code::begin_assoc_array,
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
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_key_int()
{
    const value_type input[] = { token::code::begin_assoc_array,
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
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::null,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "invalid value");
}

void fail_unexpected_value_int()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 0x00,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(in >> value,
                                    format::error, "incompatible type");
}

void fail_unexpected_value_null()
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::null,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
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

} // namespace map_suite

//-----------------------------------------------------------------------------
// Struct
//-----------------------------------------------------------------------------

namespace struct_suite
{

struct person
{
    person(const std::string& name, int age)
        : name(name),
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
    split_person(const std::string& name, int age)
        : name(name),
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
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    integer_suite::run();
    floating_suite::run();
    string_suite::run();
    binary_suite::run();
    array_suite::run();
    pair_suite::run();
    optional_suite::run();
    vector_suite::run();
    set_suite::run();
    map_suite::run();
    struct_suite::run();
    split_struct_suite::run();
    container_suite::run();

    return boost::report_errors();
}
