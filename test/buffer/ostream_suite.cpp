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
#include <trial/protocol/buffer/ostream.hpp>
#include <trial/protocol/detail/lightweight_test.hpp>

using namespace trial::protocol;

template <typename CharT>
class ostream_buffer : buffer::basic_ostream<CharT>
{
    typedef buffer::basic_ostream<CharT> super;

public:
    typedef typename super::value_type value_type;
    typedef typename super::size_type size_type;
    typedef typename super::view_type view_type;

    ostream_buffer(std::basic_ostream<CharT>& data)
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
// std::ostringstream
//-----------------------------------------------------------------------------

namespace ostringstream_suite
{

void test_empty()
{
    std::ostringstream output;
    ostream_buffer<char> container(output);

    TRIAL_PROTOCOL_TEST_EQUAL(output.str(), "");
}

void test_single()
{
    std::ostringstream output;
    ostream_buffer<char> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(1), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write('A'));
    TRIAL_PROTOCOL_TEST_EQUAL(output.str(), "A");
}

void test_view()
{
    std::ostringstream output;
    ostream_buffer<char> container(output);
    std::string input = "alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(input.size()), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(input));
    TRIAL_PROTOCOL_TEST_EQUAL(output.str(), input);
}

void test()
{
    test_empty();
    test_single();
    test_view();
}

} // namespace ostringstream_suite

//-----------------------------------------------------------------------------
// std::wostringstream
//-----------------------------------------------------------------------------

namespace wostringstream_suite
{

void test_empty()
{
    std::wstringstream output;
    ostream_buffer<wchar_t> container(output);

    TRIAL_PROTOCOL_TEST(output.str() == L"");
}

void test_single()
{
    std::wostringstream output;
    ostream_buffer<wchar_t> container(output);
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(1), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(L'A'));
    TRIAL_PROTOCOL_TEST(output.str() == L"A");
}

void test_view()
{
    std::wostringstream output;
    ostream_buffer<wchar_t> container(output);
    std::wstring input = L"alpha";
    TRIAL_PROTOCOL_TEST_EQUAL(container.grow(input.size()), true);
    TRIAL_PROTOCOL_TEST_NO_THROW(container.write(input));
    TRIAL_PROTOCOL_TEST(output.str() == input);
}

void test()
{
    test_empty();
    test_single();
    test_view();
}

} // namespace wostringstream_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    ostringstream_suite::test();
    wostringstream_suite::test();

    return boost::report_errors();
}
