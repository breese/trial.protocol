#ifndef TRIAL_PROTOCOL_DYNAMIC_STD_MAP_HPP
#define TRIAL_PROTOCOL_DYNAMIC_STD_MAP_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <map>
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

template <typename CharT, typename Key, typename Value>
struct convert_overloader<
    basic_variable<CharT>,
    std::map<Key, Value>>
{
    static basic_variable<CharT> convert(const std::map<Key, Value>& map,
                                         std::error_code&)
    {
        auto result = basic_map<CharT>::make();
        for (const auto& entry : map)
        {
            result += map::make(entry.first, entry.second);
        }
        return result;
    }
};

template <typename CharT, typename Key, typename Value>
struct convert_overloader<
    std::map<Key, Value>,
    basic_variable<CharT>>
{
    static std::map<Key, Value> convert(const basic_variable<CharT>& map,
                                        std::error_code& error)
    {
        std::map<Key, Value> result;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            if (it->template is<Value>())
                result.emplace(it.key().template value<Key>(error),
                               it->template value<Value>(error));
            else
                error = dynamic::make_error_code(incompatible_type);

            if (error)
                return {};
        }
        return result;
    }
};

// Special case for std::map<T, variable>

template <typename CharT, typename Key>
struct convert_overloader<
    std::map<Key, basic_variable<CharT>>,
    basic_variable<CharT>>
{
    static std::map<Key, basic_variable<CharT>> convert(const basic_variable<CharT>& map,
                                                        std::error_code& error)
    {
        std::map<Key, basic_variable<CharT>> result;
        for (auto it = map.begin(); it != map.end(); ++it)
        {
            result.emplace(it.key().template value<Key>(error), it.value());

            if (error)
                return {};
        }
        return result;
    }
};

} // namespace detail
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_STD_MAP_HPP
