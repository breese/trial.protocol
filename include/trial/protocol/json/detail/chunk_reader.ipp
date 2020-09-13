///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace protocol
{
namespace json
{

template <typename CharT>
bool basic_chunk_reader<CharT>::next()
{
    auto backup = *this;
    super::decoder.next();
    if (super::decoder.code() == token::code::end)
        goto error;
    if (super::next_frame())
        if (full_token())
            return true;
error:
    *this = std::move(backup);
    return false;
}

template <typename CharT>
bool basic_chunk_reader<CharT>::next(const view_type& view)
{
    if (TRIAL_UNLIKELY(super::decoder.code() == token::code::uninitialized))
    {
        // Create reader
        basic_chunk_reader other(view);
        switch (other.code())
        {
        case token::code::end:
        case token::code::error_unexpected_token:
            return false;

        default:
            if (other.full_token())
            {
                std::swap(*this, other);
                return true;
            }
            return false;
        }
    }

    // Replace decoder but retain reader state
    auto backup = *this;
    super::decoder.shift(view.data(), view.size());
    super::decoder.next();
    switch (super::decoder.code())
    {
    case token::code::error_invalid_value:
        return true;
    default:
        break;
    }
    if (super::next_frame())
        if (full_token())
            return true;
    *this = std::move(backup);
    return false;
}

template <typename CharT>
bool basic_chunk_reader<CharT>::finish(const view_type& view)
{
    if (TRIAL_UNLIKELY(super::decoder.code() == token::code::uninitialized))
    {
        // Create reader
        basic_chunk_reader other(view);
        switch (other.code())
        {
        case token::code::end:
        case token::code::error_unexpected_token:
            return false;

        default:
            std::swap(*this, other);
            return true;
        }
    }

    // Replace decoder but retain reader state
    auto backup = *this;
    super::decoder.shift(view.data(), view.size());
    super::decoder.next();
    switch (super::decoder.code())
    {
    case token::code::error_invalid_value:
        return true;
    default:
        break;
    }
    if (super::next_frame())
        return true;
    *this = std::move(backup);
    return false;
}

template <typename CharT>
void basic_chunk_reader<CharT>::shift(view_type view)
{
    super::decoder.shift(view.data(), view.size());
}

template <typename CharT>
bool basic_chunk_reader<CharT>::full_token()
{
    switch (super::decoder.code())
    {
    case token::code::integer:
    case token::code::real:
        // When a chunk ends with a number, then the number could continue into
        // the next chunk.
        return !tail().empty();
    default:
        return true;
    }
}

} // namespace json
} // namespace protocol
} // namespace trial
