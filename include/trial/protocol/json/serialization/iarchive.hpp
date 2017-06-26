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

template <typename CharT>
class basic_iarchive
    : public boost::archive::detail::common_iarchive< basic_iarchive<CharT> >
{
    friend class boost::archive::load_access;

public:
    using value_type = CharT;

    basic_iarchive(const json::reader&);
    basic_iarchive(const json::reader::view_type&);
    template <typename Iterator>
    basic_iarchive(Iterator begin, Iterator end);

    template<typename T>
    void load_override(T& data, long);

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
    json::basic_reader<value_type> reader;
#endif
};

using iarchive = basic_iarchive<char>;

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/serialization/detail/iarchive.ipp>
#include <boost/archive/detail/register_archive.hpp>

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::json::iarchive)

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_IARCHIVE_HPP
