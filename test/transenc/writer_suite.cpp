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
#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/transenc/writer.hpp>
#include <trial/protocol/transenc/error.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::writer::value_type value_type;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void test_null()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::null>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::null);
}

void test_false()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(false), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::false_value);
}

void test_true()
{
    std::vector<value_type> result;
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
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0);
}

void test_int8()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(-128), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x80);
}

void test_int16()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0x100), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int16);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x01);
}

void test_int32()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(0x1000000), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::int32);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x00);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x01);
}

void test_int64()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(UINT64_C(0x100000000000000)), 9);
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

void test_float()
{
    std::vector<value_type> result;
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
    std::vector<value_type> result;
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
    test_int16();
    test_int32();
    test_int64();
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
    std::vector<value_type> result;
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
    std::vector<value_type> result;
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
    std::vector<value_type> result;
    format::writer writer(result);
    std::string data("ABC");
    boost::string_ref view(data.data());
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
// Binary data
//-----------------------------------------------------------------------------

namespace binary_suite
{

void test_empty()
{
    std::vector<value_type> result;
    format::writer writer(result);
    boost::array<value_type, 0> data;
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(data), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::binary8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x00);
}

void test_many()
{
    std::vector<value_type> result;
    format::writer writer(result);
    value_type data[] = { 0x41, 0x42, 0x43 };
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value(data), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::binary8);
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 0x03);
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 0x41);
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 0x42);
    TRIAL_PROTOCOL_TEST_EQUAL(result[4], 0x43);
}

void run()
{
    test_empty();
    test_many();
}

} // namespace binary_suite

//-----------------------------------------------------------------------------
// Record
//-----------------------------------------------------------------------------

namespace record_suite
{

void test_one()
{
    std::vector<value_type> result;
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
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_record>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_array()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_record>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_array>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_assoc_array()
{
    std::vector<value_type> result;
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
    std::vector<value_type> result;
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
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_array>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_record()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_array>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_record>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_assoc_array()
{
    std::vector<value_type> result;
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
    std::vector<value_type> result;
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
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_assoc_array>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_record()
{
    std::vector<value_type> result;
    format::writer writer(result);
    TRIAL_PROTOCOL_TEST_EQUAL(writer.value<token::begin_assoc_array>(), 1);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(writer.value<token::end_record>(),
                                    format::error, "unexpected token");
}

void fail_mismatched_end_array()
{
    std::vector<value_type> result;
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
    binary_suite::run();
    record_suite::run();
    array_suite::run();
    assoc_array_suite::run();

    return boost::report_errors();
}
