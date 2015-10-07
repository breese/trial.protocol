#ifndef TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_IARCHIVE_HPP
#define TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_IARCHIVE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/optional.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <trial/protocol/transenc/reader.hpp>
#include <trial/protocol/transenc/token.hpp>

namespace trial
{
namespace protocol
{
namespace transenc
{

class iarchive
    : public boost::archive::detail::common_iarchive<iarchive>
{
    friend class boost::archive::load_access;

public:
    typedef transenc::reader::value_type value_type;

    template <typename T>
    iarchive(const T&);

    template <typename T>
    void load_override(T& data)
    {
        boost::archive::load(*this->This(), data);
    }

    template <typename T>
    void load_override(T& data, long /* version */)
    {
        load_override(data);
    }

    template <typename T>
    void load(T&);

    template <typename Tag>
    void load();

    template <typename Tag>
    bool at() const;

    token::code::value code() const;
    token::symbol::value symbol() const;
    token::category::value category() const;

    // Ignore these
    void load(boost::archive::version_type&) {}
    void load(boost::archive::object_id_type) {}
    void load(boost::archive::object_reference_type) {}
    void load(boost::archive::class_id_type) {}
    void load(boost::archive::class_id_optional_type) {}
    void load(boost::archive::class_id_reference_type) {}
    void load(boost::archive::tracking_type) {}
    void load(boost::archive::class_name_type&) {}

    void next();
    void next(token::code::value);

private:
    transenc::reader reader;
};

} // namespace transenc
} // namespace protocol
} // namespace trial

#include <trial/protocol/transenc/serialization/detail/iarchive.ipp>

#include <boost/archive/detail/register_archive.hpp>

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::transenc::iarchive);

#endif // TRIAL_PROTOCOL_TRANSENC_SERIALIZATION_IARCHIVE_HPP
