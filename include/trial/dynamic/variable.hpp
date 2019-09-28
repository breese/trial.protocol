#ifndef TRIAL_DYNAMIC_VARIABLE_HPP
#define TRIAL_DYNAMIC_VARIABLE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef>
#include <cstdint>
#include <memory>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <trial/dynamic/detail/config.hpp>
#include <trial/dynamic/detail/small_union.hpp>
#include <trial/dynamic/error.hpp>
#include <trial/dynamic/token.hpp>

namespace trial
{
namespace dynamic
{

// Forward declarations

namespace detail
{

template <typename T, typename U, typename> struct overloader;
template <typename T, typename U, typename> struct operator_overloader;
template <typename A, typename T, typename> struct same_overloader;
template <typename A, typename U, typename> struct iterator_overloader;

} // namespace detail

enum nullable { null };
struct boolean {};
struct integer {};
struct real {};
struct string {};
struct wstring {};
struct u16string {};
struct u32string {};
template <typename Allocator> struct basic_array;
template <typename Allocator> struct basic_map;

//! @brief Dynamic variable.
//!
//! Dynamic variable is a tagged union that can change both its type and value
//! during program execution.
//!
//! Dynamic variable is a heterogenous hierarchical data structure with a
//! pre-determined list of supported types: fundamental data types, strings,
//! arrays, and associative arrays.
//!
//! Type                          | Tag
//! ------------------------------|-----------------------
//! `dynamic::nullable`           | `dynamic::nullable`
//! `bool`                        | `dynamic::boolean`
//! `signed char`                 | `dynamic::integer`
//! `signed short int`            | `dynamic::integer`
//! `signed int`                  | `dynamic::integer`
//! `signed long int`             | `dynamic::integer`
//! `signed long long int`        | `dynamic::integer`
//! `unsigned char`               | `dynamic::integer`
//! `unsigned short int`          | `dynamic::integer`
//! `unsigned int`                | `dynamic::integer`
//! `unsigned long int`           | `dynamic::integer`
//! `unsigned long long int`      | `dynamic::integer`
//! `float`                       | `dynamic::real`
//! `double`                      | `dynamic::real`
//! `long double`                 | `dynamic::real`
//! `dynamic::string_type`        | `dynamic::string`
//! `dynamic::wstring_type`       | `dynamic::wstring`
//! `dynamic::u16string_type`     | `dynamic::u16string`
//! `dynamic::u32string_type`     | `dynamic::u32string`
//! `dynamic::array_type`         | `dynamic::array`
//! `dynamic::map_type`           | `dynamic::map`
//!
//! @tparam Allocator Allocator type (defaults to `std::allocator`)

template <typename Allocator>
class basic_variable
{
    template <typename T> struct traits;
    template <typename T, typename = void> struct tag_traits;

public:
#if defined(BOOST_DOXYGEN_INVOKED)

    using value_type = basic_variable<Allocator>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using difference_type = unspecified; //!< signed integer type
    using size_type = unspecified; //!< unsigned integer type
    using string_type = std::basic_string<char, std::char_traits<char>, Allocator>; //!< std::string by default
    using wstring_type = std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>; //!< std::wstring by default
    using u16string_type = std::basic_string<char16_t, std::char_traits<char16_t>, Allocator>; //!< std::u16string by default
    using u32string_type = std::basic_string<char32_t, std::char_traits<char32_t>, Allocator>; //!< std::u32string by default
    using array_type = unspecified; //!< SequenceContainer
    using map_type = unspecified; //!< AssociativeContainer
    using pair_type = unspecified;

#else

    using value_type = basic_variable<Allocator>;
    using reference = typename std::add_lvalue_reference<value_type>::type;
    using const_reference = typename std::add_const<reference>::type;
    using allocator_type = typename std::allocator_traits<Allocator>::template rebind_alloc<value_type>;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;
private:
    template <typename CharT>
    using basic_string = std::basic_string<CharT,
                                           typename std::char_traits<CharT>,
                                           typename std::allocator_traits<allocator_type>::template rebind_alloc<CharT>>;
    using map_value_type = typename std::map<value_type, value_type>::value_type;
public:
    using string_type = basic_string<char>;
    using wstring_type = basic_string<wchar_t>;
    using u16string_type = basic_string<char16_t>;
    using u32string_type = basic_string<char32_t>;
    using array_type = std::vector<value_type,
                                   allocator_type>;
    using map_type = std::map<value_type,
                              value_type,
                              std::less<value_type>,
                              typename std::allocator_traits<allocator_type>::template rebind_alloc<map_value_type>>;
    using pair_type = typename map_type::value_type;

#endif

#if !defined(BOOST_DOXYGEN_INVOKED)
private:
    friend struct basic_array<Allocator>;
    friend struct basic_map<Allocator>;

    template <typename Derived, typename T>
    class iterator_base
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using key_type = typename std::add_const<typename map_type::key_type>::type;
        using value_type = T;
        using difference_type = typename value_type::difference_type;
        using pointer = typename std::add_pointer<value_type>::type;
        using reference = typename std::add_lvalue_reference<value_type>::type;
        using const_reference = typename std::add_const<reference>::type;

        Derived& operator= (const Derived&);
        Derived& operator= (Derived&&);

        Derived& operator++ ();
        Derived operator++ (int);
        Derived& operator-- ();
        Derived operator-- (int);

        pointer operator-> ();

        bool operator== (const Derived&) const;
        bool operator!= (const Derived&) const;

    protected:
        friend class basic_variable;

        using array_iterator = typename std::conditional<std::is_const<T>::value,
                                                         typename array_type::const_iterator,
                                                         typename array_type::iterator>::type;
        using map_iterator = typename std::conditional<std::is_const<T>::value,
                                                       typename map_type::const_iterator,
                                                       typename map_type::iterator>::type;

        iterator_base();
        explicit iterator_base(const iterator_base&);
        explicit iterator_base(iterator_base&&);
        explicit iterator_base(pointer, bool = true);
        explicit iterator_base(pointer, array_iterator);
        explicit iterator_base(pointer, map_iterator);

        const_reference key() const;
        reference value();
        const_reference value() const;

    protected:
        using index_type = unsigned char;
        using small_union = detail::small_union<allocator_type,
                                                pointer,
                                                index_type,
                                                pointer,
                                                array_iterator,
                                                map_iterator>;

        pointer scope;
        small_union current;
    };

#endif

public:
    class const_iterator;

    class iterator
        : public iterator_base<iterator, typename basic_variable::value_type>
    {
        using super = iterator_base<iterator, typename basic_variable::value_type>;

    public:
        using typename super::iterator_category;
        using typename super::key_type;
        using typename super::value_type;
        using typename super::difference_type;
        using typename super::pointer;
        using typename super::reference;
        using typename super::const_reference;

        iterator();
        iterator(const iterator& other);
        iterator(iterator&& other);

        iterator& operator= (const iterator& other);
        iterator& operator= (iterator&& other);

        const_reference key() const { return super::key(); }
        reference value() { return super::value(); }
        const_reference value() const { return super::value(); }
        reference operator* () { return super::value(); }
        const_reference operator* () const { return super::value(); }

    private:
        friend class basic_variable;

        // Conversion from const_iterator to iterator is kept private
        explicit iterator(const const_iterator& other);
        explicit iterator(pointer p, bool initialize = true);
        explicit iterator(pointer p, typename super::array_iterator);
        explicit iterator(pointer p, typename super::map_iterator);
    };

    class const_iterator
        : public iterator_base<const_iterator, const typename basic_variable::value_type>
    {
        using super = iterator_base<const_iterator, const typename basic_variable::value_type>;

    public:
        using typename super::iterator_category;
        using typename super::key_type;
        using typename super::value_type;
        using typename super::difference_type;
        using typename super::pointer;
        using typename super::reference;
        using typename super::const_reference;

        const_iterator();
        const_iterator(const const_iterator& other);
        const_iterator(const_iterator&& other);
        // iterator is convertible to const_iterator
        const_iterator(const iterator& other);

        const_reference key() const { return super::key(); }
        const_reference value() const { return super::value(); }
        const_reference operator* () const { return super::value(); }

    private:
        friend class basic_variable;
        template <typename A, typename U, typename> friend struct detail::iterator_overloader;

        explicit const_iterator(pointer p, bool initialize = true);
    };

    class key_iterator
        : public iterator_base<key_iterator, const typename basic_variable::value_type>
    {
        using super = iterator_base<key_iterator, const typename basic_variable::value_type>;

    public:
        using typename super::iterator_category;
        using typename super::key_type;
        using typename super::value_type;
        using typename super::difference_type;
        using typename super::pointer;
        using typename super::reference;
        using typename super::const_reference;

        key_iterator();
        key_iterator(const key_iterator& other);
        key_iterator(key_iterator&& other);

        key_iterator& operator= (const key_iterator& other);
        key_iterator& operator= (key_iterator&& other);

        const_reference key() const;
        const_reference value() const { return super::value(); }
        const_reference operator* () { return key(); }

        key_iterator& operator++();

        //! @brief Convert key_iterator to const_iterator
        //!
        //! This conversion is lossy because const_iterator has fewer member
        //! variables than key_iterator.
        //!
        //! @returns const_iterator pointing to the same container item as
        //! key_iterator.

        const_iterator base() const;

    private:
        friend class basic_variable;

        explicit key_iterator(pointer p, bool initialize = true);

    private:
        typename std::remove_const<value_type>::type index;
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    //! @brief Constructs a default variable of type `nullable`.
    //!
    //! A default constructed variable contains `null`, which means it has no
    //! value.

    basic_variable();

    //! @brief Copy-constructs a copy of `element`.

    basic_variable(const basic_variable& element);

    //! @brief Move-constructs a copy of `element`.

    basic_variable(basic_variable&& element) noexcept;

    //! @brief Constructs a variable of type `T`.
    //!
    //! `T` must be a supported type, otherwise a compilation error occurs.

    template <typename T> basic_variable(T);

    //! @brief Constructs a variable from initializer list.
    //!
    //! If the initializer list `elements` contains an array of pairs then the
    //! variable will be of type `map`, otherwise of type `array`.

    basic_variable(const std::initializer_list<value_type>& elements);

    //! @brief Constructs a variable of type `nullable`.

    basic_variable(const nullable&);

    //! @brief Constructs a variable of type `string`.

    basic_variable(const char *);

    //! @brief Constructs a variable of type `wstring`.

    basic_variable(const wchar_t *);

    //! @brief Constructs a variable of type `u16string`.

    basic_variable(const char16_t *);

    //! @brief Constructs a variable of type `u32string`.

    basic_variable(const char32_t *);

    //! @brief Construct a variable from array type.
    //!
    //! Re-construct a variable from the value returned by @c assume_value.
    //!
    //! Prefer to use factory or initializer-lists when creating arrays.

    basic_variable(const typename basic_variable::array_type&);

    //! @brief Construct a variable from array type.
    //!
    //! Re-construct a variable from the value returned by @c assume_value.
    //!
    //! Prefer to use factory or initializer-lists when creating arrays.

    basic_variable(typename basic_variable::array_type&&);

    //! @brief Construct a variable from map type.
    //!
    //! Re-construct a variable from the value returned by @c assume_value.
    //!
    //! Prefer to use factory or initializer-lists when creating associative arrays.

    basic_variable(const typename basic_variable::map_type&);

    //! @brief Construct a variable from map type.
    //!
    //! Re-construct a variable from the value returned by @c assume_value.
    //!
    //! Prefer to use factory or initializer-lists when creating associative arrays.

    basic_variable(typename basic_variable::map_type&&);

#if !defined(BOOST_DOXYGEN_INVOKED)
    basic_variable(typename basic_variable::pair_type) = delete;
#endif
 
    //! @brief Copy-asigns one variable to another.

    basic_variable& operator= (const basic_variable&);

    //! @brief Move-assigns one variable to another.

    basic_variable& operator= (basic_variable&&);

    //! @brief Assigns content to a variable.

    template <typename T> basic_variable& operator= (T);

    //! @brief Assigns null to variable.

    basic_variable& operator= (nullable);

    //! @brief Assigns a string literal to a variable.

    basic_variable& operator= (const char *);

    //! @brief Assigns a wide-string literal to a variable.

    basic_variable& operator= (const wchar_t *);

    //! @brief Assigns a UTF-16 encoded string literal to a variable.

    basic_variable& operator= (const char16_t *);

    //! @brief Assigns a UTF-32 encoded string literal to a variable.

    basic_variable& operator= (const char32_t *);

    //! @brief Appends values.
    //!
    //! The append operator has different meanings depending on the types.
    //!
    //! * Appending null to any other type has no effect.
    //! * Appending any value to null overwrites the variable.
    //! * Appending an integral value with another integral value adds the two.
    //! * Appending a string to another string concatenates the two.
    //! * Appending a wide string to another wide string concatenates the two.
    //! * Appending a UTF-16 encoded string to another UTF-16 encoded string concatenates the two.
    //! * Appending a UTF-32 encoded string to another UTF-32 encoded string concatenates the two.
    //! * Appending an array to an array concatenates the two.
    //! * Appending any type to an array inserts the value at the end of the array.
    //! * Appending a map to a map merges the two.
    //!
    //! Tag      | nullable  | boolean  | integer  | real    | string  | wstring  | u16string | u32string | array   | map
    //! ---------|-----------|----------|----------|---------|---------|----------|-----------|-----------|---------|-----
    //! nullable | No effect | Assigns  | Assigns  | Assigns | Assigns | Assigns  | Assigns   | Assigns   | Assigns | Assigns
    //! boolean  | No effect | Adds     | Adds     | Adds    | Fails   | Fails    | Fails     | Fails     | Fails   | Fails
    //! integer  | No effect | Adds     | Adds     | Adds    | Fails   | Fails    | Fails     | Fails     | Fails   | Fails
    //! real     | No effect | Adds     | Adds     | Adds    | Fails   | Fails    | Fails     | Fails     | Fails   | Fails
    //! string   | No effect | Fails    | Fails    | Fails   | Concats | Fails    | Fails     | Fails     | Fails   | Fails
    //! wstring  | No effect | Fails    | Fails    | Fails   | Fails   | Concats  | Fails     | Fails     | Fails   | Fails
    //! u16string| No effect | Fails    | Fails    | Fails   | Fails   | Fails    | Concats   | Fails     | Fails   | Fails
    //! u32string| No effect | Fails    | Fails    | Fails   | Fails   | Fails    | Fails     | Concats   | Fails   | Fails
    //! array    | No effect | Inserts  | Inserts  | Inserts | Inserts | Inserts  | Inserts   | Inserts   | Concats | Inserts
    //! map      | No effect | Fails    | Fails    | Fails   | Fails   | Fails    | Fails     | Fails     | Fails   | Merges

    basic_variable& operator+= (const basic_variable&);

    //! @overload basic_variable<Allocator>::operator+=(const basic_variable&)

    template <typename T> basic_variable& operator+= (const T&);

    //! @overload basic_variable<Allocator>::operator+=(const basic_variable&)

    basic_variable& operator+= (const char *);

    //! @overload basic_variable<Allocator>::operator+=(const basic_variable&)

    basic_variable& operator+= (const wchar_t *);

    //! @overload basic_variable<Allocator>::operator+=(const basic_variable&)

    basic_variable& operator+= (const char16_t *);

    //! @overload basic_variable<Allocator>::operator+=(const basic_variable&)

    basic_variable& operator+= (const char32_t *);

    // Accessor

#if defined(BOOST_DOXYGEN_INVOKED)

    //! @brief Returns current value as type T.
    //!
    //! Calls `basic_variable<Allocator>::value<T>(std::error_code&)` and throws
    //! an exception if an error occurred.
    //!
    //! @tparam T Supported type
    //!
    //! @exception dynamic::error with `dynamic::incompatible_type` if `T` is an unsupported or incompatible type.
    //!
    //! @sa basic_variable<Allocator>::value<T>(std::error_code&)

    template <typename T> T value() const;

    //! @brief Returns current value as type T.
    //!
    //! `T` can either be a type or a tag.
    //!
    //! If current tag is `dynamic::integer` or `dynamic::real`, then `T` can
    //! be any arithmetic type. Such a conversion may result in loss of precision.
    //!
    //! If current tag is any other type, then `T` must be the associated type.
    //!
    //! If `T` is a tag, then the following types are used.
    //!
    //! Tag         | Type
    //! ------------|-----------------------
    //! nullable    | `dynamic::nullable`
    //! boolean     | `bool`
    //! integer     | `int`
    //! real        | `float`
    //! string      | `variable::string_type`
    //! wstring     | `variable::wstring_type`
    //! u16string   | `variable::u16string_type`
    //! u32string   | `variable::u32string_type`
    //! array       | `variable::array_type`
    //! map         | `variable::map_type`
    //!
    //! @tparam T Supported type
    //!
    //! @param[out] error Set to `dynamic::incompatible_type` if `T` is an unsupported or incompatible type, otherwise unchanged.

    template <typename T> T value(std::error_code& error) const noexcept;

#else
    template <typename Tag> typename tag_traits<typename std::decay<Tag>::type>::type value() const;
    template <typename Tag> typename tag_traits<typename std::decay<Tag>::type>::type value(std::error_code&) const noexcept;
#endif

    //! @brief Returns current value as type `R`.
    //!
    //! Calls `basic_variable<Allocator>::value<R>()`
    //!
    //! @sa basic_variable<Allocator>::value<T>()

    template <typename R> explicit operator R() const;

    //! @brief Returns reference to stored value.
    //!
    //! `assume_value()` has a narrow contract. Using a type `R` that does not
    //! match the type of the stored value results in undefined behavior.
    //!
    //! @tparam R Supported type.
    //!
    //! @pre basic_variable<Allocator>::same<R>() is true.

    template <typename R> R& assume_value() & noexcept;

    //! @brief Returns constant reference to stored value.
    //!
    //! @overload basic_variable<Allocator>::assume_value()

    template <typename R> const R& assume_value() const & noexcept;

#if !defined(BOOST_DOXYGEN_INVOKED)
    explicit operator bool() const;
#endif

    //! @brief Returns reference to element at specified position.
    //!
    //! The stored value must be an array.
    //!
    //! No bounds-checking is performed.
    //!
    //! @param[in] position Index position.
    //!
    //! @pre basic_variable<Allocator>::is<array>() is true.

    basic_variable& operator[] (size_type position) &;

    //! @brief Returns constant reference to element at specified position.
    //!
    //! @overload basic_variable<Allocator>::operator[](size_type)

    const basic_variable& operator[] (size_type position) const &;

    //! @brief Returns reference to element indexed by key.
    //!
    //! Returns a reference to the value associated with @c key in an
    //! associative array, or inserts a key of none exists.
    //!
    //! If the current tag is `nullable`, then the current value is
    //! changed into an associative array and @c key is inserted.
    //!
    //! @pre basic_variable<Allocator>::is<map>() is true.
    //!
    //! @exception dynamic::error with `dynamic::incompatible_type` is thrown if current tag is not `dynamic::map`.

    basic_variable& operator[] (const typename map_type::key_type& key) &;

    //! @brief Returns constant reference to element indexed by key.
    //!
    //! Returns a reference to the value associated with @c key in an
    //! associative array.
    //!
    //! @pre basic_variable<Allocator>::is<map>() is true.
    //!
    //! @exception dynamic::error with `dynamic::incompatible_type` is thrown if @c key does not exist in associative array.
    //! @exception dynamic::error with `dynamic::incompatible_type` is thrown if current tag is not `dynamic::map`.

    const basic_variable& operator[] (const typename map_type::key_type& key) const &;

    //! @brief Checks if variable has a given tag.
    //!
    //! Converts `T` into a tag, and returns true if variable has the same
    //! tag, otherwise returns false.
    //!
    //! If `T` is a tag, then this tag is used directly:
    //!
    //!     variable v = true; // Boolean
    //!     assert(v.is<boolean>());
    //!
    //! If `T` is a C++ type, then this is converted a tag:
    //!
    //!     variable v = true; // Boolean
    //!     assert(v.is<bool>()); // Same as is<boolean>()
    //!
    //! The type-to-tag conversion means that any type from the same category
    //! can be used:
    //!
    //!     variable v = 2; // Integer
    //!     assert(v.is<int>()); // Same as is<integer>()
    //!     assert(v.is<long int>()); // Same as is<integer>()
    //!
    //! Checking for an array or a map can either be done by a tag:
    //!
    //!     variable v = { 1, 2, 3}; // Array
    //!     assert(v.is<array>());
    //!
    //! or by the unspecified `variable::array_type` or `variable::map_type` type aliases:
    //!
    //!     variable v = { 1, 2, 3}; // Array
    //!     assert(v.is<variable::array_type>());
    //!
    //! Using unsupported types will result in a compilation error.
    //!
    //! @tparam T Type or tag to be checked.

    template <typename T> bool is() const noexcept;

    //! @brief Checks if variable has exactly a given type.
    //!
    //! Returns true if variable has the exact same type as `T`, otherwise
    //! returns false.
    //!
    //!     variable v = int(2); // int
    //!     assert(v.same<int>() == true); // Same as int
    //!     assert(v.same<long int>() == false); // Not same as long int
    //!
    //! @tparam T Type to be checked.

    template <typename T> bool same() const noexcept;

    //! @brief Returns the current code.
    //!
    //! Code is an enumerator that represents the exact type that is currently
    //! stored.
    //!
    //! Type                          | Code
    //! ------------------------------|-----------------------
    //! `dynamic::nullable`           | `dynamic::code::null`
    //! `bool`                        | `dynamic::code::boolean`
    //! `signed char`                 | `dynamic::code::signed_char`
    //! `signed short int`            | `dynamic::code::signed_short_integer`
    //! `signed int`                  | `dynamic::code::signed_integer`
    //! `signed long int`             | `dynamic::code::signed_long_integer`
    //! `signed long long int`        | `dynamic::code::signed_long_long_integer`
    //! `unsigned char`               | `dynamic::code::unsigned_char`
    //! `unsigned short int`          | `dynamic::code::unsigned_short_integer`
    //! `unsigned int`                | `dynamic::code::unsigned_integer`
    //! `unsigned long int`           | `dynamic::code::unsigned_long_integer`
    //! `unsigned long long int`      | `dynamic::code::unsigned_long_long_integer`
    //! `float`                       | `dynamic::code::real`
    //! `double`                      | `dynamic::code::long_real`
    //! `long double`                 | `dynamic::code::long_long_real`
    //! `dynamic::string_type`        | `dynamic::code::string`
    //! `dynamic::wstring_type`       | `dynamic::code::wstring`
    //! `dynamic::u16string_type`     | `dynamic::code::u16string`
    //! `dynamic::u32string_type`     | `dynamic::code::u32string`
    //! `dynamic::array_type`         | `dynamic::code::array`
    //! `dynamic::map_type`           | `dynamic::code::map`

    dynamic::code::value code() const noexcept;

    //! @brief Returns the current symbol.
    //!
    //! Symbol is an enumerator that represents the tag of the type currently
    //! stored.
    //!
    //! Type                          | Tag       | Symbol
    //! ------------------------------|-----------|---------------------------
    //! `dynamic::nullable`           | nullable  | `dynamic::symbol::null`
    //! `bool`                        | boolean   | `dynamic::symbol::boolean`
    //! `signed char`                 | integer   | `dynamic::symbol::integer`
    //! `signed short int`            | integer   | `dynamic::symbol::integer`
    //! `signed int`                  | integer   | `dynamic::symbol::integer`
    //! `signed long int`             | integer   | `dynamic::symbol::integer`
    //! `signed long long int`        | integer   | `dynamic::symbol::integer`
    //! `unsigned char`               | integer   | `dynamic::symbol::integer`
    //! `unsigned short int`          | integer   | `dynamic::symbol::integer`
    //! `unsigned int`                | integer   | `dynamic::symbol::integer`
    //! `unsigned long int`           | integer   | `dynamic::symbol::integer`
    //! `unsigned long long int`      | integer   | `dynamic::symbol::integer`
    //! `float`                       | real      | `dynamic::symbol::real`
    //! `double`                      | real      | `dynamic::symbol::real`
    //! `long double`                 | real      | `dynamic::symbol::real`
    //! `dynamic::string_type`        | string    | `dynamic::symbol::string`
    //! `dynamic::wstring_type`       | wstring   | `dynamic::symbol::wstring`
    //! `dynamic::u16string_type`     | u16string | `dynamic::symbol::u16string`
    //! `dynamic::u32string_type`     | u32string | `dynamic::symbol::u32string`
    //! `dynamic::array_type`         | array     | `dynamic::symbol::array`
    //! `dynamic::map_type`           | map       | `dynamic::symbol::map`

    dynamic::symbol::value symbol() const noexcept;

    //! @brief Checks if variable is empty.
    //!
    //! Same as `size()` == 0

    bool empty() const noexcept;

    //! @brief Returns the number of elements in variable.
    //!
    //! The number of elements stored in a variable corresponds to the iteration
    //! count, that is `v.size() == std::distance(v.begin(), v.end())`.
    //!
    //! Notice that strings are regarded as single elements, rather than a
    //! sequence of characters.
    //!
    //! Current tag | Size | Description
    //! ------------|------|----
    //! nullable    | 0    | null is an empty variable.
    //! boolean     | 1    | boolean is a single element.
    //! integer     | 1    | integer is a single element.
    //! real        | 1    | real is a single element.
    //! string      | 1    | string is a single element, so `variable::string_type::size()` is not used.
    //! wstring     | 1    | wstring is a single element, so `variable::wstring_type::size()` is not used.
    //! u16string   | 1    | u16string is a single element, so `variable::u16string_type::size()` is not used.
    //! u32string   | 1    | u32string is a single element, so `variable::u32string_type::size()` is not used.
    //! array       | `variable::array_type::size()`     | The number of elements in the array.
    //! map         | `variable::map_type::size()`       | The number of elements (pairs) in the map.

    size_type size() const noexcept;

    //! @brief Returns the maximum possible number of elements.
    //!
    //! Current tag | Size | Description
    //! ------------|------|----
    //! nullable    | 0    | null cannot contain element.
    //! boolean     | 1    | Can contain a single boolean element.
    //! integer     | 1    | Can contain a single integer element.
    //! real        | 1    | Can contain a single real element.
    //! string      | 1    | Can contain a single string element, so `variable::string_type::max_size()` is not used.
    //! wstring     | 1    | Can contain a single wstring element, so `variable::wstring_type::max_size()` is not used.
    //! u16string   | 1    | Can contain a single u16string element, so `variable::u16string_type::max_size()` is not used.
    //! u32string   | 1    | Can contain a single u32string element, so `variable::u32string_type::max_size()` is not used.
    //! array       | `variable::array_type::max_size()`     | The maximum possible number of elements in the array.
    //! map         | `variable::map_type::max_size()`       | The maximum possible number of elements (pairs) in the map.

    size_type max_size() const noexcept;

    //! @brief Clears the content of the variable.
    //!
    //! Only the value is cleared. The type is not modified.
    //!
    //! Current tag | Behavior
    //! ------------|---------
    //! nullable    | No effect.
    //! boolean     | Sets the default constructed value.
    //! integer     | Sets the default constructed value.
    //! real        | Sets the default constructed value.
    //! string      | Calls `variable::string_type::clear()`.
    //! wstring     | Calls `variable::wstring_type::clear()`.
    //! u16string   | Calls `variable::u16string_type::clear()`.
    //! u32string   | Calls `variable::u32string_type::clear()`.
    //! array       | Calls `variable::array_type::clear()`.
    //! map         | Calls `variable::map_type::clear()`.
    void clear() noexcept;

    //! @brief Inserts element into variable.
    //!
    //! Current tag | Behavior
    //! ------------|---------
    //! nullable    | Create `array` and insert `element`.
    //! boolean     | Fails.
    //! integer     | Fails.
    //! real        | Fails.
    //! string      | Fails.
    //! wstring     | Fails.
    //! u16string   | Fails.
    //! u32string   | Fails.
    //! array       | Insert `element` at end.
    //! map         | Insert `element`, otherwise fails if `element` is not pair.

    iterator insert(const basic_variable& element);

    //! @brief Inserts range into variable.
    //!
    //! Current tag | Behavior
    //! ------------|---------
    //! nullable    | Create `array` and insert range.
    //! boolean     | Fails.
    //! integer     | Fails.
    //! real        | Fails.
    //! string      | Fails.
    //! wstring     | Fails.
    //! u16string   | Fails.
    //! u32string   | Fails.
    //! array       | Insert range at end.
    //! map         | Insert range, otherwise fails if any element in range is not pair.

    template <typename InputIterator>
    void insert(InputIterator begin, InputIterator end);

    //! @brief Inserts element into variable.
    //!
    //! Current tag | Behavior
    //! ------------|---------
    //! nullable    | Fails.
    //! boolean     | Fails.
    //! integer     | Fails.
    //! real        | Fails.
    //! string      | Fails.
    //! wstring     | Fails.
    //! u16string   | Fails.
    //! u32string   | Fails.
    //! array       | Insert `element` before `position`.
    //! map         | Insert `element` with `position` as hint, otherwise fails if `element` is not pair.

    iterator insert(const_iterator position, const basic_variable& element);

    //! @brief Inserts range into variable.
    //!
    //! Current tag | Behavior
    //! ------------|---------
    //! nullable    | Fails.
    //! boolean     | Fails.
    //! integer     | Fails.
    //! real        | Fails.
    //! string      | Fails.
    //! wstring     | Fails.
    //! u16string   | Fails.
    //! u32string   | Fails.
    //! array       | Insert range before `position`.
    //! map         | Insert range with `position` as hint, otherwise fails if any element in range is not pair.

    template <typename InputIterator>
    void insert(const_iterator, InputIterator begin, InputIterator end);

    //! @brief Erases an element from variable.
    //!
    //! Returns iterator following last erased element.
    //!
    //! Current tag | Behavior
    //! ------------|---------
    //! nullable    | No effect.
    //! boolean     | No effect.
    //! integer     | No effect.
    //! real        | No effect.
    //! string      | No effect.
    //! wstring     | No effect.
    //! u16string   | No effect.
    //! u32string   | No effect.
    //! array       | Erases element at `position`.
    //! map         | Erases element at `position`.

    iterator erase(iterator position);

    //! @brief Erases an element from variable.
    //!
    //! @sa basic_variable<Allocator>::erase(iterator)

    iterator erase(const_iterator position);

    //! @brief Erases range from variable.
    //!
    //! Returns iterator following last erased element.
    //!
    //! Current tag | Behavior
    //! ------------|---------
    //! nullable    | No effect.
    //! boolean     | No effect.
    //! integer     | No effect.
    //! real        | No effect.
    //! string      | No effect.
    //! wstring     | No effect.
    //! u16string   | No effect.
    //! u32string   | No effect.
    //! array       | Erases elements in range.
    //! map         | Erases elements in range.

    iterator erase(const_iterator begin, const_iterator end);

    //! @brief Exchange contents of variable and `other`.
    void swap(basic_variable& other) noexcept;

    //! @brief Returns an iterator to the beginning.

    iterator begin() &;

    //! @brief Returns an iterator to the beginning.

    const_iterator begin() const &;

    //! @brief Returns an iterator to the beginning.

    const_iterator cbegin() const &;

    //! @brief Returns an iterator to the end.

    iterator end() &;

    //! @brief Returns an iterator to the end.

    const_iterator end() const &;

    //! @brief Returns an iterator to the end.

    const_iterator cend() const &;

    //! @brief Returns a reverse iterator to the beginning.

    reverse_iterator rbegin() &;

    //! @brief Returns a reverse iterator to the beginning.

    const_reverse_iterator rbegin() const &;

    //! @brief Returns a reverse iterator to the beginning.

    const_reverse_iterator crbegin() const &;

    //! @brief Returns a reverse iterator to the end.

    reverse_iterator rend() &;

    //! @brief Returns a reverse iterator to the end.

    const_reverse_iterator rend() const&;

    //! @brief Returns a reverse iterator to the end.

    const_reverse_iterator crend() const&;

    //! @brief Returns a key iterator to the beginning.

    key_iterator key_begin() const &;

    //! @brief Returns a key iterator to the end.

    key_iterator key_end() const &;

#if !defined(BOOST_DOXYGEN_INVOKED)
private:
    bool is_pair() const;

private:
    template <typename T, typename U, typename> friend struct detail::overloader;
    template <typename A, typename U, typename> friend struct detail::iterator_overloader;
    template <typename T, typename U, typename> friend struct detail::operator_overloader;
    template <typename A, typename T, typename> friend struct detail::same_overloader;
    template <typename T> struct similar_visitor;

    using index_type = unsigned char;
    using storage_type = detail::small_union<allocator_type,
                                             std::max_align_t,
                                             index_type,
                                             nullable,
                                             bool,
                                             signed char,
                                             unsigned char,
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
                                             wstring_type,
                                             u16string_type,
                                             u32string_type,
                                             array_type,
                                             map_type>;
    storage_type storage;
#endif
};

template <typename Allocator, typename U>
basic_variable<Allocator> operator+ (const basic_variable<Allocator>&, const U&);

template <typename Allocator>
basic_variable<Allocator> operator+ (nullable, const basic_variable<Allocator>&);

// Comparison operators defined in variable.ipp

// Convenience

using variable = basic_variable<std::allocator<char>>;
using array = basic_array<std::allocator<char>>;
using map = basic_map<std::allocator<char>>;

} // namespace dynamic
} // namespace trial

#include <trial/dynamic/detail/variable.ipp>

#endif // TRIAL_DYNAMIC_VARIABLE_HPP
