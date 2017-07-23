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

#include <cstdlib>
#include <limits>
#include <string>
#include <sstream>
#include <iomanip>
#include <locale>
#include <trial/protocol/core/detail/string_view.hpp>
#include <trial/protocol/core/char_traits.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

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
        return std::strtof(view.data(), nullptr);
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
        return std::strtod(view.data(), nullptr);
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
        return std::strtold(view.data(), nullptr);
    }
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_FROM_STRING_HPP
