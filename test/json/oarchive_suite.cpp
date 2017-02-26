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
#include <limits>
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/json/serialization.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

using namespace trial::protocol;

//-----------------------------------------------------------------------------
// Basic types
//-----------------------------------------------------------------------------

namespace basic_suite
{

void test_empty()
{
    std::ostringstream result;
    json::oarchive ar(result);
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "");
}

void test_false()
{
    std::ostringstream result;
    json::oarchive out(result);
    bool value = false;
    out << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "false");
}

void test_const_false()
{
    std::ostringstream result;
    json::oarchive out(result);
    const bool value = false;
    out << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "false");
}

void test_true()
{
    std::ostringstream result;
    json::oarchive out(result);
    bool value = true;
    out << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "true");
}

void test_const_true()
{
    std::ostringstream result;
    json::oarchive out(result);
    const bool value = true;
    out << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "true");
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
    std::ostringstream result;
    json::oarchive ar(result);
    int value = 0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0");
}

void test_const_zero()
{
    std::ostringstream result;
    json::oarchive ar(result);
    const int value = 0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0");
}

void test_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    int value = 1;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "1");
}

void test_minus_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    int value = -1;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "-1");
}

void run()
{
    test_zero();
    test_const_zero();
    test_one();
    test_minus_one();
}

} // namespace integer_suite

//-----------------------------------------------------------------------------
// Number
//-----------------------------------------------------------------------------

namespace number_suite
{

void test_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = 1.0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "1.00000000000000");
}

void test_const_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    const double value = 1.0;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "1.00000000000000");
}

void test_half()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = 0.5;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "0.500000000000000");
}

void test_max()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::max();
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "1.79769313486232e+308");
}

void test_min()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::min();
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "2.22507385850720e-308");
}

void test_infinity()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::infinity();
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "null");
}

void test_minus_infinity()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = -std::numeric_limits<double>::infinity();
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "null");
}

void test_nan()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double value = std::numeric_limits<double>::quiet_NaN();
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "null");
}

void run()
{
    test_one();
    test_const_one();
    test_half();
    test_max();
    test_min();
    test_infinity();
    test_minus_infinity();
    test_nan();
}

} // namespace number_suite

//-----------------------------------------------------------------------------
// String
//-----------------------------------------------------------------------------

namespace string_suite
{

void test_empty()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::string value("");
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"\"");
}

void test_const_empty()
{
    std::ostringstream result;
    json::oarchive ar(result);
    const std::string value("");
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"\"");
}

void test_alpha()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::string value("alpha");
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"alpha\"");
}

void run()
{
    test_empty();
    test_const_empty();
    test_alpha();
}

} // namespace string_suite

//-----------------------------------------------------------------------------
// Array
//-----------------------------------------------------------------------------

namespace array_suite
{

void test_int_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    int array[] = { 1 };
    ar << array;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[1]");
}

void test_int_four()
{
    std::ostringstream result;
    json::oarchive ar(result);
    int array[] = { 1, 2, 3, 4 };
    ar << array;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[1,2,3,4]");
}

void test_double_four()
{
    std::ostringstream result;
    json::oarchive ar(result);
    double array[] = { 1.5, 2.5, 3.5, 4.5 };
    ar << array;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[1.50000000000000,2.50000000000000,3.50000000000000,4.50000000000000]");
}

void run()
{
    test_int_one();
    test_int_four();
    test_double_four();
}

} // namespace array_suite

//-----------------------------------------------------------------------------
// Pair
//-----------------------------------------------------------------------------

namespace pair_suite
{

void test_string_bool()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::pair<std::string, bool> value("alpha", true);
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[\"alpha\",true]");
}

void test_const_string_bool()
{
    std::ostringstream result;
    json::oarchive ar(result);
    const std::pair<std::string, bool> value("alpha", true);
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[\"alpha\",true]");
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
    std::ostringstream result;
    json::oarchive ar(result);
    boost::optional<std::string> value("alpha");
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"alpha\"");
}

void test_null()
{
    std::ostringstream result;
    json::oarchive ar(result);
    boost::optional<std::string> value;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "null");
}

void test_const_value()
{
    std::ostringstream result;
    json::oarchive ar(result);
    const boost::optional<std::string> value("alpha");
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "\"alpha\"");
}

void test_const_null()
{
    std::ostringstream result;
    json::oarchive ar(result);
    const boost::optional<std::string> value;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "null");
}

void run()
{
    test_value();
    test_null();
    test_const_value();
    test_const_null();
}

} // namespace optional_suite

//-----------------------------------------------------------------------------
// Vector
//-----------------------------------------------------------------------------

namespace vector_suite
{

void test_int_empty()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::vector<int> value;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[]");
}

void test_int_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::vector<int> value;
    value.push_back(1);
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[1]");
}

void test_int_two()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::vector<int> value;
    value.push_back(1);
    value.push_back(2);
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[1,2]");
}

void run()
{
    test_int_empty();
    test_int_one();
    test_int_two();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// Map
//-----------------------------------------------------------------------------

namespace map_suite
{

void test_bool_empty()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<std::string, bool> value;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{}");
}

void test_bool_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{\"A\":true}");
}

void test_bool_two()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<std::string, bool> value;
    value["A"] = true;
    value["B"] = false;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "{\"A\":true,\"B\":false}");
}

void test_nonobject_bool_empty()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<int, bool> value;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[]");
}

void test_nonobject_bool_one()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<int, bool> value;
    value[2] = true;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[[2,true]]");
}

void test_nonobject_bool_two()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::map<int, bool> value;
    value[2] = true;
    value[4] = false;
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[[2,true],[4,false]]");
}

void run()
{
    test_bool_empty();
    test_bool_one();
    test_bool_two();
    test_nonobject_bool_empty();
    test_nonobject_bool_one();
    test_nonobject_bool_two();
}

} // namespace map_suite

//-----------------------------------------------------------------------------
// Set
//-----------------------------------------------------------------------------

namespace set_suite
{

void test_empty()
{
    std::ostringstream result;
    json::oarchive ar(result);
    std::set<int> value;
    value.insert(2);
    value.insert(4);
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[2,4]");
}

void run()
{
    test_empty();
}

} // namespace set_suite

//-----------------------------------------------------------------------------
// Record
//-----------------------------------------------------------------------------

namespace record_suite
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
    std::int16_t age;
};

void test_struct()
{
    std::ostringstream result;
    json::oarchive ar(result);
    person value("Kant", 127);
    ar << value;
    TRIAL_PROTOCOL_TEST_EQUAL(result.str(), "[\"Kant\",127]");
}

void run()
{
    test_struct();
}

} // namespace record_suite

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
    pair_suite::run();
    optional_suite::run();
    vector_suite::run();
    map_suite::run();
    set_suite::run();
    record_suite::run();

    return boost::report_errors();
}
