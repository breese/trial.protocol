#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_OARCHIVE_IPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_OARCHIVE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/serialization/detail/array_save.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
template <typename T>
basic_oarchive<CharT>::basic_oarchive(T& buffer)
    : writer(buffer)
{
}

template <typename CharT>
template <typename Tag>
void basic_oarchive<CharT>::save()
{
    writer.template value<Tag>();
}

template <typename CharT>
template <typename T>
void basic_oarchive<CharT>::save(const T& data)
{
    writer.value(data);
}

template <typename CharT>
template<typename T>
void basic_oarchive<CharT>::save_override(const T& data, long protocol_version)
{
    serialization::save_overloader<basic_oarchive<CharT>, T>::
        save(*this, data, protocol_version);
}

template <typename CharT>
void basic_oarchive<CharT>::save_override(const char *data)
{
    save(data);
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_OARCHIVE_IPP
