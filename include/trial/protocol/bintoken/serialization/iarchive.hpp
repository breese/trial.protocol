#ifndef TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_IARCHIVE_HPP
#define TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_IARCHIVE_HPP

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
#include <trial/protocol/bintoken/reader.hpp>
#include <trial/protocol/bintoken/token.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

class iarchive
    : public boost::archive::detail::common_iarchive<iarchive>
{
    friend class boost::archive::load_access;

public:
    using value_type = bintoken::reader::value_type;
    using view_type = bintoken::reader::view_type;

    template <typename T>
    iarchive(const T&);

    template <typename T>
    void load_override(T& data);
    template <typename T, std::size_t N>
    void load_override(T (&data)[N]);
    template <typename T>
    void load_override(T& data, long);

    void load(view_type&);

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
    bintoken::reader reader;
};

} // namespace bintoken
} // namespace protocol
} // namespace trial

#include <trial/protocol/bintoken/serialization/detail/iarchive.ipp>

#include <boost/archive/detail/register_archive.hpp>

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::bintoken::iarchive);

#endif // TRIAL_PROTOCOL_BINTOKEN_SERIALIZATION_IARCHIVE_HPP
