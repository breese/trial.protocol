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

template <typename Reader>
class basic_iarchive
    : public boost::archive::detail::common_iarchive< basic_iarchive<Reader> >
{
    friend class boost::archive::load_access;

public:
    using reader_type = typename std::decay<Reader>::type;
    using value_type = typename reader_type::value_type;

    basic_iarchive(Reader);

    template <typename T,
              typename = typename std::enable_if<!std::is_same<basic_iarchive, typename std::decay<T>::type>::value>::type>
    basic_iarchive(T&&);

    template<typename T>
    void load_override(T& data);

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

    const reader_type& reader() const;

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
    struct
    {
        Reader reader;
    } member;
#endif
};

using iarchive = basic_iarchive<basic_reader<char>>;
using iarchive_view = basic_iarchive<basic_reader<char>&>;

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/serialization/detail/iarchive.ipp>
#include <boost/archive/detail/register_archive.hpp>

BOOST_SERIALIZATION_REGISTER_ARCHIVE(trial::protocol::json::iarchive)

#endif // TRIAL_PROTOCOL_JSON_SERIALIZATION_IARCHIVE_HPP
