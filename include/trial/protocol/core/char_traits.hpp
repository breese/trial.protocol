#ifndef TRIAL_PROTOCOL_CORE_CHAR_TRAITS_HPP
#define TRIAL_PROTOCOL_CORE_CHAR_TRAITS_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>

namespace trial
{
namespace protocol
{
namespace core
{
namespace detail
{

template <typename CharT>
struct char_traits
{
    static_assert(sizeof(CharT) == 0, "Type not supported");
};

// Specialization for unsigned char

template <>
struct char_traits<unsigned char>
    : private std::char_traits<char>
{
private:
    using base_type = std::char_traits<char>;

public:
    using char_type = unsigned char;
    using base_type::int_type;
    using base_type::off_type;
    using base_type::pos_type;
    using base_type::state_type;

    using base_type::eq_int_type;
    using base_type::eof;
    using base_type::not_eof;

    static void assign(char_type& lhs, const char_type& rhs) noexcept
    {
        lhs = rhs;
    }

    static char_type *assign(char_type *lhs, std::size_t size, char_type value)
    {
        return reinterpret_cast<char_type *>
            (
                base_type::assign(reinterpret_cast<char *>(lhs),
                                  size,
                                  static_cast<char>(value))
             );
    }

    static char_type *copy(char_type *lhs, const char_type *rhs, std::size_t size)
    {
        return reinterpret_cast<char_type *>
            (
                base_type::copy(reinterpret_cast<char *>(lhs),
                                reinterpret_cast<const char *>(rhs),
                                size)
             );
    }

    static char_type *move(char_type *lhs, const char_type *rhs, std::size_t size)
    {
        return reinterpret_cast<char_type *>
            (
                base_type::move(reinterpret_cast<char *>(lhs),
                                reinterpret_cast<const char *>(rhs),
                                size)
             );
    }

    static std::size_t length(const char_type *lhs)
    {
        return base_type::length(reinterpret_cast<const char *>(lhs));
    }

    static constexpr bool eq(char_type lhs, char_type rhs) noexcept
    {
        return base_type::eq(static_cast<char>(lhs), static_cast<char>(rhs));
    }

    static constexpr bool lt(char_type lhs, char_type rhs) noexcept
    {
        return base_type::lt(static_cast<char>(lhs), static_cast<char>(rhs));
    }

    static int compare(const char_type *lhs, const char_type *rhs, std::size_t size)
    {
        return base_type::compare(reinterpret_cast<const char *>(lhs),
                                  reinterpret_cast<const char *>(rhs),
                                  size);
    }

    static const char_type *find(const char_type *lhs, std::size_t size, const char_type& rhs)
    {
        return reinterpret_cast<const char_type *>
            (
                base_type::find(reinterpret_cast<const char *>(lhs),
                                size,
                                static_cast<const char&>(rhs))
             );
    }

    static constexpr char_type to_char_type(int_type value) noexcept
    {
        return char_type(value);
    }

    static constexpr int_type to_int_type(char_type value) noexcept
    {
        return int_type(value);
    }
};

// Select whether to use std::char_traits or own specializations

template <typename CharT>
struct char_traits_type
{
    using type = std::char_traits<CharT>;
};

template <>
struct char_traits_type<unsigned char>
{
    using type = char_traits<unsigned char>;
};

} // namespace detail

template <typename CharT>
using char_traits = typename detail::char_traits_type<CharT>::type;

} // namespace core
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_CORE_CHAR_TRAITS_HPP
