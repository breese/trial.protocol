#ifndef TRIAL_DYNAMIC_DETAIL_VARIABLE_IPP
#define TRIAL_DYNAMIC_DETAIL_VARIABLE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/dynamic/detail/type_traits.hpp>
#include <trial/dynamic/error.hpp>

namespace trial
{
namespace dynamic
{

//-----------------------------------------------------------------------------
// type traits
//-----------------------------------------------------------------------------

namespace detail
{

template <typename T>
using is_null = std::is_same<T, nullable>;

template <typename T>
using is_boolean = detail::is_bool<T>;

template <typename CharT> struct is_character : std::false_type {};
template <> struct is_character<char> : std::true_type {};
template <> struct is_character<wchar_t> : std::true_type {};
template <> struct is_character<char16_t> : std::true_type {};
template <> struct is_character<char32_t> : std::true_type {};

template <typename T>
using is_integer = typename std::conditional<std::is_integral<T>::value && !detail::is_boolean<T>::value && !detail::is_character<T>::value,
                                             std::true_type,
                                             std::false_type>::type;

template <typename T>
using is_real = std::is_floating_point<T>;

template <typename>
struct is_literal_string : std::false_type {};

template <typename CharT>
struct is_literal_string<const CharT *>
    : is_character<CharT>
{
};

template <typename>
struct is_string : std::false_type {};

template <typename CharT>
struct is_string<std::basic_string<CharT>>
    : is_character<CharT>
{
};

template <typename Allocator, typename T>
using is_array = std::is_same<T, typename basic_variable<Allocator>::array_type>;

template <typename Allocator, typename T>
using is_map = std::is_same<T, typename basic_variable<Allocator>::map_type>;

} // namespace detail

//-----------------------------------------------------------------------------
// variable::traits
//-----------------------------------------------------------------------------

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::traits
{
    static const std::size_t value = decltype(basic_variable<Allocator>::storage)::template to_index<T>::value;
};

//-----------------------------------------------------------------------------
// variable::tag_traits
//-----------------------------------------------------------------------------

template <typename Allocator>
template <typename T, typename>
struct basic_variable<Allocator>::tag_traits
{
    using type = T;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, nullable>::value>::type>
{
    using type = nullable;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::boolean>::value>::type>
{
    using type = bool;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::integer>::value>::type>
{
    using type = int;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::real>::value>::type>
{
    using type = double;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::string>::value>::type>
{
    using type = typename basic_variable<Allocator>::string_type;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::wstring>::value>::type>
{
    using type = typename basic_variable<Allocator>::wstring_type;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::u16string>::value>::type>
{
    using type = typename basic_variable<Allocator>::u16string_type;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::u32string>::value>::type>
{
    using type = typename basic_variable<Allocator>::u32string_type;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::array>::value>::type>
{
    using type = typename basic_variable<Allocator>::array_type;
};

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::map>::value>::type>
{
    using type = typename basic_variable<Allocator>::map_type;
};

//-----------------------------------------------------------------------------
// detail::overloader
//-----------------------------------------------------------------------------

namespace detail
{

template <typename T, typename U, typename = void>
struct overloader
{
    static_assert_t<T, U> unsupported_type;
};

// Null

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<detail::is_null<U>::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using type = nullable;
    using category_type = type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::null:
            return null;

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return null;
        }
    }

    static bool equal(const variable_type& self, const U&) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::null:
            return true;

        default:
            return false;
        }
    }

    static bool less(const variable_type&, const U&) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        // Null is smaller than anything
        return false;
    }

    static void append(variable_type&, const U&)
    {
        // Appending null is a no-op
    }
};

// Boolean

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<detail::is_boolean<U>::value>::type>
{
    using type = bool;
    using category_type = type;
    using variable_type = basic_variable<Allocator>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::boolean:
            return type(self.template assume_value<bool>());

        case code::signed_char:
            return type(self.template assume_value<signed char>());

        case code::unsigned_char:
            return type(self.template assume_value<unsigned char>());

        case code::signed_short_integer:
            return type(self.template assume_value<signed short int>());

        case code::unsigned_short_integer:
            return type(self.template assume_value<unsigned short int>());

        case code::signed_integer:
            return type(self.template assume_value<signed int>());

        case code::unsigned_integer:
            return type(self.template assume_value<unsigned int>());

        case code::signed_long_integer:
            return type(self.template assume_value<signed long int>());

        case code::unsigned_long_integer:
            return type(self.template assume_value<unsigned long int>());

        case code::signed_long_long_integer:
            return type(self.template assume_value<signed long long int>());

        case code::unsigned_long_long_integer:
            return type(self.template assume_value<unsigned long long int>());

        case code::real:
            return type(self.template assume_value<float>());

        case code::long_real:
            return type(self.template assume_value<double>());

        case code::long_long_real:
            return type(self.template assume_value<long double>());

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::boolean:
            return self.template assume_value<bool>() == other;

        case code::signed_char:
            return self.template assume_value<signed char>() == other;

        case code::unsigned_char:
            return self.template assume_value<unsigned char>() == other;

        case code::signed_short_integer:
            return self.template assume_value<signed short int>() == other;

        case code::unsigned_short_integer:
            return self.template assume_value<unsigned short int>() == other;

        case code::signed_integer:
            return self.template assume_value<signed int>() == other;

        case code::unsigned_integer:
            return self.template assume_value<unsigned int>() == other;

        case code::signed_long_integer:
            return self.template assume_value<signed long int>() == other;

        case code::unsigned_long_integer:
            return self.template assume_value<unsigned long int>() == other;

        case code::signed_long_long_integer:
            return self.template assume_value<signed long long int>() == other;

        case code::unsigned_long_long_integer:
            return self.template assume_value<unsigned long long int>() == other;

        case code::real:
            return self.template assume_value<float>() == other;

        case code::long_real:
            return self.template assume_value<double>() == other;

        case code::long_long_real:
            return self.template assume_value<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::null:
            return true;

        case code::boolean:
            return self.template assume_value<bool>() < other;

        case code::signed_char:
            return self.template assume_value<signed char>() < other;

        case code::unsigned_char:
            return self.template assume_value<unsigned char>() < other;

        case code::signed_short_integer:
            return self.template assume_value<signed short int>() < other;

        case code::unsigned_short_integer:
            return self.template assume_value<unsigned short int>() < other;

        case code::signed_integer:
            return self.template assume_value<signed int>() < other;

        case code::unsigned_integer:
            return self.template assume_value<unsigned int>() < other;

        case code::signed_long_integer:
            return self.template assume_value<signed long int>() < other;

        case code::unsigned_long_integer:
            return self.template assume_value<unsigned long int>() < other;

        case code::signed_long_long_integer:
            return self.template assume_value<signed long long int>() < other;

        case code::unsigned_long_long_integer:
            return self.template assume_value<unsigned long long int>() < other;

        case code::real:
            return self.template assume_value<float>() < other;

        case code::long_real:
            return self.template assume_value<double>() < other;

        case code::long_long_real:
            return self.template assume_value<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::boolean:
            self.template assume_value<bool>() += other;
            break;

        case code::signed_char:
            self.template assume_value<signed char>() += other;
            break;

        case code::unsigned_char:
            self.template assume_value<unsigned char>() += other;
            break;

        case code::signed_short_integer:
            self.template assume_value<signed short int>() += other;
            break;

        case code::unsigned_short_integer:
            self.template assume_value<unsigned short int>() += other;
            break;

        case code::signed_integer:
            self.template assume_value<signed int>() += other;
            break;

        case code::unsigned_integer:
            self.template assume_value<unsigned int>() += other;
            break;

        case code::signed_long_integer:
            self.template assume_value<signed long int>() += other;
            break;

        case code::unsigned_long_integer:
            self.template assume_value<unsigned long int>() += other;
            break;

        case code::signed_long_long_integer:
            self.template assume_value<signed long long int>() += other;
            break;

        case code::unsigned_long_long_integer:
            self.template assume_value<unsigned long long int>() += other;
            break;

        case code::real:
            self.template assume_value<float>() += other;
            break;

        case code::long_real:
            self.template assume_value<double>() += other;
            break;

        case code::long_long_real:
            self.template assume_value<long double>() += other;
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Signed integer

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<detail::is_integer<U>::value &&
                            std::is_signed<U>::value>::type>
{
    using type = U;
    using category_type = int;
    using variable_type = basic_variable<Allocator>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::boolean:
            return type(self.template assume_value<bool>());

        case code::signed_char:
            return type(self.template assume_value<signed char>());

        case code::unsigned_char:
            return type(self.template assume_value<unsigned char>());

        case code::signed_short_integer:
            return type(self.template assume_value<signed short int>());

        case code::unsigned_short_integer:
            return type(self.template assume_value<unsigned short int>());

        case code::signed_integer:
            return type(self.template assume_value<signed int>());

        case code::unsigned_integer:
            return type(self.template assume_value<unsigned int>());

        case code::signed_long_integer:
            return type(self.template assume_value<signed long int>());

        case code::unsigned_long_integer:
            return type(self.template assume_value<unsigned long int>());

        case code::signed_long_long_integer:
            return type(self.template assume_value<signed long long int>());

        case code::unsigned_long_long_integer:
            return type(self.template assume_value<unsigned long long int>());

        case code::real:
            return type(self.template assume_value<float>());

        case code::long_real:
            return type(self.template assume_value<double>());

        case code::long_long_real:
            return type(self.template assume_value<long double>());

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::boolean:
            return self.template assume_value<bool>() == other;

        case code::signed_char:
            return self.template assume_value<signed char>() == other;
        case code::unsigned_char:
            return static_cast<signed char>(self.template assume_value<unsigned char>()) == other;

        case code::signed_short_integer:
            return self.template assume_value<signed short int>() == other;
        case code::unsigned_short_integer:
            return static_cast<signed short int>(self.template assume_value<unsigned short int>()) == other;

        case code::signed_integer:
            return self.template assume_value<signed int>() == other;
        case code::unsigned_integer:
            return static_cast<signed int>(self.template assume_value<unsigned int>()) == other;

        case code::signed_long_integer:
            return self.template assume_value<signed long int>() == other;
        case code::unsigned_long_integer:
            return static_cast<signed long int>(self.template assume_value<unsigned long int>()) == other;

        case code::signed_long_long_integer:
            return self.template assume_value<signed long long int>() == other;
        case code::unsigned_long_long_integer:
            return static_cast<signed long long int>(self.template assume_value<unsigned long long int>()) == other;

        case code::real:
            return self.template assume_value<float>() == other;

        case code::long_real:
            return self.template assume_value<double>() == other;

        case code::long_long_real:
            return self.template assume_value<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::null:
            return true;

        case code::boolean:
            return self.template assume_value<bool>() < other;

        case code::signed_char:
            return self.template assume_value<signed char>() < other;
        case code::unsigned_char:
            return static_cast<signed char>(self.template assume_value<unsigned char>()) < other;

        case code::signed_short_integer:
            return self.template assume_value<signed short int>() < other;
        case code::unsigned_short_integer:
            return static_cast<signed short int>(self.template assume_value<unsigned short int>()) < other;

        case code::signed_integer:
            return self.template assume_value<signed int>() < other;
        case code::unsigned_integer:
            return static_cast<signed int>(self.template assume_value<unsigned int>()) < other;

        case code::signed_long_integer:
            return self.template assume_value<signed long int>() < other;
        case code::unsigned_long_integer:
            return static_cast<signed long int>(self.template assume_value<unsigned long int>()) < other;

        case code::signed_long_long_integer:
            return self.template assume_value<signed long long int>() < other;
        case code::unsigned_long_long_integer:
            return static_cast<signed long long int>(self.template assume_value<unsigned long long int>()) < other;

        case code::real:
            return self.template assume_value<float>() < other;

        case code::long_real:
            return self.template assume_value<double>() < other;

        case code::long_long_real:
            return self.template assume_value<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::boolean:
            self.template assume_value<bool>() += other;
            break;

        case code::signed_char:
            self.template assume_value<signed char>() += other;
            break;

        case code::unsigned_char:
            self.template assume_value<unsigned char>() += other;
            break;

        case code::signed_short_integer:
            self.template assume_value<signed short int>() += other;
            break;

        case code::unsigned_short_integer:
            self.template assume_value<unsigned short int>() += other;
            break;

        case code::signed_integer:
            self.template assume_value<signed int>() += other;
            break;

        case code::unsigned_integer:
            self.template assume_value<unsigned int>() += other;
            break;

        case code::signed_long_integer:
            self.template assume_value<signed long int>() += other;
            break;

        case code::unsigned_long_integer:
            self.template assume_value<unsigned long int>() += other;
            break;

        case code::signed_long_long_integer:
            self.template assume_value<signed long long int>() += other;
            break;

        case code::unsigned_long_long_integer:
            self.template assume_value<unsigned long long int>() += other;
            break;

        case code::real:
            self.template assume_value<float>() += other;
            break;

        case code::long_real:
            self.template assume_value<double>() += other;
            break;

        case code::long_long_real:
            self.template assume_value<long double>() += other;
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Unsigned integer

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<detail::is_integer<U>::value &&
                            std::is_unsigned<U>::value>::type>
{
    using type = U;
    using category_type = int;
    using variable_type = basic_variable<Allocator>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::boolean:
            return type(self.template assume_value<bool>());

        case code::signed_char:
            return type(self.template assume_value<signed char>());

        case code::unsigned_char:
            return type(self.template assume_value<unsigned char>());

        case code::signed_short_integer:
            return type(self.template assume_value<signed short int>());

        case code::unsigned_short_integer:
            return type(self.template assume_value<unsigned short int>());

        case code::signed_integer:
            return type(self.template assume_value<signed int>());

        case code::unsigned_integer:
            return type(self.template assume_value<unsigned int>());

        case code::signed_long_integer:
            return type(self.template assume_value<signed long int>());

        case code::unsigned_long_integer:
            return type(self.template assume_value<unsigned long int>());

        case code::signed_long_long_integer:
            return type(self.template assume_value<signed long long int>());

        case code::unsigned_long_long_integer:
            return type(self.template assume_value<unsigned long long int>());

        case code::real:
            return type(self.template assume_value<float>());

        case code::long_real:
            return type(self.template assume_value<double>());

        case code::long_long_real:
            return type(self.template assume_value<long double>());

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::boolean:
            return self.template assume_value<bool>() == other;

        case code::signed_char:
            return static_cast<unsigned char>(self.template assume_value<signed char>()) == other;
        case code::unsigned_char:
            return self.template assume_value<unsigned char>() == other;

        case code::signed_short_integer:
            return static_cast<unsigned short int>(self.template assume_value<signed short int>()) == other;
        case code::unsigned_short_integer:
            return self.template assume_value<unsigned short int>() == other;

        case code::signed_integer:
            return static_cast<unsigned int>(self.template assume_value<signed int>()) == other;
        case code::unsigned_integer:
            return self.template assume_value<unsigned int>() == other;

        case code::signed_long_integer:
            return static_cast<unsigned long int>(self.template assume_value<signed long int>()) == other;
        case code::unsigned_long_integer:
            return self.template assume_value<unsigned long int>() == other;

        case code::signed_long_long_integer:
            return static_cast<unsigned long long int>(self.template assume_value<signed long long int>()) == other;
        case code::unsigned_long_long_integer:
            return self.template assume_value<unsigned long long int>() == other;

        case code::real:
            return self.template assume_value<float>() == other;

        case code::long_real:
            return self.template assume_value<double>() == other;

        case code::long_long_real:
            return self.template assume_value<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::null:
            return true;

        case code::boolean:
            return self.template assume_value<bool>() < other;

        case code::signed_char:
            return static_cast<unsigned char>(self.template assume_value<signed char>()) < other;
        case code::unsigned_char:
            return self.template assume_value<unsigned char>() < other;

        case code::signed_short_integer:
            return static_cast<unsigned short int>(self.template assume_value<signed short int>()) < other;
        case code::unsigned_short_integer:
            return self.template assume_value<unsigned short int>() < other;

        case code::signed_integer:
            return static_cast<unsigned int>(self.template assume_value<signed int>()) < other;
        case code::unsigned_integer:
            return self.template assume_value<unsigned int>() < other;

        case code::signed_long_integer:
            return static_cast<unsigned long int>(self.template assume_value<signed long int>()) < other;
        case code::unsigned_long_integer:
            return self.template assume_value<unsigned long int>() < other;

        case code::signed_long_long_integer:
            return static_cast<unsigned long long int>(self.template assume_value<signed long long int>()) < other;
        case code::unsigned_long_long_integer:
            return self.template assume_value<unsigned long long int>() < other;

        case code::real:
            return self.template assume_value<float>() < other;

        case code::long_real:
            return self.template assume_value<double>() < other;

        case code::long_long_real:
            return self.template assume_value<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::boolean:
            self.template assume_value<bool>() += other;
            break;

        case code::signed_char:
            self.template assume_value<signed char>() += other;
            break;

        case code::unsigned_char:
            self.template assume_value<unsigned char>() += other;
            break;

        case code::signed_short_integer:
            self.template assume_value<signed short int>() += other;
            break;

        case code::unsigned_short_integer:
            self.template assume_value<unsigned short int>() += other;
            break;

        case code::signed_integer:
            self.template assume_value<signed int>() += other;
            break;

        case code::unsigned_integer:
            self.template assume_value<unsigned int>() += other;
            break;

        case code::signed_long_integer:
            self.template assume_value<signed long int>() += other;
            break;

        case code::unsigned_long_integer:
            self.template assume_value<unsigned long int>() += other;
            break;

        case code::signed_long_long_integer:
            self.template assume_value<signed long long int>() += other;
            break;

        case code::unsigned_long_long_integer:
            self.template assume_value<unsigned long long int>() += other;
            break;

        case code::real:
            self.template assume_value<float>() += other;
            break;

        case code::long_real:
            self.template assume_value<double>() += other;
            break;

        case code::long_long_real:
            self.template assume_value<long double>() += other;
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Floating-point

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<detail::is_real<U>::value>::type>
{
    using type = U;
    using category_type = float;
    using variable_type = basic_variable<Allocator>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::boolean:
            return type(self.template assume_value<bool>());

        case code::signed_char:
            return type(self.template assume_value<signed char>());

        case code::unsigned_char:
            return type(self.template assume_value<unsigned char>());

        case code::signed_short_integer:
            return type(self.template assume_value<signed short int>());

        case code::unsigned_short_integer:
            return type(self.template assume_value<unsigned short int>());

        case code::signed_integer:
            return type(self.template assume_value<signed int>());

        case code::unsigned_integer:
            return type(self.template assume_value<unsigned int>());

        case code::signed_long_integer:
            return type(self.template assume_value<signed long int>());

        case code::unsigned_long_integer:
            return type(self.template assume_value<unsigned long int>());

        case code::signed_long_long_integer:
            return type(self.template assume_value<signed long long int>());

        case code::unsigned_long_long_integer:
            return type(self.template assume_value<unsigned long long int>());

        case code::real:
            return type(self.template assume_value<float>());

        case code::long_real:
            return type(self.template assume_value<double>());

        case code::long_long_real:
            return type(self.template assume_value<long double>());

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::boolean:
            return self.template assume_value<bool>() == other;

        case code::signed_char:
            return self.template assume_value<signed char>() == other;

        case code::unsigned_char:
            return self.template assume_value<unsigned char>() == other;

        case code::signed_short_integer:
            return self.template assume_value<signed short int>() == other;

        case code::unsigned_short_integer:
            return self.template assume_value<unsigned short int>() == other;

        case code::signed_integer:
            return self.template assume_value<signed int>() == other;

        case code::unsigned_integer:
            return self.template assume_value<unsigned int>() == other;

        case code::signed_long_integer:
            return self.template assume_value<signed long int>() == other;

        case code::unsigned_long_integer:
            return self.template assume_value<unsigned long int>() == other;

        case code::signed_long_long_integer:
            return self.template assume_value<signed long long int>() == other;

        case code::unsigned_long_long_integer:
            return self.template assume_value<unsigned long long int>() == other;

        case code::real:
            return self.template assume_value<float>() == other;

        case code::long_real:
            return self.template assume_value<double>() == other;

        case code::long_long_real:
            return self.template assume_value<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::null:
            return true;

        case code::boolean:
            return self.template assume_value<bool>() < other;

        case code::signed_char:
            return self.template assume_value<signed char>() < other;

        case code::unsigned_char:
            return self.template assume_value<unsigned char>() < other;

        case code::signed_short_integer:
            return self.template assume_value<signed short int>() < other;

        case code::unsigned_short_integer:
            return self.template assume_value<unsigned short int>() < other;

        case code::signed_integer:
            return self.template assume_value<signed int>() < other;

        case code::unsigned_integer:
            return self.template assume_value<unsigned int>() < other;

        case code::signed_long_integer:
            return self.template assume_value<signed long int>() < other;

        case code::unsigned_long_integer:
            return self.template assume_value<unsigned long int>() < other;

        case code::signed_long_long_integer:
            return self.template assume_value<signed long long int>() < other;

        case code::unsigned_long_long_integer:
            return self.template assume_value<unsigned long long int>() < other;

        case code::real:
            return self.template assume_value<float>() < other;

        case code::long_real:
            return self.template assume_value<double>() < other;

        case code::long_long_real:
            return self.template assume_value<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::boolean:
            self.template assume_value<bool>() += other;
            break;

        case code::signed_char:
            self.template assume_value<signed char>() += other;
            break;

        case code::unsigned_char:
            self.template assume_value<unsigned char>() += other;
            break;

        case code::signed_short_integer:
            self.template assume_value<signed short int>() += other;
            break;

        case code::unsigned_short_integer:
            self.template assume_value<unsigned short int>() += other;
            break;

        case code::signed_integer:
            self.template assume_value<signed int>() += other;
            break;

        case code::unsigned_integer:
            self.template assume_value<unsigned int>() += other;
            break;

        case code::signed_long_integer:
            self.template assume_value<signed long int>() += other;
            break;

        case code::unsigned_long_integer:
            self.template assume_value<unsigned long int>() += other;
            break;

        case code::signed_long_long_integer:
            self.template assume_value<signed long long int>() += other;
            break;

        case code::unsigned_long_long_integer:
            self.template assume_value<unsigned long long int>() += other;
            break;

        case code::real:
            self.template assume_value<float>() += other;
            break;

        case code::long_real:
            self.template assume_value<double>() += other;
            break;

        case code::long_long_real:
            self.template assume_value<long double>() += other;
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// String

template <typename T, typename U, typename = void>
struct string_overloader
{
    static bool equal(const T&, const U&)
    {
        throw dynamic::error(incompatible_type);
    }

    static bool less(const T&, const U&)
    {
        throw dynamic::error(incompatible_type);
    }

    static void append(T&, const U&)
    {
        throw dynamic::error(incompatible_type);
    }
};

template <typename CharT, typename Traits, typename Allocator, typename U>
struct string_overloader<
    std::basic_string<CharT, Traits, Allocator>,
    U,
    typename std::enable_if<std::is_same<U, std::basic_string<CharT, Traits, Allocator>>::value>::type>
{
    using string_type = std::basic_string<CharT, Traits, Allocator>;

    static bool equal(const string_type& lhs, const U& rhs)
    {
        return lhs == rhs;
    }

    static bool less(const string_type& lhs, const U& rhs)
    {
        return lhs < rhs;
    }

    static void append(string_type& lhs, const U& rhs)
    {
        lhs += rhs;
    }
};

// string_type

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<std::is_same<U, typename basic_variable<Allocator>::string_type>::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using type = typename variable_type::string_type;
    using category_type = type;

    using string_type = typename variable_type::string_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::string:
            return self.template assume_value<string_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::string:
            return string_overloader<string_type, U>::equal(self.template assume_value<string_type>(), other);

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::string:
            return string_overloader<string_type, U>::less(self.template assume_value<string_type>(), other);

        case code::wstring:
        case code::u16string:
        case code::u32string:
        case code::array:
        case code::map:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::string:
            string_overloader<string_type, U>::append(self.template assume_value<string_type>(), other);
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// wstring_type

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<std::is_same<U, typename basic_variable<Allocator>::wstring_type>::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using type = typename variable_type::wstring_type;
    using category_type = type;

    using wstring_type = typename variable_type::wstring_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::wstring:
            return self.template assume_value<wstring_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::wstring:
            return string_overloader<wstring_type, U>::equal(self.template assume_value<wstring_type>(), other);

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::wstring:
            return string_overloader<wstring_type, U>::less(self.template assume_value<wstring_type>(), other);

        case code::u16string:
        case code::u32string:
        case code::array:
        case code::map:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::wstring:
            string_overloader<wstring_type, U>::append(self.template assume_value<wstring_type>(), other);
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// u16string_type

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<std::is_same<U, typename basic_variable<Allocator>::u16string_type>::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using type = typename variable_type::u16string_type;
    using category_type = type;

    using u16string_type = typename variable_type::u16string_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::u16string:
            return self.template assume_value<u16string_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::u16string:
            return string_overloader<u16string_type, U>::equal(self.template assume_value<u16string_type>(), other);

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::u16string:
            return string_overloader<u16string_type, U>::less(self.template assume_value<u16string_type>(), other);

        case code::u32string:
        case code::array:
        case code::map:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::u16string:
            string_overloader<u16string_type, U>::append(self.template assume_value<u16string_type>(), other);
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// u32string_type

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<std::is_same<U, typename basic_variable<Allocator>::u32string_type>::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using type = typename variable_type::u32string_type;
    using category_type = type;

    using u32string_type = typename variable_type::u32string_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::u32string:
            return self.template assume_value<u32string_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::u32string:
            return string_overloader<u32string_type, U>::equal(self.template assume_value<u32string_type>(), other);

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::u32string:
            return string_overloader<u32string_type, U>::less(self.template assume_value<u32string_type>(), other);

        case code::array:
        case code::map:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::u32string:
            string_overloader<u32string_type, U>::append(self.template assume_value<u32string_type>(), other);
            break;

        case code::array:
            self.template assume_value<array_type>().emplace_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Array

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<detail::is_array<Allocator, U>::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using type = typename variable_type::array_type;
    using category_type = type;

    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::array:
            return self.template assume_value<array_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::array:
            {
                const auto& array = self.template assume_value<array_type>();
                if (array.size() == other.size())
                {
                    return std::equal(array.begin(), array.end(), other.begin());
                }
                return false;
            }
        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::array:
            {
                const auto& array = self.template assume_value<array_type>();
                auto less_than = std::less<decltype(*array.begin())>();
                auto array_it = array.begin();
                auto other_it = other.begin();
                while ((array_it != array.end()) && (other_it != other.end()))
                {
                    if (!less_than(*array_it, *other_it))
                        return false;
                    ++array_it;
                    ++other_it;
                }
                return (array_it == array.end());
            }

        case code::map:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::array:
            {
                auto& array = self.template assume_value<array_type>();
                array.insert(array.end(), other.begin(), other.end());
            }
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Map

template <typename Allocator, typename U>
struct overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<detail::is_map<Allocator, U>::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using type = typename variable_type::map_type;
    using category_type = type;

    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case code::map:
            return self.template assume_value<map_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::map:
            {
                const auto& map = self.template assume_value<map_type>();
                if (map.size() == other.size())
                {
                    return std::equal(map.begin(), map.end(), other.begin());
                }
                return false;
            }
        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (self.code())
        {
        case code::map:
            {
                const auto& map = self.template assume_value<map_type>();
                auto less_than = std::less<decltype(*map.begin())>();
                auto map_it = map.begin();
                auto other_it = other.begin();
                while ((map_it != map.end()) && (other_it != other.end()))
                {
                    if (!less_than(*map_it, *other_it))
                        return false;
                    ++map_it;
                    ++other_it;
                }
                return (map_it == map.end());
            }

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case code::null:
            self.storage = other; // Overwrite null
            break;

        case code::map:
            {
                auto& map = self.template assume_value<map_type>();
                map.insert(other.begin(), other.end());
            }
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// detail::operator_overloader
//-----------------------------------------------------------------------------

namespace detail
{

template <typename T, typename U, typename = void>
struct operator_overloader
{
    static_assert_t<T, U> unsupported_type;
};

template <typename Allocator, typename U>
struct operator_overloader<
    basic_variable<Allocator>,
    U,
    typename std::enable_if<!std::is_same<U, basic_variable<Allocator> >::value>::type>
{
    using variable_type = basic_variable<Allocator>;
    using string_type = typename variable_type::string_type;
    using wstring_type = typename variable_type::wstring_type;
    using u16string_type = typename variable_type::u16string_type;
    using u32string_type = typename variable_type::u32string_type;

    template <typename T = U>
    static typename std::enable_if<!is_literal_string<typename std::decay<T>::type>::value, bool>::type
    equal(const variable_type& lhs, const U& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, U>::equal(lhs, rhs);
    }

    static bool equal(const variable_type& lhs, const char* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, string_type>::equal(lhs, string_type(rhs));
    }

    static bool equal(const variable_type& lhs, const wchar_t* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, wstring_type>::equal(lhs, wstring_type(rhs));
    }

    static bool equal(const variable_type& lhs, const char16_t* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, u16string_type>::equal(lhs, u16string_type(rhs));
    }

    static bool equal(const variable_type& lhs, const char32_t* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, u32string_type>::equal(lhs, u32string_type(rhs));
    }

    template <typename T = U>
    static typename std::enable_if<!is_literal_string<typename std::decay<T>::type>::value, bool>::type
    less(const variable_type& lhs, const T& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, T>::less(lhs, rhs);
    }

    static bool less(const variable_type& lhs, const char* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, string_type>::less(lhs, string_type(rhs));
    }

    static bool less(const variable_type& lhs, const wchar_t* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, wstring_type>::less(lhs, wstring_type(rhs));
    }

    static bool less(const variable_type& lhs, const char16_t* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, u16string_type>::less(lhs, u16string_type(rhs));
    }

    static bool less(const variable_type& lhs, const char32_t* rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, u32string_type>::less(lhs, u32string_type(rhs));
    }
};

template <typename T, typename Allocator>
struct operator_overloader<
    T,
    basic_variable<Allocator>,
    typename std::enable_if<!std::is_same<T, basic_variable<Allocator> >::value>::type>
{
    using variable_type = basic_variable<Allocator>;

    static bool equal(const T& lhs, const variable_type& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return operator_overloader<variable_type, variable_type>::equal(variable_type(lhs), rhs);
    }

    static bool less(const T& lhs, const variable_type& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        return operator_overloader<variable_type, variable_type>::less(variable_type(lhs), rhs);
    }
};

template <typename Allocator>
struct operator_overloader<
    basic_variable<Allocator>,
    basic_variable<Allocator>>
{
    using variable_type = basic_variable<Allocator>;
    using string_type = typename variable_type::string_type;
    using wstring_type = typename variable_type::wstring_type;
    using u16string_type = typename variable_type::u16string_type;
    using u32string_type = typename variable_type::u32string_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static bool equal(const variable_type& lhs,
                      const variable_type& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (rhs.code())
        {
        case code::null:
            return detail::template overloader<variable_type, nullable>::
                equal(lhs, rhs.template value<nullable>());

        case code::boolean:
            return detail::template overloader<variable_type, bool>::
                equal(lhs, rhs.template assume_value<bool>());

        case code::signed_char:
            return detail::template overloader<variable_type, signed char>::
                equal(lhs, rhs.template assume_value<signed char>());

        case code::unsigned_char:
            return detail::template overloader<variable_type, unsigned char>::
                equal(lhs, rhs.template assume_value<unsigned char>());

        case code::signed_short_integer:
            return detail::template overloader<variable_type, signed short int>::
                equal(lhs, rhs.template assume_value<signed short int>());

        case code::unsigned_short_integer:
            return detail::template overloader<variable_type, unsigned short int>::
                equal(lhs, rhs.template assume_value<unsigned short int>());

        case code::signed_integer:
            return detail::template overloader<variable_type, signed int>::
                equal(lhs, rhs.template assume_value<signed int>());

        case code::unsigned_integer:
            return detail::template overloader<variable_type, unsigned int>::
                equal(lhs, rhs.template assume_value<unsigned int>());

        case code::signed_long_integer:
            return detail::template overloader<variable_type, signed long int>::
                equal(lhs, rhs.template assume_value<signed long int>());

        case code::unsigned_long_integer:
            return detail::template overloader<variable_type, unsigned long int>::
                equal(lhs, rhs.template assume_value<unsigned long int>());

        case code::signed_long_long_integer:
            return detail::template overloader<variable_type, signed long long int>::
                equal(lhs, rhs.template assume_value<signed long long int>());

        case code::unsigned_long_long_integer:
            return detail::template overloader<variable_type, unsigned long long int>::
                equal(lhs, rhs.template assume_value<unsigned long long int>());

        case code::real:
            return detail::template overloader<variable_type, float>::
                equal(lhs, rhs.template assume_value<float>());

        case code::long_real:
            return detail::template overloader<variable_type, double>::
                equal(lhs, rhs.template assume_value<double>());

        case code::long_long_real:
            return detail::template overloader<variable_type, long double>::
                equal(lhs, rhs.template assume_value<long double>());

        case code::string:
            return detail::template overloader<variable_type, string_type>::
                equal(lhs, rhs.template assume_value<string_type>());

        case code::wstring:
            return detail::template overloader<variable_type, wstring_type>::
                equal(lhs, rhs.template assume_value<wstring_type>());

        case code::u16string:
            return detail::template overloader<variable_type, u16string_type>::
                equal(lhs, rhs.template assume_value<u16string_type>());

        case code::u32string:
            return detail::template overloader<variable_type, u32string_type>::
                equal(lhs, rhs.template assume_value<u32string_type>());

        case code::array:
            return detail::template overloader<variable_type, array_type>::
                equal(lhs, rhs.template assume_value<array_type>());

        case code::map:
            return detail::template overloader<variable_type, map_type>::
                equal(lhs, rhs.template assume_value<map_type>());
        }
        return false;
    }

    static bool less(const variable_type& lhs,
                     const variable_type& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    {
        switch (rhs.code())
        {
        case code::null:
            return detail::template overloader<variable_type, nullable>::
                less(lhs, rhs.template value<nullable>());

        case code::boolean:
            return detail::template overloader<variable_type, bool>::
                less(lhs, rhs.template assume_value<bool>());

        case code::signed_char:
            return detail::template overloader<variable_type, signed char>::
                less(lhs, rhs.template assume_value<signed char>());

        case code::unsigned_char:
            return detail::template overloader<variable_type, unsigned char>::
                less(lhs, rhs.template assume_value<unsigned char>());

        case code::signed_short_integer:
            return detail::template overloader<variable_type, signed short int>::
                less(lhs, rhs.template assume_value<signed short int>());

        case code::unsigned_short_integer:
            return detail::template overloader<variable_type, unsigned short int>::
                less(lhs, rhs.template assume_value<unsigned short int>());

        case code::signed_integer:
            return detail::template overloader<variable_type, signed int>::
                less(lhs, rhs.template assume_value<signed int>());

        case code::unsigned_integer:
            return detail::template overloader<variable_type, unsigned int>::
                less(lhs, rhs.template assume_value<unsigned int>());

        case code::signed_long_integer:
            return detail::template overloader<variable_type, signed long int>::
                less(lhs, rhs.template assume_value<signed long int>());

        case code::unsigned_long_integer:
            return detail::template overloader<variable_type, unsigned long int>::
                less(lhs, rhs.template assume_value<unsigned long int>());

        case code::signed_long_long_integer:
            return detail::template overloader<variable_type, signed long long int>::
                less(lhs, rhs.template assume_value<signed long long int>());

        case code::unsigned_long_long_integer:
            return detail::template overloader<variable_type, unsigned long long int>::
                less(lhs, rhs.template assume_value<unsigned long long int>());

        case code::real:
            return detail::template overloader<variable_type, float>::
                less(lhs, rhs.template assume_value<float>());

        case code::long_real:
            return detail::template overloader<variable_type, double>::
                less(lhs, rhs.template assume_value<double>());

        case code::long_long_real:
            return detail::template overloader<variable_type, long double>::
                less(lhs, rhs.template assume_value<long double>());

        case code::string:
            return detail::template overloader<variable_type, string_type>::
                less(lhs, rhs.template assume_value<string_type>());

        case code::wstring:
            return detail::template overloader<variable_type, wstring_type>::
                less(lhs, rhs.template assume_value<wstring_type>());

        case code::u16string:
            return detail::template overloader<variable_type, u16string_type>::
                less(lhs, rhs.template assume_value<u16string_type>());

        case code::u32string:
            return detail::template overloader<variable_type, u32string_type>::
                less(lhs, rhs.template assume_value<u32string_type>());

        case code::array:
            return detail::template overloader<variable_type, array_type>::
                less(lhs, rhs.template assume_value<array_type>());

        case code::map:
            return detail::template overloader<variable_type, map_type>::
                less(lhs, rhs.template assume_value<map_type>());
        }
        return false;
    }
};

} // namespace detail
    
//-----------------------------------------------------------------------------
// detail::same_overloader
//-----------------------------------------------------------------------------

namespace detail
{

// The specialized template capture qualifications removed during template
// argument deduction to ensure that only the exact type is matched in the
// general case.
//
// For example:
//   variable data(0.0f);
//   assert(data.same<float>(), true);
//   assert(data.same<float&>(), false);
//   assert(data.same<const float>(), false);

template <typename Allocator, typename T, typename = void>
struct same_overloader
{
    static constexpr bool same(std::size_t which) noexcept
    {
        return which == basic_variable<Allocator>::template traits<T>::value;
    }
};

template <typename Allocator, typename T>
struct same_overloader<
    Allocator,
    T,
    typename std::enable_if<std::is_const<T>::value ||
                            std::is_volatile<T>::value ||
                            std::is_reference<T>::value>::type>
{
    static constexpr bool same(std::size_t) noexcept
    {
        return false;
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// detail::iterator_overloader
//-----------------------------------------------------------------------------

namespace detail
{

template <typename Allocator, typename Iterator, typename = void>
struct iterator_overloader
{
    using variable_type = basic_variable<Allocator>;

    static void insert(variable_type& self,
                       Iterator begin,
                       Iterator end)
    {
        switch (self.symbol())
        {
        case symbol::null:
            self = basic_array<Allocator>::make();
            goto case_array;
        case symbol::array:
        case_array:
        {
            // Insert at end
            auto& array = self.template assume_value<typename variable_type::array_type>();
            array.insert(array.end(), begin, end);
        }
        break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }

    static void insert(variable_type& self,
                       typename variable_type::const_iterator where,
                       Iterator begin,
                       Iterator end)
    {
        switch (self.symbol())
        {
        case symbol::array:
            self.template assume_value<typename variable_type::array_type>()
                .insert(where.current.template get<typename variable_type::const_iterator::array_iterator>(),
                        begin,
                        end);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

template <typename Allocator, typename Iterator>
struct iterator_overloader<
    Allocator,
    Iterator,
    typename std::enable_if<detail::is_iterator<Iterator>::value &&
                            detail::is_pair<typename Iterator::value_type>::value>::type>
{
    using variable_type = basic_variable<Allocator>;

    static void insert(variable_type& self,
                       Iterator begin,
                       Iterator end)
    {
        switch (self.symbol())
        {
        case symbol::map:
            self.template assume_value<typename variable_type::map_type>()
                .insert(begin, end);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }

    static void insert(variable_type& self,
                       typename variable_type::const_iterator,
                       Iterator begin,
                       Iterator end)
    {
        switch (self.symbol())
        {
        case symbol::map:
            // Ignore hint
            self.template assume_value<typename variable_type::map_type>()
                .insert(begin,
                        end);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// variable::iterator_base
//-----------------------------------------------------------------------------

template <typename Allocator>
template <typename Derived, typename T>
basic_variable<Allocator>::iterator_base<Derived, T>::iterator_base()
    : scope(nullptr),
      current(pointer(nullptr))
{
}

template <typename Allocator>
template <typename Derived, typename T>
basic_variable<Allocator>::iterator_base<Derived, T>::iterator_base(const iterator_base& other)
    : scope(other.scope),
      current(other.current)
{
}

template <typename Allocator>
template <typename Derived, typename T>
basic_variable<Allocator>::iterator_base<Derived, T>::iterator_base(iterator_base&& other)
    : scope(std::move(other.scope)),
      current(std::move(other.current))
{
}

template <typename Allocator>
template <typename Derived, typename T>
basic_variable<Allocator>::iterator_base<Derived, T>::iterator_base(pointer p,
                                                                    bool initialize)
    : scope(p),
      current(pointer(nullptr))
{
    switch (scope->symbol())
    {
    case symbol::null:
        current = pointer(nullptr);
        break;

    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        if (initialize)
            current = p;
        break;

    case symbol::array:
        if (initialize)
            current = p->template assume_value<array_type>().begin();
        else
            current = p->template assume_value<array_type>().end();
        break;

    case symbol::map:
        if (initialize)
            current = p->template assume_value<map_type>().begin();
        else
            current = p->template assume_value<map_type>().end();
        break;
    }
}

template <typename Allocator>
template <typename Derived, typename T>
basic_variable<Allocator>::iterator_base<Derived, T>::iterator_base(pointer p,
                                                                    array_iterator where)
    : scope(p),
      current(where)
{
}

template <typename Allocator>
template <typename Derived, typename T>
basic_variable<Allocator>::iterator_base<Derived, T>::iterator_base(pointer p,
                                                                    map_iterator where)
    : scope(p),
      current(where)
{
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::operator= (const Derived& other) -> Derived&
{
    scope = other.scope;
    current = other.current;
    return *static_cast<Derived*>(this);
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::operator= (Derived&& other) -> Derived&
{
    scope = std::move(other.scope);
    current = std::move(other.current);
    return *static_cast<Derived*>(this);
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::operator++ () -> Derived&
{
    assert(scope);

    switch (scope->symbol())
    {
    case symbol::null:
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        current = pointer(nullptr);
        break;

    case symbol::array:
        ++current.template get<array_iterator>();
        break;

    case symbol::map:
        ++current.template get<map_iterator>();
        break;
    }
    return *static_cast<Derived*>(this);
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::operator++ (int) -> Derived
{
    assert(scope);

    Derived result = *static_cast<Derived*>(this);
    ++(*this);
    return result;
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::operator-- () -> Derived&
{
    assert(scope);

    switch (scope->symbol())
    {
    case symbol::null:
        current = pointer(nullptr);
        break;

    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        if (current.template get<pointer>() == nullptr)
        {
            current = scope;
        }
        break;

    case symbol::array:
        --current.template get<array_iterator>();
        break;

    case symbol::map:
        --current.template get<map_iterator>();
        break;
    }
    return *static_cast<Derived*>(this);
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::operator-- (int) -> Derived
{
    assert(scope);

    Derived result = *static_cast<Derived*>(this);
    --(*this);
    return result;
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::key() const -> const_reference
{
    assert(scope);

    switch (scope->symbol())
    {
    case symbol::map:
        return const_cast<const_reference>(current.template get<map_iterator>()->first);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::value() -> reference
{
    assert(scope);

    switch (scope->symbol())
    {
    case symbol::null:
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return *current.template get<pointer>();

    case symbol::array:
        return *current.template get<array_iterator>();

    case symbol::map:
        return current.template get<map_iterator>()->second;
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::value() const -> const_reference
{
    assert(scope);

    switch (scope->symbol())
    {
    case symbol::null:
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return *current.template get<pointer>();

    case symbol::array:
        return *current.template get<array_iterator>();

    case symbol::map:
        return current.template get<map_iterator>()->second;
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
template <typename Derived, typename T>
auto basic_variable<Allocator>::iterator_base<Derived, T>::operator-> () -> pointer
{
    assert(scope);

    switch (scope->symbol())
    {
    case symbol::null:
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return current.template get<pointer>();

    case symbol::array:
        return &*current.template get<array_iterator>();

    case symbol::map:
        return &current.template get<map_iterator>()->second;
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
template <typename Derived, typename T>
bool basic_variable<Allocator>::iterator_base<Derived, T>::operator== (const Derived& other) const
{
    if (!scope)
        return !other.scope;
    if (!other.scope)
        return false;

    assert(scope->code() == other.scope->code());

    switch (scope->symbol())
    {
    case symbol::null:
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return current.template get<pointer>() == other.current.template get<pointer>();

    case symbol::array:
        return current.template get<array_iterator>() == other.current.template get<array_iterator>();

    case symbol::map:
        return current.template get<map_iterator>() == other.current.template get<map_iterator>();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
template <typename Derived, typename T>
bool basic_variable<Allocator>::iterator_base<Derived, T>::operator!= (const Derived& other) const
{
    return !(*this == other);
}

//-----------------------------------------------------------------------------
// variable::iterator
//-----------------------------------------------------------------------------

template <typename Allocator>
basic_variable<Allocator>::iterator::iterator()
    : super()
{
}

template <typename Allocator>
basic_variable<Allocator>::iterator::iterator(const iterator& other)
    : super(other)
{
}

template <typename Allocator>
basic_variable<Allocator>::iterator::iterator(iterator&& other)
    : super(std::move(other))
{
}

template <typename Allocator>
basic_variable<Allocator>::iterator::iterator(pointer p, bool initialize)
    : super(p, initialize)
{
}

template <typename Allocator>
basic_variable<Allocator>::iterator::iterator(pointer p,
                                              typename super::array_iterator where)
    : super(p, where)
{
}

template <typename Allocator>
basic_variable<Allocator>::iterator::iterator(pointer p,
                                              typename super::map_iterator where)
    : super(p, where)
{
}

template <typename Allocator>
basic_variable<Allocator>::iterator::iterator(const const_iterator& other)
    : super(const_cast<pointer>(other.scope))
{
    switch (other.current.index())
    {
    case super::small_union::template to_index<pointer>::value:
        super::current = other.current.template get<pointer>();
        break;
    case super::small_union::template to_index<typename super::array_iterator>::value:
        super::current = other.current.template get<typename super::array_iterator>();
        break;
    case super::small_union::template to_index<typename super::map_iterator>::value:
        super::current = other.current.template get<typename super::map_iterator>();
        break;
    }
}

template <typename Allocator>
auto basic_variable<Allocator>::iterator::operator= (const iterator& other) -> iterator&
{
    return super::operator=(other);
}

template <typename Allocator>
auto basic_variable<Allocator>::iterator::operator= (iterator&& other) -> iterator&
{
    return super::operator=(std::forward<iterator&&>(other));
}

//-----------------------------------------------------------------------------
// variable::const_iterator
//-----------------------------------------------------------------------------

template <typename Allocator>
basic_variable<Allocator>::const_iterator::const_iterator()
    : super()
{
}

template <typename Allocator>
basic_variable<Allocator>::const_iterator::const_iterator(const const_iterator& other)
    : super(other)
{
}

template <typename Allocator>
basic_variable<Allocator>::const_iterator::const_iterator(const_iterator&& other)
    : super(std::move(other))
{
}

template <typename Allocator>
basic_variable<Allocator>::const_iterator::const_iterator(pointer p, bool initialize)
    : super(p, initialize)
{
}

template <typename Allocator>
basic_variable<Allocator>::const_iterator::const_iterator(const iterator& other)
    : super(other.scope)
{
    switch (other.current.index())
    {
    case super::small_union::template to_index<pointer>::value:
        super::current = other.current.template get<pointer>();
        break;
    case super::small_union::template to_index<typename super::array_iterator>::value:
        super::current = other.current.template get<typename super::array_iterator>();
        break;
    case super::small_union::template to_index<typename super::map_iterator>::value:
        super::current = other.current.template get<typename super::map_iterator>();
        break;
    }
}

//-----------------------------------------------------------------------------
// variable::key_iterator
//-----------------------------------------------------------------------------

template <typename Allocator>
basic_variable<Allocator>::key_iterator::key_iterator()
    : super()
{
}

template <typename Allocator>
basic_variable<Allocator>::key_iterator::key_iterator(const key_iterator& other)
    : super(other),
      index(other.index)
{
}

template <typename Allocator>
basic_variable<Allocator>::key_iterator::key_iterator(key_iterator&& other)
{
    super::scope = std::move(other.scope);
    super::current = std::move(other.current);
    index = std::move(other.index);
}

template <typename Allocator>
basic_variable<Allocator>::key_iterator::key_iterator(pointer p, bool initialize)
    : super(p, initialize),
      index(0)
{
}

template <typename Allocator>
auto basic_variable<Allocator>::key_iterator::operator= (const key_iterator& other) -> key_iterator&
{
    return super::operator=(other);
}

template <typename Allocator>
auto basic_variable<Allocator>::key_iterator::operator= (key_iterator&& other) -> key_iterator&
{
    return super::operator=(std::forward<key_iterator>(other));
}

template <typename Allocator>
auto basic_variable<Allocator>::key_iterator::key() const -> const_reference
{
    assert(super::scope);

    switch (super::scope->symbol())
    {
    case symbol::null:
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
    case symbol::array:
        return index;

    case symbol::map:
        return super::key();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
auto basic_variable<Allocator>::key_iterator::operator++ () -> key_iterator&
{
    assert(super::scope);

    switch (super::scope->symbol())
    {
    case symbol::null:
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
    case symbol::array:
        index += 1;
        break;

    case symbol::map:
        break;
    }
    return super::operator++();
}

template <typename Allocator>
auto basic_variable<Allocator>::key_iterator::base() const -> const_iterator
{
    assert(super::scope);

    const_iterator result;
    result.scope = super::scope;
    result.current = super::current;
    return result;
}

//-----------------------------------------------------------------------------
// storage visitors
//-----------------------------------------------------------------------------

template <typename Allocator>
template <typename T>
struct basic_variable<Allocator>::similar_visitor
{
    template <typename Which>
    static bool call(const storage_type&)
    {
        using variable_type = basic_variable<Allocator>;
        using lhs_type = typename detail::overloader<variable_type, T>::category_type;
        using rhs_type = typename detail::overloader<variable_type, Which>::category_type;
        return std::is_same<lhs_type, rhs_type>::value;
    }
};

//-----------------------------------------------------------------------------
// variable
//-----------------------------------------------------------------------------

template <typename Allocator>
basic_variable<Allocator>::basic_variable()
    : storage(null)
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const basic_variable& other)
    : storage(null)
{
    switch (other.code())
    {
    case code::null:
        storage = null;
        break;
    case code::boolean:
        storage = other.assume_value<bool>();
        break;
    case code::signed_char:
        storage = other.assume_value<signed char>();
        break;
    case code::unsigned_char:
        storage = other.assume_value<unsigned char>();
        break;
    case code::signed_short_integer:
        storage = other.assume_value<signed short int>();
        break;
    case code::unsigned_short_integer:
        storage = other.assume_value<unsigned short int>();
        break;
    case code::signed_integer:
        storage = other.assume_value<signed int>();
        break;
    case code::unsigned_integer:
        storage = other.assume_value<unsigned int>();
        break;
    case code::signed_long_integer:
        storage = other.assume_value<signed long int>();
        break;
    case code::unsigned_long_integer:
        storage = other.assume_value<unsigned long int>();
        break;
    case code::signed_long_long_integer:
        storage = other.assume_value<signed long long int>();
        break;
    case code::unsigned_long_long_integer:
        storage = other.assume_value<unsigned long long int>();
        break;
    case code::real:
        storage = other.assume_value<float>();
        break;
    case code::long_real:
        storage = other.assume_value<double>();
        break;
    case code::long_long_real:
        storage = other.assume_value<long double>();
        break;
    case code::string:
        storage = other.assume_value<string_type>();
        break;
    case code::wstring:
        storage = other.assume_value<wstring_type>();
        break;
    case code::u16string:
        storage = other.assume_value<u16string_type>();
        break;
    case code::u32string:
        storage = other.assume_value<u32string_type>();
        break;
    case code::array:
        storage = other.assume_value<array_type>();
        break;
    case code::map:
        storage = other.assume_value<map_type>();
        break;
    }
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(basic_variable&& other) noexcept
    : storage(null)
{
    switch (other.code())
    {
    case code::null:
        storage = null;
        break;
    case code::boolean:
        storage = std::move(other.assume_value<bool>());
        break;
    case code::signed_char:
        storage = std::move(other.assume_value<signed char>());
        break;
    case code::unsigned_char:
        storage = std::move(other.assume_value<unsigned char>());
        break;
    case code::signed_short_integer:
        storage = std::move(other.assume_value<signed short int>());
        break;
    case code::unsigned_short_integer:
        storage = std::move(other.assume_value<unsigned short int>());
        break;
    case code::signed_integer:
        storage = std::move(other.assume_value<signed int>());
        break;
    case code::unsigned_integer:
        storage = std::move(other.assume_value<unsigned int>());
        break;
    case code::signed_long_integer:
        storage = std::move(other.assume_value<signed long int>());
        break;
    case code::unsigned_long_integer:
        storage = std::move(other.assume_value<unsigned long int>());
        break;
    case code::signed_long_long_integer:
        storage = std::move(other.assume_value<signed long long int>());
        break;
    case code::unsigned_long_long_integer:
        storage = std::move(other.assume_value<unsigned long long int>());
        break;
    case code::real:
        storage = std::move(other.assume_value<float>());
        break;
    case code::long_real:
        storage = std::move(other.assume_value<double>());
        break;
    case code::long_long_real:
        storage = std::move(other.assume_value<long double>());
        break;
    case code::string:
        storage = std::move(other.assume_value<string_type>());
        break;
    case code::wstring:
        storage = std::move(other.assume_value<wstring_type>());
        break;
    case code::u16string:
        storage = std::move(other.assume_value<u16string_type>());
        break;
    case code::u32string:
        storage = std::move(other.assume_value<u32string_type>());
        break;
    case code::array:
        storage = std::move(other.assume_value<array_type>());
        break;
    case code::map:
        // This is not guaranteed to be noexcept
        storage = std::move(other.assume_value<map_type>());
        break;
    }
}

template <typename Allocator>
template <typename T>
basic_variable<Allocator>::basic_variable(T value)
    : storage(typename detail::overloader<value_type, typename std::decay<T>::type>::type(std::move(value)))
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const std::initializer_list<value_type>& init)
    : storage(null)
{
    if (init.size() == 0)
    {
        storage = array_type{};
        return;
    }

    for (const auto& i : init)
    {
        if (i.is_pair())
            continue;

        storage = array_type(init);
        return;
    }

    storage = map_type{};
    auto& map = assume_value<map_type>();
    for (const auto& i : init)
    {
        auto& array = i.template assume_value<array_type>();
        map[array[0]] = array[1];
    }
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const nullable&)
    : storage(null)
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const char *value)
    : storage(string_type(value))
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const wchar_t *value)
    : storage(wstring_type(value))
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const char16_t *value)
    : storage(u16string_type(value))
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const char32_t *value)
    : storage(u32string_type(value))
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const typename basic_variable::array_type& value)
    : storage(value)
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(typename basic_variable::array_type&& value)
    : storage(std::move(value))
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(const typename basic_variable::map_type& value)
    : storage(value)
{
}

template <typename Allocator>
basic_variable<Allocator>::basic_variable(typename basic_variable::map_type&& value)
    : storage(std::move(value))
{
}

template <typename Allocator>
auto basic_variable<Allocator>::operator= (const basic_variable& other) -> basic_variable&
{
    switch (other.code())
    {
    case code::null:
        storage = null;
        break;
    case code::boolean:
        storage = other.assume_value<bool>();
        break;
    case code::signed_char:
        storage = other.assume_value<signed char>();
        break;
    case code::unsigned_char:
        storage = other.assume_value<unsigned char>();
        break;
    case code::signed_short_integer:
        storage = other.assume_value<signed short int>();
        break;
    case code::unsigned_short_integer:
        storage = other.assume_value<unsigned short int>();
        break;
    case code::signed_integer:
        storage = other.assume_value<signed int>();
        break;
    case code::unsigned_integer:
        storage = other.assume_value<unsigned int>();
        break;
    case code::signed_long_integer:
        storage = other.assume_value<signed long int>();
        break;
    case code::unsigned_long_integer:
        storage = other.assume_value<unsigned long int>();
        break;
    case code::signed_long_long_integer:
        storage = other.assume_value<signed long long int>();
        break;
    case code::unsigned_long_long_integer:
        storage = other.assume_value<unsigned long long int>();
        break;
    case code::real:
        storage = other.assume_value<float>();
        break;
    case code::long_real:
        storage = other.assume_value<double>();
        break;
    case code::long_long_real:
        storage = other.assume_value<long double>();
        break;
    case code::string:
        storage = other.assume_value<string_type>();
        break;
    case code::wstring:
        storage = other.assume_value<wstring_type>();
        break;
    case code::u16string:
        storage = other.assume_value<u16string_type>();
        break;
    case code::u32string:
        storage = other.assume_value<u32string_type>();
        break;
    case code::array:
        storage = other.assume_value<array_type>();
        break;
    case code::map:
        storage = other.assume_value<map_type>();
        break;
    }
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator= (basic_variable&& other) -> basic_variable&
{
    switch (other.code())
    {
    case code::null:
        storage = null;
        break;
    case code::boolean:
        storage = std::move(other.assume_value<bool>());
        break;
    case code::signed_char:
        storage = std::move(other.assume_value<signed char>());
        break;
    case code::unsigned_char:
        storage = std::move(other.assume_value<unsigned char>());
        break;
    case code::signed_short_integer:
        storage = std::move(other.assume_value<signed short int>());
        break;
    case code::unsigned_short_integer:
        storage = std::move(other.assume_value<unsigned short int>());
        break;
    case code::signed_integer:
        storage = std::move(other.assume_value<signed int>());
        break;
    case code::unsigned_integer:
        storage = std::move(other.assume_value<unsigned int>());
        break;
    case code::signed_long_integer:
        storage = std::move(other.assume_value<signed long int>());
        break;
    case code::unsigned_long_integer:
        storage = std::move(other.assume_value<unsigned long int>());
        break;
    case code::signed_long_long_integer:
        storage = std::move(other.assume_value<signed long long int>());
        break;
    case code::unsigned_long_long_integer:
        storage = std::move(other.assume_value<unsigned long long int>());
        break;
    case code::real:
        storage = std::move(other.assume_value<float>());
        break;
    case code::long_real:
        storage = std::move(other.assume_value<double>());
        break;
    case code::long_long_real:
        storage = std::move(other.assume_value<long double>());
        break;
    case code::string:
        storage = std::move(other.assume_value<string_type>());
        break;
    case code::wstring:
        storage = std::move(other.assume_value<wstring_type>());
        break;
    case code::u16string:
        storage = std::move(other.assume_value<u16string_type>());
        break;
    case code::u32string:
        storage = std::move(other.assume_value<u32string_type>());
        break;
    case code::array:
        storage = std::move(other.assume_value<array_type>());
        break;
    case code::map:
        storage = std::move(other.assume_value<map_type>());
        break;
    }
    return *this;
}

template <typename Allocator>
template <typename T>
auto basic_variable<Allocator>::operator= (T value) -> basic_variable&
{
    storage = typename detail::overloader<value_type, T>::type{std::move(value)};
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator= (nullable) -> basic_variable&
{
    storage = null;
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator= (const char *value) -> basic_variable&
{
    storage = string_type{value};
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator= (const wchar_t *value) -> basic_variable&
{
    storage = wstring_type{value};
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator= (const char16_t *value) -> basic_variable&
{
    storage = u16string_type{value};
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator= (const char32_t *value) -> basic_variable&
{
    storage = u32string_type{value};
    return *this;
}

template <typename Allocator>
template <typename T>
auto basic_variable<Allocator>::operator+= (const T& other) -> basic_variable&
{
    detail::overloader<value_type, T>::append(*this, other);
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator+= (const basic_variable& other) -> basic_variable&
{
    switch (other.code())
    {
    case code::null:
        detail::overloader<value_type, nullable>::
            append(*this, other.assume_value<nullable>());
        break;
    case code::boolean:
        detail::overloader<value_type, bool>::
            append(*this, other.assume_value<bool>());
        break;
    case code::signed_char:
        detail::overloader<value_type, signed char>::
            append(*this, other.assume_value<signed char>());
        break;
    case code::unsigned_char:
        detail::overloader<value_type, unsigned char>::
            append(*this, other.assume_value<unsigned char>());
        break;
    case code::signed_short_integer:
        detail::overloader<value_type, signed short int>::
            append(*this, other.assume_value<signed short int>());
        break;
    case code::unsigned_short_integer:
        detail::overloader<value_type, unsigned short int>::
            append(*this, other.assume_value<unsigned short int>());
        break;
    case code::signed_integer:
        detail::overloader<value_type, signed int>::
            append(*this, other.assume_value<signed int>());
        break;
    case code::unsigned_integer:
        detail::overloader<value_type, unsigned int>::
            append(*this, other.assume_value<unsigned int>());
        break;
    case code::signed_long_integer:
        detail::overloader<value_type, signed long int>::
            append(*this, other.assume_value<signed long int>());
        break;
    case code::unsigned_long_integer:
        detail::overloader<value_type, unsigned long int>::
            append(*this, other.assume_value<unsigned long int>());
        break;
    case code::signed_long_long_integer:
        detail::overloader<value_type, signed long long int>::
            append(*this, other.assume_value<signed long long int>());
        break;
    case code::unsigned_long_long_integer:
        detail::overloader<value_type, unsigned long long int>::
            append(*this, other.assume_value<unsigned long long int>());
        break;
    case code::real:
        detail::overloader<value_type, float>::
            append(*this, other.assume_value<float>());
        break;
    case code::long_real:
        detail::overloader<value_type, double>::
            append(*this, other.assume_value<double>());
        break;
    case code::long_long_real:
        detail::overloader<value_type, long double>::
            append(*this, other.assume_value<long double>());
        break;
    case code::string:
        detail::overloader<value_type, string_type>::
            append(*this, other.assume_value<string_type>());
        break;
    case code::wstring:
        detail::overloader<value_type, wstring_type>::
            append(*this, other.assume_value<wstring_type>());
        break;
    case code::u16string:
        detail::overloader<value_type, u16string_type>::
            append(*this, other.assume_value<u16string_type>());
        break;
    case code::u32string:
        detail::overloader<value_type, u32string_type>::
            append(*this, other.assume_value<u32string_type>());
        break;
    case code::array:
        detail::overloader<value_type, array_type>::
            append(*this, other.assume_value<array_type>());
        break;
    case code::map:
        detail::overloader<value_type, map_type>::
            append(*this, other.assume_value<map_type>());
        break;
    }
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator+= (const char *other) -> basic_variable&
{
    detail::overloader<value_type, string_type>::append(*this, other);
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator+= (const wchar_t *other) -> basic_variable&
{
    detail::overloader<value_type, wstring_type>::append(*this, other);
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator+= (const char16_t *other) -> basic_variable&
{
    detail::overloader<value_type, u16string_type>::append(*this, other);
    return *this;
}

template <typename Allocator>
auto basic_variable<Allocator>::operator+= (const char32_t *other) -> basic_variable&
{
    detail::overloader<value_type, u32string_type>::append(*this, other);
    return *this;
}

template <typename Allocator, typename U>
auto operator+ (const basic_variable<Allocator>& lhs, const U& rhs) -> basic_variable<Allocator>
{
    basic_variable<Allocator> result(lhs);
    result += rhs;
    return result;
}

template <typename Allocator>
auto operator+ (nullable,
                const basic_variable<Allocator>& rhs) -> basic_variable<Allocator>
{
    basic_variable<Allocator> result;
    result += rhs;
    return result;
}

template <typename Allocator>
template <typename R>
basic_variable<Allocator>::operator R() const
{
    return value<R>();
}

template <typename Allocator>
template <typename Tag>
auto basic_variable<Allocator>::value(std::error_code& error) const noexcept -> typename tag_traits<typename std::decay<Tag>::type>::type
{
    using return_type = typename tag_traits<typename std::decay<Tag>::type>::type;
    return detail::overloader<value_type, return_type>::convert(*this, error);
}

template <typename Allocator>
template <typename Tag>
auto basic_variable<Allocator>::value() const -> typename tag_traits<typename std::decay<Tag>::type>::type
{
    std::error_code error;
    auto result = value<Tag>(error);
    if (error)
        throw dynamic::error(error);
    return result;
}

template <typename Allocator>
template <typename R>
auto basic_variable<Allocator>::assume_value() & noexcept -> R&
{
    assert(same<R>());
    return storage.template get<typename std::decay<R>::type>();
}

template <typename Allocator>
template <typename R>
auto basic_variable<Allocator>::assume_value() const & noexcept -> const R&
{
    assert(same<R>());
    return storage.template get<typename std::decay<R>::type>();
}

template <typename Allocator>
basic_variable<Allocator>::operator bool() const
{
    switch (code())
    {
    case code::null:
        return false;
    case code::boolean:
        return bool(assume_value<bool>());
    case code::signed_char:
        return bool(assume_value<signed char>());
    case code::unsigned_char:
        return bool(assume_value<unsigned char>());
    case code::signed_short_integer:
        return bool(assume_value<signed short int>());
    case code::unsigned_short_integer:
        return bool(assume_value<unsigned short int>());
    case code::signed_integer:
        return bool(assume_value<signed int>());
    case code::unsigned_integer:
        return bool(assume_value<unsigned int>());
    case code::signed_long_integer:
        return bool(assume_value<signed long int>());
    case code::unsigned_long_integer:
        return bool(assume_value<unsigned long int>());
    case code::signed_long_long_integer:
        return bool(assume_value<signed long long int>());
    case code::unsigned_long_long_integer:
        return bool(assume_value<unsigned long long int>());
    case code::real:
        return bool(assume_value<float>());
    case code::long_real:
        return bool(assume_value<double>());
    case code::long_long_real:
        return bool(assume_value<long double>());
    case code::string:
    case code::wstring:
    case code::u16string:
    case code::u32string:
        throw dynamic::error(incompatible_type);
    case code::array:
    case code::map:
        // C++ containers are not contextually convertible to bool, but we
        // make them so for variable to let the code compiler for non-container
        // types.
        throw dynamic::error(incompatible_type);
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
auto basic_variable<Allocator>::operator[] (size_type position) & -> basic_variable&
{
    switch (symbol())
    {
    case symbol::array:
        return assume_value<array_type>()[position];

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename Allocator>
auto basic_variable<Allocator>::operator[] (size_type position) const & -> const basic_variable&
{
    switch (symbol())
    {
    case symbol::array:
        return assume_value<array_type>().at(position);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename Allocator>
auto basic_variable<Allocator>::operator[] (const typename map_type::key_type& key) & -> basic_variable&
{
    switch (symbol())
    {
    case symbol::null:
        *this = basic_map<Allocator>::make();
        goto case_map;
    case symbol::map:
    case_map:
        return assume_value<map_type>()[key];

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename Allocator>
auto basic_variable<Allocator>::operator[] (const typename map_type::key_type& key) const & -> const basic_variable&
{
    switch (symbol())
    {
    case symbol::map:
        return assume_value<map_type>().at(key);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename Allocator>
template <typename Tag>
bool basic_variable<Allocator>::is() const noexcept
{
    using tag_type = typename tag_traits<typename std::decay<Tag>::type>::type;
    return storage.template call<similar_visitor<tag_type>, bool>();
}

template <typename Allocator>
template <typename T>
bool basic_variable<Allocator>::same() const noexcept
{
    return detail::same_overloader<Allocator, T>::same(storage.index());
}

template <typename Allocator>
dynamic::code::value basic_variable<Allocator>::code() const noexcept
{
    switch (storage.index())
    {
    case traits<nullable>::value:
        return code::null;
    case traits<bool>::value:
        return code::boolean;
    case traits<signed char>::value:
        return code::signed_char;
    case traits<unsigned char>::value:
        return code::unsigned_char;
    case traits<signed short int>::value:
        return code::signed_short_integer;
    case traits<unsigned short int>::value:
        return code::unsigned_short_integer;
    case traits<signed int>::value:
        return code::signed_integer;
    case traits<unsigned int>::value:
        return code::unsigned_integer;
    case traits<signed long int>::value:
        return code::signed_long_integer;
    case traits<unsigned long int>::value:
        return code::unsigned_long_integer;
    case traits<signed long long int>::value:
        return code::signed_long_long_integer;
    case traits<unsigned long long int>::value:
        return code::unsigned_long_long_integer;
    case traits<float>::value:
        return code::real;
    case traits<double>::value:
        return code::long_real;
    case traits<long double>::value:
        return code::long_long_real;
    case traits<string_type>::value:
        return code::string;
    case traits<wstring_type>::value:
        return code::wstring;
    case traits<u16string_type>::value:
        return code::u16string;
    case traits<u32string_type>::value:
        return code::u32string;
    case traits<array_type>::value:
        return code::array;
    case traits<map_type>::value:
        return code::map;
    default:
        assert(false);
        return code::null;
    }
}

template <typename Allocator>
dynamic::symbol::value basic_variable<Allocator>::symbol() const noexcept
{
    switch (storage.index())
    {
    case traits<nullable>::value:
        return symbol::null;
    case traits<bool>::value:
        return symbol::boolean;
    case traits<signed char>::value:
    case traits<unsigned char>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
        return symbol::integer;
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
        return symbol::real;
    case traits<string_type>::value:
        return symbol::string;
    case traits<wstring_type>::value:
        return symbol::wstring;
    case traits<u16string_type>::value:
        return symbol::u16string;
    case traits<u32string_type>::value:
        return symbol::u32string;
    case traits<array_type>::value:
        return symbol::array;
    case traits<map_type>::value:
        return symbol::map;
    default:
        assert(false);
        return symbol::null;
    }
}

template <typename Allocator>
bool basic_variable<Allocator>::empty() const noexcept
{
    switch (symbol())
    {
    case symbol::null:
        return true;
    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::wstring:
    case symbol::u16string:
    case symbol::u32string:
        return false;
    case symbol::array:
        return assume_value<array_type>().empty();
    case symbol::map:
        return assume_value<map_type>().empty();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
auto basic_variable<Allocator>::size() const noexcept -> size_type
{
    switch (symbol())
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
        return 1;
    case symbol::array:
        return assume_value<array_type>().size();
    case symbol::map:
        return assume_value<map_type>().size();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
auto basic_variable<Allocator>::max_size() const noexcept -> size_type
{
    switch (symbol())
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
        return 1;
    case symbol::array:
        return assume_value<array_type>().max_size();
    case symbol::map:
        return assume_value<map_type>().max_size();
    }
    TRIAL_DYNAMIC_UNREACHABLE();
}

template <typename Allocator>
void basic_variable<Allocator>::clear() noexcept
{
    switch (code())
    {
    case code::null:
        storage = null;
        break;
    case code::boolean:
        storage = bool{};
        break;
    case code::signed_char:
        {
            const signed char value = 0;
            storage = value;
        }
        break;
    case code::unsigned_char:
        {
            const unsigned char value = 0U;
            storage = value;
        }
        break;
    case code::signed_short_integer:
        {
            const signed short int value = 0;
            storage = value;
        }
        break;
    case code::unsigned_short_integer:
        {
            const unsigned short int value = 0U;
            storage = value;
        }
        break;
    case code::signed_integer:
        storage = 0;
        break;
    case code::unsigned_integer:
        storage = 0U;
        break;
    case code::signed_long_integer:
        storage = 0L;
        break;
    case code::unsigned_long_integer:
        storage = 0UL;
        break;
    case code::signed_long_long_integer:
        storage = 0LL;
        break;
    case code::unsigned_long_long_integer:
        storage = 0ULL;
        break;
    case code::real:
        storage = 0.0f;
        break;
    case code::long_real:
        storage = 0.0;
        break;
    case code::long_long_real:
        storage = 0.0L;
        break;
    case code::string:
        assume_value<string_type>().clear();
        break;
    case code::wstring:
        assume_value<wstring_type>().clear();
        break;
    case code::u16string:
        assume_value<u16string_type>().clear();
        break;
    case code::u32string:
        assume_value<u32string_type>().clear();
        break;
    case code::array:
        assume_value<array_type>().clear();
        break;
    case code::map:
        assume_value<map_type>().clear();
        break;
    }
}

template <typename Allocator>
auto basic_variable<Allocator>::insert(basic_variable value) -> iterator
{
    switch (symbol())
    {
    case symbol::null:
        *this = basic_array<Allocator>::make();
        goto case_array;
    case symbol::array:
    case_array:
    {
        // Insert at end
        auto& array = assume_value<array_type>();
        array.emplace_back(std::move(value));
        return iterator(this, --array.end());
        }

    case symbol::map:
        if (value.is_pair())
        {
            auto result = assume_value<map_type>().insert(pair_type{std::move(value[0]), std::move(value[1])});
            return iterator(this, std::move(result.first));
        }
        break;

    default:
        break;
    }

    throw dynamic::error(incompatible_type);
}

template <typename Allocator>
template <typename InputIterator>
void basic_variable<Allocator>::insert(InputIterator begin,
                                       InputIterator end)
{
    return detail::iterator_overloader<Allocator, InputIterator>
        ::insert(*this, std::move(begin), std::move(end));
}

template <typename Allocator>
auto basic_variable<Allocator>::insert(const_iterator where, const basic_variable& value) -> iterator
{
    switch (symbol())
    {
    case symbol::array:
        {
            auto result = assume_value<array_type>()
                .insert(where.current.template get<typename const_iterator::array_iterator>(),
                        value);
            return iterator(this, result);
        }

    case symbol::map:
        if (value.is_pair())
        {
            // Use iterator as hint
            auto result = assume_value<map_type>()
                .insert(where.current.template get<typename const_iterator::map_iterator>(),
                        pair_type{value[0], value[1]});
            return iterator(this, std::move(result));
        }
        break;

    default:
        break;
    }

    throw dynamic::error(incompatible_type);
}

template <typename Allocator>
template <typename InputIterator>
void basic_variable<Allocator>::insert(const_iterator where,
                                       InputIterator begin,
                                       InputIterator end)
{
    return detail::iterator_overloader<Allocator, InputIterator>
        ::insert(*this, std::move(where), std::move(begin), std::move(end));
}

template <typename Allocator>
auto basic_variable<Allocator>::erase(iterator where) -> iterator
{
    // The iterator to iterator signature was introduced in C++17 as a
    // resolution to LWG defect 2059.

    using array_iterator = typename basic_variable::const_iterator::array_iterator;
    using map_iterator = typename basic_variable::const_iterator::map_iterator;

    switch (symbol())
    {
    case symbol::array:
        {
            auto& array = assume_value<array_type>();
            auto& array_where = where.current.template get<array_iterator>();
            where.current = array.erase(array_where);
        }
        break;

    case symbol::map:
        where.current =
            assume_value<map_type>().erase(where.current.template get<map_iterator>());
        break;

    default:
        // Non-container types are unerasable
        break;
    }
    return where;
}

template <typename Allocator>
auto basic_variable<Allocator>::erase(const_iterator where) -> iterator
{
    // The const_iterator to iterator signature was introduced in C++11 by
    // proposal N2350.

    using array_iterator = typename basic_variable::const_iterator::array_iterator;
    using map_iterator = typename basic_variable::const_iterator::map_iterator;

    auto result = iterator(where);

    switch (symbol())
    {
    case symbol::array:
        {
            auto& array = assume_value<array_type>();
            auto& array_where = where.current.template get<array_iterator>();
            result.current = array.erase(array_where);
        }
        break;

    case symbol::map:
        result.current =
            assume_value<map_type>().erase(where.current.template get<map_iterator>());
        break;

    default:
        // Non-container types are unerasable
        break;
    }
    return result;
}

template <typename Allocator>
auto basic_variable<Allocator>::erase(const_iterator first, const_iterator last) -> iterator
{
    using array_iterator = typename basic_variable::const_iterator::array_iterator;
    using map_iterator = typename basic_variable::const_iterator::map_iterator;

    auto result = iterator(first);

    switch (symbol())
    {
    case symbol::array:
        result.current =
            assume_value<array_type>().erase(first.current.template get<array_iterator>(),
                                             last.current.template get<array_iterator>());
        break;

    case symbol::map:
        result.current =
            assume_value<map_type>().erase(first.current.template get<map_iterator>(),
                                           last.current.template get<map_iterator>());
        break;

    default:
        // Non-container types are unerasable
        break;
    }
    return result;
}

template <typename Allocator>
void basic_variable<Allocator>::swap(basic_variable& other) noexcept
{
    using std::swap;
    swap(*this, other);
}

template <typename Allocator>
auto basic_variable<Allocator>::begin() & -> iterator
{
    return iterator(this);
}

template <typename Allocator>
auto basic_variable<Allocator>::begin() const & -> const_iterator
{
    return const_iterator(this);
}

template <typename Allocator>
auto basic_variable<Allocator>::cbegin() const & -> const_iterator
{
    return begin();
}

template <typename Allocator>
auto basic_variable<Allocator>::end() & -> iterator
{
    return iterator(this, false);
}

template <typename Allocator>
auto basic_variable<Allocator>::end() const & -> const_iterator
{
    return const_iterator(this, false);
}

template <typename Allocator>
auto basic_variable<Allocator>::cend() const & -> const_iterator
{
    return end();
}

template <typename Allocator>
auto basic_variable<Allocator>::rbegin() & -> reverse_iterator
{
    return reverse_iterator(end());
}

template <typename Allocator>
auto basic_variable<Allocator>::rbegin() const & -> const_reverse_iterator
{
    return const_reverse_iterator(cend());
}

template <typename Allocator>
auto basic_variable<Allocator>::crbegin() const & -> const_reverse_iterator
{
    return const_reverse_iterator(cend());
}

template <typename Allocator>
auto basic_variable<Allocator>::rend() & -> reverse_iterator
{
    return reverse_iterator(begin());
}

template <typename Allocator>
auto basic_variable<Allocator>::rend() const & -> const_reverse_iterator
{
    return const_reverse_iterator(cbegin());
}

template <typename Allocator>
auto basic_variable<Allocator>::crend() const & -> const_reverse_iterator
{
    return const_reverse_iterator(cbegin());
}

template <typename Allocator>
auto basic_variable<Allocator>::key_begin() const & -> key_iterator
{
    return key_iterator(this);
}

template <typename Allocator>
auto basic_variable<Allocator>::key_end() const & -> key_iterator
{
    return key_iterator(this, false);
}

template <typename Allocator>
bool basic_variable<Allocator>::is_pair() const
{
    return is<array>() && (size() == 2);
}

// Container comparison operators are noexcept from C++14

template <typename Allocator, typename U>
auto operator== (const basic_variable<Allocator>& lhs, const U& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    -> typename std::enable_if<!std::is_same<U, basic_variable<Allocator>>::value, bool>::type
{
    return detail::operator_overloader<basic_variable<Allocator>, U>::equal(lhs, rhs);
}

template <typename T, typename Allocator>
auto operator== (const T& lhs, const basic_variable<Allocator>& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    -> typename std::enable_if<!std::is_same<T, basic_variable<Allocator>>::value, bool>::type
{
    return detail::operator_overloader<T, basic_variable<Allocator>>::equal(lhs, rhs);
}

template <typename Allocator>
bool operator== (const basic_variable<Allocator>& lhs, const basic_variable<Allocator>& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
{
    return detail::operator_overloader<basic_variable<Allocator>, basic_variable<Allocator>>::equal(lhs, rhs);
}

template <typename T, typename U>
bool operator!= (const T& lhs, const U& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
{
    return !(lhs == rhs);
}

template <typename Allocator, typename U>
auto operator< (const basic_variable<Allocator>& lhs, const U& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    -> typename std::enable_if<!std::is_same<U, basic_variable<Allocator>>::value, bool>::type
{
    return detail::operator_overloader<basic_variable<Allocator>, U>::less(lhs, rhs);
}

template <typename T, typename Allocator>
auto operator< (const T& lhs, const basic_variable<Allocator>& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
    -> typename std::enable_if<!std::is_same<T, basic_variable<Allocator>>::value, bool>::type
{
    return detail::operator_overloader<T, basic_variable<Allocator>>::less(lhs, rhs);
}

template <typename Allocator>
bool operator< (const basic_variable<Allocator>& lhs, const basic_variable<Allocator>& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
{
    return detail::operator_overloader<basic_variable<Allocator>, basic_variable<Allocator>>::less(lhs, rhs);
}

template <typename Allocator, typename U>
bool operator<= (const basic_variable<Allocator>& lhs, const U& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
{
    if (lhs.template same<nullable>())
        return true;

    return !(rhs < lhs);
}

template <typename Allocator, typename U>
bool operator> (const basic_variable<Allocator>& lhs, const U& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
{
    if (lhs.template same<nullable>())
        return false;

    return rhs < lhs;
}

template <typename T, typename U>
bool operator>= (const T& lhs, const U& rhs) TRIAL_DYNAMIC_CXX14(noexcept)
{
    return !(lhs < rhs);
}

//-----------------------------------------------------------------------------
// Factories
//-----------------------------------------------------------------------------

template <typename Allocator>
struct basic_array
{
    static basic_variable<Allocator> make()
    {
        basic_variable<Allocator> result;
        result.storage = typename basic_variable<Allocator>::array_type{};
        return result;
    }

    template <typename ForwardIterator>
    static basic_variable<Allocator> make(ForwardIterator begin, ForwardIterator end)
    {
        basic_variable<Allocator> result;
        result.storage = typename basic_variable<Allocator>::array_type(begin, end);
        return result;
    }

    static basic_variable<Allocator> make(std::initializer_list<typename basic_variable<Allocator>::value_type> init)
    {
        basic_variable<Allocator> result;
        result.storage = typename basic_variable<Allocator>::array_type(init.begin(), init.end());
        return result;
    }

    template <typename T>
    static basic_variable<Allocator> repeat(typename basic_variable<Allocator>::size_type size,
                                            const T& value)
    {
        basic_variable<Allocator> result;
        result.storage = typename basic_variable<Allocator>::array_type(size, basic_variable<Allocator>(value));
        return result;
    }
};

template <typename Allocator>
struct basic_map
{
    static basic_variable<Allocator> make()
    {
        basic_variable<Allocator> result;
        result.storage = typename basic_variable<Allocator>::map_type{};
        return result;
    }

    template <typename T, typename U>
    static basic_variable<Allocator> make(T key, U value)
    {
        return make({ std::move(key), std::move(value) });
    }

    static basic_variable<Allocator> make(typename basic_variable<Allocator>::pair_type value)
    {
        basic_variable<Allocator> result;
        result.storage = typename basic_variable<Allocator>::map_type{std::move(value)};
        return result;
    }

    static basic_variable<Allocator> make(std::initializer_list<typename basic_variable<Allocator>::pair_type> init)
    {
        basic_variable<Allocator> result;
        result.storage = typename basic_variable<Allocator>::map_type(init.begin(), init.end());
        return result;
    }
};

} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_DETAIL_VARIABLE_IPP
