#ifndef TRIAL_PROTOCOL_BUFFER_STRING_HPP
#define TRIAL_PROTOCOL_BUFFER_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT>
class basic_string : public base<CharT>
{
public:
    typedef typename base<CharT>::value_type value_type;
    typedef typename base<CharT>::size_type size_type;
    typedef typename base<CharT>::view_type view_type;

    basic_string(std::basic_string<CharT>& output)
        : content(output)
    {
    }

protected:
    virtual bool grow(size_type delta)
    {
        const size_type size = content.size() + delta + 1;
        if (size > content.capacity())
        {
            if (size > content.max_size())
                return false;
            content.reserve(size);
        }
        return true;
    }

    virtual void write(value_type value)
    {
        content.push_back(value);
    }

    virtual void write(const view_type& view)
    {
        content.append(view.begin(), view.size());
    }

private:
    std::basic_string<CharT>& content;
};

template <typename CharT>
struct traits< std::basic_string<CharT> >
{
    typedef buffer::basic_string<CharT> buffer_type;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_STRING_HPP
