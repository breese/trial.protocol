#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_OARCHIVE_IPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_OARCHIVE_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/bintoken/serialization/detail/array_save.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

template <typename T>
oarchive::oarchive(T& buffer)
    : writer(buffer)
{
}

template <typename T>
inline void oarchive::save_override(const T& data, long protocol_version)
{
    serialization::save_overloader<oarchive, T>::
        save(*this, data, protocol_version);
}

template <typename T>
void oarchive::save(const T& data)
{
    writer.value(data);
}

template <typename T>
void oarchive::save()
{
    writer.value<T>();
}

template <typename T>
void oarchive::save_array(const T *data, std::size_t size)
{
    writer.array(data, size);
}

} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_OARCHIVE_IPP
