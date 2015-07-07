#ifndef TRIAL_PROTOCOL_BUFFER_OSTREAM_HPP
#define TRIAL_PROTOCOL_BUFFER_OSTREAM_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <ostream>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT>
class basic_ostream : public base<CharT>
{
public:
    typedef typename base<CharT>::value_type value_type;
    typedef typename base<CharT>::size_type size_type;
    typedef typename base<CharT>::view_type view_type;

    basic_ostream(std::ostream& stream) : content(stream) {}

private:
    virtual bool grow(size_type delta)
    {
        return content.good();
    }

    virtual void write(value_type value)
    {
        content << value;
    }

    virtual void write(const view_type& view)
    {
        content << view;
    }

private:
    std::ostream& content;
};

typedef basic_ostream<char> ostream;

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_OSTREAM_HPP
