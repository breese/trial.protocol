#ifndef TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <cstdlib> // std::atof
#include <iterator>
#include <limits>
#include <type_traits>
#include <trial/protocol/json/detail/string_converter.hpp>
#include <trial/protocol/json/detail/decoder.hpp>
#include <trial/protocol/json/detail/traits.hpp>
#include <trial/protocol/json/error.hpp>

// http://tools.ietf.org/html/rfc7159

//-----------------------------------------------------------------------------

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

//-----------------------------------------------------------------------------
// decoder::overloader
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename ReturnType, typename Enable>
struct basic_decoder<CharT>::overloader
{
};

// Integers

template <typename CharT>
template <typename ReturnType>
struct basic_decoder<CharT>::overloader<ReturnType,
                                        typename std::enable_if<std::is_integral<ReturnType>::value &&
                                                                std::is_signed<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_decoder<CharT>& self)
    {
        ReturnType result;
        value(self, result);
        return result;
    }

    inline static void value(const basic_decoder<CharT>& self,
                             ReturnType& output)
    {
        if (self.code() != token::detail::code::integer)
        {
            self.current.code = token::detail::code::error_incompatible_type;
            throw json::error(self.error());
        }
        output = {};
        return self.signed_integer_value(output);
    }
};

template <typename CharT>
template <typename ReturnType>
struct basic_decoder<CharT>::overloader<ReturnType,
                                        typename std::enable_if<std::is_integral<ReturnType>::value &&
                                                                std::is_unsigned<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_decoder<CharT>& self)
    {
        ReturnType result;
        value(self, result);
        return result;
    }

    inline static void value(const basic_decoder<CharT>& self,
                             ReturnType& output)
    {
        if (self.code() != token::detail::code::integer)
        {
            self.current.code = token::detail::code::error_incompatible_type;
            throw json::error(self.error());
        }
        output = {};
        return self.unsigned_integer_value(output);
    }
};

// Floating-point numbers

template <typename CharT>
template <typename ReturnType>
struct basic_decoder<CharT>::overloader<ReturnType,
                                        typename std::enable_if<std::is_floating_point<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_decoder<CharT>& self)
    {
        ReturnType result;
        value(self, result);
        return result;
    }

    inline static void value(const  basic_decoder<CharT>& self,
                             ReturnType& output)
    {
        if (self.code() != token::detail::code::real)
        {
            self.current.code = token::detail::code::error_incompatible_type;
            throw json::error(self.error());
        }
        output = {};
        return self.real_value(output);
    }
};

// Strings

template <typename CharT>
template <typename CharTraits, typename Allocator>
struct basic_decoder<CharT>::overloader<std::basic_string<CharT, CharTraits, Allocator>>
{
    using return_type = std::basic_string<CharT, CharTraits, Allocator>;

    inline static return_type value(const basic_decoder<CharT>& self)
    {
        return_type result;
        value(self, result);
        return result;
    }

    inline static void value(const basic_decoder<CharT>& self,
                             return_type& output)
    {
        if (self.code() != token::detail::code::string)
        {
            self.current.code = token::detail::code::error_incompatible_type;
            throw json::error(self.error());
        }
        self.string_value(output);
    }
};

//-----------------------------------------------------------------------------
// basic_decoder
//-----------------------------------------------------------------------------

template <typename CharT>
basic_decoder<CharT>::basic_decoder(const_pointer first,
                                    const_pointer last)
    : input(first, last),
      current{token::detail::code::uninitialized, {}, {}}
{
    next();
}

template <typename CharT>
basic_decoder<CharT>::basic_decoder(const_pointer first,
                                    size_type length)
    : basic_decoder(first, first + length)
{
}

template <typename CharT>
template <std::size_t M>
basic_decoder<CharT>::basic_decoder(const value_type (&array)[M])
    : basic_decoder(array, array + M - 1) // Skip terminating zero
{
}

template <typename CharT>
void basic_decoder<CharT>::code(token::detail::code::value code) BOOST_NOEXCEPT
{
    current.code = code;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::code() const BOOST_NOEXCEPT
{
    return current.code;
}

template <typename CharT>
std::error_code basic_decoder<CharT>::error() const BOOST_NOEXCEPT
{
    return json::make_error_code(to_errc(token::detail::convert(code())));
}

template <typename CharT>
void basic_decoder<CharT>::next() BOOST_NOEXCEPT
{
    if (current.code < 0)
        return; // Already marked as error
    if (current.code == token::detail::code::end)
    {
        current.code = token::detail::code::error_unexpected_token;
        return;
    }

    skip_whitespaces();

    if (input.empty())
    {
        current.code = token::detail::code::value::end;
        return;
    }

    switch (input.front())
    {
    case traits<CharT>::alpha_f:
        current.code = next_f_keyword();
        break;

    case traits<CharT>::alpha_n:
        current.code = next_n_keyword();
        break;

    case traits<CharT>::alpha_t:
        current.code = next_t_keyword();
        break;

    case traits<CharT>::alpha_minus:
    case traits<CharT>::alpha_0:
    case traits<CharT>::alpha_1:
    case traits<CharT>::alpha_2:
    case traits<CharT>::alpha_3:
    case traits<CharT>::alpha_4:
    case traits<CharT>::alpha_5:
    case traits<CharT>::alpha_6:
    case traits<CharT>::alpha_7:
    case traits<CharT>::alpha_8:
    case traits<CharT>::alpha_9:
        current.code = next_number();
        break;

    case traits<CharT>::alpha_quote:
        current.code = next_string();
        break;

    case traits<CharT>::alpha_brace_open:
        current.code = next_token(token::detail::code::begin_object);
        break;

    case traits<CharT>::alpha_brace_close:
        current.code = next_token(token::detail::code::end_object);
        break;

    case traits<CharT>::alpha_bracket_open:
        current.code = next_token(token::detail::code::begin_array);
        break;

    case traits<CharT>::alpha_bracket_close:
        current.code = next_token(token::detail::code::end_array);
        break;

    case traits<CharT>::alpha_comma:
        current.code = next_token(token::detail::code::value_separator);
        break;

    case traits<CharT>::alpha_colon:
        current.code = next_token(token::detail::code::name_separator);
        break;

    default:
        current.code = token::detail::code::error_unexpected_token;
        break;
    }
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_decoder<CharT>::value() const
{
    return basic_decoder<CharT>::overloader<ReturnType>::value(*this);
}

template <typename CharT>
template <typename T>
void basic_decoder<CharT>::value(T& output) const
{
    basic_decoder<CharT>::overloader<T>::value(*this, output);
}

template <typename CharT>
template <typename T>
void basic_decoder<CharT>::signed_integer_value(T& result) const
{
    static_assert(std::is_signed<T>::value, "T must be signed");
    assert(current.code == token::detail::code::integer);

    auto it = literal().begin();

    const bool is_negative = (*it == traits<CharT>::alpha_minus);
    if (is_negative)
    {
        ++it; // Skip minus

        const T lowest = std::numeric_limits<T>::lowest();
        while (it != literal().end())
        {
            if (lowest / T(10) > result) {
                // Overflow
                current.code = token::detail::code::error_invalid_value;
                throw json::error(error());
            }
            result *= T(10);

            const T digit = *it - traits<CharT>::alpha_0;
            if (lowest + digit > result + 1) {
                // Overflow
                current.code = token::detail::code::error_invalid_value;
                throw json::error(error());
            }
            result -= digit;

            ++it;
        }
    }
    else
    {
        unsigned_integer_value(result);
    }
}

template <typename CharT>
template <typename T>
void basic_decoder<CharT>::unsigned_integer_value(T& result) const
{
    assert(current.code == token::detail::code::integer);

    auto it = literal().begin();

    const bool is_negative = (*it == traits<CharT>::alpha_minus);
    if (is_negative)
    {
        current.code = token::detail::code::error_invalid_value;
        throw json::error(error());
    }

    const T max = std::numeric_limits<T>::max();
    while (it != literal().end())
    {
        if (max / T(10) < result) {
            // Overflow
            current.code = token::detail::code::error_invalid_value;
            throw json::error(error());
        }
        result *= T(10);

        const T digit = *it - traits<CharT>::alpha_0;
        if (max - digit < result) {
            // Overflow
            current.code = token::detail::code::error_invalid_value;
            throw json::error(error());
        }
        result += digit;

        ++it;
    }
}

template <typename CharT>
template <typename T>
void basic_decoder<CharT>::real_value(T& output) const
{
    assert(current.code == token::detail::code::real);

    static constexpr T zero = T(0.0);
    static constexpr T one = T(1.0);
    static constexpr T base = T(10.0);

    const CharT *marker = current.view.begin();
    T result = zero;
    const bool is_negative = *marker == detail::traits<CharT>::alpha_minus;
    if (is_negative)
    {
        ++marker;
    }
    while (true)
    {
        const unsigned delta = *marker - detail::traits<CharT>::alpha_0;
        if (delta > 9)
            break;
        result *= base;
        result += delta;
        ++marker;
    }
    if (*marker == '.')
    {
        ++marker;
        T fraction = zero;

        static constexpr T em1[] = { 0e-1, 1e-1, 2e-1, 3e-1, 4e-1, 5e-1, 6e-1, 7e-1, 8e-1, 9e-1 };
        static constexpr T em2[] = { 0e-2, 1e-2, 2e-2, 3e-2, 4e-2, 5e-2, 6e-2, 7e-2, 8e-2, 9e-2 };
        static constexpr T em3[] = { 0e-3, 1e-3, 2e-3, 3e-3, 4e-3, 5e-3, 6e-3, 7e-3, 8e-3, 9e-3 };
        static constexpr T em4[] = { 0e-4, 1e-4, 2e-4, 3e-4, 4e-4, 5e-4, 6e-4, 7e-4, 8e-4, 9e-4 };
        static constexpr T em5[] = { 0e-5, 1e-5, 2e-5, 3e-5, 4e-5, 5e-5, 6e-5, 7e-5, 8e-5, 9e-5 };
        static constexpr T em6[] = { 0e-6, 1e-6, 2e-6, 3e-6, 4e-6, 5e-6, 6e-6, 7e-6, 8e-6, 9e-6 };
        static constexpr T em7[] = { 0e-7, 1e-7, 2e-7, 3e-7, 4e-7, 5e-7, 6e-7, 7e-7, 8e-7, 9e-7 };
        static constexpr T em8[] = { 0e-8, 1e-8, 2e-8, 3e-8, 4e-8, 5e-8, 6e-8, 7e-8, 8e-8, 9e-8 };
        static constexpr T em9[] = { 0e-9, 1e-9, 2e-9, 3e-9, 4e-9, 5e-9, 6e-9, 7e-9, 8e-9, 9e-9 };
        static constexpr T em10[] = { 0e-10, 1e-10, 2e-10, 3e-10, 4e-10, 5e-10, 6e-10, 7e-10, 8e-10, 9e-10 };
        static constexpr T em11[] = { 0e-11, 1e-11, 2e-11, 3e-11, 4e-11, 5e-11, 6e-11, 7e-11, 8e-11, 9e-11 };
        static constexpr T em12[] = { 0e-12, 1e-12, 2e-12, 3e-12, 4e-12, 5e-12, 6e-12, 7e-12, 8e-12, 9e-12 };
        static constexpr T em13[] = { 0e-13, 1e-13, 2e-13, 3e-13, 4e-13, 5e-13, 6e-13, 7e-13, 8e-13, 9e-13 };
        static constexpr T em14[] = { 0e-14, 1e-14, 2e-14, 3e-14, 4e-14, 5e-14, 6e-14, 7e-14, 8e-14, 9e-14 };
        static constexpr T em15[] = { 0e-15, 1e-15, 2e-15, 3e-15, 4e-15, 5e-15, 6e-15, 7e-15, 8e-15, 9e-15 };
        static constexpr T em16[] = { 0e-16, 1e-16, 2e-16, 3e-16, 4e-16, 5e-16, 6e-16, 7e-16, 8e-16, 9e-16 };
        static constexpr T em17[] = { 0e-17, 1e-17, 2e-17, 3e-17, 4e-17, 5e-17, 6e-17, 7e-17, 8e-17, 9e-17 };
        static constexpr T em18[] = { 0e-18, 1e-18, 2e-18, 3e-18, 4e-18, 5e-18, 6e-18, 7e-18, 8e-18, 9e-18 };

        const auto fraction_size = current.scan.real.fraction_end - marker;
        switch (fraction_size)
        {
        default:
        {
            static constexpr T superbase = T(1e4);
            T scale = one;

            auto it = marker;
            while (current.scan.real.fraction_end - it > 4)
            {
                const auto delta1000 = unsigned(it[0] - detail::traits<CharT>::alpha_0);
                const auto delta100 = unsigned(it[1] - detail::traits<CharT>::alpha_0);
                const auto delta10 = unsigned(it[2] - detail::traits<CharT>::alpha_0);
                const auto delta1 = unsigned(it[3] - detail::traits<CharT>::alpha_0);
                const auto delta = delta1000 * 1000 + delta100 * 100 + delta10 * 10 + delta1;
                fraction = fraction * superbase + delta;
                scale *= superbase;
                it += 4;
            }

            while (current.scan.real.fraction_end > it)
            {
                const unsigned delta = *it - detail::traits<CharT>::alpha_0;
                scale *= base;
                fraction *= base;
                fraction += delta;
                ++it;
            }
            fraction /= scale;
            break;
        }
        case 18:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            fraction += em12[unsigned(marker[11] - detail::traits<CharT>::alpha_0)];
            fraction += em13[unsigned(marker[12] - detail::traits<CharT>::alpha_0)];
            fraction += em14[unsigned(marker[13] - detail::traits<CharT>::alpha_0)];
            fraction += em15[unsigned(marker[14] - detail::traits<CharT>::alpha_0)];
            fraction += em16[unsigned(marker[15] - detail::traits<CharT>::alpha_0)];
            fraction += em17[unsigned(marker[16] - detail::traits<CharT>::alpha_0)];
            fraction += em18[unsigned(marker[17] - detail::traits<CharT>::alpha_0)];
            break;
        case 17:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            fraction += em12[unsigned(marker[11] - detail::traits<CharT>::alpha_0)];
            fraction += em13[unsigned(marker[12] - detail::traits<CharT>::alpha_0)];
            fraction += em14[unsigned(marker[13] - detail::traits<CharT>::alpha_0)];
            fraction += em15[unsigned(marker[14] - detail::traits<CharT>::alpha_0)];
            fraction += em16[unsigned(marker[15] - detail::traits<CharT>::alpha_0)];
            fraction += em17[unsigned(marker[16] - detail::traits<CharT>::alpha_0)];
            break;
        case 16:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            fraction += em12[unsigned(marker[11] - detail::traits<CharT>::alpha_0)];
            fraction += em13[unsigned(marker[12] - detail::traits<CharT>::alpha_0)];
            fraction += em14[unsigned(marker[13] - detail::traits<CharT>::alpha_0)];
            fraction += em15[unsigned(marker[14] - detail::traits<CharT>::alpha_0)];
            fraction += em16[unsigned(marker[15] - detail::traits<CharT>::alpha_0)];
            break;
        case 15:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            fraction += em12[unsigned(marker[11] - detail::traits<CharT>::alpha_0)];
            fraction += em13[unsigned(marker[12] - detail::traits<CharT>::alpha_0)];
            fraction += em14[unsigned(marker[13] - detail::traits<CharT>::alpha_0)];
            fraction += em15[unsigned(marker[14] - detail::traits<CharT>::alpha_0)];
            break;
        case 14:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            fraction += em12[unsigned(marker[11] - detail::traits<CharT>::alpha_0)];
            fraction += em13[unsigned(marker[12] - detail::traits<CharT>::alpha_0)];
            fraction += em14[unsigned(marker[13] - detail::traits<CharT>::alpha_0)];
            break;
        case 13:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            fraction += em12[unsigned(marker[11] - detail::traits<CharT>::alpha_0)];
            fraction += em13[unsigned(marker[12] - detail::traits<CharT>::alpha_0)];
            break;
        case 12:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            fraction += em12[unsigned(marker[11] - detail::traits<CharT>::alpha_0)];
            break;
        case 11:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            fraction += em11[unsigned(marker[10] - detail::traits<CharT>::alpha_0)];
            break;
        case 10:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            fraction += em10[unsigned(marker[9] - detail::traits<CharT>::alpha_0)];
            break;
        case 9:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            fraction += em9[unsigned(marker[8] - detail::traits<CharT>::alpha_0)];
            break;
        case 8:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            fraction += em8[unsigned(marker[7] - detail::traits<CharT>::alpha_0)];
            break;
        case 7:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            fraction += em7[unsigned(marker[6] - detail::traits<CharT>::alpha_0)];
            break;
        case 6:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            fraction += em6[unsigned(marker[5] - detail::traits<CharT>::alpha_0)];
            break;
        case 5:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            fraction += em5[unsigned(marker[4] - detail::traits<CharT>::alpha_0)];
            break;
        case 4:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            fraction += em4[unsigned(marker[3] - detail::traits<CharT>::alpha_0)];
            break;
        case 3:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            fraction += em3[unsigned(marker[2] - detail::traits<CharT>::alpha_0)];
            break;
        case 2:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            fraction += em2[unsigned(marker[1] - detail::traits<CharT>::alpha_0)];
            break;
        case 1:
            fraction += em1[unsigned(marker[0] - detail::traits<CharT>::alpha_0)];
            break;
        case 0:
            break;
        }
        marker += fraction_size;
        result += fraction;
    }
    if ((*marker == detail::traits<CharT>::alpha_e) || (*marker == detail::traits<CharT>::alpha_E))
    {
        ++marker;
        const bool is_exponent_negative = *marker == detail::traits<CharT>::alpha_minus;
        if (is_exponent_negative || *marker == detail::traits<CharT>::alpha_plus)
        {
            ++marker;
        }
        int exponent = 0;
        const int max = std::numeric_limits<int>::max();
        while (true)
        {
            const unsigned delta = *marker - detail::traits<CharT>::alpha_0;
            if (delta > 9)
                break;
            if (max / 10 < exponent) // Overflow
            {
                output = std::numeric_limits<T>::infinity();
                return;
            }
            exponent *= 10;
            exponent += delta;
            ++marker;
        }
        result *= detail::power10<T>(is_exponent_negative ? -exponent : exponent);
    }
    output = is_negative ? -result : result;
}

template <typename CharT>
template <typename T>
void basic_decoder<CharT>::string_value(T& result) const
{
    // FIXME: Validate string [ http://www.w3.org/International/questions/qa-forms-utf-8 ]
    assert(current.code == token::detail::code::string);

    const auto approximateSize = literal().size();
    assert(approximateSize >= 2);
    if (result.capacity() < approximateSize)
        result.reserve(approximateSize);

    // Skip initial and terminating quotes
    assert(literal().front() == traits<CharT>::alpha_quote);
    assert(literal().back() == traits<CharT>::alpha_quote);
    const auto end = literal().end() - 1;
    auto it = literal().begin() + 1;
    int segment_index = 0;
    while (it != end)
    {
        switch (traits<CharT>::to_category(*it))
        {
        case traits_category::escape:
        {
            assert(std::distance(it, end) >= 2);
            ++it;
            switch (*it)
            {
            case traits<CharT>::alpha_quote:
            case traits<CharT>::alpha_reverse_solidus:
            case traits<CharT>::alpha_solidus:
                result += *it;
                break;

            case traits<CharT>::alpha_b:
                result += traits<CharT>::alpha_backspace;
                break;

            case traits<CharT>::alpha_f:
                result += traits<CharT>::alpha_formfeed;
                break;

            case traits<CharT>::alpha_n:
                result += traits<CharT>::alpha_newline;
                break;

            case traits<CharT>::alpha_r:
                result += traits<CharT>::alpha_return;
                break;

            case traits<CharT>::alpha_t:
                result += traits<CharT>::alpha_tab;
                break;

            case traits<CharT>::alpha_u:
                {
                    // Convert \uXXXX value to UTF-8
                    assert(std::distance(it, end) >= 5);
                    std::uint32_t number = (std::uint32_t(traits<CharT>::to_int(it[1])) << 12)
                        + (std::uint32_t(traits<CharT>::to_int(it[2])) << 8)
                        + (std::uint32_t(traits<CharT>::to_int(it[3])) << 4)
                        + (std::uint32_t(traits<CharT>::to_int(it[4])));
                    it += 4;
                    if (number <= 0x007F)
                    {
                        // 0xxxxxxx
                        result += std::char_traits<CharT>::to_char_type(number & 0x7F);
                    }
                    else if (number <= 0x07FF)
                    {
                        // 110xxxxx 10xxxxxx
                        result += 0xC0 | std::char_traits<CharT>::to_char_type((number >> 6) & 0x1F);
                        result += 0x80 | std::char_traits<CharT>::to_char_type(number & 0x3F);
                    }
                    else
                    {
                        // 1110xxxx 10xxxxxx 10xxxxxx
                        result += 0xE0 | std::char_traits<CharT>::to_char_type((number >> 12) & 0x0F);
                        result += 0x80 | std::char_traits<CharT>::to_char_type((number >> 6) & 0x3F);
                        result += 0x80 | std::char_traits<CharT>::to_char_type(number & 0x3F);
                    }
                }
                break;

            default:
                assert(false);
                break;
            }
            ++it;
            continue;
        }

        case traits_category::narrow:
        {
            const auto head = it;
            if (segment_index < current.scan.string.length)
            {
                it = current.scan.string.segment[segment_index];
                ++segment_index;
            }
            else
            {
                it = traits<CharT>::skip_narrow(++it);
            }
            result.append(head, it);
            continue;
        }

        case traits_category::extra_1:
            result += it[0];
            result += it[1];
            it += 2;
            continue;

        case traits_category::extra_2:
            result += it[0];
            result += it[1];
            result += it[2];
            it += 3;
            continue;

        case traits_category::extra_3:
            result += it[0];
            result += it[1];
            result += it[2];
            result += it[3];
            it += 4;
            continue;

        case traits_category::extra_4:
            result += it[0];
            result += it[1];
            result += it[2];
            result += it[3];
            result += it[4];
            it += 5;
            continue;

        case traits_category::extra_5:
            result += it[0];
            result += it[1];
            result += it[2];
            result += it[3];
            result += it[4];
            result += it[5];
            it += 6;
            continue;

        default:
        {
            result += *it;
            ++it;
            continue;
        }
        }
    }
}

template <typename CharT>
auto basic_decoder<CharT>::literal() const BOOST_NOEXCEPT -> const view_type&
{
    return current.view;
}

template <typename CharT>
auto basic_decoder<CharT>::tail() const BOOST_NOEXCEPT -> const view_type&
{
    return input;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_token(token::detail::code::value type) BOOST_NOEXCEPT
{
    current.view = view_type(input.begin(), 1);
    input.remove_front();
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_f_keyword() BOOST_NOEXCEPT
{
    token::detail::code::value type = token::detail::code::false_value;
    auto marker = input.begin();

    const std::size_t false_length = 5;
    if (input.size() < false_length)
    {
        type = token::detail::code::error_unexpected_token;
    }
    else if ((marker[1] == traits<CharT>::alpha_a) &&
             (marker[2] == traits<CharT>::alpha_l) &&
             (marker[3] == traits<CharT>::alpha_s) &&
             (marker[4] == traits<CharT>::alpha_e))
    {
        input.remove_front(false_length);
        if (!at_keyword_end())
        {
            while (!at_keyword_end())
                input.remove_front();
            type = token::detail::code::error_unexpected_token;
        }
    }
    else
    {
        type = token::detail::code::error_unexpected_token;
    }
    current.view = view_type(marker, input.begin());
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_n_keyword() BOOST_NOEXCEPT
{
    token::detail::code::value type = token::detail::code::null;
    auto marker = input.begin();

    const std::size_t null_size = 4;
    if (input.size() < null_size)
    {
        type = token::detail::code::error_unexpected_token;
    }
    else if ((marker[1] == traits<CharT>::alpha_u) &&
             (marker[2] == traits<CharT>::alpha_l) &&
             (marker[3] == traits<CharT>::alpha_l))
    {
        input.remove_front(null_size);
        if (!at_keyword_end())
        {
            while (!at_keyword_end())
                input.remove_front();
            type = token::detail::code::error_unexpected_token;
        }
    }
    else
    {
        type = token::detail::code::error_unexpected_token;
    }
    current.view = view_type(marker, input.begin());
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_t_keyword() BOOST_NOEXCEPT
{
    token::detail::code::value type = token::detail::code::true_value;
    auto marker = input.begin();

    const std::size_t true_size = 4;
    if (input.size() < true_size)
    {
        type = token::detail::code::error_unexpected_token;
    }
    else if ((marker[1] == traits<CharT>::alpha_r) &&
             (marker[2] == traits<CharT>::alpha_u) &&
             (marker[3] == traits<CharT>::alpha_e))
    {
        input.remove_front(true_size);
        if (!at_keyword_end())
        {
            while (!at_keyword_end())
                input.remove_front();
            type = token::detail::code::error_unexpected_token;
        }
    }
    else
    {
        type = token::detail::code::error_unexpected_token;
    }
    current.view = view_type(marker, input.begin());
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_number() BOOST_NOEXCEPT
{
    auto begin = input.begin();
    token::detail::code::value type = token::detail::code::integer;

    const bool is_negative = (*begin == traits<CharT>::alpha_minus);
    if (is_negative)
    {
        input.remove_front(); // Skip '-'
        if (input.empty())
        {
            type = token::detail::code::end;
            goto end;
        }
    }

    {
        auto digit_begin = input.begin();
        if (input.front() == traits<CharT>::alpha_0)
        {
            input.remove_front();
            if (!input.empty() && traits<CharT>::is_digit(input.front()))
            {
                // Leading zeros not allowed
                type = token::detail::code::error_invalid_value;
                goto end;
            }
        }
        else
        {
            while (!input.empty() && traits<CharT>::is_digit(input.front()))
            {
                input.remove_front();
            }
        }
        if (input.begin() == digit_begin)
        {
            // No digits found
            type = token::detail::code::error_unexpected_token;
            goto end;
        }
        if (!input.empty())
        {
            if (input.front() == traits<CharT>::alpha_dot)
            {
                type = token::detail::code::real;
                input.remove_front();
                if (input.empty())
                {
                    type = token::detail::code::end;
                    goto end;
                }
                auto it = input.begin();
                while (true)
                {
                    if (!traits<CharT>::is_digit(it[0])) { break; }
                    if (!traits<CharT>::is_digit(it[1])) { it += 1; break; }
                    if (!traits<CharT>::is_digit(it[2])) { it += 2; break; }
                    if (!traits<CharT>::is_digit(it[3])) { it += 3; break; }
                    it += 4;
                }
                if (it == input.begin())
                {
                    type = token::detail::code::error_unexpected_token;
                    goto end;
                }
                current.scan.real.fraction_end = it;
                input.remove_front(std::distance(input.begin(), it));
            }
            if (!input.empty() && ((input.front() == traits<CharT>::alpha_E) ||
                                   (input.front() == traits<CharT>::alpha_e)))
            {
                type = token::detail::code::real;
                input.remove_front();
                if (input.empty())
                {
                    type = token::detail::code::end;
                    goto end;
                }

                if (input.front() == traits<CharT>::alpha_plus)
                {
                    input.remove_front();
                    if (input.empty())
                    {
                        type = token::detail::code::end;
                        goto end;
                    }
                }
                else if (input.front() == traits<CharT>::alpha_minus)
                {
                    input.remove_front();
                    if (input.empty())
                    {
                        type = token::detail::code::end;
                        goto end;
                    }
                }
                auto exponent_begin = input.begin();
                while (!input.empty() && traits<CharT>::is_digit(input.front()))
                {
                    input.remove_front();
                }
                if (input.begin() == exponent_begin)
                {
                    type = token::detail::code::error_unexpected_token;
                    goto end;
                }
            }
        }
    }
 end:
    current.view = view_type(begin, input.begin());
    return type;
}

template <typename CharT>
token::detail::code::value basic_decoder<CharT>::next_string() BOOST_NOEXCEPT
{
    assert(input.front() == traits<CharT>::alpha_quote);

    current.scan.string.length = 0;
    auto marker = input.begin();
    const auto end = input.end();
    ++marker; // Skip initial '"'
    while (marker != end)
    {
        switch (traits<CharT>::to_category(*marker++))
        {
        case traits_category::escape:
            {
                // Handle escaped character
                if (marker == end)
                    goto eof;
                switch (*marker++)
                {
                case traits<CharT>::alpha_quote:
                case traits<CharT>::alpha_reverse_solidus:
                case traits<CharT>::alpha_solidus:
                case traits<CharT>::alpha_b:
                case traits<CharT>::alpha_f:
                case traits<CharT>::alpha_n:
                case traits<CharT>::alpha_r:
                case traits<CharT>::alpha_t:
                    break;

                case traits<CharT>::alpha_u:
                    switch (std::distance(marker, end))
                    {
                    case 3:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto case_2;
                    case 2:
                    case_2:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto case_1;
                    case 1:
                    case_1:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto case_0;
                    case 0:
                    case_0:
                        goto eof;

                    default:
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits<CharT>::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        break;
                    }
                    break;

                default:
                    goto error;
                }
            }
            break;

        case traits_category::quote:
            // Handle end of string
            current.view = view_type(input.begin(), marker); // Includes terminating '"'
            input.remove_front(std::distance(input.begin(), marker));
            return token::detail::code::string;

        case traits_category::narrow:
            {
                marker = traits<CharT>::skip_narrow(marker);
                if (current.scan.string.length < segment_max)
                {
                    current.scan.string.segment[current.scan.string.length] = marker;
                    ++current.scan.string.length;
                }
            }
            break;

        case traits_category::extra_5:
            // Skip UTF-8 characters
            // Check for 10xxxxxx pattern of subsequent bytes
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_4;
        case traits_category::extra_4:
        case_extra_4:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_3;
        case traits_category::extra_3:
        case_extra_3:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_2;
        case traits_category::extra_2:
        case_extra_2:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_1;
        case traits_category::extra_1:
        case_extra_1:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            break;

        case traits_category::illegal:
            goto error;
        }
    }
 eof:
 error:
    current.view = view_type(input.begin(), marker);
    return token::detail::code::error_unexpected_token;
}

template <typename CharT>
void basic_decoder<CharT>::skip_whitespaces() BOOST_NOEXCEPT
{
    auto it = input.begin();
    while (true)
    {
        if (!traits<CharT>::is_space(it[0])) { break; }
        if (!traits<CharT>::is_space(it[1])) { it += 1; break; }
        if (!traits<CharT>::is_space(it[2])) { it += 2; break; }
        if (!traits<CharT>::is_space(it[3])) { it += 3; break; }
        it += 4;
    }
    input.remove_front(std::distance(input.begin(), it));
}

template <typename CharT>
bool basic_decoder<CharT>::at_keyword_end() const BOOST_NOEXCEPT
{
    if (input.empty())
    {
        return true;
    }
    return !traits<CharT>::is_keyword(input.front());
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP
