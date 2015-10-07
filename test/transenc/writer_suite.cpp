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
#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/transenc/writer.hpp>

namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::writer::value_type value_type;

BOOST_AUTO_TEST_SUITE(transenc_writer_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(result.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_null)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value<token::null>(), 1);
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], token::code::null);
}

BOOST_AUTO_TEST_CASE(test_false)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(false), 1);
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], token::code::false_value);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(true), 1);
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], token::code::true_value);
}

//-----------------------------------------------------------------------------
// Numbers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_integer_zero)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0), 1);
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], 0);
}

BOOST_AUTO_TEST_CASE(test_integer_int8)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(-128), 2);
    BOOST_REQUIRE_EQUAL(result.size(), 2);
    BOOST_REQUIRE_EQUAL(result[0], token::code::int8);
    BOOST_REQUIRE_EQUAL(result[1], 0x80);
}

BOOST_AUTO_TEST_CASE(test_integer_int16)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0x100), 3);
    BOOST_REQUIRE_EQUAL(result.size(), 3);
    BOOST_REQUIRE_EQUAL(result[0], token::code::int16);
    BOOST_REQUIRE_EQUAL(result[1], 0x00);
    BOOST_REQUIRE_EQUAL(result[2], 0x01);
}

BOOST_AUTO_TEST_CASE(test_integer_int32)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0x1000000), 5);
    BOOST_REQUIRE_EQUAL(result.size(), 5);
    BOOST_REQUIRE_EQUAL(result[0], token::code::int32);
    BOOST_REQUIRE_EQUAL(result[1], 0x00);
    BOOST_REQUIRE_EQUAL(result[2], 0x00);
    BOOST_REQUIRE_EQUAL(result[3], 0x00);
    BOOST_REQUIRE_EQUAL(result[4], 0x01);
}

BOOST_AUTO_TEST_CASE(test_integer_int64)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(UINT64_C(0x100000000000000)), 9);
    BOOST_REQUIRE_EQUAL(result.size(), 9);
    BOOST_REQUIRE_EQUAL(result[0], token::code::int64);
    BOOST_REQUIRE_EQUAL(result[1], 0x00);
    BOOST_REQUIRE_EQUAL(result[2], 0x00);
    BOOST_REQUIRE_EQUAL(result[3], 0x00);
    BOOST_REQUIRE_EQUAL(result[4], 0x00);
    BOOST_REQUIRE_EQUAL(result[5], 0x00);
    BOOST_REQUIRE_EQUAL(result[6], 0x00);
    BOOST_REQUIRE_EQUAL(result[7], 0x00);
    BOOST_REQUIRE_EQUAL(result[8], 0x01);
}

BOOST_AUTO_TEST_CASE(test_float_zero)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0.0f), 5);
    BOOST_REQUIRE_EQUAL(result.size(), 5);
    BOOST_REQUIRE_EQUAL(result[0], token::code::float32);
    BOOST_REQUIRE_EQUAL(result[1], 0x00);
    BOOST_REQUIRE_EQUAL(result[2], 0x00);
    BOOST_REQUIRE_EQUAL(result[3], 0x00);
    BOOST_REQUIRE_EQUAL(result[4], 0x00);
}

BOOST_AUTO_TEST_CASE(test_double_zero)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value(0.0), 9);
    BOOST_REQUIRE_EQUAL(result.size(), 9);
    BOOST_REQUIRE_EQUAL(result[0], token::code::float64);
    BOOST_REQUIRE_EQUAL(result[1], 0x00);
    BOOST_REQUIRE_EQUAL(result[2], 0x00);
    BOOST_REQUIRE_EQUAL(result[3], 0x00);
    BOOST_REQUIRE_EQUAL(result[4], 0x00);
    BOOST_REQUIRE_EQUAL(result[5], 0x00);
    BOOST_REQUIRE_EQUAL(result[6], 0x00);
    BOOST_REQUIRE_EQUAL(result[7], 0x00);
    BOOST_REQUIRE_EQUAL(result[8], 0x00);
}

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_abc)
{
    std::vector<value_type> result;
    format::writer writer(result);
    std::string data("ABC");
    BOOST_REQUIRE_EQUAL(writer.value(data), 5);
    BOOST_REQUIRE_EQUAL(result.size(), 5);
    BOOST_REQUIRE_EQUAL(result[0], token::code::string8);
    BOOST_REQUIRE_EQUAL(result[1], 0x03);
    BOOST_REQUIRE_EQUAL(result[2], 0x41);
    BOOST_REQUIRE_EQUAL(result[3], 0x42);
    BOOST_REQUIRE_EQUAL(result[4], 0x43);
}

BOOST_AUTO_TEST_CASE(test_string_literal_abc)
{
    std::vector<value_type> result;
    format::writer writer(result);
    BOOST_REQUIRE_EQUAL(writer.value("ABC"), 5);
    BOOST_REQUIRE_EQUAL(result.size(), 5);
    BOOST_REQUIRE_EQUAL(result[0], token::code::string8);
    BOOST_REQUIRE_EQUAL(result[1], 0x03);
    BOOST_REQUIRE_EQUAL(result[2], 0x41);
    BOOST_REQUIRE_EQUAL(result[3], 0x42);
    BOOST_REQUIRE_EQUAL(result[4], 0x43);
}

BOOST_AUTO_TEST_CASE(test_string_view_abc)
{
    std::vector<value_type> result;
    format::writer writer(result);
    std::string data("ABC");
    boost::string_ref view(data.data());
    BOOST_REQUIRE_EQUAL(writer.value(view), 5);
    BOOST_REQUIRE_EQUAL(result.size(), 5);
    BOOST_REQUIRE_EQUAL(result[0], token::code::string8);
    BOOST_REQUIRE_EQUAL(result[1], 0x03);
    BOOST_REQUIRE_EQUAL(result[2], 0x41);
    BOOST_REQUIRE_EQUAL(result[3], 0x42);
    BOOST_REQUIRE_EQUAL(result[4], 0x43);
}

//-----------------------------------------------------------------------------
// Binary data
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_binary_empty)
{
    std::vector<value_type> result;
    format::writer writer(result);
    boost::array<value_type, 0> data;
    BOOST_REQUIRE_EQUAL(writer.value(data), 2);
    BOOST_REQUIRE_EQUAL(result.size(), 2);
    BOOST_REQUIRE_EQUAL(result[0], token::code::binary8);
    BOOST_REQUIRE_EQUAL(result[1], 0x00);
}

BOOST_AUTO_TEST_CASE(test_binary_three)
{
    std::vector<value_type> result;
    format::writer writer(result);
    value_type data[] = { 0x41, 0x42, 0x43 };
    BOOST_REQUIRE_EQUAL(writer.value(data), 5);
    BOOST_REQUIRE_EQUAL(result.size(), 5);
    BOOST_REQUIRE_EQUAL(result[0], token::code::binary8);
    BOOST_REQUIRE_EQUAL(result[1], 0x03);
    BOOST_REQUIRE_EQUAL(result[2], 0x41);
    BOOST_REQUIRE_EQUAL(result[3], 0x42);
    BOOST_REQUIRE_EQUAL(result[4], 0x43);
}

BOOST_AUTO_TEST_SUITE_END()
