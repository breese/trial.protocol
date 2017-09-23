#ifndef TRIAL_DYNAMIC_STD_VECTOR_HPP
#define TRIAL_DYNAMIC_STD_VECTOR_HPP

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
#include <trial/dynamic/variable.hpp>
#include <trial/dynamic/convert.hpp>

namespace trial
{
namespace dynamic
{
namespace detail
{

template <template <typename> class Allocator, typename T>
struct convert_overloader<
    basic_variable<Allocator>,
    std::vector<T>>
{
    static basic_variable<Allocator> convert(const std::vector<T>& array,
                                             std::error_code&)
    {
        auto result = basic_array<Allocator>::make();
        for (const auto& entry : array)
        {
            result += entry;
        }
        return result;
    }
};

template <template <typename> class Allocator, typename T>
struct convert_overloader<
    std::vector<T>,
    basic_variable<Allocator>>
{
    static std::vector<T> convert(const basic_variable<Allocator>& array,
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

template <template <typename> class Allocator>
struct convert_overloader<
    std::vector<basic_variable<Allocator>>,
    basic_variable<Allocator>>
{
    static std::vector<basic_variable<Allocator>> convert(const basic_variable<Allocator>& array,
                                                          std::error_code&)
    {
        std::vector<basic_variable<Allocator>> result;
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
} // namespace trial

#endif // TRIAL_DYNAMIC_STD_VECTOR_HPP
