///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/json/chunk_reader.hpp>

using namespace trial::protocol;
namespace token = json::token;

//-----------------------------------------------------------------------------

namespace string_suite
{

void string_missing_quote()
{
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(!reader.next("\""));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(!reader.next("\"a"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(reader.finish("\"a\""));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
}

void string_missing_array_end()
{
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.next("[\"a\""));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(reader.next());
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST(!reader.next());
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST(reader.next("]"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void string_invalid_token()
{
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.finish("\"a\"%"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST(!reader.next());
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    string_missing_quote();
    string_missing_array_end();
    string_invalid_token();
}

} // namespace string_suite

//-----------------------------------------------------------------------------

namespace number_suite
{

void outer_int()
{
    // "0" is legal, but we must specify that we reached the input end
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(!reader.next("0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.finish("0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 0);
}

void outer_real()
{
    // "0.0" is legal
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(!reader.next("0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized); // Retains old state
    TRIAL_PROTOCOL_TEST(!reader.next("0."));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized); // Retains old state
    TRIAL_PROTOCOL_TEST(!reader.next("0.0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.finish("0.0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
}

void outer_zero_one_fail()
{
    // "01" is illegal
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(!reader.next("0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(reader.next("01"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_value);
}

void array_int()
{
    // "[0]"
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.next("["));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(!reader.next("0")); // Single zero is legal, but defer until next input
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.next("0]"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST(reader.next("]"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void array_int_int()
{
    // "[0,1]"
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.next("["));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(!reader.next("0")); // Single zero is legal, but defer until next input
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.next("0,1"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST(!reader.next(",1"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.next(",1]"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST(reader.next("]"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void array_real()
{
    // "[0.0]"
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.next("["));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(!reader.next("0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array); // Retains old state
    TRIAL_PROTOCOL_TEST(!reader.next("0."));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array); // Retains old state
    TRIAL_PROTOCOL_TEST(!reader.next("0.0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.next("0.0]"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST(reader.next("]"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void array_zero_one_fail()
{
    // "[01]" is illegal
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.next("["));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(!reader.next("0"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.next("01")); // Leading zero is illegal
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_value);
}

void run()
{
    outer_int();
    outer_real();
    outer_zero_one_fail();
    array_int();
    array_int_int();
    array_real();
    array_zero_one_fail();
}

} // namespace number_suite

//-----------------------------------------------------------------------------

namespace array_suite
{

void array_invalid_token()
{
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.finish("[%"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(!reader.next());
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    array_invalid_token();
}

} // namespace array_suite

//-----------------------------------------------------------------------------

namespace object_suite
{

void object_invalid_token()
{
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(reader.finish("{%"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST(!reader.next());
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    object_invalid_token();
}

} // namespace object_suite

//-----------------------------------------------------------------------------

namespace whitespace_suite
{

void white_only()
{
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(!reader.next("\n"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(!reader.next("\n\n"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(!reader.next("\n\n\n"));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
}

void white_keyword()
{
    const char input[] = "\n\nnull";
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(!reader.next(json::chunk_reader::view_type(input, 1)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(!reader.next(json::chunk_reader::view_type(input, 2)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(!reader.next(json::chunk_reader::view_type(input, 3)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(!reader.next(json::chunk_reader::view_type(input, 4)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(!reader.next(json::chunk_reader::view_type(input, 5)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(reader.next(json::chunk_reader::view_type(input, 6)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
}

void white_array_empty()
{
    json::chunk_reader reader;
    TRIAL_PROTOCOL_TEST(!reader.next(json::chunk_reader::view_type("\n[", 1)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::uninitialized);
    TRIAL_PROTOCOL_TEST(reader.next(json::chunk_reader::view_type("\n[", 2)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST(!reader.next(json::chunk_reader::view_type("\n]", 1)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array); // Retains old state
    TRIAL_PROTOCOL_TEST(reader.next(json::chunk_reader::view_type("\n]", 2)));
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void run()
{
    white_only();
    white_keyword();
    white_array_empty();
}

} // namespace whitespace_suite

//-----------------------------------------------------------------------------

int main()
{
    string_suite::run();
    number_suite::run();
    array_suite::run();
    object_suite::run();
    whitespace_suite::run();

    return boost::report_errors();
}
