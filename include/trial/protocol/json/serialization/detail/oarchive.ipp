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

template <typename T>
oarchive::oarchive(T& buffer)
    : writer(buffer)
{
}

template <typename Tag>
void oarchive::save()
{
    writer.template value<Tag>();
}

template <typename T>
void oarchive::save(const T& data)
{
    writer.value(data);
}

template<typename T>
void oarchive::save_override(const T& data)
{
    boost::archive::save(*this, data);
}

template<typename T>
void oarchive::save_override(const T& data, long /* PFTO */)
{
    save_override(data);
}

template <typename T, std::size_t N>
inline void oarchive::save_override(const T (&data)[N])
{
    // By-pass Boost.Serialization which has its own array formatting
    serialization::save_overloader<oarchive, const T[N]>::save(*this, data, 0);
}

inline void oarchive::save_override(const char *data)
{
    save(data);
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_DETAIL_OARCHIVE_IPP
