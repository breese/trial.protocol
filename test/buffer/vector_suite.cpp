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
#include <boost/array.hpp>
#include <trial/protocol/buffer/vector.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

using namespace trial::protocol;

template <typename CharT>
class vector_buffer : buffer::vector<CharT>
{
    typedef buffer::vector<CharT> super;

public:
    typedef typename super::value_type value_type;
    typedef typename super::size_type size_type;
    typedef typename super::view_type view_type;

    vector_buffer(std::vector<CharT>& data)
        : super(data)
    {
    }

    virtual bool grow(size_type size)
    {
        return super::grow(size);
    }

    virtual void write(value_type value)
    {
        return super::write(value);
    }

    virtual void write(const view_type& view)
    {
        return super::write(view);
    }
};

//-----------------------------------------------------------------------------
// std::vector<char>
//-----------------------------------------------------------------------------

namespace vector_suite
{

void test_empty()
{
    std::vector<char> output;
    vector_buffer<char> container(output);

    boost::array<char, 0> expected;
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          expected.begin(), expected.end());
}

void test_single()
{
    std::vector<char> output;
    vector_buffer<char> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(1), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write('A'));

    char expected[] = { 'A' };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          expected, expected + sizeof(expected));
}

void test_view()
{
    std::vector<char> output;
    vector_buffer<char> container(output);
    std::string input = "alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(input.size()), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(input));

    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          input.begin(), input.end());
}

void test()
{
    test_empty();
    test_single();
    test_view();
}

} // namespace vector_suite

//-----------------------------------------------------------------------------
// std::vector<unsigned char>
//-----------------------------------------------------------------------------

namespace uvector_suite
{

void test_empty()
{
    std::vector<unsigned char> output;
    vector_buffer<unsigned char> container(output);

    boost::array<unsigned char, 0> expected;
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          expected.begin(), expected.end());
}

void test_single()
{
    std::vector<unsigned char> output;
    vector_buffer<unsigned char> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(1), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write('A'));

    unsigned char expected[] = { 'A' };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          expected, expected + sizeof(expected));
}

void test_view()
{
    std::vector<unsigned char> output;
    vector_buffer<unsigned char> container(output);
    std::basic_string<unsigned char> input;
    input += 'a';
    input += 'l';
    input += 'p';
    input += 'h';
    input += 'a';
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(input.size()), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(input));

    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          input.begin(), input.end());
}

void test()
{
    test_empty();
    test_single();
    test_view();
}

} // namespace uvector_suite

//-----------------------------------------------------------------------------
// std::vector<wchar_t>
//-----------------------------------------------------------------------------

namespace wvector_suite
{

void test_empty()
{
    std::vector<wchar_t> output;
    vector_buffer<wchar_t> container(output);

    boost::array<wchar_t, 0> expected;
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          expected.begin(), expected.end());
}

void test_single()
{
    std::vector<wchar_t> output;
    vector_buffer<wchar_t> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(1), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(L'A'));

    wchar_t expected[] = { L'A' };
    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          expected, expected + sizeof(expected) / sizeof(wchar_t));
}

void test_view()
{
    std::vector<wchar_t> output;
    vector_buffer<wchar_t> container(output);
    std::wstring input = L"alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(input.size()), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(input));

    TRIAL_PROTOCOL_TEST_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                          input.begin(), input.end());
}

void test()
{
    test_empty();
    test_single();
    test_view();
}

} // namespace wvector_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    vector_suite::test();
    uvector_suite::test();
    wvector_suite::test();

    return boost::report_errors();
}
