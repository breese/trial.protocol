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
#include <cstdint>
#include <algorithm>
#include <array>
#include <type_traits>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT, std::size_t N, typename Super = base<CharT> >
class array : public Super
{
public:
    using value_type = typename Super::value_type;
    using size_type = typename Super::size_type;
    using view_type = typename Super::view_type;
    using iterator = typename std::add_pointer<value_type>::type;
    using const_iterator = typename std::add_pointer<const value_type>::type;

    array(std::array<CharT, N>& output)
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
    std::array<CharT, N>& content;
    iterator current;
};

template <typename CharT, std::size_t N>
struct traits< std::array<CharT, N> >
{
    using view_type = typename base<CharT>::view_type;
    using buffer_type = buffer::array<CharT, N>;

    static view_type view_cast(const std::array<CharT, N>& data)
    {
        return view_type(data.data(), data.size());
    }
};

template <typename CharT, std::size_t N>
struct traits<CharT[N]>
{
    using view_type = typename base<CharT>::view_type;
    using buffer_type = buffer::array<CharT, N>;

    static view_type view_cast(const CharT(&data)[N])
    {
        return view_type(data, N);
    }
};

template <typename CharT, std::size_t N>
struct is_binary< std::array<CharT, N> >
{
    static const bool value = true;
};

template <std::size_t N>
struct is_binary<std::uint8_t[N]>
{
    static const bool value = true;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_ARRAY_HPP
