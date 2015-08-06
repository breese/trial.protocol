#ifndef TRIAL_PROTOCOL_BUFFER_CONTAINER_HPP
#define TRIAL_PROTOCOL_BUFFER_CONTAINER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT,
          template <typename, typename = std::allocator<CharT> > class ContainerType>
class basic_container : public base<CharT>
{
public:
    typedef typename base<CharT>::value_type value_type;
    typedef typename base<CharT>::size_type size_type;
    typedef typename base<CharT>::view_type view_type;
    typedef ContainerType<value_type> container_type;

    basic_container(container_type& buffer)
        : buffer(buffer)
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
    container_type& buffer;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_CONTAINER_HPP
