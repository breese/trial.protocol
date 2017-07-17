#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_OARCHIVE_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_OARCHIVE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/archive/detail/common_oarchive.hpp>
#include <trial/protocol/bintoken/writer.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

class oarchive
    : public boost::archive::detail::common_oarchive<oarchive>
{
    friend class boost::archive::save_access;

public:
    template <typename T>
    oarchive(T&);

    template <typename T>
    void save_override(const T& data);

    template <typename T>
    void save_override(const T& data, long);

    template <typename T>
    void save(const T& data);

    template <typename T>
    void save();

    template <typename T>
    void save_array(const T *data, std::size_t size);

    // Ignore these
    void save_override(const boost::archive::version_type, int) {}
    void save_override(const boost::archive::object_id_type, int) {}
    void save_override(const boost::archive::object_reference_type, int) {}
    void save_override(const boost::archive::class_id_type, int) {}
    void save_override(const boost::archive::class_id_optional_type, int) {}
    void save_override(const boost::archive::class_id_reference_type, int) {}
    void save_override(const boost::archive::tracking_type, int) {}
    void save_override(const boost::archive::class_name_type&, int) {}

protected:
    bintoken::writer writer;
};

} // namespace bintoken
} // namespace protocol
} // namespace trial

#include <trial/protocol/bintoken/serialization/detail/oarchive.ipp>

#include <boost/archive/detail/register_archive.hpp>

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::bintoken::oarchive)

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_OARCHIVE_HPP
