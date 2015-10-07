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

#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/transenc/serialization/iarchive.hpp>
#include <trial/protocol/transenc/serialization/pair.hpp>
#include <trial/protocol/transenc/serialization/string.hpp>
#include <trial/protocol/transenc/serialization/optional.hpp>
#include <trial/protocol/transenc/serialization/vector.hpp>
#include <trial/protocol/transenc/serialization/set.hpp>
#include <trial/protocol/transenc/serialization/map.hpp>
#include "is_system_error.hpp"

namespace test = trial::protocol::test;
namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::reader::value_type value_type;

BOOST_AUTO_TEST_SUITE(transenc_iarchive_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_false)
{
    const value_type input[] = { token::code::false_value };
    format::iarchive in(input);
    bool value = true;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, false);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    const value_type input[] = { token::code::true_value };
    format::iarchive in(input);
    bool value = false;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, true);
}

BOOST_AUTO_TEST_CASE(test_bool_junk)
{
    const value_type input[] = { token::code::null }; // Null cannot be deserialized as bool (only as optional<bool>)
    format::iarchive in(input);
    bool value = true;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

//-----------------------------------------------------------------------------
// Integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    const value_type input[] = { 0x00 };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 0);
}

BOOST_AUTO_TEST_CASE(test_int_one)
{
    const value_type input[] = { 0x01 };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 1);
}

BOOST_AUTO_TEST_CASE(test_int_minus_one)
{
    const value_type input[] = { 0xFF };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, -1);
}

BOOST_AUTO_TEST_CASE(test_int_one_int8)
{
    const value_type input[] = { token::code::int8, 0x01 };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 1);
}

BOOST_AUTO_TEST_CASE(test_int_minus_one_int8)
{
    const value_type input[] = { token::code::int8, 0xFF };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, -1);
}

BOOST_AUTO_TEST_CASE(test_int_one_int16)
{
    const value_type input[] = { token::code::int16, 0x01, 0x00 };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 1);
}

BOOST_AUTO_TEST_CASE(test_int_minus_one_int16)
{
    const value_type input[] = { token::code::int16, 0xFF, 0xFF };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, -1);
}

BOOST_AUTO_TEST_CASE(test_int_one_int32)
{
    const value_type input[] = { token::code::int32, 0x01, 0x00, 0x00, 0x00 };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 1);
}

BOOST_AUTO_TEST_CASE(test_int_minus_one_int32)
{
    const value_type input[] = { token::code::int32, 0xFF, 0xFF, 0xFF, 0xFF };
    format::iarchive in(input);
    int value = 99;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, -1);
}

//-----------------------------------------------------------------------------
// Floating-point
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float_one)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::iarchive in(input);
    token::float32::type value = 0.0f;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 1.0f);
}

BOOST_AUTO_TEST_CASE(test_double_one)
{
    const value_type input[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    format::iarchive in(input);
    token::float64::type value = 0.0;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 1.0);
}

BOOST_AUTO_TEST_CASE(test_double_one_float)
{
    const value_type input[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    format::iarchive in(input);
    token::float64::type value = 0.0;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, 1.0);
}

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    const value_type input[] = { token::code::string8, 0x00 };
    format::iarchive in(input);
    std::string value("replace");
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, "");
}

BOOST_AUTO_TEST_CASE(test_string_alpha)
{
    const value_type input[] = { token::code::string8, 0x05, 'a', 'l', 'p', 'h', 'a' };
    format::iarchive in(input);
    std::string value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value, "alpha");
}

//-----------------------------------------------------------------------------
// Pair
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_pair)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value("replace", false);
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.first, "A");
    BOOST_REQUIRE_EQUAL(value.second, true);
}

BOOST_AUTO_TEST_CASE(test_pair_too_short)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

BOOST_AUTO_TEST_CASE(test_pair_too_long)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::true_value,
                                 token::code::false_value,
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(test_pair_missing_end)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A',
                                 token::code::true_value };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(test_pair_missing_end_2)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x01, 'A' };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

BOOST_AUTO_TEST_CASE(test_pair_missing_end_3)
{
    const value_type input[] = { token::code::begin_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(test_pair_missing_begin)
{
    const value_type input[] = { token::code::string8, 0x01, 'A',
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    std::pair<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

//-----------------------------------------------------------------------------
// Optional
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_optional)
{
    const value_type input[] = { token::code::string8, 0x01, 'A' };
    format::iarchive in(input);
    boost::optional<std::string> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE(value);
    BOOST_REQUIRE_EQUAL(*value, "A");
}

BOOST_AUTO_TEST_CASE(test_optional_null)
{
    const value_type input[] = { token::code::null };
    format::iarchive in(input);
    boost::optional<std::string> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE(!value);
}

BOOST_AUTO_TEST_CASE(test_optional_null_value)
{
    const value_type input[] = { token::code::null,
                                 token::code::true_value };
    format::iarchive in(input);
    boost::optional<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE(!value);
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE(value);
    BOOST_REQUIRE_EQUAL(*value, true);
}

BOOST_AUTO_TEST_CASE(fail_optional_wrong_type)
{
    const value_type input[] = { token::code::true_value };
    format::iarchive in(input);
    boost::optional<std::string> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

//-----------------------------------------------------------------------------
// Vector
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_vector_bool_empty)
{
    const value_type input[] = { token::code::begin_array,
                                 0x00,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_vector_bool_one)
{
    const value_type input[] = { token::code::begin_array,
                                 0x01,
                                 token::code::true_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 1);
    BOOST_REQUIRE_EQUAL(value[0], true);
}

BOOST_AUTO_TEST_CASE(test_vector_bool_two)
{
    const value_type input[] = { token::code::begin_array,
                                 0x02,
                                 token::code::true_value,
                                 token::code::false_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 2);
    BOOST_REQUIRE_EQUAL(value[0], true);
    BOOST_REQUIRE_EQUAL(value[1], false);
}

BOOST_AUTO_TEST_CASE(test_vector_bool_two_uncounted)
{
    const value_type input[] = { token::code::begin_array,
                                 0x82,
                                 token::code::true_value,
                                 token::code::false_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 2);
    BOOST_REQUIRE_EQUAL(value[0], true);
    BOOST_REQUIRE_EQUAL(value[1], false);
}

BOOST_AUTO_TEST_CASE(fail_vector_unexpected_float)
{
    // FIXME: No exception because of implicit conversion from float to int
    const value_type input[] = { token::code::begin_array,
                                 token::code::float32, 0x00, 0x00, 0x00, 0x00,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_vector_unexpected_begin)
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::begin_array,
                                 0x00,
                                 token::code::end_array,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_vector_mixed)
{
    const value_type input[] = { token::code::begin_array,
                                 0x02,
                                 token::code::true_value,
                                 0x00,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

BOOST_AUTO_TEST_CASE(fail_vector_missing_end)
{
    const value_type input[] = { token::code::begin_array,
                                 0x01,
                                 token::code::true_value };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

BOOST_AUTO_TEST_CASE(fail_vector_missing_begin)
{
    const value_type input[] = { 0x01,
                                 token::code::true_value,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_vector_missing_count)
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::end_array };
    format::iarchive in(input);
    std::vector<bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

//-----------------------------------------------------------------------------
// Set
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_set_int_empty)
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_set_int_one)
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null,
                                 0x11,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 1);
    BOOST_REQUIRE_EQUAL(value.count(0x11), 1);
}

BOOST_AUTO_TEST_CASE(test_set_int_two)
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null,
                                 0x11,
                                 0x22,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 2);
    BOOST_REQUIRE_EQUAL(value.count(0x11), 1);
    BOOST_REQUIRE_EQUAL(value.count(0x22), 1);
}

BOOST_AUTO_TEST_CASE(fail_set_missing_begin)
{
    const value_type input[] = { token::code::null,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_set_missing_end)
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::null };
    format::iarchive in(input);
    std::set<int> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_set_missing_count)
{
    const value_type input[] = { token::code::begin_array,
                                 token::code::end_array };
    format::iarchive in(input);
    std::set<int> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

//-----------------------------------------------------------------------------
// Map
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_map_bool_empty)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 0x00,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_map_bool_empty_null)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_map_bool_one)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 1);
    BOOST_REQUIRE_EQUAL(value["A"], true);
}

BOOST_AUTO_TEST_CASE(test_map_bool_two)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x42,
                                 token::code::false_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.size(), 2);
    BOOST_REQUIRE_EQUAL(value["A"], true);
    BOOST_REQUIRE_EQUAL(value["B"], false);
}

BOOST_AUTO_TEST_CASE(fail_map_missing_end)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_map_missing_begin)
{
    const value_type input[] = { token::code::null,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_map_missing_count)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_map_missing_pair_end)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_map_missing_pair_second)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41 };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

BOOST_AUTO_TEST_CASE(fail_map_missing_pair_first)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_map_key_unexpected_int)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 0x00,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_map_key_unexpected_null)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::null,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_map_value_unexpected_int)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 0x00,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

BOOST_AUTO_TEST_CASE(fail_map_value_unexpected_null)
{
    const value_type input[] = { token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::null,
                                 token::code::end_record,
                                 token::code::end_assoc_array };
    format::iarchive in(input);
    std::map<std::string, bool> value;
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::incompatible_type));
}

//-----------------------------------------------------------------------------
// Struct
//-----------------------------------------------------------------------------

struct person
{
    person(const std::string& name, int age)
        : name(name),
          age(age)
    {}

    template<typename T>
    void serialize(T& archive, const unsigned int)
    {
        archive & name;
        archive & age;
    }

    std::string name;
    int age;
};

BOOST_AUTO_TEST_CASE(test_struct_person)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.name, "ABC");
    BOOST_REQUIRE_EQUAL(value.age, 127);
}

BOOST_AUTO_TEST_CASE(fail_struct_person_missing_begin)
{
    const value_type input[] = { token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_struct_person_missing_end)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00 };
    format::iarchive in(input);
    person value("", 99);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::unexpected_token));
}

BOOST_AUTO_TEST_CASE(fail_struct_person_missing_second)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43 };
    format::iarchive in(input);
    person value("", 99);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_struct_person_missing_first)
{
    const value_type input[] = { token::code::begin_record };
    format::iarchive in(input);
    person value("", 99);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_struct_person_invalid_second)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

BOOST_AUTO_TEST_CASE(fail_struct_person_invalid_first)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::true_value,
                                 token::code::end_record };
    format::iarchive in(input);
    person value("", 99);
    BOOST_REQUIRE_EXCEPTION(in >> value,
                            format::error,
                            test::is_system_error(format::invalid_value));
}

//-----------------------------------------------------------------------------
// Split struct
//-----------------------------------------------------------------------------

struct split_person
{
    split_person(const std::string& name, int age)
        : name(name),
          age(age)
    {}

    template<typename T>
    void load(T& archive, const unsigned int)
    {
        archive >> name;
        archive >> age;
    }

    template<typename T>
    void save(T& archive, const unsigned int) const
    {
        archive << name;
        archive << age;
    }

    std::string name;
    int age;

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

BOOST_AUTO_TEST_CASE(test_struct_split_person)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::string8, 0x03, 0x41, 0x42, 0x43,
                                 token::code::int16, 0x7F, 0x00,
                                 token::code::end_record };
    format::iarchive in(input);
    split_person value("", 99);
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.name, "ABC");
    BOOST_REQUIRE_EQUAL(value.age, 127);
}

//-----------------------------------------------------------------------------
// Container struct
//-----------------------------------------------------------------------------

template <typename Type>
struct type_struct
{
    template<typename T>
    void serialize(T& archive, const unsigned int)
    {
        archive & data;
    }

    Type data;
};

BOOST_AUTO_TEST_CASE(test_struct_vector_empty)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::vector<bool> > value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.data.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_struct_vector_one)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 token::code::true_value,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::vector<bool> > value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.data.size(), 1);
    BOOST_REQUIRE_EQUAL(value.data[0], true);
}

BOOST_AUTO_TEST_CASE(test_struct_set_empty)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::set<int> > value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.data.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_struct_set_one)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_array,
                                 token::code::null,
                                 0x12,
                                 token::code::end_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::set<int> > value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.data.size(), 1);
    BOOST_REQUIRE_EQUAL(value.data.count(0x12), 1);
}

BOOST_AUTO_TEST_CASE(test_struct_map_empty)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::end_assoc_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::map<std::string, bool> > value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.data.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_struct_map_one)
{
    const value_type input[] = { token::code::begin_record,
                                 token::code::begin_assoc_array,
                                 token::code::null,
                                 token::code::begin_record,
                                 token::code::string8, 0x01, 0x41,
                                 token::code::true_value,
                                 token::code::end_record,
                                 token::code::end_assoc_array,
                                 token::code::end_record };
    format::iarchive in(input);
    type_struct< std::map<std::string, bool> > value;
    BOOST_REQUIRE_NO_THROW(in >> value);
    BOOST_REQUIRE_EQUAL(value.data.size(), 1);
    BOOST_REQUIRE_EQUAL(value.data["A"], true);
}

BOOST_AUTO_TEST_SUITE_END()
