#ifndef TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP
#define TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP

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
#include <boost/cstdint.hpp>
#include <boost/none.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/utility/string_ref.hpp>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace json
{
namespace detail
{

class encoder
{
public:
    typedef char value_type;
    typedef std::size_t size_type;
    typedef buffer::base<value_type> buffer_type;
    typedef boost::basic_string_ref<char> view_type;

    template <typename T>
    encoder(T&);

    //! @brief Write value
    //!
    //! Type U can be an integral type (except bool), a floating-point type, a
    //! string, or a string view.
    template <typename U> size_type value(const U&);
    template <typename U> size_type value();
    //! @brief Write boolean value
    size_type value(bool);
    //! @brief Write string literal
    size_type value(const char *);

    size_type literal(const view_type&);

private:
    template <typename T, typename Enable = void> struct overloader;

    boost::scoped_ptr<buffer_type> buffer;
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/encoder.ipp>

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP
