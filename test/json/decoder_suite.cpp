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

#include <trial/protocol/json/detail/decoder.hpp>

using namespace trial::protocol;

BOOST_AUTO_TEST_SUITE(json_decoder_suite)

//-----------------------------------------------------------------------------
// Whitespaces
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    const char input[] = "";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_spaces)
{
    const char input[] = "  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_tabs)
{
    const char input[] = "\t\t";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_carriage_returns)
{
    const char input[] = "\r\r";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_newlines)
{
    const char input[] = "\n\n";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_junk)
{
    const char input[] = "n true";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
}

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_null)
{
    const char input[] = "null";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::null_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_null)
{
    const char input[] = "  null  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::null_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_nul)
{
    const char input[] = "nul";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "nul");
}

BOOST_AUTO_TEST_CASE(fail_nuller)
{
    const char input[] = "nuller";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "nuller");
}

BOOST_AUTO_TEST_CASE(test_false)
{
    const char input[] = "false";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_false)
{
    const char input[] = "  false  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_fals)
{
    const char input[] = "fals";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "fals");
}

BOOST_AUTO_TEST_CASE(fail_falser)
{
    const char input[] = "falser";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "falser");
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const char input[] = "true";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::true_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_true)
{
    const char input[] = "  true  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::true_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_tru)
{
    const char input[] = "tru";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "tru");
}

BOOST_AUTO_TEST_CASE(fail_truer)
{
    const char input[] = "truer";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "truer");
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_integer_zero)
{
    const char input[] = "0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<int>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_integer_zero)
{
    const char input[] = "  0  ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_hundred)
{
    const char input[] = "100";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), 100);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_minus_hundred)
{
    const char input[] = "-100";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), -100);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_large)
{
    const char input[] = "100000000000000000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), INT64_C(100000000000000000));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_max)
{
    const char input[] = "9223372036854775807";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), INT64_C(9223372036854775807));
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_integer_minus)
{
    const char input[] = "-";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "-");
}

BOOST_AUTO_TEST_CASE(fail_integer_minus_white)
{
    const char input[] = "- 0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "-");
}

BOOST_AUTO_TEST_CASE(fail_integer_minus_a)
{
    const char input[] = "-a";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "-");
}

BOOST_AUTO_TEST_CASE(fail_integer_too_large)
{
    const char input[] = "10000000000000000000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "10000000000000000000");
    BOOST_REQUIRE_EQUAL(decoder.value<boost::int64_t>(), 0);
}

BOOST_AUTO_TEST_CASE(test_integer_short)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<short>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_int)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<int>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_long)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<long>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_intmax)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<boost::intmax_t>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_integer_unsigned)
{
    const char input[] = "1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<unsigned int>(), 1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_unsigned_negative)
{
    const char input[] = "-1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.value<unsigned int>(), 0);
    BOOST_REQUIRE_EQUAL(decoder.error(), json::invalid_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

//-----------------------------------------------------------------------------
// Floating
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_floating_zero)
{
    const char input[] = "0.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 0.0f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 0.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_one)
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1.0f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_minus_one)
{
    const char input[] = "-1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), -1.0f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), -1.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_half)
{
    const char input[] = "0.5";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 0.5f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 0.5);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_one_exp_one)
{
    const char input[] = "1e1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_one_upper_exp_one)
{
    const char input[] = "1E1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_one_dot_exp_one)
{
    const char input[] = "1.0e1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_one_exp_plus_one)
{
    const char input[] = "1e+1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_floating_one_exp_minus_one)
{
    const char input[] = "1e-1";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1e-1f);
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 1e-1);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_fraction)
{
    const char input[] = "0.";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0.");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_fraction)
{
    const char input[] = "0. ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0.");
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_exponent)
{
    const char input[] = "0e";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_exponent)
{
    const char input[] = "0e ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e");
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_exponent_plus)
{
    const char input[] = "0e+";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e+");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_exponent_plus)
{
    const char input[] = "0e+ ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e+");
}

BOOST_AUTO_TEST_CASE(fail_floating_eof_missing_exponent_minus)
{
    const char input[] = "0e-";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e-");
}

BOOST_AUTO_TEST_CASE(fail_floating_missing_exponent_minus)
{
    const char input[] = "0e- ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0e-");
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    const char input[] = "\"\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "alpha");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_quote)
{
    const char input[] = "\"\\\"\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\"");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\\"\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_reverse_solidus)
{
    const char input[] = "\"\\\\\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\\");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_solidus)
{
    const char input[] = "\"\\/\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "/");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_backspace)
{
    const char input[] = "\"\\b\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\b");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\b\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_formfeed)
{
    const char input[] = "\"\\f\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\f");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_newline)
{
    const char input[] = "\"\\n\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\n");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_carriage_return)
{
    const char input[] = "\"\\r\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\r");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_tab)
{
    const char input[] = "\"\\t\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\t");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_one)
{
    const char input[] = "\"\\u0001\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\x01");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0001\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_a)
{
    const char input[] = "\"\\u0061\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "a");
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0061\"");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_0123)
{
    const char input[] = "\"\\u0123\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\u0123");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_4567)
{
    const char input[] = "\"\\u4567\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\u4567");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_89AB)
{
    const char input[] = "\"\\u89AB\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\u89AB");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_string_escape_unicode_CDEF)
{
    const char input[] = "\"\\uCDEF\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "\uCDEF");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_one)
{
    const char input[] = "\"\\u000\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u000");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_two)
{
    const char input[] = "\"\\u00\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u00");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_three)
{
    const char input[] = "\"\\u0\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_missing_four)
{
    const char input[] = "\"\\u\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::error);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof)
{
    const char input[] = "\"\\u0000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0000");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_one)
{
    const char input[] = "\"\\u000";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u000");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_two)
{
    const char input[] = "\"\\u00";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u00");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_three)
{
    const char input[] = "\"\\u0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u0");
}

BOOST_AUTO_TEST_CASE(fail_string_escape_unicode_eof_four)
{
    const char input[] = "\"\\u";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\\u");
}

BOOST_AUTO_TEST_CASE(fail_string_escape)
{
    const char input[] = "\"\\\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(fail_string_begin)
{
    const char input[] = "\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"");
}
//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_object_open)
{
    const char input[] = "{";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::object_open);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_object_open)
{
    const char input[] = " { ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::object_open);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_object_close)
{
    const char input[] = "}";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::object_close);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_object_close)
{
    const char input[] = " } ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::object_close);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_object)
{
    const char input[] = "{ \"key\" : false }";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::object_open);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "key");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::name_separator);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::object_close);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_array_open)
{
    const char input[] = "[";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::array_open);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_array_open)
{
    const char input[] = " [ ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::array_open);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_array_close)
{
    const char input[] = "]";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::array_close);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_white_array_close)
{
    const char input[] = " ] ";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::array_close);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_array)
{
    const char input[] = "[true, false]";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::array_open);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::true_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::value_separator);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::false_value);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::array_close);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

//-----------------------------------------------------------------------------
// View
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_view_null)
{
    const char input[] = "null";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::null_value);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "null");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_view_true)
{
    const char input[] = "true";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::true_value);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "true");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_view_false)
{
    const char input[] = "false";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::false_value);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "false");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_view_integer_zero)
{
    const char input[] = "0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::integer);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0");
    BOOST_REQUIRE_EQUAL(decoder.value<boost::intmax_t>(), 0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_view_floating_zero)
{
    const char input[] = "0.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "0.0");
    BOOST_REQUIRE_EQUAL(decoder.value<double>(), 0.0);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_view_floating_float)
{
    const char input[] = "1.0";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::floating);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "1.0");
    BOOST_REQUIRE_EQUAL(decoder.value<float>(), 1.0f);
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

//-----------------------------------------------------------------------------
// View
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_view_string_empty)
{
    const char input[] = "\"\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"\"");
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_CASE(test_view_string_alpha)
{
    const char input[] = "\"alpha\"";
    json::detail::decoder decoder(input);
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::string);
    BOOST_REQUIRE_EQUAL(decoder.literal(), "\"alpha\"");
    BOOST_REQUIRE_EQUAL(decoder.value<std::string>(), "alpha");
    decoder.next();
    BOOST_REQUIRE_EQUAL(decoder.type(), json::detail::token::eof);
}

BOOST_AUTO_TEST_SUITE_END()
