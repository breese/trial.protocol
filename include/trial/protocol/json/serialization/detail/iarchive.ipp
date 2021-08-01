#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/serialization/detail/array_load.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename Reader>
basic_iarchive<Reader>::basic_iarchive(Reader reader)
    : member{ std::forward<Reader>(reader) }
{
}

template <typename Reader>
template <typename T, typename>
basic_iarchive<Reader>::basic_iarchive(T&& input)
    : member{ Reader{std::forward<T>(input)} }
{
}

template <typename Reader>
template<typename T>
void basic_iarchive<Reader>::load_override(T& data)
{
    serialization::load_overloader<basic_iarchive<Reader>, T>::
        load(*this, data, 0);
}

template <typename Reader>
template<typename T>
void basic_iarchive<Reader>::load_override(T& data, long protocol_version)
{
    serialization::load_overloader<basic_iarchive<Reader>, T>::
        load(*this, data, protocol_version);
}

template <typename Reader>
template <typename Tag>
void basic_iarchive<Reader>::load()
{
    next(Tag::code);
}

template <typename Reader>
template <typename T>
void basic_iarchive<Reader>::load(T& value)
{
    value = member.reader.template value<T>();
    next();
}

template <typename Reader>
template <typename Tag>
bool basic_iarchive<Reader>::at() const
{
    return (member.reader.code() == Tag::code);
}

template <typename Reader>
token::code::value basic_iarchive<Reader>::code() const
{
    return member.reader.code();
}

template <typename Reader>
token::symbol::value basic_iarchive<Reader>::symbol() const
{
    return member.reader.symbol();
}

template <typename Reader>
token::category::value basic_iarchive<Reader>::category() const
{
    return member.reader.category();
}

template <typename Reader>
auto basic_iarchive<Reader>::reader() const -> const reader_type&
{
    return member.reader;
}

template <typename Reader>
void basic_iarchive<Reader>::next()
{
    if (!member.reader.next() && (member.reader.symbol() == token::symbol::error))
    {
        throw json::error(member.reader.error());
    }
}

template <typename Reader>
void basic_iarchive<Reader>::next(token::code::value expect)
{
    if (!member.reader.next(expect) && (member.reader.symbol() == token::symbol::error))
    {
        throw json::error(member.reader.error());
    }
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP
