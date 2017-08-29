#ifndef TRIAL_PROTOCOL_DYNAMIC_STD_VECTOR_HPP
#define TRIAL_PROTOCOL_DYNAMIC_STD_VECTOR_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <trial/protocol/dynamic/variable.hpp>
#include <trial/protocol/dynamic/convert.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{
namespace detail
{

template <typename CharT, typename T>
struct convert_overloader<
    basic_variable<CharT>,
    std::vector<T>>
{
    static basic_variable<CharT> convert(const std::vector<T>& array,
                                         std::error_code&)
    {
        auto result = basic_array<CharT>::make();
        for (const auto& entry : array)
        {
            result += entry;
        }
        return result;
    }
};

template <typename CharT, typename T>
struct convert_overloader<
    std::vector<T>,
    basic_variable<CharT>>
{
    static std::vector<T> convert(const basic_variable<CharT>& array,
                                  std::error_code& error)
    {
        std::vector<T> result;
        result.reserve(array.size());
        for (auto it = array.begin(); it != array.end(); ++it)
        {
            if (it->template is<T>())
                result.push_back(it->template value<T>(error));
            else
                error = dynamic::make_error_code(incompatible_type);

            if (error)
                return {};
        }
        return result;
    }
};

// Special case for std::vector<variable>

template <typename CharT>
struct convert_overloader<
    std::vector<basic_variable<CharT>>,
    basic_variable<CharT>>
{
    static std::vector<basic_variable<CharT>> convert(const basic_variable<CharT>& array,
                                                      std::error_code&)
    {
        std::vector<basic_variable<CharT>> result;
        result.reserve(array.size());
        for (auto it = array.begin(); it != array.end(); ++it)
        {
            result.push_back(*it);
        }
        return result;
    }
};

} // namespace detail
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_STD_VECTOR_HPP
