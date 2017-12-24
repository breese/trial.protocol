#ifndef TRIAL_PROTOCOL_BINTOKEN_READER_HPP
#define TRIAL_PROTOCOL_BINTOKEN_READER_HPP

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
#include <stack>
#include <trial/protocol/bintoken/error.hpp>
#include <trial/protocol/bintoken/detail/decoder.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

class reader
{
public:
    using size_type = std::size_t;
    using value_type = detail::decoder::value_type;
    using view_type = detail::decoder::view_type;

    reader(view_type);
    template <typename T> reader(const T&);

    //! @brief Advance to the next token.
    bool next() BOOST_NOEXCEPT;
    bool next(token::code::value) BOOST_NOEXCEPT;

    //! @brief Returns the current token.
    token::code::value code() const BOOST_NOEXCEPT;

    //! @brief Returns the symbol of the current token.
    token::symbol::value symbol() const BOOST_NOEXCEPT;

    //! @brief Returns the category of the current token.
    token::category::value category() const BOOST_NOEXCEPT;

    //! @brief Returns the last error code.
    std::error_code error() const BOOST_NOEXCEPT;

    //! @brief Returns the length of the current token.
    //!
    //! @throws system_error if current token is a group.
    size_type length() const;

    //! @brief Returns the current nesting level.
    size_type level() const BOOST_NOEXCEPT;

    //! @brief Return the current value.
    //!
    //! @throws system_error if requested type is incompatible with the current token.
    template <typename ReturnType>
    typename token::type_cast<ReturnType>::type value() const;

    //! @brief Put current value into output buffer.
    //!
    //! @param[out] output Contiguous storage where current values are placed.
    //! @param[in] output_length Number of items in storage.
    //!
    //! @throws system_error if requested type is incompatible with the current token.
    template <typename T>
    size_type array(T* output, size_type output_length) const;

    //! @brief Return a view of the current value before it is converted into its type.
    const view_type& literal() const BOOST_NOEXCEPT;

private:
    template <typename ReturnType, typename Enable = void> struct overloader;

    mutable detail::decoder decoder;
    std::stack<token::code::value> stack;
};

} // namespace bintoken
} // namespace protocol
} // namespace trial

#include <trial/protocol/bintoken/detail/reader.ipp>

#endif // TRIAL_PROTOCOL_BINTOKEN_READER_HPP
