///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/test/unit_test.hpp>

#include <trial/protocol/buffer/ostream.hpp>

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

BOOST_AUTO_TEST_SUITE(buffer_ostream_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::ostringstream output;
    ostream_buffer<char> container(output);

    BOOST_REQUIRE_EQUAL(output.str(), "");
}

BOOST_AUTO_TEST_CASE(test_single)
{
    std::ostringstream output;
    ostream_buffer<char> container(output);
    BOOST_REQUIRE_EQUAL(container.grow(1), true);
    BOOST_REQUIRE_NO_THROW(container.write('A'));
    BOOST_REQUIRE_EQUAL(output.str(), "A");
}

BOOST_AUTO_TEST_CASE(test_view)
{
    std::ostringstream output;
    ostream_buffer<char> container(output);
    std::string input = "alpha";
    BOOST_REQUIRE_EQUAL(container.grow(input.size()), true);
    BOOST_REQUIRE_NO_THROW(container.write(input));
    BOOST_REQUIRE_EQUAL(output.str(), input);
}

BOOST_AUTO_TEST_SUITE_END()

//-----------------------------------------------------------------------------
// std::wostringstream
//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(buffer_wostream_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::wstringstream output;
    ostream_buffer<wchar_t> container(output);

    BOOST_REQUIRE(output.str() == L"");
}

BOOST_AUTO_TEST_CASE(test_single)
{
    std::wostringstream output;
    ostream_buffer<wchar_t> container(output);
    BOOST_REQUIRE_EQUAL(container.grow(1), true);
    BOOST_REQUIRE_NO_THROW(container.write(L'A'));
    BOOST_REQUIRE(output.str() == L"A");
}

BOOST_AUTO_TEST_CASE(test_view)
{
    std::wostringstream output;
    ostream_buffer<wchar_t> container(output);
    std::wstring input = L"alpha";
    BOOST_REQUIRE_EQUAL(container.grow(input.size()), true);
    BOOST_REQUIRE_NO_THROW(container.write(input));
    BOOST_REQUIRE(output.str() == input);
}

BOOST_AUTO_TEST_SUITE_END()
