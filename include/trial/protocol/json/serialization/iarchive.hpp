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
#include <boost/optional.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <trial/protocol/json/reader.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
class basic_iarchive
    : public boost::archive::detail::common_iarchive< basic_iarchive<CharT> >
{
    friend class boost::archive::load_access;

public:
    basic_iarchive(const json::basic_reader<CharT>&);
    basic_iarchive(const typename json::basic_reader<CharT>::view_type&);
    template <typename Iterator>
    basic_iarchive(Iterator begin, Iterator end);

    template<typename value_type>
    void load_override(value_type& data)
    {
        boost::archive::load(*this->This(), data);
    }

    template<typename value_type>
    void load_override(value_type& data, long /* version */)
    {
        load_override(data);
    }

    template <typename Tag>
    void load();

    template <typename T>
    void load(T&);

    template <typename Tag>
    bool at() const;

    token::code::value code() const;

    // Ignore these
    void load(boost::archive::version_type&) {}
    void load(boost::archive::object_id_type) {}
    void load(boost::archive::object_reference_type) {}
    void load(boost::archive::class_id_type) {}
    void load(boost::archive::class_id_optional_type) {}
    void load(boost::archive::class_id_reference_type) {}
    void load(boost::archive::tracking_type) {}
    void load(boost::archive::class_name_type&) {}

private:
    void next();
    void next(token::code::value);

private:
    json::basic_reader<CharT> reader;
};

typedef basic_iarchive<char> iarchive;

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/serialization/detail/iarchive.ipp>
#include <boost/archive/detail/register_archive.hpp>

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::json::iarchive);

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_IARCHIVE_HPP
