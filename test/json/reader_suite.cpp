///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <scoped_allocator>
#include <trial/protocol/json/reader.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void api_default_ctor()
{
    const char input[] = "";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void api_copy_ctor()
{
    const char input[] = "[ null ]";
    json::reader reader(input);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    json::reader copy(reader);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
}

void test_null()
{
    const char input[] = "null";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::null);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::nullable);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "null");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void test_false()
{
    const char input[] = "false";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::false_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "false");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_true()
{
    const char input[] = "true";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "true");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_true_output()
{
    const char input[] = "true";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    bool result;
    TRIAL_PROTOCOL_TEST_NO_THROW(reader.value(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result, true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_integer()
{
    const char input[] = "1";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_integer_const()
{
    const char input[] = "1";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<const int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_integer_output()
{
    const char input[] = "1";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    int result;
    TRIAL_PROTOCOL_TEST_NO_THROW(reader.value(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result, 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_float()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<float>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.0");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_float_output()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    float result;
    TRIAL_PROTOCOL_TEST_NO_THROW(reader.value(result));
    TRIAL_PROTOCOL_TEST_EQUAL(result, 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_double()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.0");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_long_double()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<long double>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.0");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_string()
{
    const char input[] = "\"alpha\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"alpha\"");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_string_allocator()
{
    const char input[] = "\"alpha\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    using string_type = std::basic_string<char, std::char_traits<char>, std::scoped_allocator_adaptor<std::allocator<char>>>;
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<string_type>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"alpha\"");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_string_output()
{
    const char input[] = "\"alpha\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    std::string result;
    reader.value(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result, "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"alpha\"");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void fail_true_space_true()
{
    const char input[] = "true true";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "true");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_true_comma_true()
{
    const char input[] = "true,true";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "true");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void run()
{
    api_default_ctor();
    api_copy_ctor();
    test_null();
    test_false();
    test_true();
    test_true_output();
    test_integer();
    test_integer_const();
    test_integer_output();
    test_float();
    test_float_output();
    test_double();
    test_long_double();
    test_string();
    test_string_allocator();
    test_string_output();
    fail_true_space_true();
    fail_true_comma_true();
}

} // namespace basic_suite

namespace ubasic_suite
{

void test_empty()
{
    const unsigned char input[] = "";
    json::basic_reader<unsigned char> reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    test_empty();
}

} // namespace ubasic_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_empty()
{
    const char input[] = "[]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_one()
{
    const char input[] = "[1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_many()
{
    const char input[] = "[1,2,3]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "[");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "1,2,3]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ",2,3]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "2");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ",3]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "3");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "]");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_nested_one()
{
    const char input[] = "[[1]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_nested_many_siblings()
{
    const char input[] = "[[1],[2]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "[");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "[1],[2]]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "[");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "1],[2]]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "],[2]]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "]");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ",[2]]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "[");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "2]]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "2");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "]]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "]");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "]");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void fail_missing_value()
{
    const char input[] = "[,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "[");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ",]");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), ",");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "]");
}

void fail_trailing_separator()
{
    const char input[] = "[1,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "]");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
}

void fail_empty_mismatched()
{
    const char input[] = "[}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::expected_end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "}");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
}

void fail_integer_one_mismatched()
{
    const char input[] = "[1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::expected_end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "}");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
}

void fail_outer()
{
    const char input[] = "[],false";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), ",");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "false");
}

void fail_missing_begin()
{
    const char input[] = "]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "]");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
}

void fail_missing_begin_after_array()
{
    const char input[] = "[]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "]");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
}

void fail_missing_begin_after_comma()
{
    const char input[] = "[],]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), ",");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "]");
}

void fail_missing_end()
{
    const char input[] = "[";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
}

void fail_concatenated_arrays()
{
    const char input[] = "[][]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "[");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "]");
}

void fail_nested_concatenated_arrays()
{
    const char input[] = "[[][]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "[");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "]]");
}

void run()
{
    test_empty();
    test_integer_one();
    test_integer_many();
    test_integer_nested_one();
    test_integer_nested_many_siblings();
    fail_missing_value();
    fail_trailing_separator();
    fail_empty_mismatched();
    fail_integer_one_mismatched();
    fail_outer();
    fail_missing_begin();
    fail_missing_begin_after_array();
    fail_missing_begin_after_comma();
    fail_missing_end();
    fail_concatenated_arrays();
    fail_nested_concatenated_arrays();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Object
//-----------------------------------------------------------------------------

namespace object_suite
{

void test_empty()
{
    const char input[] = "{}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_empty2()
{
    boost::string_view input{"{}\n\n{}", 3};
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_one()
{
    const char input[] = "{\"alpha\":1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_many()
{
    const char input[] = "{\"alpha\":1,\"bravo\":2}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "{");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "\"alpha\":1,\"bravo\":2}");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"alpha\"");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ":1,\"bravo\":2}");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ",\"bravo\":2}");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"bravo\"");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ":2}");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "2");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "}");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "}");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");

    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_nested_one()
{
    const char input[] = "{\"alpha\":{\"helium\":2}}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "helium");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void fail_missing_colon()
{
    const char input[] = "{\"key\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_missing_value()
{
    const char input[] = "{\"key\":}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_trailing_separator()
{
    const char input[] = "{\"key\":1,}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_invalid_integer_key()
{
    const char input[] = "{1:1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ":1}");
}

void fail_invalid_null_key()
{
    const char input[] = "{null:1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "null");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), ":1}");
}

void fail_invalid_true_key()
{
    const char input[] = "{true:1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
}

void fail_invalid_object_key()
{
    const char input[] = "{{\"key\":1}:2}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
}

void fail_empty_mismatched()
{
    const char input[] = "{]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::expected_end_object);
}

void fail_one_mismatched()
{
    const char input[] = "{\"alpha\":1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::expected_end_object);
}

void fail_outer()
{
    const char input[] = "{},true";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_missing_begin()
{
    const char input[] = "}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "}");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
}

void fail_missing_begin_after_object()
{
    const char input[] = "{}}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "}");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
}

void fail_missing_begin_after_comma()
{
    const char input[] = "{},}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), ",");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "}");
}

void fail_missing_end()
{
    const char input[] = "{";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "{");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
}

void fail_concatenated_objects()
{
    const char input[] = "{}{}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "{");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "}");
}

void fail_nested_concatenated_objects()
{
    const char input[] = "[{}{}]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "{");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "}]");
}

void run()
{
    test_empty();
    test_empty2();
    test_one();
    test_many();
    test_nested_one();
    fail_missing_colon();
    fail_missing_value();
    fail_trailing_separator();
    fail_invalid_integer_key();
    fail_invalid_null_key();
    fail_invalid_true_key();
    fail_invalid_object_key();
    fail_empty_mismatched();
    fail_one_mismatched();
    fail_outer();
    fail_missing_begin();
    fail_missing_begin_after_object();
    fail_missing_begin_after_comma();
    fail_missing_end();
    fail_concatenated_objects();
    fail_nested_concatenated_objects();
}

} // namespace object_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    ubasic_suite::run();
    array_suite::run();
    object_suite::run();

    return boost::report_errors();
}
