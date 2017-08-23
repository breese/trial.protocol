#ifndef TRIAL_PROTOCOL_DYNAMIC_ALGORITHM_KEY_HPP
#define TRIAL_PROTOCOL_DYNAMIC_ALGORITHM_KEY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/dynamic/variable.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{
namespace key
{

template <typename CharT, typename T>
auto count(const basic_variable<CharT>& self,
           const T& other) -> typename basic_variable<CharT>::size_type
{
    switch (self.symbol())
    {
    case token::symbol::null:
        return 0;

    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return (self == other) ? 1 : 0;

    case token::symbol::array:
    case token::symbol::map:
        {
            typename basic_variable<CharT>::size_type result = 0;
            for (auto it = self.key_begin(); it != self.key_end(); ++it)
            {
                if (*it == other)
                    ++result;
            }
            return result;
        }
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
auto count(const basic_variable<CharT>& self,
           const basic_variable<CharT>& other) -> typename basic_variable<CharT>::size_type
{
    switch (other.code())
    {
    case token::code::null:
        return count(self, other.template unsafe_get<nullable>());
    case token::code::boolean:
        return count(self, other.template unsafe_get<bool>());
    case token::code::signed_short_integer:
        return count(self, other.template unsafe_get<signed short int>());
    case token::code::unsigned_short_integer:
        return count(self, other.template unsafe_get<unsigned short int>());
    case token::code::signed_integer:
        return count(self, other.template unsafe_get<signed int>());
    case token::code::unsigned_integer:
        return count(self, other.template unsafe_get<unsigned int>());
    case token::code::signed_long_integer:
        return count(self, other.template unsafe_get<signed long int>());
    case token::code::unsigned_long_integer:
        return count(self, other.template unsafe_get<unsigned long int>());
    case token::code::signed_long_long_integer:
        return count(self, other.template unsafe_get<signed long long int>());
    case token::code::unsigned_long_long_integer:
        return count(self, other.template unsafe_get<unsigned long long int>());
    case token::code::float_number:
        return count(self, other.template unsafe_get<float>());
    case token::code::double_number:
        return count(self, other.template unsafe_get<double>());
    case token::code::long_double_number:
        return count(self, other.template unsafe_get<long double>());
    case token::code::string:
        return count(self, other.template unsafe_get<typename basic_variable<CharT>::string_type>());
    case token::code::array:
        return count(self, other.template unsafe_get<typename basic_variable<CharT>::array_type>());
    case token::code::map:
        return count(self, other.template unsafe_get<typename basic_variable<CharT>::map_type>());
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT, typename T>
auto find(const basic_variable<CharT>& self,
          const T& other) -> typename basic_variable<CharT>::key_iterator
{
    switch (self.symbol())
    {
    case token::symbol::null:
        return self.key_end();

    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return (self == other) ? self.key_begin() : self.key_end();

    case token::symbol::array:
    case token::symbol::map:
        for (auto it = self.key_begin(); it != self.key_end(); ++it)
        {
            if (*it == other)
                return it;
        }
        return self.key_end();
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
auto find(const basic_variable<CharT>& self,
          const basic_variable<CharT>& other) -> typename basic_variable<CharT>::key_iterator
{
    switch (other.code())
    {
    case token::code::null:
        return find(self, other.template unsafe_get<nullable>());
    case token::code::boolean:
        return find(self, other.template unsafe_get<bool>());
    case token::code::signed_short_integer:
        return find(self, other.template unsafe_get<signed short int>());
    case token::code::unsigned_short_integer:
        return find(self, other.template unsafe_get<unsigned short int>());
    case token::code::signed_integer:
        return find(self, other.template unsafe_get<signed int>());
    case token::code::unsigned_integer:
        return find(self, other.template unsafe_get<unsigned int>());
    case token::code::signed_long_integer:
        return find(self, other.template unsafe_get<signed long int>());
    case token::code::unsigned_long_integer:
        return find(self, other.template unsafe_get<unsigned long int>());
    case token::code::signed_long_long_integer:
        return find(self, other.template unsafe_get<signed long long int>());
    case token::code::unsigned_long_long_integer:
        return find(self, other.template unsafe_get<unsigned long long int>());
    case token::code::float_number:
        return find(self, other.template unsafe_get<float>());
    case token::code::double_number:
        return find(self, other.template unsafe_get<double>());
    case token::code::long_double_number:
        return find(self, other.template unsafe_get<long double>());
    case token::code::string:
        return find(self, other.template unsafe_get<typename basic_variable<CharT>::string_type>());
    case token::code::array:
        return find(self, other.template unsafe_get<typename basic_variable<CharT>::array_type>());
    case token::code::map:
        return find(self, other.template unsafe_get<typename basic_variable<CharT>::map_type>());
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

} // namespace key
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_ALGORITHM_KEY_HPP
