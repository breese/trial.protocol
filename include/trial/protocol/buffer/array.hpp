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

#include <cassert>
#include <algorithm>
#include <boost/cstdint.hpp>
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
    typedef typename base<CharT>::view_type view_type;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    array(boost::array<CharT, N>& output)
        : content(output),
          current(content.begin())
    {}

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
        assert(current >= begin());
        return size_type(current - begin());
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

    virtual void write(const view_type& view)
    {
        assert(grow(view.size()));
        current = std::copy(view.begin(), view.end(), current);
    }

private:
    boost::array<CharT, N>& content;
    iterator current;
};

template <typename CharT, std::size_t N>
struct traits< boost::array<CharT, N> >
{
    typedef typename base<CharT>::view_type view_type;
    typedef buffer::array<CharT, N> buffer_type;

    static view_type view_cast(const boost::array<CharT, N>& data)
    {
        return view_type(data.data(), data.size());
    }
};

template <typename CharT, std::size_t N>
struct traits<CharT[N]>
{
    typedef typename base<CharT>::view_type view_type;
    typedef buffer::array<CharT, N> buffer_type;

    static view_type view_cast(const CharT(&data)[N])
    {
        return view_type(data, N);
    }
};

template <typename CharT, std::size_t N>
struct is_binary< boost::array<CharT, N> >
{
    static const bool value = true;
};

template <std::size_t N>
struct is_binary<boost::uint8_t[N]>
{
    static const bool value = true;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_ARRAY_HPP
