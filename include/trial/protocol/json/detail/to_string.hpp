#ifndef TRIAL_PROTOCOL_JSON_DETAIL_TO_STRING_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_TO_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <limits>
#include <sstream>
#include <iomanip>
#include <locale>
#include <trial/protocol/buffer/char_traits.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

template <typename CharT>
std::basic_string<CharT, buffer::char_traits<CharT>> to_string(double value)
{
    // Workaround for CharT = unsigned char, which std::locale does not support
    std::ostringstream stream;
    stream.imbue(std::locale::classic());
    stream << std::showpoint << std::setprecision(std::numeric_limits<double>::digits10) << value;
    std::string work = stream.str();
    return {work.begin(), work.end()};
}

template <typename CharT>
std::basic_string<CharT, buffer::char_traits<CharT>> to_string(float value)
{
    // Workaround for CharT = unsigned char, which std::locale does not support
    std::ostringstream stream;
    stream.imbue(std::locale::classic());
    stream << std::showpoint << std::setprecision(std::numeric_limits<float>::digits10) << value;
    std::string work = stream.str();
    return {work.begin(), work.end()};
}

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_TO_STRING_HPP
