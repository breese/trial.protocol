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

#include <cstdint>
#include <string>
#include <memory>
#include <boost/none.hpp>
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

template <typename CharT>
class basic_encoder
{
public:
    using value_type = CharT;
    using size_type = std::size_t;
    using buffer_type = buffer::base<value_type>;
    using view_type = boost::basic_string_ref<value_type>;

    template <typename T>
    basic_encoder(T&);

    //! @brief Write value
    //!
    //! Type U can be an integral type (except bool), a floating-point type, a
    //! string, or a string view.
    template <typename U> size_type value(const U&);
    template <typename U> size_type value();
    //! @brief Write boolean value
    size_type value(bool);
    //! @brief Write string literal
    size_type value(const value_type *);

    size_type literal(const view_type&);

private:
    template <typename T, typename Enable = void>
    struct overloader;

    template <typename T> size_type integral_value(const T&);
    template <typename T> size_type floating_value(const T&);
    template <typename T> size_type string_value(const T&);
    size_type null_value();
    size_type begin_array_value();
    size_type end_array_value();
    size_type begin_object_value();
    size_type end_object_value();
    size_type value_separator_value();
    size_type name_separator_value();

    size_type write(value_type);
    size_type write(const view_type&);

private:
    std::unique_ptr<buffer_type> buffer;
};

} // namespace detail
} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/encoder.ipp>

#endif // TRIAL_PROTOCOL_JSON_DETAIL_ENCODER_HPP
