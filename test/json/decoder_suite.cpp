///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/detail/decoder.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;

//-----------------------------------------------------------------------------
// Whitespaces
//-----------------------------------------------------------------------------

namespace whitespace_suite
{

void test_empty()
{
    const char input[] = "";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_spaces()
{
    const char input[] = "  ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_tabs()
{
    const char input[] = "\t\t";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_carriage_returns()
{
    const char input[] = "\r\r";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_newlines()
{
    const char input[] = "\n\n";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_junk()
{
    const char input[] = "n true";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
}

void run()
{
    test_empty();
    test_spaces();
    test_tabs();
    test_carriage_returns();
    test_newlines();
    test_junk();
}

} // namespace whitespace_suite

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_null()
{
    const char input[] = "null";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::null);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_null_white()
{
    const char input[] = "  null  ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::null);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_nul()
{
    const char input[] = "nul";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "nul");
}

void fail_nuller()
{
    const char input[] = "nuller";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "nuller");
}

void test_false()
{
    const char input[] = "false";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::false_value);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_false_white()
{
    const char input[] = "  false  ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::false_value);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_fals()
{
    const char input[] = "fals";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "fals");
}

void fail_falser()
{
    const char input[] = "falser";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "falser");
}

void test_true()
{
    const char input[] = "true";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::true_value);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_true_white()
{
    const char input[] = "  true  ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::true_value);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_tru()
{
    const char input[] = "tru";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "tru");
}

void fail_truer()
{
    const char input[] = "truer";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "truer");
}

void run()
{
    test_null();
    test_null_white();
    fail_nul();
    fail_nuller();

    test_false();
    test_false_white();
    fail_fals();
    fail_falser();

    test_true();
    test_true_white();
    fail_tru();
    fail_truer();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

namespace integer_suite
{

void test_zero()
{
    const char input[] = "0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<int>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_zero_white()
{
    const char input[] = "  0  ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<boost::int64_t>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_hundred()
{
    const char input[] = "100";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<boost::int64_t>(), 100);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_hundred()
{
    const char input[] = "-100";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<boost::int64_t>(), -100);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_large()
{
    const char input[] = "100000000000000000";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<boost::int64_t>(), INT64_C(100000000000000000));
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_max()
{
    const char input[] = "9223372036854775807";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<boost::int64_t>(), INT64_C(9223372036854775807));
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_minus()
{
    const char input[] = "-";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "-");
}

void fail_minus_white()
{
    const char input[] = "- 0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "-");
}

void fail_minus_alpha()
{
    const char input[] = "-a";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "-");
}

void fail_too_large()
{
    const char input[] = "10000000000000000000";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "10000000000000000000");
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<boost::int64_t>(),
                              json::error,
                              "invalid value");
}

void fail_as_float()
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<float>(),
                              json::error,
                              "incompatible type");
}

void fail_as_string()
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<int>(), 1);
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<std::string>(),
                              boost::system::system_error,
                              "incompatible type");
}

void test_short()
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<short>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_int()
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<int>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_long()
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<long>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_intmax()
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<boost::intmax_t>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_unsigned()
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<unsigned int>(), 1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_unsigned_negative()
{
    const char input[] = "-1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<unsigned int>(),
                              json::error,
                              "invalid value");
}

void run()
{
    test_zero();
    test_zero_white();
    test_hundred();
    test_minus_hundred();
    test_large();
    test_max();
    fail_minus();
    fail_minus_white();
    fail_minus_alpha();
    fail_too_large();
    fail_as_float();
    fail_as_string();

    test_short();
    test_int();
    test_long();
    test_intmax();
    test_unsigned();
    fail_unsigned_negative();
}

} // namespace integer_suite

//-----------------------------------------------------------------------------
// Floating
//-----------------------------------------------------------------------------

namespace floating_suite
{

void test_zero()
{
    const char input[] = "0.0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 0.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one()
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_minus_one()
{
    const char input[] = "-1.0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), -1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), -1.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_half()
{
    const char input[] = "0.5";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 0.5f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 0.5);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one_exp_one()
{
    const char input[] = "1e1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 1e1f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one_upper_exp_one()
{
    const char input[] = "1E1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 1e1f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one_dot_exp_one()
{
    const char input[] = "1.0e1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 1e1f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one_exp_plus_one()
{
    const char input[] = "1e+1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 1e1f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_one_exp_minus_one()
{
    const char input[] = "1e-1";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 1e-1f);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1e-1);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_missing_fraction()
{
    const char input[] = "0.";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0.");
}

void fail_missing_fraction_white()
{
    const char input[] = "0. ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0.");
}

void fail_missing_exponent()
{
    const char input[] = "0e";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0e");
}

void fail_missing_exponent_white()
{
    const char input[] = "0e ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0e");
}

void fail_missing_exponent_plus()
{
    const char input[] = "0e+";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0e+");
}

void fail_missing_exponent_plus_white()
{
    const char input[] = "0e+ ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0e+");
}

void fail_missing_exponent_minus()
{
    const char input[] = "0e-";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0e-");
}

void fail_missing_exponent_minus_white()
{
    const char input[] = "0e- ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0e-");
}

void fail_as_int()
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1.0);
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<int>(),
                              json::error,
                              "incompatible type");
}

void fail_as_string()
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 1.0);
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<std::string>(),
                              json::error,
                              "incompatible type");
}
void run()
{
    test_zero();
    test_one();
    test_minus_one();
    test_half();
    test_one_exp_one();
    test_one_upper_exp_one();
    test_one_dot_exp_one();
    test_one_exp_plus_one();
    test_one_exp_minus_one();
    fail_missing_fraction();
    fail_missing_fraction_white();
    fail_missing_exponent();
    fail_missing_fraction_white();
    fail_missing_exponent_plus();
    fail_missing_exponent_plus_white();
    fail_missing_exponent_minus();
    fail_missing_exponent_minus_white();
    fail_as_int();
    fail_as_string();
}

} // namespace floating_suite

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_empty()
{
    const char input[] = "\"\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\"");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_space()
{
    const char input[] = "\" \"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), " ");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\" \"");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_alpha()
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "alpha");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_alpha_bravo()
{
    const char input[] = "\"alpha bravo\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "alpha bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), input);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_quote()
{
    const char input[] = "\"\\\"\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\"");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\\"\"");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_reverse_solidus()
{
    const char input[] = "\"\\\\\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\\");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_solidus()
{
    const char input[] = "\"\\/\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "/");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_backspace()
{
    const char input[] = "\"\\b\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\b");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\b\"");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_formfeed()
{
    const char input[] = "\"\\f\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\f");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_newline()
{
    const char input[] = "\"\\n\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\n");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_carriage_return()
{
    const char input[] = "\"\\r\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\r");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_tab()
{
    const char input[] = "\"\\t\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\t");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_unicode_one()
{
    const char input[] = "\"\\u0001\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\x01");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u0001\"");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_unicode_a()
{
    const char input[] = "\"\\u0061\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "a");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u0061\"");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_unicode_0123()
{
    const char input[] = "\"\\u0123\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\u0123");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_unicode_4567()
{
    const char input[] = "\"\\u4567\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\u4567");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_unicode_89AB()
{
    const char input[] = "\"\\u89AB\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\u89AB");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_escape_unicode_CDEF()
{
    const char input[] = "\"\\uCDEF\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "\uCDEF");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void fail_escape_unicode_missing_one()
{
    const char input[] = "\"\\u000\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u000");
}

void fail_escape_unicode_missing_two()
{
    const char input[] = "\"\\u00\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u00");
}

void fail_escape_unicode_missing_three()
{
    const char input[] = "\"\\u0\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u0");
}

void fail_escape_unicode_missing_four()
{
    const char input[] = "\"\\u\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u");
}

void fail_escape_unicode_eof()
{
    const char input[] = "\"\\u0000";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u0000");
}

void fail_escape_unicode_eof_one()
{
    const char input[] = "\"\\u000";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u000");
}

void fail_escape_unicode_eof_two()
{
    const char input[] = "\"\\u00";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u00");
}

void fail_escape_unicode_eof_three()
{
    const char input[] = "\"\\u0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u0");
}

void fail_escape_unicode_eof_four()
{
    const char input[] = "\"\\u";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\u");
}

void fail_escape()
{
    const char input[] = "\"\\\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\\\"");
}

void fail_begin()
{
    const char input[] = "\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"");
}

void fail_as_int()
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<int>(),
                              json::error,
                              "incompatible type");
}

void fail_as_float()
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "alpha");
    TRIAL_PROTOCOL_TEST_THROW(decoder.value<float>(),
                              json::error,
                              "incompatible type");
}

void run()
{
    test_empty();
    test_space();
    test_alpha();
    test_alpha_bravo();
    test_escape_quote();
    test_escape_reverse_solidus();
    test_escape_solidus();
    test_escape_backspace();
    test_escape_formfeed();
    test_escape_newline();
    test_escape_carriage_return();
    test_escape_tab();
    test_escape_unicode_one();
    test_escape_unicode_a();
    test_escape_unicode_0123();
    test_escape_unicode_4567();
    test_escape_unicode_89AB();
    test_escape_unicode_CDEF();
    fail_escape_unicode_missing_one();
    fail_escape_unicode_missing_two();
    fail_escape_unicode_missing_three();
    fail_escape_unicode_missing_four();
    fail_escape_unicode_eof();
    fail_escape_unicode_eof_one();
    fail_escape_unicode_eof_two();
    fail_escape_unicode_eof_three();
    fail_escape_unicode_eof_four();
    fail_escape();
    fail_begin();
    fail_as_int();
    fail_as_float();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// String pangram
//
// Adapted from http://www.cl.cam.ac.uk/~mgk25/ucs/examples/quickbrown.txt
//-----------------------------------------------------------------------------

namespace pangram_suite
{

void test_english()
{
    const char input[] = "\"The quick brown fox jumps over the lazy dog\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "The quick brown fox jumps over the lazy dog");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_german()
{
    const char input[] = "\"Falsches \\u00DCben von Xylophonmusik qu\\u00E4lt jeden gr\\u00F6\\u00DFeren Zwerg\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "Falsches Üben von Xylophonmusik quält jeden größeren Zwerg");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_danish()
{
    const char input[] = "\"Quizdeltagerne spiste jordb\\u00E6r med fl\\u00F8de, mens cirkusklovnen Wolther spillede p\\u00E5 xylofon\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "Quizdeltagerne spiste jordbær med fløde, mens cirkusklovnen Wolther spillede på xylofon");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_greek()
{
    const char input[] = "\"\\u0393\\u03B1\\u03B6\\u03AD\\u03B5\\u03C2 \\u03BA\\u03B1\\u1F76 \\u03BC\\u03C5\\u03C1\\u03C4\\u03B9\\u1F72\\u03C2 \\u03B4\\u1F72\\u03BD \\u03B8\\u1F70 \\u03B2\\u03C1\\u1FF6 \\u03C0\\u03B9\\u1F70 \\u03C3\\u03C4\\u1F78 \\u03C7\\u03C1\\u03C5\\u03C3\\u03B1\\u03C6\\u1F76 \\u03BE\\u03AD\\u03C6\\u03C9\\u03C4\\u03BF\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "Γαζέες καὶ μυρτιὲς δὲν θὰ βρῶ πιὰ στὸ χρυσαφὶ ξέφωτο");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_english();
    test_german();
    test_danish();
    test_greek();
}

} // namespace pangram_suite

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

namespace container_suite
{

void test_begin_object()
{
    const char input[] = "{";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "{");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_begin_object_white()
{
    const char input[] = " { ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "{");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_end_object()
{
    const char input[] = "}";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "}");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_end_object_white()
{
    const char input[] = " } ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "}");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_object()
{
    const char input[] = "{ \"key\" : false }";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_object);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "{");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "key");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::name_separator);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), ":");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::false_value);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_object);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "}");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array_begin()
{
    const char input[] = "[";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "[");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array_begin_white()
{
    const char input[] = " [ ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "[");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array_end()
{
    const char input[] = "]";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "]");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array_end_white()
{
    const char input[] = " ] ";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "]");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_array()
{
    const char input[] = "[true, false]";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::begin_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "[");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::true_value);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::value_separator);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), ",");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::false_value);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end_array);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "]");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_begin_object();
    test_begin_object_white();
    test_end_object();
    test_end_object_white();
    test_object();
    test_array_begin();
    test_array_begin_white();
    test_array_end();
    test_array_end_white();
    test_array();
}

} // namespace container_suite

//-----------------------------------------------------------------------------
// View
//-----------------------------------------------------------------------------

namespace view_suite
{

void test_null()
{
    const char input[] = "null";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "null");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_true()
{
    const char input[] = "true";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::true_value);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "true");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_false()
{
    const char input[] = "false";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::false_value);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "false");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_integer_zero()
{
    const char input[] = "0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<boost::intmax_t>(), 0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_floating_zero()
{
    const char input[] = "0.0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "0.0");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<double>(), 0.0);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_floating_float()
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::floating);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "1.0");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<float>(), 1.0f);
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_string_empty()
{
    const char input[] = "\"\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"\"");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void test_string_alpha()
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.literal(), "\"alpha\"");
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.value<std::string>(), "alpha");
    decoder.next();
    TRIAL_PROTOCOL_TEST_EQUAL(decoder.code(), token::code::end);
}

void run()
{
    test_null();
    test_true();
    test_false();
    test_integer_zero();
    test_floating_zero();
    test_floating_float();
    test_string_empty();
    test_string_alpha();
}

} // namespace view_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    whitespace_suite::run();
    basic_suite::run();
    integer_suite::run();
    floating_suite::run();
    string_suite::run();
    pangram_suite::run();
    container_suite::run();
    view_suite::run();

    return boost::report_errors();
}
