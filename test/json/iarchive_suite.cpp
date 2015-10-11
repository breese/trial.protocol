///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <trial/protocol/json/serialization.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

using namespace trial::protocol;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_false()
{
    const char input[] = "false";
    json::iarchive in(input);
    bool value = true;
    TRIAL_PROTOCOL_TEST_EQUAL(in.code(), json::token::code::false_value);
    TRIAL_PROTOCOL_TEST_EQUAL(in.symbol(), json::token::symbol::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(in.category(), json::token::category::data);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, false);
}

void fail_false()
{
    const char input[] = "fals";
    json::iarchive in(input);
    bool value = true;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "invalid value");
}

void test_true()
{
    const char input[] = "true";
    json::iarchive in(input);
    bool value = false;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, true);
}

void fail_true()
{
    const char input[] = "tru";
    json::iarchive in(input);
    bool value = false;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "invalid value");
}

void run()
{
    test_false();
    fail_false();
    test_true();
    fail_true();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

namespace integer_suite
{

void test_short_zero()
{
    const char input[] = "0";
    json::iarchive in(input);
    short value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0);
}

void test_int_zero()
{
    const char input[] = "0";
    json::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0);
}

void test_long_zero()
{
    const char input[] = "0";
    json::iarchive in(input);
    long value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0);
}

void test_intmax_zero()
{
    const char input[] = "0";
    json::iarchive in(input);
    intmax_t value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0);
}

void test_unsigned_zero()
{
    const char input[] = "0";
    json::iarchive in(input);
    unsigned int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0U);
}

void test_int_hundred()
{
    const char input[] = "100";
    json::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 100);
}

void test_int_minus_hundred()
{
    const char input[] = "-100";
    json::iarchive in(input);
    int value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, -100);
}

void fail_unsigned_minus_hundred()
{
    const char input[] = "-100";
    json::iarchive in(input);
    unsigned int value = 99;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "invalid value");
}

void run()
{
    test_short_zero();
    test_int_zero();
    test_long_zero();
    test_intmax_zero();
    test_unsigned_zero();
    test_int_hundred();
    test_int_minus_hundred();
    fail_unsigned_minus_hundred();
}

} // namespace integer_suite

//-----------------------------------------------------------------------------
// Float
//-----------------------------------------------------------------------------

namespace floating_suite
{

void test_float_half()
{
    const char input[] = "0.5";
    json::iarchive in(input);
    float value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0.5);
}

void test_double_half()
{
    const char input[] = "0.5";
    json::iarchive in(input);
    double value = 99;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, 0.5);
}

void run()
{
    test_float_half();
    test_double_half();
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
    json::iarchive in(input);
    std::string value("EMPTY");
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, "");
}

void test_alpha()
{
    const char input[] = "\"alpha\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, "alpha");
}

void test_escape_quote()
{
    const char input[] = "\"\\\"\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, "\"");
}

void test_escape_reverse_solidus()
{
    const char input[] = "\"\\\\\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, "\\");
}

void test_escape_solidus()
{
    const char input[] = "\"\\/\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value, "/");
}

void run()
{
    test_empty();
    test_alpha();
    test_escape_quote();
    test_escape_reverse_solidus();
    test_escape_solidus();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Pair
//-----------------------------------------------------------------------------

namespace pair_suite
{

void test_int_bool()
{
    const char input[] = "[42,true]";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.first, 42);
    TRIAL_PROTOCOL_TEST_EQUAL(value.second, true);
}

void test_string_bool()
{
    const char input[] = "[\"alpha\",true]";
    json::iarchive in(input);
    std::pair<std::string, bool> value("alpha", true);
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.first, "alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(value.second, true);
}

void fail_first()
{
    const char input[] = "[42]";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "invalid value");
}

void fail_first_comma()
{
    const char input[] = "[42,]";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "unexpected token");
}

void fail_missing_end()
{
    const char input[] = "[42,true";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "expected end array bracket");
}

void run()
{
    test_int_bool();
    test_string_bool();
    fail_first();
    fail_first_comma();
    fail_missing_end();
}

} // namespace pair_suite

//-----------------------------------------------------------------------------
// Optional
//-----------------------------------------------------------------------------

namespace optional_suite
{

void test_value()
{
    const char input[] = "\"alpha\"";
    json::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(value);
    TRIAL_PROTOCOL_TEST_EQUAL(*value, "alpha");
}

void test_null()
{
    const char input[] = "null";
    json::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST(!value);
}

void fail_wrong_type()
{
    const char input[] = "true";
    json::iarchive in(input);
    boost::optional<std::string> value;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "invalid value");
}

void run()
{
    test_value();
    test_null();
    fail_wrong_type();
}

} // namespace optional_suite

//-----------------------------------------------------------------------------
// Vector
//-----------------------------------------------------------------------------

namespace vector_suite
{

void test_bool_empty()
{
    const char input[] = "[]";
    json::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0U);
}

void test_bool_one()
{
    const char input[] = "[true]";
    json::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1U);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], true);
}

void test_bool_two()
{
    const char input[] = "[true,false]";
    json::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2U);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value[1], false);
}

void test_nested()
{
    const char input[] = "[[true]]";
    json::iarchive in(input);
    std::vector< std::vector<bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1U);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0].size(), 1U);
    TRIAL_PROTOCOL_TEST_EQUAL(value[0][0], true);
}

void fail_mixed()
{
    // Although this is legal JSON, we cannot deserialize it into a vector<bool>
    const char input[] = "[true,0]";
    json::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "invalid value");
}

void fail_missing_end()
{
    const char input[] = "[true";
    json::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "expected end array bracket");
}

void fail_missing_begin()
{
    const char input[] = "true]";
    json::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "unexpected token");
}

void fail_mismatching_end()
{
    const char input[] = "[true}";
    json::iarchive in(input);
    std::vector<bool> value;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "expected end array bracket");
}

void run()
{
    test_bool_empty();
    test_bool_one();
    test_bool_two();
    test_nested();
    fail_mixed();
    fail_missing_end();
    fail_missing_begin();
    fail_mismatching_end();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// Map
//-----------------------------------------------------------------------------

namespace map_suite
{

void test_int_bool_empty()
{
    const char input[] = "[]";
    json::iarchive in(input);
    std::map<boost::int64_t, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0U);
}

void test_int_bool_one()
{
    const char input[] = "[[2,true]]";
    json::iarchive in(input);
    std::map<boost::int64_t, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1U);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], true);
}

void test_int_bool_two()
{
    const char input[] = "[[2,true],[4,false]]";
    json::iarchive in(input);
    std::map<boost::int64_t, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2U);
    TRIAL_PROTOCOL_TEST_EQUAL(value[2], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value[4], false);
}

void test_string_bool_empty()
{
    const char input[] = "{}";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 0U);
}

void test_string_bool_one()
{
    const char input[] = "{\"alpha\":true}";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1U);
    TRIAL_PROTOCOL_TEST_EQUAL(value["alpha"], true);
}

void test_string_bool_two()
{
    const char input[] = "{\"alpha\":true,\"bravo\":false}";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 2U);
    TRIAL_PROTOCOL_TEST_EQUAL(value["alpha"], true);
    TRIAL_PROTOCOL_TEST_EQUAL(value["bravo"], false);
}

void test_string_nested()
{
    const char input[] = "{\"alpha\":{\"bravo\":true}}";
    json::iarchive in(input);
    std::map< std::string, std::map< std::string, bool> > value;
    TRIAL_PROTOCOL_TEST_NO_THROW(in >> value);
    TRIAL_PROTOCOL_TEST_EQUAL(value.size(), 1U);
    TRIAL_PROTOCOL_TEST_EQUAL(value["alpha"].size(), 1U);
    TRIAL_PROTOCOL_TEST_EQUAL(value["alpha"]["bravo"], true);
}

void fail_string_bool_missing_end()
{
    const char input[] = "{\"alpha\":true";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "expected end object bracket");
}

void fail_string_bool_mismatching_end()
{
    const char input[] = "{\"alpha\":true]";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    TRIAL_PROTOCOL_TEST_THROW(in >> value,
                              json::error,
                              "expected end object bracket");
}

void run()
{
    test_int_bool_empty();
    test_int_bool_one();
    test_int_bool_two();
    test_string_bool_empty();
    test_string_bool_one();
    test_string_bool_two();
    test_string_nested();
    fail_string_bool_missing_end();
    fail_string_bool_mismatching_end();
}

} // namespace map_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    integer_suite::run();
    floating_suite::run();
    string_suite::run();
    pair_suite::run();
    optional_suite::run();
    vector_suite::run();
    map_suite::run();

    return boost::report_errors();
}
