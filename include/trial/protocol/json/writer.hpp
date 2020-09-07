#ifndef TRIAL_PROTOCOL_JSON_WRITER_HPP
#define TRIAL_PROTOCOL_JSON_WRITER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <stack>
#include <vector>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/json/error.hpp>
#include <trial/protocol/json/token.hpp>
#include <trial/protocol/json/detail/encoder.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

//! @brief Incremental JSON writer.
//!
//! Generate JSON output incrementally by appending C++ data.
template <typename CharT, std::size_t N = 2 * sizeof(void *)>
class basic_writer
{
public:
    using value_type = CharT;
    using size_type = std::size_t;
    using view_type = typename detail::basic_encoder<value_type, N>::view_type;

    //! @brief Construct an incremental JSON writer.
    //!
    //! The buffer type can be any for which a buffer wrapper exists.
    //!
    //! @param[in] buffer A buffer where the JSON formatted output is stored.
    template <typename T> basic_writer(T& buffer);

    std::error_code error() const BOOST_NOEXCEPT;
    size_type level() const BOOST_NOEXCEPT;

    //! @brief Write structural output.
    template <typename T>
    size_type value();

    //! @brief Write data output.
    template <typename T>
    size_type value(T&& value);

    //! @brief Write raw output.
    size_type literal(const view_type&) BOOST_NOEXCEPT;

#ifndef BOOST_DOXYGEN_INVOKED
private:
    void validate_scope();
    void validate_scope(token::code::value, enum json::errc);

    template <typename T, typename Enable = void>
    struct overloader;

    size_type null_value();
    size_type begin_array_value();
    size_type end_array_value();
    size_type begin_object_value();
    size_type end_object_value();

private:
    using encoder_type = detail::basic_encoder<value_type, N>;
    encoder_type encoder;
    mutable enum json::errc last_error;

    struct frame
    {
        frame(encoder_type& encoder, token::code::value);

        void write_separator();

        encoder_type& encoder;
        token::code::value code;
        std::size_t counter;
    };
    std::stack<frame, std::vector<frame>> stack;
#endif // BOOST_DOXYGEN_INVOKED
};

using writer = basic_writer<char>;

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/writer.ipp>

#endif // TRIAL_PROTOCOL_JSON_WRITER_HPP
