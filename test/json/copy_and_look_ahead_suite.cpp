///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2021 Vinícius dos Santos Oliveira <vini.ipsmaker@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/partial/copy_and_look_ahead.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;

void test_int()
{
    const json::reader reader("{\"foo\": 42");
    int value = 0;
    auto on_value = [&](json::reader& reader) {
        value = reader.value<int>();
    };
    auto ret = json::partial::copy_and_look_ahead(reader, "foo", on_value);
    TRIAL_PROTOCOL_TEST_EQUAL(ret, true);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 42);
}

void test_string()
{
    const json::reader reader("{\"foo\": \"bar\"");
    std::error_code ec;
    auto ret = json::partial::copy_and_look_ahead(reader, "foo", "bar2", ec);
    TRIAL_PROTOCOL_TEST_EQUAL(ret, false);
    TRIAL_PROTOCOL_TEST_EQUAL(ec, json::errc::field_not_found);
    ret = json::partial::copy_and_look_ahead(reader, "foo", "bar");
    TRIAL_PROTOCOL_TEST_EQUAL(ret, true);
}

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    test_int();
    test_string();

    return boost::report_errors();
}

