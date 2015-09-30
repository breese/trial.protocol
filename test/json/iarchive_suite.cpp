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

#include <sstream>
#include <trial/protocol/json/serialization/iarchive.hpp>
#include <trial/protocol/json/serialization/pair.hpp>
#include <trial/protocol/json/serialization/string.hpp>
#include <trial/protocol/json/serialization/vector.hpp>
#include <trial/protocol/json/serialization/set.hpp>
#include <trial/protocol/json/serialization/map.hpp>
#include <trial/protocol/json/serialization/optional.hpp>
#include "is_system_error.hpp"

using namespace trial::protocol;

BOOST_AUTO_TEST_SUITE(json_iarchive_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_false)
{
    const char input[] = "false";
    json::iarchive in(input);
    bool value = true;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, false);
}

BOOST_AUTO_TEST_CASE(fail_false)
{
    const char input[] = "fals";
    json::iarchive in(input);
    bool value = true;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::invalid_value));
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const char input[] = "true";
    json::iarchive in(input);
    bool value = false;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, true);
}

BOOST_AUTO_TEST_CASE(fail_true)
{
    const char input[] = "tru";
    json::iarchive in(input);
    bool value = false;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::invalid_value));
}

//-----------------------------------------------------------------------------
// Integer
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_short_zero)
{
    const char input[] = "0";
    json::iarchive in(input);
    short value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0);
}

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    const char input[] = "0";
    json::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0);
}

BOOST_AUTO_TEST_CASE(test_long_zero)
{
    const char input[] = "0";
    json::iarchive in(input);
    long value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0);
}

BOOST_AUTO_TEST_CASE(test_intmax_zero)
{
    const char input[] = "0";
    json::iarchive in(input);
    intmax_t value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0);
}

BOOST_AUTO_TEST_CASE(test_unsigned_zero)
{
    const char input[] = "0";
    json::iarchive in(input);
    unsigned int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0U);
}

BOOST_AUTO_TEST_CASE(test_int_hundred)
{
    const char input[] = "100";
    json::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 100);
}

BOOST_AUTO_TEST_CASE(test_int_minus_hundred)
{
    const char input[] = "-100";
    json::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, -100);
}

BOOST_AUTO_TEST_CASE(fail_unsigned_minus_hundred)
{
    const char input[] = "-100";
    json::iarchive in(input);
    unsigned int value = 99;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::invalid_value));
}

//-----------------------------------------------------------------------------
// Float
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float_half)
{
    const char input[] = "0.5";
    json::iarchive in(input);
    float value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0.5);
}

BOOST_AUTO_TEST_CASE(test_double_half)
{
    const char input[] = "0.5";
    json::iarchive in(input);
    double value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0.5);
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    const char input[] = "\"\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, "");
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    const char input[] = "\"alpha\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, "alpha");
}

BOOST_AUTO_TEST_CASE(test_string_escape_quote)
{
    const char input[] = "\"\\\"\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, "\"");
}

BOOST_AUTO_TEST_CASE(test_string_escape_reverse_solidus)
{
    const char input[] = "\"\\\\\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, "\\");
}

BOOST_AUTO_TEST_CASE(test_string_escape_solidus)
{
    const char input[] = "\"\\/\"";
    json::iarchive in(input);
    std::string value("EMPTY");
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, "/");
}

//-----------------------------------------------------------------------------
// Pair
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_pair)
{
    const char input[] = "[42,true]";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.first, 42);
    BOOST_REQUIRE_EQUAL(value.second, true);
}

BOOST_AUTO_TEST_CASE(test_pair_object)
{
    const char input[] = "[\"alpha\",true]";
    json::iarchive in(input);
    std::pair<std::string, bool> value("alpha", true);
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.first, "alpha");
    BOOST_REQUIRE_EQUAL(value.second, true);
}

BOOST_AUTO_TEST_CASE(fail_pair_first)
{
    const char input[] = "[42]";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_pair_first_comma)
{
    const char input[] = "[42,]";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_pair_missing_end)
{
    const char input[] = "[42,true";
    json::iarchive in(input);
    std::pair<int, bool> value(42, true);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::expected_end_array));
}

//-----------------------------------------------------------------------------
// Optional
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_optional)
{
    const char input[] = "\"alpha\"";
    json::iarchive in(input);
    boost::optional<std::string> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE(value);
    BOOST_REQUIRE_EQUAL(*value, "alpha");
}

BOOST_AUTO_TEST_CASE(test_optional_null)
{
    const char input[] = "null";
    json::iarchive in(input);
    boost::optional<std::string> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE(!value);
}

BOOST_AUTO_TEST_CASE(fail_optional_wrong_type)
{
    const char input[] = "true";
    json::iarchive in(input);
    boost::optional<std::string> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::invalid_value));
}

//-----------------------------------------------------------------------------
// Container
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_vector_bool_empty)
{
    const char input[] = "[]";
    json::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 0U);
}

BOOST_AUTO_TEST_CASE(test_vector_bool_one)
{
    const char input[] = "[true]";
    json::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 1U);
    BOOST_REQUIRE_EQUAL(value[0], true);
}

BOOST_AUTO_TEST_CASE(test_vector_bool_two)
{
    const char input[] = "[true,false]";
    json::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 2U);
    BOOST_REQUIRE_EQUAL(value[0], true);
    BOOST_REQUIRE_EQUAL(value[1], false);
}

BOOST_AUTO_TEST_CASE(fail_vector_mixed)
{
    // Although this is legal JSON, we cannot deserialize it into a vector<bool>
    const char input[] = "[true,0]";
    json::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_vector_missing_end)
{
    const char input[] = "[true";
    json::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::expected_end_array));
}

BOOST_AUTO_TEST_CASE(fail_vector_missing_begin)
{
    const char input[] = "true]";
    json::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_vector_mismatching_end)
{
    const char input[] = "[true}";
    json::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::expected_end_array));
}

BOOST_AUTO_TEST_CASE(test_intmap_bool_empty)
{
    const char input[] = "[]";
    json::iarchive in(input);
    std::map<boost::int64_t, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 0U);
}

BOOST_AUTO_TEST_CASE(test_intmap_bool_one)
{
    const char input[] = "[[2,true]]";
    json::iarchive in(input);
    std::map<boost::int64_t, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 1U);
    BOOST_REQUIRE_EQUAL(value[2], true);
}

BOOST_AUTO_TEST_CASE(test_intmap_bool_two)
{
    const char input[] = "[[2,true],[4,false]]";
    json::iarchive in(input);
    std::map<boost::int64_t, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 2U);
    BOOST_REQUIRE_EQUAL(value[2], true);
    BOOST_REQUIRE_EQUAL(value[4], false);
}

BOOST_AUTO_TEST_CASE(test_map_bool_empty)
{
    const char input[] = "{}";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 0U);
}

BOOST_AUTO_TEST_CASE(test_map_bool_one)
{
    const char input[] = "{\"alpha\":true}";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 1U);
    BOOST_REQUIRE_EQUAL(value["alpha"], true);
}

BOOST_AUTO_TEST_CASE(test_map_bool_two)
{
    const char input[] = "{\"alpha\":true,\"bravo\":false}";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 2U);
    BOOST_REQUIRE_EQUAL(value["alpha"], true);
    BOOST_REQUIRE_EQUAL(value["bravo"], false);
}

BOOST_AUTO_TEST_CASE(fail_map_bool_missing_end)
{
    const char input[] = "{\"alpha\":true";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::expected_end_object));
}

BOOST_AUTO_TEST_CASE(fail_map_bool_mismatching_end)
{
    const char input[] = "{\"alpha\":true]";
    json::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            json::error,
                            test::is_system_error(json::expected_end_object));
}

BOOST_AUTO_TEST_SUITE_END()
