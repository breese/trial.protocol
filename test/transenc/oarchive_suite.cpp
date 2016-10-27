///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/transenc/serialization.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::transenc;
namespace token = format::token;
typedef format::writer::value_type value_type;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 0);
}

void test_false()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    bool value = false;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::false_value);
}

void test_const_false()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const bool value = false;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::false_value);
}

void test_true()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    bool value = true;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], token::code::true_value);
}

void test_const_true()
{
    std::vector<value_type> result;
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
    std::vector<value_type> result;
    format::oarchive ar(result);
    int value = 0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0x00);
}

void test_const_zero()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const int value = 0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0x00);
}

void test_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    int value = 1;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0x01);
}

void test_minus_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    int value = -1;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(result[0], 0xFF);
}

void test_all_types()
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
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
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

namespace floating_suite
{

void test_float32_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    token::float32::type value = 1.0f;
    ar << value;

    value_type expected[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_const_float32_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const token::float32::type value = 1.0f;
    ar << value;

    value_type expected[] = { token::code::float32, 0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_float64_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    token::float64::type value = 1.0;
    ar << value;

    value_type expected[] = { token::code::float64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_float32_one();
    test_const_float32_one();
    test_float64_one();
}

} // namespace floating_suite

//-----------------------------------------------------------------------------
// Strings
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_empty()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::string value("");
    ar << value;

    value_type expected[] = { token::code::string8, 0x00 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_const_empty()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const std::string value("");
    ar << value;

    value_type expected[] = { token::code::string8, 0x00 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::string value("A");
    ar << value;

    value_type expected[] = { token::code::string8, 0x01, 0x41 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_many()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::string value("ABCD");
    ar << value;

    value_type expected[] = { token::code::string8, 0x04, 0x41, 0x42, 0x43, 0x44 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
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
// Binary
//-----------------------------------------------------------------------------

namespace binary_suite
{

void test_empty()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<boost::uint8_t> value;
    ar << value;

    value_type expected[] = { token::code::binary8, 0x00 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<boost::uint8_t> value(1, 0xFF);
    ar << value;

    value_type expected[] = { token::code::binary8, 0x01, 0xFF };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_many()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<boost::uint8_t> value(4, 0xFF);
    ar << value;

    value_type expected[] = { token::code::binary8, 0x04, 0xFF, 0xFF, 0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_big()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<boost::uint8_t> value(0x10000, 0xFF);
    ar << value;

    std::vector<value_type> expected;
    expected.push_back(token::code::binary32);
    expected.push_back(0x00);
    expected.push_back(0x00);
    expected.push_back(0x01);
    expected.push_back(0x00);
    for (std::vector<value_type>::size_type i = 0; i < value.size(); ++i)
    {
        expected.push_back(0xFF);
    }
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected.begin(), expected.end());
}

void run()
{
    test_empty();
    test_one();
    test_many();
    test_big();
}

} // namespace binary_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_one()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    value_type array[] = { 1 };
    ar << array;

    value_type expected[] = { token::code::begin_array,
                              0x01,
                              0x01,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_four()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    value_type array[] = { 1, 2, 3, 4 };
    ar << array;

    value_type expected[] = { token::code::begin_array,
                              0x04,
                              0x01, 0x02, 0x03, 0x04,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_one();
    test_four();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Pair
//-----------------------------------------------------------------------------

namespace pair_suite
{

void test_string_bool()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::pair<std::string, bool> value("A", true);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x01, 0x41,
                              token::code::true_value,
                              token::code::end_record };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_const_string_bool()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const std::pair<std::string, bool> value("A", true);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x01, 0x41,
                              token::code::true_value,
                              token::code::end_record };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_string_bool();
    test_const_string_bool();
}

} // namespace pair_suite

//-----------------------------------------------------------------------------
// Optional
//-----------------------------------------------------------------------------

namespace optional_suite
{

void test_value()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    boost::optional<std::string> value("A");
    ar << value;

    value_type expected[] = { token::code::string8, 0x01, 0x41 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_const_value()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    const boost::optional<std::string> value("A");
    ar << value;

    value_type expected[] = { token::code::string8, 0x01, 0x41 };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_null()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    boost::optional<std::string> value;
    ar << value;

    value_type expected[] = { token::code::null };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_value();
    test_const_value();
    test_null();
}

} // namespace optional_suite

//-----------------------------------------------------------------------------
// Vector
//-----------------------------------------------------------------------------

namespace vector_suite
{

void test_bool_empty()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::vector<bool> value;
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              0x00,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_bool_one()
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
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_bool_two()
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
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_bool_empty();
    test_bool_one();
    test_bool_two();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// Set
//-----------------------------------------------------------------------------

namespace set_suite
{

void test_int_empty()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::set<int> value;
    ar << value;

    value_type expected[] = { token::code::begin_array,
                              token::code::null,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_int_one()
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
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_int_two()
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
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_int_empty();
    test_int_one();
    test_int_two();
}

} // namespace set_suite

//-----------------------------------------------------------------------------
// Map
//-----------------------------------------------------------------------------

namespace map_suite
{

void test_string_bool_empty()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::map<std::string, bool> value;
    ar << value;

    value_type expected[] = { token::code::begin_assoc_array,
                              token::code::null,
                              token::code::end_assoc_array };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_string_bool_one()
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
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_string_bool_two()
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
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void test_int_string_two()
{
    std::vector<value_type> result;
    format::oarchive ar(result);
    std::map<int, std::string> value;
    value[0x11] = "A";
    value[0x12] = "B";
    ar << value;

    value_type expected[] = { token::code::begin_assoc_array,
                              token::code::null,
                              token::code::begin_record,
                              0x11,
                              token::code::string8, 0x01, 0x41,
                              token::code::end_record,
                              token::code::begin_record,
                              0x12,
                              token::code::string8, 0x01, 0x42,
                              token::code::end_record,
                              token::code::end_assoc_array };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
}

void run()
{
    test_string_bool_empty();
    test_string_bool_one();
    test_string_bool_two();
    test_int_string_two();
}

} // namespace map_suite

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
    std::vector<value_type> result;
    format::oarchive ar(result);
    person value("ABC", 127);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x03, 0x41, 0x42, 0x43,
                              0x7F,
                              token::code::end_record };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
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
    std::vector<value_type> result;
    format::oarchive ar(result);
    split_person value("ABC", 127);
    ar << value;

    value_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x03, 0x41, 0x42, 0x43,
                              0x7F,
                              token::code::end_record };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(result.begin(), result.end(),
                                          expected, expected + sizeof(expected));
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
    floating_suite::run();
    string_suite::run();
    binary_suite::run();
    array_suite::run();
    pair_suite::run();
    optional_suite::run();
    vector_suite::run();
    set_suite::run();
    map_suite::run();
    struct_suite::run();
    split_struct_suite::run();

    return boost::report_errors();
}
