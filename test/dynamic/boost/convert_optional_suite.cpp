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
#include <trial/dynamic/boost/optional.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// boost::optional -> dynamic::variable
//-----------------------------------------------------------------------------

namespace from_suite
{

void convert_null()
{
    boost::optional<int> value;
    variable result = convert<variable>(value);
    TRIAL_PROTOCOL_TEST(result.is<nullable>());
}

void convert_boolean()
{
    boost::optional<bool> value = true;
    variable result = convert<variable>(value);
    TRIAL_PROTOCOL_TEST(result.is<bool>());
    TRIAL_PROTOCOL_TEST_EQUAL(result.value<bool>(), true);
}

void convert_integer()
{
    {
        using integer_type = signed char;
        boost::optional<integer_type> value = 2;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2);
    }
    {
        using integer_type = unsigned char;
        boost::optional<integer_type> value = 2U;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2U);
    }
    {
        using integer_type = signed short int;
        boost::optional<integer_type> value = 2;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2);
    }
    {
        using integer_type = unsigned short int;
        boost::optional<integer_type> value = 2U;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2U);
    }
    {
        using integer_type = signed int;
        boost::optional<integer_type> value = 2;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2);
    }
    {
        using integer_type = unsigned int;
        boost::optional<integer_type> value = 2U;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2U);
    }
    {
        using integer_type = signed long int;
        boost::optional<integer_type> value = 2L;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2L);
    }
    {
        using integer_type = unsigned long int;
        boost::optional<integer_type> value = 2UL;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2UL);
    }
    {
        using integer_type = signed long long int;
        boost::optional<integer_type> value = 2LL;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2LL);
    }
    {
        using integer_type = unsigned long long int;
        boost::optional<integer_type> value = 2ULL;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<integer_type>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<integer_type>(), 2ULL);
    }
}

void convert_real()
{
    // float
    {
        boost::optional<float> value = 3.0f;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<float>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<float>(), 3.0f);
    }
    // double
    {
        boost::optional<double> value = 3.0;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<double>(), 3.0);
    }
    // long double
    {
        boost::optional<long double> value = 3.0L;
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.same<long double>());
        TRIAL_PROTOCOL_TEST_EQUAL(result.value<long double>(), 3.0L);
    }
}

void convert_string()
{
    {
        boost::optional<std::string> value{"alpha"};
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.is<string>());
        TRIAL_PROTOCOL_TEST(result.value<string>() == "alpha");
    }
    {
        boost::optional<std::wstring> value{L"bravo"};
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.is<wstring>());
        TRIAL_PROTOCOL_TEST(result.value<wstring>() == L"bravo");
    }
    {
        boost::optional<std::u16string> value{u"charlie"};
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.is<u16string>());
        TRIAL_PROTOCOL_TEST(result.value<u16string>() == u"charlie");
    }
    {
        boost::optional<std::u32string> value{U"delta"};
        variable result = convert<variable>(value);
        TRIAL_PROTOCOL_TEST(result.is<u32string>());
        TRIAL_PROTOCOL_TEST(result.value<u32string>() == U"delta");
    }
}

void run()
{
    convert_null();
    convert_boolean();
    convert_integer();
    convert_real();
    convert_string();
}

} // namespace from_suite

//-----------------------------------------------------------------------------
// dynamic::variable -> boost::optional
//-----------------------------------------------------------------------------

namespace to_suite
{

void convert_null()
{
    variable data;
    auto result = convert<boost::optional<int>>(data);
    TRIAL_PROTOCOL_TEST(!result);
}

void convert_boolean()
{
    variable data = true;
    auto result = convert<boost::optional<bool>>(data);
    TRIAL_PROTOCOL_TEST(result);
    TRIAL_PROTOCOL_TEST(result == true);
}

void convert_integer()
{
    {
        using integer_type = signed char;
        integer_type value = 2;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = unsigned char;
        integer_type value = 2U;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = signed short int;
        integer_type value = 2;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = unsigned short int;
        integer_type value = 2U;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = signed int;
        integer_type value = 2;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = unsigned int;
        integer_type value = 2U;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = signed long int;
        integer_type value = 2L;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = unsigned long int;
        integer_type value = 2UL;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = signed long long int;
        integer_type value = 2LL;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
    {
        using integer_type = unsigned long long int;
        integer_type value = 2ULL;
        variable data = value;
        auto result = convert<boost::optional<integer_type>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == value);
    }
}

void convert_real()
{
    // float - float
    {
        variable data = 3.0f;
        auto result = convert<boost::optional<float>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0f);
    }
    // float - double
    {
        variable data = 3.0f;
        auto result = convert<boost::optional<double>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0);
    }
    // float - long double
    {
        variable data = 3.0f;
        auto result = convert<boost::optional<long double>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0L);
    }
    // double - float
    {
        variable data = 3.0;
        auto result = convert<boost::optional<float>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0f);
    }
    // double - double
    {
        variable data = 3.0;
        auto result = convert<boost::optional<double>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0);
    }
    // double - long double
    {
        variable data = 3.0;
        auto result = convert<boost::optional<long double>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0L);
    }
    // long double - float
    {
        variable data = 3.0L;
        auto result = convert<boost::optional<float>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0f);
    }
    // long double - double
    {
        variable data = 3.0L;
        auto result = convert<boost::optional<double>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0);
    }
    // long double - long double
    {
        variable data = 3.0L;
        auto result = convert<boost::optional<long double>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == 3.0L);
    }
}

void convert_string()
{
    {
        variable data = "alpha";
        auto result = convert<boost::optional<std::string>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == std::string("alpha"));
    }
    {
        variable data = L"bravo";
        auto result = convert<boost::optional<std::wstring>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == std::wstring(L"bravo"));
    }
    {
        variable data = u"charlie";
        auto result = convert<boost::optional<std::u16string>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == std::u16string(u"charlie"));
    }
    {
        variable data = U"delta";
        auto result = convert<boost::optional<std::u32string>>(data);
        TRIAL_PROTOCOL_TEST(result);
        TRIAL_PROTOCOL_TEST(result == std::u32string(U"delta"));
    }
}

void fail_boolean()
{
    {
        variable data = true;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<boost::optional<int>>(data),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = true;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<boost::optional<float>>(data),
                                        error,
                                        "incompatible type");
    }
    {
        variable data = true;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<boost::optional<std::string>>(data),
                                        error,
                                        "incompatible type");
    }
}

void run()
{
    convert_null();
    convert_boolean();
    convert_integer();
    convert_real();
    convert_string();

    fail_boolean();
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
