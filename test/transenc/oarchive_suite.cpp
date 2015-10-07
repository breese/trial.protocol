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

#include <vector>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/transenc/serialization/oarchive.hpp>
#include <trial/protocol/transenc/serialization/string.hpp>
#include <trial/protocol/transenc/serialization/pair.hpp>
#include <trial/protocol/transenc/serialization/optional.hpp>
#include <trial/protocol/transenc/serialization/vector.hpp>
#include <trial/protocol/transenc/serialization/set.hpp>
#include <trial/protocol/transenc/serialization/map.hpp>

namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::writer::value_type value_type;

BOOST_AUTO_TEST_SUITE(transenc_oarchive_suite)

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    BOOST_REQUIRE_EQUAL(result.size(), 0);
}

BOOST_AUTO_TEST_CASE(test_false)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    bool value = false;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], token::code::false_value);
}

BOOST_AUTO_TEST_CASE(test_const_false)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const bool value = false;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], token::code::false_value);
}

BOOST_AUTO_TEST_CASE(test_true)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    bool value = true;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], token::code::true_value);
}

BOOST_AUTO_TEST_CASE(test_const_true)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const bool value = true;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], token::code::true_value);
}

//-----------------------------------------------------------------------------
// Integers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_int_zero)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    int value = 0;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], 0x00);
}

BOOST_AUTO_TEST_CASE(test_const_int_zero)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const int value = 0;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], 0x00);
}

BOOST_AUTO_TEST_CASE(test_int_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    int value = 1;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], 0x01);
}

BOOST_AUTO_TEST_CASE(test_int_minus_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    int value = -1;
    ar << value;
    BOOST_REQUIRE_EQUAL(result.size(), 1);
    BOOST_REQUIRE_EQUAL(result[0], 0xFF);
}

BOOST_AUTO_TEST_CASE(test_int_all_types)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    int alpha = 0x01;
    int bravo = 0x0100;
    int charlie = 0x010000;
    long long delta = UINT64_C(0x0100000000);
    ar << alpha << bravo << charlie << delta;

    value_type expected[] = { 0x01,
                              token::code::int16, 0x00, 0x01,
                              token::code::int32, 0x00, 0x00, 0x01, 0x00,
                              token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Floating-point numbers
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_float32_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    token::float32::type value = 1.0f;
    ar << value;

    value_type expected[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_const_float32_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const token::float32::type value = 1.0f;
    ar << value;

    value_type expected[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_float64_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    token::float64::type value = 1.0;
    ar << value;

    value_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_string_empty)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::string value("");
    ar << value;

    value_type expected[] = { token::code::string8, 0x00 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_const_string_empty)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const std::string value("");
    ar << value;

    value_type expected[] = { token::code::string8, 0x00 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_string_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::string value("A");
    ar << value;

    value_type expected[] = { token::code::string8, 0x01, 0x41 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_string_many)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::string value("ABCD");
    ar << value;

    value_type expected[] = { token::code::string8, 0x04, 0x41, 0x42, 0x43, 0x44 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Binary
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_binary_empty)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<boost::uint8_t> value;
    ar << value;

    value_type expected[] = { token::code::binary8, 0x00 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_binary_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<boost::uint8_t> value(1, 0xFF);
    ar << value;

    value_type expected[] = { token::code::binary8, 0x01, 0xFF };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_binary_many)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<boost::uint8_t> value(4, 0xFF);
    ar << value;

    value_type expected[] = { token::code::binary8, 0x04, 0xFF, 0xFF, 0xFF, 0xFF };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Pair
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_pair)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::pair<std::string, bool> value("A", true);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x01, 0x41,
                              token::code::true_value,
                              token::code::end_record };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_const_pair)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const std::pair<std::string, bool> value("A", true);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x01, 0x41,
                              token::code::true_value,
                              token::code::end_record };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Optional
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_optional)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    boost::optional<std::string> value("A");
    ar << value;

    value_type expected[] = { token::code::string8, 0x01, 0x41 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_const_optional)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const boost::optional<std::string> value("A");
    ar << value;

    value_type expected[] = { token::code::string8, 0x01, 0x41 };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_optional_null)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    boost::optional<std::string> value;
    ar << value;

    value_type expected[] = { token::code::null };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Vector
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_vector_bool_empty)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<bool> value;
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              0x00,
                              token::code::end_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_vector_bool_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<bool> value;
    value.push_back(true);
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              0x01,
                              token::code::true_value,
                              token::code::end_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_vector_bool_two)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<bool> value;
    value.push_back(true);
    value.push_back(false);
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              0x02,
                              token::code::true_value,
                              token::code::false_value,
                              token::code::end_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Set
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_set_int_empty)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::set<int> value;
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              token::code::null,
                              token::code::end_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_set_int_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::set<int> value;
    value.insert(0x11);
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              token::code::null,
                              0x11,
                              token::code::end_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_set_int_two)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::set<int> value;
    value.insert(0x11);
    value.insert(0x22);
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              token::code::null,
                              0x11,
                              0x22,
                              token::code::end_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

//-----------------------------------------------------------------------------
// Map
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_map_bool_empty)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::map<std::string, bool> value;
    ar << value;

    value_type expected[] = { token::code::begin_assoc_array,
                              token::code::null,
                              token::code::end_assoc_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_map_bool_one)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    ar << value;

    value_type expected[] = { token::code::begin_assoc_array,
                              token::code::null,
                              token::code::begin_record,
                              token::code::string8, 0x01, 0x41,
                              token::code::true_value,
                              token::code::end_record,
                              token::code::end_assoc_array };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_map_bool_two)
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    value["B"] = false;
    ar << value;

    value_type expected[] = { token::code::begin_assoc_array,
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
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
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
    std::vector<value_type> result;
    format::oarchive ar(result);
    person value("ABC", 127);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x03, 0x41, 0x42, 0x43,
                              0x7F,
                              token::code::end_record };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
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
    std::vector<value_type> result;
    format::oarchive ar(result);
    split_person value("ABC", 127);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x03, 0x41, 0x42, 0x43,
                              0x7F,
                              token::code::end_record };
    BOOST_REQUIRE_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                    expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_SUITE_END()
