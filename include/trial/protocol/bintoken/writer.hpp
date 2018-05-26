#ifndef TRIAL_PROTOCOL_BINTOKEN_WRITER_HPP
#define TRIAL_PROTOCOL_BINTOKEN_WRITER_HPP

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
#include <trial/protocol/bintoken/error.hpp>
#include <trial/protocol/bintoken/detail/encoder.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

template <std::size_t N = 2 * sizeof(void *)>
class basic_writer
{
public:
    using size_type = typename detail::basic_encoder<N>::size_type;
    using view_type = typename detail::basic_encoder<N>::view_type;
    using string_view_type = typename detail::basic_encoder<N>::string_view_type;

    template <typename T> basic_writer(T&);

    template <typename T>
    size_type value();

    template <typename T>
    size_type value(const T&);

    template <typename T>
    size_type array(const T *, size_type);

private:
    void validate_scope(token::code::value, enum bintoken::errc);

private:
    template <typename T, typename Enable = void> struct overloader;

    detail::basic_encoder<N> encoder;
    std::stack<token::code::value> stack;
};

using writer = basic_writer<>;

} // namespace bintoken
} // namespace protocol
} // namespace trial

#include <trial/protocol/bintoken/detail/writer.ipp>

#endif // TRIAL_PROTOCOL_BINTOKEN_WRITER_HPP
