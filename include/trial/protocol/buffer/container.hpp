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

template <typename T>
class basic_container
{
};

template <template <typename, typename> class ContainerType,
          typename CharT,
          typename AllocatorType>
class basic_container< ContainerType<CharT, AllocatorType> >
    : public base<CharT>
{
public:
    using value_type = typename base<CharT>::value_type;
    using size_type = typename base<CharT>::size_type;
    using view_type = typename base<CharT>::view_type;
    using container_type = ContainerType<CharT, AllocatorType>;

    basic_container(container_type& data)
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
    container_type& buffer;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_CONTAINER_HPP
