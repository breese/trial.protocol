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

#include <trial/protocol/buffer/string.hpp>

using namespace trial::protocol;

template <typename CharT>
class string_buffer : buffer::basic_string<CharT>
{
    typedef buffer::basic_string<CharT> super;

public:
    typedef typename super::value_type value_type;
    typedef typename super::size_type size_type;
    typedef typename super::view_type view_type;

    string_buffer(std::basic_string<CharT>& data)
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

    virtual void write(view_type view)
    {
        return super::write(view);
    }
};

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(buffer_string_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::string output;
    string_buffer<char> container(output);
    BOOST_REQUIRE_EQUAL(output, "");
}

BOOST_AUTO_TEST_CASE(test_single)
{
    std::string output;
    string_buffer<char> container(output);
    BOOST_REQUIRE_EQUAL(container.grow(1), true);
    BOOST_REQUIRE_NO_THROW(container.write('A'));
    BOOST_REQUIRE_EQUAL(output, "A");
}

BOOST_AUTO_TEST_CASE(test_view)
{
    std::string output;
    string_buffer<char> container(output);
    std::string input = "alpha";
    BOOST_REQUIRE_EQUAL(container.grow(input.size()), true);
    BOOST_REQUIRE_NO_THROW(container.write(input));
    BOOST_REQUIRE_EQUAL(output, input);
}

BOOST_AUTO_TEST_SUITE_END()
