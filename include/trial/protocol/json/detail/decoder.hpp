#ifndef TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP

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
#include <boost/config.hpp>
#include <trial/protocol/core/detail/string_view.hpp>
#include <trial/protocol/core/detail/span.hpp>
#include <trial/protocol/core/char_traits.hpp>
#include <trial/protocol/json/token.hpp>
#include <trial/protocol/json/error.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
class basic_decoder
{
public:
    using size_type = std::size_t;
    using value_type = CharT;
    using const_pointer = const value_type *;
    using view_type = core::detail::span<value_type>;

    basic_decoder() = default;
    basic_decoder(const_pointer first, const_pointer last);
    basic_decoder(const_pointer first, size_type length);
    template <std::size_t M>
    basic_decoder(const value_type (&array)[M]);

    void next() noexcept;

    void code(token::code::value) noexcept;
    token::code::value code() const noexcept;
    std::error_code error() const noexcept;
    const view_type& literal() const noexcept;
    const view_type& tail() const noexcept;
    template <typename ReturnType> ReturnType value() const;
    template <typename T> json::errc value(T&) const noexcept;

private:
    void next_token(token::code::value) noexcept;
    void next_f_keyword() noexcept;
    void next_n_keyword() noexcept;
    void next_t_keyword() noexcept;
    void next_number() noexcept;
    void next_string() noexcept;

    void skip_whitespaces() noexcept;
    bool at_keyword_end() const noexcept;

    template <typename ReturnType, typename Enable = void>
    struct overloader;
    template <typename T> json::errc signed_integer_value(T&) const noexcept;
    template <typename T> json::errc unsigned_integer_value(const_pointer, const_pointer, T&) const noexcept;
    json::errc unsigned_integer_value(const_pointer, const_pointer, std::uint8_t&) const noexcept;
    json::errc unsigned_integer_value(const_pointer, const_pointer, std::uint16_t&) const noexcept;
    json::errc unsigned_integer_value(const_pointer, const_pointer, std::uint32_t&) const noexcept;
    json::errc unsigned_integer_value(const_pointer, const_pointer, std::uint64_t&) const noexcept;
    template <typename T> void real_value(T&) const noexcept;
    template <typename T> void string_value(T&) const noexcept;

private:
    static constexpr int segment_max = 32;
    view_type input;
    struct
    {
        token::code::value code;
        view_type view;
        union
        {
            // Auxillary information collected during scanning.
            // Only add trivially destructible types.
            struct
            {
                const_pointer integer_tail;
                const_pointer fraction_tail;
            } number;
            struct
            {
                int length;
                const_pointer segment_tail[segment_max];
            } string;
        } scan;
    } current;
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/decoder.ipp>

#endif /* TRIAL_PROTOCOL_JSON_DETAIL_DECODER_HPP */
