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

#include <trial/protocol/detail/type_traits.hpp>
#include <trial/protocol/dynamic/error.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{

namespace detail
{

template <typename T>
using is_null = std::is_same<T, nullable>;

template <typename T>
using is_boolean = protocol::detail::is_bool<T>;

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
template <typename T, typename Enable>
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

template <typename T, typename U, typename Enable = void>
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

    static U convert(const variable_type& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return {};

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U&)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return true;

        default:
            return false;
        }
    }

    static bool less(const variable_type&, const U&)
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

    static U convert(const variable_type& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>();

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>();

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>();

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>();

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>();

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>();

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>();

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>();

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>();

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>();

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>();

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() == other;

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>() == other;

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>() == other;

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>() == other;

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>() == other;

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>() == other;

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>() == other;

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>() == other;

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>() == other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() == other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() == other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return true;

        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() < other;

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>() < other;

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>() < other;

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>() < other;

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>() < other;

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>() < other;

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>() < other;

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>() < other;

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>() < other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() < other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() < other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            self.storage = other; // Overwrite null
            break;

        case variable_type::template traits<bool>::value:
            self.storage.template get<bool>() += other;
            break;

        case variable_type::template traits<signed short int>::value:
            self.storage.template get<signed short int>() += other;
            break;

        case variable_type::template traits<unsigned short int>::value:
            self.storage.template get<unsigned short int>() += other;
            break;

        case variable_type::template traits<signed int>::value:
            self.storage.template get<signed int>() += other;
            break;

        case variable_type::template traits<unsigned int>::value:
            self.storage.template get<unsigned int>() += other;
            break;

        case variable_type::template traits<signed long int>::value:
            self.storage.template get<signed long int>() += other;
            break;

        case variable_type::template traits<unsigned long int>::value:
            self.storage.template get<unsigned long int>() += other;
            break;

        case variable_type::template traits<signed long long int>::value:
            self.storage.template get<signed long long int>() += other;
            break;

        case variable_type::template traits<unsigned long long int>::value:
            self.storage.template get<unsigned long long int>() += other;
            break;

        case variable_type::template traits<float>::value:
            self.storage.template get<float>() += other;
            break;

        case variable_type::template traits<double>::value:
            self.storage.template get<double>() += other;
            break;

        case variable_type::template traits<long double>::value:
            self.storage.template get<long double>() += other;
            break;

        case variable_type::template traits<array_type>::value:
            self.storage.template get<array_type>().push_back(other);
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

    static U convert(const variable_type& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>();

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>();

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>();

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>();

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>();

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>();

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>();

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>();

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>();

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>();

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>();

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() == other;

        case variable_type::template traits<signed short int>::value:
        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<signed short int>() == other;

        case variable_type::template traits<signed int>::value:
        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<signed int>() == other;

        case variable_type::template traits<signed long int>::value:
        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<signed long int>() == other;

        case variable_type::template traits<signed long long int>::value:
        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<signed long long int>() == other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() == other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() == other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return true;

        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() < other;

        case variable_type::template traits<signed short int>::value:
        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<signed short int>() < other;

        case variable_type::template traits<signed int>::value:
        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<signed int>() < other;

        case variable_type::template traits<signed long int>::value:
        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<signed long int>() < other;

        case variable_type::template traits<signed long long int>::value:
        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<signed long long int>() < other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() < other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() < other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            self.storage = other; // Overwrite null
            break;

        case variable_type::template traits<bool>::value:
            self.storage.template get<bool>() += other;
            break;

        case variable_type::template traits<signed short int>::value:
            self.storage.template get<signed short int>() += other;
            break;

        case variable_type::template traits<unsigned short int>::value:
            self.storage.template get<unsigned short int>() += other;
            break;

        case variable_type::template traits<signed int>::value:
            self.storage.template get<signed int>() += other;
            break;

        case variable_type::template traits<unsigned int>::value:
            self.storage.template get<unsigned int>() += other;
            break;

        case variable_type::template traits<signed long int>::value:
            self.storage.template get<signed long int>() += other;
            break;

        case variable_type::template traits<unsigned long int>::value:
            self.storage.template get<unsigned long int>() += other;
            break;

        case variable_type::template traits<signed long long int>::value:
            self.storage.template get<signed long long int>() += other;
            break;

        case variable_type::template traits<unsigned long long int>::value:
            self.storage.template get<unsigned long long int>() += other;
            break;

        case variable_type::template traits<float>::value:
            self.storage.template get<float>() += other;
            break;

        case variable_type::template traits<double>::value:
            self.storage.template get<double>() += other;
            break;

        case variable_type::template traits<long double>::value:
            self.storage.template get<long double>() += other;
            break;

        case variable_type::template traits<array_type>::value:
            self.storage.template get<array_type>().push_back(other);
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

    static U convert(const variable_type& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>();

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>();

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>();

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>();

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>();

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>();

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>();

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>();

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>();

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>();

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>();

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() == other;

        case variable_type::template traits<signed short int>::value:
        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>() == other;

        case variable_type::template traits<signed int>::value:
        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>() == other;

        case variable_type::template traits<signed long int>::value:
        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>() == other;

        case variable_type::template traits<signed long long int>::value:
        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>() == other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() == other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() == other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return true;

        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() < other;

        case variable_type::template traits<signed short int>::value:
        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>() < other;

        case variable_type::template traits<signed int>::value:
        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>() < other;

        case variable_type::template traits<signed long int>::value:
        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>() < other;

        case variable_type::template traits<signed long long int>::value:
        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>() < other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() < other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() < other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            self.storage = other; // Overwrite null
            break;

        case variable_type::template traits<bool>::value:
            self.storage.template get<bool>() += other;
            break;

        case variable_type::template traits<signed short int>::value:
            self.storage.template get<signed short int>() += other;
            break;

        case variable_type::template traits<unsigned short int>::value:
            self.storage.template get<unsigned short int>() += other;
            break;

        case variable_type::template traits<signed int>::value:
            self.storage.template get<signed int>() += other;
            break;

        case variable_type::template traits<unsigned int>::value:
            self.storage.template get<unsigned int>() += other;
            break;

        case variable_type::template traits<signed long int>::value:
            self.storage.template get<signed long int>() += other;
            break;

        case variable_type::template traits<unsigned long int>::value:
            self.storage.template get<unsigned long int>() += other;
            break;

        case variable_type::template traits<signed long long int>::value:
            self.storage.template get<signed long long int>() += other;
            break;

        case variable_type::template traits<unsigned long long int>::value:
            self.storage.template get<unsigned long long int>() += other;
            break;

        case variable_type::template traits<float>::value:
            self.storage.template get<float>() += other;
            break;

        case variable_type::template traits<double>::value:
            self.storage.template get<double>() += other;
            break;

        case variable_type::template traits<long double>::value:
            self.storage.template get<long double>() += other;
            break;

        case variable_type::template traits<array_type>::value:
            self.storage.template get<array_type>().push_back(other);
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

    static U convert(const variable_type& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>();

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>();

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>();

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>();

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>();

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>();

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>();

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>();

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>();

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>();

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>();

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() == other;

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>() == other;

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>() == other;

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>() == other;

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>() == other;

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>() == other;

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>() == other;

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>() == other;

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>() == other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() == other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() == other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return true;

        case variable_type::template traits<bool>::value:
            return self.storage.template get<bool>() < other;

        case variable_type::template traits<signed short int>::value:
            return self.storage.template get<signed short int>() < other;

        case variable_type::template traits<unsigned short int>::value:
            return self.storage.template get<unsigned short int>() < other;

        case variable_type::template traits<signed int>::value:
            return self.storage.template get<signed int>() < other;

        case variable_type::template traits<unsigned int>::value:
            return self.storage.template get<unsigned int>() < other;

        case variable_type::template traits<signed long int>::value:
            return self.storage.template get<signed long int>() < other;

        case variable_type::template traits<unsigned long int>::value:
            return self.storage.template get<unsigned long int>() < other;

        case variable_type::template traits<signed long long int>::value:
            return self.storage.template get<signed long long int>() < other;

        case variable_type::template traits<unsigned long long int>::value:
            return self.storage.template get<unsigned long long int>() < other;

        case variable_type::template traits<float>::value:
            return self.storage.template get<float>() < other;

        case variable_type::template traits<double>::value:
            return self.storage.template get<double>() < other;

        case variable_type::template traits<long double>::value:
            return self.storage.template get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            self.storage = other; // Overwrite null
            break;

        case variable_type::template traits<bool>::value:
            self.storage.template get<bool>() += other;
            break;

        case variable_type::template traits<signed short int>::value:
            self.storage.template get<signed short int>() += other;
            break;

        case variable_type::template traits<unsigned short int>::value:
            self.storage.template get<unsigned short int>() += other;
            break;

        case variable_type::template traits<signed int>::value:
            self.storage.template get<signed int>() += other;
            break;

        case variable_type::template traits<unsigned int>::value:
            self.storage.template get<unsigned int>() += other;
            break;

        case variable_type::template traits<signed long int>::value:
            self.storage.template get<signed long int>() += other;
            break;

        case variable_type::template traits<unsigned long int>::value:
            self.storage.template get<unsigned long int>() += other;
            break;

        case variable_type::template traits<signed long long int>::value:
            self.storage.template get<signed long long int>() += other;
            break;

        case variable_type::template traits<unsigned long long int>::value:
            self.storage.template get<unsigned long long int>() += other;
            break;

        case variable_type::template traits<float>::value:
            self.storage.template get<float>() += other;
            break;

        case variable_type::template traits<double>::value:
            self.storage.template get<double>() += other;
            break;

        case variable_type::template traits<long double>::value:
            self.storage.template get<long double>() += other;
            break;

        case variable_type::template traits<array_type>::value:
            self.storage.template get<array_type>().push_back(other);
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

    static U convert(const variable_type& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<string_type>::value:
            return self.storage.template get<string_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<string_type>::value:
            return self.storage.template get<string_type>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<string_type>::value:
            return self.storage.template get<string_type>() < other;

        case variable_type::template traits<array_type>::value:
        case variable_type::template traits<map_type>::value:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            self.storage = other; // Overwrite null
            break;

        case variable_type::template traits<string_type>::value:
            self.storage.template get<string_type>() += other;
            break;

        case variable_type::template traits<array_type>::value:
            self.storage.template get<array_type>().push_back(other);
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

    static U convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<array_type>::value:
            return self.storage.template get<array_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<array_type>::value:
            {
                const auto& array = self.storage.template get<array_type>();
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

    static bool less(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<array_type>::value:
            {
                const auto& array = self.storage.template get<array_type>();
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

        case variable_type::template traits<map_type>::value:
            return false;

        default:
            return true;
        }
    }

    static void append(variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            self.storage = other; // Overwrite null
            break;

        case variable_type::template traits<array_type>::value:
            {
                auto& array = self.storage.template get<array_type>();
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

    static U convert(const variable_type& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<map_type>::value:
            return self.storage.template get<map_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<map_type>::value:
            {
                const auto& map = self.storage.template get<map_type>();
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

    static bool less(const variable_type& self, const U& other)
    {
        switch (self.storage.which())
        {
        case variable_type::template traits<map_type>::value:
            {
                const auto& map = self.storage.template get<map_type>();
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
        switch (self.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            self.storage = other; // Overwrite null
            break;

        case variable_type::template traits<map_type>::value:
            {
                auto& map = self.storage.template get<map_type>();
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

template <typename T, typename U, typename Enable = void>
struct operator_overloader
{
    static bool equal(const T& lhs, const U& rhs)
    {
        // This function is called by dynamic::operator== when none of the
        // specializations below apply.
        //
        // basic_variable<CharT>::iterator_type<T> cannot be matched via
        // SFINAE below (due to being a non-deduced context), so instead
        // lhs.operator(rhs) is called in the general case.
        //
        // Notice: operator==(lhs, rhs) cannot be used because it uses
        // argument dependent lookup which will find dynamic::operator==
        // which got us here in the first place. That would cause an
        // infinity recursion.

        return lhs.operator==(rhs);
    }

    static bool less(const T& lhs, const U& rhs)
    {
        // See comment for operator_overloader::equal()

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
    equal(const variable_type& lhs,
          const T& rhs)
    {
        return detail::template overloader<variable_type, T>::equal(lhs, rhs);
    }

    static bool equal(const variable_type& lhs,
                      const CharT* rhs)
    {
        return detail::template overloader<variable_type, string_type>::equal(lhs, string_type(rhs));
    }

    template <typename T = U>
    static typename std::enable_if<!std::is_same<typename std::decay<T>::type,
                                                 const CharT *>::value,
                                   bool>::type
    less(const variable_type& lhs,
         const T& rhs)
    {
        return detail::template overloader<variable_type, T>::less(lhs, rhs);
    }

    static bool less(const variable_type& lhs,
                     const CharT* rhs)
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

    static bool equal(const T& lhs,
                      const variable_type& rhs)
    {
        return operator_overloader<variable_type, variable_type>::equal(variable_type(lhs), rhs);
    }

    static bool less(const T& lhs,
                     const variable_type& rhs)
    {
        return operator_overloader<variable_type, variable_type>::less(variable_type(lhs), rhs);
    }
};

template <typename CharT>
struct operator_overloader<
    basic_variable<CharT>,
    basic_variable<protocol::detail::meta::identity_t<CharT>>>
{
    using variable_type = basic_variable<CharT>;
    using string_type = typename variable_type::string_type;
    using array_type = typename variable_type::array_type;
    using map_type = typename variable_type::map_type;

    static bool equal(const variable_type& lhs,
                      const variable_type& rhs)
    {
        switch (rhs.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return detail::template overloader<variable_type, nullable>::
                equal(lhs, rhs.template value<nullable>());

        case variable_type::template traits<bool>::value:
            return detail::template overloader<variable_type, bool>::
                equal(lhs, rhs.storage.template get<bool>());

        case variable_type::template traits<signed short int>::value:
            return detail::template overloader<variable_type, signed short int>::
                equal(lhs, rhs.storage.template get<signed short int>());

        case variable_type::template traits<unsigned short int>::value:
            return detail::template overloader<variable_type, unsigned short int>::
                equal(lhs, rhs.storage.template get<unsigned short int>());

        case variable_type::template traits<signed int>::value:
            return detail::template overloader<variable_type, signed int>::
                equal(lhs, rhs.storage.template get<signed int>());

        case variable_type::template traits<unsigned int>::value:
            return detail::template overloader<variable_type, unsigned int>::
                equal(lhs, rhs.storage.template get<unsigned int>());

        case variable_type::template traits<signed long int>::value:
            return detail::template overloader<variable_type, signed long int>::
                equal(lhs, rhs.storage.template get<signed long int>());

        case variable_type::template traits<unsigned long int>::value:
            return detail::template overloader<variable_type, unsigned long int>::
                equal(lhs, rhs.storage.template get<unsigned long int>());

        case variable_type::template traits<signed long long int>::value:
            return detail::template overloader<variable_type, signed long long int>::
                equal(lhs, rhs.storage.template get<signed long long int>());

        case variable_type::template traits<unsigned long long int>::value:
            return detail::template overloader<variable_type, unsigned long long int>::
                equal(lhs, rhs.storage.template get<unsigned long long int>());

        case variable_type::template traits<float>::value:
            return detail::template overloader<variable_type, float>::
                equal(lhs, rhs.storage.template get<float>());

        case variable_type::template traits<double>::value:
            return detail::template overloader<variable_type, double>::
                equal(lhs, rhs.storage.template get<double>());

        case variable_type::template traits<long double>::value:
            return detail::template overloader<variable_type, long double>::
                equal(lhs, rhs.storage.template get<long double>());

        case variable_type::template traits<string_type>::value:
            return detail::template overloader<variable_type, string_type>::
                equal(lhs, rhs.storage.template get<string_type>());

        case variable_type::template traits<array_type>::value:
            return detail::template overloader<variable_type, array_type>::
                equal(lhs, rhs.storage.template get<array_type>());

        case variable_type::template traits<map_type>::value:
            return detail::template overloader<variable_type, map_type>::
                equal(lhs, rhs.storage.template get<map_type>());
        }
        return false;
    }

    static bool less(const variable_type& lhs,
                     const variable_type& rhs)
    {
        switch (rhs.storage.which())
        {
        case variable_type::template traits<nullable>::value:
            return detail::template overloader<variable_type, nullable>::
                less(lhs, rhs.template value<nullable>());

        case variable_type::template traits<bool>::value:
            return detail::template overloader<variable_type, bool>::
                less(lhs, rhs.storage.template get<bool>());

        case variable_type::template traits<signed short int>::value:
            return detail::template overloader<variable_type, signed short int>::
                less(lhs, rhs.storage.template get<signed short int>());

        case variable_type::template traits<unsigned short int>::value:
            return detail::template overloader<variable_type, unsigned short int>::
                less(lhs, rhs.storage.template get<unsigned short int>());

        case variable_type::template traits<signed int>::value:
            return detail::template overloader<variable_type, signed int>::
                less(lhs, rhs.storage.template get<signed int>());

        case variable_type::template traits<unsigned int>::value:
            return detail::template overloader<variable_type, unsigned int>::
                less(lhs, rhs.storage.template get<unsigned int>());

        case variable_type::template traits<signed long int>::value:
            return detail::template overloader<variable_type, signed long int>::
                less(lhs, rhs.storage.template get<signed long int>());

        case variable_type::template traits<unsigned long int>::value:
            return detail::template overloader<variable_type, unsigned long int>::
                less(lhs, rhs.storage.template get<unsigned long int>());

        case variable_type::template traits<signed long long int>::value:
            return detail::template overloader<variable_type, signed long long int>::
                less(lhs, rhs.storage.template get<signed long long int>());

        case variable_type::template traits<unsigned long long int>::value:
            return detail::template overloader<variable_type, unsigned long long int>::
                less(lhs, rhs.storage.template get<unsigned long long int>());

        case variable_type::template traits<float>::value:
            return detail::template overloader<variable_type, float>::
                less(lhs, rhs.storage.template get<float>());

        case variable_type::template traits<double>::value:
            return detail::template overloader<variable_type, double>::
                less(lhs, rhs.storage.template get<double>());

        case variable_type::template traits<long double>::value:
            return detail::template overloader<variable_type, long double>::
                less(lhs, rhs.storage.template get<long double>());

        case variable_type::template traits<string_type>::value:
            return detail::template overloader<variable_type, string_type>::
                less(lhs, rhs.storage.template get<string_type>());

        case variable_type::template traits<array_type>::value:
            return detail::template overloader<variable_type, array_type>::
                less(lhs, rhs.storage.template get<array_type>());

        case variable_type::template traits<map_type>::value:
            return detail::template overloader<variable_type, map_type>::
                less(lhs, rhs.storage.template get<map_type>());
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

template <typename C, typename T, typename Enable = void>
struct same_overloader
{
    static bool same(std::size_t which)
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
    static bool same(std::size_t)
    {
        return false;
    }
};

} // namespace detail

//-----------------------------------------------------------------------------
// variable::iterator_type
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename T>
basic_variable<CharT>::iterator_type<T>::iterator_type()
    : scope(nullptr),
      current(pointer(nullptr))
{
}

template <typename CharT>
template <typename T>
basic_variable<CharT>::iterator_type<T>::iterator_type(const iterator_type& other)
    : scope(other.scope),
      current(other.current)
{
}

template <typename CharT>
template <typename T>
basic_variable<CharT>::iterator_type<T>::iterator_type(iterator_type&& other)
    : scope(std::move(other.scope)),
      current(std::move(other.current))
{
}

template <typename CharT>
template <typename T>
basic_variable<CharT>::iterator_type<T>::iterator_type(pointer p,
                                                       bool initialize)
    : scope(p),
      current(pointer(nullptr))
{
    switch (scope->storage.which())
    {
    case traits<nullable>::value:
        current = pointer(nullptr);
        break;

    case traits<bool>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
    case traits<string_type>::value:
        if (initialize)
            current = p;
        break;

    case traits<array_type>::value:
        if (initialize)
            current = p->storage.template get<array_type>().begin();
        else
            current = p->storage.template get<array_type>().end();
        break;

    case traits<map_type>::value:
        if (initialize)
            current = p->storage.template get<map_type>().begin();
        else
            current = p->storage.template get<map_type>().end();
        break;

    default:
        assert(false);
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
template <typename T>
template <typename U>
basic_variable<CharT>::iterator_type<T>::iterator_type(const iterator_type<typename std::remove_const<U>::type>& other,
                                                       typename std::enable_if<std::is_const<U>::value, pointer>::type nil)
    : scope(other.scope),
      current(nil)
{
    switch (other.current.which())
    {
    case small_union::template index<pointer>::value:
        current = other.current.template get<pointer>();
        break;
    case small_union::template index<array_iterator>::value:
        current = other.current.template get<array_iterator>();
        break;
    case small_union::template index<map_iterator>::value:
        current = other.current.template get<map_iterator>();
        break;
    }
}

template <typename CharT>
template <typename T>
template <typename U>
basic_variable<CharT>::iterator_type<T>::iterator_type(const iterator_type<typename std::add_const<U>::type>& other,
                                                       typename std::enable_if<!std::is_const<U>::value, pointer>::type nil)
    : scope(const_cast<pointer>(other.scope)),
      current(nil)
{
    switch (other.current.which())
    {
    case small_union::template index<pointer>::value:
        current = other.current.template get<pointer>();
        break;
    case small_union::template index<array_iterator>::value:
        current = other.current.template get<array_iterator>();
        break;
    case small_union::template index<map_iterator>::value:
        current = other.current.template get<map_iterator>();
        break;
    }
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::operator= (const iterator_type& other) -> iterator_type&
{
    scope = other.scope;
    current = other.current;
    return *this;
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::operator= (iterator_type&& other) -> iterator_type&
{
    scope = std::move(other.scope);
    current = std::move(other.current);
    return *this;
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::operator++ () -> iterator_type&
{
    assert(scope);

    switch (scope->storage.which())
    {
    case traits<nullable>::value:
    case traits<bool>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
    case traits<string_type>::value:
        current = pointer(nullptr);
        break;

    case traits<array_type>::value:
        ++current.template get<array_iterator>();
        break;

    case traits<map_type>::value:
        ++current.template get<map_iterator>();
        break;

    default:
        assert(false);
        break;
    }
    return *this;
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::operator++ (int) -> iterator_type
{
    assert(scope);

    iterator_type result = *this;
    ++(*this);
    return result;
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::operator* () -> reference
{
    assert(scope);

    return value();
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::key() const -> key_reference
{
    assert(scope);

    switch (scope->storage.which())
    {
    case traits<map_type>::value:
        return current.template get<map_iterator>()->first;

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::value() -> reference
{
    assert(scope);

    switch (scope->storage.which())
    {
    case traits<nullable>::value:
    case traits<bool>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
    case traits<string_type>::value:
        return *current.template get<pointer>();

    case traits<array_type>::value:
        return *current.template get<array_iterator>();

    case traits<map_type>::value:
        return current.template get<map_iterator>()->second;
    }
    assert(false);
    throw dynamic::error(incompatible_type);
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::iterator_type<T>::operator-> () -> pointer
{
    assert(scope);

    switch (scope->storage.which())
    {
    case traits<nullable>::value:
    case traits<bool>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
    case traits<string_type>::value:
        return current.template get<pointer>();

    case traits<array_type>::value:
        return &*current.template get<array_iterator>();

    case traits<map_type>::value:
        return &current.template get<map_iterator>()->second;
    }
    assert(false);
    throw dynamic::error(incompatible_type);
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::iterator_type<T>::operator== (const iterator_type<T>& other)
{
    if (!scope)
        return !other.scope;
    if (!other.scope)
        return false;

    assert(scope->storage.which() == other.scope->storage.which());

    switch (scope->storage.which())
    {
    case traits<nullable>::value:
    case traits<bool>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
    case traits<string_type>::value:
        return current.template get<pointer>() == other.current.template get<pointer>();

    case traits<array_type>::value:
        return current.template get<array_iterator>() == other.current.template get<array_iterator>();

    case traits<map_type>::value:
        return current.template get<map_iterator>() == other.current.template get<map_iterator>();

    default:
        assert(false);
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::iterator_type<T>::operator!= (const iterator_type<T>& other)
{
    return !(*this == other);
}

//-----------------------------------------------------------------------------
// visitors
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
    switch (other.storage.which())
    {
    case traits<nullable>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = other.storage.template get<bool>();
        break;
    case traits<signed short int>::value:
        storage = other.storage.template get<signed short int>();
        break;
    case traits<unsigned short int>::value:
        storage = other.storage.template get<unsigned short int>();
        break;
    case traits<signed int>::value:
        storage = other.storage.template get<signed int>();
        break;
    case traits<unsigned int>::value:
        storage = other.storage.template get<unsigned int>();
        break;
    case traits<signed long int>::value:
        storage = other.storage.template get<signed long int>();
        break;
    case traits<unsigned long int>::value:
        storage = other.storage.template get<unsigned long int>();
        break;
    case traits<signed long long int>::value:
        storage = other.storage.template get<signed long long int>();
        break;
    case traits<unsigned long long int>::value:
        storage = other.storage.template get<unsigned long long int>();
        break;
    case traits<float>::value:
        storage = other.storage.template get<float>();
        break;
    case traits<double>::value:
        storage = other.storage.template get<double>();
        break;
    case traits<long double>::value:
        storage = other.storage.template get<long double>();
        break;
    case traits<string_type>::value:
        storage = other.storage.template get<string_type>();
        break;
    case traits<array_type>::value:
        storage = other.storage.template get<array_type>();
        break;
    case traits<map_type>::value:
        storage = other.storage.template get<map_type>();
        break;
    default:
        assert(false);
        break;
    }
}

template <typename CharT>
basic_variable<CharT>::basic_variable(basic_variable&& other)
    : storage(null)
{
    switch (other.storage.which())
    {
    case traits<nullable>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = std::move(other.storage.template get<bool>());
        break;
    case traits<signed short int>::value:
        storage = std::move(other.storage.template get<signed short int>());
        break;
    case traits<unsigned short int>::value:
        storage = std::move(other.storage.template get<unsigned short int>());
        break;
    case traits<signed int>::value:
        storage = std::move(other.storage.template get<signed int>());
        break;
    case traits<unsigned int>::value:
        storage = std::move(other.storage.template get<unsigned int>());
        break;
    case traits<signed long int>::value:
        storage = std::move(other.storage.template get<signed long int>());
        break;
    case traits<unsigned long int>::value:
        storage = std::move(other.storage.template get<unsigned long int>());
        break;
    case traits<signed long long int>::value:
        storage = std::move(other.storage.template get<signed long long int>());
        break;
    case traits<unsigned long long int>::value:
        storage = std::move(other.storage.template get<unsigned long long int>());
        break;
    case traits<float>::value:
        storage = std::move(other.storage.template get<float>());
        break;
    case traits<double>::value:
        storage = std::move(other.storage.template get<double>());
        break;
    case traits<long double>::value:
        storage = std::move(other.storage.template get<long double>());
        break;
    case traits<string_type>::value:
        storage = std::move(other.storage.template get<string_type>());
        break;
    case traits<array_type>::value:
        storage = std::move(other.storage.template get<array_type>());
        break;
    case traits<map_type>::value:
        storage = std::move(other.storage.template get<map_type>());
        break;
    default:
        assert(false);
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
auto basic_variable<CharT>::array() -> value_type
{
    variable result;
    result.storage = array_type{};
    return result;
}

template <typename CharT>
template <typename ForwardIterator>
auto basic_variable<CharT>::array(ForwardIterator begin, ForwardIterator end) -> value_type
{
    variable result;
    result.storage = array_type(begin, end);
    return result;
}

template <typename CharT>
auto basic_variable<CharT>::array(std::initializer_list<typename array_type::value_type> init) -> value_type
{
    variable result;
    result.storage = array_type(init.begin(), init.end());
    return result;
}

template <typename CharT>
template <typename T>
auto basic_variable<CharT>::array(size_type size, const T& value) -> value_type
{
    variable result;
    result.storage = array_type(size, variable(value));
    return result;
}

template <typename CharT>
auto basic_variable<CharT>::map() -> value_type
{
    variable result;
    result.storage = map_type{};
    return result;
}

template <typename CharT>
auto basic_variable<CharT>::map(std::initializer_list<typename map_type::value_type> init) -> value_type
{
    variable result;
    result.storage = map_type(init.begin(), init.end());
    return result;
}

template <typename CharT>
auto basic_variable<CharT>::operator= (const basic_variable& other) -> basic_variable&
{
    switch (other.storage.which())
    {
    case traits<nullable>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = other.storage.template get<bool>();
        break;
    case traits<signed short int>::value:
        storage = other.storage.template get<signed short int>();
        break;
    case traits<unsigned short int>::value:
        storage = other.storage.template get<unsigned short int>();
        break;
    case traits<signed int>::value:
        storage = other.storage.template get<signed int>();
        break;
    case traits<unsigned int>::value:
        storage = other.storage.template get<unsigned int>();
        break;
    case traits<signed long int>::value:
        storage = other.storage.template get<signed long int>();
        break;
    case traits<unsigned long int>::value:
        storage = other.storage.template get<unsigned long int>();
        break;
    case traits<signed long long int>::value:
        storage = other.storage.template get<signed long long int>();
        break;
    case traits<unsigned long long int>::value:
        storage = other.storage.template get<unsigned long long int>();
        break;
    case traits<float>::value:
        storage = other.storage.template get<float>();
        break;
    case traits<double>::value:
        storage = other.storage.template get<double>();
        break;
    case traits<long double>::value:
        storage = other.storage.template get<long double>();
        break;
    case traits<string_type>::value:
        storage = other.storage.template get<string_type>();
        break;
    case traits<array_type>::value:
        storage = other.storage.template get<array_type>();
        break;
    case traits<map_type>::value:
        storage = other.storage.template get<map_type>();
        break;
    default:
        assert(false);
        break;
    }
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator= (basic_variable&& other) -> basic_variable&
{
    switch (other.storage.which())
    {
    case traits<nullable>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = std::move(other.storage.template get<bool>());
        break;
    case traits<signed short int>::value:
        storage = std::move(other.storage.template get<signed short int>());
        break;
    case traits<unsigned short int>::value:
        storage = std::move(other.storage.template get<unsigned short int>());
        break;
    case traits<signed int>::value:
        storage = std::move(other.storage.template get<signed int>());
        break;
    case traits<unsigned int>::value:
        storage = std::move(other.storage.template get<unsigned int>());
        break;
    case traits<signed long int>::value:
        storage = std::move(other.storage.template get<signed long int>());
        break;
    case traits<unsigned long int>::value:
        storage = std::move(other.storage.template get<unsigned long int>());
        break;
    case traits<signed long long int>::value:
        storage = std::move(other.storage.template get<signed long long int>());
        break;
    case traits<unsigned long long int>::value:
        storage = std::move(other.storage.template get<unsigned long long int>());
        break;
    case traits<float>::value:
        storage = std::move(other.storage.template get<float>());
        break;
    case traits<double>::value:
        storage = std::move(other.storage.template get<double>());
        break;
    case traits<long double>::value:
        storage = std::move(other.storage.template get<long double>());
        break;
    case traits<string_type>::value:
        storage = std::move(other.storage.template get<string_type>());
        break;
    case traits<array_type>::value:
        storage = std::move(other.storage.template get<array_type>());
        break;
    case traits<map_type>::value:
        storage = std::move(other.storage.template get<map_type>());
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
auto basic_variable<CharT>::operator+= (const basic_variable& other) -> basic_variable&
{
    switch (other.storage.which())
    {
    case traits<nullable>::value:
        detail::overloader<value_type, nullable>::
            append(*this, other.storage.template get<nullable>());
        break;
    case traits<bool>::value:
        detail::overloader<value_type, bool>::
            append(*this, other.storage.template get<bool>());
        break;
    case traits<signed short int>::value:
        detail::overloader<value_type, signed short int>::
            append(*this, other.storage.template get<signed short int>());
        break;
    case traits<unsigned short int>::value:
        detail::overloader<value_type, unsigned short int>::
            append(*this, other.storage.template get<unsigned short int>());
        break;
    case traits<signed int>::value:
        detail::overloader<value_type, signed int>::
            append(*this, other.storage.template get<signed int>());
        break;
    case traits<unsigned int>::value:
        detail::overloader<value_type, unsigned int>::
            append(*this, other.storage.template get<unsigned int>());
        break;
    case traits<signed long int>::value:
        detail::overloader<value_type, signed long int>::
            append(*this, other.storage.template get<signed long int>());
        break;
    case traits<unsigned long int>::value:
        detail::overloader<value_type, unsigned long int>::
            append(*this, other.storage.template get<unsigned long int>());
        break;
    case traits<signed long long int>::value:
        detail::overloader<value_type, signed long long int>::
            append(*this, other.storage.template get<signed long long int>());
        break;
    case traits<unsigned long long int>::value:
        detail::overloader<value_type, unsigned long long int>::
            append(*this, other.storage.template get<unsigned long long int>());
        break;
    case traits<float>::value:
        detail::overloader<value_type, float>::
            append(*this, other.storage.template get<float>());
        break;
    case traits<double>::value:
        detail::overloader<value_type, double>::
            append(*this, other.storage.template get<double>());
        break;
    case traits<long double>::value:
        detail::overloader<value_type, long double>::
            append(*this, other.storage.template get<long double>());
        break;
    case traits<string_type>::value:
        detail::overloader<value_type, string_type>::
            append(*this, other.storage.template get<string_type>());
        break;
    case traits<array_type>::value:
        detail::overloader<value_type, array_type>::
            append(*this, other.storage.template get<array_type>());
        break;
    case traits<map_type>::value:
        detail::overloader<value_type, map_type>::
            append(*this, other.storage.template get<map_type>());
        break;
    }
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator+= (std::initializer_list<typename array_type::value_type> init) -> basic_variable&
{
    switch (storage.which())
    {
    case traits<array_type>::value:
        {
            auto& array = storage.template get<array_type>();
            array.insert(array.end(), init.begin(), init.end());
        }
        break;

    default:
        throw dynamic::error(incompatible_type);
    }
    return *this;
}

template <typename CharT>
auto basic_variable<CharT>::operator+= (std::initializer_list<typename map_type::value_type> init) -> basic_variable&
{
    switch (storage.which())
    {
    case traits<map_type>::value:
        storage.template get<map_type>().insert(init);
        break;

    default:
        throw dynamic::error(incompatible_type);
    }
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
        throw std::system_error(error);
    return result;
}

template <typename CharT>
basic_variable<CharT>::operator bool() const
{
    switch (storage.which())
    {
    case traits<nullable>::value:
        return false;

    case traits<bool>::value:
        return bool(storage.template get<bool>());

    case traits<signed short int>::value:
        return bool(storage.template get<signed short int>());

    case traits<unsigned short int>::value:
        return bool(storage.template get<unsigned short int>());

    case traits<signed int>::value:
        return bool(storage.template get<signed int>());

    case traits<unsigned int>::value:
        return bool(storage.template get<unsigned int>());

    case traits<signed long int>::value:
        return bool(storage.template get<signed long int>());

    case traits<unsigned long int>::value:
        return bool(storage.template get<unsigned long int>());

    case traits<signed long long int>::value:
        return bool(storage.template get<signed long long int>());

    case traits<unsigned long long int>::value:
        return bool(storage.template get<unsigned long long int>());

    case traits<float>::value:
        return bool(storage.template get<float>());

    case traits<double>::value:
        return bool(storage.template get<double>());

    case traits<long double>::value:
        return bool(storage.template get<long double>());

    case traits<string_type>::value:
    case traits<array_type>::value:
    case traits<map_type>::value:
        // C++ containers are not contextually convertible to bool, but we
        // make them so for variable to let the code compiler for non-container
        // types.
        // FIXME: Throw an exception instead?
        return false;
    }
    assert(false);
    return false;
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (typename array_type::size_type position) -> basic_variable&
{
    switch (storage.which())
    {
    case traits<array_type>::value:
        return storage.template get<array_type>()[position];

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (typename array_type::size_type position) const -> const basic_variable&
{
    switch (storage.which())
    {
    case traits<array_type>::value:
        return storage.template get<array_type>().at(position);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (const typename map_type::key_type& key) -> basic_variable&
{
    switch (storage.which())
    {
    case traits<map_type>::value:
        return storage.template get<map_type>()[key];

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
auto basic_variable<CharT>::operator[] (const typename map_type::key_type& key) const -> const basic_variable&
{
    switch (storage.which())
    {
    case traits<map_type>::value:
        return storage.template get<map_type>().at(key);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
template <typename Tag>
bool basic_variable<CharT>::is() const
{
    using tag_type = typename tag_traits<typename std::decay<Tag>::type>::type;
    return storage.template call<similar_visitor<tag_type>, bool>();
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::same() const
{
    return detail::same_overloader<CharT, T>::same(storage.which());
}

template <typename CharT>
token::code::value basic_variable<CharT>::code() const
{
    switch (storage.which())
    {
    case traits<nullable>::value:
        return token::code::null;
    case traits<bool>::value:
        return token::code::boolean;
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
        throw dynamic::error(incompatible_type);
    }
}

template <typename CharT>
token::symbol::value basic_variable<CharT>::symbol() const
{
    return token::symbol::convert(code());
}

template <typename CharT>
bool basic_variable<CharT>::empty() const
{
    switch (storage.which())
    {
    case traits<nullable>::value:
        return true;
    case traits<bool>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
        return false;
    case traits<string_type>::value:
        return storage.template get<string_type>().empty();
    case traits<array_type>::value:
        return storage.template get<array_type>().empty();
    case traits<map_type>::value:
        return storage.template get<map_type>().empty();
    }
    assert(false);
    throw dynamic::error(incompatible_type);
}

template <typename CharT>
auto basic_variable<CharT>::size() const -> size_type
{
    switch (storage.which())
    {
    case traits<nullable>::value:
        return 0;
    case traits<bool>::value:
    case traits<signed short int>::value:
    case traits<unsigned short int>::value:
    case traits<signed int>::value:
    case traits<unsigned int>::value:
    case traits<signed long int>::value:
    case traits<unsigned long int>::value:
    case traits<signed long long int>::value:
    case traits<unsigned long long int>::value:
    case traits<float>::value:
    case traits<double>::value:
    case traits<long double>::value:
        return 1;
    case traits<string_type>::value:
        return storage.template get<string_type>().size();
    case traits<array_type>::value:
        return storage.template get<array_type>().size();
    case traits<map_type>::value:
        return storage.template get<map_type>().size();
    }
    assert(false);
    throw dynamic::error(incompatible_type);
}

template <typename CharT>
void basic_variable<CharT>::clear()
{
    switch (storage.which())
    {
    case traits<nullable>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = bool{};
        break;
    case traits<signed short int>::value:
        {
            signed short int value = 0;
            storage = value;
        }
        break;
    case traits<unsigned short int>::value:
        {
            unsigned short int value = 0U;
            storage = value;
        }
        break;
    case traits<signed int>::value:
        storage = 0;
        break;
    case traits<unsigned int>::value:
        storage = 0U;
        break;
    case traits<signed long int>::value:
        storage = 0L;
        break;
    case traits<unsigned long int>::value:
        storage = 0UL;
        break;
    case traits<signed long long int>::value:
        storage = 0LL;
        break;
    case traits<unsigned long long int>::value:
        storage = 0ULL;
        break;
    case traits<float>::value:
        storage = 0.0f;
        break;
    case traits<double>::value:
        storage = 0.0;
        break;
    case traits<long double>::value:
        storage = 0.0L;
        break;
    case traits<string_type>::value:
        storage.template get<string_type>().clear();
        break;
    case traits<array_type>::value:
        storage.template get<array_type>().clear();
        break;
    case traits<map_type>::value:
        storage.template get<map_type>().clear();
        break;
    }
}

template <typename CharT>
auto basic_variable<CharT>::erase(const_iterator where) -> iterator
{
    using array_iterator = typename basic_variable<CharT>::const_iterator::array_iterator;
    using map_iterator = typename basic_variable<CharT>::const_iterator::map_iterator;

    iterator result = where;

    switch (storage.which())
    {
    case traits<array_type>::value:
        {
            auto& array = storage.template get<array_type>();
            auto& array_where = where.current.template get<array_iterator>();
            result.current = array.erase(array_where);
        }
        break;

    case traits<map_type>::value:
        result.current =
            storage.template get<map_type>().erase(where.current.template get<map_iterator>());
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

    switch (storage.which())
    {
    case traits<array_type>::value:
        result.current =
            storage.template get<array_type>().erase(first.current.template get<array_iterator>(),
                                                     last.current.template get<array_iterator>());
        break;

    case traits<map_type>::value:
        result.current =
            storage.template get<map_type>().erase(first.current.template get<map_iterator>(),
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

// Comparison

template <typename T, typename U>
bool operator== (const T& lhs, const U& rhs)
{
    return detail::operator_overloader<T, U>::equal(lhs, rhs);
}

template <typename T, typename U>
bool operator!= (const T& lhs, const U& rhs)
{
    return !(lhs == rhs);
}

template <typename T, typename U>
bool operator< (const T& lhs, const U& rhs)
{
    return detail::operator_overloader<T, U>::less(lhs, rhs);
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::operator<= (const T& rhs) const
{
    if (same<nullable>())
        return true;

    return !(rhs < *this);
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::operator> (const T& rhs) const
{
    if (same<nullable>())
        return false;

    return rhs < *this;
}

template <typename CharT>
template <typename T>
bool basic_variable<CharT>::operator>= (const T& rhs) const
{
    return !(*this < rhs);
}

} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_DETAIL_VARIABLE_IPP
