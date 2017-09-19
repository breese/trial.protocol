///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/boost/any.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// boost::any
//-----------------------------------------------------------------------------

namespace any_suite
{

void convert_null()
{
    boost::any any;
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<nullable>());
}

void convert_boolean()
{
    boost::any any(true);
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<boolean>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<boolean>(), true);
}

void convert_integer()
{
    {
        const signed char value = 2;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed char>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned char value = 2U;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned char>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed short int value = 2;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed short int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned short int value = 2U;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned short int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed int value = 2;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned int value = 2U;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed long int value = 2L;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned long int value = 2UL;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed long long int value = 2LL;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed long long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned long long int value = 2ULL;
        boost::any any(value);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned long long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
}

void convert_number()
{
    {
        boost::any any(3.0f);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
    }
    {
        boost::any any(3.0);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
    }
    {
        boost::any any(3.0L);
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
    }
}

void convert_string()
{
    boost::any any(std::string("alpha"));
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<std::string>(), "alpha");
}

void convert_string_literal()
{
    boost::any any("alpha");
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<std::string>(), "alpha");
}

void convert_wstring()
{
    boost::any any(std::wstring(L"bravo"));
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<wstring>());
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"bravo");
}

void convert_wstring_literal()
{
    boost::any any(L"bravo");
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<wstring>());
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"bravo");
}

void convert_u16string()
{
    boost::any any(std::u16string(u"charlie"));
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<u16string>());
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"charlie");
}

void convert_u16string_literal()
{
    boost::any any(u"charlie");
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<u16string>());
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"charlie");
}

void convert_array_integer()
{
    {
        boost::any any(std::vector<signed short int>{ 2, 22 });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2, 22 }));
    }
    {
        boost::any any(std::vector<unsigned short int>{ 2U, 22U });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2U, 22U }));
    }
    {
        boost::any any(std::vector<signed int>{ 2, 22 });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2, 22 }));
    }
    {
        boost::any any(std::vector<unsigned int>{ 2U, 22U });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2U, 22U }));
    }
    {
        boost::any any(std::vector<signed long int>{ 2L, 22L });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2L, 22L }));
    }
    {
        boost::any any(std::vector<unsigned long int>{ 2UL, 22UL });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2UL, 22UL }));
    }
    {
        boost::any any(std::vector<signed long long int>{ 2LL, 22LL });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2LL, 22LL }));
    }
    {
        boost::any any(std::vector<unsigned long long int>{ 2ULL, 22ULL });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2ULL, 22ULL }));
    }
}

void convert_array_number()
{
    {
        boost::any any(std::vector<float>{ 3.0f, 33.0f, 333.0f });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 3.0f, 33.0f, 333.0f }));
    }
    {
        boost::any any(std::vector<double>{ 3.0, 33.0, 333.0 });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 3.0, 33.0, 333.0 }));
    }
    {
        boost::any any(std::vector<long double>{ 3.0L, 33.0L, 333.0L });
        variable result = convert<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 3.0L, 33.0L, 333.0L }));
    }
}

void convert_array_string()
{
    boost::any any(std::vector<std::string>{ "alpha", "bravo", "charlie" });
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    TRIAL_PROTOCOL_TEST(result == array::make({ "alpha", "bravo", "charlie" }));
}

void convert_array_wstring()
{
    boost::any any(std::vector<std::wstring>{ L"alpha", L"bravo", L"charlie" });
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    TRIAL_PROTOCOL_TEST(result == array::make({ L"alpha", L"bravo", L"charlie" }));
}

void convert_array_u16string()
{
    boost::any any(std::vector<std::u16string>{ u"alpha", u"bravo", u"charlie" });
    variable result = convert<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    TRIAL_PROTOCOL_TEST(result == array::make({ u"alpha", u"bravo", u"charlie" }));
}

void fail_on_struct()
{
    struct record {};
    boost::any any(record{});
    std::error_code error;
    variable result = convert<variable>(any, error);
    TRIAL_PROTOCOL_TEST(result.is<nullable>());
    TRIAL_PROTOCOL_TEST(error == make_error_code(incompatible_type));
}

void throw_on_struct()
{
    struct record {};
    boost::any any(record{});
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<variable>(any),
                                    error,
                                    "incompatible type");
}

void run()
{
    convert_null();
    convert_boolean();
    convert_integer();
    convert_number();
    convert_string();
    convert_string_literal();
    convert_wstring();
    convert_wstring_literal();
    convert_u16string();
    convert_u16string_literal();
    convert_array_integer();
    convert_array_number();
    convert_array_string();
    convert_array_wstring();
    convert_array_u16string();
    fail_on_struct();
    throw_on_struct();
}

} // namespace any_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    any_suite::run();

    return boost::report_errors();
}
