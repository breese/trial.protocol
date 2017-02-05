#ifndef TRIAL_PROTOCOL_SERIALIZATION_SERIALIZATION_HPP
#define TRIAL_PROTOCOL_SERIALIZATION_SERIALIZATION_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>
#include <boost/serialization/split_free.hpp>

// Non-intrusive serialization

namespace trial
{
namespace protocol
{
namespace serialization
{

//-----------------------------------------------------------------------------
// Traits
//-----------------------------------------------------------------------------

template <typename Archive, typename Type, typename Enable = void>
struct has_serialize
{
    enum { value = 0 };
};

template <typename Archive, typename Type>
struct has_serialize<Archive, Type, typename std::enable_if<std::is_class<Type>::value>::type>
{
private:
    template <typename T, T> struct type_check;

    typedef char yes[1];
    typedef char no[2];

    template <typename A, typename T> struct signature_ptr
    {
        typedef void (T::*type)(A&, const unsigned int);
    };

    template <typename A, typename T> static no& has(...);
    template <typename A, typename T> static yes& has(type_check< typename signature_ptr<A, T>::type,
                                                                  &T::template serialize<A> >*);

public:
    enum { value = (sizeof(has<Archive, Type>(0)) == sizeof(yes)) };
};

template <typename Archive, typename Type, typename Enable = void>
struct has_load
{
    enum { value = 0 };
};

template <typename Archive, typename Type>
struct has_load<Archive, Type, typename std::enable_if<std::is_class<Type>::value>::type>
{
private:
    template <typename T, T> struct type_check;

    typedef char yes[1];
    typedef char no[2];

    template <typename A, typename T> struct signature_ptr
    {
        typedef void (T::*type)(A&, const unsigned int);
    };

    template <typename A, typename T> static no& has(...);
    template <typename A, typename T> static yes& has(type_check< typename signature_ptr<A, T>::type,
                                                                  &T::template load<A> >*);

public:
    enum { value = (sizeof(has<Archive, Type>(0)) == sizeof(yes)) };
};

template <typename Archive, typename Type, typename Enable = void>
struct has_save
{
    enum { value = 0 };
};

template <typename Archive, typename Type>
struct has_save<Archive, Type, typename std::enable_if<std::is_class<Type>::value>::type>
{
private:
    template <typename T, T> struct type_check;

    typedef char yes[1];
    typedef char no[2];

    template <typename A, typename T> struct signature_ptr
    {
        typedef void (T::*type)(A&, const unsigned int);
    };

    template <typename A, typename T> static no& has(...);
    template <typename A, typename T> static yes& has(type_check< typename signature_ptr<A, T>::type,
                                                                  &T::template save<A> >*);

public:
    enum { value = (sizeof(has<Archive, Type>(0)) == sizeof(yes)) };
};

//-----------------------------------------------------------------------------
// Generalized overloaders.
//
// These must be specialized by the concrete archives.
//-----------------------------------------------------------------------------

template <typename Archive, typename Value, typename Enable = void>
struct save_overloader
{
};

template <typename Archive, typename Value, typename Enable = void>
struct load_overloader
{
};

template <typename Archive, typename Value, typename Enable = void>
struct serialize_overloader
{
    // If the compiler complains about a missing serialize function here
    // then you need to add serialization to the Value type, either
    // intrusively by adding a serialize() function or non-intrusively
    // by adding a serialize_overloader specialization (or by including
    // the appropriate header files for pre-defined types.)
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_SERIALIZATION_SERIALIZATION_HPP
