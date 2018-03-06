///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/bintoken/format.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::dynamic;
using namespace trial::protocol;

using value_type = std::uint8_t;
using buffer_type = std::vector<value_type>;

//-----------------------------------------------------------------------------

namespace formatter_suite
{

void format_null()
{
    variable data;
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = { bintoken::token::code::null };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_boolean()
{
    variable data(true);
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = { bintoken::token::code::true_value };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_integer()
{
    // small-pos-int
    {
        variable data(0x00);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { 0x00 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(0x7F);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { 0x7F };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    // small-neg-int
    {
        variable data(-0x01);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { 0xFF };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(-0x20);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { 0xE0 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    // int8
    {
        variable data(-0x21);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int8, 0xDF };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(-0x80);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int8, 0x80 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    // int16
    {
        variable data(0x80);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int16, 0x80, 0x00 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(0x7FFF);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int16, 0xFF, 0x7F };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(-0x81);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int16, 0x7F, 0xFF };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(-0x8000);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int16, 0x00, 0x80 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    // int32
    {
        variable data(0x8000);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int32, 0x00, 0x80, 0x00, 0x00 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(0x7FFFFFFFL);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int32, 0xFF, 0xFF, 0xFF, 0x7F };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(-0x8001);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int32, 0xFF, 0x7F, 0xFF, 0xFF };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(-0x80000000L);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int32, 0x00, 0x00, 0x00, 0x80 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    // int64
    {
        variable data(0x80000000L);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int64, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(-0x80000001L);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::int64, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
}

void format_real()
{
    {
        variable data(3.0f);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(3.0);
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(bintoken::format<buffer_type>(data),
                                        bintoken::error,
                                        "incompatible type");
    }
}

void format_string()
{
    {
        variable data("ABC");
        auto result = bintoken::format<buffer_type>(data);
        const value_type expected[] = { bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43 };
        TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                     expected, expected + sizeof(expected),
                                     std::equal_to<value_type>());
    }
    {
        variable data(L"ABC");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(bintoken::format<buffer_type>(data),
                                        bintoken::error,
                                        "incompatible type");
    }
    {
        variable data(u"ABC");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(bintoken::format<buffer_type>(data),
                                        bintoken::error,
                                        "incompatible type");
    }
    {
        variable data(U"ABC");
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(bintoken::format<buffer_type>(data),
                                        bintoken::error,
                                        "incompatible type");
    }
}

void format_array()
{
    variable data = { null, true, 2, 3.0f, "ABC" };
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = {
        bintoken::token::code::begin_array,
        bintoken::token::code::null,
        bintoken::token::code::true_value,
        0x02,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::end_array
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_array_nested_array()
{
    variable data = { null, true, { 2, 3.0f }, "ABC" };
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = {
        bintoken::token::code::begin_array,
        bintoken::token::code::null,
        bintoken::token::code::true_value,
        bintoken::token::code::begin_array,
        0x02,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::end_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::end_array
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_array_nested_map()
{
    variable data = { null, true, {{ 2, 3.0f }} };
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = {
        bintoken::token::code::begin_array,
        bintoken::token::code::null,
        bintoken::token::code::true_value,
        bintoken::token::code::begin_assoc_array,
        0x02,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::end_assoc_array,
        bintoken::token::code::end_array
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_map()
{
    variable data =
        {
            { null, null },
            { true, true },
            { 2, 2 },
            { 3.0f, 3.0f },
            { "ABC", "ABC" }
        };
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = {
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::null,
        bintoken::token::code::null,
        bintoken::token::code::true_value,
        bintoken::token::code::true_value,
        0x02,
        0x02,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::end_assoc_array
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_map_nested_array()
{
    variable data =
        {
            { "ABC", { null, true, 2, 3.0f } }
        };
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = {
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::string8, 0x03, 0x41, 0x42, 0x43,
        bintoken::token::code::begin_array,
        bintoken::token::code::null,
        bintoken::token::code::true_value,
        0x02,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::end_array,
        bintoken::token::code::end_assoc_array
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_map_nested_map()
{
    variable data =
        {
            { null, null },
            { true, {{ 2, 3.0f }} }
        };
    auto result = bintoken::format<buffer_type>(data);
    const value_type expected[] = {
        bintoken::token::code::begin_assoc_array,
        bintoken::token::code::null,
        bintoken::token::code::null,
        bintoken::token::code::true_value,
        bintoken::token::code::begin_assoc_array,
        0x02,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::end_assoc_array,
        bintoken::token::code::end_assoc_array
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void run()
{
    format_null();
    format_boolean();
    format_integer();
    format_real();
    format_string();
    format_array();
    format_array_nested_array();
    format_array_nested_map();
    format_map();
    format_map_nested_array();
    format_map_nested_map();
}

} // namespace formatter_suite

//-----------------------------------------------------------------------------

namespace partial_suite
{

void format_null()
{
    variable data;
    buffer_type result;
    bintoken::writer writer(result);
    writer.value<bintoken::token::begin_record>();
    bintoken::partial::format(data, writer);
    writer.value<bintoken::token::end_record>();
    const value_type expected[] = {
        bintoken::token::code::begin_record,
        bintoken::token::code::null,
        bintoken::token::code::end_record
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_boolean()
{
    variable data(true);
    buffer_type result;
    bintoken::writer writer(result);
    writer.value<bintoken::token::begin_record>();
    bintoken::partial::format(data, writer);
    writer.value<bintoken::token::end_record>();
    const value_type expected[] = {
        bintoken::token::code::begin_record,
        bintoken::token::code::true_value,
        bintoken::token::code::end_record
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_integer()
{
    variable data(2);
    buffer_type result;
    bintoken::writer writer(result);
    writer.value<bintoken::token::begin_record>();
    bintoken::partial::format(data, writer);
    writer.value<bintoken::token::end_record>();
    const value_type expected[] = {
        bintoken::token::code::begin_record,
        0x02,
        bintoken::token::code::end_record
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void format_real()
{
    variable data(3.0f);
    buffer_type result;
    bintoken::writer writer(result);
    writer.value<bintoken::token::begin_record>();
    bintoken::partial::format(data, writer);
    writer.value<bintoken::token::end_record>();
    const value_type expected[] = {
        bintoken::token::code::begin_record,
        bintoken::token::code::float32, 0x00, 0x00, 0x40, 0x40,
        bintoken::token::code::end_record
    };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<value_type>());
}

void run()
{
    format_null();
    format_boolean();
    format_integer();
    format_real();
}

} // namespace partial_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    formatter_suite::run();
    partial_suite::run();

    return boost::report_errors();
}
