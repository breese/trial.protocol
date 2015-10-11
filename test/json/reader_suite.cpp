///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/reader.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    const char input[] = "";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
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

void test_float()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::data);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<float>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.0");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_double()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.0");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_long_double()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::floating);
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

void fail_true_true()
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
    test_empty();
    test_null();
    test_false();
    test_true();
    test_integer();
    test_integer_const();
    test_float();
    test_double();
    test_long_double();
    test_string();
    fail_true_true();
}

} // namespace basic_suite

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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_one()
{
    const char input[] = "[1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_many()
{
    const char input[] = "[1,2,3]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_nested_one()
{
    const char input[] = "[[1]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_integer_nested_many_siblings()
{
    const char input[] = "[[1],[2]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void fail_missing_value()
{
    const char input[] = "[,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_trailing_separator()
{
    const char input[] = "[1,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_empty_mismatched()
{
    const char input[] = "[}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::expected_end_array);
}

void fail_integer_one_mismatched()
{
    const char input[] = "[1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::expected_end_array);
}

void fail_outer()
{
    const char input[] = "[],false";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.symbol(), token::symbol::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.category(), token::category::structural);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_one()
{
    const char input[] = "{\"alpha\":1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_many()
{
    const char input[] = "{\"alpha\":1,\"bravo\":2}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void test_nested_one()
{
    const char input[] = "{\"alpha\":{\"helium\":2}}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "helium");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
}

void fail_missing_colon()
{
    const char input[] = "{\"key\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void fail_trailing_separator()
{
    const char input[] = "{\"key\":1,}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
}

void fail_invalid_null_key()
{
    const char input[] = "{null:1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
}

void fail_invalid_true_key()
{
    const char input[] = "{true:1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
}

void fail_invalid_object_key()
{
    const char input[] = "{{\"key\":1}:2}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::invalid_key);
}

void fail_empty_mismatched()
{
    const char input[] = "{]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::expected_end_object);
}

void fail_one_mismatched()
{
    const char input[] = "{\"alpha\":1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
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
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.error(), json::unexpected_token);
}

void run()
{
    test_empty();
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
}

} // namespace object_suite

//-----------------------------------------------------------------------------
// boost::get
//-----------------------------------------------------------------------------

namespace get_suite
{

void test_bool()
{
    const char input[] = "true";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<bool>(reader), true);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_integer()
{
    const char input[] = "1";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<int>(reader), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_float()
{
    const char input[] = "1.0";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<double>(reader), 1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<float>(reader), 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void test_string()
{
    const char input[] = "\"alpha\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(boost::get<std::string>(reader), "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.next(), false);
}

void run()
{
    test_bool();
    test_integer();
    test_float();
    test_string();
}

} // namespace get_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    array_suite::run();
    object_suite::run();
    get_suite::run();

    return boost::report_errors();
}
