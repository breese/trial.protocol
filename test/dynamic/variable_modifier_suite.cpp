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
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// Clear
//-----------------------------------------------------------------------------

namespace clear_suite
{

void clear_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void clear_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool{});
}

void clear_integer()
{
    {
        signed char value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), 0);
    }
    {
        unsigned char value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), 0U);
    }
    {
        signed short int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), 0);
    }
    {
        unsigned short int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), 0U);
    }
    {
        signed int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        unsigned int value = 1;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        signed long int value = 1L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), 0L);
    }
    {
        unsigned long int value = 1UL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), 0UL);
    }
    {
        signed long long int value = 1LL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), 0LL);
    }
    {
        unsigned long long int value = 1ULL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), 0ULL);
    }
}

void clear_real()
{
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data.clear();
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    }
}

void clear_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST(data == "");
}

void clear_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    TRIAL_PROTOCOL_TEST(data == L"");
}

void clear_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    TRIAL_PROTOCOL_TEST(data == u"");
}

void clear_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<u32string>(), true);
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<u32string>(), true);
    TRIAL_PROTOCOL_TEST(data == U"");
}

void clear_array()
{
    variable data = array::make({ 1, 2 });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void clear_map()
{
    variable data = map::make({ {"alpha", 1} });
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    TRIAL_PROTOCOL_TEST(!data.empty());
    data.clear();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    TRIAL_PROTOCOL_TEST(data.empty());
}

void run()
{
    clear_null();
    clear_boolean();
    clear_integer();
    clear_real();
    clear_string();
    clear_wstring();
    clear_u16string();
    clear_u32string();
    clear_array();
    clear_map();
}

} // namespace clear_suite

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------

namespace insert_suite
{

void insert_null()
{
    // null - null
    {
        variable data;
        auto where = data.insert(null);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - boolean
    {
        variable data;
        auto where = data.insert(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - integer
    {
        variable data;
        auto where = data.insert(2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - real
    {
        variable data;
        auto where = data.insert(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == 3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - string
    {
        variable data;
        auto where = data.insert("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == "alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - wstring
    {
        variable data;
        auto where = data.insert(L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == L"bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - u16string
    {
        variable data;
        auto where = data.insert(u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == u"charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - u32string
    {
        variable data;
        auto where = data.insert(U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == U"delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - array
    {
        variable data;
        auto where = data.insert(array::make({ 1, 20, 300 }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == array::make({ 1, 20, 300 }));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // null - map
    {
        variable data;
        auto where = data.insert(map::make("alpha", true));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == map::make("alpha", true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
}

void insert_null_range()
{
    std::vector<int> input = { 1, 20, 300 };
    variable data;
    TRIAL_PROTOCOL_TEST_NO_THROW(data.insert(input.begin(), input.end()));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    TRIAL_PROTOCOL_TEST(data[0] == 1);
    TRIAL_PROTOCOL_TEST(data[1] == 20);
    TRIAL_PROTOCOL_TEST(data[2] == 300);
}

void fail_null()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                        error,
                                        "incompatible type");
    }
    {
        std::vector<int> input = { 1, 20, 300 };
        variable data;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
}

void fail_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(true),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                    error,
                                    "incompatible type");

    variable array = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(array.begin(), array.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), array.begin(), array.end()),
                                    error,
                                    "incompatible type");

    variable map =
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(map.begin(), map.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), map.begin(), map.end()),
                                    error,
                                    "incompatible type");
}

void fail_integer()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(true),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                    error,
                                    "incompatible type");

    variable array = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(array.begin(), array.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), array.begin(), array.end()),
                                    error,
                                    "incompatible type");

    variable map =
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(map.begin(), map.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), map.begin(), map.end()),
                                    error,
                                    "incompatible type");
}

void fail_real()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(true),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                    error,
                                    "incompatible type");

    variable array = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(array.begin(), array.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), array.begin(), array.end()),
                                    error,
                                    "incompatible type");

    variable map =
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(map.begin(), map.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), map.begin(), map.end()),
                                    error,
                                    "incompatible type");
}

void fail_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(true),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                    error,
                                    "incompatible type");

    variable array = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(array.begin(), array.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), array.begin(), array.end()),
                                    error,
                                    "incompatible type");

    variable map =
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(map.begin(), map.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), map.begin(), map.end()),
                                    error,
                                    "incompatible type");
}

void fail_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(true),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                    error,
                                    "incompatible type");

    variable array = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(array.begin(), array.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), array.begin(), array.end()),
                                    error,
                                    "incompatible type");

    variable map =
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(map.begin(), map.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), map.begin(), map.end()),
                                    error,
                                    "incompatible type");
}

void fail_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(true),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                    error,
                                    "incompatible type");

    variable array = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(array.begin(), array.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), array.begin(), array.end()),
                                    error,
                                    "incompatible type");

    variable map =
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(map.begin(), map.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), map.begin(), map.end()),
                                    error,
                                    "incompatible type");
}

void fail_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(true),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.begin(), true),
                                    error,
                                    "incompatible type");

    variable array = { true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(array.begin(), array.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), array.begin(), array.end()),
                                    error,
                                    "incompatible type");

    variable map =
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(map.begin(), map.end()),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), map.begin(), map.end()),
                                    error,
                                    "incompatible type");
}

void insert_array()
{
    variable data = array::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    auto where = data.insert(null);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    TRIAL_PROTOCOL_TEST(data[0] == null);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    where = data.insert(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    TRIAL_PROTOCOL_TEST(data[0] == null);
    TRIAL_PROTOCOL_TEST(data[1] == true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    where = data.insert(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    TRIAL_PROTOCOL_TEST(data[0] == null);
    TRIAL_PROTOCOL_TEST(data[1] == true);
    TRIAL_PROTOCOL_TEST(data[2] == 2);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
}

void insert_array_iterator()
{
    {
        // Inserts at beginning
        variable data = array::make();
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
        auto where = data.insert(data.begin(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
        where = data.insert(data.begin(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
        TRIAL_PROTOCOL_TEST(data[0] == true);
        TRIAL_PROTOCOL_TEST(data[1] == null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
        where = data.insert(data.begin(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
        TRIAL_PROTOCOL_TEST(data[0] == 2);
        TRIAL_PROTOCOL_TEST(data[1] == true);
        TRIAL_PROTOCOL_TEST(data[2] == null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        // Inserts at end
        variable data = array::make();
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
        auto where = data.insert(data.end(), null);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST(data[0] == null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
        where = data.insert(data.end(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
        TRIAL_PROTOCOL_TEST(data[0] == null);
        TRIAL_PROTOCOL_TEST(data[1] == true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        where = data.insert(data.end(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
        TRIAL_PROTOCOL_TEST(data[0] == null);
        TRIAL_PROTOCOL_TEST(data[1] == true);
        TRIAL_PROTOCOL_TEST(data[2] == 2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
}

void insert_array_range()
{
    // null variable
    {
        variable data = array::make();
        variable input = null;
        data.insert(input.begin(), input.end());
        TRIAL_PROTOCOL_TEST(data.empty());
    }
    // boolean variable
    {
        variable data = array::make();
        variable input = true;
        data.insert(input.begin(), input.end());

        variable expect = array::make({ true });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // integer variable
    {
        variable data = array::make();
        variable input = 2;
        data.insert(input.begin(), input.end());

        variable expect = array::make({ 2 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // real variable
    {
        variable data = array::make();
        variable input = 3.0;
        data.insert(input.begin(), input.end());

        variable expect = array::make({ 3.0 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // string variable
    {
        variable data = array::make();
        variable input = "alpha";
        data.insert(input.begin(), input.end());

        variable expect = array::make({ "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // wstring variable
    {
        variable data = array::make();
        variable input = L"bravo";
        data.insert(input.begin(), input.end());

        variable expect = array::make({ L"bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // u16string variable
    {
        variable data = array::make();
        variable input = u"charlie";
        data.insert(input.begin(), input.end());

        variable expect = array::make({ u"charlie" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // u32string variable
    {
        variable data = array::make();
        variable input = U"delta";
        data.insert(input.begin(), input.end());

        variable expect = array::make({ U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // array variable
    {
        variable data = array::make();
        variable input = { null, true, 2, 3.0, "alpha" };
        data.insert(input.begin(), input.end());

        variable expect = array::make({ null, true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // vector<variable>
    {
        variable data = array::make();
        std::vector<variable> input = { null, true, 2, 3.0, "alpha" };
        data.insert(input.begin(), input.end());

        variable expect = array::make({ null, true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // vector<int>
    {
        variable data = array::make();
        std::vector<int> input = { 0, 1, 2, 3, 4 };
        data.insert(input.begin(), input.end());

        variable expect = array::make({ 0, 1, 2, 3, 4 });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void fail_array_range()
{
    variable data = array::make();
    std::map<std::string, int> input = { { "alpha", 1 }, { "bravo", 2 } };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                    error,
                                    "incompatible type");
}

void insert_array_range_iterator()
{
    // Inserts at beginning
    {
        variable data = array::make({ null });
        variable input = { true, 2, 3.0, "alpha" };
        data.insert(data.begin(), input.begin(), input.end());

        variable expect = array::make({ true, 2, 3.0, "alpha", null });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // Inserts at end
    {
        variable data = array::make({ null });
        variable input = { true, 2, 3.0, "alpha" };
        data.insert(data.end(), input.begin(), input.end());

        variable expect = array::make({ null, true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void insert_map()
{
    variable data = map::make();
    auto where = data.insert({"alpha", "hydrogen"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    TRIAL_PROTOCOL_TEST(data["alpha"] == "hydrogen");
    TRIAL_PROTOCOL_TEST(where.key() == "alpha");
    where = data.insert({"bravo", "helium"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    TRIAL_PROTOCOL_TEST(data["bravo"] == "helium");
    TRIAL_PROTOCOL_TEST(where.key() == "bravo");
}

void fail_map()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert("alpha"),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert({ "alpha" }),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert({ "alpha", "bravo", "charlie" }),
                                    error,
                                    "incompatible type");
}

void insert_map_iterator()
{
    variable data = map::make();
    auto where = data.insert(data.end(), {"alpha", "hydrogen"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
    TRIAL_PROTOCOL_TEST(data["alpha"] == "hydrogen");
    TRIAL_PROTOCOL_TEST(where.key() == "alpha");
    where = data.insert(data.end(), {"bravo", "helium"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
    TRIAL_PROTOCOL_TEST(data["bravo"] == "helium");
    TRIAL_PROTOCOL_TEST(where.key() == "bravo");
}

void fail_map_iterator()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), "alpha"),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), { "alpha" }),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(data.end(), { "alpha", "bravo", "charlie" }),
                                    error,
                                    "incompatible type");
}

void insert_map_range()
{
    variable data = map::make();
    std::map<std::string, int> input = {{ "alpha", 1 }, { "bravo", 2 }};
    data.insert(input.begin(), input.end());

    variable expect = map::make({ { "alpha", 1 }, { "bravo", 2 } });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void fail_map_range()
{
    // null variable
    {
        variable data = map::make();
        variable input;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // boolean variable
    {
        variable data = map::make();
        variable input = true;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // integer variable
    {
        variable data = map::make();
        variable input = 2;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // real variable
    {
        variable data = map::make();
        variable input = 3.0;
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // string variable
    {
        variable data = map::make();
        variable input = "alpha";
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // wstring variable
    {
        variable data = map::make();
        variable input = L"bravo";
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // u16string variable
    {
        variable data = map::make();
        variable input = u"charlie";
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // u32string variable
    {
        variable data = map::make();
        variable input = U"delta";
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // array variable
    {
        variable data = map::make();
        variable input = { null, true, 2, 3.0, "alpha" };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
    // vector<int>
    {
        variable data = map::make();
        std::vector<int> input = { 0, 1, 2, 3, 4 };
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(data.insert(input.begin(), input.end()),
                                        error,
                                        "incompatible type");
    }
}

void insert_map_range_iterator()
{
    // Inserts at beginning
    {
        variable data = map::make();
        std::map<std::string, int> input = {{ "alpha", 1 }, { "bravo", 2 }};
        data.insert(data.begin(), input.begin(), input.end());

        variable expect = map::make({ { "alpha", 1 }, { "bravo", 2 } });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // Inserts at end
    {
        variable data = map::make();
        std::map<std::string, int> input = {{ "alpha", 1 }, { "bravo", 2 }};
        data.insert(data.end(), input.begin(), input.end());

        variable expect = map::make({ { "alpha", 1 }, { "bravo", 2 } });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void run()
{
    insert_null();
    insert_null_range();
    fail_null();
    fail_boolean();
    fail_integer();
    fail_real();
    fail_string();
    fail_wstring();
    fail_u16string();
    fail_u32string();

    insert_array();
    insert_array_iterator();
    insert_array_range();
    fail_array_range();
    insert_array_range_iterator();

    insert_map();
    fail_map();
    insert_map_iterator();
    fail_map_iterator();
    insert_map_range();
    fail_map_range();
    insert_map_range_iterator();
}

} // namespace insert_suite

//-----------------------------------------------------------------------------
// Erase
//-----------------------------------------------------------------------------

namespace erase_suite
{

void erase_null()
{
    {
        variable data;
        variable::iterator where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == null);
    }
    {
        variable data;
        variable::iterator where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == null);
    }
}

void erase_boolean()
{
    {
        variable data(true);
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == true);
    }
    {
        variable data(true);
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == true);
    }
}

void erase_integer()
{
    {
        variable data(2);
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
    {
        variable data(2);
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 2);
    }
}

void erase_real()
{
    // float
    {
        variable data(3.0f);
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0f);
    }
    {
        variable data(3.0f);
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0f);
    }
    // double
    {
        variable data(3.0);
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    {
        variable data(3.0);
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    // long double
    {
        variable data(3.0L);
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0L);
    }
    {
        variable data(3.0L);
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0L);
    }
}

void erase_string()
{
    {
        variable data("alpha");
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
    {
        variable data("alpha");
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == "alpha");
    }
}

void erase_wstring()
{
    {
        variable data(L"bravo");
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
    {
        variable data(L"bravo");
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == L"bravo");
    }
}

void erase_u16string()
{
    {
        variable data(u"charlie");
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
    {
        variable data(u"charlie");
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == u"charlie");
    }
}

void erase_u32string()
{
    {
        variable data(U"delta");
        auto where = data.erase(data.begin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
    {
        variable data(U"delta");
        auto where = data.erase(data.cbegin());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == U"delta");
    }
}

void erase_array_first()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(data.begin());
        variable expect = array::make({ 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(data.cbegin());
        variable expect = array::make({ 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void erase_array_second()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.begin()));
        variable expect = array::make({ true, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.cbegin()));
        variable expect = array::make({ true, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void erase_array_third()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.begin(), 2));
        variable expect = array::make({ true, 2, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.cbegin(), 2));
        variable expect = array::make({ true, 2, "alpha", L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void erase_array_fourth()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.begin(), 3));
        variable expect = array::make({ true, 2, 3.0, L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.cbegin(), 3));
        variable expect = array::make({ true, 2, 3.0, L"bravo", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void erase_array_fifth()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.begin(), 4));
        variable expect = array::make({ true, 2, 3.0, "alpha", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.cbegin(), 4));
        variable expect = array::make({ true, 2, 3.0, "alpha", u"charlie", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void erase_array_sixth()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.begin(), 5));
        variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.cbegin(), 5));
        variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", U"delta" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void erase_array_seventh()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.begin(), 6));
        variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        auto where = data.erase(std::next(data.cbegin(), 6));
        variable expect = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void erase_array_all()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = data.erase(data.begin());
    variable expect = array::make({ 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make({ 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make({ "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make({ L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make({ u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make({ U"delta" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = array::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_map_all()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    auto where = data.erase(data.begin());
    variable expect = map::make(
        {
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = map::make(
        {
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = map::make(
        {
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    where = data.erase(where);
    expect = map::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_null()
{
    variable data;
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == null);
}

void erase_range_boolean()
{
    variable data(true);
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == true);
}

void erase_range_integer()
{
    variable data(2);
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == 2);
}

void erase_range_real()
{
    {
        variable data(3.0f);
        auto where = data.erase(data.begin(), data.end());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0f);
    }
    {
        variable data(3.0);
        auto where = data.erase(data.begin(), data.end());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0);
    }
    {
        variable data(3.0L);
        auto where = data.erase(data.begin(), data.end());
        TRIAL_PROTOCOL_TEST(where == data.begin());
        TRIAL_PROTOCOL_TEST(data == 3.0L);
    }
}

void erase_range_string()
{
    variable data("alpha");
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == "alpha");
}

void erase_range_wstring()
{
    variable data(L"bravo");
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == L"bravo");
}

void erase_range_u16string()
{
    variable data(u"charlie");
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == u"charlie");
}

void erase_range_u32string()
{
    variable data(U"delta");
    auto where = data.erase(data.begin(), data.end());
    TRIAL_PROTOCOL_TEST(where == data.begin());
    TRIAL_PROTOCOL_TEST(data == U"delta");
}

void erase_range_array_first_first()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), data.begin());
    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_second()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), ++data.begin());
    variable expect = array::make({ 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_third()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), ++(++data.begin()));
    variable expect = array::make({ 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_fourth()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), ++(++(++data.begin())));
    variable expect = array::make({ "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_first_last()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(data.begin(), data.end());
    variable expect = array::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_array_second_fourth()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.erase(++data.begin(), ++(++(++data.begin())));
    variable expect = array::make({ true, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_first()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), data.begin());
    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_second()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), ++data.begin());
    variable expect = map::make(
        {
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_third()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), ++(++data.begin()));
    variable expect = map::make(
        {
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_fourth()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), ++(++(++data.begin())));
    variable expect = map::make(
        {
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_first_last()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(data.begin(), data.end());
    variable expect = map::make();
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void erase_range_map_second_fourth()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });

    data.erase(++data.begin(), ++(++(++data.begin())));
    variable expect = map::make(
        {
            { "alpha", true },
            { "delta", "beryllium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    erase_null();
    erase_boolean();
    erase_integer();
    erase_real();
    erase_string();
    erase_wstring();
    erase_u16string();
    erase_u32string();
    erase_array_first();
    erase_array_second();
    erase_array_third();
    erase_array_fourth();
    erase_array_fifth();
    erase_array_sixth();
    erase_array_seventh();
    erase_array_all();
    erase_map_all();

    erase_range_null();
    erase_range_boolean();
    erase_range_integer();
    erase_range_real();
    erase_range_string();
    erase_range_wstring();
    erase_range_u16string();
    erase_range_u32string();
    erase_range_array_first_first();
    erase_range_array_first_second();
    erase_range_array_first_third();
    erase_range_array_first_fourth();
    erase_range_array_first_last();
    erase_range_array_second_fourth();
    erase_range_map_first_first();
    erase_range_map_first_second();
    erase_range_map_first_third();
    erase_range_map_first_fourth();
    erase_range_map_first_last();
    erase_range_map_second_fourth();
}

} // namespace erase_suite

//-----------------------------------------------------------------------------
// Swap
//-----------------------------------------------------------------------------

namespace swap_suite
{

void swap_null()
{
    // null - null
    {
        variable data;
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
    }
    // null - boolean
    {
        variable data;
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // null - integer
    {
        variable data;
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // null - real
    {
        variable data;
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // null - string
    {
        variable data;
        variable other("alpha");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "alpha");
    }
    // null - wstring
    {
        variable data;
        variable other(L"bravo");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"bravo");
    }
    // null - u16string
    {
        variable data;
        variable other(u"charlie");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"charlie");
    }
    // null - u32string
    {
        variable data;
        variable other(U"delta");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());
        TRIAL_PROTOCOL_TEST(data.value<std::u32string>() == U"delta");
    }
    // null - array
    {
        variable data;
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // null - map
    {
        variable data;
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<nullable>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_boolean()
{
    // boolean - null
    {
        variable data(true);
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
    }
    // boolean - boolean
    {
        variable data(true);
        variable other(false);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == false);
    }
    // boolean - integer
    {
        variable data(true);
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // boolean - real
    {
        variable data(true);
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // boolean - string
    {
        variable data(true);
        variable other("alpha");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "alpha");
    }
    // boolean - wstring
    {
        variable data(true);
        variable other(L"bravo");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"bravo");
    }
    // boolean - u16string
    {
        variable data(true);
        variable other(u"charlie");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"charlie");
    }
    // boolean - u32string
    {
        variable data(true);
        variable other(U"delta");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());
        TRIAL_PROTOCOL_TEST(data.value<std::u32string>() == U"delta");
    }
    // boolean - array
    {
        variable data(true);
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // boolean - map
    {
        variable data(true);
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<boolean>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_integer()
{
    // integer - null
    {
        variable data(2);
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
    }
    // integer - boolean
    {
        variable data(2);
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // integer - integer
    {
        variable data(2);
        variable other(20);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 20);
    }
    // integer - real
    {
        variable data(2);
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // integer - string
    {
        variable data(2);
        variable other("alpha");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "alpha");
    }
    // integer - wstring
    {
        variable data(2);
        variable other(L"bravo");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"bravo");
    }
    // integer - u16string
    {
        variable data(2);
        variable other(u"charlie");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"charlie");
    }
    // integer - u32string
    {
        variable data(2);
        variable other(U"delta");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());
        TRIAL_PROTOCOL_TEST(data.value<std::u32string>() == U"delta");
    }
    // integer - array
    {
        variable data(2);
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // integer - map
    {
        variable data(2);
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<integer>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_real()
{
    // real - null
    {
        variable data(3.0);
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
    }
    // real - boolean
    {
        variable data(3.0);
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // real - integer
    {
        variable data(3.0);
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // real - real
    {
        variable data(3.0);
        variable other(300.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 300.0);
    }
    // real - string
    {
        variable data(3.0);
        variable other("alpha");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "alpha");
    }
    // real - wstring
    {
        variable data(3.0);
        variable other(L"bravo");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"bravo");
    }
    // real - u16string
    {
        variable data(3.0);
        variable other(u"charlie");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"charlie");
    }
    // real - u32string
    {
        variable data(3.0);
        variable other(U"delta");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<real>());
        TRIAL_PROTOCOL_TEST(data.value<std::u32string>() == U"delta");
    }
    // real - array
    {
        variable data(3.0);
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<real>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // real - map
    {
        variable data(3.0);
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<real>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_string()
{
    // string - null
    {
        variable data("alpha");
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
    }
    // string - boolean
    {
        variable data("alpha");
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // string - integer
    {
        variable data("alpha");
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // string - real
    {
        variable data("alpha");
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // string - string
    {
        variable data("alpha");
        variable other("zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "zulu");
    }
    // string - wstring
    {
        variable data("alpha");
        variable other(L"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"zulu");
    }
    // string - u16string
    {
        variable data("alpha");
        variable other(u"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"zulu");
    }
    // string - u32string
    {
        variable data("alpha");
        variable other(U"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<string>());
        TRIAL_PROTOCOL_TEST(data.value<std::u32string>() == U"zulu");
    }
    // string - array
    {
        variable data("alpha");
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<string>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // string - map
    {
        variable data("alpha");
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<string>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_wstring()
{
    // wstring - null
    {
        variable data(L"bravo");
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
    }
    // wstring - boolean
    {
        variable data(L"bravo");
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // wstring - integer
    {
        variable data(L"bravo");
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // wstring - real
    {
        variable data(L"bravo");
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // wstring - string
    {
        variable data(L"bravo");
        variable other("zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "zulu");
    }
    // wstring - wstring
    {
        variable data(L"bravo");
        variable other(L"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"zulu");
    }
    // wstring - u16string
    {
        variable data(L"bravo");
        variable other(u"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"zulu");
    }
    // wstring - u32string
    {
        variable data(L"bravo");
        variable other(U"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());
        TRIAL_PROTOCOL_TEST(data.value<std::u32string>() == U"zulu");
    }
    // wstring - array
    {
        variable data(L"bravo");
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // wstring - map
    {
        variable data(L"bravo");
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<wstring>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_u16string()
{
    // u16string - null
    {
        variable data(u"charlie");
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
    }
    // u16string - boolean
    {
        variable data(u"charlie");
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // u16string - integer
    {
        variable data(u"charlie");
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // u16string - real
    {
        variable data(u"charlie");
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // u16string - string
    {
        variable data(u"charlie");
        variable other("zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "zulu");
    }
    // u16string - wstring
    {
        variable data(u"charlie");
        variable other(L"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"zulu");
    }
    // u16string - u16string
    {
        variable data(u"charlie");
        variable other(u"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"zulu");
    }
    // u16string - u32string
    {
        variable data(u"charlie");
        variable other(U"zulu");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());
        TRIAL_PROTOCOL_TEST(data.value<std::u32string>() == U"zulu");
    }
    // u16string - array
    {
        variable data(u"charlie");
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // u16string - map
    {
        variable data(u"charlie");
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<u16string>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_array()
{
    // array - null
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
    }
    // array - boolean
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // array - integer
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // array - real
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // array - string
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other("alpha");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "alpha");
    }
    // array - wstring
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other(L"bravo");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<wstring>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
        TRIAL_PROTOCOL_TEST(data.value<wstring>() == L"bravo");
    }
    // array - u16string
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other(u"charlie");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u16string>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
        TRIAL_PROTOCOL_TEST(data.value<u16string>() == u"charlie");
    }
    // array - u32string
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other(U"delta");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<u32string>());
        TRIAL_PROTOCOL_TEST(other.is<array>());
        TRIAL_PROTOCOL_TEST(data.value<u32string>() == U"delta");
    }
    // array - array
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other = { false, 1, 2.0, "bravo" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<array>());

        variable expect = array::make({ false, 1, 2.0, "bravo" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // array - map
    {
        variable data = { true, 2, 3.0, "alpha" };
        variable other = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<array>());

        variable expect = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void swap_map()
{
    // map - null
    {
        variable data = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        variable other;

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<nullable>());
        TRIAL_PROTOCOL_TEST(other.is<map>());
    }
    // map - boolean
    {
        variable data = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        variable other(true);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<boolean>());
        TRIAL_PROTOCOL_TEST(other.is<map>());
        TRIAL_PROTOCOL_TEST(data.value<boolean>() == true);
    }
    // map - integer
    {
        variable data = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        variable other(2);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<integer>());
        TRIAL_PROTOCOL_TEST(other.is<map>());
        TRIAL_PROTOCOL_TEST(data.value<integer>() == 2);
    }
    // map - real
    {
        variable data = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        variable other(3.0);

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<real>());
        TRIAL_PROTOCOL_TEST(other.is<map>());
        TRIAL_PROTOCOL_TEST(data.value<real>() == 3.0);
    }
    // map - string
    {
        variable data = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        variable other("alpha");

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<string>());
        TRIAL_PROTOCOL_TEST(other.is<map>());
        TRIAL_PROTOCOL_TEST(data.value<string>() == "alpha");
    }
    // map - array
    {
        variable data = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        variable other = { true, 2, 3.0, "alpha" };

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<array>());
        TRIAL_PROTOCOL_TEST(other.is<map>());

        variable expect = array::make({ true, 2, 3.0, "alpha" });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
    // map - map
    {
        variable data = map::make(
            {
                { "alpha", true },
                { "bravo", 2 },
                { "charlie", 3.0 },
                { "delta", "beryllium" }
            });
        variable other = map::make(
            {
                { "echo", true },
                { "foxtrot", 2 },
                { "golf", 3.0 },
                { "hotel", "beryllium" }
            });

        data.swap(other);
        TRIAL_PROTOCOL_TEST(data.is<map>());
        TRIAL_PROTOCOL_TEST(other.is<map>());

        variable expect = map::make(
            {
                { "echo", true },
                { "foxtrot", 2 },
                { "golf", 3.0 },
                { "hotel", "beryllium" }
            });
        TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                     expect.begin(), expect.end(),
                                     std::equal_to<variable>());
    }
}

void run()
{
    swap_null();
    swap_boolean();
    swap_integer();
    swap_real();
    swap_string();
    swap_wstring();
    swap_u16string();
    swap_array();
    swap_map();
}

} // namespace swap_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    clear_suite::run();
    insert_suite::run();
    erase_suite::run();
    swap_suite::run();

    return boost::report_errors();
}
