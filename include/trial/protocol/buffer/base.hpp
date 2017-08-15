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
#include <trial/protocol/core/detail/string_view.hpp>
#include <trial/protocol/core/char_traits.hpp>

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
    using value_type = CharT;
    using size_type = std::size_t;
    using view_type = core::detail::basic_string_view<value_type, core::char_traits<value_type>>;

    virtual ~base() {}

    virtual bool grow(size_type) = 0;
    virtual void write(value_type) = 0;
    virtual void write(const view_type&) = 0;
};

template <typename T, typename Enable = void>
struct traits
{
};

} // namespace buffer
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BUFFER_BASE_HPP
