///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/partial/skip.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;

void test_one_primitive()
{
    json::reader reader("42");
    auto skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "42");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_one_object()
{
    json::reader reader(R"({"skip": "me"})");
    auto skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, R"({"skip": "me"})");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_primitive()
{
    const char input[] = R"([
        42,
        42.5,
        null,
        true,
        "foo"
    ])";
    json::reader reader(input);
    json::reader::view_type skipped;
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(reader.next());

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 42);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "42");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), 42.5);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "42.5");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "null");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), true);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "true");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "foo");
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "\"foo\"");
}

void test_array()
{
    const char input[] = R"([
        [],
        42,
        [ false ],
        43,
        [ "test", false, 33 ],
        44,
        [ "test", false, [32, "foo"] ],
        45,
        [ "test", false, {"bar": "bar"} ],
        46
    ])";
    json::reader reader(input);
    json::reader::view_type skipped;
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(reader.next());

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "[]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 42);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "42");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "[ false ]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 43);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "43");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, R"([ "test", false, 33 ])");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 44);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "44");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, R"([ "test", false, [32, "foo"] ])");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 45);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "45");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, R"([ "test", false, {"bar": "bar"} ])");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 46);
    skipped = json::partial::skip(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "46");
}

void fail_comma_after_primitive()
{
    json::reader reader("false,");
    std::error_code ec;
    auto skipped = json::partial::skip(reader, ec);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "false");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::error);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::unexpected_token);
}

void fail_comma_after_object()
{
    json::reader reader(R"({"skip": "me"},)");
    std::error_code ec;
    auto skipped = json::partial::skip(reader, ec);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, R"({"skip": "me"})");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::error);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::unexpected_token);
}

void fail_invalid_token()
{
    json::reader reader(",");
    std::error_code ec;
    auto skipped = json::partial::skip(reader, ec);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::error);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::insufficient_tokens);
}

void fail_invalid_token_in_middle_of_object()
{
    json::reader reader(R"({"skip": "me"  {)");
    std::error_code ec;
    auto skipped = json::partial::skip(reader, ec);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, R"({"skip": "me")");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::error);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::insufficient_tokens);
}

void fail_invalid_token_in_middle_of_object2()
{
    json::reader reader(R"({"skip": "me"])");
    std::error_code ec;
    auto skipped = json::partial::skip(reader, ec);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, R"({"skip": "me")");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::error);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::insufficient_tokens);
}

void fail_on_close_array()
{
    json::reader reader("[]");
    reader.next();
    std::error_code ec;
    auto skipped = json::partial::skip(reader, ec);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::insufficient_tokens);
}

void fail_on_close_object()
{
    json::reader reader("{}");
    reader.next();
    std::error_code ec;
    auto skipped = json::partial::skip(reader, ec);
    TRIAL_PROTOCOL_TEST_EQUAL(skipped, "");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::insufficient_tokens);
}

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    test_one_primitive();
    test_one_object();
    test_primitive();
    test_array();
    fail_comma_after_primitive();
    fail_comma_after_object();
    fail_invalid_token();
    fail_invalid_token_in_middle_of_object();
    fail_invalid_token_in_middle_of_object2();
    fail_on_close_array();
    fail_on_close_object();

    return boost::report_errors();
}
