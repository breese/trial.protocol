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
#include <trial/dynamic/convert/std/vector.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------

namespace from_suite
{

void convert_vector_int()
{
    std::vector<int> input = { 1, 2, 3, 4 };
    variable result = convert::into<variable>(input);

    variable expect = array::make({ 1, 2, 3, 4 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_vector_double()
{
    std::vector<double> input = { 1.0, 2.0, 3.0, 4.0 };
    variable result = convert::into<variable>(input);

    variable expect = array::make({ 1.0, 2.0, 3.0, 4.0 });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_vector_string()
{
    std::vector<std::string> input = { "alpha", "bravo" };
    variable result = convert::into<variable>(input);

    variable expect = array::make({ "alpha", "bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_vector_wstring()
{
    std::vector<std::wstring> input = { L"alpha", L"bravo" };
    variable result = convert::into<variable>(input);

    variable expect = array::make({ L"alpha", L"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_vector_u16string()
{
    std::vector<std::u16string> input = { u"alpha", u"bravo" };
    variable result = convert::into<variable>(input);

    variable expect = array::make({ u"alpha", u"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void convert_vector_u32string()
{
    std::vector<std::u32string> input = { U"alpha", U"bravo" };
    variable result = convert::into<variable>(input);

    variable expect = array::make({ U"alpha", U"bravo" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    convert_vector_int();
    convert_vector_double();
    convert_vector_string();
    convert_vector_wstring();
    convert_vector_u16string();
    convert_vector_u32string();
}

} // namespace from_suite

//-----------------------------------------------------------------------------

namespace to_suite
{

void convert_vector_int()
{
    variable input = { 1, 2, 3, 4 };
    auto result = convert::into<std::vector<int>>(input);

    std::vector<int> expect = { 1, 2, 3, 4 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void convert_vector_double()
{
    variable input = { 1.0, 2.0, 3.0, 4.0 };
    auto result = convert::into<std::vector<double>>(input);

    std::vector<double> expect = { 1.0, 2.0, 3.0, 4.0 };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void convert_vector_string()
{
    variable input = { "alpha", "bravo" };
    auto result = convert::into<std::vector<std::string>>(input);

    std::vector<std::string> expect = { "alpha", "bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void convert_vector_wstring()
{
    variable input = { L"alpha", L"bravo" };
    auto result = convert::into<std::vector<std::wstring>>(input);

    std::vector<std::wstring> expect = { L"alpha", L"bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void convert_vector_u16string()
{
    variable input = { u"alpha", u"bravo" };
    auto result = convert::into<std::vector<std::u16string>>(input);

    std::vector<std::u16string> expect = { u"alpha", u"bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void convert_vector_u32string()
{
    variable input = { U"alpha", U"bravo" };
    auto result = convert::into<std::vector<std::u32string>>(input);

    std::vector<std::u32string> expect = { U"alpha", U"bravo" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<decltype(result)::value_type>());
}

void convert_vector_variable()
{
    variable input = { null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" };
    auto result = convert::into<std::vector<variable>>(input);

    std::vector<variable> expect = { null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" };
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void fail_vector_mixed()
{
    variable input = { null, true, 2, 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert::into<std::vector<int>>(input),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert::into<std::vector<double>>(input),
                                    error,
                                    "incompatible type");
    TRIAL_PROTOCOL_TEST_THROW_EQUAL(convert::into<std::vector<std::string>>(input),
                                    error,
                                    "incompatible type");
}

void run()
{
    convert_vector_int();
    convert_vector_double();
    convert_vector_string();
    convert_vector_wstring();
    convert_vector_u16string();
    convert_vector_u32string();

    convert_vector_variable();
    fail_vector_mixed();
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
