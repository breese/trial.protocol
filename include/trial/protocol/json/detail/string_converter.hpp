#ifndef TRIAL_PROTOCOL_JSON_DETAIL_FROM_STRING_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_FROM_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>
#include <locale>
#include <trial/protocol/core/detail/string_view.hpp>
#include <trial/protocol/json/detail/traits.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename RealT>
RealT power10(int exponent)
{
    switch (exponent)
    {
    case 0: return RealT(1.0);
    case 1: return RealT(1E1);
    case 2: return RealT(1E2);
    case 3: return RealT(1E3);
    case 4: return RealT(1E4);
    case 5: return RealT(1E5);
    case 6: return RealT(1E6);
    case 7: return RealT(1E7);
    case 8: return RealT(1E8);
    case 9: return RealT(1E9);
    case 10: return RealT(1E10);
    default: return std::pow(RealT(10), exponent);
    }
}

template <typename RealT, typename CharT>
RealT from_string(const CharT * const head, std::size_t size) noexcept
{
    static constexpr RealT zero = RealT(0.0);
    static constexpr RealT one = RealT(1.0);
    static constexpr RealT base = RealT(10.0);

    const CharT *tail = head + size;
    const CharT *current = head;
    RealT result = zero;
    const bool is_negative = *current == detail::traits<CharT>::alpha_minus;
    if (is_negative)
    {
        ++current;
    }
    while (true)
    {
        const unsigned delta = *current - detail::traits<CharT>::alpha_0;
        if (delta > 9)
            break;
        result *= base;
        result += delta;
        ++current;
    }
    if (*current == '.')
    {
        ++current;
        RealT fraction = zero;
        RealT scale = one;
        // The following loop is an optimization. Measure the performance before making
        // any changes to this loop.
        static constexpr RealT superbase = RealT(1e4);
        while (tail - current > 4)
        {
            const auto delta1000 = unsigned(current[0] - detail::traits<CharT>::alpha_0);
            const auto delta100 = unsigned(current[1] - detail::traits<CharT>::alpha_0);
            const auto delta10 = unsigned(current[2] - detail::traits<CharT>::alpha_0);
            const auto delta1 = unsigned(current[3] - detail::traits<CharT>::alpha_0);
            const auto delta = delta1000 * 1000 + delta100 * 100 + delta10 * 10 + delta1;
            if (delta1000 > 9 || delta100 > 9 || delta10 > 9 || delta1 > 9)
                break;
            fraction = fraction * superbase + delta;
            scale *= superbase;
            current += 4;
        }

        while (tail > current)
        {
            const unsigned delta = *current - detail::traits<CharT>::alpha_0;
            if (delta > 9)
                break;
            scale *= base;
            fraction *= base;
            fraction += delta;
            ++current;
        }
        result += fraction / scale;
    }
    if ((*current == detail::traits<CharT>::alpha_e) || (*current == detail::traits<CharT>::alpha_E))
    {
        ++current;
        const bool is_exponent_negative = *current == detail::traits<CharT>::alpha_minus;
        if (is_exponent_negative || *current == detail::traits<CharT>::alpha_plus)
        {
            ++current;
        }
        int exponent = 0;
        const int max = std::numeric_limits<int>::max();
        while (true)
        {
            const unsigned delta = *current - detail::traits<CharT>::alpha_0;
            if (delta > 9)
                break;
            if (max / 10 < exponent) // Overflow
                return std::numeric_limits<RealT>::infinity();
            exponent *= 10;
            exponent += delta;
            ++current;
        }
        result *= detail::power10<RealT>(is_exponent_negative ? -exponent : exponent);
    }
    return is_negative ? -result : result;
}

template <typename CharT, typename ReturnType>
struct string_converter
{
};

template <typename CharT>
struct string_converter<CharT, float>
{
    using string = std::basic_string<CharT, core::char_traits<CharT>>;
    using string_view = core::detail::basic_string_view<CharT, core::char_traits<CharT>>;

    static string encode(float value)
    {
        // Workaround for CharT = unsigned char, which std::locale does not support
        std::ostringstream stream;
        stream.imbue(std::locale::classic());
        stream << std::showpoint << std::setprecision(std::numeric_limits<float>::digits10) << value;
        std::string work = stream.str();
        return {work.begin(), work.end()};
    }

    static float decode(const string_view& view)
    {
        return detail::from_string<float>(view.data(), view.size());
    }
};

template <typename CharT>
struct string_converter<CharT, double>
{
    using string = std::basic_string<CharT, core::char_traits<CharT>>;
    using string_view = core::detail::basic_string_view<CharT, core::char_traits<CharT>>;

    static string encode(double value)
    {
        // Workaround for CharT = unsigned char, which std::locale does not support
        std::ostringstream stream;
        stream.imbue(std::locale::classic());
        stream << std::showpoint << std::setprecision(std::numeric_limits<double>::digits10) << value;
        std::string work = stream.str();
        return {work.begin(), work.end()};
    }

    static double decode(const string_view& view)
    {
        return detail::from_string<double>(view.data(), view.size());
    }
};

template <typename CharT>
struct string_converter<CharT, long double>
{
    using string = std::basic_string<CharT, core::char_traits<CharT>>;
    using string_view = core::detail::basic_string_view<CharT, core::char_traits<CharT>>;

    static string encode(long double value)
    {
        // Workaround for CharT = unsigned char, which std::locale does not support
        std::ostringstream stream;
        stream.imbue(std::locale::classic());
        stream << std::showpoint << std::setprecision(std::numeric_limits<long double>::digits10) << value;
        std::string work = stream.str();
        return {work.begin(), work.end()};
    }

    static long double decode(const string_view& view)
    {
        return detail::from_string<long double>(view.data(), view.size());
    }
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_FROM_STRING_HPP
