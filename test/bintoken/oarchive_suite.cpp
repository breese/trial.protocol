///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <functional>
#include <vector>
#include <limits>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/bintoken/serialization.hpp>
#include <trial/protocol/bintoken/serialization/array.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using output_type = std::uint8_t;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void test_false()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    bool value = false;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::false_value);
}

void test_const_false()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    const bool value = false;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::false_value);
}

void test_true()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    bool value = true;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::true_value);
}

void test_const_true()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    const bool value = true;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::true_value);
}

void run()
{
    test_empty();
    test_false();
    test_const_false();
    test_true();
    test_const_true();
}

} // namespace basic_suite

//-----------------------------------------------------------------------------
// Integers
//-----------------------------------------------------------------------------

namespace integer_suite
{

void test_zero()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    int value = 0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0x00);
}

void test_const_zero()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    const int value = 0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0x00);
}

void test_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    int value = 1;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0x01);
}

void test_minus_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    int value = -1;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0xFF);
}

void test_all_types()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    int alpha = 0x01;
    int bravo = 0x0100;
    int charlie = 0x010000;
    long long delta = UINT64_C(0x0100000000);
    ar << alpha << bravo << charlie << delta;

    output_type expected[] = { 0x01,
                              token::code::int16, 0x00, 0x01,
                              token::code::int32, 0x00, 0x00, 0x01, 0x00,
                              token::code::int64, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_zero();
    test_const_zero();
    test_one();
    test_minus_one();
    test_all_types();
}

} // namespace integer_suite

//-----------------------------------------------------------------------------
// Floating-point numbers
//-----------------------------------------------------------------------------

namespace number_suite
{

void test_float32_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    token::float32::type value = 1.0f;
    ar << value;

    output_type expected[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_const_float32_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    const token::float32::type value = 1.0f;
    ar << value;

    output_type expected[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float64_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    token::float64::type value = 1.0;
    ar << value;

    output_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_float32_one();
    test_const_float32_one();
    test_float64_one();
}

} // namespace number_suite

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::string value("");
    ar << value;

    output_type expected[] = { token::code::string8, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_const_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    const std::string value("");
    ar << value;

    output_type expected[] = { token::code::string8, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::string value("A");
    ar << value;

    output_type expected[] = { token::code::string8, 0x01, 0x41 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::string value("ABCD");
    ar << value;

    output_type expected[] = { token::code::string8, 0x04, 0x41, 0x42, 0x43, 0x44 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_empty();
    test_const_empty();
    test_one();
    test_many();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    bool array[] = { false };
    ar << array;

    output_type expected[] = { token::code::begin_array,
                              0x01,
                              0x80,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_four()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    bool array[] = { false, true, false, true };
    ar << array;

    output_type expected[] = { token::code::begin_array,
                              0x04,
                              0x80, 0x81, 0x80, 0x81,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_one();
    test_four();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Compact array
//-----------------------------------------------------------------------------

namespace compact_array_suite
{

void test_int8_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int8_t value[] = {0x7F};
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x01, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int8_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int8_t value[] = {0, -1, std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max()};
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x04, 0x00, 0xFF, 0x80, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint8_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint8_t value[] = {0xFF};
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x01, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint8_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint8_t value[] = {0x00, 0x7F, 0x80, 0xFF};
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x04, 0x00, 0x7F, 0x80, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_int16_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int16_t value[] = {0x7FFF};
    ar << value;

    output_type expected[] = { token::code::array8_int16, 0x02, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int16_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int16_t value[] = {0, -1, std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max()};
    ar << value;

    output_type expected[] = { token::code::array8_int16, 0x08,
                               0x00, 0x00,
                               0xFF, 0xFF,
                               0x00, 0x80,
                               0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint16_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint16_t value[] = {0x7FFF};
    ar << value;

    output_type expected[] = { token::code::array8_int16, 0x02, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint16_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint16_t value[] = {0x0000, 0x7FFF, 0x8000, 0xFFFF};
    ar << value;

    output_type expected[] = { token::code::array8_int16, 0x08, 0x00, 0x00, 0xFF, 0x7F, 0x00, 0x80, 0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_int32_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int32_t value[] = {std::numeric_limits<std::int32_t>::max()};
    ar << value;

    output_type expected[] = { token::code::array8_int32, 0x04, 0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int32_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int32_t value[] = {0, -1, std::numeric_limits<std::int32_t>::min(), std::numeric_limits<std::int32_t>::max()};
    ar << value;

    output_type expected[] = { token::code::array8_int32, 0x10,
                               0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0xFF,
                               0x00, 0x00, 0x00, 0x80,
                               0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint32_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint32_t value[] = {0x7FFFFFFF};
    ar << value;

    output_type expected[] = { token::code::array8_int32, 0x04, 0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint32_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint32_t value[] = {0x00000000, 0x7FFFFFFF, 0x80000000, 0xFFFFFFFF};
    ar << value;

    output_type expected[] = { token::code::array8_int32, 0x10,
                               0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0x7F,
                               0x00, 0x00, 0x00, 0x80,
                               0xFF, 0xFF, 0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_int64_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int64_t value[] = {std::numeric_limits<std::int64_t>::max()};
    ar << value;

    output_type expected[] = { token::code::array8_int64, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int64_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::int64_t value[] = {0, -1, std::numeric_limits<std::int64_t>::min(), std::numeric_limits<std::int64_t>::max()};
    ar << value;

    output_type expected[] = { token::code::array8_int64, 0x20,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint64_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint64_t value[] = {UINT64_C(0x7FFFFFFFFFFFFFFF)};
    ar << value;

    output_type expected[] = { token::code::array8_int64, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint64_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::uint64_t value[] = {UINT64_C(0x0000000000000000), UINT64_C(0x7FFFFFFFFFFFFFFF), UINT64_C(0x8000000000000000), UINT64_C(0xFFFFFFFFFFFFFFFF)};
    ar << value;

    output_type expected[] = { token::code::array8_int64, 0x20,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_float32_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    token::float32::type value[] = {1.0f};
    ar << value;

    output_type expected[] = { token::code::array8_float32, 0x04, 0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float32_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    token::float32::type value[] = {0.0f, -1.0f, 1.0f};
    ar << value;

    output_type expected[] = { token::code::array8_float32, 0x0C,
                               0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x80, 0xBF,
                               0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float64_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    token::float64::type value[] = {1.0};
    ar << value;

    output_type expected[] = { token::code::array8_float64, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float64_many()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    token::float64::type value[] = {0.0f, -1.0f, 1.0f};
    ar << value;

    output_type expected[] = { token::code::array8_float64, 0x18,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xBF,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_int8_one();
    test_int8_many();
    test_uint8_one();
    test_uint8_many();

    test_int16_one();
    test_int16_many();
    test_uint16_one();
    test_uint16_many();

    test_int32_one();
    test_int32_many();
    test_uint32_one();
    test_uint32_many();

    test_int64_one();
    test_int64_many();
    test_uint64_one();
    test_uint64_many();

    test_float32_one();
    test_float32_many();

    test_float64_one();
    test_float64_many();
}

} // namespace compact_array_suite

//-----------------------------------------------------------------------------
// Struct
//-----------------------------------------------------------------------------

namespace struct_suite
{

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

void test_person()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    person value("ABC", 127);
    ar << value;

    output_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x03, 0x41, 0x42, 0x43,
                              0x7F,
                              token::code::end_record };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_person();
}

} // namespace struct_suite

//-----------------------------------------------------------------------------
// Split struct
//-----------------------------------------------------------------------------

namespace split_struct_suite
{

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

void test_split_person()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    split_person value("ABC", 127);
    ar << value;

    output_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x03, 0x41, 0x42, 0x43,
                              0x7F,
                              token::code::end_record };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_split_person();
}

} // namespace split_struct_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    basic_suite::run();
    integer_suite::run();
    number_suite::run();
    string_suite::run();
    array_suite::run();
    compact_array_suite::run();
    struct_suite::run();
    split_struct_suite::run();

    return boost::report_errors();
}
