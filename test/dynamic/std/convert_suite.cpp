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
#include <trial/protocol/dynamic/std/map.hpp>
#include <trial/protocol/dynamic/std/vector.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// std::vector
//-----------------------------------------------------------------------------

namespace vector_suite
{

void from_vector_int()
{
    std::vector<int> input = { 1, 2, 3, 4 };
    variable result = convert<variable>(input);

    variable expect = array::make({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_vector_int()
{
    variable input = { 1, 2, 3, 4 };
    auto result = convert<std::vector<int>>(input);

    std::vector<int> expect = { 1, 2, 3, 4 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_vector_double()
{
    std::vector<double> input = { 1.0, 2.0, 3.0, 4.0 };
    variable result = convert<variable>(input);

    variable expect = array::make({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_vector_double()
{
    variable input = { 1.0, 2.0, 3.0, 4.0 };
    auto result = convert<std::vector<double>>(input);

    std::vector<double> expect = { 1.0, 2.0, 3.0, 4.0 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_vector_string()
{
    std::vector<std::string> input = { "alpha", "bravo" };
    variable result = convert<variable>(input);

    variable expect = array::make({ "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_vector_string()
{
    variable input = { "alpha", "bravo" };
    auto result = convert<std::vector<std::string>>(input);

    std::vector<std::string> expect = { "alpha", "bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_vector_wstring()
{
    std::vector<std::wstring> input = { L"alpha", L"bravo" };
    variable result = convert<variable>(input);

    variable expect = array::make({ L"alpha", L"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_vector_wstring()
{
    variable input = { L"alpha", L"bravo" };
    auto result = convert<std::vector<std::wstring>>(input);

    std::vector<std::wstring> expect = { L"alpha", L"bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_vector_u16string()
{
    std::vector<std::u16string> input = { u"alpha", u"bravo" };
    variable result = convert<variable>(input);

    variable expect = array::make({ u"alpha", u"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_vector_u16string()
{
    variable input = { u"alpha", u"bravo" };
    auto result = convert<std::vector<std::u16string>>(input);

    std::vector<std::u16string> expect = { u"alpha", u"bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void from_vector_u32string()
{
    std::vector<std::u32string> input = { U"alpha", U"bravo" };
    variable result = convert<variable>(input);

    variable expect = array::make({ U"alpha", U"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void to_vector_u32string()
{
    variable input = { U"alpha", U"bravo" };
    auto result = convert<std::vector<std::u32string>>(input);

    std::vector<std::u32string> expect = { U"alpha", U"bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void to_vector_variable()
{
    variable input = { null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" };
    auto result = convert<std::vector<variable>>(input);

    std::vector<variable> expect = { null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void fail_to_vector_mixed()
{
    variable input = { null, true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<std::vector<int>>(input),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<std::vector<double>>(input),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert<std::vector<std::string>>(input),
                                    error,
                                    "incompatible type");
}

void run()
{
    from_vector_int();
    to_vector_int();
    from_vector_double();
    to_vector_double();
    from_vector_string();
    to_vector_string();
    from_vector_wstring();
    to_vector_wstring();
    from_vector_u16string();
    to_vector_u16string();
    from_vector_u32string();
    to_vector_u32string();

    to_vector_variable();

    fail_to_vector_mixed();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// std::map
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
    variable result = convert<variable>(input);

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
    auto result = convert<std::map<int, int>>(input);

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
    variable result = convert<variable>(input);

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
    auto result = convert<std::map<std::string, int>>(input);

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
    variable result = convert<variable>(input);

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
    auto result = convert<std::map<std::string, std::string>>(input);

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
    variable result = convert<variable>(input);

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
    auto result = convert<std::map<std::string, std::wstring>>(input);

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
    variable result = convert<variable>(input);

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
    auto result = convert<std::map<std::string, std::u16string>>(input);

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
    variable result = convert<variable>(input);

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
    auto result = convert<std::map<std::string, std::u32string>>(input);

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
    auto result = convert<std::map<std::string, variable>>(input);

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
    TRIAL_PROTOCOL_TEST_THROW_EQUAL((convert<std::map<int, int>>(input)),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL((convert<std::map<std::string, int>>(input)),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL((convert<std::map<std::string, std::string>>(input)),
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
    vector_suite::run();
    map_suite::run();

    return boost::report_errors();
}
