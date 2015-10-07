#ifndef TRIAL_PROTOCOL_TRANSENC_DETAIL_ENCODER_HPP
#define TRIAL_PROTOCOL_TRANSENC_DETAIL_ENCODER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstddef> // std::size_t
#include <string>
#include <boost/cstdint.hpp>
#include <boost/utility/string_ref.hpp>
#include <boost/scoped_ptr.hpp>
#include <trial/protocol/transenc/token.hpp>

namespace trial
{
namespace protocol
{
namespace transenc
{
namespace detail
{

class encoder
{
public:
    typedef boost::uint8_t value_type;
    typedef std::size_t size_type;
    typedef boost::basic_string_ref<value_type> view_type;
    typedef boost::basic_string_ref<char> string_view_type;

    template <typename T>
    encoder(T&);

    template <typename T> size_type value();
    size_type value(bool);
    size_type value(token::int8::type);
    size_type value(token::int16::type);
    size_type value(token::int32::type);
    size_type value(token::int64::type);
    size_type value(token::float32::type);
    size_type value(token::float64::type);
    size_type value(const string_view_type&);
    size_type value(const char *);
    size_type value(const char *, size_type);
    size_type binary(const value_type *, size_type);
    size_type binary(const view_type&);

private:
    size_type write_length(boost::uint8_t);
    size_type write_length(boost::uint16_t);
    size_type write_length(boost::uint32_t);
    size_type write_length(boost::uint64_t);
    size_type write(value_type);
    size_type write(const view_type&);

private:
    typedef buffer::base<value_type> buffer_type;
    boost::scoped_ptr<buffer_type> buffer;
};

} // namespace detail
} // namespace transenc
} // namespace protocol
} // namespace trial

#include <trial/protocol/transenc/detail/encoder.ipp>

#endif // TRIAL_PROTOCOL_TRANSENC_DETAIL_ENCODER_HPP
