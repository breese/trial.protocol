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
    class view_type
    {
    public:
        view_type() noexcept = default;
        view_type(const view_type&) noexcept = default;
        view_type(view_type&&) noexcept = default;
        view_type& operator=(const view_type&) noexcept = delete;
        view_type& operator=(view_type&&) noexcept = default;

        view_type(const_pointer first, const_pointer last) : head(first), tail(last) {}
        view_type(const_pointer first, size_type size) : head(first), tail(head + size) {}

        const_pointer data() const noexcept { return head; }
        size_type size() const noexcept { return tail - head; }
        bool empty() const noexcept { return head == tail; }
        value_type front() const noexcept { return *head; }
        value_type back() const noexcept { return *(tail - 1); }
        value_type operator[](size_type index) const noexcept { return head[index]; }

        void remove_front(size_type amount = 1) noexcept { head += amount; }

        const_pointer begin() const noexcept { return head; }
        const_pointer end() const noexcept { return tail; }

        // For test purposes
        template <std::size_t M>
        bool operator==(const char (&rhs)[M]) const noexcept
        {
            const auto rhs_size = M - 1;
            if (size() != rhs_size)
                return false;
            for (std::size_t k = 0; k < rhs_size; ++k)
            {
                if ((*this)[k] != rhs[k])
                    return false;
            }
            return true;
        }
    private:
        const_pointer head = nullptr;
        const_pointer tail = nullptr;
    };

    basic_decoder() = default;
    basic_decoder(const_pointer first, const_pointer last);
    basic_decoder(const_pointer first, size_type length);
    template <std::size_t M>
    basic_decoder(const value_type (&array)[M]);

    void next() noexcept;

    void code(token::detail::code::value) noexcept;
    token::detail::code::value code() const noexcept;
    std::error_code error() const noexcept;
    const view_type& literal() const noexcept;
    const view_type& tail() const noexcept;
    template <typename ReturnType> ReturnType value() const;
    template <typename T> json::errc value(T&) const noexcept;

private:
    token::detail::code::value next_token(token::detail::code::value) noexcept;
    token::detail::code::value next_f_keyword() noexcept;
    token::detail::code::value next_n_keyword() noexcept;
    token::detail::code::value next_t_keyword() noexcept;
    token::detail::code::value next_number() noexcept;
    token::detail::code::value next_string() noexcept;

    void skip_whitespaces() noexcept;
    bool at_keyword_end() const noexcept;

    template <typename ReturnType, typename Enable = void>
    struct overloader;
    template <typename T> json::errc signed_integer_value(T&) const noexcept;
    template <typename T> json::errc unsigned_integer_value(T&) const noexcept;
    json::errc unsigned_integer_value(std::uint8_t&) const noexcept;
    json::errc unsigned_integer_value(std::uint16_t&) const noexcept;
    json::errc unsigned_integer_value(std::uint32_t&) const noexcept;
    json::errc unsigned_integer_value(std::uint64_t&) const noexcept;
    template <typename T> void real_value(T&) const noexcept;
    template <typename T> void string_value(T&) const noexcept;

private:
    static constexpr int segment_max = 32;
    view_type input;
    struct
    {
        token::detail::code::value code;
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
