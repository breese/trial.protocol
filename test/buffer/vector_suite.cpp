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

#include <vector>
#include <trial/protocol/buffer/vector.hpp>

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

    virtual void write(view_type view)
    {
        return super::write(view);
    }
};

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(buffer_vector_suite)

BOOST_AUTO_TEST_CASE(test_empty)
{
    std::vector<char> output;
    vector_buffer<char> container(output);

    char expected[] = { };
    BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                  expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_single)
{
    std::vector<char> output;
    vector_buffer<char> container(output);
    BOOST_REQUIRE_EQUAL(container.grow(1), true);
    BOOST_REQUIRE_NO_THROW(container.write('A'));

    char expected[] = { 'A' };
    BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                  expected, expected + sizeof(expected));
}

BOOST_AUTO_TEST_CASE(test_view)
{
    std::vector<char> output;
    vector_buffer<char> container(output);
    std::string input = "alpha";
    BOOST_REQUIRE_EQUAL(container.grow(input.size()), true);
    BOOST_REQUIRE_NO_THROW(container.write(input));

    BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                  input.begin(), input.end());
}

BOOST_AUTO_TEST_SUITE_END()
