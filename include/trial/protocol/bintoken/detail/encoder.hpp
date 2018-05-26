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
#include <type_traits>
#include <trial/protocol/core/detail/string_view.hpp>
#include <trial/protocol/core/char_traits.hpp>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/bintoken/token.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace detail
{

template <std::size_t N>
class basic_encoder
{
    using value_type = std::uint8_t;
public:
    using size_type = std::size_t;
    using buffer_type = buffer::base<value_type>;
    using view_type = core::detail::basic_string_view<value_type, core::char_traits<value_type>>;
    using string_view_type = core::detail::basic_string_view<char, core::char_traits<char>>;

    template <typename T>
    basic_encoder(T&);
    ~basic_encoder();

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

    size_type array(const token::int8::type *, size_type);
    size_type array(const token::int16::type *, size_type);
    size_type array(const token::int32::type *, size_type);
    size_type array(const token::int64::type *, size_type);
    size_type array(const token::float32::type *, size_type);
    size_type array(const token::float64::type *, size_type);

private:
    template <typename T, typename = void>
    struct overloader;

    size_type write_length(std::uint8_t);
    size_type write_length(std::uint16_t);
    size_type write_length(std::uint32_t);
    size_type write_length(std::uint64_t);
    size_type write(value_type);
    size_type write(const view_type&);

    void endian_write(token::int16::type);
    void endian_write(token::int32::type);
    void endian_write(token::int64::type);
    void endian_write(token::float32::type);
    void endian_write(token::float64::type);

    void endian_write(std::uint16_t);
    void endian_write(std::uint32_t);
    void endian_write(std::uint64_t);

    buffer_type& buffer();
    const buffer_type& buffer() const;

private:
    typename std::aligned_storage<N>::type storage;
};

} // namespace detail
} // namespace bintoken
} // namespace protocol
} // namespace trial

#include <trial/protocol/bintoken/detail/encoder.ipp>

#endif // TRIAL_PROTOCOL_BINTOKEN_DETAIL_ENCODER_HPP
