///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/json/format.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::dynamic;
using namespace trial::protocol;

//-----------------------------------------------------------------------------

namespace buffer_suite
{

void format_string()
{
    variable data(true);
    std::string result;
    json::format(data, result);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "true");
}

void format_ostringstream()
{
    variable data(true);
    std::ostringstream result;
    json::format(data, result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "true");
}

void format_vector()
{
    variable data(true);
    std::vector<char> result;
    json::format(data, result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 't');
    TRIAL_PROTOCOL_TEST_EQUAL(result[1], 'r');
    TRIAL_PROTOCOL_TEST_EQUAL(result[2], 'u');
    TRIAL_PROTOCOL_TEST_EQUAL(result[3], 'e');
}

void run()
{
    format_string();
    format_ostringstream();
    format_vector();
}

} // namespace buffer_suite

//-----------------------------------------------------------------------------

namespace formatter_suite
{

void format_null()
{
    variable data;
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "null");
}

void format_boolean()
{
    variable data(true);
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "true");
}

void format_integer()
{
    variable data(2);
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "2");
}

void format_real()
{
    variable data(3.0);
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "3.00000000000000");
}

void format_string()
{
    variable data("alpha");
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "\"alpha\"");
}

void fail_wstring()
{
    variable data(L"alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::format<std::string>(data),
                                    json::error,
                                    "incompatible type");
}

void fail_u16string()
{
    variable data(u"alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::format<std::string>(data),
                                    json::error,
                                    "incompatible type");
}

void fail_u32string()
{
    variable data(U"alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::format<std::string>(data),
                                    json::error,
                                    "incompatible type");
}

void format_empty_array()
{
    variable data = array::make();
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[]");
}

void format_array()
{
    variable data = { null, true, 2, 3.0, "alpha" };
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[null,true,2,3.00000000000000,\"alpha\"]");
}

void format_empty_map()
{
    variable data = map::make();
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "{}");
}

void format_map()
{
    variable data =
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2},
            { "delta", 3.0},
            { "echo", "hydrogen" }
        };
    auto result = json::format<std::string>(data);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "{\"alpha\":null,\"bravo\":true,\"charlie\":2,\"delta\":3.00000000000000,\"echo\":\"hydrogen\"}");
}

void run()
{
    format_null();
    format_boolean();
    format_integer();
    format_real();
    format_string();
    fail_wstring();
    fail_u16string();
    fail_u32string();
    format_empty_array();
    format_array();
    format_empty_map();
    format_map();
}

} // namespace formatter_suite

//-----------------------------------------------------------------------------

namespace partial_suite
{

void format_null()
{
    variable data;
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    json::partial::format(data, writer);
    writer.value<json::token::end_array>();
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[null]");
}

void format_boolean()
{
    variable data(true);
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    json::partial::format(data, writer);
    writer.value<json::token::end_array>();
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[true]");
}

void format_integer()
{
    variable data(2);
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    json::partial::format(data, writer);
    writer.value<json::token::end_array>();
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[2]");
}

void format_real()
{
    variable data(3.0);
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    json::partial::format(data, writer);
    writer.value<json::token::end_array>();
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[3.00000000000000]");
}

void format_string()
{
    variable data("alpha");
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    json::partial::format(data, writer);
    writer.value<json::token::end_array>();
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[\"alpha\"]");
}

void fail_wstring()
{
    variable data(L"bravo");
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::partial::format(data, writer),
                                    json::error,
                                    "incompatible type");
}

void fail_u16string()
{
    variable data(u"charlie");
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::partial::format(data, writer),
                                    json::error,
                                    "incompatible type");
}

void fail_u32string()
{
    variable data(U"delta");
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(json::partial::format(data, writer),
                                    json::error,
                                    "incompatible type");
}

void format_array()
{
    variable data = { null, true, 2, 3.0, "alpha" };
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    json::partial::format(data, writer);
    writer.value<json::token::end_array>();
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[[null,true,2,3.00000000000000,\"alpha\"]]");
}

void format_map()
{
    variable data =
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2},
            { "delta", 3.0},
            { "echo", "hydrogen" }
        };
    std::string result;
    json::writer writer(result);
    writer.value<json::token::begin_array>();
    json::partial::format(data, writer);
    writer.value<json::token::end_array>();
    TRIAL_PROTOCOL_TEST_EQUAL(result, "[{\"alpha\":null,\"bravo\":true,\"charlie\":2,\"delta\":3.00000000000000,\"echo\":\"hydrogen\"}]");
}

void run()
{
    format_null();
    format_boolean();
    format_integer();
    format_real();
    format_string();
    fail_wstring();
    fail_u16string();
    fail_u32string();
    format_array();
    format_map();
}

} // namespace partial_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    buffer_suite::run();
    formatter_suite::run();
    partial_suite::run();

    return boost::report_errors();
}
