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
#include <trial/protocol/json/detail/scan.hpp>
#include <trial/protocol/json/error.hpp>

// http://tools.ietf.org/html/rfc8259

//-----------------------------------------------------------------------------

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
basic_decoder<CharT>::basic_decoder(const_pointer first,
                                    const_pointer last)
    : input(first, last),
      current{token::code::uninitialized, {}, {}}
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
void basic_decoder<CharT>::code(token::code::value code) noexcept
{
    current.code = code;
}

template <typename CharT>
token::code::value basic_decoder<CharT>::code() const noexcept
{
    return current.code;
}

template <typename CharT>
std::error_code basic_decoder<CharT>::error() const noexcept
{
    return json::make_error_code(to_errc(code()));
}

template <typename CharT>
void basic_decoder<CharT>::next() noexcept
{
    if (current.code < 0)
        return; // Already marked as error
    if (current.code == token::code::end)
    {
        current.code = token::code::error_unexpected_token;
        return;
    }

    skip_whitespaces();

    if (input.empty())
    {
        current.code = token::code::value::end;
        return;
    }

    switch (input.front())
    {
    case traits::alphabet<CharT>::letter_f:
        return next_f_keyword();

    case traits::alphabet<CharT>::letter_n:
        return next_n_keyword();

    case traits::alphabet<CharT>::letter_t:
        return next_t_keyword();

    case traits::alphabet<CharT>::minus:
    case traits::alphabet<CharT>::digit_0:
    case traits::alphabet<CharT>::digit_1:
    case traits::alphabet<CharT>::digit_2:
    case traits::alphabet<CharT>::digit_3:
    case traits::alphabet<CharT>::digit_4:
    case traits::alphabet<CharT>::digit_5:
    case traits::alphabet<CharT>::digit_6:
    case traits::alphabet<CharT>::digit_7:
    case traits::alphabet<CharT>::digit_8:
    case traits::alphabet<CharT>::digit_9:
        return next_number();

    case traits::alphabet<CharT>::quote:
        return next_string();

    case traits::alphabet<CharT>::brace_open:
        return next_token(token::code::begin_object);

    case traits::alphabet<CharT>::brace_close:
        return next_token(token::code::end_object);

    case traits::alphabet<CharT>::bracket_open:
        return next_token(token::code::begin_array);

    case traits::alphabet<CharT>::bracket_close:
        return next_token(token::code::end_array);

    case traits::alphabet<CharT>::comma:
        return next_token(token::code::error_value_separator);

    case traits::alphabet<CharT>::colon:
        return next_token(token::code::error_name_separator);

    default:
        current.code = token::code::error_unexpected_token;
        break;
    }
}

template <typename CharT>
template <typename T>
auto basic_decoder<CharT>::signed_value(T& output) const noexcept -> json::errc
{
    static_assert(std::is_signed<T>::value, "T must be signed integer");

    using unsigned_type = typename std::make_unsigned<T>::type;
    assert(current.code == token::code::integer);

    auto marker = current.view.begin();

    unsigned_type result = {};
    const bool is_negative = (*marker == traits::alphabet<CharT>::minus);
    if (is_negative)
    {
        ++marker; // Skip minus

        const auto errc = unsigned_value(marker,
                                         current.scan.number.integer_tail,
                                         result);
        if (errc == json::no_error)
        {
            if (result > unsigned_type(-std::numeric_limits<T>::lowest()))
                return json::invalid_value;
            output = -T(result);
        }
        return  errc;
    }
    else
    {
        const auto errc = unsigned_value(marker,
                                         current.scan.number.integer_tail,
                                         result);
        if (errc == json::no_error)
        {
            if (result > unsigned_type(std::numeric_limits<T>::max()))
                return json::invalid_value;
            output = T(result);
        }
        return errc;
    }
}

template <typename CharT>
template <typename T>
auto basic_decoder<CharT>::unsigned_value(const_pointer head,
                                          const_pointer tail,
                                          T& output) const noexcept -> json::errc
{
    static_assert(std::is_unsigned<T>::value, "T must be unsigned integer");

    // Coerce into largest supported integer type
    std::uint64_t result = {};
    const auto errc = unsigned_value(head, tail, result);
    if (errc == no_error)
        output = T(result);
    return errc;
}

template <typename CharT>
auto basic_decoder<CharT>::unsigned_value(const_pointer marker,
                                          const_pointer tail,
                                          std::uint8_t& output) const noexcept -> json::errc
{
    using T = std::uint8_t;

    static constexpr T number[][10] = {
        { UINT8_C(0), UINT8_C(10), UINT8_C(20), UINT8_C(30), UINT8_C(40), UINT8_C(50), UINT8_C(60), UINT8_C(70), UINT8_C(80), UINT8_C(90) },
        { UINT8_C(0), UINT8_C(100), UINT8_C(200) }
    };

    T result = {};
    switch (tail - marker)
    {
    default:
        goto error;

    case 3:
    {
        const auto digit3 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit3 > 2)
            goto error;
        result += number[1][digit3];
        if (digit3 < 2)
            goto digit_2;

        const auto digit2 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit2 > 5)
            goto error;
        result += number[0][digit2];
        if (digit2 < 5)
            goto digit_1;

        const auto digit1 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit1 > 5)
            goto error;
        result += digit1;

        break;
    }
    case 2:
    digit_2:
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 1:
    digit_1:
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    }

    output = result;
    return json::no_error;

error:
    return json::invalid_value;
}

template <typename CharT>
auto basic_decoder<CharT>::unsigned_value(const_pointer marker,
                                          const_pointer tail,
                                          std::uint16_t& output) const noexcept -> json::errc
{
    using T = std::uint16_t;

    static constexpr T number[][10] = {
        { UINT16_C(0), UINT16_C(10), UINT16_C(20), UINT16_C(30), UINT16_C(40), UINT16_C(50), UINT16_C(60), UINT16_C(70), UINT16_C(80), UINT16_C(90) },
        { UINT16_C(0), UINT16_C(100), UINT16_C(200), UINT16_C(300), UINT16_C(400), UINT16_C(500), UINT16_C(600), UINT16_C(700), UINT16_C(800), UINT16_C(900) },
        { UINT16_C(0), UINT16_C(1000), UINT16_C(2000), UINT16_C(3000), UINT16_C(4000), UINT16_C(5000), UINT16_C(6000), UINT16_C(7000), UINT16_C(8000), UINT16_C(9000) },
        { UINT16_C(0), UINT16_C(10000), UINT16_C(20000), UINT16_C(30000), UINT16_C(40000), UINT16_C(50000), UINT16_C(60000) }
    };

    T result = {};
    switch (tail - marker)
    {
    default:
        goto error;

    case 5:
    {
        const auto digit5 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit5 > 6)
            goto error;
        result += number[3][digit5];
        if (digit5 < 6)
            goto digit_4;
        assert(digit5 == 6);

        const auto digit4 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit4 > 5)
            goto error;
        result += number[2][digit4];
        if (digit4 < 5)
            goto digit_3;
        assert(digit4 == 5);

        const auto digit3 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit3 > 5)
            goto error;
        result += number[1][digit3];
        if (digit3 < 5)
            goto digit_2;
        assert(digit3 == 5);

        const auto digit2 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit2 > 3)
            goto error;
        result += number[0][digit2];
        if (digit2 < 3)
            goto digit_1;
        assert(digit2 == 3);

        const auto digit1 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit1 > 5)
            goto error;
        result += digit1;

        break;
    }

    case 4:
    digit_4:
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 3:
    digit_3:
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 2:
    digit_2:
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 1:
    digit_1:
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    }

    output = result;
    return json::no_error;

error:
    return json::invalid_value;
}

template <typename CharT>
auto basic_decoder<CharT>::unsigned_value(const_pointer marker,
                                          const_pointer tail,
                                          std::uint32_t& output) const noexcept -> json::errc
{
    using T = std::uint32_t;

    static constexpr T number[][10] = {
        { UINT32_C(0), UINT32_C(10), UINT32_C(20), UINT32_C(30), UINT32_C(40), UINT32_C(50), UINT32_C(60), UINT32_C(70), UINT32_C(80), UINT32_C(90) },
        { UINT32_C(0), UINT32_C(100), UINT32_C(200), UINT32_C(300), UINT32_C(400), UINT32_C(500), UINT32_C(600), UINT32_C(700), UINT32_C(800), UINT32_C(900) },
        { UINT32_C(0), UINT32_C(1000), UINT32_C(2000), UINT32_C(3000), UINT32_C(4000), UINT32_C(5000), UINT32_C(6000), UINT32_C(7000), UINT32_C(8000), UINT32_C(9000) },
        { UINT32_C(0), UINT32_C(10000), UINT32_C(20000), UINT32_C(30000), UINT32_C(40000), UINT32_C(50000), UINT32_C(60000), UINT32_C(70000), UINT32_C(80000), UINT32_C(90000) },
        { UINT32_C(0), UINT32_C(100000), UINT32_C(200000), UINT32_C(300000), UINT32_C(400000), UINT32_C(500000), UINT32_C(600000), UINT32_C(700000), UINT32_C(800000), UINT32_C(900000) },
        { UINT32_C(0), UINT32_C(1000000), UINT32_C(2000000), UINT32_C(3000000), UINT32_C(4000000), UINT32_C(5000000), UINT32_C(6000000), UINT32_C(7000000), UINT32_C(8000000), UINT32_C(9000000) },
        { UINT32_C(0), UINT32_C(10000000), UINT32_C(20000000), UINT32_C(30000000), UINT32_C(40000000), UINT32_C(50000000), UINT32_C(60000000), UINT32_C(70000000), UINT32_C(80000000), UINT32_C(90000000) },
        { UINT32_C(0), UINT32_C(100000000), UINT32_C(200000000), UINT32_C(300000000), UINT32_C(400000000), UINT32_C(500000000), UINT32_C(600000000), UINT32_C(700000000), UINT32_C(800000000), UINT32_C(900000000) },
        { UINT32_C(0), UINT32_C(1000000000), UINT32_C(2000000000), UINT32_C(3000000000), UINT32_C(4000000000) }
    };

    T result = {};
    switch (tail - marker)
    {
    default:
        goto error;

    case 10:
    {
        const auto digit10 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit10 > 4)
            goto error;
        result += number[8][digit10];
        if (digit10 < 4)
            goto digit_9;
        assert(digit10 == 4);

        const auto digit9 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit9 > 2)
            goto error;
        result += number[7][digit9];
        if (digit9 < 2)
            goto digit_8;
        assert(digit9 == 2);

        const auto digit8 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        assert(digit8 <= 9);
        result += number[6][digit8];
        if (digit8 < 9)
            goto digit_7;
        assert(digit8 == 9);

        const auto digit7 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit7 > 4)
            goto error;
        result += number[5][digit7];
        if (digit7 < 4)
            goto digit_6;
        assert(digit7 == 4);

        const auto digit6 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        assert(digit6 <= 9);
        result += number[4][digit6];
        if (digit6 < 9)
            goto digit_5;
        assert(digit6 == 9);

        const auto digit5 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit5 > 6)
            goto error;
        result += number[3][digit5];
        if (digit5 < 6)
            goto digit_4;
        assert(digit5 == 6);

        const auto digit4 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit4 > 7)
            goto error;
        result += number[2][digit4];
        if (digit4 < 7)
            goto digit_3;
        assert(digit4 == 7);

        const auto digit3 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit3 > 2)
            goto error;
        result += number[1][digit3];
        if (digit3 < 2)
            goto digit_2;
        assert(digit3 == 2);

        const auto digit2 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        assert(digit2 <= 9);
        result += number[0][digit2];
        if (digit2 < 9)
            goto digit_1;
        assert(digit2 == 9);

        const auto digit1 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit1 > 5)
            goto error;
        result += digit1;

        break;
    }

    case 9:
    digit_9:
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 8:
    digit_8:
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 7:
    digit_7:
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 6:
    digit_6:
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 5:
    digit_5:
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 4:
    digit_4:
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 3:
    digit_3:
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 2:
    digit_2:
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 1:
    digit_1:
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    }

    output = result;
    return json::no_error;

error:
    return json::invalid_value;
}

template <typename CharT>
auto basic_decoder<CharT>::unsigned_value(const_pointer marker,
                                          const_pointer tail,
                                          std::uint64_t& output) const noexcept -> json::errc
{
    using T = std::uint64_t;

    static constexpr T number[][10] = {
        { UINT64_C(0), UINT64_C(10), UINT64_C(20), UINT64_C(30), UINT64_C(40), UINT64_C(50), UINT64_C(60), UINT64_C(70), UINT64_C(80), UINT64_C(90) },
        { UINT64_C(0), UINT64_C(100), UINT64_C(200), UINT64_C(300), UINT64_C(400), UINT64_C(500), UINT64_C(600), UINT64_C(700), UINT64_C(800), UINT64_C(900) },
        { UINT64_C(0), UINT64_C(1000), UINT64_C(2000), UINT64_C(3000), UINT64_C(4000), UINT64_C(5000), UINT64_C(6000), UINT64_C(7000), UINT64_C(8000), UINT64_C(9000) },
        { UINT64_C(0), UINT64_C(10000), UINT64_C(20000), UINT64_C(30000), UINT64_C(40000), UINT64_C(50000), UINT64_C(60000), UINT64_C(70000), UINT64_C(80000), UINT64_C(90000) },
        { UINT64_C(0), UINT64_C(100000), UINT64_C(200000), UINT64_C(300000), UINT64_C(400000), UINT64_C(500000), UINT64_C(600000), UINT64_C(700000), UINT64_C(800000), UINT64_C(900000) },
        { UINT64_C(0), UINT64_C(1000000), UINT64_C(2000000), UINT64_C(3000000), UINT64_C(4000000), UINT64_C(5000000), UINT64_C(6000000), UINT64_C(7000000), UINT64_C(8000000), UINT64_C(9000000) },
        { UINT64_C(0), UINT64_C(10000000), UINT64_C(20000000), UINT64_C(30000000), UINT64_C(40000000), UINT64_C(50000000), UINT64_C(60000000), UINT64_C(70000000), UINT64_C(80000000), UINT64_C(90000000) },
        { UINT64_C(0), UINT64_C(100000000), UINT64_C(200000000), UINT64_C(300000000), UINT64_C(400000000), UINT64_C(500000000), UINT64_C(600000000), UINT64_C(700000000), UINT64_C(800000000), UINT64_C(900000000) },
        { UINT64_C(0), UINT64_C(1000000000), UINT64_C(2000000000), UINT64_C(3000000000), UINT64_C(4000000000), UINT64_C(5000000000), UINT64_C(6000000000), UINT64_C(7000000000), UINT64_C(8000000000), UINT64_C(9000000000) },
        { UINT64_C(0), UINT64_C(10000000000), UINT64_C(20000000000), UINT64_C(30000000000), UINT64_C(40000000000), UINT64_C(50000000000), UINT64_C(60000000000), UINT64_C(70000000000), UINT64_C(80000000000), UINT64_C(90000000000) },
        { UINT64_C(0), UINT64_C(100000000000), UINT64_C(200000000000), UINT64_C(300000000000), UINT64_C(400000000000), UINT64_C(500000000000), UINT64_C(600000000000), UINT64_C(700000000000), UINT64_C(800000000000), UINT64_C(900000000000) },
        { UINT64_C(0), UINT64_C(1000000000000), UINT64_C(2000000000000), UINT64_C(3000000000000), UINT64_C(4000000000000), UINT64_C(5000000000000), UINT64_C(6000000000000), UINT64_C(7000000000000), UINT64_C(8000000000000), UINT64_C(9000000000000) },
        { UINT64_C(0), UINT64_C(10000000000000), UINT64_C(20000000000000), UINT64_C(30000000000000), UINT64_C(40000000000000), UINT64_C(50000000000000), UINT64_C(60000000000000), UINT64_C(70000000000000), UINT64_C(80000000000000), UINT64_C(90000000000000) },
        { UINT64_C(0), UINT64_C(100000000000000), UINT64_C(200000000000000), UINT64_C(300000000000000), UINT64_C(400000000000000), UINT64_C(500000000000000), UINT64_C(600000000000000), UINT64_C(700000000000000), UINT64_C(800000000000000), UINT64_C(900000000000000) },
        { UINT64_C(0), UINT64_C(1000000000000000), UINT64_C(2000000000000000), UINT64_C(3000000000000000), UINT64_C(4000000000000000), UINT64_C(5000000000000000), UINT64_C(6000000000000000), UINT64_C(7000000000000000), UINT64_C(8000000000000000), UINT64_C(9000000000000000) },
        { UINT64_C(0), UINT64_C(10000000000000000), UINT64_C(20000000000000000), UINT64_C(30000000000000000), UINT64_C(40000000000000000), UINT64_C(50000000000000000), UINT64_C(60000000000000000), UINT64_C(70000000000000000), UINT64_C(80000000000000000), UINT64_C(90000000000000000) },
        { UINT64_C(0), UINT64_C(100000000000000000), UINT64_C(200000000000000000), UINT64_C(300000000000000000), UINT64_C(400000000000000000), UINT64_C(500000000000000000), UINT64_C(600000000000000000), UINT64_C(700000000000000000), UINT64_C(800000000000000000), UINT64_C(900000000000000000) },
        { UINT64_C(0), UINT64_C(1000000000000000000), UINT64_C(2000000000000000000), UINT64_C(3000000000000000000), UINT64_C(4000000000000000000), UINT64_C(5000000000000000000), UINT64_C(6000000000000000000), UINT64_C(7000000000000000000), UINT64_C(8000000000000000000), UINT64_C(9000000000000000000) },
        { UINT64_C(0), UINT64_C(10000000000000000000) }
    };

    T result = {};
    switch (tail - marker)
    {
    default:
        goto error;

    case 20:
    {
        const auto digit20 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit20 > 1)
            goto error;
        result += number[18][digit20];
        if (digit20 < 1)
            goto digit_19;
        assert(digit20 == 1);

        const auto digit19 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit19 > 8)
            goto error;
        result += number[17][digit19];
        if (digit19 < 8)
            goto digit_18;
        assert(digit19 == 8);

        const auto digit18 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit18 > 4)
            goto error;
        result += number[16][digit18];
        if (digit18 < 4)
            goto digit_17;
        assert(digit18 == 4);

        const auto digit17 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit17 > 4)
            goto error;
        result += number[15][digit17];
        if (digit17 < 4)
            goto digit_16;
        assert(digit17 == 4);

        const auto digit16 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit16 > 6)
            goto error;
        result += number[14][digit16];
        if (digit16 < 6)
            goto digit_15;
        assert(digit16 == 6);

        const auto digit15 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit15 > 7)
            goto error;
        result += number[13][digit15];
        if (digit15 < 7)
            goto digit_14;
        assert(digit15 == 7);

        const auto digit14 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit14 > 4)
            goto error;
        result += number[12][digit14];
        if (digit14 < 4)
            goto digit_13;
        assert(digit14 == 4);

        const auto digit13 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit13 > 4)
            goto error;
        result += number[11][digit13];
        if (digit13 < 4)
            goto digit_12;
        assert(digit13 == 4);

        const auto digit12 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit12 > 0)
            goto error;
        result += number[10][digit12];
        assert(digit12 == 0);

        const auto digit11 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit11 > 7)
            goto error;
        result += number[9][digit11];
        if (digit11 < 7)
            goto digit_10;
        assert(digit11 == 7);

        const auto digit10 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit10 > 3)
            goto error;
        result += number[8][digit10];
        if (digit10 < 3)
            goto digit_9;
        assert(digit10 == 3);

        const auto digit9 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit9 > 7)
            goto error;
        result += number[7][digit9];
        if (digit9 < 7)
            goto digit_8;
        assert(digit9 == 7);

        const auto digit8 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit8 > 0)
            goto error;
        result += number[6][digit8];
        assert(digit8 == 0);

        const auto digit7 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        assert(digit7 <= 9);
        result += number[5][digit7];
        if (digit7 < 9)
            goto digit_6;
        assert(digit7 == 9);

        const auto digit6 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit6 > 5)
            goto error;
        result += number[4][digit6];
        if (digit6 < 5)
            goto digit_5;
        assert(digit6 == 5);

        const auto digit5 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit5 > 5)
            goto error;
        result += number[3][digit5];
        if (digit5 < 5)
            goto digit_4;
        assert(digit5 == 5);

        const auto digit4 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit4 > 1)
            goto error;
        result += number[2][digit4];
        if (digit4 < 1)
            goto digit_3;
        assert(digit4 == 1);

        const auto digit3 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit3 > 6)
            goto error;
        result += number[1][digit3];
        if (digit3 < 6)
            goto digit_2;
        assert(digit3 == 6);

        const auto digit2 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit2 > 1)
            goto error;
        result += number[0][digit2];
        if (digit2 < 1)
            goto digit_1;
        assert(digit2 == 1);

        const auto digit1 = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
        if (digit1 > 5)
            goto error;
        result += digit1;

        break;
    }
    case 19:
    digit_19:
        result += number[17][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[16][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[15][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[14][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[13][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[12][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[11][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 18:
    digit_18:
        result += number[16][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[15][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[14][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[13][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[12][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[11][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 17:
    digit_17:
        result += number[15][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[14][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[13][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[12][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[11][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 16:
    digit_16:
        result += number[14][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[13][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[12][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[11][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 15:
    digit_15:
        result += number[13][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[12][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[11][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 14:
    digit_14:
        result += number[12][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[11][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 13:
    digit_13:
        result += number[11][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 12:
    digit_12:
        result += number[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 11:
        result += number[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 10:
    digit_10:
        result += number[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 9:
    digit_9:
        result += number[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 8:
    digit_8:
        result += number[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 7:
        result += number[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 6:
    digit_6:
        result += number[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 5:
    digit_5:
        result += number[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 4:
    digit_4:
        result += number[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 3:
    digit_3:
        result += number[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 2:
    digit_2:
        result += number[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    case 1:
    digit_1:
        result += T(*marker++ - traits::alphabet<CharT>::digit_0);
        break;
    }

    output = result;
    return json::no_error;

error:
    return json::invalid_value;
}

template <typename CharT>
template <typename T>
T basic_decoder<CharT>::signed_value() const
{
    if (current.code != token::code::integer)
        throw_on_error(errc::incompatible_type);

    T result = {};
    throw_on_error(signed_value(result));
    return result;
}

template <typename CharT>
template <typename T>
T basic_decoder<CharT>::unsigned_value() const
{
    if (current.code != token::code::integer)
        throw_on_error(errc::incompatible_type);

    T result = {};
    throw_on_error(unsigned_value(literal().begin(), literal().end(), result));
    return result;
}

template <typename CharT>
template <typename T>
auto basic_decoder<CharT>::unsigned_value(T& output) const noexcept -> json::errc
{
    if (current.code != token::code::integer)
        return errc::incompatible_type;
    if (literal().front() == traits::alphabet<CharT>::minus)
        return errc::invalid_value;

    return unsigned_value(literal().begin(), literal().end(), output);
}

template <typename CharT>
template <typename T>
void basic_decoder<CharT>::real_value(T& output) const noexcept
{
    static_assert(std::is_floating_point<T>::value, "T must be floating-point");

    assert(current.code == token::code::real);

    static constexpr T zero = T(0.0);
    static constexpr T one = T(1.0);
    static constexpr T base = T(10.0);

    const CharT *marker = current.view.begin();
    const bool is_negative = *marker == traits::alphabet<CharT>::minus;
    if (is_negative)
    {
        ++marker;
    }
    T result = unsigned(*marker++ - traits::alphabet<CharT>::digit_0);
    while (marker != current.scan.number.integer_tail)
    {
        result *= base;
        result += unsigned(*marker - traits::alphabet<CharT>::digit_0);
        ++marker;
    }
    if (*marker == traits::alphabet<CharT>::dot)
    {
        ++marker;
        T fraction = zero;

        static constexpr T fractions[][10] = {
            { 0e-1, 1e-1, 2e-1, 3e-1, 4e-1, 5e-1, 6e-1, 7e-1, 8e-1, 9e-1 },
            { 0e-2, 1e-2, 2e-2, 3e-2, 4e-2, 5e-2, 6e-2, 7e-2, 8e-2, 9e-2 },
            { 0e-3, 1e-3, 2e-3, 3e-3, 4e-3, 5e-3, 6e-3, 7e-3, 8e-3, 9e-3 },
            { 0e-4, 1e-4, 2e-4, 3e-4, 4e-4, 5e-4, 6e-4, 7e-4, 8e-4, 9e-4 },
            { 0e-5, 1e-5, 2e-5, 3e-5, 4e-5, 5e-5, 6e-5, 7e-5, 8e-5, 9e-5 },
            { 0e-6, 1e-6, 2e-6, 3e-6, 4e-6, 5e-6, 6e-6, 7e-6, 8e-6, 9e-6 },
            { 0e-7, 1e-7, 2e-7, 3e-7, 4e-7, 5e-7, 6e-7, 7e-7, 8e-7, 9e-7 },
            { 0e-8, 1e-8, 2e-8, 3e-8, 4e-8, 5e-8, 6e-8, 7e-8, 8e-8, 9e-8 },
            { 0e-9, 1e-9, 2e-9, 3e-9, 4e-9, 5e-9, 6e-9, 7e-9, 8e-9, 9e-9 },
            { 0e-10, 1e-10, 2e-10, 3e-10, 4e-10, 5e-10, 6e-10, 7e-10, 8e-10, 9e-10 },
            { 0e-11, 1e-11, 2e-11, 3e-11, 4e-11, 5e-11, 6e-11, 7e-11, 8e-11, 9e-11 },
            { 0e-12, 1e-12, 2e-12, 3e-12, 4e-12, 5e-12, 6e-12, 7e-12, 8e-12, 9e-12 },
            { 0e-13, 1e-13, 2e-13, 3e-13, 4e-13, 5e-13, 6e-13, 7e-13, 8e-13, 9e-13 },
            { 0e-14, 1e-14, 2e-14, 3e-14, 4e-14, 5e-14, 6e-14, 7e-14, 8e-14, 9e-14 },
            { 0e-15, 1e-15, 2e-15, 3e-15, 4e-15, 5e-15, 6e-15, 7e-15, 8e-15, 9e-15 },
            { 0e-16, 1e-16, 2e-16, 3e-16, 4e-16, 5e-16, 6e-16, 7e-16, 8e-16, 9e-16 },
            { 0e-17, 1e-17, 2e-17, 3e-17, 4e-17, 5e-17, 6e-17, 7e-17, 8e-17, 9e-17 },
            { 0e-18, 1e-18, 2e-18, 3e-18, 4e-18, 5e-18, 6e-18, 7e-18, 8e-18, 9e-18 }
        };

        const auto fraction_size = current.scan.number.fraction_tail - marker;
        switch (fraction_size)
        {
        default:
        {
            static constexpr T superbase = T(1e4);
            T scale = one;

            while (current.scan.number.fraction_tail - marker > 4)
            {
                const auto delta1000 = unsigned(marker[0] - traits::alphabet<CharT>::digit_0);
                const auto delta100 = unsigned(marker[1] - traits::alphabet<CharT>::digit_0);
                const auto delta10 = unsigned(marker[2] - traits::alphabet<CharT>::digit_0);
                const auto delta1 = unsigned(marker[3] - traits::alphabet<CharT>::digit_0);
                const auto delta = delta1000 * 1000 + delta100 * 100 + delta10 * 10 + delta1;
                fraction = fraction * superbase + delta;
                scale *= superbase;
                marker += 4;
            }

            while (current.scan.number.fraction_tail > marker)
            {
                const unsigned delta = *marker - traits::alphabet<CharT>::digit_0;
                scale *= base;
                fraction *= base;
                fraction += delta;
                ++marker;
            }
            fraction /= scale;
            break;
        }
        case 18:
        {
            const auto head = marker;
            marker += 18;
            std::uint64_t integer;
            unsigned_value(head, marker, integer);
            fraction += integer * T(1e-18);
            break;
        }
        case 17:
        {
            const auto head = marker;
            marker += 17;
            std::uint64_t integer;
            unsigned_value(head, marker, integer);
            fraction += integer * T(1e-17);
            break;
        }
        case 16:
        {
            const auto head = marker;
            marker += 16;
            std::uint64_t integer;
            unsigned_value(head, marker, integer);
            fraction += integer * T(1e-16);
            break;
        }
        case 15:
        {
            const auto head = marker;
            marker += 15;
            std::uint64_t integer;
            unsigned_value(head, marker, integer);
            fraction += integer * T(1e-15);
            break;
        }
        case 14:
        {
            const auto head = marker;
            marker += 14;
            std::uint64_t integer;
            unsigned_value(head, marker, integer);
            fraction += integer * T(1e-14);
            break;
        }
        case 13:
        {
            const auto head = marker;
            marker += 13;
            std::uint64_t integer;
            unsigned_value(head, marker, integer);
            fraction += integer * T(1e-13);
            break;
        }
        case 12:
        {
            const auto head = marker;
            marker += 12;
            std::uint64_t integer;
            unsigned_value(head, marker, integer);
            fraction += integer * T(1e-12);
            break;
        }
        case 11:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[6][unsigned(*marker++- traits::alphabet<CharT>::digit_0)];
            fraction += fractions[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[10][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 10:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[9][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 9:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[8][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 8:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[7][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 7:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[6][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 6:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[5][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 5:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[4][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 4:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[3][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 3:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[2][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 2:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            fraction += fractions[1][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 1:
            fraction += fractions[0][unsigned(*marker++ - traits::alphabet<CharT>::digit_0)];
            break;
        case 0:
            break;
        }
        result += fraction;
    }
    if ((*marker == traits::alphabet<CharT>::letter_e) || (*marker == traits::alphabet<CharT>::letter_E))
    {
        ++marker;
        const bool is_exponent_negative = *marker == traits::alphabet<CharT>::minus;
        if (is_exponent_negative || *marker == traits::alphabet<CharT>::plus)
        {
            ++marker;
        }
        int exponent = 0;
        const int max = std::numeric_limits<int>::max();
        while (true)
        {
            const unsigned delta = *marker - traits::alphabet<CharT>::digit_0;
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
T basic_decoder<CharT>::real_value() const
{
    if (current.code != token::code::real)
        throw_on_error(errc::incompatible_type);

    T result = {};
    real_value(result);
    return result;
}

template <typename CharT>
template <typename Collector>
void basic_decoder<CharT>::string_value(Collector& collector) const noexcept
{
    // FIXME: Validate string [ http://www.w3.org/International/questions/qa-forms-utf-8 ]
    assert(current.code == token::code::string);

    // Skip initial and terminating quotes
    assert(literal().front() == traits::alphabet<CharT>::quote);
    assert(literal().back() == traits::alphabet<CharT>::quote);
    const auto end = literal().end() - 1;
    auto it = literal().begin() + 1;
    int segment_index = 0;
    while (it != end)
    {
        switch (traits::to_category(*it))
        {
        case traits::category::escape:
        {
            assert(std::distance(it, end) >= 2);
            ++it;
            switch (*it)
            {
            case traits::alphabet<CharT>::quote:
            case traits::alphabet<CharT>::reverse_solidus:
            case traits::alphabet<CharT>::solidus:
                collector.push_back(*it);
                break;

            case traits::alphabet<CharT>::letter_b:
                collector.push_back(traits::alphabet<CharT>::backspace);
                break;

            case traits::alphabet<CharT>::letter_f:
                collector.push_back(traits::alphabet<CharT>::formfeed);
                break;

            case traits::alphabet<CharT>::letter_n:
                collector.push_back(traits::alphabet<CharT>::newline);
                break;

            case traits::alphabet<CharT>::letter_r:
                collector.push_back(traits::alphabet<CharT>::carriage_return);
                break;

            case traits::alphabet<CharT>::letter_t:
                collector.push_back(traits::alphabet<CharT>::tabulator);
                break;

            case traits::alphabet<CharT>::letter_u:
                {
                    // Convert \uXXXX value to UTF-8
                    assert(std::distance(it, end) >= 5);
                    std::uint32_t number =
                        (std::uint32_t(traits::to_hexint(it[1])) << 12)
                        + (std::uint32_t(traits::to_hexint(it[2])) << 8)
                        + (std::uint32_t(traits::to_hexint(it[3])) << 4)
                        + (std::uint32_t(traits::to_hexint(it[4])));
                    it += 4;
                    if (number <= 0x007F)
                    {
                        // 0xxxxxxx
                        collector.push_back(std::char_traits<CharT>::to_char_type(number & 0x7F));
                    }
                    else if (number <= 0x07FF)
                    {
                        // 110xxxxx 10xxxxxx
                        const value_type data[] = {
                            CharT(0xC0 | std::char_traits<CharT>::to_char_type((number >> 6) & 0x1F)),
                            CharT(0x80 | std::char_traits<CharT>::to_char_type(number & 0x3F))
                        };
                        collector.append(data, 2);
                    }
                    else
                    {
                        // 1110xxxx 10xxxxxx 10xxxxxx
                        const value_type data[] = {
                            CharT(0xE0 | std::char_traits<CharT>::to_char_type((number >> 12) & 0x0F)),
                            CharT(0x80 | std::char_traits<CharT>::to_char_type((number >> 6) & 0x3F)),
                            CharT(0x80 | std::char_traits<CharT>::to_char_type(number & 0x3F))
                        };
                        collector.append(data, 3);
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

        case traits::category::narrow:
        {
            const auto head = it;
            if (segment_index < current.scan.string.length)
            {
                it = current.scan.string.segment_tail[segment_index];
                ++segment_index;
            }
            else
            {
                it = scan_narrow(++it, end);
            }
            collector.append(head, std::distance(head, it));
            continue;
        }

        case traits::category::extra_1:
        {
            const auto head = it;
            if (segment_index < current.scan.string.length)
            {
                it = current.scan.string.segment_tail[segment_index];
                ++segment_index;
            }
            else
            {
                it += 2;
            }
            collector.append(head, std::distance(head, it));
            continue;
        }

        case traits::category::extra_2:
        {
            const auto head = it;
            if (segment_index < current.scan.string.length)
            {
                it = current.scan.string.segment_tail[segment_index];
                ++segment_index;
            }
            else
            {
                it += 3;
            }
            collector.append(head, std::distance(head, it));
            continue;
        }

        case traits::category::extra_3:
        {
            const auto head = it;
            if (segment_index < current.scan.string.length)
            {
                it = current.scan.string.segment_tail[segment_index];
                ++segment_index;
            }
            else
            {
                it += 4;
            }
            collector.append(head, std::distance(head, it));
            continue;
        }

        case traits::category::extra_4:
        {
            const auto head = it;
            if (segment_index < current.scan.string.length)
            {
                it = current.scan.string.segment_tail[segment_index];
                ++segment_index;
            }
            else
            {
                it += 5;
            }
            collector.append(head, std::distance(head, it));
            continue;
        }

        case traits::category::extra_5:
        {
            const auto head = it;
            if (segment_index < current.scan.string.length)
            {
                it = current.scan.string.segment_tail[segment_index];
                ++segment_index;
            }
            else
            {
                it += 6;
            }
            collector.append(head, std::distance(head, it));
            continue;
        }

        default:
        {
            collector.push_back(*it);
            ++it;
            continue;
        }
        }
    }
}

template <typename CharT>
template <typename T>
T basic_decoder<CharT>::string_value() const
{
    if (current.code != token::code::string)
        throw_on_error(errc::incompatible_type);

    T result = {};
    string_value(result);
    return result;
}

template <typename CharT>
auto basic_decoder<CharT>::literal() const noexcept -> const view_type&
{
    return current.view;
}

template <typename CharT>
auto basic_decoder<CharT>::tail() const noexcept -> const view_type&
{
    return input;
}

template <typename CharT>
void basic_decoder<CharT>::next_token(token::code::value type) noexcept
{
    current.view = view_type(input.begin(), 1);
    input.remove_front();
    current.code = type;
}

template <typename CharT>
void basic_decoder<CharT>::next_f_keyword() noexcept
{
    token::code::value type = token::code::false_value;
    auto marker = input.begin();

    const std::size_t false_length = 5;
    if (input.size() < false_length)
    {
        type = token::code::error_unexpected_token;
    }
    else
    {
        static constexpr const CharT false_suffix[] = {
            traits::alphabet<CharT>::letter_a,
            traits::alphabet<CharT>::letter_l,
            traits::alphabet<CharT>::letter_s,
            traits::alphabet<CharT>::letter_e
        };
        if (std::memcmp(&marker[1], false_suffix, sizeof(false_suffix)) == 0)
        {
            input.remove_front(false_length);
            if (!at_keyword_end())
            {
                while (!at_keyword_end())
                    input.remove_front();
                type = token::code::error_unexpected_token;
            }
        }
        else
        {
            type = token::code::error_unexpected_token;
        }
    }
    current.view = view_type(marker, input.begin());
    current.code = type;
}

template <typename CharT>
void basic_decoder<CharT>::next_n_keyword() noexcept
{
    token::code::value type = token::code::null;
    auto marker = input.begin();

    const std::size_t null_size = 4;
    if (input.size() < null_size)
    {
        type = token::code::error_unexpected_token;
    }
    else
    {
        static constexpr const CharT null_keyword[] = {
            traits::alphabet<CharT>::letter_n,
            traits::alphabet<CharT>::letter_u,
            traits::alphabet<CharT>::letter_l,
            traits::alphabet<CharT>::letter_l
        };
        if (std::memcmp(marker, null_keyword, sizeof(null_keyword)) == 0)
        {
            input.remove_front(null_size);
            if (!at_keyword_end())
            {
                while (!at_keyword_end())
                    input.remove_front();
                type = token::code::error_unexpected_token;
            }
        }
        else
        {
            type = token::code::error_unexpected_token;
        }
    }
    current.view = view_type(marker, input.begin());
    current.code = type;
}

template <typename CharT>
void basic_decoder<CharT>::next_t_keyword() noexcept
{
    token::code::value type = token::code::true_value;
    auto marker = input.begin();

    const std::size_t true_size = 4;
    if (input.size() < true_size)
    {
        type = token::code::error_unexpected_token;
    }
    else
    {
        static constexpr const CharT true_keyword[] = {
            traits::alphabet<CharT>::letter_t,
            traits::alphabet<CharT>::letter_r,
            traits::alphabet<CharT>::letter_u,
            traits::alphabet<CharT>::letter_e
        };
        if (std::memcmp(marker, true_keyword, sizeof(true_keyword)) == 0)
        {
            input.remove_front(true_size);
            if (!at_keyword_end())
            {
                while (!at_keyword_end())
                    input.remove_front();
                type = token::code::error_unexpected_token;
            }
        }
        else
        {
            type = token::code::error_unexpected_token;
        }
    }
    current.view = view_type(marker, input.begin());
    current.code = type;
}

template <typename CharT>
void basic_decoder<CharT>::next_number() noexcept
{
    // RFC 8259, section 6
    //
    // number = [ minus ] int [ frac ] [ exp ]
    //
    // int = zero / ( digit1-9 *digit)
    //
    // frac = dot 1*digit
    //
    // exp = e [ minus / plus ] 1*digit

    auto begin = input.begin();
    token::code::value type = token::code::integer;

    const bool is_negative = (*begin == traits::alphabet<CharT>::minus);
    if (is_negative)
    {
        input.remove_front(); // Skip '-'
        if (input.empty())
        {
            type = token::code::end;
            goto end;
        }
    }

    {
        auto digit_begin = input.begin();
        if (input.front() == traits::alphabet<CharT>::digit_0)
        {
            input.remove_front();
            if (!input.empty() && traits::is_digit(input.front()))
            {
                // Leading zeros not allowed
                type = token::code::error_invalid_value;
                goto end;
            }
        }
        else
        {
            const auto marker = scan_digit(input.begin(), input.end());
            input.remove_front(std::distance(input.begin(), marker));
        }
        if (input.begin() == digit_begin)
        {
            // No digits found
            type = token::code::error_unexpected_token;
            goto end;
        }
        current.scan.number.integer_tail = input.begin();
        if (!input.empty())
        {
            if (input.front() == traits::alphabet<CharT>::dot)
            {
                type = token::code::real;
                input.remove_front();
                if (input.empty())
                {
                    type = token::code::end;
                    goto end;
                }
                auto it = scan_digit(input.begin(), input.end());
                if (it == input.begin())
                {
                    type = token::code::error_unexpected_token;
                    goto end;
                }
                current.scan.number.fraction_tail = it;
                input.remove_front(std::distance(input.begin(), it));
            }
            if (!input.empty() && ((input.front() == traits::alphabet<CharT>::letter_E) ||
                                   (input.front() == traits::alphabet<CharT>::letter_e)))
            {
                type = token::code::real;
                input.remove_front();
                if (input.empty())
                {
                    type = token::code::end;
                    goto end;
                }

                if (input.front() == traits::alphabet<CharT>::plus)
                {
                    input.remove_front();
                    if (input.empty())
                    {
                        type = token::code::end;
                        goto end;
                    }
                }
                else if (input.front() == traits::alphabet<CharT>::minus)
                {
                    input.remove_front();
                    if (input.empty())
                    {
                        type = token::code::end;
                        goto end;
                    }
                }
                auto exponent_begin = input.begin();
                while (!input.empty() && traits::is_digit(input.front()))
                {
                    input.remove_front();
                }
                if (input.begin() == exponent_begin)
                {
                    type = token::code::error_unexpected_token;
                    goto end;
                }
            }
        }
    }
 end:
    current.view = view_type(begin, input.begin());
    current.code = type;
}

template <typename CharT>
void basic_decoder<CharT>::next_string() noexcept
{
    // RFC 8259, section 7
    //
    // string = quote *char quote
    //
    // char = unescaped /
    //        escape (
    //          quote
    //          reverse-solidus
    //          solidus
    //          backspace
    //          form-feed
    //          line-feed
    //          carriage-return
    //          tab
    //          'u' 4hexdig )

    assert(input.front() == traits::alphabet<CharT>::quote);

    current.scan.string.length = 0;
    auto marker = input.begin();
    const auto end = input.end();
    bool in_segment = false;
    ++marker; // Skip initial '"'
    while (marker != end)
    {
        switch (traits::to_category(*marker++))
        {
        case traits::category::escape:
            {
                // Handle escaped character
                if (marker == end)
                    goto eof;
                switch (*marker++)
                {
                case traits::alphabet<CharT>::quote:
                case traits::alphabet<CharT>::reverse_solidus:
                case traits::alphabet<CharT>::solidus:
                case traits::alphabet<CharT>::letter_b:
                case traits::alphabet<CharT>::letter_f:
                case traits::alphabet<CharT>::letter_n:
                case traits::alphabet<CharT>::letter_r:
                case traits::alphabet<CharT>::letter_t:
                    break;

                case traits::alphabet<CharT>::letter_u:
                    switch (std::distance(marker, end))
                    {
                    case 3:
                        if (!traits::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto case_2;
                    case 2:
                    case_2:
                        if (!traits::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto case_1;
                    case 1:
                    case_1:
                        if (!traits::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        goto case_0;
                    case 0:
                    case_0:
                        goto eof;

                    default:
                        if (!traits::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        if (!traits::is_hexdigit(*marker))
                            goto error;
                        ++marker;
                        break;
                    }
                    break;

                default:
                    goto error;
                }
                in_segment = false;
            }
            break;

        case traits::category::quote:
            // Handle end of string
            current.view = view_type(input.begin(), marker); // Includes terminating '"'
            input.remove_front(std::distance(input.begin(), marker));
            current.code = token::code::string;
            return;

        case traits::category::narrow:
            {
                marker = scan_narrow(marker, end);
                if (in_segment)
                {
                    current.scan.string.segment_tail[current.scan.string.length - 1] = marker;
                }
                else if (current.scan.string.length < segment_max)
                {
                    current.scan.string.segment_tail[current.scan.string.length] = marker;
                    ++current.scan.string.length;
                    in_segment = true;
                }
            }
            break;

        case traits::category::extra_5:
            // Skip UTF-8 characters
            // Check for 10xxxxxx pattern of subsequent bytes
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_4;
        case traits::category::extra_4:
        case_extra_4:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_3;
        case traits::category::extra_3:
        case_extra_3:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_2;
        case traits::category::extra_2:
        case_extra_2:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;
            goto case_extra_1;
        case traits::category::extra_1:
        case_extra_1:
            if (marker == end)
                goto error;
            if ((*marker & 0xC0) != 0x80)
                goto error;
            ++marker;

            if (in_segment)
            {
                current.scan.string.segment_tail[current.scan.string.length - 1] = marker;
            }
            else if (current.scan.string.length < segment_max)
            {
                current.scan.string.segment_tail[current.scan.string.length] = marker;
                ++current.scan.string.length;
                in_segment = true;
            }
            break;

        case traits::category::illegal:
            goto error;
        }
    }
 eof:
 error:
    current.view = view_type(input.begin(), marker);
    current.code = token::code::error_unexpected_token;
}

template <typename CharT>
void basic_decoder<CharT>::skip_whitespaces() noexcept
{
    const auto it = scan_whitespace(input.begin(), input.end());
    input.remove_front(std::distance(input.begin(), it));
}

template <typename CharT>
bool basic_decoder<CharT>::at_keyword_end() const noexcept
{
    if (input.empty())
    {
        return true;
    }
    return !traits::is_alpha(input.front());
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_DECODER_IPP
