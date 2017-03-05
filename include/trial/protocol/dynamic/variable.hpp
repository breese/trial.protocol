#ifndef TRIAL_PROTOCOL_DYNAMIC_VARIABLE_HPP
#define TRIAL_PROTOCOL_DYNAMIC_VARIABLE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <memory>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <trial/protocol/detail/small_union.hpp>
#include <trial/protocol/dynamic/error.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{

class variable
{
public:
    // FIXME: From std::iterator_traits?
    using value_type = variable;
    using reference = std::add_lvalue_reference<value_type>::type;
    using const_reference = std::add_const<reference>::type;
    using size_type = std::size_t;

    struct null_type {};
    using boolean_type = bool;
    using integer_type = std::intmax_t;
    using number_type = double;
    using string_type = std::string;
    using array_type = std::vector<value_type>;
    using map_type = std::map<string_type, value_type>; // FIXME: key = value_type?

    template <typename T>
    class iterator_type
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using key_type = std::add_const<map_type::key_type>::type;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = typename std::add_pointer<value_type>::type;
        using reference = typename std::add_lvalue_reference<value_type>::type;
        using key_reference = typename std::add_lvalue_reference<key_type>::type;

        iterator_type() = delete;
        iterator_type(const iterator_type&);
        iterator_type(iterator_type&&);
        iterator_type(pointer, bool = true);

        iterator_type& operator= (const iterator_type&);
        iterator_type& operator= (iterator_type&&);

        iterator_type operator++ ();
        iterator_type operator++ (int);

        reference operator* ();
        pointer operator-> ();

        key_reference key() const;
        reference value();

        bool operator== (const iterator_type<T>&);
        bool operator!= (const iterator_type<T>&);

    private:
        pointer scope;

        using array_iterator = typename std::conditional<std::is_const<T>::value,
                                                         array_type::const_iterator,
                                                         array_type::iterator>::type;
        using map_iterator = typename std::conditional<std::is_const<T>::value,
                                                       map_type::const_iterator,
                                                       map_type::iterator>::type;

        protocol::detail::small_union<sizeof(pointer), pointer, array_iterator, map_iterator> current;
    };

    using iterator = iterator_type<variable>;
    using const_iterator = iterator_type<const variable>;

    static constexpr null_type null{};

    // Constructor
    variable(const variable&);
    variable(variable&&);
    template <typename T> variable(T);
    // Null constructor
    variable();
    variable(null_type);
    // String constructor
    variable(const string_type::value_type *);
    // Array constructor
    template <typename ForwardIterator> variable(ForwardIterator begin, ForwardIterator end);
    static variable array();
    static variable array(std::initializer_list<array_type::value_type>);
    template <typename T>
    static variable array(size_type, const T&);
    // Map constructor
    template <typename T> variable(const string_type&, T);
    template <typename T> variable(const string_type::value_type *, T);
    static variable map();
    static variable map(std::initializer_list<map_type::value_type>);
 
    // Assignment

    variable& operator= (const variable&);
    variable& operator= (variable&&);
    template <typename T> variable& operator= (T);
    variable& operator= (null_type);
    variable& operator= (const string_type::value_type *);

    variable& operator+= (const variable&);
    variable& operator+= (std::initializer_list<array_type::value_type>);
    variable& operator+= (std::initializer_list<map_type::value_type>);

    // Accessor

    template <typename R> R value() const;
    template <typename R> R value(std::error_code&) const noexcept;
    template <typename R> explicit operator R() const;

    explicit operator bool() const;

    variable& operator[] (const map_type::key_type&);
    const variable& operator[] (const map_type::key_type&) const;

    // Type checker

    template <typename T> bool is() const;

    void clear();
    bool empty() const;
    size_type size() const;

    // Iteration

    iterator begin() &;
    const_iterator begin() const &;
    iterator end() &;
    const_iterator end() const &;

    // Comparison

    template <typename T>
    friend bool operator== (const variable&, const T&);
    friend bool operator== (const variable&, const variable&);
    friend bool operator== (const variable&, const variable::string_type::value_type *);

    template <typename T>
    friend bool operator< (const variable&, const T&);
    friend bool operator< (const variable&, const variable&);
    friend bool operator< (const variable&, const variable::string_type::value_type *);

    template <typename T>
    friend bool operator!= (const variable&, const T&);

    template <typename T>
    friend bool operator<= (const variable&, const T&);

    template <typename T>
    friend bool operator> (const variable&, const T&);

    template <typename T>
    friend bool operator>= (const variable&, const T&);

private:
    template <typename T> struct traits;
    template <typename T, typename Enable = void> struct overloader;

    protocol::detail::small_union<sizeof(number_type), null_type, boolean_type, integer_type, number_type, string_type, array_type, map_type> storage;
};

} // namespace dynamic
} // namespace protocol
} // namespace trial

#include <trial/protocol/dynamic/detail/variable.ipp>

#endif // TRIAL_PROTOCOL_DYNAMIC_VARIABLE_HPP
