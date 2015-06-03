#ifndef TRIAL_PROTOCOL_BUFFER_BASE_HPP
#define TRIAL_PROTOCOL_BUFFER_BASE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t

namespace trial
{
namespace protocol
{
namespace buffer
{

template <typename CharT>
class base
{
public:
    typedef CharT value_type;
    typedef std::size_t size_type;

    virtual ~base() {}

    virtual bool grow(size_type) = 0;
    virtual void write(value_type) = 0;
    virtual void write(const value_type*, size_type) = 0;
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_BASE_HPP
