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
using is_null = std::is_same<T, variable::null_type>;

template <typename T>
using is_boolean = protocol::detail::is_bool<T>;

template <typename T>
using is_integer = typename std::conditional<std::is_integral<T>::value && !detail::is_boolean<T>::value,
                                             std::true_type,
                                             std::false_type>::type;

template <typename T>
using is_number = std::is_floating_point<T>;

template <typename T>
using is_string = std::is_same<T, variable::string_type>;

template <typename T>
using is_array = std::is_same<T, variable::array_type>;

template <typename T>
using is_map = std::is_same<T, variable::map_type>;

} // namespace detail

//-----------------------------------------------------------------------------
// variable::traits
//-----------------------------------------------------------------------------

template <typename T>
struct variable::traits
{
    static const std::size_t value = decltype(variable::storage)::template index<T>::value;
};

//-----------------------------------------------------------------------------
// variable::overloader
//-----------------------------------------------------------------------------

template <typename T, typename Enable>
struct variable::overloader
{
    static_assert(sizeof(T) == 0, "Unsupported type");
};

// Null

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_null<T>::value>::type>
{
    using type = variable::null_type;
    using category_type = variable::null_type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            return {};

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T&)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            return true;

        default:
            return false;
        }
    }

    static bool less(const variable&, const T&)
    {
        // Null is smaller than anything
        return false;
    }

    static void append(variable&, const T&)
    {
        // Appending null is a no-op
    }
};

// Boolean

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_boolean<T>::value>::type>
{
    using type = bool;
    using category_type = type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>();

        case traits<signed short int>::value:
            return self.storage.get<signed short int>();

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>();

        case traits<signed int>::value:
            return self.storage.get<signed int>();

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>();

        case traits<signed long int>::value:
            return self.storage.get<signed long int>();

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>();

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>();

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>();

        case traits<float>::value:
            return self.storage.get<float>();

        case traits<double>::value:
            return self.storage.get<double>();

        case traits<long double>::value:
            return self.storage.get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>() == other;

        case traits<signed short int>::value:
            return self.storage.get<signed short int>() == other;

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>() == other;

        case traits<signed int>::value:
            return self.storage.get<signed int>() == other;

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>() == other;

        case traits<signed long int>::value:
            return self.storage.get<signed long int>() == other;

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>() == other;

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>() == other;

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>() == other;

        case traits<float>::value:
            return self.storage.get<float>() == other;

        case traits<double>::value:
            return self.storage.get<double>() == other;

        case traits<long double>::value:
            return self.storage.get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            return true;

        case traits<bool>::value:
            return self.storage.get<bool>() < other;

        case traits<signed short int>::value:
            return self.storage.get<signed short int>() < other;

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>() < other;

        case traits<signed int>::value:
            return self.storage.get<signed int>() < other;

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>() < other;

        case traits<signed long int>::value:
            return self.storage.get<signed long int>() < other;

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>() < other;

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>() < other;

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>() < other;

        case traits<float>::value:
            return self.storage.get<float>() < other;

        case traits<double>::value:
            return self.storage.get<double>() < other;

        case traits<long double>::value:
            return self.storage.get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            self.storage = other; // Overwrite null
            break;

        case traits<bool>::value:
            self.storage.get<bool>() += other;
            break;

        case traits<signed short int>::value:
            self.storage.get<signed short int>() += other;
            break;

        case traits<unsigned short int>::value:
            self.storage.get<unsigned short int>() += other;
            break;

        case traits<signed int>::value:
            self.storage.get<signed int>() += other;
            break;

        case traits<unsigned int>::value:
            self.storage.get<unsigned int>() += other;
            break;

        case traits<signed long int>::value:
            self.storage.get<signed long int>() += other;
            break;

        case traits<unsigned long int>::value:
            self.storage.get<unsigned long int>() += other;
            break;

        case traits<signed long long int>::value:
            self.storage.get<signed long long int>() += other;
            break;

        case traits<unsigned long long int>::value:
            self.storage.get<unsigned long long int>() += other;
            break;

        case traits<float>::value:
            self.storage.get<float>() += other;
            break;

        case traits<double>::value:
            self.storage.get<double>() += other;
            break;

        case traits<long double>::value:
            self.storage.get<long double>() += other;
            break;

        case traits<variable::array_type>::value:
            self.storage.get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Signed integer

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_integer<T>::value &&
                                                       std::is_signed<T>::value>::type>
{
    using type = T;
    using category_type = int;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>();

        case traits<signed short int>::value:
            return self.storage.get<signed short int>();

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>();

        case traits<signed int>::value:
            return self.storage.get<signed int>();

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>();

        case traits<signed long int>::value:
            return self.storage.get<signed long int>();

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>();

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>();

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>();

        case traits<float>::value:
            return self.storage.get<float>();

        case traits<double>::value:
            return self.storage.get<double>();

        case traits<long double>::value:
            return self.storage.get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>() == other;

        case traits<signed short int>::value:
        case traits<unsigned short int>::value:
            return self.storage.get<signed short int>() == other;

        case traits<signed int>::value:
        case traits<unsigned int>::value:
            return self.storage.get<signed int>() == other;

        case traits<signed long int>::value:
        case traits<unsigned long int>::value:
            return self.storage.get<signed long int>() == other;

        case traits<signed long long int>::value:
        case traits<unsigned long long int>::value:
            return self.storage.get<signed long long int>() == other;

        case traits<float>::value:
            return self.storage.get<float>() == other;

        case traits<double>::value:
            return self.storage.get<double>() == other;

        case traits<long double>::value:
            return self.storage.get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            return true;

        case traits<bool>::value:
            return self.storage.get<bool>() < other;

        case traits<signed short int>::value:
        case traits<unsigned short int>::value:
            return self.storage.get<signed short int>() < other;

        case traits<signed int>::value:
        case traits<unsigned int>::value:
            return self.storage.get<signed int>() < other;

        case traits<signed long int>::value:
        case traits<unsigned long int>::value:
            return self.storage.get<signed long int>() < other;

        case traits<signed long long int>::value:
        case traits<unsigned long long int>::value:
            return self.storage.get<signed long long int>() < other;

        case traits<float>::value:
            return self.storage.get<float>() < other;

        case traits<double>::value:
            return self.storage.get<double>() < other;

        case traits<long double>::value:
            return self.storage.get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            self.storage = other; // Overwrite null
            break;

        case traits<bool>::value:
            self.storage.get<bool>() += other;
            break;

        case traits<signed short int>::value:
            self.storage.get<signed short int>() += other;
            break;

        case traits<unsigned short int>::value:
            self.storage.get<unsigned short int>() += other;
            break;

        case traits<signed int>::value:
            self.storage.get<signed int>() += other;
            break;

        case traits<unsigned int>::value:
            self.storage.get<unsigned int>() += other;
            break;

        case traits<signed long int>::value:
            self.storage.get<signed long int>() += other;
            break;

        case traits<unsigned long int>::value:
            self.storage.get<unsigned long int>() += other;
            break;

        case traits<signed long long int>::value:
            self.storage.get<signed long long int>() += other;
            break;

        case traits<unsigned long long int>::value:
            self.storage.get<unsigned long long int>() += other;
            break;

        case traits<float>::value:
            self.storage.get<float>() += other;
            break;

        case traits<double>::value:
            self.storage.get<double>() += other;
            break;

        case traits<long double>::value:
            self.storage.get<long double>() += other;
            break;

        case traits<variable::array_type>::value:
            self.storage.get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Unsigned integer

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_integer<T>::value &&
                                                       std::is_unsigned<T>::value>::type>
{
    using type = T;
    using category_type = int;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>();

        case traits<signed short int>::value:
            return self.storage.get<signed short int>();

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>();

        case traits<signed int>::value:
            return self.storage.get<signed int>();

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>();

        case traits<signed long int>::value:
            return self.storage.get<signed long int>();

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>();

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>();

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>();

        case traits<float>::value:
            return self.storage.get<float>();

        case traits<double>::value:
            return self.storage.get<double>();

        case traits<long double>::value:
            return self.storage.get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>() == other;

        case traits<signed short int>::value:
        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>() == other;

        case traits<signed int>::value:
        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>() == other;

        case traits<signed long int>::value:
        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>() == other;

        case traits<signed long long int>::value:
        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>() == other;

        case traits<float>::value:
            return self.storage.get<float>() == other;

        case traits<double>::value:
            return self.storage.get<double>() == other;

        case traits<long double>::value:
            return self.storage.get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            return true;

        case traits<bool>::value:
            return self.storage.get<bool>() < other;

        case traits<signed short int>::value:
        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>() < other;

        case traits<signed int>::value:
        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>() < other;

        case traits<signed long int>::value:
        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>() < other;

        case traits<signed long long int>::value:
        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>() < other;

        case traits<float>::value:
            return self.storage.get<float>() < other;

        case traits<double>::value:
            return self.storage.get<double>() < other;

        case traits<long double>::value:
            return self.storage.get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            self.storage = other; // Overwrite null
            break;

        case traits<bool>::value:
            self.storage.get<bool>() += other;
            break;

        case traits<signed short int>::value:
            self.storage.get<signed short int>() += other;
            break;

        case traits<unsigned short int>::value:
            self.storage.get<unsigned short int>() += other;
            break;

        case traits<signed int>::value:
            self.storage.get<signed int>() += other;
            break;

        case traits<unsigned int>::value:
            self.storage.get<unsigned int>() += other;
            break;

        case traits<signed long int>::value:
            self.storage.get<signed long int>() += other;
            break;

        case traits<unsigned long int>::value:
            self.storage.get<unsigned long int>() += other;
            break;

        case traits<signed long long int>::value:
            self.storage.get<signed long long int>() += other;
            break;

        case traits<unsigned long long int>::value:
            self.storage.get<unsigned long long int>() += other;
            break;

        case traits<float>::value:
            self.storage.get<float>() += other;
            break;

        case traits<double>::value:
            self.storage.get<double>() += other;
            break;

        case traits<long double>::value:
            self.storage.get<long double>() += other;
            break;

        case traits<variable::array_type>::value:
            self.storage.get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Floating-point

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_number<T>::value>::type>
{
    using type = T;
    using category_type = float;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>();

        case traits<signed short int>::value:
            return self.storage.get<signed short int>();

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>();

        case traits<signed int>::value:
            return self.storage.get<signed int>();

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>();

        case traits<signed long int>::value:
            return self.storage.get<signed long int>();

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>();

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>();

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>();

        case traits<float>::value:
            return self.storage.get<float>();

        case traits<double>::value:
            return self.storage.get<double>();

        case traits<long double>::value:
            return self.storage.get<long double>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<bool>::value:
            return self.storage.get<bool>() == other;

        case traits<signed short int>::value:
            return self.storage.get<signed short int>() == other;

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>() == other;

        case traits<signed int>::value:
            return self.storage.get<signed int>() == other;

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>() == other;

        case traits<signed long int>::value:
            return self.storage.get<signed long int>() == other;

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>() == other;

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>() == other;

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>() == other;

        case traits<float>::value:
            return self.storage.get<float>() == other;

        case traits<double>::value:
            return self.storage.get<double>() == other;

        case traits<long double>::value:
            return self.storage.get<long double>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            return true;

        case traits<bool>::value:
            return self.storage.get<bool>() < other;

        case traits<signed short int>::value:
            return self.storage.get<signed short int>() < other;

        case traits<unsigned short int>::value:
            return self.storage.get<unsigned short int>() < other;

        case traits<signed int>::value:
            return self.storage.get<signed int>() < other;

        case traits<unsigned int>::value:
            return self.storage.get<unsigned int>() < other;

        case traits<signed long int>::value:
            return self.storage.get<signed long int>() < other;

        case traits<unsigned long int>::value:
            return self.storage.get<unsigned long int>() < other;

        case traits<signed long long int>::value:
            return self.storage.get<signed long long int>() < other;

        case traits<unsigned long long int>::value:
            return self.storage.get<unsigned long long int>() < other;

        case traits<float>::value:
            return self.storage.get<float>() < other;

        case traits<double>::value:
            return self.storage.get<double>() < other;

        case traits<long double>::value:
            return self.storage.get<long double>() < other;

        default:
            return false;
        }
    }

    static void append(variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            self.storage = other; // Overwrite null
            break;

        case traits<bool>::value:
            self.storage.get<bool>() += other;
            break;

        case traits<signed short int>::value:
            self.storage.get<signed short int>() += other;
            break;

        case traits<unsigned short int>::value:
            self.storage.get<unsigned short int>() += other;
            break;

        case traits<signed int>::value:
            self.storage.get<signed int>() += other;
            break;

        case traits<unsigned int>::value:
            self.storage.get<unsigned int>() += other;
            break;

        case traits<signed long int>::value:
            self.storage.get<signed long int>() += other;
            break;

        case traits<unsigned long int>::value:
            self.storage.get<unsigned long int>() += other;
            break;

        case traits<signed long long int>::value:
            self.storage.get<signed long long int>() += other;
            break;

        case traits<unsigned long long int>::value:
            self.storage.get<unsigned long long int>() += other;
            break;

        case traits<float>::value:
            self.storage.get<float>() += other;
            break;

        case traits<double>::value:
            self.storage.get<double>() += other;
            break;

        case traits<long double>::value:
            self.storage.get<long double>() += other;
            break;

        case traits<variable::array_type>::value:
            self.storage.get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// String

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_string<T>::value>::type>
{
    using type = variable::string_type;
    using category_type = variable::string_type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<variable::string_type>::value:
            return self.storage.get<variable::string_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::string_type>::value:
            return self.storage.get<string_type>() == other;

        default:
            return false;
        }
    }

    static bool less(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::string_type>::value:
            return self.storage.get<string_type>() < other;

        case traits<variable::array_type>::value:
        case traits<variable::map_type>::value:
            return false;

        default:
            return true;
        }
    }

    static void append(variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            self.storage = other; // Overwrite null
            break;

        case traits<variable::string_type>::value:
            self.storage.get<string_type>() += other;
            break;

        case traits<variable::array_type>::value:
            self.storage.get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Array

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_array<T>::value>::type>
{
    using type = variable::array_type;
    using category_type = variable::array_type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<variable::array_type>::value:
            return self.storage.get<variable::array_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::array_type>::value:
            {
                const auto& array = self.storage.get<variable::array_type>();
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

    static bool less(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::array_type>::value:
            {
                const auto& array = self.storage.get<variable::array_type>();
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

        case traits<variable::map_type>::value:
            return false;

        default:
            return true;
        }
    }

    static void append(variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            self.storage = other; // Overwrite null
            break;

        case traits<variable::array_type>::value:
            {
                auto& array = self.storage.get<array_type>();
                array.insert(array.end(), other.begin(), other.end());
            }
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Map

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_map<T>::value>::type>
{
    using type = variable::map_type;
    using category_type = variable::map_type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<variable::map_type>::value:
            return self.storage.get<variable::map_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::map_type>::value:
            {
                const auto& map = self.storage.get<variable::map_type>();
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

    static bool less(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::map_type>::value:
            {
                const auto& map = self.storage.get<variable::map_type>();
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

    static void append(variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            self.storage = other; // Overwrite null
            break;

        case traits<variable::map_type>::value:
            {
                auto& map = self.storage.get<map_type>();
                map.insert(other.begin(), other.end());
            }
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

//-----------------------------------------------------------------------------
// variable::same_overloader
//-----------------------------------------------------------------------------

// The specialized template capture qualifications removed during template
// argument deduction to ensure that only the exact type is matched in the
// general case.
//
// For example:
//   variable data(0.0f);
//   assert(data.same<float>(), true);
//   assert(data.same<float&>(), false);
//   assert(data.same<const float>(), false);

template <typename T, typename Enable>
struct variable::same_overloader
{
    static bool same(std::size_t which)
    {
        return which == traits<T>::value;
    }
};

template <typename T>
struct variable::same_overloader<T,
                                 typename std::enable_if<std::is_const<T>::value ||
                                                         std::is_volatile<T>::value ||
                                                         std::is_reference<T>::value>::type>
{
    static bool same(std::size_t)
    {
        return false;
    }
};

//-----------------------------------------------------------------------------
// variable::iterator_type
//-----------------------------------------------------------------------------

template <typename T>
variable::iterator_type<T>::iterator_type()
    : scope(nullptr),
      current(pointer(nullptr))
{
}

template <typename T>
variable::iterator_type<T>::iterator_type(const iterator_type& other)
    : scope(other.scope),
      current(other.current)
{
}

template <typename T>
variable::iterator_type<T>::iterator_type(iterator_type&& other)
    : scope(std::move(other.scope)),
      current(std::move(other.current))
{
}

template <typename T>
variable::iterator_type<T>::iterator_type(pointer p,
                                          bool initialize)
    : scope(p),
      current(pointer(nullptr))
{
    switch (scope->storage.which())
    {
    case traits<null_type>::value:
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

template <typename T>
template <typename U>
variable::iterator_type<T>::iterator_type(const iterator_type<typename std::remove_const<U>::type>& other,
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

template <typename T>
template <typename U>
variable::iterator_type<T>::iterator_type(const iterator_type<typename std::add_const<U>::type>& other,
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

template <typename T>
auto variable::iterator_type<T>::operator= (const iterator_type& other) -> iterator_type&
{
    scope = other.scope;
    current = other.current;
    return *this;
}

template <typename T>
auto variable::iterator_type<T>::operator= (iterator_type&& other) -> iterator_type&
{
    scope = std::move(other.scope);
    current = std::move(other.current);
    return *this;
}

template <typename T>
auto variable::iterator_type<T>::operator++ () -> iterator_type&
{
    assert(scope);

    switch (scope->storage.which())
    {
    case traits<null_type>::value:
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

template <typename T>
auto variable::iterator_type<T>::operator++ (int) -> iterator_type
{
    assert(scope);

    iterator_type result = *this;
    ++(*this);
    return result;
}

template <typename T>
auto variable::iterator_type<T>::operator* () -> reference
{
    assert(scope);

    return value();
}

template <typename T>
auto variable::iterator_type<T>::key() const -> key_reference
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

template <typename T>
auto variable::iterator_type<T>::value() -> reference
{
    assert(scope);

    switch (scope->storage.which())
    {
    case traits<null_type>::value:
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

template <typename T>
auto variable::iterator_type<T>::operator-> () -> pointer
{
    assert(scope);

    switch (scope->storage.which())
    {
    case traits<null_type>::value:
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

template <typename T>
bool variable::iterator_type<T>::operator== (const iterator_type<T>& other)
{
    if (!scope)
        return !other.scope;
    if (!other.scope)
        return false;

    assert(scope->storage.which() == other.scope->storage.which());

    switch (scope->storage.which())
    {
    case traits<null_type>::value:
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

template <typename T>
bool variable::iterator_type<T>::operator!= (const iterator_type<T>& other)
{
    return !(*this == other);
}

//-----------------------------------------------------------------------------
// visitors
//-----------------------------------------------------------------------------

template <typename T>
struct variable::similar_visitor
{
    template <typename Which>
    static bool call(const storage_type&)
    {
        return std::is_same<typename variable::overloader<T>::category_type,
                            typename variable::overloader<Which>::category_type>::value;
    }
};

//-----------------------------------------------------------------------------
// variable
//-----------------------------------------------------------------------------

inline variable::variable()
    : storage(null)
{
}

inline variable::variable(const variable& other)
    : storage(null)
{
    switch (other.storage.which())
    {
    case traits<null_type>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = other.storage.get<bool>();
        break;
    case traits<signed short int>::value:
        storage = other.storage.get<signed short int>();
        break;
    case traits<unsigned short int>::value:
        storage = other.storage.get<unsigned short int>();
        break;
    case traits<signed int>::value:
        storage = other.storage.get<signed int>();
        break;
    case traits<unsigned int>::value:
        storage = other.storage.get<unsigned int>();
        break;
    case traits<signed long int>::value:
        storage = other.storage.get<signed long int>();
        break;
    case traits<unsigned long int>::value:
        storage = other.storage.get<unsigned long int>();
        break;
    case traits<signed long long int>::value:
        storage = other.storage.get<signed long long int>();
        break;
    case traits<unsigned long long int>::value:
        storage = other.storage.get<unsigned long long int>();
        break;
    case traits<float>::value:
        storage = other.storage.get<float>();
        break;
    case traits<double>::value:
        storage = other.storage.get<double>();
        break;
    case traits<long double>::value:
        storage = other.storage.get<long double>();
        break;
    case traits<string_type>::value:
        storage = other.storage.get<string_type>();
        break;
    case traits<array_type>::value:
        storage = other.storage.get<array_type>();
        break;
    case traits<map_type>::value:
        storage = other.storage.get<map_type>();
        break;
    default:
        assert(false);
        break;
    }
}

inline variable::variable(variable&& other)
    : storage(null)
{
    switch (other.storage.which())
    {
    case traits<null_type>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = std::move(other.storage.get<bool>());
        break;
    case traits<signed short int>::value:
        storage = std::move(other.storage.get<signed short int>());
        break;
    case traits<unsigned short int>::value:
        storage = std::move(other.storage.get<unsigned short int>());
        break;
    case traits<signed int>::value:
        storage = std::move(other.storage.get<signed int>());
        break;
    case traits<unsigned int>::value:
        storage = std::move(other.storage.get<unsigned int>());
        break;
    case traits<signed long int>::value:
        storage = std::move(other.storage.get<signed long int>());
        break;
    case traits<unsigned long int>::value:
        storage = std::move(other.storage.get<unsigned long int>());
        break;
    case traits<signed long long int>::value:
        storage = std::move(other.storage.get<signed long long int>());
        break;
    case traits<unsigned long long int>::value:
        storage = std::move(other.storage.get<unsigned long long int>());
        break;
    case traits<float>::value:
        storage = std::move(other.storage.get<float>());
        break;
    case traits<double>::value:
        storage = std::move(other.storage.get<double>());
        break;
    case traits<long double>::value:
        storage = std::move(other.storage.get<long double>());
        break;
    case traits<string_type>::value:
        storage = std::move(other.storage.get<string_type>());
        break;
    case traits<array_type>::value:
        storage = std::move(other.storage.get<array_type>());
        break;
    case traits<map_type>::value:
        storage = std::move(other.storage.get<map_type>());
        break;
    default:
        assert(false);
        break;
    }
}

template <typename T>
variable::variable(T value)
    : storage(typename overloader<typename std::decay<T>::type>::type(std::move(value)))
{
}

inline variable::variable(null_type)
    : storage(null)
{
}

inline variable::variable(const string_type::value_type *value)
    : storage(string_type(value))
{
}

inline variable variable::array()
{
    variable result;
    result.storage = array_type{};
    return result;
}

template <typename ForwardIterator>
variable variable::array(ForwardIterator begin, ForwardIterator end)
{
    variable result;
    result.storage = array_type(begin, end);
    return result;
}

inline variable variable::array(std::initializer_list<array_type::value_type> init)
{
    variable result;
    result.storage = array_type(init.begin(), init.end());
    return result;
}

template <typename T>
variable variable::array(size_type size, const T& value)
{
    variable result;
    result.storage = array_type(size, variable(value));
    return result;
}

inline variable variable::map()
{
    variable result;
    result.storage = map_type{};
    return result;
}

inline variable variable::map(std::initializer_list<map_type::value_type> init)
{
    variable result;
    result.storage = map_type(init.begin(), init.end());
    return result;
}

inline variable& variable::operator= (const variable& other)
{
    switch (other.storage.which())
    {
    case traits<null_type>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = other.storage.get<bool>();
        break;
    case traits<signed short int>::value:
        storage = other.storage.get<signed short int>();
        break;
    case traits<unsigned short int>::value:
        storage = other.storage.get<unsigned short int>();
        break;
    case traits<signed int>::value:
        storage = other.storage.get<signed int>();
        break;
    case traits<unsigned int>::value:
        storage = other.storage.get<unsigned int>();
        break;
    case traits<signed long int>::value:
        storage = other.storage.get<signed long int>();
        break;
    case traits<unsigned long int>::value:
        storage = other.storage.get<unsigned long int>();
        break;
    case traits<signed long long int>::value:
        storage = other.storage.get<signed long long int>();
        break;
    case traits<unsigned long long int>::value:
        storage = other.storage.get<unsigned long long int>();
        break;
    case traits<float>::value:
        storage = other.storage.get<float>();
        break;
    case traits<double>::value:
        storage = other.storage.get<double>();
        break;
    case traits<long double>::value:
        storage = other.storage.get<long double>();
        break;
    case traits<string_type>::value:
        storage = other.storage.get<string_type>();
        break;
    case traits<array_type>::value:
        storage = other.storage.get<array_type>();
        break;
    case traits<map_type>::value:
        storage = other.storage.get<map_type>();
        break;
    default:
        assert(false);
        break;
    }
    return *this;
}

inline variable& variable::operator= (variable&& other)
{
    switch (other.storage.which())
    {
    case traits<null_type>::value:
        storage = null;
        break;
    case traits<bool>::value:
        storage = std::move(other.storage.get<bool>());
        break;
    case traits<signed short int>::value:
        storage = std::move(other.storage.get<signed short int>());
        break;
    case traits<unsigned short int>::value:
        storage = std::move(other.storage.get<unsigned short int>());
        break;
    case traits<signed int>::value:
        storage = std::move(other.storage.get<signed int>());
        break;
    case traits<unsigned int>::value:
        storage = std::move(other.storage.get<unsigned int>());
        break;
    case traits<signed long int>::value:
        storage = std::move(other.storage.get<signed long int>());
        break;
    case traits<unsigned long int>::value:
        storage = std::move(other.storage.get<unsigned long int>());
        break;
    case traits<signed long long int>::value:
        storage = std::move(other.storage.get<signed long long int>());
        break;
    case traits<unsigned long long int>::value:
        storage = std::move(other.storage.get<unsigned long long int>());
        break;
    case traits<float>::value:
        storage = std::move(other.storage.get<float>());
        break;
    case traits<double>::value:
        storage = std::move(other.storage.get<double>());
        break;
    case traits<long double>::value:
        storage = std::move(other.storage.get<long double>());
        break;
    case traits<string_type>::value:
        storage = std::move(other.storage.get<string_type>());
        break;
    case traits<array_type>::value:
        storage = std::move(other.storage.get<array_type>());
        break;
    case traits<map_type>::value:
        storage = std::move(other.storage.get<map_type>());
        break;
    }
    return *this;
}

template <typename T>
variable& variable::operator= (T value)
{
    storage = typename overloader<T>::type{std::move(value)};
    return *this;
}

inline variable& variable::operator= (null_type)
{
    storage = null;
    return *this;
}

inline variable& variable::operator= (const string_type::value_type *value)
{
    storage = string_type{value};
    return *this;
}

inline variable& variable::operator+= (const variable& other)
{
    switch (other.storage.which())
    {
    case traits<null_type>::value:
        overloader<null_type>::append(*this, other.storage.get<null_type>());
        break;
    case traits<bool>::value:
        overloader<bool>::append(*this, other.storage.get<bool>());
        break;
    case traits<signed short int>::value:
        overloader<signed short int>::append(*this, other.storage.get<signed short int>());
        break;
    case traits<unsigned short int>::value:
        overloader<unsigned short int>::append(*this, other.storage.get<unsigned short int>());
        break;
    case traits<signed int>::value:
        overloader<signed int>::append(*this, other.storage.get<signed int>());
        break;
    case traits<unsigned int>::value:
        overloader<unsigned int>::append(*this, other.storage.get<unsigned int>());
        break;
    case traits<signed long int>::value:
        overloader<signed long int>::append(*this, other.storage.get<signed long int>());
        break;
    case traits<unsigned long int>::value:
        overloader<unsigned long int>::append(*this, other.storage.get<unsigned long int>());
        break;
    case traits<signed long long int>::value:
        overloader<signed long long int>::append(*this, other.storage.get<signed long long int>());
        break;
    case traits<unsigned long long int>::value:
        overloader<unsigned long long int>::append(*this, other.storage.get<unsigned long long int>());
        break;
    case traits<float>::value:
        overloader<float>::append(*this, other.storage.get<float>());
        break;
    case traits<double>::value:
        overloader<double>::append(*this, other.storage.get<double>());
        break;
    case traits<long double>::value:
        overloader<long double>::append(*this, other.storage.get<long double>());
        break;
    case traits<string_type>::value:
        overloader<string_type>::append(*this, other.storage.get<string_type>());
        break;
    case traits<array_type>::value:
        overloader<array_type>::append(*this, other.storage.get<array_type>());
        break;
    case traits<map_type>::value:
        overloader<map_type>::append(*this, other.storage.get<map_type>());
        break;
    }
    return *this;
}

inline variable& variable::operator+= (std::initializer_list<array_type::value_type> init)
{
    switch (storage.which())
    {
    case traits<array_type>::value:
        {
            auto& array = storage.get<array_type>();
            array.insert(array.end(), init.begin(), init.end());
        }
        break;

    default:
        throw dynamic::error(incompatible_type);
    }
    return *this;
}

inline variable& variable::operator+= (std::initializer_list<map_type::value_type> init)
{
    switch (storage.which())
    {
    case traits<map_type>::value:
        storage.get<map_type>().insert(init);
        break;

    default:
        throw dynamic::error(incompatible_type);
    }
    return *this;
}

template <typename T>
variable variable::operator+ (const T& rhs)
{
    variable result(*this);
    result += rhs;
    return result;
}

template <typename T>
variable operator+ (variable::null_type, const T& rhs)
{
    return variable() + rhs;
}

template <typename R>
variable::operator R() const
{
    return value<R>();
}

template <typename R>
R variable::value(std::error_code& error) const noexcept
{
    return overloader<R>::convert(*this, error);
}

template <typename R>
R variable::value() const
{
    std::error_code error;
    auto result = value<R>(error);
    if (error)
        throw std::system_error(error);
    return result;
}

inline variable::operator bool() const
{
    switch (storage.which())
    {
    case traits<null_type>::value:
        return false;

    case traits<bool>::value:
        return bool(storage.get<bool>());

    case traits<signed short int>::value:
        return bool(storage.get<signed short int>());

    case traits<unsigned short int>::value:
        return bool(storage.get<unsigned short int>());

    case traits<signed int>::value:
        return bool(storage.get<signed int>());

    case traits<unsigned int>::value:
        return bool(storage.get<unsigned int>());

    case traits<signed long int>::value:
        return bool(storage.get<signed long int>());

    case traits<unsigned long int>::value:
        return bool(storage.get<unsigned long int>());

    case traits<signed long long int>::value:
        return bool(storage.get<signed long long int>());

    case traits<unsigned long long int>::value:
        return bool(storage.get<unsigned long long int>());

    case traits<float>::value:
        return bool(storage.get<float>());

    case traits<double>::value:
        return bool(storage.get<double>());

    case traits<long double>::value:
        return bool(storage.get<long double>());

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

inline variable& variable::operator[] (array_type::size_type position)
{
    switch (storage.which())
    {
    case traits<array_type>::value:
        return storage.get<array_type>()[position];

    default:
        throw dynamic::error(incompatible_type);
    }
}

inline const variable& variable::operator[] (array_type::size_type position) const
{
    switch (storage.which())
    {
    case traits<array_type>::value:
        return storage.get<array_type>().at(position);

    default:
        throw dynamic::error(incompatible_type);
    }
}

inline variable& variable::operator[] (const map_type::key_type& key)
{
    switch (storage.which())
    {
    case traits<map_type>::value:
        return storage.get<map_type>()[key];

    default:
        throw dynamic::error(incompatible_type);
    }
}

inline const variable& variable::operator[] (const map_type::key_type& key) const
{
    switch (storage.which())
    {
    case traits<map_type>::value:
        return storage.get<map_type>().at(key);

    default:
        throw dynamic::error(incompatible_type);
    }
}

template <typename T>
bool variable::is() const
{
    return storage.call<similar_visitor<typename std::decay<T>::type>, bool>();
}

template <typename T>
bool variable::same() const
{
    return same_overloader<T>::same(storage.which());
}

inline token::code::value variable::code() const
{
    switch (storage.which())
    {
    case traits<null_type>::value:
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

inline token::symbol::value variable::symbol() const
{
    return token::symbol::convert(code());
}

inline bool variable::empty() const
{
    switch (storage.which())
    {
    case traits<null_type>::value:
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
        return storage.get<string_type>().empty();
    case traits<array_type>::value:
        return storage.get<array_type>().empty();
    case traits<map_type>::value:
        return storage.get<map_type>().empty();
    }
    assert(false);
    throw dynamic::error(incompatible_type);
}

inline auto variable::size() const -> size_type
{
    switch (storage.which())
    {
    case traits<null_type>::value:
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
        return storage.get<string_type>().size();
    case traits<array_type>::value:
        return storage.get<array_type>().size();
    case traits<map_type>::value:
        return storage.get<map_type>().size();
    }
    assert(false);
    throw dynamic::error(incompatible_type);
}

inline void variable::clear()
{
    switch (storage.which())
    {
    case traits<null_type>::value:
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
        storage.get<string_type>().clear();
        break;
    case traits<array_type>::value:
        storage.get<array_type>().clear();
        break;
    case traits<map_type>::value:
        storage.get<map_type>().clear();
        break;
    }
}

inline auto variable::erase(const_iterator where) -> iterator
{
    iterator result = where;

    switch (storage.which())
    {
    case traits<array_type>::value:
        result.current =
            storage.get<array_type>().erase(where.current.template get<iterator::array_iterator>());
        break;

    case traits<map_type>::value:
        result.current =
            storage.get<map_type>().erase(where.current.template get<iterator::map_iterator>());
        break;

    default:
        // Non-container types are unerasable
        break;
    }
    return result;
}

inline auto variable::erase(const_iterator first, const_iterator last) -> iterator
{
    iterator result = first;

    switch (storage.which())
    {
    case traits<array_type>::value:
        result.current =
            storage.get<array_type>().erase(first.current.template get<iterator::array_iterator>(),
                                            last.current.template get<iterator::array_iterator>());
        break;

    case traits<map_type>::value:
        result.current =
            storage.get<map_type>().erase(first.current.template get<iterator::map_iterator>(),
                                          last.current.template get<iterator::map_iterator>());
        break;

    default:
        // Non-container types are unerasable
        break;
    }
    return result;
}

inline auto variable::begin() & -> iterator
{
    return {this};
}

inline auto variable::begin() const & -> const_iterator
{
    return {this};
}

inline auto variable::end() & -> iterator
{
    return {this, false};
}

inline auto variable::end() const & -> const_iterator
{
    return {this, false};
}

// Comparison

template <typename T>
bool variable::operator== (const T& rhs) const
{
    return variable::overloader<T>::equal(*this, rhs);
}

inline bool operator== (const variable& lhs, const variable& rhs)
{
    switch (rhs.storage.which())
    {
    case variable::traits<variable::null_type>::value:
        return variable::overloader<variable::null_type>::
            equal(lhs, rhs.storage.get<variable::null_type>());

    case variable::traits<bool>::value:
        return variable::overloader<bool>::
            equal(lhs, rhs.storage.get<bool>());

    case variable::traits<signed short int>::value:
        return variable::overloader<signed short int>::
            equal(lhs, rhs.storage.get<signed short int>());

    case variable::traits<unsigned short int>::value:
        return variable::overloader<unsigned short int>::
            equal(lhs, rhs.storage.get<unsigned short int>());

    case variable::traits<signed int>::value:
        return variable::overloader<signed int>::
            equal(lhs, rhs.storage.get<signed int>());

    case variable::traits<unsigned int>::value:
        return variable::overloader<unsigned int>::
            equal(lhs, rhs.storage.get<unsigned int>());

    case variable::traits<signed long int>::value:
        return variable::overloader<signed long int>::
            equal(lhs, rhs.storage.get<signed long int>());

    case variable::traits<unsigned long int>::value:
        return variable::overloader<unsigned long int>::
            equal(lhs, rhs.storage.get<unsigned long int>());

    case variable::traits<signed long long int>::value:
        return variable::overloader<signed long long int>::
            equal(lhs, rhs.storage.get<signed long long int>());

    case variable::traits<unsigned long long int>::value:
        return variable::overloader<unsigned long long int>::
            equal(lhs, rhs.storage.get<unsigned long long int>());

    case variable::traits<float>::value:
        return variable::overloader<float>::
            equal(lhs, rhs.storage.get<float>());

    case variable::traits<double>::value:
        return variable::overloader<double>::
            equal(lhs, rhs.storage.get<double>());

    case variable::traits<long double>::value:
        return variable::overloader<long double>::
            equal(lhs, rhs.storage.get<long double>());

    case variable::traits<variable::string_type>::value:
        return variable::overloader<variable::string_type>::
            equal(lhs, rhs.storage.get<variable::string_type>());

    case variable::traits<variable::array_type>::value:
        return variable::overloader<variable::array_type>::
            equal(lhs, rhs.storage.get<variable::array_type>());

    case variable::traits<variable::map_type>::value:
        return variable::overloader<variable::map_type>::
            equal(lhs, rhs.storage.get<variable::map_type>());
    }
    return false;
}

inline bool operator== (const variable& lhs, const variable::string_type::value_type *rhs)
{
    return variable::overloader<variable::string_type>::equal(lhs, rhs);
}

template <typename T>
bool variable::operator< (const T& rhs) const
{
    return variable::overloader<T>::less(*this, rhs);
}

inline bool operator< (const variable& lhs, const variable& rhs)
{
    switch (rhs.storage.which())
    {
    case variable::traits<variable::null_type>::value:
        return variable::overloader<variable::null_type>::
            less(lhs, rhs.value<variable::null_type>());

    case variable::traits<bool>::value:
        return variable::overloader<bool>::
            less(lhs, rhs.storage.get<bool>());

    case variable::traits<signed short int>::value:
        return variable::overloader<signed short int>::
            less(lhs, rhs.storage.get<signed short int>());

    case variable::traits<unsigned short int>::value:
        return variable::overloader<unsigned short int>::
            less(lhs, rhs.storage.get<unsigned short int>());

    case variable::traits<signed int>::value:
        return variable::overloader<signed int>::
            less(lhs, rhs.storage.get<signed int>());

    case variable::traits<unsigned int>::value:
        return variable::overloader<unsigned int>::
            less(lhs, rhs.storage.get<unsigned int>());

    case variable::traits<signed long int>::value:
        return variable::overloader<signed long int>::
            less(lhs, rhs.storage.get<signed long int>());

    case variable::traits<unsigned long int>::value:
        return variable::overloader<unsigned long int>::
            less(lhs, rhs.storage.get<unsigned long int>());

    case variable::traits<signed long long int>::value:
        return variable::overloader<signed long long int>::
            less(lhs, rhs.storage.get<signed long long int>());

    case variable::traits<unsigned long long int>::value:
        return variable::overloader<unsigned long long int>::
            less(lhs, rhs.storage.get<unsigned long long int>());

    case variable::traits<float>::value:
        return variable::overloader<float>::less(lhs, rhs.storage.get<float>());

    case variable::traits<double>::value:
        return variable::overloader<double>::less(lhs, rhs.storage.get<double>());

    case variable::traits<long double>::value:
        return variable::overloader<long double>::less(lhs, rhs.storage.get<long double>());

    case variable::traits<variable::string_type>::value:
        return variable::overloader<variable::string_type>::
            less(lhs, rhs.storage.get<variable::string_type>());

    case variable::traits<variable::array_type>::value:
        return variable::overloader<variable::array_type>::
            less(lhs, rhs.storage.get<variable::array_type>());

    case variable::traits<variable::map_type>::value:
        return variable::overloader<variable::map_type>::
            less(lhs, rhs.storage.get<variable::map_type>());
    }
    return false;
}

inline bool operator< (const variable& lhs, const variable::string_type::value_type *rhs)
{
    return variable::overloader<variable::string_type>::less(lhs, rhs);
}

template <typename T>
bool variable::operator!= (const T& rhs) const
{
    return !(*this == rhs);
}

template <typename T>
bool variable::operator<= (const T& rhs) const
{
    if (is<variable::null_type>())
        return true;

    return !(rhs < *this);
}

template <typename T>
bool variable::operator> (const T& rhs) const
{
    if (is<variable::null_type>())
        return false;

    return rhs < *this;
}

template <typename T>
bool variable::operator>= (const T& rhs) const
{
    return !(*this < rhs);
}

} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_DETAIL_VARIABLE_IPP
