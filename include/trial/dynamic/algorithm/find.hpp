#ifndef TRIAL_DYNAMIC_ALGORITHM_KEY_HPP
#define TRIAL_DYNAMIC_ALGORITHM_KEY_HPP

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

//-----------------------------------------------------------------------------
// key::find
//-----------------------------------------------------------------------------

namespace key
{

template <template <typename> class Allocator, typename T>
auto find(const basic_variable<Allocator>& self,
          const T& other) -> typename basic_variable<Allocator>::key_iterator
{
    switch (self.symbol())
    {
    case symbol::null:
        return self.key_end();

    case symbol::boolean:
    case symbol::integer:
    case symbol::number:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return (self == other) ? self.key_begin() : self.key_end();

    case symbol::array:
    case symbol::map:
        for (auto it = self.key_begin(); it != self.key_end(); ++it)
        {
            if (*it == other)
                return it;
        }
        return self.key_end();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

} // namespace key

//-----------------------------------------------------------------------------
// value::find
//-----------------------------------------------------------------------------

namespace value
{

template <template <typename> class Allocator, typename T>
auto find(basic_variable<Allocator>& self,
          const T& other) -> typename basic_variable<Allocator>::iterator
{
    switch (self.symbol())
    {
    case symbol::null:
        return self.end();

    case symbol::boolean:
    case symbol::integer:
    case symbol::number:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return (self == other) ? self.begin() : self.end();

    case symbol::array:
    case symbol::map:
        for (auto it = self.begin(); it != self.end(); ++it)
        {
            if (*it == other)
                return it;
        }
        return self.end();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <template <typename> class Allocator, typename T>
auto find(const basic_variable<Allocator>& self,
          const T& other) -> typename basic_variable<Allocator>::const_iterator
{
    switch (self.symbol())
    {
    case symbol::null:
        return self.end();

    case symbol::boolean:
    case symbol::integer:
    case symbol::number:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return (self == other) ? self.begin() : self.end();

    case symbol::array:
    case symbol::map:
        for (auto it = self.begin(); it != self.end(); ++it)
        {
            if (*it == other)
                return it;
        }
        return self.end();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

} // namespace value

} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_ALGORITHM_KEY_HPP
