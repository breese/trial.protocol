#ifndef TRIAL_DYNAMIC_ALGORITHM_COUNT_HPP
#define TRIAL_DYNAMIC_ALGORITHM_COUNT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/dynamic/variable.hpp>

namespace trial
{
namespace dynamic
{

namespace key
{

template <template <typename> class Allocator, typename T>
auto count(const basic_variable<Allocator>& self,
           const T& other) -> typename basic_variable<Allocator>::size_type
{
    switch (self.symbol())
    {
    case symbol::null:
        return 0;

    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return (self == other) ? 1 : 0;

    case symbol::array:
    case symbol::map:
        {
            typename basic_variable<Allocator>::size_type result = 0;
            for (auto it = self.key_begin(); it != self.key_end(); ++it)
            {
                if (*it == other)
                    ++result;
            }
            return result;
        }
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

} // namespace key

namespace value
{

template <template <typename> class Allocator, typename T>
auto count(const basic_variable<Allocator>& self,
           const T& other) -> typename basic_variable<Allocator>::size_type
{
    switch (self.symbol())
    {
    case symbol::null:
        return 0;

    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return (self == other) ? 1 : 0;

    case symbol::array:
    case symbol::map:
        {
            typename basic_variable<Allocator>::size_type result = 0;
            for (auto it = self.begin(); it != self.end(); ++it)
            {
                if (*it == other)
                    ++result;
            }
            return result;
        }
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

} // namespace value

} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_ALGORITHM_COUNT_HPP
