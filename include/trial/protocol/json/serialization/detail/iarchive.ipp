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

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
basic_iarchive<CharT>::basic_iarchive(const json::basic_reader<CharT>& reader)
    : reader(reader)
{
}

template <typename CharT>
basic_iarchive<CharT>::basic_iarchive(const typename json::basic_reader<CharT>::view_type& view)
    : reader(view)
{
}

template <typename CharT>
template <typename Iterator>
basic_iarchive<CharT>::basic_iarchive(Iterator begin, Iterator end)
    : reader(begin, end)
{
}

template <typename CharT>
template <typename Tag>
void basic_iarchive<CharT>::load()
{
    next(Tag::code);
}

template <typename CharT>
template <typename T>
void basic_iarchive<CharT>::load(T& value)
{
    value = reader.template value<T>();
    next();
}

template <typename CharT>
template <typename Tag>
bool basic_iarchive<CharT>::at() const
{
    return (reader.code() == Tag::code);
}

template <typename CharT>
token::code::value basic_iarchive<CharT>::code() const
{
    return reader.code();
}

template <typename CharT>
void basic_iarchive<CharT>::next()
{
    if (!reader.next() && (reader.symbol() == token::symbol::error))
    {
        throw json::error(reader.error());
    }
}

template <typename CharT>
void basic_iarchive<CharT>::next(token::code::value expect)
{
    if (!reader.next(expect) && (reader.symbol() == token::symbol::error))
    {
        throw json::error(reader.error());
    }
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_IARCHIVE_IPP
