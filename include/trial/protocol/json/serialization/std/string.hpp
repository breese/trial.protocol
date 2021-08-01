#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_STRING_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_STRING_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/serialization/serialization.hpp>
#include <trial/protocol/core/serialization/std/string.hpp>

namespace trial
{
namespace protocol
{
namespace serialization
{

template <typename CharT>
struct save_overloader< protocol::json::basic_oarchive<CharT>,
                        std::basic_string<CharT> >
{
    static void save(protocol::json::basic_oarchive<CharT>& ar,
                     const std::basic_string<CharT>& data,
                     const unsigned int)
    {
        ar.save(data);
    }
};

template <typename Reader>
struct load_overloader< protocol::json::basic_iarchive<Reader>,
                        std::basic_string<typename std::decay<Reader>::type::value_type> >
{
    using value_type = typename std::decay<Reader>::type::value_type;
    static void load(protocol::json::basic_iarchive<Reader>& ar,
                     std::basic_string<value_type>& data,
                     const unsigned int)
    {
        ar.load(data);
    }
};

} // namespace serialization
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_STD_STRING_HPP
