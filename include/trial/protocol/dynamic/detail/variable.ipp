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

    static bool less(const variable& self, const T&)
    {
        switch (self.storage.which())
        {
        case traits<variable::null_type>::value:
            return false;

        default:
            return true;
        }
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
    using type = variable::boolean_type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<variable::boolean_type>::value:
            return self.storage.get<variable::boolean_type>();

        case traits<variable::integer_type>::value:
            return self.storage.get<variable::integer_type>();

        case traits<variable::number_type>::value:
            return self.storage.get<variable::number_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::boolean_type>::value:
            return self.storage.get<boolean_type>() == other;

        case traits<variable::integer_type>::value:
            return self.storage.get<integer_type>() == other;

        case traits<variable::number_type>::value:
            return self.storage.get<number_type>() == other;

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

        case traits<variable::boolean_type>::value:
            return self.storage.get<boolean_type>() < other;

        case traits<variable::integer_type>::value:
            return self.storage.get<integer_type>() < other;

        case traits<variable::number_type>::value:
            return self.storage.get<number_type>() < other;

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

        case traits<variable::boolean_type>::value:
            self.storage.get<boolean_type>() += other;
            break;

        case traits<variable::integer_type>::value:
            self.storage.get<integer_type>() += other;
            break;

        case traits<variable::number_type>::value:
            self.storage.get<number_type>() += other;
            break;

        case traits<variable::array_type>::value:
            self.storage.get<array_type>().push_back(other);
            break;

        default:
            throw dynamic::error(incompatible_type);
        }
    }
};

// Integer

template <typename T>
struct variable::overloader<T, typename std::enable_if<detail::is_integer<T>::value>::type>
{
    using type = variable::integer_type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<variable::boolean_type>::value:
            return self.storage.get<variable::boolean_type>();

        case traits<variable::integer_type>::value:
            return self.storage.get<variable::integer_type>();

        case traits<variable::number_type>::value:
            return self.storage.get<variable::number_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::boolean_type>::value:
            return self.storage.get<boolean_type>() == other;

        case traits<variable::integer_type>::value:
            return self.storage.get<integer_type>() == other;

        case traits<variable::number_type>::value:
            return self.storage.get<number_type>() == other;

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

        case traits<variable::boolean_type>::value:
            return self.storage.get<boolean_type>() < other;

        case traits<variable::integer_type>::value:
            return self.storage.get<integer_type>() < other;

        case traits<variable::number_type>::value:
            return self.storage.get<number_type>() < other;

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

        case traits<variable::boolean_type>::value:
            self.storage.get<boolean_type>() += other;
            break;

        case traits<variable::integer_type>::value:
            self.storage.get<integer_type>() += other;
            break;

        case traits<variable::number_type>::value:
            self.storage.get<number_type>() += other;
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
    using type = variable::number_type;

    static T convert(const variable& self, std::error_code& error)
    {
        switch (self.storage.which())
        {
        case traits<variable::boolean_type>::value:
            return self.storage.get<variable::boolean_type>();

        case traits<variable::integer_type>::value:
            return self.storage.get<variable::integer_type>();

        case traits<variable::number_type>::value:
            return self.storage.get<variable::number_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }

    static bool equal(const variable& self, const T& other)
    {
        switch (self.storage.which())
        {
        case traits<variable::boolean_type>::value:
            return self.storage.get<boolean_type>() == other;

        case traits<variable::integer_type>::value:
            return self.storage.get<integer_type>() == other;

        case traits<variable::number_type>::value:
            return self.storage.get<number_type>() == other;

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

        case traits<variable::boolean_type>::value:
            return self.storage.get<boolean_type>() < other;

        case traits<variable::integer_type>::value:
            return self.storage.get<integer_type>() < other;

        case traits<variable::number_type>::value:
            return self.storage.get<number_type>() < other;

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

        case traits<variable::boolean_type>::value:
            self.storage.get<boolean_type>() += other;
            break;

        case traits<variable::integer_type>::value:
            self.storage.get<integer_type>() += other;
            break;

        case traits<variable::number_type>::value:
            self.storage.get<number_type>() += other;
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
            return true;

        case traits<variable::map_type>::value:
            return true;

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
// variable::iterator_type
//-----------------------------------------------------------------------------

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

    case traits<boolean_type>::value:
    case traits<integer_type>::value:
    case traits<number_type>::value:
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
auto variable::iterator_type<T>::operator++ () -> iterator_type
{
    switch (scope->storage.which())
    {
    case traits<null_type>::value:
    case traits<boolean_type>::value:
    case traits<integer_type>::value:
    case traits<number_type>::value:
    case traits<string_type>::value:
        current = pointer(nullptr);
        break;

    case traits<array_type>::value:
        ++current.template get<array_iterator>();
        break;

    case traits<map_type>::value:
        ++current.template get<map_iterator>();
        break;
    }
    return *this;
}

template <typename T>
auto variable::iterator_type<T>::operator++ (int) -> iterator_type
{
    iterator_type result = *this;
    ++(*this);
    return result;
}

template <typename T>
auto variable::iterator_type<T>::operator* () -> reference
{
    return value();
}

template <typename T>
auto variable::iterator_type<T>::key() const -> key_reference
{
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
    switch (scope->storage.which())
    {
    case traits<null_type>::value:
    case traits<boolean_type>::value:
    case traits<integer_type>::value:
    case traits<number_type>::value:
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
    switch (scope->storage.which())
    {
    case traits<null_type>::value:
    case traits<boolean_type>::value:
    case traits<integer_type>::value:
    case traits<number_type>::value:
    case traits<string_type>::value:
        return current.template get<pointer>();

    case traits<array_type>::value:
        return &*current.template get<array_iterator>();

    case traits<map_type>::value:
        return &current.template get<map_iterator>()->second;
    }
}

template <typename T>
bool variable::iterator_type<T>::operator== (const iterator_type<T>& other)
{
    assert(scope->storage.which() == other.scope->storage.which());

    switch (scope->storage.which())
    {
    case traits<null_type>::value:
    case traits<boolean_type>::value:
    case traits<integer_type>::value:
    case traits<number_type>::value:
    case traits<string_type>::value:
        return current.template get<pointer>() == other.current.template get<pointer>();

    case traits<array_type>::value:
        return current.template get<array_iterator>() == other.current.template get<array_iterator>();

    case traits<map_type>::value:
        return current.template get<map_iterator>() == other.current.template get<map_iterator>();
    }
    assert(false);
    throw dynamic::error(incompatible_type);
}

template <typename T>
bool variable::iterator_type<T>::operator!= (const iterator_type<T>& other)
{
    return !(*this == other);
}

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
    // FIXME: shallow or deep copy of array/maps?
    switch (other.storage.which())
    {
    case traits<null_type>::value:
        storage = null;
        break;
    case traits<boolean_type>::value:
        storage = other.storage.get<boolean_type>();
        break;
    case traits<integer_type>::value:
        storage = other.storage.get<integer_type>();
        break;
    case traits<number_type>::value:
        storage = other.storage.get<number_type>();
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
    case traits<boolean_type>::value:
        storage = std::move(other.storage.get<boolean_type>());
        break;
    case traits<integer_type>::value:
        storage = std::move(other.storage.get<integer_type>());
        break;
    case traits<number_type>::value:
        storage = std::move(other.storage.get<number_type>());
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
}

template <typename T>
variable::variable(T value)
    : storage(typename overloader<typename std::decay<T>::type>::type(std::move(value)))
{
}

template <typename ForwardIterator>
variable::variable(ForwardIterator begin, ForwardIterator end)
    : storage(array_type(begin, end))
{
}

template <typename T>
variable::variable(const string_type& key, T value)
    : storage(map_type{std::make_pair(key, std::move(value))})
{
}

template <typename T>
variable::variable(const string_type::value_type *key, T value)
    : storage(map_type{std::make_pair(key, std::move(value))})
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
    result = array_type{};
    return result;
}

inline variable variable::array(std::initializer_list<array_type::value_type> init)
{
    variable result;
    result = array_type(init.begin(), init.end());
    return result;
}

template <typename T>
variable variable::array(size_type size, const T& value)
{
    variable result;
    result = array_type(size, variable(value));
    return result;
}

inline variable variable::map()
{
    variable result;
    result = map_type{};
    return result;
}

inline variable variable::map(std::initializer_list<map_type::value_type> init)
{
    variable result;
    result = map_type(init.begin(), init.end());
    return result;
}

inline variable& variable::operator= (const variable& other)
{
    // FIXME: shallow or deep copy of array/maps?
    switch (other.storage.which())
    {
    case traits<null_type>::value:
        storage = null;
        break;
    case traits<boolean_type>::value:
        storage = other.storage.get<boolean_type>();
        break;
    case traits<integer_type>::value:
        storage = other.storage.get<integer_type>();
        break;
    case traits<number_type>::value:
        storage = other.storage.get<number_type>();
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
    case traits<boolean_type>::value:
        storage = std::move(other.storage.get<boolean_type>());
        break;
    case traits<integer_type>::value:
        storage = std::move(other.storage.get<integer_type>());
        break;
    case traits<number_type>::value:
        storage = std::move(other.storage.get<number_type>());
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
    case traits<boolean_type>::value:
        overloader<boolean_type>::append(*this, other.storage.get<boolean_type>());
        break;
    case traits<integer_type>::value:
        overloader<integer_type>::append(*this, other.storage.get<integer_type>());
        break;
    case traits<number_type>::value:
        overloader<number_type>::append(*this, other.storage.get<number_type>());
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
variable operator+ (const variable& lhs, const T& rhs)
{
    variable result(lhs);
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
    case traits<boolean_type>::value:
        return bool(storage.get<boolean_type>());
    case traits<integer_type>::value:
        return bool(storage.get<integer_type>());
    case traits<number_type>::value:
        return bool(storage.get<number_type>());
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
    return storage.which() == traits<typename overloader<T>::type>::value;
}

inline void variable::clear()
{
    switch (storage.which())
    {
    case traits<null_type>::value:
        storage = null;
        break;
    case traits<boolean_type>::value:
        storage = boolean_type{};
        break;
    case traits<integer_type>::value:
        storage = integer_type{};
        break;
    case traits<number_type>::value:
        storage = number_type{};
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

inline bool variable::empty() const
{
    switch (storage.which())
    {
    case traits<null_type>::value:
        return true;
    case traits<boolean_type>::value:
    case traits<integer_type>::value:
    case traits<number_type>::value:
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
    case traits<boolean_type>::value:
    case traits<integer_type>::value:
    case traits<number_type>::value:
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
bool operator== (const variable& lhs, const T& rhs)
{
    return variable::overloader<T>::equal(lhs, rhs);
}

inline bool operator== (const variable& lhs, const variable& rhs)
{
    switch (rhs.storage.which())
    {
    case variable::traits<variable::null_type>::value:
        return variable::overloader<variable::null_type>::
            equal(lhs, rhs.storage.get<variable::null_type>());

    case variable::traits<variable::boolean_type>::value:
        return variable::overloader<variable::boolean_type>::
            equal(lhs, rhs.storage.get<variable::boolean_type>());

    case variable::traits<variable::integer_type>::value:
        return variable::overloader<variable::integer_type>::
            equal(lhs, rhs.storage.get<variable::integer_type>());

    case variable::traits<variable::number_type>::value:
        return variable::overloader<variable::number_type>::
            equal(lhs, rhs.storage.get<variable::number_type>());

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
inline bool operator< (const variable& lhs, const T& rhs)
{
    return variable::overloader<T>::less(lhs, rhs);
}

inline bool operator< (const variable& lhs, const variable& rhs)
{
    switch (rhs.storage.which())
    {
    case variable::traits<variable::null_type>::value:
        return variable::overloader<variable::null_type>::
            less(lhs, rhs.value<variable::null_type>());

    case variable::traits<variable::boolean_type>::value:
        return variable::overloader<variable::boolean_type>::
            less(lhs, rhs.storage.get<variable::boolean_type>());

    case variable::traits<variable::integer_type>::value:
        return variable::overloader<variable::integer_type>::
            less(lhs, rhs.storage.get<variable::integer_type>());

    case variable::traits<variable::number_type>::value:
        return variable::overloader<variable::number_type>::
            less(lhs, rhs.storage.get<variable::number_type>());

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
bool operator!= (const variable& lhs, const T& rhs)
{
    return !(lhs == rhs);
}

template <typename T>
bool operator<= (const variable& lhs, const T& rhs)
{
    if (lhs.is<variable::null_type>())
        return true;

    return !(rhs < lhs);
}

template <typename T>
bool operator> (const variable& lhs, const T& rhs)
{
    if (lhs.is<variable::null_type>())
        return false;

    return rhs < lhs;
}

template <typename T>
bool operator>= (const variable& lhs, const T& rhs)
{
    return !(lhs < rhs);
}

} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_DETAIL_VARIABLE_IPP
