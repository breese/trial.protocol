///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/bintoken/serialization.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

namespace format = trial::protocol::bintoken;
namespace token = format::token;
using output_type = std::uint8_t;

//-----------------------------------------------------------------------------
// std::array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_bool()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<bool, 4> value = {{ false, true, false, true }};
    ar << value;

    const output_type expected[] = { token::code::begin_array,
                                     0x04,
                                     0x80, 0x81, 0x80, 0x81,
                                     token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_string()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::string, 2> value = {{ "AB", "CD" }};
    ar << value;

    const output_type expected[] = { token::code::begin_array,
                                     0x02,
                                     token::code::string8, 0x02, 0x41, 0x42,
                                     token::code::string8, 0x02, 0x43, 0x44,
                                     token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_bool();
    test_string();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Compact std::array
//-----------------------------------------------------------------------------

namespace compact_array_suite
{

void test_int8()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::int8_t, 4> value = {{0, -1, std::numeric_limits<std::int8_t>::min(), std::numeric_limits<std::int8_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int8, 4 * token::int8::size,
                               0x00, 0xFF, 0x80, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint8()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::uint8_t, 4> value = {{0, 1, std::numeric_limits<std::uint8_t>::min(), std::numeric_limits<std::uint8_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int8, 4 * token::int8::size,
                               0x00, 0x01, 0x00, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int16()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::int16_t, 4> value = {{0, -1, std::numeric_limits<std::int16_t>::min(), std::numeric_limits<std::int16_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int16, 4 * token::int16::size,
                               0x00, 0x00,
                               0xFF, 0xFF,
                               0x00, 0x80,
                               0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint16()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::uint16_t, 4> value = {{0, 1, std::numeric_limits<std::uint16_t>::min(), std::numeric_limits<std::uint16_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int16, 4 * token::int16::size,
                               0x00, 0x00,
                               0x01, 0x00,
                               0x00, 0x00,
                               0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int32()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::int32_t, 4> value = {{0, -1, std::numeric_limits<std::int32_t>::min(), std::numeric_limits<std::int32_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int32, 4 * token::int32::size,
                               0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0xFF,
                               0x00, 0x00, 0x00, 0x80,
                               0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint32()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::uint32_t, 4> value = {{0, 1, std::numeric_limits<std::uint32_t>::min(), std::numeric_limits<std::uint32_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int32, 4 * token::int32::size,
                               0x00, 0x00, 0x00, 0x00,
                               0x01, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int64()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::int64_t, 4> value = {{0, -1, std::numeric_limits<std::int64_t>::min(), std::numeric_limits<std::int64_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int64, 4 * token::int64::size,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint64()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<std::uint64_t, 4> value = {{0, 1, std::numeric_limits<std::uint64_t>::min(), std::numeric_limits<std::uint64_t>::max()}};
    ar << value;

    output_type expected[] = { token::code::array8_int64, 4 * token::int64::size,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float32()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<token::float32::type, 3> value = {{0.0f, -1.0f, 1.0f}};
    ar << value;

    output_type expected[] = { token::code::array8_float32, 3 * token::float32::size,
                               0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x80, 0xBF,
                               0x00, 0x00, 0x80, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_float64()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::array<token::float64::type, 3> value = {{0.0f, -1.0f, 1.0f}};
    ar << value;

    output_type expected[] = { token::code::array8_float64, 3 * token::float64::size,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xBF,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3F };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_int8();
    test_uint8();
    test_int16();
    test_uint16();
    test_int32();
    test_uint32();
    test_int64();
    test_uint64();
    test_float32();
    test_float64();
}

} // namespace compact_array_suite

//-----------------------------------------------------------------------------
// std::pair
//-----------------------------------------------------------------------------

namespace pair_suite
{

void test_string_bool()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::pair<std::string, bool> value("A", true);
    ar << value;

    output_type expected[] = { token::code::begin_record,
                               token::code::string8, 0x01, 0x41,
                               token::code::true_value,
                               token::code::end_record };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_const_string_bool()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    const std::pair<std::string, bool> value("A", true);
    ar << value;

    output_type expected[] = { token::code::begin_record,
                              token::code::string8, 0x01, 0x41,
                              token::code::true_value,
                              token::code::end_record };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_string_bool();
    test_const_string_bool();
}

} // namespace pair_suite

//-----------------------------------------------------------------------------
// std::vector
//-----------------------------------------------------------------------------

namespace vector_suite
{

void test_bool_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<bool> value;
    ar << value;

    output_type expected[] = { token::code::begin_array,
                              0x00,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_bool_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<bool> value;
    value.push_back(true);
    ar << value;

    output_type expected[] = { token::code::begin_array,
                              0x01,
                              token::code::true_value,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_bool_two()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<bool> value;
    value.push_back(true);
    value.push_back(false);
    ar << value;

    output_type expected[] = { token::code::begin_array,
                              0x02,
                              token::code::true_value,
                              token::code::false_value,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int8_two()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::int8_t> value;
    value.push_back(0);
    value.push_back(1);
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x02, 0x00, 0x01 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_bool_empty();
    test_bool_one();
    test_bool_two();

    test_int8_two();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// Compact std::vector
//-----------------------------------------------------------------------------

namespace compact_vector_suite
{

void test_int8_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::int8_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int8_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::int8_t> value{0x7F};
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
    std::vector<std::int8_t> value{0x00, 0x7F, -0x80, -0x01};
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x04, 0x00, 0x7F, 0x80, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int8_big()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::int8_t> value(0x10000, 0x7F);
    ar << value;

    std::vector<output_type> expected{{token::code::array32_int8, 0x00, 0x00, 0x01, 0x00}};
    for (std::vector<output_type>::size_type i = 0; i < value.size(); ++i)
    {
        expected.push_back(0x7F);
    }
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<output_type>());
}

void test_uint8_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::uint8_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint8_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::uint8_t> value(1, 0xFF);
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
    std::vector<std::uint8_t> value(4, 0xFF);
    ar << value;

    output_type expected[] = { token::code::array8_int8, 0x04, 0xFF, 0xFF, 0xFF, 0xFF };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint8_big()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::uint8_t> value(0x10000, 0xFF);
    ar << value;

    std::vector<output_type> expected;
    expected.push_back(token::code::array32_int8);
    expected.push_back(0x00);
    expected.push_back(0x00);
    expected.push_back(0x01);
    expected.push_back(0x00);
    for (std::vector<output_type>::size_type i = 0; i < value.size(); ++i)
    {
        expected.push_back(0xFF);
    }
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected.begin(), expected.end(),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_int16_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::int16_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int16, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint16_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::uint16_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int16, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_int32_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::int32_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int32, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint32_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::uint32_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int32, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_int64_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::int64_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int64, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_uint64_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<std::uint64_t> value;
    ar << value;

    output_type expected[] = { token::code::array8_int64, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_float32_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<token::float32::type> value;
    ar << value;

    output_type expected[] = { token::code::array8_float32, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

//-----------------------------------------------------------------------------

void test_float64_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::vector<token::float64::type> value;
    ar << value;

    output_type expected[] = { token::code::array8_float64, 0x00 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_int8_empty();
    test_int8_one();
    test_int8_many();
    test_int8_big();
    test_uint8_empty();
    test_uint8_one();
    test_uint8_many();
    test_uint8_big();

    test_int16_empty();
    test_uint16_empty();

    test_int32_empty();
    test_uint32_empty();

    test_int64_empty();
    test_uint64_empty();

    test_float32_empty();
    test_float64_empty();
}

} // namespace compact_vector_suite

//-----------------------------------------------------------------------------
// std::set
//-----------------------------------------------------------------------------

namespace set_suite
{

void test_int_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::set<int> value;
    ar << value;

    output_type expected[] = { token::code::begin_array,
                               token::code::null,
                               token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::set<int> value;
    value.insert(0x11);
    ar << value;

    output_type expected[] = { token::code::begin_array,
                              token::code::null,
                              0x11,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int_two()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::set<int> value;
    value.insert(0x11);
    value.insert(0x22);
    ar << value;

    output_type expected[] = { token::code::begin_array,
                              token::code::null,
                              0x11,
                              0x22,
                              token::code::end_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void run()
{
    test_int_empty();
    test_int_one();
    test_int_two();
}

} // namespace set_suite

//-----------------------------------------------------------------------------
// std::map
//-----------------------------------------------------------------------------

namespace map_suite
{

void test_string_bool_empty()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::map<std::string, bool> value;
    ar << value;

    output_type expected[] = { token::code::begin_assoc_array,
                              token::code::null,
                              token::code::end_assoc_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_string_bool_one()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    ar << value;

    output_type expected[] = { token::code::begin_assoc_array,
                              token::code::null,
                              token::code::begin_record,
                              token::code::string8, 0x01, 0x41,
                              token::code::true_value,
                              token::code::end_record,
                              token::code::end_assoc_array };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_string_bool_two()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    value["B"] = false;
    ar << value;

    output_type expected[] = { token::code::begin_assoc_array,
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
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
}

void test_int_string_two()
{
    std::vector<output_type> result;
    format::oarchive ar(result);
    std::map<int, std::string> value;
    value[0x11] = "A";
    value[0x12] = "B";
    ar << value;

    output_type expected[] = { token::code::begin_assoc_array,
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
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expected, expected + sizeof(expected),
                                 std::equal_to<output_type>());
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
// main
//-----------------------------------------------------------------------------

int main()
{
    array_suite::run();
    compact_array_suite::run();
    pair_suite::run();
    vector_suite::run();
    compact_vector_suite::run();
    set_suite::run();
    map_suite::run();

    return boost::report_errors();
}
