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
#include <trial/dynamic/convert/boost/any.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------

namespace from_suite
{

void convert_null()
{
    boost::any any;
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<nullable>());
}

void convert_boolean()
{
    boost::any any(true);
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<boolean>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<boolean>(), true);
}

void convert_integer()
{
    {
        const signed char value = 2;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed char>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned char value = 2U;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned char>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed short int value = 2;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed short int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned short int value = 2U;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned short int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed int value = 2;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned int value = 2U;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed long int value = 2L;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned long int value = 2UL;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const signed long long int value = 2LL;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<signed long long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
    {
        const unsigned long long int value = 2ULL;
        boost::any any(value);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.same<unsigned long long int>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<int>(), 2);
    }
}

void convert_real()
{
    {
        boost::any any(3.0f);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
    }
    {
        boost::any any(3.0);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
    }
    {
        boost::any any(3.0L);
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
    }
}

void convert_string()
{
    boost::any any(std::string("alpha"));
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<std::string>(), "alpha");
}

void convert_string_literal()
{
    boost::any any("alpha");
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<string>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<std::string>(), "alpha");
}

void convert_wstring()
{
    boost::any any(std::wstring(L"bravo"));
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<wstring>());
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"bravo");
}

void convert_wstring_literal()
{
    boost::any any(L"bravo");
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<wstring>());
    TRIAL_PROTOCOL_TEST(result.value<std::wstring>() == L"bravo");
}

void convert_u16string()
{
    boost::any any(std::u16string(u"charlie"));
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<u16string>());
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"charlie");
}

void convert_u16string_literal()
{
    boost::any any(u"charlie");
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<u16string>());
    TRIAL_PROTOCOL_TEST(result.value<std::u16string>() == u"charlie");
}

void convert_u32string()
{
    boost::any any(std::u32string(U"delta"));
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<u32string>());
    TRIAL_PROTOCOL_TEST(result.value<std::u32string>() == U"delta");
}

void convert_u32string_literal()
{
    boost::any any(U"delta");
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<u32string>());
    TRIAL_PROTOCOL_TEST(result.value<std::u32string>() == U"delta");
}

void convert_array_integer()
{
    {
        boost::any any(std::vector<signed short int>{ 2, 22 });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2, 22 }));
    }
    {
        boost::any any(std::vector<unsigned short int>{ 2U, 22U });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2U, 22U }));
    }
    {
        boost::any any(std::vector<signed int>{ 2, 22 });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2, 22 }));
    }
    {
        boost::any any(std::vector<unsigned int>{ 2U, 22U });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2U, 22U }));
    }
    {
        boost::any any(std::vector<signed long int>{ 2L, 22L });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2L, 22L }));
    }
    {
        boost::any any(std::vector<unsigned long int>{ 2UL, 22UL });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2UL, 22UL }));
    }
    {
        boost::any any(std::vector<signed long long int>{ 2LL, 22LL });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2LL, 22LL }));
    }
    {
        boost::any any(std::vector<unsigned long long int>{ 2ULL, 22ULL });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 2ULL, 22ULL }));
    }
}

void convert_array_real()
{
    {
        boost::any any(std::vector<float>{ 3.0f, 33.0f, 333.0f });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 3.0f, 33.0f, 333.0f }));
    }
    {
        boost::any any(std::vector<double>{ 3.0, 33.0, 333.0 });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 3.0, 33.0, 333.0 }));
    }
    {
        boost::any any(std::vector<long double>{ 3.0L, 33.0L, 333.0L });
        variable result = convert::into<variable>(any);
        TRIAL_PROTOCOL_TEST(result.is<array>());
        TRIAL_PROTOCOL_TEST(result == array::make({ 3.0L, 33.0L, 333.0L }));
    }
}

void convert_array_string()
{
    boost::any any(std::vector<std::string>{ "alpha", "bravo", "charlie" });
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    TRIAL_PROTOCOL_TEST(result == array::make({ "alpha", "bravo", "charlie" }));
}

void convert_array_wstring()
{
    boost::any any(std::vector<std::wstring>{ L"alpha", L"bravo", L"charlie" });
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    TRIAL_PROTOCOL_TEST(result == array::make({ L"alpha", L"bravo", L"charlie" }));
}

void convert_array_u16string()
{
    boost::any any(std::vector<std::u16string>{ u"alpha", u"bravo", u"charlie" });
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    TRIAL_PROTOCOL_TEST(result == array::make({ u"alpha", u"bravo", u"charlie" }));
}

void convert_array_u32string()
{
    boost::any any(std::vector<std::u32string>{ U"alpha", U"bravo", U"charlie" });
    variable result = convert::into<variable>(any);
    TRIAL_PROTOCOL_TEST(result.is<array>());
    TRIAL_PROTOCOL_TEST(result == array::make({ U"alpha", U"bravo", U"charlie" }));
}

void fail_on_struct()
{
    struct record {};
    boost::any any(record{});
    std::error_code error;
    variable result = convert::into<variable>(any, error);
    TRIAL_PROTOCOL_TEST(result.is<nullable>());
    TRIAL_PROTOCOL_TEST(error == make_error_code(incompatible_type));
}

void throw_on_struct()
{
    struct record {};
    boost::any any(record{});
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert::into<variable>(any),
                                    error,
                                    "incompatible type");
}

void run()
{
    convert_null();
    convert_boolean();
    convert_integer();
    convert_real();
    convert_string();
    convert_string_literal();
    convert_wstring();
    convert_wstring_literal();
    convert_u16string();
    convert_u16string_literal();
    convert_u32string();
    convert_u32string_literal();
    convert_array_integer();
    convert_array_real();
    convert_array_string();
    convert_array_wstring();
    convert_array_u16string();
    convert_array_u32string();
    fail_on_struct();
    throw_on_struct();
}

} // namespace from_suite

//-----------------------------------------------------------------------------

namespace to_suite
{

void convert_null()
{
    variable data;
    auto result = convert::into<boost::any>(data);
    TRIAL_PROTOCOL_TEST(result.empty());
    TRIAL_PROTOCOL_TEST(result.type() == typeid(void));
}

void convert_boolean()
{
    variable data(true);
    auto result = convert::into<boost::any>(data);
    TRIAL_PROTOCOL_TEST(result.type() == typeid(bool));
    TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<bool>(result), true);
}

void convert_integer()
{
    {
        using integer_type = signed char;
        integer_type input = 2;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = unsigned char;
        integer_type input = 2U;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = signed short int;
        integer_type input = 2;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = unsigned short int;
        integer_type input = 2U;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = signed int;
        integer_type input = 2;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = unsigned int;
        integer_type input = 2U;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = signed long int;
        integer_type input = 2L;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = unsigned long int;
        integer_type input = 2UL;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = signed long long int;
        integer_type input = 2LL;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
    {
        using integer_type = unsigned long long int;
        integer_type input = 2ULL;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(integer_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<integer_type>(result), input);
    }
}

void convert_real()
{
    {
        using real_type = float;
        real_type input = 3.0f;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(real_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<real_type>(result), input);
    }
    {
        using real_type = double;
        real_type input = 3.0;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(real_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<real_type>(result), input);
    }
    {
        using real_type = double;
        real_type input = 3.0L;
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(real_type));
        TRIAL_PROTOCOL_TEST_EQUAL(boost::any_cast<real_type>(result), input);
    }
}

void convert_string()
{
    {
        using string_type = std::string;
        string_type input = "alpha";
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(string_type));
        TRIAL_PROTOCOL_TEST(boost::any_cast<string_type>(result) == input);
    }
    {
        using string_type = std::wstring;
        string_type input = L"bravo";
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(string_type));
        TRIAL_PROTOCOL_TEST(boost::any_cast<string_type>(result) == input);
    }
    {
        using string_type = std::u16string;
        string_type input = u"charlie";
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(string_type));
        TRIAL_PROTOCOL_TEST(boost::any_cast<string_type>(result) == input);
    }
    {
        using string_type = std::u32string;
        string_type input = U"delta";
        variable data(input);
        auto result = convert::into<boost::any>(data);
        TRIAL_PROTOCOL_TEST(result.type() == typeid(string_type));
        TRIAL_PROTOCOL_TEST(boost::any_cast<string_type>(result) == input);
    }
}

void convert_array()
{
    variable data = { null, true, 2, 3.0f, "alpha" };
    std::error_code error;
    auto result = convert::into<std::vector<boost::any>>(data, error);
    TRIAL_PROTOCOL_TEST_EQUAL(result.size(), 5);
    TRIAL_PROTOCOL_TEST(result[0].type() == typeid(void));
    TRIAL_PROTOCOL_TEST(result[1].type() == typeid(bool));
    TRIAL_PROTOCOL_TEST(boost::any_cast<bool>(result[1]) == true);
    TRIAL_PROTOCOL_TEST(result[2].type() == typeid(int));
    TRIAL_PROTOCOL_TEST(boost::any_cast<int>(result[2]) == 2);
    TRIAL_PROTOCOL_TEST(result[3].type() == typeid(float));
    TRIAL_PROTOCOL_TEST(boost::any_cast<float>(result[3]) == 3.0f);
    TRIAL_PROTOCOL_TEST(result[4].type() == typeid(std::string));
    TRIAL_PROTOCOL_TEST(boost::any_cast<std::string>(result[4]) == "alpha");
}

void run()
{
    convert_null();
    convert_boolean();
    convert_integer();
    convert_real();
    convert_string();
    convert_array();
}

} // namespace to_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    from_suite::run();
    to_suite::run();

    return boost::report_errors();
}
