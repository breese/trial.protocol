///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/bintoken/parse.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::dynamic;
using namespace trial::protocol;

using value_type = bintoken::reader::value_type;

//-----------------------------------------------------------------------------

namespace parser_suite
{

void parse_empty()
{
    const std::array<value_type, 0> input = {};
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.same<nullable>());
    TRIAL_PROTOCOL_TEST(result.empty());
}

void parse_null()
{
    const value_type input[] = { bintoken::token::code::null };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.same<nullable>());
}

void parse_false()
{
    const value_type input[] = { bintoken::token::code::false_value };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.same<bool>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), false);
}

void parse_true()
{
    const value_type input[] = { bintoken::token::code::true_value };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.same<bool>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void parse_integer()
{
    // small-pos-int
    {
        const value_type input[] = { 0x02 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    // small-neg-int
    {
        const value_type input[] = { 0xFE };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), -2);
    }
    // int8
    {
        const value_type input[] = { bintoken::token::code::int8, 0x02 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<std::int8_t>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    // int16
    {
        const value_type input[] = { bintoken::token::code::int16, 0x02, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.same<std::int16_t>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    // int32
    {
        const value_type input[] = { bintoken::token::code::int32, 0x02, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.same<std::int32_t>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    // int64
    {
        const value_type input[] = { bintoken::token::code::int64, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.same<std::int64_t>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
}

void parse_real()
{
    // float32
    {
        const value_type input[] = { bintoken::token::code::float32, 0x00, 0x00, 0x80, 0x3F };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.same<float>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<float>(), 1.0f);
    }
    // float64
    {
        const value_type input[] = { bintoken::token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.same<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 1.0);
    }
}

void parse_string()
{
    // string8
    {
        const value_type input[] = { bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "ABC");
    }
    // string16
    {
        const value_type input[] = { bintoken::token::code::string16, 0x03, 0x00, 0x41, 0x42, 0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "ABC");
    }
    // string32
    {
        const value_type input[] = { bintoken::token::code::string32, 0x03, 0x00, 0x00, 0x00, 0x41, 0x42, 0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "ABC");
    }
    // string64
    {
        const value_type input[] = { bintoken::token::code::string64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x42, 0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<string>(), "ABC");
    }
}

void parse_compact_array()
{
    // array8_int8
    {
        const value_type input[] = {
            bintoken::token::code::array8_int8, 3 * bintoken::token::int8::size,
            0x41,
            0x42,
            0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array16_int8
    {
        const value_type input[] = {
            bintoken::token::code::array16_int8, 3 * bintoken::token::int8::size, 0x00,
            0x41,
            0x42,
            0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array32_int8
    {
        const value_type input[] = {
            bintoken::token::code::array32_int8, 3 * bintoken::token::int8::size, 0x00, 0x00, 0x00,
            0x41,
            0x42,
            0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array64_int8
    {
        const value_type input[] = {
            bintoken::token::code::array64_int8, 3 * bintoken::token::int8::size, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x41,
            0x42,
            0x43 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array8_int16
    {
        const value_type input[] = {
            bintoken::token::code::array8_int16, 3 * bintoken::token::int16::size,
            0x41, 0x00,
            0x42, 0x00,
            0x43, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array16_int16
    {
        const value_type input[] = {
            bintoken::token::code::array16_int16, 3 * bintoken::token::int16::size, 0x00,
            0x41, 0x00,
            0x42, 0x00,
            0x43, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array32_int16
    {
        const value_type input[] = {
            bintoken::token::code::array32_int16, 3 * bintoken::token::int16::size, 0x00, 0x00, 0x00,
            0x41, 0x00,
            0x42, 0x00,
            0x43, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array64_int16
    {
        const value_type input[] = {
            bintoken::token::code::array64_int16, 3 * bintoken::token::int16::size, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x41, 0x00,
            0x42, 0x00,
            0x43, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array8_int32
    {
        const value_type input[] = {
            bintoken::token::code::array8_int32, 3 * bintoken::token::int32::size,
            0x41, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array16_int32
    {
        const value_type input[] = {
            bintoken::token::code::array16_int32, 3 * bintoken::token::int32::size, 0x00,
            0x41, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array32_int32
    {
        const value_type input[] = {
            bintoken::token::code::array32_int32, 3 * bintoken::token::int32::size, 0x00, 0x00, 0x00,
            0x41, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array64_int32
    {
        const value_type input[] = {
            bintoken::token::code::array64_int32, 3 * bintoken::token::int32::size, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x41, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array8_int64
    {
        const value_type input[] = {
            bintoken::token::code::array8_int64, 3 * bintoken::token::int64::size,
            0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array16_int64
    {
        const value_type input[] = {
            bintoken::token::code::array16_int64, 3 * bintoken::token::int64::size, 0x00,
            0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array32_int64
    {
        const value_type input[] = {
            bintoken::token::code::array32_int64, 3 * bintoken::token::int64::size, 0x00, 0x00, 0x00,
            0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // array64_int64
    {
        const value_type input[] = {
            bintoken::token::code::array64_int64, 3 * bintoken::token::int64::size, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ 0x41, 0x42, 0x43 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
}

void parse_record()
{
    {
        const value_type input[] = {
            bintoken::token::code::begin_record,
            bintoken::token::code::end_record
        };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make();
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    {
        const value_type input[] = {
            bintoken::token::code::begin_record,
            bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
            bintoken::token::code::int16, 0x7F, 0x00,
            bintoken::token::code::end_record
        };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ "ABC", 127 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
}

void parse_record_nested_record()
{
    const value_type input[] = {
        bintoken::token::code::begin_record,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_record,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_record,
        bintoken::token::code::null,
        bintoken::token::code::end_record
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    const auto expected = array::make({ "ABC", array::make({ 127 }), null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_record_nested_array()
{
    const value_type input[] = {
        bintoken::token::code::begin_record,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_array,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_array,
        bintoken::token::code::null,
        bintoken::token::code::end_record
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    const auto expected = array::make({ "ABC", array::make({ 127 }), null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_record_nested_assoc_array()
{
    const value_type input[] = {
        bintoken::token::code::begin_record,
        bintoken::token::code::true_value,
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_assoc_array,
        bintoken::token::code::null,
        bintoken::token::code::end_record
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    const auto expected = array::make({ true, map::make({ "ABC", 127 }), null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_array()
{
    {
        const value_type input[] = {
            bintoken::token::code::begin_array,
            bintoken::token::code::end_array
        };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make();
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    {
        const value_type input[] = {
            bintoken::token::code::begin_array,
            bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
            bintoken::token::code::int16, 0x7F, 0x00,
            bintoken::token::code::end_array
        };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        const auto expected = array::make({ "ABC", 127 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
}

void parse_array_nested_record()
{
    const value_type input[] = {
        bintoken::token::code::begin_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_record,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_record,
        bintoken::token::code::null,
        bintoken::token::code::end_array
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    const auto expected = array::make({ "ABC", array::make({ 127 }), null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_array_nested_array()
{
    const value_type input[] = {
        bintoken::token::code::begin_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_array,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_array,
        bintoken::token::code::null,
        bintoken::token::code::end_array
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    const auto expected = array::make({ "ABC", array::make({127 }), null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_array_nested_assoc_array()
{
    const value_type input[] = {
        bintoken::token::code::begin_array,
        bintoken::token::code::true_value,
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_assoc_array,
        bintoken::token::code::null,
        bintoken::token::code::end_array
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    const auto expected = array::make({ true, map::make({ "ABC", 127 }), null });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_assoc_array()
{
    {
        const value_type input[] = {
            bintoken::token::code::begin_assoc_array,
            bintoken::token::code::end_assoc_array
        };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<map>());
        const auto expected = map::make();
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    {
        const value_type input[] = {
            bintoken::token::code::begin_assoc_array,
            bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
            bintoken::token::code::int16, 0x7F, 0x00,
            bintoken::token::code::end_assoc_array
        };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<map>());
        const auto expected = map::make({ "ABC", 127 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
    // Non-string key
    {
        const value_type input[] = {
            bintoken::token::code::begin_assoc_array,
            bintoken::token::code::int16, 0x7F, 0x00,
            bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
            bintoken::token::code::end_assoc_array
        };
        auto result = bintoken::parse(input);
        TRIAL_PROTOCOL_TEST(result.is<map>());
        const auto expected = map::make({ 127, "ABC" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected.begin(), expected.end(),
                                     std::equal_to<decltype(expected)>());
    }
}

void parse_assoc_array_nested_record()
{
    const value_type input[] = {
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_record,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_record,
        bintoken::token::code::end_assoc_array
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<map>());
    const auto expected = map::make({ "ABC", array::make({ 127 }) });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_assoc_array_nested_array()
{
    const value_type input[] = {
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_array,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_array,
        bintoken::token::code::end_assoc_array
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<map>());
    const auto expected = map::make({ "ABC", array::make({ 127 }) });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void parse_assoc_array_nested_assoc_array()
{
    const value_type input[] = {
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::string8, 0x03, 0x44, 0x45, 0x46,
        bintoken::token::code::int16, 0x7F, 0x00,
        bintoken::token::code::end_assoc_array,
        bintoken::token::code::end_assoc_array
    };
    auto result = bintoken::parse(input);
    TRIAL_PROTOCOL_TEST(result.is<map>());
    const auto expected = map::make({ "ABC", map::make({ "DEF", 127 }) });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<decltype(expected)>());
}

void run()
{
    parse_empty();
    parse_null();
    parse_false();
    parse_true();
    parse_integer();
    parse_real();
    parse_string();
    parse_compact_array();
    parse_record();
    parse_record_nested_record();
    parse_record_nested_array();
    parse_record_nested_assoc_array();
    parse_array();
    parse_array_nested_record();
    parse_array_nested_array();
    parse_array_nested_assoc_array();
    parse_assoc_array();
    parse_assoc_array_nested_record();
    parse_assoc_array_nested_array();
    parse_assoc_array_nested_assoc_array();
}

} // namespace parser_suite

//-----------------------------------------------------------------------------

namespace partial_suite
{

void run()
{
    // FIXME
}

} // namespace partial_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    parser_suite::run();
    partial_suite::run();

    return boost::report_errors();
}
