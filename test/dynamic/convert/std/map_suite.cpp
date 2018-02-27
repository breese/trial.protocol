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
#include <trial/dynamic/convert/std/map.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------

namespace map_suite
{

void from_map_int_int()
{
    std::map<int, int> input =
        {
            { 1, 2 },
            { 3, 4 }
        };
    variable result = convert::into<variable>(input);

    variable expect = map::make(
        {
            { 1, 2 },
            { 3, 4 }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_map_int_int()
{
    variable input =
        {
            { 1, 2 },
            { 3, 4 }
        };
    auto result = convert::into<std::map<int, int>>(input);

    std::map<int, int> expect =
        {
            { 1, 2 },
            { 3, 4 }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_map_string_int()
{
    std::map<std::string, int> input =
        {
            { "alpha", 2 },
            { "bravo", 4 }
        };
    variable result = convert::into<variable>(input);

    variable expect = map::make(
        {
            { "alpha", 2 },
            { "bravo", 4 }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_map_string_int()
{
    variable input =
        {
            { "alpha", 2 },
            { "bravo", 4 }
        };
    auto result = convert::into<std::map<std::string, int>>(input);

    decltype(result) expect =
        {
            { "alpha", 2 },
            { "bravo", 4 }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_map_string_string()
{
    std::map<std::string, std::string> input =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    variable result = convert::into<variable>(input);

    variable expect = map::make(
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_map_string_string()
{
    variable input =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    auto result = convert::into<std::map<std::string, std::string>>(input);

    decltype(result) expect =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_map_string_wstring()
{
    std::map<std::string, std::wstring> input =
        {
            { "alpha", L"hydrogen" },
            { "bravo", L"helium" }
        };
    variable result = convert::into<variable>(input);

    variable expect = map::make(
        {
            { "alpha", L"hydrogen" },
            { "bravo", L"helium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_map_string_wstring()
{
    variable input =
        {
            { "alpha", L"hydrogen" },
            { "bravo", L"helium" }
        };
    auto result = convert::into<std::map<std::string, std::wstring>>(input);

    decltype(result) expect =
        {
            { "alpha", L"hydrogen" },
            { "bravo", L"helium" }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_map_string_u16string()
{
    std::map<std::string, std::u16string> input =
        {
            { "alpha", u"hydrogen" },
            { "bravo", u"helium" }
        };
    variable result = convert::into<variable>(input);

    variable expect = map::make(
        {
            { "alpha", u"hydrogen" },
            { "bravo", u"helium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_map_string_u16string()
{
    variable input =
        {
            { "alpha", u"hydrogen" },
            { "bravo", u"helium" }
        };
    auto result = convert::into<std::map<std::string, std::u16string>>(input);

    decltype(result) expect =
        {
            { "alpha", u"hydrogen" },
            { "bravo", u"helium" }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_map_string_u32string()
{
    std::map<std::string, std::u32string> input =
        {
            { "alpha", U"hydrogen" },
            { "bravo", U"helium" }
        };
    variable result = convert::into<variable>(input);

    variable expect = map::make(
        {
            { "alpha", U"hydrogen" },
            { "bravo", U"helium" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_map_string_u32string()
{
    variable input =
        {
            { "alpha", U"hydrogen" },
            { "bravo", U"helium" }
        };
    auto result = convert::into<std::map<std::string, std::u32string>>(input);

    decltype(result) expect =
        {
            { "alpha", U"hydrogen" },
            { "bravo", U"helium" }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void to_map_string_variable()
{
    variable input =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    auto result = convert::into<std::map<std::string, variable>>(input);

    decltype(result) expect =
        {
            { "alpha", "hydrogen" },
            { "bravo", "helium" }
        };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void fail_to_map_mixed()
{
    variable input = { null, true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL((convert::into<std::map<int, int>>(input)),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL((convert::into<std::map<std::string, int>>(input)),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL((convert::into<std::map<std::string, std::string>>(input)),
                                    error,
                                    "incompatible type");
}

void run()
{
    from_map_int_int();
    to_map_int_int();
    from_map_string_int();
    to_map_string_int();
    from_map_string_string();
    to_map_string_string();
    from_map_string_wstring();
    to_map_string_wstring();
    from_map_string_u16string();
    to_map_string_u16string();
    from_map_string_u32string();
    to_map_string_u32string();

    to_map_string_variable();

    fail_to_map_mixed();
}

} // namespace map_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    map_suite::run();

    return boost::report_errors();
}
