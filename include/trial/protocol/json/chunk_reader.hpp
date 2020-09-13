#ifndef TRIAL_PROTOCOL_JSON_CHUNK_READER_HPP
#define TRIAL_PROTOCOL_JSON_CHUNK_READER_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/protocol/json/reader.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
class basic_chunk_reader
    : protected basic_reader<CharT>
{
    using super = basic_reader<CharT>;
    using typename super::decoder_type;

public:
    using typename super::value_type;
    using typename super::size_type;
    using typename super::view_type;

    using super::super;

    //! @brief Parse the next token.
    //!
    //! @returns false if an error occurred or end-of-input was reached, true otherwise.

    bool next();

    //! @brief Parse the next token from a new view.
    //!
    //! The reader replaces its internal view with the @c view passed as
    //! argument.
    //!
    //! The nesting levels are retained.
    //!
    //! @param[in] view  A string view of a JSON formatted chunk.
    //! @returns false if an error occurred or end-of-input was reached, true otherwise.

    bool next(const view_type& view);

    //! @brief Parse the final token from a new view.
    //!
    //! This function is only necessary when parsing numbers at the outer scope.

    bool finish(const view_type& view);

    //! @brief Adjust the view.
    //!
    //! When chunk parsing fails due to insufficient input, the remaining unparsed
    //! input (tail()) must be placed at the beginning of the subsequent input view.
    //! The reader must be informed when the tail is moved in memory. This causes
    //! the reader to enter a special shifted state that is recognized by the
    //! subsequent call to next() or next(view_type).
    //!
    //! @param[in] view A string view of a JSON formatted chunk.
    //!
    //! @pre view.size() <= size()
    //!
    //! @post code() == json::token::code::shifted
    //! @post size() == 0
    //! @post literal() == view

    void shift(view_type view);

    using super::level;
    using super::code;
    using super::symbol;
    using super::category;
    using super::error;
    using super::value;
    using super::string;
    using super::literal;
    using super::tail;

private:
    bool next_frame();
    bool full_token();
};

using chunk_reader = basic_chunk_reader<char>;

} // namespace json
} // namespace protocol
} // namespace trial

#include <trial/protocol/json/detail/chunk_reader.ipp>

#endif // TRIAL_PROTOCOL_JSON_CHUNK_READER_HPP
