#ifndef TRIAL_PROTOCOL_BINTOKEN_DETAIL_ENCODER_HPP
#define TRIAL_PROTOCOL_BINTOKEN_DETAIL_ENCODER_HPP

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
#include <cstdint>
#include <string>
#include <memory>
#include <trial/protocol/detail/string_view.hpp>
#include <trial/protocol/bintoken/token.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace detail
{

class encoder
{
public:
    using value_type = std::uint8_t;
    using size_type = std::size_t;
    using view_type = trial::protocol::detail::basic_string_view<value_type>;
    using string_view_type = trial::protocol::detail::basic_string_view<char>;

    template <typename T>
    encoder(T&);

    template <typename T> size_type value();
    size_type value(bool);
    size_type value(token::int8::type);
    size_type value(token::int16::type);
    size_type value(token::int32::type);
    size_type value(token::int64::type);
    size_type value(token::float32::type);
    size_type value(token::float64::type);
    size_type value(const string_view_type&);
    size_type value(const char *);
    size_type value(const char *, size_type);
    size_type binary(const value_type *, size_type);
    size_type binary(const view_type&);

private:
    size_type write_length(std::uint8_t);
    size_type write_length(std::uint16_t);
    size_type write_length(std::uint32_t);
    size_type write_length(std::uint64_t);
    size_type write(value_type);
    size_type write(const view_type&);

private:
    using buffer_type = buffer::base<value_type>;
    std::unique_ptr<buffer_type> buffer;
};

} // namespace detail
} // namespace bintoken
} // namespace protocol
} // namespace trial

#include <trial/protocol/bintoken/detail/encoder.ipp>

#endif // TRIAL_PROTOCOL_BINTOKEN_DETAIL_ENCODER_HPP
