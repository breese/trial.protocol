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
    case symbol::number:
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
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <template <typename> class Allocator>
auto count(const basic_variable<Allocator>& self,
           const basic_variable<Allocator>& other) -> typename basic_variable<Allocator>::size_type
{
    using variable_type = basic_variable<Allocator>;

    switch (other.code())
    {
    case code::null:
        return count(self, other.template unsafe_get<nullable>());
    case code::boolean:
        return count(self, other.template unsafe_get<bool>());
    case code::signed_char:
        return count(self, other.template unsafe_get<signed char>());
    case code::unsigned_char:
        return count(self, other.template unsafe_get<unsigned char>());
    case code::signed_short_integer:
        return count(self, other.template unsafe_get<signed short int>());
    case code::unsigned_short_integer:
        return count(self, other.template unsafe_get<unsigned short int>());
    case code::signed_integer:
        return count(self, other.template unsafe_get<signed int>());
    case code::unsigned_integer:
        return count(self, other.template unsafe_get<unsigned int>());
    case code::signed_long_integer:
        return count(self, other.template unsafe_get<signed long int>());
    case code::unsigned_long_integer:
        return count(self, other.template unsafe_get<unsigned long int>());
    case code::signed_long_long_integer:
        return count(self, other.template unsafe_get<signed long long int>());
    case code::unsigned_long_long_integer:
        return count(self, other.template unsafe_get<unsigned long long int>());
    case code::float_number:
        return count(self, other.template unsafe_get<float>());
    case code::double_number:
        return count(self, other.template unsafe_get<double>());
    case code::long_double_number:
        return count(self, other.template unsafe_get<long double>());
    case code::string:
        return count(self, other.template unsafe_get<typename variable_type::string_type>());
    case code::wstring:
        return count(self, other.template unsafe_get<typename variable_type::wstring_type>());
    case code::u16string:
        return count(self, other.template unsafe_get<typename variable_type::u16string_type>());
    case code::u32string:
        return count(self, other.template unsafe_get<typename variable_type::u32string_type>());
    case code::array:
        return count(self, other.template unsafe_get<typename variable_type::array_type>());
    case code::map:
        return count(self, other.template unsafe_get<typename variable_type::map_type>());
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

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
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <template <typename> class Allocator>
auto find(const basic_variable<Allocator>& self,
          const basic_variable<Allocator>& other) -> typename basic_variable<Allocator>::key_iterator
{
    using variable_type = basic_variable<Allocator>;

    switch (other.code())
    {
    case code::null:
        return find(self, other.template unsafe_get<nullable>());
    case code::boolean:
        return find(self, other.template unsafe_get<bool>());
    case code::signed_char:
        return find(self, other.template unsafe_get<signed char>());
    case code::unsigned_char:
        return find(self, other.template unsafe_get<unsigned char>());
    case code::signed_short_integer:
        return find(self, other.template unsafe_get<signed short int>());
    case code::unsigned_short_integer:
        return find(self, other.template unsafe_get<unsigned short int>());
    case code::signed_integer:
        return find(self, other.template unsafe_get<signed int>());
    case code::unsigned_integer:
        return find(self, other.template unsafe_get<unsigned int>());
    case code::signed_long_integer:
        return find(self, other.template unsafe_get<signed long int>());
    case code::unsigned_long_integer:
        return find(self, other.template unsafe_get<unsigned long int>());
    case code::signed_long_long_integer:
        return find(self, other.template unsafe_get<signed long long int>());
    case code::unsigned_long_long_integer:
        return find(self, other.template unsafe_get<unsigned long long int>());
    case code::float_number:
        return find(self, other.template unsafe_get<float>());
    case code::double_number:
        return find(self, other.template unsafe_get<double>());
    case code::long_double_number:
        return find(self, other.template unsafe_get<long double>());
    case code::string:
        return find(self, other.template unsafe_get<typename variable_type::string_type>());
    case code::wstring:
        return find(self, other.template unsafe_get<typename variable_type::wstring_type>());
    case code::u16string:
        return find(self, other.template unsafe_get<typename variable_type::u16string_type>());
    case code::u32string:
        return find(self, other.template unsafe_get<typename variable_type::u32string_type>());
    case code::array:
        return find(self, other.template unsafe_get<typename variable_type::array_type>());
    case code::map:
        return find(self, other.template unsafe_get<typename variable_type::map_type>());
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

} // namespace key
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_ALGORITHM_KEY_HPP
