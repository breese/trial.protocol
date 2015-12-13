#ifndef TRIAL_PROTOCOL_JSON_SERIALIZATION_IARCHIVE_HPP
#define TRIAL_PROTOCOL_JSON_SERIALIZATION_IARCHIVE_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <trial/protocol/json/reader.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

class iarchive
    : public boost::archive::detail::common_iarchive<iarchive>
{
    friend class boost::archive::load_access;

public:
    iarchive(const json::reader&);
    iarchive(const json::reader::view_type&);
    template <typename Iterator>
    iarchive(Iterator begin, Iterator end);

    template<typename value_type>
    void load_override(value_type& data);

    template<typename value_type>
    void load_override(value_type& data, long);

    template <typename T, std::size_t N>
    void load_override(T (&data)[N]);

    template <typename Tag>
    void load();

    template <typename T>
    void load(T&);

    template <typename Tag>
    bool at() const;

    token::code::value code() const;
    token::symbol::value symbol() const;
    token::category::value category() const;

#ifndef BOOST_DOXYGEN_INVOKED
    // Ignore these
    void load(boost::archive::version_type&) {}
    void load(boost::archive::object_id_type) {}
    void load(boost::archive::object_reference_type) {}
    void load(boost::archive::class_id_type) {}
    void load(boost::archive::class_id_optional_type) {}
    void load(boost::archive::class_id_reference_type) {}
    void load(boost::archive::tracking_type) {}
    void load(boost::archive::class_name_type&) {}
#endif

#ifndef BOOST_DOXYGEN_INVOKED
private:
    void next();
    void next(token::code::value);

private:
    json::reader reader;
#endif
};

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/serialization/detail/iarchive.ipp>
#include <boost/archive/detail/register_archive.hpp>

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::json::iarchive);

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_IARCHIVE_HPP
