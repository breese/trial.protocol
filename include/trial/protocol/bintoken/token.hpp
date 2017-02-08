#ifndef TRIAL_PROTOCOL_BINTOKEN_TOKEN_HPP
#define TRIAL_PROTOCOL_BINTOKEN_TOKEN_HPP

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
#include <trial/protocol/detail/cstdfloat.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace token
{

//-----------------------------------------------------------------------------
// Token types
//-----------------------------------------------------------------------------

struct code
{
    enum value
    {
        end = 0,
        error_unknown_token,
        error_unexpected_token,
        error_negative_length,
        error_overflow,
        error_invalid_value,
        error_expected_end_record,
        error_expected_end_array,
        error_expected_end_assoc_array,

        null = 0x82,
        true_value = 0x81,
        false_value = 0x80,

        int8 = 0xA0,
        int16 = 0xB0,
        int32 = 0xC0,
        int64 = 0xD0,

        float32 = 0xC2,
        float64 = 0xD2,

        string8 = 0xA9,
        string16 = 0xB9,
        string32 = 0xC9,
        string64 = 0xD9,

        binary8 = 0xAB,
        binary16 = 0xBB,
        binary32 = 0xCB,
        binary64 = 0xDB,

        begin_record = 0x90,
        end_record = 0x91,
        begin_array = 0x92,
        end_array = 0x93,
        begin_assoc_array = 0x9C,
        end_assoc_array = 0x9D
    };
};

struct symbol
{
    enum value
    {
        end,
        error,

        null,
        boolean,
        integer,
        number,
        string,
        binary,

        begin_record,
        end_record,
        begin_array,
        end_array,
        begin_assoc_array,
        end_assoc_array
    };

    static value convert(code::value);
};

struct category
{
    enum value
    {
        status,
        nullable,
        data,
        structural
    };

    static value convert(symbol::value);
    static value convert(code::value);
};

//-----------------------------------------------------------------------------
// Token tags
//-----------------------------------------------------------------------------

struct null
{
    using type = void;
    static const std::size_t size = 0;
    static const token::code::value code = token::code::null;
    static bool same(token::code::value);
};

struct begin_record
{
    using type = void;
    static const std::size_t size = 0;
    static const token::code::value code = token::code::begin_record;
    static bool same(token::code::value);
};

struct end_record
{
    using type = void;
    static const std::size_t size = 0;
    static const token::code::value code = token::code::end_record;
    static bool same(token::code::value);
};

struct begin_array
{
    using type = void;
    static const std::size_t size = 0;
    static const token::code::value code = token::code::begin_array;
    static bool same(token::code::value);
};

struct end_array
{
    using type = void;
    static const std::size_t size = 0;
    static const token::code::value code = token::code::end_array;
    static bool same(token::code::value);
};

struct begin_assoc_array
{
    using type = void;
    static const std::size_t size = 0;
    static const token::code::value code = token::code::begin_assoc_array;
    static bool same(token::code::value);
};

struct end_assoc_array
{
    using type = void;
    static const std::size_t size = 0;
    static const token::code::value code = token::code::end_assoc_array;
    static bool same(token::code::value);
};

struct boolean
{
    using type = bool;
    static const std::size_t size = 0;
    static const token::symbol::value symbol = token::symbol::boolean;
    static bool same(token::code::value);
};

struct int8
{
    using type = std::int8_t;
    static const std::size_t size = sizeof(type);
    static const token::code::value code = token::code::int8;
    static bool same(token::code::value);
};

struct int16
{
    using type = std::int16_t;
    static const std::size_t size = sizeof(type);
    static const token::code::value code = token::code::int16;
    static bool same(token::code::value);
};

struct int32
{
    using type = std::int32_t;
    static const std::size_t size = sizeof(type);
    static const token::code::value code = token::code::int32;
    static bool same(token::code::value);
};

struct int64
{
    using type = std::int64_t;
    static const std::size_t size = sizeof(type);
    static const token::code::value code = token::code::int64;
    static bool same(token::code::value);
};

struct float32
{
    using type = protocol::detail::float32_t;
    static const std::size_t size = sizeof(type);
    static const token::code::value code = token::code::float32;
    static bool same(token::code::value);
};

struct float64
{
    using type = protocol::detail::float64_t;
    static const std::size_t size = sizeof(type);
    static const token::code::value code = token::code::float64;
    static bool same(token::code::value);
};

struct string
{
    using type = std::string;
    static bool same(token::code::value);
};

struct binary
{
    static bool same(token::code::value);
};

//-----------------------------------------------------------------------------
// Token traits
//-----------------------------------------------------------------------------

template <typename T>
struct is_structural
{
    static const bool value = false;
};

template <typename T>
struct is_tag
{
    static const bool value = false;
};

template <typename T, typename Enable = void>
struct type_cast
{
    using type = T;
};

} // namespace token
} // namespace bintoken
} // namespace protocol
} // namespace trial

#include <trial/protocol/bintoken/detail/token.ipp>

#endif // TRIAL_PROTOCOL_BINTOKEN_TOKEN_HPP
