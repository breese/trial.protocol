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
#include <trial/protocol/dynamic/token.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{

// Forward declarations

namespace detail
{

template <typename T, typename U, typename Enable> struct overloader;
template <typename T, typename U, typename Enable> struct operator_overloader;
template <typename C, typename T, typename Enable> struct same_overloader;

} // namespace detail

enum nullable { null };
struct boolean {};
struct integer {};
struct number {};
struct string {};
struct array {};
struct map {};

template <typename CharT>
class basic_variable
{
    template <typename T> struct traits;
    template <typename T, typename Enable = void> struct tag_traits;

public:
    using value_type = basic_variable<CharT>;
    using reference = typename std::add_lvalue_reference<value_type>::type;
    using const_reference = typename std::add_const<reference>::type;
    using size_type = std::size_t;

private:
    using string_type = std::basic_string<CharT>;
    using array_type = std::vector<value_type>;
    using map_type = std::map<string_type, value_type>;

public:
    template <typename T>
    class iterator_type
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using key_type = typename std::add_const<typename map_type::key_type>::type;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = typename std::add_pointer<value_type>::type;
        using reference = typename std::add_lvalue_reference<value_type>::type;
        using key_reference = typename std::add_lvalue_reference<key_type>::type;

        iterator_type();
        iterator_type(const iterator_type&);
        iterator_type(iterator_type&&);
        iterator_type(pointer, bool = true);
        // iterator is convertible to const_iterator
        template <typename U = T>
        iterator_type(const iterator_type<typename std::remove_const<U>::type>& other,
                      typename std::enable_if<std::is_const<U>::value, pointer>::type = 0);

        iterator_type& operator= (const iterator_type&);
        iterator_type& operator= (iterator_type&&);

        iterator_type& operator++ ();
        iterator_type operator++ (int);

        reference operator* ();
        pointer operator-> ();

        key_reference key() const;
        reference value();

        bool operator== (const iterator_type<T>&);
        bool operator!= (const iterator_type<T>&);

    private:
        friend class basic_variable<CharT>;

        using array_iterator = typename std::conditional<std::is_const<T>::value,
                                                         typename array_type::const_iterator,
                                                         typename array_type::iterator>::type;
        using map_iterator = typename std::conditional<std::is_const<T>::value,
                                                       typename map_type::const_iterator,
                                                       typename map_type::iterator>::type;
        using small_union = protocol::detail::small_union<sizeof(pointer), pointer, array_iterator, map_iterator>;

        // Conversion from const_iterator to iterator is kept private
        template <typename U = T>
        iterator_type(const iterator_type<typename std::add_const<U>::type>& other,
                      typename std::enable_if<!std::is_const<U>::value, pointer>::type = 0);

        pointer scope;
        small_union current;
    };

    using iterator = iterator_type<value_type>;
    using const_iterator = iterator_type<const value_type>;

    // Constructor
    basic_variable(const basic_variable<CharT>&);
    basic_variable(basic_variable<CharT>&&);
    template <typename T> basic_variable(T);
    // Null constructor
    basic_variable();
    basic_variable(const nullable&);
    // String constructor
    basic_variable(const CharT *);
    // Array constructor
    basic_variable(typename basic_variable::array_type) = delete;
    template <typename ForwardIterator> static value_type array(ForwardIterator begin, ForwardIterator end);
    static value_type array();
    static value_type array(std::initializer_list<typename array_type::value_type>);
    template <typename T> static value_type array(size_type, const T&);
    // Map constructor
    basic_variable(typename basic_variable::map_type) = delete;
    static value_type map();
    static value_type map(std::initializer_list<typename map_type::value_type>);
 
    // Assignment

    basic_variable& operator= (const basic_variable&);
    basic_variable& operator= (basic_variable&&);
    template <typename T> basic_variable& operator= (T);
    basic_variable& operator= (nullable);
    basic_variable& operator= (const CharT *);

    // Addition / concatenation

    basic_variable& operator+= (const basic_variable&);
    basic_variable& operator+= (std::initializer_list<typename array_type::value_type>);
    basic_variable& operator+= (std::initializer_list<typename map_type::value_type>);

    template <typename T, typename U>
    friend basic_variable<T> operator+ (const basic_variable<T>&,
                                        const U&);
    template <typename T>
    friend basic_variable<T> operator+ (nullable,
                                        const basic_variable<T>&);

    // Accessor

    template <typename Tag> typename tag_traits<typename std::decay<Tag>::type>::type value() const;
    template <typename Tag> typename tag_traits<typename std::decay<Tag>::type>::type value(std::error_code&) const noexcept;
    template <typename R> explicit operator R() const;

    explicit operator bool() const;

    basic_variable& operator[] (typename array_type::size_type);
    const basic_variable& operator[] (typename array_type::size_type) const;

    basic_variable& operator[] (const typename map_type::key_type&);
    const basic_variable& operator[] (const typename map_type::key_type&) const;

    // Type checker

    template <typename T> bool is() const;
    template <typename T> bool same() const;

    token::code::value code() const;
    token::symbol::value symbol() const;

    bool empty() const;
    size_type size() const;

    void clear();
    iterator erase(const_iterator);
    iterator erase(const_iterator, const_iterator);

    // Iteration

    iterator begin() &;
    const_iterator begin() const &;
    iterator end() &;
    const_iterator end() const &;

    // Comparison

    template <typename T, typename U>
    friend bool operator== (const T&, const U&);

    template <typename T, typename U>
    friend bool operator!= (const T&, const U&);

    template <typename T, typename U>
    friend bool operator< (const T&, const U&);

    template <typename T>
    bool operator<= (const T&) const;

    template <typename T>
    bool operator> (const T&) const;

    template <typename T>
    bool operator>= (const T&) const;

private:
    template <typename T, typename U, typename Enable> friend struct detail::overloader;
    template <typename T, typename U, typename Enable> friend struct detail::operator_overloader;
    template <typename C, typename T, typename Enable> friend struct detail::same_overloader;
    template <typename T> struct similar_visitor;

    using storage_type = protocol::detail::small_union<sizeof(double),
                                                       nullable,
                                                       bool,
                                                       signed short int,
                                                       unsigned short int,
                                                       signed int,
                                                       unsigned int,
                                                       signed long int,
                                                       unsigned long int,
                                                       signed long long int,
                                                       unsigned long long int,
                                                       float,
                                                       double,
                                                       long double,
                                                       string_type,
                                                       array_type,
                                                       map_type>;
    storage_type storage;
};

using variable = basic_variable<char>;

} // namespace dynamic
} // namespace protocol
} // namespace trial

#include <trial/protocol/dynamic/detail/variable.ipp>

#endif // TRIAL_PROTOCOL_DYNAMIC_VARIABLE_HPP
