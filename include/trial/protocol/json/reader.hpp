#ifndef TRIAL_PROTOCOL_JSON_READER_HPP
#define TRIAL_PROTOCOL_JSON_READER_HPP

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
#include <stack>
#include <boost/config.hpp>
#include <trial/protocol/detail/string_view.hpp>
#include <trial/protocol/json/error.hpp>
#include <trial/protocol/json/token.hpp>
#include <trial/protocol/json/detail/decoder.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

//! @brief Incremental JSON reader.
//!
//! Parse a JSON formatted input buffer incrementally. Incrementally means that
//! the reader only parses enough of the input to identify the next token.
//! The entire input has to be parsed by repeating parsing the next token until
//! the end of the input.
template <typename CharT>
class basic_reader
{
public:
    using value_type = typename detail::basic_decoder<CharT>::value_type;
    using size_type = typename detail::basic_decoder<CharT>::size_type;
    using view_type = typename detail::basic_decoder<CharT>::view_type;

    //! @brief Construct an incremental JSON reader.
    //!
    //! The first token is automatically parsed.
    //!
    //! The reader does not assume ownership of the view.
    //!
    //! @param[in] view A string view of a JSON formatted buffer.
    basic_reader(const view_type& view);

    //! @brief Copy-construct an incremental JSON reader.
    //!
    //! Copies the internal parsing state from the input reader, and continues
    //! parsing independently from where the input reader had reached.
    //!
    //! @param[in] other The reader that is copied.
    basic_reader(const basic_reader& other);

    //! @brief Parse the next token.
    //!
    //! @returns false if an error occurred or end-of-input was reached, true otherwise.
    bool next();

    //! @brief Parse the next token if current token has a given value.
    //!
    //! @param[in] expect Expected value of current token.
    //! @returns false if current token does not have the expected value.
    bool next(token::code::value expect);

    //! @brief Get the current nesting level.
    //!
    //! Keep track of the nesting level of containers.
    //! The outermost root level is 0.
    //!
    //! @returns The current nesting level.
    size_type level() const BOOST_NOEXCEPT;

    //! @brief Get the current token as a detailed code.
    //!
    //! @returns The code of the current token.
    token::code::value code() const BOOST_NOEXCEPT;

    //! @brief Get the current token as a symbol.
    //!
    //! @returns The symbol of the current token.
    token::symbol::value symbol() const BOOST_NOEXCEPT;

    //! @brief Get the current token as a category.
    //!
    //! @returns The category of the current token.
    token::category::value category() const BOOST_NOEXCEPT;

    //! @brief Get the current error.
    //!
    //! The error code contains an error enumerator. If parsing did not result
    //! in an error, the json::no_error enumerator is used.
    //!
    //! @returns The current error code.
    std::error_code error() const BOOST_NOEXCEPT;

    //! @brief Converts the current value into ReturnType.
    //!
    //! The following conversions are valid:
    //! -# Convert a symbol::boolean token into bool.
    //! -# Convert a symbol::integer token into an integral C++ type (expect bool.)
    //! -# Convert a symbol::number token into a floating-point C++ type.
    //! -# Convert a symbol::string token into std::string.
    //!
    //! @pre category() returns token::category::data
    //! @returns The converted value.
    //! @throws json::error If requested type is incompatible with the current token.
    template <typename ReturnType> ReturnType value() const;

    //! @returns A view of the current value before it is converted into its type.
    const view_type& literal() const BOOST_NOEXCEPT;

    //! @returns A view of the remaining buffer.
    const view_type& tail() const BOOST_NOEXCEPT;

#ifndef BOOST_DOXYGEN_INVOKED
private:
    template <typename ReturnType, typename Enable = void>
    struct overloader;

    template <typename ReturnType> ReturnType bool_value() const;
    template <typename ReturnType> ReturnType integer_value() const;
    template <typename ReturnType> ReturnType number_value() const;
    template <typename ReturnType> ReturnType string_value() const;

private:
    using decoder_type = detail::basic_decoder<value_type>;
    mutable decoder_type decoder;

    struct frame
    {
        frame(token::code::value);

        bool is_array() const;
        bool is_object() const;

        token::code::value next(decoder_type&);
        token::code::value check_outer(decoder_type&);
        token::code::value check_array(decoder_type&);
        token::code::value check_object(decoder_type&);

        token::code::value scope;
        size_type counter;
    };
    std::stack<frame> stack;
#endif
};

using reader = basic_reader<char>;

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/reader.ipp>

#endif // TRIAL_PROTOCOL_JSON_READER_HPP
