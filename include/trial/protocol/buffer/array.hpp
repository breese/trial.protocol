#ifndef TRIAL_PROTOCOL_BUFFER_ARRAY_HPP
#define TRIAL_PROTOCOL_BUFFER_ARRAY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/array.hpp>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT, int N>
class array : public base<CharT>
{
public:
    typedef typename base<CharT>::value_type value_type;
    typedef typename base<CharT>::size_type size_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    array() : current(content.begin()) {}

    const_iterator begin() const
    {
        return content.begin();
    }

    const_iterator end() const
    {
        return content.end();
    }

    // Returns the number of elements that has been inserted into the array
    size_type size() const
    {
        return (current - begin());
    }

private:
    virtual bool grow(size_type delta)
    {
        return (N - size() >= delta);
    }

    virtual void write(value_type value)
    {
        assert(grow(sizeof(value_type)));
        *current = value;
        ++current;
    }

    virtual void write(const value_type *values, size_type size)
    {
        assert(grow(size));
        for (size_type i = 0; i < size; ++i)
        {
            current[i] = values[i];
        }
        current += size;
    }

private:
    boost::array<CharT, N> content;
    iterator current;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_ARRAY_HPP
