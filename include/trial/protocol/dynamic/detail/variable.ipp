#ifndef TRIAL_PROTOCOL_DYNAMIC_DETAIL_VARIABLE_IPP
#define TRIAL_PROTOCOL_DYNAMIC_DETAIL_VARIABLE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/core/detail/type_traits.hpp>
#include <trial/protocol/dynamic/error.hpp>

namespace trial
{
namespace protocol
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
using is_boolean = core::detail::is_bool<T>;

template <typename T>
using is_integer = typename std::conditional<std::is_integral<T>::value && !detail::is_boolean<T>::value,
                                             std::true_type,
                                             std::false_type>::type;

template <typename T>
using is_number = std::is_floating_point<T>;

template <typename CharT, typename T>
using is_string = std::is_same<T, typename basic_variable<CharT>::string_type>;

template <typename CharT, typename T>
using is_array = std::is_same<T, typename basic_variable<CharT>::array_type>;

template <typename CharT, typename T>
using is_map = std::is_same<T, typename basic_variable<CharT>::map_type>;

} // namespace detail

//-----------------------------------------------------------------------------
// variable::traits
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::traits
{
    static const std::size_t value = decltype(basic_variable<CharT>::storage)::template index<T>::value;
};

//-----------------------------------------------------------------------------
// variable::tag_traits
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T, typename>
struct basic_variable<CharT>::tag_traits
{
    using type = T;
};

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, nullable>::value>::type>
{
    using type = nullable;
};

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::boolean>::value>::type>
{
    using type = bool;
};

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::integer>::value>::type>
{
    using type = int;
};

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::number>::value>::type>
{
    using type = float;
};

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::string>::value>::type>
{
    using type = typename basic_variable<CharT>::string_type;
};

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::array>::value>::type>
{
    using type = typename basic_variable<CharT>::array_type;
};

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::tag_traits<
    T,
    typename std::enable_if<std::is_same<T, typename dynamic::map>::value>::type>
{
    using type = typename basic_variable<CharT>::map_type;
};

//-----------------------------------------------------------------------------
// detail::overloader
//-----------------------------------------------------------------------------

namespace detail
{

template <typename T, typename U, typename = void>
struct overloader
{
    static_assert(sizeof(T) == 0, "Unsupported type");
};

// Null

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_null<U>::value>::type>
{
    using variable_type = basic_variable<CharT>;
    using type = nullable;
    using category_type = type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::null:
            return {};

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U&) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::null:
            return true;

        default:
            return false;
        }
    }

    static bool less(const variable_type&, const U&) TRIAL_PROTOCOL_CXX14(noexcept)
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

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_boolean<U>::value>::type>
{
    using type = bool;
    using category_type = type;
    using variable_type = basic_variable<CharT>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>();

        case token::code::signed_char:
            return self.template unsafe_get<signed char>();

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>();

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>();

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>();

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>();

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>();

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>();

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>();

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>();

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>();

        case token::code::float_number:
            return self.template unsafe_get<float>();

        case token::code::double_number:
            return self.template unsafe_get<double>();

        case token::code::long_double_number:
            return self.template unsafe_get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>() == other;

        case token::code::signed_char:
            return self.template unsafe_get<signed char>() == other;

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>() == other;

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>() == other;

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>() == other;

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>() == other;

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>() == other;

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>() == other;

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>() == other;

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>() == other;

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>() == other;

        case token::code::float_number:
            return self.template unsafe_get<float>() == other;

        case token::code::double_number:
            return self.template unsafe_get<double>() == other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::null:
            return true;

        case token::code::boolean:
            return self.template unsafe_get<bool>() < other;

        case token::code::signed_char:
            return self.template unsafe_get<signed char>() < other;

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>() < other;

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>() < other;

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>() < other;

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>() < other;

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>() < other;

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>() < other;

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>() < other;

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>() < other;

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>() < other;

        case token::code::float_number:
            return self.template unsafe_get<float>() < other;

        case token::code::double_number:
            return self.template unsafe_get<double>() < other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case token::code::null:
            self.storage = other; // Overwrite null
            break;

        case token::code::boolean:
            self.template unsafe_get<bool>() += other;
            break;

        case token::code::signed_char:
            self.template unsafe_get<signed char>() += other;
            break;

        case token::code::unsigned_char:
            self.template unsafe_get<unsigned char>() += other;
            break;

        case token::code::signed_short_integer:
            self.template unsafe_get<signed short int>() += other;
            break;

        case token::code::unsigned_short_integer:
            self.template unsafe_get<unsigned short int>() += other;
            break;

        case token::code::signed_integer:
            self.template unsafe_get<signed int>() += other;
            break;

        case token::code::unsigned_integer:
            self.template unsafe_get<unsigned int>() += other;
            break;

        case token::code::signed_long_integer:
            self.template unsafe_get<signed long int>() += other;
            break;

        case token::code::unsigned_long_integer:
            self.template unsafe_get<unsigned long int>() += other;
            break;

        case token::code::signed_long_long_integer:
            self.template unsafe_get<signed long long int>() += other;
            break;

        case token::code::unsigned_long_long_integer:
            self.template unsafe_get<unsigned long long int>() += other;
            break;

        case token::code::float_number:
            self.template unsafe_get<float>() += other;
            break;

        case token::code::double_number:
            self.template unsafe_get<double>() += other;
            break;

        case token::code::long_double_number:
            self.template unsafe_get<long double>() += other;
            break;

        case token::code::array:
            self.template unsafe_get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Signed integer

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_integer<U>::value &&
                            std::is_signed<U>::value>::type>
{
    using type = U;
    using category_type = int;
    using variable_type = basic_variable<CharT>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>();

        case token::code::signed_char:
            return self.template unsafe_get<signed char>();

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>();

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>();

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>();

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>();

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>();

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>();

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>();

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>();

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>();

        case token::code::float_number:
            return self.template unsafe_get<float>();

        case token::code::double_number:
            return self.template unsafe_get<double>();

        case token::code::long_double_number:
            return self.template unsafe_get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>() == other;

        case token::code::signed_char:
            return self.template unsafe_get<signed char>() == other;
        case token::code::unsigned_char:
            return static_cast<signed char>(self.template unsafe_get<unsigned char>()) == other;

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>() == other;
        case token::code::unsigned_short_integer:
            return static_cast<signed short int>(self.template unsafe_get<unsigned short int>()) == other;

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>() == other;
        case token::code::unsigned_integer:
            return static_cast<signed int>(self.template unsafe_get<unsigned int>()) == other;

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>() == other;
        case token::code::unsigned_long_integer:
            return static_cast<signed long int>(self.template unsafe_get<unsigned long int>()) == other;

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>() == other;
        case token::code::unsigned_long_long_integer:
            return static_cast<signed long long int>(self.template unsafe_get<unsigned long long int>()) == other;

        case token::code::float_number:
            return self.template unsafe_get<float>() == other;

        case token::code::double_number:
            return self.template unsafe_get<double>() == other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::null:
            return true;

        case token::code::boolean:
            return self.template unsafe_get<bool>() < other;

        case token::code::signed_char:
            return self.template unsafe_get<signed char>() < other;
        case token::code::unsigned_char:
            return static_cast<signed char>(self.template unsafe_get<unsigned char>()) < other;

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>() < other;
        case token::code::unsigned_short_integer:
            return static_cast<signed short int>(self.template unsafe_get<unsigned short int>()) < other;

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>() < other;
        case token::code::unsigned_integer:
            return static_cast<signed int>(self.template unsafe_get<unsigned int>()) < other;

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>() < other;
        case token::code::unsigned_long_integer:
            return static_cast<signed long int>(self.template unsafe_get<unsigned long int>()) < other;

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>() < other;
        case token::code::unsigned_long_long_integer:
            return static_cast<signed long long int>(self.template unsafe_get<unsigned long long int>()) < other;

        case token::code::float_number:
            return self.template unsafe_get<float>() < other;

        case token::code::double_number:
            return self.template unsafe_get<double>() < other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case token::code::null:
            self.storage = other; // Overwrite null
            break;

        case token::code::boolean:
            self.template unsafe_get<bool>() += other;
            break;

        case token::code::signed_char:
            self.template unsafe_get<signed char>() += other;
            break;

        case token::code::unsigned_char:
            self.template unsafe_get<unsigned char>() += other;
            break;

        case token::code::signed_short_integer:
            self.template unsafe_get<signed short int>() += other;
            break;

        case token::code::unsigned_short_integer:
            self.template unsafe_get<unsigned short int>() += other;
            break;

        case token::code::signed_integer:
            self.template unsafe_get<signed int>() += other;
            break;

        case token::code::unsigned_integer:
            self.template unsafe_get<unsigned int>() += other;
            break;

        case token::code::signed_long_integer:
            self.template unsafe_get<signed long int>() += other;
            break;

        case token::code::unsigned_long_integer:
            self.template unsafe_get<unsigned long int>() += other;
            break;

        case token::code::signed_long_long_integer:
            self.template unsafe_get<signed long long int>() += other;
            break;

        case token::code::unsigned_long_long_integer:
            self.template unsafe_get<unsigned long long int>() += other;
            break;

        case token::code::float_number:
            self.template unsafe_get<float>() += other;
            break;

        case token::code::double_number:
            self.template unsafe_get<double>() += other;
            break;

        case token::code::long_double_number:
            self.template unsafe_get<long double>() += other;
            break;

        case token::code::array:
            self.template unsafe_get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Unsigned integer

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_integer<U>::value &&
                            std::is_unsigned<U>::value>::type>
{
    using type = U;
    using category_type = int;
    using variable_type = basic_variable<CharT>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>();

        case token::code::signed_char:
            return self.template unsafe_get<signed char>();

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>();

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>();

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>();

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>();

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>();

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>();

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>();

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>();

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>();

        case token::code::float_number:
            return self.template unsafe_get<float>();

        case token::code::double_number:
            return self.template unsafe_get<double>();

        case token::code::long_double_number:
            return self.template unsafe_get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>() == other;

        case token::code::signed_char:
            return static_cast<unsigned char>(self.template unsafe_get<signed char>()) == other;
        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>() == other;

        case token::code::signed_short_integer:
            return static_cast<unsigned short int>(self.template unsafe_get<signed short int>()) == other;
        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>() == other;

        case token::code::signed_integer:
            return static_cast<unsigned int>(self.template unsafe_get<signed int>()) == other;
        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>() == other;

        case token::code::signed_long_integer:
            return static_cast<unsigned long int>(self.template unsafe_get<signed long int>()) == other;
        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>() == other;

        case token::code::signed_long_long_integer:
            return static_cast<unsigned long long int>(self.template unsafe_get<signed long long int>()) == other;
        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>() == other;

        case token::code::float_number:
            return self.template unsafe_get<float>() == other;

        case token::code::double_number:
            return self.template unsafe_get<double>() == other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::null:
            return true;

        case token::code::boolean:
            return self.template unsafe_get<bool>() < other;

        case token::code::signed_char:
            return static_cast<unsigned char>(self.template unsafe_get<signed char>()) < other;
        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>() < other;

        case token::code::signed_short_integer:
            return static_cast<unsigned short int>(self.template unsafe_get<signed short int>()) < other;
        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>() < other;

        case token::code::signed_integer:
            return static_cast<unsigned int>(self.template unsafe_get<signed int>()) < other;
        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>() < other;

        case token::code::signed_long_integer:
            return static_cast<unsigned long int>(self.template unsafe_get<signed long int>()) < other;
        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>() < other;

        case token::code::signed_long_long_integer:
            return static_cast<unsigned long long int>(self.template unsafe_get<signed long long int>()) < other;
        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>() < other;

        case token::code::float_number:
            return self.template unsafe_get<float>() < other;

        case token::code::double_number:
            return self.template unsafe_get<double>() < other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable& self, const U& other)
    {
        switch (self.code())
        {
        case token::code::null:
            self.storage = other; // Overwrite null
            break;

        case token::code::boolean:
            self.template unsafe_get<bool>() += other;
            break;

        case token::code::signed_char:
            self.template unsafe_get<signed char>() += other;
            break;

        case token::code::unsigned_char:
            self.template unsafe_get<unsigned char>() += other;
            break;

        case token::code::signed_short_integer:
            self.template unsafe_get<signed short int>() += other;
            break;

        case token::code::unsigned_short_integer:
            self.template unsafe_get<unsigned short int>() += other;
            break;

        case token::code::signed_integer:
            self.template unsafe_get<signed int>() += other;
            break;

        case token::code::unsigned_integer:
            self.template unsafe_get<unsigned int>() += other;
            break;

        case token::code::signed_long_integer:
            self.template unsafe_get<signed long int>() += other;
            break;

        case token::code::unsigned_long_integer:
            self.template unsafe_get<unsigned long int>() += other;
            break;

        case token::code::signed_long_long_integer:
            self.template unsafe_get<signed long long int>() += other;
            break;

        case token::code::unsigned_long_long_integer:
            self.template unsafe_get<unsigned long long int>() += other;
            break;

        case token::code::float_number:
            self.template unsafe_get<float>() += other;
            break;

        case token::code::double_number:
            self.template unsafe_get<double>() += other;
            break;

        case token::code::long_double_number:
            self.template unsafe_get<long double>() += other;
            break;

        case token::code::array:
            self.template unsafe_get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Floating-point

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_number<U>::value>::type>
{
    using type = U;
    using category_type = float;
    using variable_type = basic_variable<CharT>;

    using array_type = typename variable_type::array_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>();

        case token::code::signed_char:
            return self.template unsafe_get<signed char>();

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>();

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>();

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>();

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>();

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>();

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>();

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>();

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>();

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>();

        case token::code::float_number:
            return self.template unsafe_get<float>();

        case token::code::double_number:
            return self.template unsafe_get<double>();

        case token::code::long_double_number:
            return self.template unsafe_get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::boolean:
            return self.template unsafe_get<bool>() == other;

        case token::code::signed_char:
            return self.template unsafe_get<signed char>() == other;

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>() == other;

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>() == other;

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>() == other;

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>() == other;

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>() == other;

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>() == other;

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>() == other;

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>() == other;

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>() == other;

        case token::code::float_number:
            return self.template unsafe_get<float>() == other;

        case token::code::double_number:
            return self.template unsafe_get<double>() == other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::null:
            return true;

        case token::code::boolean:
            return self.template unsafe_get<bool>() < other;

        case token::code::signed_char:
            return self.template unsafe_get<signed char>() < other;

        case token::code::unsigned_char:
            return self.template unsafe_get<unsigned char>() < other;

        case token::code::signed_short_integer:
            return self.template unsafe_get<signed short int>() < other;

        case token::code::unsigned_short_integer:
            return self.template unsafe_get<unsigned short int>() < other;

        case token::code::signed_integer:
            return self.template unsafe_get<signed int>() < other;

        case token::code::unsigned_integer:
            return self.template unsafe_get<unsigned int>() < other;

        case token::code::signed_long_integer:
            return self.template unsafe_get<signed long int>() < other;

        case token::code::unsigned_long_integer:
            return self.template unsafe_get<unsigned long int>() < other;

        case token::code::signed_long_long_integer:
            return self.template unsafe_get<signed long long int>() < other;

        case token::code::unsigned_long_long_integer:
            return self.template unsafe_get<unsigned long long int>() < other;

        case token::code::float_number:
            return self.template unsafe_get<float>() < other;

        case token::code::double_number:
            return self.template unsafe_get<double>() < other;

        case token::code::long_double_number:
            return self.template unsafe_get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case token::code::null:
            self.storage = other; // Overwrite null
            break;

        case token::code::boolean:
            self.template unsafe_get<bool>() += other;
            break;

        case token::code::signed_char:
            self.template unsafe_get<signed char>() += other;
            break;

        case token::code::unsigned_char:
            self.template unsafe_get<unsigned char>() += other;
            break;

        case token::code::signed_short_integer:
            self.template unsafe_get<signed short int>() += other;
            break;

        case token::code::unsigned_short_integer:
            self.template unsafe_get<unsigned short int>() += other;
            break;

        case token::code::signed_integer:
            self.template unsafe_get<signed int>() += other;
            break;

        case token::code::unsigned_integer:
            self.template unsafe_get<unsigned int>() += other;
            break;

        case token::code::signed_long_integer:
            self.template unsafe_get<signed long int>() += other;
            break;

        case token::code::unsigned_long_integer:
            self.template unsafe_get<unsigned long int>() += other;
            break;

        case token::code::signed_long_long_integer:
            self.template unsafe_get<signed long long int>() += other;
            break;

        case token::code::unsigned_long_long_integer:
            self.template unsafe_get<unsigned long long int>() += other;
            break;

        case token::code::float_number:
            self.template unsafe_get<float>() += other;
            break;

        case token::code::double_number:
            self.template unsafe_get<double>() += other;
            break;

        case token::code::long_double_number:
            self.template unsafe_get<long double>() += other;
            break;

        case token::code::array:
            self.template unsafe_get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// String

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_string<CharT, U>::value>::type>
{
    using variable_type = basic_variable<CharT>;
    using type = typename variable_type::string_type;
    using category_type = type;

    using string_type = typename variable_type::string_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::string:
            return self.template unsafe_get<string_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::string:
            return self.template unsafe_get<string_type>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::string:
            return self.template unsafe_get<string_type>() < other;

        case token::code::array:
        case token::code::map:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case token::code::null:
            self.storage = other; // Overwrite null
            break;

        case token::code::string:
            self.template unsafe_get<string_type>() += other;
            break;

        case token::code::array:
            self.template unsafe_get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Array

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_array<CharT, U>::value>::type>
{
    using variable_type = basic_variable<CharT>;
    using type = typename variable_type::array_type;
    using category_type = type;

    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static U convert(const variable& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::array:
            return self.template unsafe_get<array_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::array:
            {
                const auto& array = self.template unsafe_get<array_type>();
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

    static bool less(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::array:
            {
                const auto& array = self.template unsafe_get<array_type>();
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

        case token::code::map:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.code())
        {
        case token::code::null:
            self.storage = other; // Overwrite null
            break;

        case token::code::array:
            {
                auto& array = self.template unsafe_get<array_type>();
                array.insert(array.end(), other.begin(), other.end());
            }
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Map

template <typename CharT, typename U>
struct overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<detail::is_map<CharT, U>::value>::type>
{
    using variable_type = basic_variable<CharT>;
    using type = typename variable_type::map_type;
    using category_type = type;

    using map_type = typename variable_type::map_type;

    static U convert(const variable_type& self, std::error_code& error) noexcept
    {
        switch (self.code())
        {
        case token::code::map:
            return self.template unsafe_get<map_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::map:
            {
                const auto& map = self.template unsafe_get<map_type>();
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

    static bool less(const variable_type& self, const U& other) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (self.code())
        {
        case token::code::map:
            {
                const auto& map = self.template unsafe_get<map_type>();
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
        case token::code::null:
            self.storage = other; // Overwrite null
            break;

        case token::code::map:
            {
                auto& map = self.template unsafe_get<map_type>();
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
    static bool equal(const T& lhs, const U& rhs)
    {
        // This function is called by dynamic::operator== so we must avoid
        // infinite recursion.

        using std::operator==;
        return operator==(lhs, rhs);
    }

    static bool less(const T& lhs, const U& rhs)
    {
        // See comment in equal() in this struct.

        using std::operator<;
        return operator<(lhs, rhs);
    }
};

template <typename T, typename U>
struct operator_overloader<
    T,
    U,
    typename std::enable_if<core::detail::is_iterator<T>::value>::type>
{
    static bool equal(const T& lhs, const U& rhs)
    {
        // This function is called by dynamic::operator== when T is an
        // iterator.
        //
        // basic_variable<CharT>::iterator_base<T> cannot be matched via
        // SFINAE below (due to being a non-deduced context), so instead
        // lhs.operator(rhs) is called in the general case.
        //
        // Notice: operator==(lhs, rhs) cannot be used because it uses
        // argument dependent lookup which will find dynamic::operator==
        // which got us here in the first place. That would cause an
        // infinite recursion.

        return lhs.operator==(rhs);
    }

    static bool less(const T& lhs, const U& rhs)
    {
        // See comment for equal() in this struct.

        return lhs.operator<(rhs);
    }
};

template <typename CharT, typename U>
struct operator_overloader<
    basic_variable<CharT>,
    U,
    typename std::enable_if<!std::is_same<U, basic_variable<CharT> >::value>::type>
{
    using variable_type = basic_variable<CharT>;
    using string_type = typename variable_type::string_type;

    template <typename T = U>
    static typename std::enable_if<!std::is_same<typename std::decay<T>::type,
                                                 const CharT *>::value,
                                   bool>::type
    equal(const variable_type& lhs, const T& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, T>::equal(lhs, rhs);
    }

    static bool equal(const variable_type& lhs, const CharT* rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, string_type>::equal(lhs, string_type(rhs));
    }

    template <typename T = U>
    static typename std::enable_if<!std::is_same<typename std::decay<T>::type,
                                                 const CharT *>::value,
                                   bool>::type
    less(const variable_type& lhs, const T& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, T>::less(lhs, rhs);
    }

    static bool less(const variable_type& lhs, const CharT* rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        return detail::template overloader<variable_type, string_type>::less(lhs, string_type(rhs));
    }
};

template <typename T, typename CharT>
struct operator_overloader<
    T,
    basic_variable<CharT>,
    typename std::enable_if<!std::is_same<T, basic_variable<CharT> >::value>::type>
{
    using variable_type = basic_variable<CharT>;

    static bool equal(const T& lhs, const variable_type& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        return operator_overloader<variable_type, variable_type>::equal(variable_type(lhs), rhs);
    }

    static bool less(const T& lhs, const variable_type& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        return operator_overloader<variable_type, variable_type>::less(variable_type(lhs), rhs);
    }
};

template <typename CharT>
struct operator_overloader<
    basic_variable<CharT>,
    basic_variable<core::detail::meta::identity_t<CharT>>>
{
    using variable_type = basic_variable<CharT>;
    using string_type = typename variable_type::string_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static bool equal(const variable_type& lhs,
                      const variable_type& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (rhs.code())
        {
        case token::code::null:
            return detail::template overloader<variable_type, nullable>::
                equal(lhs, rhs.template value<nullable>());

        case token::code::boolean:
            return detail::template overloader<variable_type, bool>::
                equal(lhs, rhs.template unsafe_get<bool>());

        case token::code::signed_char:
            return detail::template overloader<variable_type, signed char>::
                equal(lhs, rhs.template unsafe_get<signed char>());

        case token::code::unsigned_char:
            return detail::template overloader<variable_type, unsigned char>::
                equal(lhs, rhs.template unsafe_get<unsigned char>());

        case token::code::signed_short_integer:
            return detail::template overloader<variable_type, signed short int>::
                equal(lhs, rhs.template unsafe_get<signed short int>());

        case token::code::unsigned_short_integer:
            return detail::template overloader<variable_type, unsigned short int>::
                equal(lhs, rhs.template unsafe_get<unsigned short int>());

        case token::code::signed_integer:
            return detail::template overloader<variable_type, signed int>::
                equal(lhs, rhs.template unsafe_get<signed int>());

        case token::code::unsigned_integer:
            return detail::template overloader<variable_type, unsigned int>::
                equal(lhs, rhs.template unsafe_get<unsigned int>());

        case token::code::signed_long_integer:
            return detail::template overloader<variable_type, signed long int>::
                equal(lhs, rhs.template unsafe_get<signed long int>());

        case token::code::unsigned_long_integer:
            return detail::template overloader<variable_type, unsigned long int>::
                equal(lhs, rhs.template unsafe_get<unsigned long int>());

        case token::code::signed_long_long_integer:
            return detail::template overloader<variable_type, signed long long int>::
                equal(lhs, rhs.template unsafe_get<signed long long int>());

        case token::code::unsigned_long_long_integer:
            return detail::template overloader<variable_type, unsigned long long int>::
                equal(lhs, rhs.template unsafe_get<unsigned long long int>());

        case token::code::float_number:
            return detail::template overloader<variable_type, float>::
                equal(lhs, rhs.template unsafe_get<float>());

        case token::code::double_number:
            return detail::template overloader<variable_type, double>::
                equal(lhs, rhs.template unsafe_get<double>());

        case token::code::long_double_number:
            return detail::template overloader<variable_type, long double>::
                equal(lhs, rhs.template unsafe_get<long double>());

        case token::code::string:
            return detail::template overloader<variable_type, string_type>::
                equal(lhs, rhs.template unsafe_get<string_type>());

        case token::code::array:
            return detail::template overloader<variable_type, array_type>::
                equal(lhs, rhs.template unsafe_get<array_type>());

        case token::code::map:
            return detail::template overloader<variable_type, map_type>::
                equal(lhs, rhs.template unsafe_get<map_type>());
        }
        return false;
    }

    static bool less(const variable_type& lhs,
                     const variable_type& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
    {
        switch (rhs.code())
        {
        case token::code::null:
            return detail::template overloader<variable_type, nullable>::
                less(lhs, rhs.template value<nullable>());

        case token::code::boolean:
            return detail::template overloader<variable_type, bool>::
                less(lhs, rhs.template unsafe_get<bool>());

        case token::code::signed_char:
            return detail::template overloader<variable_type, signed char>::
                less(lhs, rhs.template unsafe_get<signed char>());

        case token::code::unsigned_char:
            return detail::template overloader<variable_type, unsigned char>::
                less(lhs, rhs.template unsafe_get<unsigned char>());

        case token::code::signed_short_integer:
            return detail::template overloader<variable_type, signed short int>::
                less(lhs, rhs.template unsafe_get<signed short int>());

        case token::code::unsigned_short_integer:
            return detail::template overloader<variable_type, unsigned short int>::
                less(lhs, rhs.template unsafe_get<unsigned short int>());

        case token::code::signed_integer:
            return detail::template overloader<variable_type, signed int>::
                less(lhs, rhs.template unsafe_get<signed int>());

        case token::code::unsigned_integer:
            return detail::template overloader<variable_type, unsigned int>::
                less(lhs, rhs.template unsafe_get<unsigned int>());

        case token::code::signed_long_integer:
            return detail::template overloader<variable_type, signed long int>::
                less(lhs, rhs.template unsafe_get<signed long int>());

        case token::code::unsigned_long_integer:
            return detail::template overloader<variable_type, unsigned long int>::
                less(lhs, rhs.template unsafe_get<unsigned long int>());

        case token::code::signed_long_long_integer:
            return detail::template overloader<variable_type, signed long long int>::
                less(lhs, rhs.template unsafe_get<signed long long int>());

        case token::code::unsigned_long_long_integer:
            return detail::template overloader<variable_type, unsigned long long int>::
                less(lhs, rhs.template unsafe_get<unsigned long long int>());

        case token::code::float_number:
            return detail::template overloader<variable_type, float>::
                less(lhs, rhs.template unsafe_get<float>());

        case token::code::double_number:
            return detail::template overloader<variable_type, double>::
                less(lhs, rhs.template unsafe_get<double>());

        case token::code::long_double_number:
            return detail::template overloader<variable_type, long double>::
                less(lhs, rhs.template unsafe_get<long double>());

        case token::code::string:
            return detail::template overloader<variable_type, string_type>::
                less(lhs, rhs.template unsafe_get<string_type>());

        case token::code::array:
            return detail::template overloader<variable_type, array_type>::
                less(lhs, rhs.template unsafe_get<array_type>());

        case token::code::map:
            return detail::template overloader<variable_type, map_type>::
                less(lhs, rhs.template unsafe_get<map_type>());
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

template <typename C, typename T, typename = void>
struct same_overloader
{
    static bool same(std::size_t which) noexcept
    {
        return which == basic_variable<C>::template traits<T>::value;
    }
};

template <typename C, typename T>
struct same_overloader<
    C,
    T,
    typename std::enable_if<std::is_const<T>::value ||
                            std::is_volatile<T>::value ||
                            std::is_reference<T>::value>::type>
{
    static bool same(std::size_t) noexcept
    {
        return false;
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// variable::iterator_base
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename Derived, typename T>
basic_variable<CharT>::iterator_base<Derived, T>::iterator_base()
    : scope(nullptr),
      current(pointer(nullptr))
{
}

template <typename CharT>
template <typename Derived, typename T>
basic_variable<CharT>::iterator_base<Derived, T>::iterator_base(const iterator_base& other)
    : scope(other.scope),
      current(other.current)
{
}

template <typename CharT>
template <typename Derived, typename T>
basic_variable<CharT>::iterator_base<Derived, T>::iterator_base(iterator_base&& other)
    : scope(std::move(other.scope)),
      current(std::move(other.current))
{
}

template <typename CharT>
template <typename Derived, typename T>
basic_variable<CharT>::iterator_base<Derived, T>::iterator_base(pointer p,
                                                                bool initialize)
    : scope(p),
      current(pointer(nullptr))
{
    switch (scope->symbol())
    {
    case token::symbol::null:
        current = pointer(nullptr);
        break;

    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        if (initialize)
            current = p;
        break;

    case token::symbol::array:
        if (initialize)
            current = p->template unsafe_get<array_type>().begin();
        else
            current = p->template unsafe_get<array_type>().end();
        break;

    case token::symbol::map:
        if (initialize)
            current = p->template unsafe_get<map_type>().begin();
        else
            current = p->template unsafe_get<map_type>().end();
        break;
    }
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::operator= (const Derived& other) -> Derived&
{
    scope = other.scope;
    current = other.current;
    return *static_cast<Derived*>(this);
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::operator= (Derived&& other) -> Derived&
{
    scope = std::move(other.scope);
    current = std::move(other.current);
    return *static_cast<Derived*>(this);
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::operator++ () -> Derived&
{
    assert(scope);

    switch (scope->symbol())
    {
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        current = pointer(nullptr);
        break;

    case token::symbol::array:
        ++current.template get<array_iterator>();
        break;

    case token::symbol::map:
        ++current.template get<map_iterator>();
        break;
    }
    return *static_cast<Derived*>(this);
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::operator++ (int) -> Derived
{
    assert(scope);

    Derived result = *static_cast<Derived*>(this);
    ++(*this);
    return result;
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::key() const -> const_reference
{
    assert(scope);

    switch (scope->symbol())
    {
    case token::symbol::map:
        return const_cast<const_reference>(current.template get<map_iterator>()->first);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::value() -> reference
{
    assert(scope);

    switch (scope->symbol())
    {
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return *current.template get<pointer>();

    case token::symbol::array:
        return *current.template get<array_iterator>();

    case token::symbol::map:
        return current.template get<map_iterator>()->second;
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::value() const -> const_reference
{
    assert(scope);

    switch (scope->symbol())
    {
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return *current.template get<pointer>();

    case token::symbol::array:
        return *current.template get<array_iterator>();

    case token::symbol::map:
        return current.template get<map_iterator>()->second;
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
template <typename Derived, typename T>
auto basic_variable<CharT>::iterator_base<Derived, T>::operator-> () -> pointer
{
    assert(scope);

    switch (scope->symbol())
    {
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return current.template get<pointer>();

    case token::symbol::array:
        return &*current.template get<array_iterator>();

    case token::symbol::map:
        return &current.template get<map_iterator>()->second;
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
template <typename Derived, typename T>
bool basic_variable<CharT>::iterator_base<Derived, T>::operator== (const Derived& other) const
{
    if (!scope)
        return !other.scope;
    if (!other.scope)
        return false;

    assert(scope->code() == other.scope->code());

    switch (scope->symbol())
    {
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return current.template get<pointer>() == other.current.template get<pointer>();

    case token::symbol::array:
        return current.template get<array_iterator>() == other.current.template get<array_iterator>();

    case token::symbol::map:
        return current.template get<map_iterator>() == other.current.template get<map_iterator>();
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
template <typename Derived, typename T>
bool basic_variable<CharT>::iterator_base<Derived, T>::operator!= (const Derived& other) const
{
    return !(*this == other);
}

//-----------------------------------------------------------------------------
// variable::iterator
//-----------------------------------------------------------------------------

template <typename CharT>
basic_variable<CharT>::iterator::iterator()
    : super()
{
}

template <typename CharT>
basic_variable<CharT>::iterator::iterator(const iterator& other)
    : super(other)
{
}

template <typename CharT>
basic_variable<CharT>::iterator::iterator(iterator&& other)
    : super(std::move(other))
{
}

template <typename CharT>
basic_variable<CharT>::iterator::iterator(pointer p, bool e)
    : super(p, e)
{
}

template <typename CharT>
basic_variable<CharT>::iterator::iterator(const const_iterator& other)
    : super(const_cast<pointer>(other.scope))
{
    switch (other.current.which())
    {
    case super::small_union::template index<pointer>::value:
        super::current = other.current.template get<pointer>();
        break;
    case super::small_union::template index<typename super::array_iterator>::value:
        super::current = other.current.template get<typename super::array_iterator>();
        break;
    case super::small_union::template index<typename super::map_iterator>::value:
        super::current = other.current.template get<typename super::map_iterator>();
        break;
    }
}

template <typename CharT>
auto basic_variable<CharT>::iterator::operator= (const iterator& other) -> iterator&
{
    return super::operator=(other);
}

template <typename CharT>
auto basic_variable<CharT>::iterator::operator= (iterator&& other) -> iterator&
{
    return super::operator=(std::forward<iterator&&>(other));
}

//-----------------------------------------------------------------------------
// variable::const_iterator
//-----------------------------------------------------------------------------

template <typename CharT>
basic_variable<CharT>::const_iterator::const_iterator()
    : super()
{
}

template <typename CharT>
basic_variable<CharT>::const_iterator::const_iterator(const const_iterator& other)
    : super(other)
{
}

template <typename CharT>
basic_variable<CharT>::const_iterator::const_iterator(const_iterator&& other)
    : super(std::move(other))
{
}

template <typename CharT>
basic_variable<CharT>::const_iterator::const_iterator(pointer p, bool e)
    : super(p, e)
{
}

template <typename CharT>
basic_variable<CharT>::const_iterator::const_iterator(const iterator& other)
    : super(other.scope)
{
    switch (other.current.which())
    {
    case super::small_union::template index<pointer>::value:
        super::current = other.current.template get<pointer>();
        break;
    case super::small_union::template index<typename super::array_iterator>::value:
        super::current = other.current.template get<typename super::array_iterator>();
        break;
    case super::small_union::template index<typename super::map_iterator>::value:
        super::current = other.current.template get<typename super::map_iterator>();
        break;
    }
}

//-----------------------------------------------------------------------------
// variable::key_iterator
//-----------------------------------------------------------------------------

template <typename CharT>
basic_variable<CharT>::key_iterator::key_iterator(const key_iterator& other)
    : super(other),
      index(other.index)
{
}

template <typename CharT>
basic_variable<CharT>::key_iterator::key_iterator(key_iterator&& other)
{
    super::scope = std::move(other.scope);
    super::current = std::move(other.current);
    index = std::move(other.index);
}

template <typename CharT>
basic_variable<CharT>::key_iterator::key_iterator(pointer p, bool e)
    : super(p, e),
      index(0)
{
}

template <typename CharT>
auto basic_variable<CharT>::key_iterator::operator= (const key_iterator& other) -> key_iterator&
{
    return super::operator=(other);
}

template <typename CharT>
auto basic_variable<CharT>::key_iterator::operator= (key_iterator&& other) -> key_iterator&
{
    return super::operator=(std::forward<key_iterator>(other));
}

template <typename CharT>
auto basic_variable<CharT>::key_iterator::key() const -> const_reference
{
    assert(super::scope);

    switch (super::scope->symbol())
    {
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
    case token::symbol::array:
        return index;

    case token::symbol::map:
        return super::key();
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
auto basic_variable<CharT>::key_iterator::operator++ () -> key_iterator&
{
    assert(super::scope);

    switch (super::scope->symbol())
    {
    case token::symbol::null:
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
    case token::symbol::array:
        index += 1;
        break;

    case token::symbol::map:
        break;
    }
    return super::operator++();
}

//-----------------------------------------------------------------------------
// storage visitors
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T>
struct basic_variable<CharT>::similar_visitor
{
    template <typename Which>
    static bool call(const storage_type&)
    {
        using variable_type = basic_variable<CharT>;
        using lhs_type = typename detail::overloader<variable_type, T>::category_type;
        using rhs_type = typename detail::overloader<variable_type, Which>::category_type;
        return std::is_same<lhs_type, rhs_type>::value;
    }
};

//-----------------------------------------------------------------------------
// variable
//-----------------------------------------------------------------------------

template <typename CharT>
basic_variable<CharT>::basic_variable()
    : storage(null)
{
}

template <typename CharT>
basic_variable<CharT>::basic_variable(const basic_variable& other)
    : storage(null)
{
    switch (other.code())
    {
    case token::code::null:
        storage = null;
        break;
    case token::code::boolean:
        storage = other.unsafe_get<bool>();
        break;
    case token::code::signed_char:
        storage = other.unsafe_get<signed char>();
        break;
    case token::code::unsigned_char:
        storage = other.unsafe_get<unsigned char>();
        break;
    case token::code::signed_short_integer:
        storage = other.unsafe_get<signed short int>();
        break;
    case token::code::unsigned_short_integer:
        storage = other.unsafe_get<unsigned short int>();
        break;
    case token::code::signed_integer:
        storage = other.unsafe_get<signed int>();
        break;
    case token::code::unsigned_integer:
        storage = other.unsafe_get<unsigned int>();
        break;
    case token::code::signed_long_integer:
        storage = other.unsafe_get<signed long int>();
        break;
    case token::code::unsigned_long_integer:
        storage = other.unsafe_get<unsigned long int>();
        break;
    case token::code::signed_long_long_integer:
        storage = other.unsafe_get<signed long long int>();
        break;
    case token::code::unsigned_long_long_integer:
        storage = other.unsafe_get<unsigned long long int>();
        break;
    case token::code::float_number:
        storage = other.unsafe_get<float>();
        break;
    case token::code::double_number:
        storage = other.unsafe_get<double>();
        break;
    case token::code::long_double_number:
        storage = other.unsafe_get<long double>();
        break;
    case token::code::string:
        storage = other.unsafe_get<string_type>();
        break;
    case token::code::array:
        storage = other.unsafe_get<array_type>();
        break;
    case token::code::map:
        storage = other.unsafe_get<map_type>();
        break;
    }
}

template <typename CharT>
basic_variable<CharT>::basic_variable(basic_variable&& other)
    : storage(null)
{
    switch (other.code())
    {
    case token::code::null:
        storage = null;
        break;
    case token::code::boolean:
        storage = std::move(other.unsafe_get<bool>());
        break;
    case token::code::signed_char:
        storage = std::move(other.unsafe_get<signed char>());
        break;
    case token::code::unsigned_char:
        storage = std::move(other.unsafe_get<unsigned char>());
        break;
    case token::code::signed_short_integer:
        storage = std::move(other.unsafe_get<signed short int>());
        break;
    case token::code::unsigned_short_integer:
        storage = std::move(other.unsafe_get<unsigned short int>());
        break;
    case token::code::signed_integer:
        storage = std::move(other.unsafe_get<signed int>());
        break;
    case token::code::unsigned_integer:
        storage = std::move(other.unsafe_get<unsigned int>());
        break;
    case token::code::signed_long_integer:
        storage = std::move(other.unsafe_get<signed long int>());
        break;
    case token::code::unsigned_long_integer:
        storage = std::move(other.unsafe_get<unsigned long int>());
        break;
    case token::code::signed_long_long_integer:
        storage = std::move(other.unsafe_get<signed long long int>());
        break;
    case token::code::unsigned_long_long_integer:
        storage = std::move(other.unsafe_get<unsigned long long int>());
        break;
    case token::code::float_number:
        storage = std::move(other.unsafe_get<float>());
        break;
    case token::code::double_number:
        storage = std::move(other.unsafe_get<double>());
        break;
    case token::code::long_double_number:
        storage = std::move(other.unsafe_get<long double>());
        break;
    case token::code::string:
        storage = std::move(other.unsafe_get<string_type>());
        break;
    case token::code::array:
        storage = std::move(other.unsafe_get<array_type>());
        break;
    case token::code::map:
        storage = std::move(other.unsafe_get<map_type>());
        break;
    }
}

template <typename CharT>
template <typename T>
basic_variable<CharT>::basic_variable(T value)
    : storage(typename detail::overloader<value_type, typename std::decay<T>::type>::type(std::move(value)))
{
}

template <typename CharT>
basic_variable<CharT>::basic_variable(const std::initializer_list<value_type>& init)
    : storage(null)
{
    if (init.size() == 0)
    {
        storage = array_type{};
        return;
    }

    for (const auto& i : init)
    {
        if (i.is<array>() && (i.size() == 2))
            continue;

        storage = array_type(init);
        return;
    }

    storage = map_type{};
    auto& map = unsafe_get<map_type>();
    for (const auto& i : init)
    {
        auto& array = i.unsafe_get<array_type>();
        map[array[0]] = array[1];
    }
}

template <typename CharT>
basic_variable<CharT>::basic_variable(const nullable&)
    : storage(null)
{
}

template <typename CharT>
basic_variable<CharT>::basic_variable(const CharT *value)
    : storage(string_type(value))
{
}

template <typename CharT>
auto basic_variable<CharT>::operator= (const basic_variable& other) -> basic_variable&
{
    switch (other.code())
    {
    case token::code::null:
        storage = null;
        break;
    case token::code::boolean:
        storage = other.unsafe_get<bool>();
        break;
    case token::code::signed_char:
        storage = other.unsafe_get<signed char>();
        break;
    case token::code::unsigned_char:
        storage = other.unsafe_get<unsigned char>();
        break;
    case token::code::signed_short_integer:
        storage = other.unsafe_get<signed short int>();
        break;
    case token::code::unsigned_short_integer:
        storage = other.unsafe_get<unsigned short int>();
        break;
    case token::code::signed_integer:
        storage = other.unsafe_get<signed int>();
        break;
    case token::code::unsigned_integer:
        storage = other.unsafe_get<unsigned int>();
        break;
    case token::code::signed_long_integer:
        storage = other.unsafe_get<signed long int>();
        break;
    case token::code::unsigned_long_integer:
        storage = other.unsafe_get<unsigned long int>();
        break;
    case token::code::signed_long_long_integer:
        storage = other.unsafe_get<signed long long int>();
        break;
    case token::code::unsigned_long_long_integer:
        storage = other.unsafe_get<unsigned long long int>();
        break;
    case token::code::float_number:
        storage = other.unsafe_get<float>();
        break;
    case token::code::double_number:
        storage = other.unsafe_get<double>();
        break;
    case token::code::long_double_number:
        storage = other.unsafe_get<long double>();
        break;
    case token::code::string:
        storage = other.unsafe_get<string_type>();
        break;
    case token::code::array:
        storage = other.unsafe_get<array_type>();
        break;
    case token::code::map:
        storage = other.unsafe_get<map_type>();
        break;
    }
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator= (basic_variable&& other) -> basic_variable&
{
    switch (other.code())
    {
    case token::code::null:
        storage = null;
        break;
    case token::code::boolean:
        storage = std::move(other.unsafe_get<bool>());
        break;
    case token::code::signed_char:
        storage = std::move(other.unsafe_get<signed char>());
        break;
    case token::code::unsigned_char:
        storage = std::move(other.unsafe_get<unsigned char>());
        break;
    case token::code::signed_short_integer:
        storage = std::move(other.unsafe_get<signed short int>());
        break;
    case token::code::unsigned_short_integer:
        storage = std::move(other.unsafe_get<unsigned short int>());
        break;
    case token::code::signed_integer:
        storage = std::move(other.unsafe_get<signed int>());
        break;
    case token::code::unsigned_integer:
        storage = std::move(other.unsafe_get<unsigned int>());
        break;
    case token::code::signed_long_integer:
        storage = std::move(other.unsafe_get<signed long int>());
        break;
    case token::code::unsigned_long_integer:
        storage = std::move(other.unsafe_get<unsigned long int>());
        break;
    case token::code::signed_long_long_integer:
        storage = std::move(other.unsafe_get<signed long long int>());
        break;
    case token::code::unsigned_long_long_integer:
        storage = std::move(other.unsafe_get<unsigned long long int>());
        break;
    case token::code::float_number:
        storage = std::move(other.unsafe_get<float>());
        break;
    case token::code::double_number:
        storage = std::move(other.unsafe_get<double>());
        break;
    case token::code::long_double_number:
        storage = std::move(other.unsafe_get<long double>());
        break;
    case token::code::string:
        storage = std::move(other.unsafe_get<string_type>());
        break;
    case token::code::array:
        storage = std::move(other.unsafe_get<array_type>());
        break;
    case token::code::map:
        storage = std::move(other.unsafe_get<map_type>());
        break;
    }
    return *this;
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::operator= (T value) -> basic_variable&
{
    storage = typename detail::overloader<value_type, T>::type{std::move(value)};
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator= (nullable) -> basic_variable&
{
    storage = null;
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator= (const CharT *value) -> basic_variable&
{
    storage = string_type{value};
    return *this;
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::operator+= (const T& other) -> basic_variable&
{
    detail::overloader<value_type, T>::append(*this, other);
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator+= (const basic_variable& other) -> basic_variable&
{
    switch (other.code())
    {
    case token::code::null:
        detail::overloader<value_type, nullable>::
            append(*this, other.unsafe_get<nullable>());
        break;
    case token::code::boolean:
        detail::overloader<value_type, bool>::
            append(*this, other.unsafe_get<bool>());
        break;
    case token::code::signed_char:
        detail::overloader<value_type, signed char>::
            append(*this, other.unsafe_get<signed char>());
        break;
    case token::code::unsigned_char:
        detail::overloader<value_type, unsigned char>::
            append(*this, other.unsafe_get<unsigned char>());
        break;
    case token::code::signed_short_integer:
        detail::overloader<value_type, signed short int>::
            append(*this, other.unsafe_get<signed short int>());
        break;
    case token::code::unsigned_short_integer:
        detail::overloader<value_type, unsigned short int>::
            append(*this, other.unsafe_get<unsigned short int>());
        break;
    case token::code::signed_integer:
        detail::overloader<value_type, signed int>::
            append(*this, other.unsafe_get<signed int>());
        break;
    case token::code::unsigned_integer:
        detail::overloader<value_type, unsigned int>::
            append(*this, other.unsafe_get<unsigned int>());
        break;
    case token::code::signed_long_integer:
        detail::overloader<value_type, signed long int>::
            append(*this, other.unsafe_get<signed long int>());
        break;
    case token::code::unsigned_long_integer:
        detail::overloader<value_type, unsigned long int>::
            append(*this, other.unsafe_get<unsigned long int>());
        break;
    case token::code::signed_long_long_integer:
        detail::overloader<value_type, signed long long int>::
            append(*this, other.unsafe_get<signed long long int>());
        break;
    case token::code::unsigned_long_long_integer:
        detail::overloader<value_type, unsigned long long int>::
            append(*this, other.unsafe_get<unsigned long long int>());
        break;
    case token::code::float_number:
        detail::overloader<value_type, float>::
            append(*this, other.unsafe_get<float>());
        break;
    case token::code::double_number:
        detail::overloader<value_type, double>::
            append(*this, other.unsafe_get<double>());
        break;
    case token::code::long_double_number:
        detail::overloader<value_type, long double>::
            append(*this, other.unsafe_get<long double>());
        break;
    case token::code::string:
        detail::overloader<value_type, string_type>::
            append(*this, other.unsafe_get<string_type>());
        break;
    case token::code::array:
        detail::overloader<value_type, array_type>::
            append(*this, other.unsafe_get<array_type>());
        break;
    case token::code::map:
        detail::overloader<value_type, map_type>::
            append(*this, other.unsafe_get<map_type>());
        break;
    }
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator+= (const CharT *other) -> basic_variable&
{
    detail::overloader<value_type, string_type>::append(*this, other);
    return *this;
}

template <typename T, typename U>
auto operator+ (const basic_variable<T>& lhs, const U& rhs) -> basic_variable<T>
{
    basic_variable<T> result(lhs);
    result += rhs;
    return result;
}

template <typename T>
auto operator+ (nullable,
                const basic_variable<T>& rhs) -> basic_variable<T>
{
    basic_variable<T> result;
    result += rhs;
    return result;
}

template <typename CharT>
template <typename R>
basic_variable<CharT>::operator R() const
{
    return value<R>();
}

template <typename CharT>
template <typename Tag>
auto basic_variable<CharT>::value(std::error_code& error) const noexcept -> typename tag_traits<typename std::decay<Tag>::type>::type
{
    using return_type = typename tag_traits<typename std::decay<Tag>::type>::type;
    return detail::overloader<value_type, return_type>::convert(*this, error);
}

template <typename CharT>
template <typename Tag>
auto basic_variable<CharT>::value() const -> typename tag_traits<typename std::decay<Tag>::type>::type
{
    std::error_code error;
    auto result = value<Tag>(error);
    if (error)
        throw dynamic::error(error);
    return result;
}

template <typename CharT>
template <typename R>
auto basic_variable<CharT>::unsafe_get() & noexcept -> R&
{
    assert(same<R>());
    return storage.template get<typename std::decay<R>::type>();
}

template <typename CharT>
template <typename R>
auto basic_variable<CharT>::unsafe_get() const & noexcept -> const R&
{
    assert(same<R>());
    return storage.template get<typename std::decay<R>::type>();
}

template <typename CharT>
basic_variable<CharT>::operator bool() const
{
    switch (code())
    {
    case token::code::null:
        return false;
    case token::code::boolean:
        return bool(unsafe_get<bool>());
    case token::code::signed_char:
        return bool(unsafe_get<signed char>());
    case token::code::unsigned_char:
        return bool(unsafe_get<unsigned char>());
    case token::code::signed_short_integer:
        return bool(unsafe_get<signed short int>());
    case token::code::unsigned_short_integer:
        return bool(unsafe_get<unsigned short int>());
    case token::code::signed_integer:
        return bool(unsafe_get<signed int>());
    case token::code::unsigned_integer:
        return bool(unsafe_get<unsigned int>());
    case token::code::signed_long_integer:
        return bool(unsafe_get<signed long int>());
    case token::code::unsigned_long_integer:
        return bool(unsafe_get<unsigned long int>());
    case token::code::signed_long_long_integer:
        return bool(unsafe_get<signed long long int>());
    case token::code::unsigned_long_long_integer:
        return bool(unsafe_get<unsigned long long int>());
    case token::code::float_number:
        return bool(unsafe_get<float>());
    case token::code::double_number:
        return bool(unsafe_get<double>());
    case token::code::long_double_number:
        return bool(unsafe_get<long double>());
    case token::code::string:
    case token::code::array:
    case token::code::map:
        // C++ containers are not contextually convertible to bool, but we
        // make them so for variable to let the code compiler for non-container
        // types.
        throw dynamic::error(incompatible_type);
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (size_type position) & -> basic_variable&
{
    switch (symbol())
    {
    case token::symbol::array:
        return unsafe_get<array_type>()[position];

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (size_type position) const & -> const basic_variable&
{
    switch (symbol())
    {
    case token::symbol::array:
        return unsafe_get<array_type>().at(position);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (const typename map_type::key_type& key) & -> basic_variable&
{
    switch (symbol())
    {
    case token::symbol::map:
        return unsafe_get<map_type>()[key];

    case token::symbol::null:
        *this = basic_map<CharT>::make();
        return unsafe_get<map_type>()[key];

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (const typename map_type::key_type& key) const & -> const basic_variable&
{
    switch (symbol())
    {
    case token::symbol::map:
        return unsafe_get<map_type>().at(key);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
auto basic_variable<CharT>::find(const basic_variable<CharT>& other) & -> iterator
{
    return const_cast<const basic_variable&>(*this).find(other);
}

template <typename CharT>
auto basic_variable<CharT>::find(const basic_variable<CharT>& other) const & -> const_iterator
{
    switch (other.code())
    {
    case token::code::null:
        return find(other.unsafe_get<nullable>());
    case token::code::boolean:
        return find(other.unsafe_get<bool>());
    case token::code::signed_char:
        return find(other.unsafe_get<signed char>());
    case token::code::unsigned_char:
        return find(other.unsafe_get<unsigned char>());
    case token::code::signed_short_integer:
        return find(other.unsafe_get<signed short int>());
    case token::code::unsigned_short_integer:
        return find(other.unsafe_get<unsigned short int>());
    case token::code::signed_integer:
        return find(other.unsafe_get<signed int>());
    case token::code::unsigned_integer:
        return find(other.unsafe_get<unsigned int>());
    case token::code::signed_long_integer:
        return find(other.unsafe_get<signed long int>());
    case token::code::unsigned_long_integer:
        return find(other.unsafe_get<unsigned long int>());
    case token::code::signed_long_long_integer:
        return find(other.unsafe_get<signed long long int>());
    case token::code::unsigned_long_long_integer:
        return find(other.unsafe_get<unsigned long long int>());
    case token::code::float_number:
        return find(other.unsafe_get<float>());
    case token::code::double_number:
        return find(other.unsafe_get<double>());
    case token::code::long_double_number:
        return find(other.unsafe_get<long double>());
    case token::code::string:
        return find(other.unsafe_get<string_type>());
    case token::code::array:
        return find(other.unsafe_get<array_type>());
    case token::code::map:
        return find(other.unsafe_get<map_type>());
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::find(const T& other) & -> iterator
{
    return const_cast<const basic_variable&>(*this).find(other);
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::find(const T& other) const & -> const_iterator
{
    switch (symbol())
    {
    case token::symbol::null:
        return end();

    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return (*this == other) ? begin() : end();

    case token::symbol::array:
    case token::symbol::map:
        for (auto it = begin(); it != end(); ++it)
        {
            if (*it == other)
                return it;
        }
        return end();
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
auto basic_variable<CharT>::count(const basic_variable<CharT>& other) const -> size_type
{
    switch (other.code())
    {
    case token::code::null:
        return count(other.unsafe_get<nullable>());
    case token::code::boolean:
        return count(other.unsafe_get<bool>());
    case token::code::signed_char:
        return count(other.unsafe_get<signed char>());
    case token::code::unsigned_char:
        return count(other.unsafe_get<unsigned char>());
    case token::code::signed_short_integer:
        return count(other.unsafe_get<signed short int>());
    case token::code::unsigned_short_integer:
        return count(other.unsafe_get<unsigned short int>());
    case token::code::signed_integer:
        return count(other.unsafe_get<signed int>());
    case token::code::unsigned_integer:
        return count(other.unsafe_get<unsigned int>());
    case token::code::signed_long_integer:
        return count(other.unsafe_get<signed long int>());
    case token::code::unsigned_long_integer:
        return count(other.unsafe_get<unsigned long int>());
    case token::code::signed_long_long_integer:
        return count(other.unsafe_get<signed long long int>());
    case token::code::unsigned_long_long_integer:
        return count(other.unsafe_get<unsigned long long int>());
    case token::code::float_number:
        return count(other.unsafe_get<float>());
    case token::code::double_number:
        return count(other.unsafe_get<double>());
    case token::code::long_double_number:
        return count(other.unsafe_get<long double>());
    case token::code::string:
        return count(other.unsafe_get<string_type>());
    case token::code::array:
        return count(other.unsafe_get<array_type>());
    case token::code::map:
        return count(other.unsafe_get<map_type>());
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::count(const T& other) const -> size_type
{
    switch (symbol())
    {
    case token::symbol::null:
        return 0;

    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
    case token::symbol::string:
        return (*this == other) ? 1 : 0;

    case token::symbol::array:
    case token::symbol::map:
        {
            size_type result = 0;
            for (auto it = begin(); it != end(); ++it)
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
template <typename Tag>
bool basic_variable<CharT>::is() const noexcept
{
    using tag_type = typename tag_traits<typename std::decay<Tag>::type>::type;
    return storage.template call<similar_visitor<tag_type>, bool>();
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::same() const noexcept
{
    return detail::same_overloader<CharT, T>::same(storage.which());
}

template <typename CharT>
token::code::value basic_variable<CharT>::code() const noexcept
{
    switch (storage.which())
    {
    case traits<nullable>::value:
        return token::code::null;
    case traits<bool>::value:
        return token::code::boolean;
    case traits<signed char>::value:
        return token::code::signed_char;
    case traits<unsigned char>::value:
        return token::code::unsigned_char;
    case traits<signed short int>::value:
        return token::code::signed_short_integer;
    case traits<unsigned short int>::value:
        return token::code::unsigned_short_integer;
    case traits<signed int>::value:
        return token::code::signed_integer;
    case traits<unsigned int>::value:
        return token::code::unsigned_integer;
    case traits<signed long int>::value:
        return token::code::signed_long_integer;
    case traits<unsigned long int>::value:
        return token::code::unsigned_long_integer;
    case traits<signed long long int>::value:
        return token::code::signed_long_long_integer;
    case traits<unsigned long long int>::value:
        return token::code::unsigned_long_long_integer;
    case traits<float>::value:
        return token::code::float_number;
    case traits<double>::value:
        return token::code::double_number;
    case traits<long double>::value:
        return token::code::long_double_number;
    case traits<string_type>::value:
        return token::code::string;
    case traits<array_type>::value:
        return token::code::array;
    case traits<map_type>::value:
        return token::code::map;
    default:
        assert(false);
        return token::code::null;
    }
}

template <typename CharT>
token::symbol::value basic_variable<CharT>::symbol() const noexcept
{
    switch (storage.which())
    {
    case traits<nullable>::value:
        return token::symbol::null;
    case traits<bool>::value:
        return token::symbol::boolean;
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
        return token::symbol::integer;
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
        return token::symbol::number;
    case traits<string_type>::value:
        return token::symbol::string;
    case traits<array_type>::value:
        return token::symbol::array;
    case traits<map_type>::value:
        return token::symbol::map;
    default:
        assert(false);
        return token::symbol::null;
    }
}

template <typename CharT>
bool basic_variable<CharT>::empty() const noexcept
{
    switch (symbol())
    {
    case token::symbol::null:
        return true;
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
        return false;
    case token::symbol::string:
        return unsafe_get<string_type>().empty();
    case token::symbol::array:
        return unsafe_get<array_type>().empty();
    case token::symbol::map:
        return unsafe_get<map_type>().empty();
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
auto basic_variable<CharT>::size() const noexcept -> size_type
{
    switch (symbol())
    {
    case token::symbol::null:
        return 0;
    case token::symbol::boolean:
    case token::symbol::integer:
    case token::symbol::number:
        return 1;
    case token::symbol::string:
        return unsafe_get<string_type>().size();
    case token::symbol::array:
        return unsafe_get<array_type>().size();
    case token::symbol::map:
        return unsafe_get<map_type>().size();
    }
    TRIAL_PROTOCOL_UNREACHABLE();
}

template <typename CharT>
void basic_variable<CharT>::clear() noexcept
{
    switch (code())
    {
    case token::code::null:
        storage = null;
        break;
    case token::code::boolean:
        storage = bool{};
        break;
    case token::code::signed_char:
        {
            const signed char value = 0;
            storage = value;
        }
        break;
    case token::code::unsigned_char:
        {
            const unsigned char value = 0U;
            storage = value;
        }
        break;
    case token::code::signed_short_integer:
        {
            const signed short int value = 0;
            storage = value;
        }
        break;
    case token::code::unsigned_short_integer:
        {
            const unsigned short int value = 0U;
            storage = value;
        }
        break;
    case token::code::signed_integer:
        storage = 0;
        break;
    case token::code::unsigned_integer:
        storage = 0U;
        break;
    case token::code::signed_long_integer:
        storage = 0L;
        break;
    case token::code::unsigned_long_integer:
        storage = 0UL;
        break;
    case token::code::signed_long_long_integer:
        storage = 0LL;
        break;
    case token::code::unsigned_long_long_integer:
        storage = 0ULL;
        break;
    case token::code::float_number:
        storage = 0.0f;
        break;
    case token::code::double_number:
        storage = 0.0;
        break;
    case token::code::long_double_number:
        storage = 0.0L;
        break;
    case token::code::string:
        unsafe_get<string_type>().clear();
        break;
    case token::code::array:
        unsafe_get<array_type>().clear();
        break;
    case token::code::map:
        unsafe_get<map_type>().clear();
        break;
    }
}

template <typename CharT>
auto basic_variable<CharT>::erase(const_iterator where) -> iterator
{
    using array_iterator = typename basic_variable<CharT>::const_iterator::array_iterator;
    using map_iterator = typename basic_variable<CharT>::const_iterator::map_iterator;

    iterator result = where;

    switch (symbol())
    {
    case token::symbol::array:
        {
            auto& array = unsafe_get<array_type>();
            auto& array_where = where.current.template get<array_iterator>();
            result.current = array.erase(array_where);
        }
        break;

    case token::symbol::map:
        result.current =
            unsafe_get<map_type>().erase(where.current.template get<map_iterator>());
        break;

    default:
        // Non-container types are unerasable
        break;
    }
    return result;
}

template <typename CharT>
auto basic_variable<CharT>::erase(const_iterator first, const_iterator last) -> iterator
{
    using array_iterator = typename basic_variable<CharT>::const_iterator::array_iterator;
    using map_iterator = typename basic_variable<CharT>::const_iterator::map_iterator;

    iterator result = first;

    switch (symbol())
    {
    case token::symbol::array:
        result.current =
            unsafe_get<array_type>().erase(first.current.template get<array_iterator>(),
                                           last.current.template get<array_iterator>());
        break;

    case token::symbol::map:
        result.current =
            unsafe_get<map_type>().erase(first.current.template get<map_iterator>(),
                                         last.current.template get<map_iterator>());
        break;

    default:
        // Non-container types are unerasable
        break;
    }
    return result;
}

template <typename CharT>
auto basic_variable<CharT>::begin() & -> iterator
{
    return {this};
}

template <typename CharT>
auto basic_variable<CharT>::begin() const & -> const_iterator
{
    return {this};
}

template <typename CharT>
auto basic_variable<CharT>::end() & -> iterator
{
    return {this, false};
}

template <typename CharT>
auto basic_variable<CharT>::end() const & -> const_iterator
{
    return {this, false};
}

template <typename CharT>
auto basic_variable<CharT>::key_begin() const & -> key_iterator
{
    return {this};
}

template <typename CharT>
auto basic_variable<CharT>::key_end() const & -> key_iterator
{
    return {this, false};
}

// Comparison

template <typename T, typename U>
bool operator== (const T& lhs, const U& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
{
    return detail::operator_overloader<T, U>::equal(lhs, rhs);
}

template <typename T, typename U>
bool operator!= (const T& lhs, const U& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
{
    return !(lhs == rhs);
}

template <typename T, typename U>
bool operator< (const T& lhs, const U& rhs) TRIAL_PROTOCOL_CXX14(noexcept)
{
    return detail::operator_overloader<T, U>::less(lhs, rhs);
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::operator<= (const T& rhs) const TRIAL_PROTOCOL_CXX14(noexcept)
{
    if (same<nullable>())
        return true;

    return !(rhs < *this);
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::operator> (const T& rhs) const TRIAL_PROTOCOL_CXX14(noexcept)
{
    if (same<nullable>())
        return false;

    return rhs < *this;
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::operator>= (const T& rhs) const TRIAL_PROTOCOL_CXX14(noexcept)
{
    return !(*this < rhs);
}
template <typename CharT>
basic_variable<CharT>::key_iterator::key_iterator()
    : super()
{
}

//-----------------------------------------------------------------------------
// Factories
//-----------------------------------------------------------------------------

template <typename CharT>
struct basic_array
{
    static basic_variable<CharT> make()
    {
        basic_variable<CharT> result;
        result.storage = typename basic_variable<CharT>::array_type{};
        return result;
    }

    template <typename ForwardIterator>
    static basic_variable<CharT> make(ForwardIterator begin, ForwardIterator end)
    {
        basic_variable<CharT> result;
        result.storage = typename basic_variable<CharT>::array_type(begin, end);
        return result;
    }

    static basic_variable<CharT> make(std::initializer_list<typename basic_variable<CharT>::value_type> init)
    {
        basic_variable<CharT> result;
        result.storage = typename basic_variable<CharT>::array_type(init.begin(), init.end());
        return result;
    }

    template <typename T>
    static basic_variable<CharT> repeat(typename basic_variable<CharT>::size_type size,
                                        const T& value)
    {
        basic_variable<CharT> result;
        result.storage = typename basic_variable<CharT>::array_type(size, basic_variable<CharT>(value));
        return result;
    }
};

template <typename CharT>
struct basic_map
{
    static basic_variable<CharT> make()
    {
        basic_variable<CharT> result;
        result.storage = typename basic_variable<CharT>::map_type{};
        return result;
    }

    template <typename T, typename U>
    static basic_variable<CharT> make(T key, U value)
    {
        return make({ std::move(key), std::move(value) });
    }

    static basic_variable<CharT> make(typename basic_variable<CharT>::pair_type value)
    {
        basic_variable<CharT> result;
        result.storage = typename basic_variable<CharT>::map_type{std::move(value)};
        return result;
    }

    static basic_variable<CharT> make(std::initializer_list<typename basic_variable<CharT>::pair_type> init)
    {
        basic_variable<CharT> result;
        result.storage = typename basic_variable<CharT>::map_type(init.begin(), init.end());
        return result;
    }
};

} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_DETAIL_VARIABLE_IPP
