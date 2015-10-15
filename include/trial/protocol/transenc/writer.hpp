#ifndef TRIAL_PROTOCOL_TRANSENC_WRITER_HPP
#define TRIAL_PROTOCOL_TRANSENC_WRITER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <trial/protocol/transenc/error.hpp>
#include <trial/protocol/transenc/detail/encoder.hpp>

namespace trial
{
namespace protocol
{
namespace transenc
{

class writer
{
public:
    typedef detail::encoder::value_type value_type;
    typedef detail::encoder::size_type size_type;
    typedef detail::encoder::view_type view_type;
    typedef detail::encoder::string_view_type string_view_type;

    template <typename T> writer(T&);

    template <typename T>
    size_type value();

    template <typename T>
    size_type value(const T&);

private:
    void validate_scope(token::code::value, enum transenc::errc);

private:
    template <typename T, typename Enable = void> struct overloader;
    detail::encoder encoder;

    std::stack<token::code::value> stack;
};

} // namespace transenc
} // namespace protocol
} // namespace trial

#include <trial/protocol/transenc/detail/writer.ipp>

#endif // TRIAL_PROTOCOL_TRANSENC_WRITER_HPP
