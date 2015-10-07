#ifndef TRIAL_PROTOCOL_BUFFER_VECTOR_HPP
#define TRIAL_PROTOCOL_BUFFER_VECTOR_HPP

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
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT>
class vector : public base<CharT>
{
public:
    typedef typename base<CharT>::value_type value_type;
    typedef typename base<CharT>::size_type size_type;
    typedef typename base<CharT>::view_type view_type;

    vector(std::vector<value_type>& data)
        : buffer(data)
    {
    }

protected:
    virtual bool grow(size_type delta)
    {
        const size_type size = buffer.size() + delta;
        if (size > buffer.capacity())
        {
            if (size > buffer.max_size())
                return false;
            buffer.reserve(size);
        }
        return true;
    }

    virtual void write(value_type value)
    {
        buffer.push_back(value);
    }

    virtual void write(const view_type& view)
    {
        if (grow(view.size()))
        {
            buffer.insert(buffer.end(), view.begin(), view.end());
        }
    }

private:
    std::vector<value_type>& buffer;
};

template <typename CharT>
struct traits< std::vector<CharT> >
{
    typedef typename base<CharT>::view_type view_type;
    typedef buffer::vector<CharT> buffer_type;

    static view_type view_cast(const std::vector<CharT>& data)
    {
        return view_type(data.data(), data.size());
    }
};

template <typename CharT>
struct is_binary< std::vector<CharT> >
{
    static const bool value = true;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_VECTOR_HPP
