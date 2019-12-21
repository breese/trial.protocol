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

template <typename Real>
Real power(Real number, int exponent)
{
    switch (exponent)
    {
    case 0: return Real(1.0);
    case 1: return number * Real(1E0);
    case 2: return number * Real(1E1);
    case 3: return number * Real(1E2);
    case 4: return number * Real(1E3);
    case 5: return number * Real(1E4);
    case 6: return number * Real(1E5);
    case 7: return number * Real(1E6);
    case 8: return number * Real(1E7);
    case 9: return number * Real(1E8);
    case 10: return number * Real(1E9);
    default: return std::pow(number, exponent);
    }
}

template <typename CharT, typename RealT>
RealT parse(const CharT *head) noexcept
{
    static constexpr RealT zero = RealT(0.0);
    static constexpr RealT one = RealT(1.0);
    static constexpr RealT base = RealT(10.0);

    RealT result = zero;
    const bool is_negative = *head == detail::traits<CharT>::alpha_minus;
    if (is_negative)
    {
        ++head;
    }
    while (true)
    {
        const unsigned delta = *head - detail::traits<CharT>::alpha_0;
        if (delta > 9)
            break;
        result *= base;
        result += delta;
        ++head;
    }
    if (*head == '.')
    {
        ++head;
        RealT fraction = zero;
        RealT scale = one;
        while (true)
        {
            const unsigned delta = *head - detail::traits<CharT>::alpha_0;
            if (delta > 9)
                break;
            scale *= base;
            fraction *= base;
            fraction += delta;
            ++head;
        }
        result += fraction / scale;
    }
    if ((*head == detail::traits<CharT>::alpha_e) || (*head == detail::traits<CharT>::alpha_E))
    {
        ++head;
        const bool is_exponent_negative = *head == detail::traits<CharT>::alpha_minus;
        if (is_exponent_negative || *head == detail::traits<CharT>::alpha_plus)
        {
            ++head;
        }
        int exponent = 0;
        const int max = std::numeric_limits<int>::max();
        while (true)
        {
            const unsigned delta = *head - detail::traits<CharT>::alpha_0;
            if (delta > 9)
                break;
            if (max / 10 < exponent) // Overflow
                return std::numeric_limits<RealT>::infinity();
            exponent *= 10;
            exponent += delta;
            ++head;
        }
        result *= detail::power<RealT>(base, is_exponent_negative ? -exponent : exponent);
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
        return detail::parse<CharT, float>(view.data());
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
        return detail::parse<CharT, double>(view.data());
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
        return detail::parse<CharT, long double>(view.data());
    }
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_FROM_STRING_HPP
