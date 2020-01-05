///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <trial/protocol/json/reader.hpp>
#include <trial/protocol/core/detail/lightweight_test.hpp>

using namespace trial::protocol;
namespace token = json::token;

// Test data from
//   http://seriot.ch/parsing_json.php
//   https://github.com/nst/JSONTestSuite

//-----------------------------------------------------------------------------
// Implementation-specific behaviour
//-----------------------------------------------------------------------------

namespace i_number_suite
{

void i_number_double_huge_neg_exp()
{
    const long double tolerance = 1e-18;
    const char input[] = "123.456e-789";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123.456e-789");
    TRIAL_PROTOCOL_TEST_CLOSE(reader.value<long double>(),
                              123.456e-789L,
                              tolerance);
}

void i_number_huge_exp()
{
    const char input[] = "0.4e00669999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999969999999006";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "0.4e00669999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999969999999006");
    // Cannot be represented by long double
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<long double>(), std::numeric_limits<long double>::infinity());
}

void i_number_neg_int_huge_exp()
{
    const char input[] = "-1e+9999";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-1e+9999");
    // Cannot be represented by long double
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<long double>(), -std::numeric_limits<long double>::infinity());
}

void i_number_pos_double_huge_exp()
{
    const char input[] = "1.5e+9999";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.5e+9999");
    // Cannot be represented by long double
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<long double>(), std::numeric_limits<long double>::infinity());
}

void i_number_real_neg_overflow()
{
    const char input[] = "-123123e100000";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-123123e100000");
    // Cannot be represented by long double
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<long double>(), -std::numeric_limits<long double>::infinity());
}

void i_number_real_pos_overflow()
{
    const char input[] = "123123e100000";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123123e100000");
    // Cannot be represented by long double
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<long double>(), std::numeric_limits<long double>::infinity());
}

void i_number_too_big_neg_int()
{
    const char input[] = "-123123123123123123123123123123";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-123123123123123123123123123123");
    // Cannot be represented by integers
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<long long int>(),
                                    json::error,
                                    "invalid value");
}

void i_number_too_big_pos_int()
{
    const char input[] = "100000000000000000000";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "100000000000000000000");
    // Cannot be represented by integers
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<unsigned long long int>(),
                                    json::error,
                                    "invalid value");
}

void i_number_very_big_negative_int()
{
    const char input[] = "-237462374673276894279832749832423479823246327846";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-237462374673276894279832749832423479823246327846");
    // Cannot be represented by integers
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(reader.value<long long int>(),
                                    json::error,
                                    "invalid value");
}

void run()
{
    i_number_double_huge_neg_exp();
    i_number_huge_exp();
    i_number_neg_int_huge_exp();
    i_number_pos_double_huge_exp();
    i_number_real_neg_overflow();
    i_number_real_pos_overflow();
    i_number_too_big_neg_int();
    i_number_too_big_pos_int();
    i_number_very_big_negative_int();
}

} // namespace i_number_suite

//-----------------------------------------------------------------------------

namespace i_object_suite
{

void i_object_key_lone_2nd_surrogate()
{
    const char input[] = "{\"\\uDFAA\":0}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\uDFAA\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 0);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
}

void run()
{
    i_object_key_lone_2nd_surrogate();
}

} // namespace i_object_suite

//-----------------------------------------------------------------------------

namespace i_string_suite
{

void i_string_1st_surrogate_but_2nd_missing()
{
    const char input[] = "[\"\\uDADA\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\uDADA\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_1st_valid_surrogate_2nd_invalid()
{
    const char input[] = "[\"\\uD888\\u1234\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\uD888\\u1234\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_UTF_16LE_with_BOM()
{
    const char input[] = "\xFF\xFE\x5B\x00\x22\x00\xE9\x00\x22\x00\x5D\x00";
    core::detail::string_view view(input, sizeof(input)); // Capture nil character
    json::reader reader(view);
    // BOM not supported
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_UTF_8_invalid_sequence()
{
    const char input[] = "[\"\xE6\x91\xA5\xD1\x88\xFA\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_UTF_8_surrogate_U_D800()
{
    const char input[] = "[\"\xED\xA0\x80\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\xED\xA0\x80\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_incomplete_surrogate_and_escape_valid()
{
    const char input[] = "[\"\\uD800\n\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    // Newline is illegal in string
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_incomplete_surrogate_pair()
{
    const char input[] = "[\"\\uDd1ea\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\uDd1ea\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_incomplete_surrogates_escape_valid()
{
    const char input[] = "[\"\\uD800\\uD800\n\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    // Newline is illegal in string
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_invalid_lonely_surrogate()
{
    const char input[] = "[\"\\ud800\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\ud800\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_invalid_surrogate()
{
    const char input[] = "[\"\\ud800abc\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\ud800abc\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_invalid_utf_8()
{
    const char input[] = "[\"\xFF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_inverted_surrogates_U_1D11E()
{
    const char input[] = "[\"\\uDd1e\\uD834\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\uDd1e\\uD834\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_iso_latin_1()
{
    const char input[] = "[\"\xE9\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_lone_second_surrogate()
{
    const char input[] = "[\"\\uDFAA\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\uDFAA\""); // No knowledge of surrogates
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_lone_utf8_continuation_byte()
{
    const char input[] = "[\"\x81\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_not_in_unicode_range()
{
    const char input[] = "[\"\xF4\xBF\xBF\xBF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xF4\xBF\xBF\xBF");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_overlong_sequence_2_bytes()
{
    const char input[] = "[\"\xAF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_overlong_sequence_6_bytes()
{
    const char input[] = "[\"\xFC\x83\xBF\xBF\xBF\xBF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xFC\x83\xBF\xBF\xBF\xBF");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_overlong_sequence_6_bytes_null()
{
    const char input[] = "[\"\xFC\x80\x80\x80\x80\x80\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xFC\x80\x80\x80\x80\x80");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
}

void i_string_truncated_utf_8()
{
    const char input[] = "[\"\xE0\xFF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void i_string_utf16BE_no_BOM()
{
    // UTF-16 input not supported
}

void i_string_utf16LE_no_BOM()
{
    // UTF-16 input not supported
}

void run()
{
    i_string_1st_surrogate_but_2nd_missing();
    i_string_1st_valid_surrogate_2nd_invalid();
    i_string_UTF_16LE_with_BOM();
    i_string_UTF_8_invalid_sequence();
    i_string_UTF_8_surrogate_U_D800();
    i_string_incomplete_surrogate_and_escape_valid();
    i_string_incomplete_surrogate_pair();
    i_string_incomplete_surrogates_escape_valid();
    i_string_invalid_lonely_surrogate();
    i_string_invalid_surrogate();
    i_string_invalid_utf_8();
    i_string_inverted_surrogates_U_1D11E();
    i_string_iso_latin_1();
    i_string_lone_second_surrogate();
    i_string_lone_utf8_continuation_byte();
    i_string_not_in_unicode_range();
    i_string_overlong_sequence_2_bytes();
    i_string_overlong_sequence_6_bytes();
    i_string_overlong_sequence_6_bytes_null();
    i_string_truncated_utf_8();
    i_string_utf16BE_no_BOM();
    i_string_utf16LE_no_BOM();
}

} // namespace i_string_suite

//-----------------------------------------------------------------------------

namespace i_structure_suite
{

void i_structure_500_nested_arrays()
{
    const std::size_t size = 500;

    std::string input(size, '[');
    input += std::string(size, ']');
    json::reader reader(input);

    std::size_t begin_count = 0;
    for (auto i = 0u; i < size; ++i)
    {
        begin_count += (reader.code() == token::code::begin_array);
        reader.next();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(begin_count, size);
    std::size_t end_count = 0;
    for (auto i = 0u; i < size; ++i)
    {
        end_count += (reader.code() == token::code::end_array);
        reader.next();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(end_count, size);
}

void i_structure_UTF_8_BOM_empty_object()
{
    const char input[] = "\xEF\xBB\xBF{}";
    json::reader reader(input);
    // BOM not supported
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    i_structure_500_nested_arrays();
    i_structure_UTF_8_BOM_empty_object();
}

} // namespace i_structure_suite

//-----------------------------------------------------------------------------
// Must fail
//-----------------------------------------------------------------------------

namespace n_array_suite
{

void n_array_1_true_without_comma()
{
    const char input[] = "[1 true]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_a_invalid_utf8()
{
    const char input[] = "[a\xEF\xBF\xBD]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_bad_value()
{
    const char input[] = "[\"x\", truth]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_colon_instead_of_comma()
{
    const char input[] = "[\"\": 1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_colon_after_close()
{
    const char input[] = "[\"\"],";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_array_comma_and_number()
{
    const char input[] = "[,1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_array_double_comma()
{
    const char input[] = "[1,,2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_array_double_extra_comma()
{
    const char input[] = "[\"x\",,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_array_extra_close()
{
    const char input[] = "[\"x\"]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_array);
}

void n_array_extra_colon()
{
    const char input[] = "[\"\",]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_incomplete()
{
    const char input[] = "[\"x\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_incomplete_invalid_value()
{
    const char input[] = "[X";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_inner_array_no_comma()
{
    const char input[] = "[3[4]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 3);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_invalid_utf8()
{
    const char input[] = "[\xEF\xBF\xBD]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_items_separated_by_colon()
{
    const char input[] = "[1:2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_items_separated_by_semicolon()
{
    const char input[] = "[1;2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_just_comma()
{
    const char input[] = "[,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_array_just_minus()
{
    const char input[] = "[-]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_missing_value()
{
    const char input[] = "[   , \"\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_array_newlines_unclosed()
{
    const char input[] = "[\"a\",\n4\n,1,";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 4);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void n_array_number_and_comma()
{
    const char input[] = "[1,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_number_and_several_commas()
{
    const char input[] = "[1,,]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_array_spaces_vertical_tab_formfeed()
{
    const char input[] = "[\"\va\"\f]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    // Vertical tab illegal in string
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_star_inside()
{
    const char input[] = "[*]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_array_unclosed()
{
    const char input[] = "[\"\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_unclosed_trailing_comma()
{
    const char input[] = "[1,";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void n_array_unclosed_with_new_lines()
{
    const char input[] = "[1,\n1\n,1";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_array_unclosed_with_object_inside()
{
    const char input[] = "[{}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void run()
{
    n_array_1_true_without_comma();
    n_array_a_invalid_utf8();
    n_array_bad_value();
    n_array_colon_instead_of_comma();
    n_array_colon_after_close();
    n_array_comma_and_number();
    n_array_double_comma();
    n_array_double_extra_comma();
    n_array_extra_close();
    n_array_extra_colon();
    n_array_incomplete();
    n_array_incomplete_invalid_value();
    n_array_inner_array_no_comma();
    n_array_invalid_utf8();
    n_array_items_separated_by_colon();
    n_array_items_separated_by_semicolon();
    n_array_just_comma();
    n_array_just_minus();
    n_array_missing_value();
    n_array_newlines_unclosed();
    n_array_number_and_comma();
    n_array_number_and_several_commas();
    n_array_spaces_vertical_tab_formfeed();
    n_array_star_inside();
    n_array_unclosed();
    n_array_unclosed_trailing_comma();
    n_array_unclosed_with_new_lines();
    n_array_unclosed_with_object_inside();
}

} // namespace n_array_suite

//-----------------------------------------------------------------------------

namespace n_incomplete_suite
{

void n_incomplete_false()
{
    const char input[] = "[fals]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_incomplete_null()
{
    const char input[] = "[nul]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_incomplete_true()
{
    const char input[] = "[tru]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    n_incomplete_false();
    n_incomplete_null();
    n_incomplete_true();
}
 
} // namespace n_incomplete_suite()

//-----------------------------------------------------------------------------

namespace n_number_suite
{

void n_multidigit_number_then_nil()
{
    const char input[] = "123\x00";
    core::detail::string_view view(input, sizeof(input)); // Capture nil character
    json::reader reader(view);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 123);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_plus_plus()
{
    const char input[] = "[++1234]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_plus_1()
{
    const char input[] = "[+1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_plus_inf()
{
    const char input[] = "[+Inf]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_minus_01()
{
    const char input[] = "[-01]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_value);
}

void n_number_minus_1_dot_0_dot()
{
    const char input[] = "[-1.0.]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), -1.0);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_minus_2_dot()
{
    const char input[] = "[-2.]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_minus_nan()
{
    const char input[] = "[-NaN]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_dot_minus_1()
{
    const char input[] = "[.-1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_dot_2_exp_minus_3()
{
    const char input[] = "[.2e-3]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_0_dot_1_dot_2()
{
    const char input[] = "[0.1.2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), 0.1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_0_dot_3_exp_plus()
{
    const char input[] = "[0.3e+]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_0_dot_3_exp()
{
    const char input[] = "[0.3e]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_0_dot_exp_1()
{
    const char input[] = "[0.e1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_0_capital_exp_plus()
{
    const char input[] = "[0E+]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_0_capital_exp()
{
    const char input[] = "[0E]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_0_exp_plus()
{
    const char input[] = "[0e+]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_0_exp()
{
    const char input[] = "[0e]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_1_dot_0_exp_plus()
{
    const char input[] = "[1.0e+]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_1_dot_0_exp_minus()
{
    const char input[] = "[1.0e-]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_1_dot_0_exp()
{
    const char input[] = "[1.0e]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_1_000_dot_0()
{
    const char input[] = "[1 000.0]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_1_exp_capital_exp_2()
{
    const char input[] = "[1eE2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_2_dot_exp_plus_3()
{
    const char input[] = "[2.e+3]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_2_dot_exp_minus_3()
{
    const char input[] = "[2.e-3]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_2_dot_exp_3()
{
    const char input[] = "[2.e3]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_9_dot_exp_plus()
{
    const char input[] = "[9.e+]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_inf()
{
    const char input[] = "[Inf]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_nan()
{
    const char input[] = "[NaN]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_u_FF11_fullwidth_digit_one()
{
    const char input[] = "[\xEF\xBC\x91]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_expression()
{
    const char input[] = "[1+2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_hex_1_digit()
{
    const char input[] = "[0x1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 0);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_hex_2_digits()
{
    const char input[] = "[0x42]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 0);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_infinity()
{
    const char input[] = "[Infinity]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_invalid_plus_minus()
{
    const char input[] = "[0e+-1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_invalid_negative_real()
{
    const char input[] = "[-123.123foo]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-123.123");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_invalid_utf_8_in_bigger_int()
{
    const char input[] = "[123\xE5]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_invalid_utf_8_in_exponent()
{
    const char input[] = "[1e1\xE5]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1e1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_invalid_utf_8_in_int()
{
    const char input[] = "[1\xE5]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_minus_infinity()
{
    const char input[] = "[-Infinity]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_minus_sign_with_trailing_garbage()
{
    const char input[] = "[-foo]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_minus_space_1()
{
    const char input[] = "[- 1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_neg_int_starting_with_zero()
{
    const char input[] = "[-012]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_value);
}

void n_number_neg_real_without_int_part()
{
    const char input[] = "[-.123]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_neg_with_garbage_at_end()
{
    const char input[] = "[-1x]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_real_garbage_after_exp()
{
    const char input[] = "[1ea]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_real_with_invalid_utf8_after_exp()
{
    const char input[] = "[1e\xE5]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_real_without_fractional_part()
{
    const char input[] = "[1.]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_starting_with_dot()
{
    const char input[] = "[.123]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_number_with_alpha()
{
    const char input[] = "[1.2a-3]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.2");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_with_alpha_char()
{
    const char input[] = "[1.8011670033376514H-308]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1.8011670033376514");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_number_with_leading_zero()
{
    const char input[] = "[012]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_value);
}

void run()
{
    n_multidigit_number_then_nil();

    n_number_plus_plus();
    n_number_plus_1();
    n_number_plus_inf();
    n_number_minus_01();
    n_number_minus_1_dot_0_dot();
    n_number_minus_2_dot();
    n_number_minus_nan();
    n_number_dot_minus_1();
    n_number_dot_2_exp_minus_3();
    n_number_0_dot_1_dot_2();
    n_number_0_dot_3_exp_plus();
    n_number_0_dot_3_exp();
    n_number_0_dot_exp_1();
    n_number_0_capital_exp_plus();
    n_number_0_capital_exp();
    n_number_0_exp_plus();
    n_number_0_exp();
    n_number_1_dot_0_exp_plus();
    n_number_1_dot_0_exp_minus();
    n_number_1_dot_0_exp();
    n_number_1_000_dot_0();
    n_number_1_exp_capital_exp_2();
    n_number_2_dot_exp_plus_3();
    n_number_2_dot_exp_minus_3();
    n_number_2_dot_exp_3();
    n_number_9_dot_exp_plus();
    n_number_inf();
    n_number_nan();
    n_number_u_FF11_fullwidth_digit_one();
    n_number_expression();
    n_number_hex_1_digit();
    n_number_hex_2_digits();
    n_number_infinity();
    n_number_invalid_plus_minus();
    n_number_invalid_negative_real();
    n_number_invalid_utf_8_in_bigger_int();
    n_number_invalid_utf_8_in_exponent();
    n_number_invalid_utf_8_in_int();
    n_number_minus_infinity();
    n_number_minus_sign_with_trailing_garbage();
    n_number_minus_space_1();
    n_number_neg_int_starting_with_zero();
    n_number_neg_real_without_int_part();
    n_number_neg_with_garbage_at_end();
    n_number_real_garbage_after_exp();
    n_number_real_with_invalid_utf8_after_exp();
    n_number_real_without_fractional_part();
    n_number_starting_with_dot();
    n_number_with_alpha();
    n_number_with_alpha_char();
    n_number_with_leading_zero();
}

} // namespace n_number_suite

//-----------------------------------------------------------------------------

namespace n_object_suite
{

void n_object_bad_value()
{
    const char input[] = "{\"x\":truth}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_bracket_key()
{
    const char input[] = "{[:\"x\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_comma_instead_of_colon()
{
    const char input[] = "{\"x\", null}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_double_colon()
{
    const char input[] = "{\"x\"::\"b\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_name_separator);
}

void n_object_emoji()
{
    const char input[] = "{\xF0\x9F\x87\xA8\xF0\x9F\x87\xAD}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_garbage_at_end()
{
    const char input[] = "{\"a\":\"a\" 123}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_object);
}

void n_object_key_with_single_quotes()
{
    const char input[] = "{key: 'value'}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_missing_colon()
{
    const char input[] = "{\"a\" b}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_missing_key()
{
    const char input[] = "{:\"b\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_missing_semicolon()
{
    const char input[] = "{\"a\" \"b\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_missing_value()
{
    const char input[] = "{\"a\":";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void n_object_no_colon()
{
    const char input[] = "{\"a\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    // Should this be code::end instead?
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_non_string_key()
{
    const char input[] = "{1:1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_non_string_key_but_huge_number_instead()
{
    const char input[] = "{9999E9999:1}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_pi_in_key_and_trailing_comma()
{
    const char input[] = "{\"\xB9\":\"0\",}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_repeated_null_null()
{
    const char input[] = "{null:null,null:null}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_several_trailing_commas()
{
    const char input[] = "{\"id\":0,,,,,}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "id");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 0);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_object_single_quote()
{
    const char input[] = "{'a':0}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_trailing_comma()
{
    const char input[] = "{\"id\":0,}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "id");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 0);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_trailing_comment()
{
    const char input[] = "{\"a\":\"b\"}/**/";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_trailing_comment_open()
{
    const char input[] = "{\"a\":\"b\"}/**//";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_trailing_comment_slash_open()
{
    const char input[] = "{\"a\":\"b\"}//";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_trailing_comment_slash_open_incomplete()
{
    const char input[] = "{\"a\":\"b\"}/";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_two_commas_in_a_row()
{
    const char input[] = "{\"a\":\"b\",,\"c\":\"d\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_object_unquoted_key()
{
    const char input[] = "{a:\"b\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_object_unterminated_value()
{
    const char input[] = "{\"a\":\"a";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"a");
}

void n_object_with_single_string()
{
    const char input[] = "{ \"foo\" : \"bar\", \"a\" }";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "foo");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "bar");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_object_with_trailing_garbage()
{
    const char input[] = "{\"a\":\"b\"}#";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    n_object_bad_value();
    n_object_bracket_key();
    n_object_comma_instead_of_colon();
    n_object_double_colon();
    n_object_emoji();
    n_object_garbage_at_end();
    n_object_key_with_single_quotes();
    n_object_missing_colon();
    n_object_missing_key();
    n_object_missing_semicolon();
    n_object_missing_value();
    n_object_no_colon();
    n_object_non_string_key();
    n_object_non_string_key_but_huge_number_instead();
    n_object_pi_in_key_and_trailing_comma();
    n_object_repeated_null_null();
    n_object_several_trailing_commas();
    n_object_single_quote();
    n_object_trailing_comma();
    n_object_trailing_comment();
    n_object_trailing_comment_open();
    n_object_trailing_comment_slash_open();
    n_object_trailing_comment_slash_open_incomplete();
    n_object_two_commas_in_a_row();
    n_object_unquoted_key();
    n_object_unterminated_value();
    n_object_with_single_string();
    n_object_with_trailing_garbage();
}

} // namespace n_object_suite

//-----------------------------------------------------------------------------

namespace n_string_suite
{

void n_string_1_surrogate_then_escape()
{
    const char input[] = "[\"\\uD800\\\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    // ["\uD800\"] is interpreted as an array with an unterminated string
    // because the last quote is escaped.
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_1_surrogate_then_escape_u()
{
    const char input[] = "[\"\\uD800\\u\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_1_surrogate_then_escape_u1()
{
    const char input[] = "[\"\\uD800\\u1\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_1_surrogate_then_escape_u1x()
{
    const char input[] = "[\"\\uD800\\u1x\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_accentuated_char_no_quotes()
{
    const char input[] = "[\xC3\xA9]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_backslash_00()
{
    const char input[] = "[\\\x00]";
    core::detail::string_view view(input, sizeof(input)); // Capture nil character
    json::reader reader(view);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_escape_x()
{
    const char input[] = "[\"\\x00\"]";
    core::detail::string_view view(input, sizeof(input)); // Capture nil character
    json::reader reader(view);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_escaped_backslash_bad()
{
    const char input[] = "[\"\\\\\\\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    // ["\\\"] is interpreted as an array with an unterminated string
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_escaped_ctrl_char_tab()
{
    const char input[] = "[\"\\\t\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_escaped_emoji()
{
    const char input[] = "[\"\\\xF0\x9F\x8C\x80\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_incomplete_escape()
{
    const char input[] = "[\"\\\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    // ["\"] is interpreted as an array with an unterminated string
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_incomplete_escaped_character()
{
    const char input[] = "[\"\\u00A\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_incomplete_surrogate()
{
    const char input[] = "[\"\\uD834\\uDd\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_incomplete_surrogate_escape_invalid()
{
    const char input[] = "[\"\\uD800\\uD800\\x\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_invalid_utf_8_in_escape()
{
    const char input[] = "[\"\\u\xE5\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_invalid_backslash_esc()
{
    const char input[] = "[\"\\a\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_invalid_unicode_escape()
{
    const char input[] = "[\"\\uqqqq\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_invalid_utf_8_after_escape()
{
    const char input[] = "[\"\\\xE5\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_leading_uescaped_thinspace()
{
    const char input[] = "[\\u0020\"asd\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_no_quotes_with_bad_escape()
{
    const char input[] = "[\\n]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_single_doublequote()
{
    const char input[] = "\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_single_quote()
{
    const char input[] = "['single quote']";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_single_string_no_double_quotes()
{
    const char input[] = "abc";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_start_escape_unclosed()
{
    const char input[] = "[\"\\";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_unescaped_crtl_char()
{
    const char input[] = "[\"a\x00\x61\"]";
    core::detail::string_view view(input, sizeof(input)); // Capture nil character
    json::reader reader(view);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_unescaped_newline()
{
    const char input[] = "[\"new\nline\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_unescaped_tab()
{
    const char input[] = "[\"\t\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_unicode_CapitalU()
{
    const char input[] = "\"\\UA66D\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_string_with_trailing_garbage()
{
    const char input[] = "\"\"x";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    n_string_1_surrogate_then_escape();
    n_string_1_surrogate_then_escape_u();
    n_string_1_surrogate_then_escape_u1();
    n_string_1_surrogate_then_escape_u1x();
    n_string_accentuated_char_no_quotes();
    n_string_backslash_00();
    n_string_escape_x();
    n_string_escaped_backslash_bad();
    n_string_escaped_ctrl_char_tab();
    n_string_escaped_emoji();
    n_string_incomplete_escape();
    n_string_incomplete_escaped_character();
    n_string_incomplete_surrogate();
    n_string_incomplete_surrogate_escape_invalid();
    n_string_invalid_utf_8_in_escape();
    n_string_invalid_backslash_esc();
    n_string_invalid_unicode_escape();
    n_string_invalid_utf_8_after_escape();
    n_string_leading_uescaped_thinspace();
    n_string_no_quotes_with_bad_escape();
    n_string_single_quote();
    n_string_single_string_no_double_quotes();
    n_string_start_escape_unclosed();
    n_string_unescaped_crtl_char();
    n_string_unescaped_newline();
    n_string_unescaped_tab();
    n_string_unicode_CapitalU();
}

} // namespace n_string_suite

//-----------------------------------------------------------------------------

namespace n_structure_suite
{

void n_single_space()
{
    const char input[] = " ";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void n_structure_100000_opening_arrays()
{
    const std::size_t size = 100000;

    std::string input(size, '[');
    input += std::string(size, ']');
    json::reader reader(input);

    std::size_t begin_count = 0;
    for (auto i = 0u; i < size; ++i)
    {
        begin_count += (reader.code() == token::code::begin_array);
        reader.next();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(begin_count, size);
    std::size_t end_count = 0;
    for (auto i = 0u; i < size; ++i)
    {
        end_count += (reader.code() == token::code::end_array);
        reader.next();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(end_count, size);
}

void n_structure_U_plus_2060_word_joined()
{
    const char input[] = "[\xE2\x81\xA0]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_angle_bracket_dot()
{
    const char input[] = "<.>";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_angle_bracket_null()
{
    const char input[] = "[<null>]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_array_trailing_garbage()
{
    const char input[] = "[1]x";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_array_with_extra_array_close()
{
    const char input[] = "[1]]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_array);
}

void n_structure_array_with_unclosed_string()
{
    const char input[] = "[\"asd]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_ascii_unicode_identifier()
{
    const char input[] = "a\xC3\xA5";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_capitalized_True()
{
    const char input[] = "[True]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_close_unopened_array()
{
    const char input[] = "1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_array);
}

void n_structure_comma_instead_of_closing_brace()
{
    const char input[] = "{\"x\": true,";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.level(), 1);
}

void n_structure_double_array()
{
    const char input[] = "[][]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_end_array()
{
    const char input[] = "]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_array);
}

void n_structure_incomplete_UTF8_BOM()
{
    const char input[] = "\xEF\xBB{}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_lone_invalid_utf_8()
{
    const char input[] = "\xE5";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_lone_open_bracket()
{
    const char input[] = "[";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void n_structure_no_data()
{
    const char input[] = "";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void n_structure_null_byte_outside_string()
{
    const char input[] = "[\x00]";
    core::detail::string_view view(input, sizeof(input)); // Capture nil character
    json::reader reader(view);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_number_with_trailing_garbage()
{
    const char input[] = "2@";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_object_followed_by_closing_object()
{
    const char input[] = "{}}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unbalanced_end_object);
}

void n_structure_object_unclosed_no_value()
{
    const char input[] = "{\"\":";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void n_structure_object_with_comment()
{
    const char input[] = "{\"a\":/*comment*/\"b\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_object_with_trailing_garbage()
{
    const char input[] = "{\"a\": true} \"x\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_open_array_apostrophe()
{
    const char input[] = "['";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_open_array_comma()
{
    const char input[] = "[,";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_value_separator);
}

void n_structure_open_array_open_object()
{
    const char input[] = "[{";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_structure_open_array_open_string()
{
    const char input[] = "[\"a";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_open_array_string()
{
    const char input[] = "[\"a\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_structure_open_object()
{
    const char input[] = "{";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_structure_open_object_close_array()
{
    const char input[] = "{]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_object);
}

void n_structure_open_object_comma()
{
    const char input[] = "{,";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_open_object_open_array()
{
    const char input[] = "{[";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_structure_open_object_open_string()
{
    const char input[] = "{\"a";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_structure_open_object_string_with_apostrophes()
{
    const char input[] = "{'a'";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_invalid_key);
}

void n_structure_open_open_open()
{
    const char input[] = "[\"\\{[\"\\{[\"\\{[\"\\{";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_single_eacute()
{
    const char input[] = "\xE9";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_single_star()
{
    const char input[] = "*";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_trailing_hash()
{
    const char input[] = "{\"a\":\"b\"}#{}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_uescaped_LF_before_string()
{
    const char input[] = "[\\u000A\"\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_unclosed_array()
{
    const char input[] = "[1";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_array);
}

void n_structure_unclosed_array_partial_null()
{
    const char input[] = "[ false, nul";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::false_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "nul");
}

void n_structure_unclosed_array_unfinished_false()
{
    const char input[] = "[ true, fals";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "fals");
}

void n_structure_unclosed_array_unfinished_true()
{
    const char input[] = "[ false, tru";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::false_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.tail(), "tru");
}

void n_structure_unclosed_object()
{
    const char input[] = "{\"asd\":\"asd\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_expected_end_object);
}

void n_structure_unicode_identifier()
{
    const char input[] = "\xC3\xA5";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_whitespace_U_plus_2060_word_joiner()
{
    const char input[] = "[\xE2\x81\xA0]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void n_structure_whitespace_formfeed()
{
    const char input[] = "[\f]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::error_unexpected_token);
}

void run()
{
    n_single_space();
    n_structure_100000_opening_arrays();
    n_structure_U_plus_2060_word_joined();
    n_structure_angle_bracket_dot();
    n_structure_angle_bracket_null();
    n_structure_array_trailing_garbage();
    n_structure_array_with_extra_array_close();
    n_structure_array_with_unclosed_string();
    n_structure_ascii_unicode_identifier();
    n_structure_capitalized_True();
    n_structure_close_unopened_array();
    n_structure_comma_instead_of_closing_brace();
    n_structure_double_array();
    n_structure_end_array();
    n_structure_incomplete_UTF8_BOM();
    n_structure_lone_invalid_utf_8();
    n_structure_lone_open_bracket();
    n_structure_no_data();
    n_structure_null_byte_outside_string();
    n_structure_number_with_trailing_garbage();
    n_structure_object_followed_by_closing_object();
    n_structure_object_unclosed_no_value();
    n_structure_object_with_comment();
    n_structure_object_with_trailing_garbage();
    n_structure_open_array_apostrophe();
    n_structure_open_array_comma();
    // FIXME: n_structure_open_array_object
    n_structure_open_array_open_object();
    n_structure_open_array_open_string();
    n_structure_open_array_string();
    n_structure_open_object();
    n_structure_open_object_close_array();
    n_structure_open_object_comma();
    n_structure_open_object_open_string();
    n_structure_open_object_string_with_apostrophes();
    n_structure_open_open_open();
    n_structure_single_eacute();
    n_structure_single_star();
    n_structure_trailing_hash();
    n_structure_uescaped_LF_before_string();
    n_structure_unclosed_array();
    n_structure_unclosed_array_partial_null();
    n_structure_unclosed_array_unfinished_false();
    n_structure_unclosed_array_unfinished_true();
    n_structure_unclosed_object();
    n_structure_unicode_identifier();
    n_structure_whitespace_U_plus_2060_word_joiner();
    n_structure_whitespace_formfeed();
}

} // namespace n_structure_suite

//-----------------------------------------------------------------------------
// Must succeed
//-----------------------------------------------------------------------------

namespace y_array_suite
{

void y_array_arraysWithSpaces()
{
    const char input[] = "[[]   ]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_empty_string()
{
    const char input[] = "[\"\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_empty()
{
    const char input[] = "[]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_ending_with_newline()
{
    const char input[] = "[\"a\"]\n";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_false()
{
    const char input[] = "[false]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::false_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_heterogeneous()
{
    const char input[] = "[null, 1, \"1\", {}]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_null()
{
    const char input[] = "[null]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_with_1_and_newline()
{
    const char input[] = "[1\n]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_with_leading_space()
{
    const char input[] = " [1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_with_several_null()
{
    const char input[] = " [1,null,null,null,2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 2);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_array_with_trailing_space()
{
    const char input[] = "[1] ";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    y_array_arraysWithSpaces();
    y_array_empty_string();
    y_array_empty();
    y_array_ending_with_newline();
    y_array_false();
    y_array_heterogeneous();
    y_array_null();
    y_array_with_1_and_newline();
    y_array_with_leading_space();
    y_array_with_several_null();
}

} // namespace y_array_suite

//-----------------------------------------------------------------------------

namespace y_number_suite
{

void y_number()
{
    const char input[] = "[123e65]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123e65");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_0e_plus_1()
{
    const char input[] = "[0e+1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "0e+1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_0e1()
{
    const char input[] = "[0e1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "0e1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_after_space()
{
    const char input[] = "[ 4]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "4");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_double_close_to_zero()
{
    const char input[] = "[-0.000000000000000000000000000000000000000000000000000000000000000000000000000001]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-0.000000000000000000000000000000000000000000000000000000000000000000000000000001");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_int_with_exp()
{
    const char input[] = "[20e1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "20e1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_negative_int()
{
    const char input[] = "[-123]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-123");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_negative_one()
{
    const char input[] = "[-1]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_negative_zero()
{
    const char input[] = "[-0]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-0");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_real_capital_e()
{
    const char input[] = "[1E22]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1E22");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_real_capital_e_neg_exp()
{
    const char input[] = "[1E-2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1E-2");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_real_capital_e_pos_exp()
{
    const char input[] = "[1E+2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1E+2");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_real_exponent()
{
    const char input[] = "[123E45]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123E45");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_real_fraction_exponent()
{
    const char input[] = "[123.456e78]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123.456e78");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_real_neg_exp()
{
    const char input[] = "[1e-2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1e-2");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_real_pos_exp()
{
    const char input[] = "[1e+2]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "1e+2");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_simple_int()
{
    const char input[] = "[123]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_number_simple_real()
{
    const char input[] = "[123.456789]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "123.456789");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    y_number();
    y_number_0e_plus_1();
    y_number_0e1();
    y_number_after_space();
    y_number_double_close_to_zero();
    y_number_int_with_exp();
    // y_number_minus_zero same as y_number_negative_zero
    y_number_negative_int();
    y_number_negative_one();
    y_number_negative_zero();
    y_number_real_capital_e();
    y_number_real_capital_e_neg_exp();
    y_number_real_capital_e_pos_exp();
    y_number_real_exponent();
    y_number_real_fraction_exponent();
    y_number_real_neg_exp();
    y_number_real_pos_exp();
    y_number_simple_int();
    y_number_simple_real();
}

} // namespace y_number_suite

//-----------------------------------------------------------------------------

namespace y_object_suite
{

void y_object()
{
    const char input[] = "{\"asd\":\"sdf\", \"dfg\":\"fgh\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "sdf");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "dfg");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "fgh");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_basic()
{
    const char input[] = "{\"asd\":\"sdf\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "sdf");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_duplicated_key()
{
    const char input[] = "{\"a\":\"b\",\"a\":\"c\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "c");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_duplicated_key_and_value()
{
    const char input[] = "{\"a\":\"b\",\"a\":\"b\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_empty()
{
    const char input[] = "{}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_empty_key()
{
    const char input[] = "{\"\":0}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 0);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_escaped_null_in_key()
{
    const char input[] = "{\"foo\\u0000bar\": 42}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"foo\\u0000bar\"");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 42);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_extreme_numbers()
{
    const char input[] = "{ \"min\": -1.0e+28, \"max\": 1.0e+28 }";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "min");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), -1e+28);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "max");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<double>(), 1e+28);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_long_strings()
{
    const char input[] = "{\"x\":[{\"id\": \"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\"}], \"id\": \"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\"}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "x");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "id");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "id");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_simple()
{
    const char input[] = "{\"a\":[]}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_string_unicode()
{
    const char input[] = "{\"title\":\"\\u041f\\u043e\\u043b\\u0442\\u043e\\u0440\\u0430 \\u0417\\u0435\\u043c\\u043b\\u0435\\u043a\\u043e\\u043f\\u0430\" }";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "title");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\u041f\u043e\u043b\u0442\u043e\u0440\u0430 \u0417\u0435\u043c\u043b\u0435\u043a\u043e\u043f\u0430");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_object_with_newlines()
{
    const char input[] = "{\n\"a\": \"b\"\n}";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "b");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_object);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    y_object();
    y_object_basic();
    y_object_duplicated_key();
    y_object_duplicated_key_and_value();
    y_object_empty();
    y_object_empty_key();
    y_object_escaped_null_in_key();
    y_object_extreme_numbers();
    y_object_long_strings();
    y_object_simple();
    y_object_string_unicode();
    y_object_with_newlines();
}

} // namespace y_object_suite

//-----------------------------------------------------------------------------

namespace y_string_suite
{

void y_string_1_2_3_bytes_UTF_8_sequences()
{
    const char input[] = "[\"\\u0060\\u012a\\u12AB\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\x60\xC4\xAA\xE1\x8A\xAB");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_accepted_surrogate_pair()
{
    const char input[] = "[\"\\uD801\\udc37\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xED\xA0\x81\xED\xB0\xB7");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_accepted_surrogate_pairs()
{
    const char input[] = "[\"\\ud83d\\ude39\\ud83d\\udc8d\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xED\xA0\xBD\xED\xB8\xB9\xED\xA0\xBD\xED\xB2\x8D");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_allowed_escapes()
{
    const char input[] = "[\"\\\"\\\\\\/\\b\\f\\n\\r\\t\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\"\\/\b\f\n\r\t");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_backslash_and_u_escaped_zero()
{
    const char input[] = "[\"\\\\u0000\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\\u0000");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_backslash_doublequotes()
{
    const char input[] = "[\"\\\"\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\"");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_comment()
{
    const char input[] = "[\"a/*b*/c/*d//e\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a/*b*/c/*d//e");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_double_escape_a()
{
    const char input[] = "[\"\\\\a\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\\a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_double_escape_n()
{
    const char input[] = "[\"\\\\n\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\\n");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_escaped_control_character()
{
    const char input[] = "[\"\\u0012\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\x12");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_escaped_noncharacter()
{
    const char input[] = "[\"\\uFFFF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xEF\xBF\xBF");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_in_array()
{
    const char input[] = "[\"asd\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_in_array_with_leading_space()
{
    const char input[] = "[ \"asd\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_last_surrogates_1_and_2()
{
    const char input[] = "[\"\\uDBFF\\uDFFF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xED\xAF\xBF\xED\xBF\xBF");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_nbsp_uescaped()
{
    const char input[] = "[\"new\\u00A0line\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "new\xC2\xA0line");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_nonCharacterInUTF_8_U_plus_10FFFF()
{
    const char input[] = "[\"\xF4\x8F\xBF\xBF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xF4\x8F\xBF\xBF");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_nonCharacterInUTF_8_U_plus_1FFFF()
{
    const char input[] = "[\"\xF0\x9B\xBF\xBF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xF0\x9B\xBF\xBF");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_nonCharacterInUTF_8_U_plus_FFFF()
{
    const char input[] = "[\"\uFFFF\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xEF\xBF\xBF");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_null_escape()
{
    const char input[] = "[\"\\u0000\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "\"\\u0000\"");
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>().size(), 1);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_one_byte_utf_8()
{
    const char input[] = "[\"\\u002c\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\x2c");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_pi()
{
    const char input[] = "[\"\xCF\x80\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xCF\x80");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_simple_ascii()
{
    const char input[] = "[\"asd \"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd ");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_space()
{
    const char input[] = "\" \"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), " ");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_surrogates_U_plus_1D11E_MUSICAL_SYMBOL_G_CLEF()
{
    const char input[] = "[\"\\uD834\\uDd1e\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xED\xA0\xB4\xED\xB4\x9E");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_three_byte_utf_8()
{
    const char input[] = "[\"\\u0821\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xE0\xA0\xA1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_two_byte_utf_8()
{
    const char input[] = "[\"\\u0123\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xC4\xA3");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_u_2028_line_sep()
{
    const char input[] = "[\"\\u2028\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xE2\x80\xA8");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_u_2029_par_sep()
{
    const char input[] = "[\"\\u2029\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xE2\x80\xA9");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_uEscape()
{
    const char input[] = "[\"\\u0061\\u30af\\u30EA\\u30b9\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a\xE3\x82\xAF\xE3\x83\xAA\xE3\x82\xB9");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_uescaped_newline()
{
    const char input[] = "[\"new\\u000Aline\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "new\nline");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unescaped_char_delete()
{
    const char input[] = "[\"\x7F\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\x7F");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode()
{
    const char input[] = "[\"\\uA66D\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xEA\x99\xAD");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicodeEscapedBackslash()
{
    const char input[] = "[\"\\u005C\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\\");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_2()
{
    const char input[] = "[\"\xE2\x8D\x82\xE3\x88\xB4\xE2\x8D\x82\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xE2\x8D\x82\xE3\x88\xB4\xE2\x8D\x82");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_U_plus_10FFFE_nonchar()
{
    const char input[] = "[\"\\uDBFF\\uDFFE\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xED\xAF\xBF\xED\xBF\xBE");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_U_plus_1FFFE_nonchar()
{
    const char input[] = "[\"\\uD83F\\uDFFE\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xED\xA0\xBF\xED\xBF\xBE");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_U_plus_200B_ZERO_WIDTH_SPACE()
{
    const char input[] = "[\"\\u200B\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xE2\x80\x8B");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_U_plus_2064_invisible_plus()
{
    const char input[] = "[\"\\u2064\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xE2\x81\xA4");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_U_plus_FDD0_nonchar()
{
    const char input[] = "[\"\\uFDD0\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xEF\xB7\x90");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_U_plus_FFFE_nonchar()
{
    const char input[] = "[\"\\uFFFE\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xEF\xBF\xBE");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_unicode_escaped_double_quote()
{
    const char input[] = "[\"\\u0022\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\"");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_utf8()
{
    const char input[] = "[\"\xE2\x82\xAC\xF0\x9D\x84\x9E\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "\xE2\x82\xAC\xF0\x9D\x84\x9E");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_string_with_del_character()
{
    const char input[] = "[\"a\x7F\x61\"]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a\x7F\x61");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    y_string_1_2_3_bytes_UTF_8_sequences();
    y_string_accepted_surrogate_pair();
    y_string_accepted_surrogate_pairs();
    y_string_allowed_escapes();
    y_string_backslash_and_u_escaped_zero();
    y_string_backslash_doublequotes();
    y_string_comment();
    y_string_double_escape_a();
    y_string_double_escape_n();
    y_string_escaped_control_character();
    y_string_escaped_noncharacter();
    y_string_in_array();
    y_string_in_array_with_leading_space();
    y_string_last_surrogates_1_and_2();
    y_string_nbsp_uescaped();
    y_string_nonCharacterInUTF_8_U_plus_10FFFF();
    y_string_nonCharacterInUTF_8_U_plus_1FFFF();
    y_string_nonCharacterInUTF_8_U_plus_FFFF();
    y_string_null_escape();
    y_string_one_byte_utf_8();
    y_string_pi();
    y_string_simple_ascii();
    y_string_space();
    y_string_surrogates_U_plus_1D11E_MUSICAL_SYMBOL_G_CLEF();
    y_string_three_byte_utf_8();
    y_string_two_byte_utf_8();
    y_string_u_2028_line_sep();
    y_string_u_2029_par_sep();
    y_string_uEscape();
    y_string_uescaped_newline();
    y_string_unescaped_char_delete();
    y_string_unicode();
    y_string_unicodeEscapedBackslash();
    y_string_unicode_2();
    y_string_unicode_U_plus_10FFFE_nonchar();
    y_string_unicode_U_plus_1FFFE_nonchar();
    y_string_unicode_U_plus_200B_ZERO_WIDTH_SPACE();
    y_string_unicode_U_plus_2064_invisible_plus();
    y_string_unicode_U_plus_FDD0_nonchar();
    y_string_unicode_U_plus_FFFE_nonchar();
    y_string_unicode_escaped_double_quote();
    y_string_utf8();
    y_string_with_del_character();
}

} // namespace y_string_suite

//-----------------------------------------------------------------------------

namespace y_structure_suite
{

void y_structure_lonely_false()
{
    const char input[] = "false";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::false_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_lonely_int()
{
    const char input[] = "42";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::integer);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<int>(), 42);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_lonely_negative_real()
{
    const char input[] = "-0.1";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::real);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.literal(), "-0.1");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_lonely_null()
{
    const char input[] = "null";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::null);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_lonely_string()
{
    const char input[] = "\"asd\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "asd");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_lonely_true()
{
    const char input[] = "true";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_string_empty()
{
    const char input[] = "\"\"";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_trailing_newline()
{
    const char input[] = "[\"a\"]\n";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::string);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.value<std::string>(), "a");
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_true_in_array()
{
    const char input[] = "[true]";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::true_value);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void y_structure_whitespace_array()
{
    const char input[] = " [] ";
    json::reader reader(input);
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::begin_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end_array);
    reader.next();
    TRIAL_PROTOCOL_TEST_EQUAL(reader.code(), token::code::end);
}

void run()
{
    y_structure_lonely_false();
    y_structure_lonely_int();
    y_structure_lonely_negative_real();
    y_structure_lonely_null();
    y_structure_lonely_string();
    y_structure_lonely_true();
    y_structure_string_empty();
    y_structure_trailing_newline();
    y_structure_true_in_array();
    y_structure_whitespace_array();
}

} // namespace y_structure_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    i_number_suite::run();
    i_object_suite::run();
    i_string_suite::run();
    i_structure_suite::run();

    n_array_suite::run();
    n_incomplete_suite::run();
    n_number_suite::run();
    n_object_suite::run();
    n_string_suite::run();
    n_structure_suite::run();

    y_array_suite::run();
    y_number_suite::run();
    y_object_suite::run();
    y_string_suite::run();
    y_structure_suite::run();

    return boost::report_errors();
}
