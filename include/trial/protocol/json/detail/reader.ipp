#ifndef TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
#define TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <type_traits>
#include <trial/protocol/detail/type_traits.hpp>

namespace trial
{
namespace protocol
{
namespace json
{

//-----------------------------------------------------------------------------
// reader::overloader
//-----------------------------------------------------------------------------

template <typename CharT>
template <typename ReturnType, typename Enable>
struct basic_reader<CharT>::overloader
{
};

// Integers (not booleans)

template <typename CharT>
template <typename ReturnType>
struct basic_reader<CharT>::overloader<
    ReturnType,
    typename std::enable_if<std::is_integral<ReturnType>::value &&
                            !protocol::detail::is_bool<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_reader<CharT>& self)
    {
        return self.template integer_value<ReturnType>();
    }
};

// Floating-point numbers

template <typename CharT>
template <typename ReturnType>
struct basic_reader<CharT>::overloader<
    ReturnType,
    typename std::enable_if<std::is_floating_point<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_reader<CharT>& self)
    {
        return self.template number_value<ReturnType>();
    }
};

// Booleans

template <typename CharT>
template <typename ReturnType>
struct basic_reader<CharT>::overloader<
    ReturnType,
    typename std::enable_if<protocol::detail::is_bool<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_reader<CharT>& self)
    {
        return self.template bool_value<ReturnType>();
    }
};

// Strings

template <typename CharT>
template <typename ReturnType>
struct basic_reader<CharT>::overloader<
    ReturnType,
    typename std::enable_if<std::is_same< ReturnType, std::basic_string<CharT> >::value>::type>
{
    using return_type = std::basic_string<CharT>;

    inline static return_type value(const basic_reader<CharT>& self)
    {
        return self.template string_value<return_type>();
    }
};

//-----------------------------------------------------------------------------
// basic_reader
//-----------------------------------------------------------------------------

template <typename CharT>
basic_reader<CharT>::basic_reader(const view_type& input)
    : decoder(input)
{
    stack.push(token::code::end);
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const basic_reader<CharT>& other)
    : decoder(other.decoder)
{
    stack.push(token::code::end);
}

template <typename CharT>
typename basic_reader<CharT>::size_type
basic_reader<CharT>::level() const BOOST_NOEXCEPT
{
    assert(stack.size() > 0);
    return stack.size() - 1;
}

template <typename CharT>
token::code::value basic_reader<CharT>::code() const BOOST_NOEXCEPT
{
    return decoder.code();
}

template <typename CharT>
token::symbol::value basic_reader<CharT>::symbol() const BOOST_NOEXCEPT
{
    return decoder.symbol();
}

template <typename CharT>
token::category::value basic_reader<CharT>::category() const BOOST_NOEXCEPT
{
    return decoder.category();
}

template <typename CharT>
std::error_code basic_reader<CharT>::error() const BOOST_NOEXCEPT
{
    return decoder.error();
}

template <typename CharT>
bool basic_reader<CharT>::next()
{
    const token::code::value current = decoder.code();
    switch (current)
    {
    case token::code::begin_array:
        stack.push(token::code::end_array);
        break;

    case token::code::end_array:
        if (stack.empty())
        {
            decoder.code(token::code::error_unbalanced_end_array);
            return false;
        }
        if (!stack.top().is_array())
        {
            decoder.code(token::code::error_expected_end_array);
            return false;
        }
        stack.pop();
        break;

    case token::code::begin_object:
        stack.push(token::code::end_object);
        break;

    case token::code::end_object:
        if (stack.empty())
        {
            decoder.code(token::code::error_unbalanced_end_object);
            return false;
        }
        if (!stack.top().is_object())
        {
            decoder.code(token::code::error_expected_end_object);
            return false;
        }
        stack.pop();
        break;

    default:
        break;
    }

    if (stack.empty())
    {
        decoder.code(token::code::error_unexpected_token);
    }
    else
    {
        decoder.code(stack.top().next(decoder));
    }

    return (category() != token::category::status);
}

template <typename CharT>
bool basic_reader<CharT>::next(token::code::value expect)
{
    const token::code::value current = code();
    if (current != expect)
    {
        decoder.code(token::code::error_unexpected_token);
        return false;
    }
    return next();
}

template <typename CharT>
template <typename T>
T basic_reader<CharT>::value() const
{
    using return_type = typename std::remove_cv<typename std::decay<T>::type>::type;
    return basic_reader<CharT>::overloader<return_type>::value(*this);
}

template <typename CharT>
const typename basic_reader<CharT>::view_type&
basic_reader<CharT>::literal() const BOOST_NOEXCEPT
{
    return decoder.literal();
}

template <typename CharT>
const typename basic_reader<CharT>::view_type&
basic_reader<CharT>::tail() const BOOST_NOEXCEPT
{
    return decoder.tail();
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_reader<CharT>::bool_value() const
{
    switch (decoder.code())
    {
    case token::code::true_value:
        return true;

    case token::code::false_value:
        return false;

    default:
        decoder.code(token::code::error_invalid_value);
        throw json::error(error());
    }
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_reader<CharT>::integer_value() const
{
    switch (decoder.code())
    {
    case token::code::integer:
        {
            // FIXME: Raise error if value is too large
            ReturnType result = decoder.template value<ReturnType>();
            if (decoder.symbol() == token::symbol::error)
            {
                throw json::error(error());
            }
            return result;
        }

    case token::code::number:
        using number_return_type = typename protocol::detail::make_floating_point<typename std::make_signed<ReturnType>::type>::type;
        return ReturnType(std::round(decoder.template value<number_return_type>()));

    default:
        decoder.code(token::code::error_invalid_value);
        throw json::error(error());
    }
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_reader<CharT>::number_value() const
{
    switch (decoder.code())
    {
    case token::code::integer:
        using integer_return_type = typename protocol::detail::make_integral<ReturnType>::type;
        return ReturnType(decoder.template value<integer_return_type>());

    case token::code::number:
        return decoder.template value<ReturnType>();

    default:
        decoder.code(token::code::error_invalid_value);
        throw json::error(error());
    }
}

template <typename CharT>
template <typename ReturnType>
ReturnType basic_reader<CharT>::string_value() const
{
    switch (decoder.code())
    {
    case token::code::string:
        return decoder.template value<ReturnType>();

    default:
        decoder.code(token::code::error_invalid_value);
        throw json::error(error());
    }
}

template <typename CharT>
basic_reader<CharT>::frame::frame(token::code::value scope)
    : scope(scope),
      counter(0)
{
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_array() const
{
    return scope == token::code::end_array;
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_object() const
{
    return scope == token::code::end_object;
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next(decoder_type& decoder)
{
    decoder.next();

    switch (scope)
    {
    case token::code::end:
        return check_outer(decoder);

    case token::code::end_array:
        return check_array(decoder);

    case token::code::end_object:
        return check_object(decoder);

    default:
        return token::code::error_unexpected_token;
    }
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::check_outer(decoder_type& decoder)
{
    // RFC 7159, section 2
    //
    // JSON-text = value

    switch (decoder.code())
    {
    case token::code::value_separator:
    case token::code::name_separator:
        return token::code::error_unexpected_token;

    default:
        return decoder.code();
    }
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::check_array(decoder_type& decoder)
{
    // RFC 7159, section 5
    //
    // array = begin-array [ value *( value-separator value ) ] end-array

    const token::code::value current = decoder.code();

    ++counter;
    if (counter % 2 == 0)
    {
        // Expect separator
        switch (current)
        {
        case token::code::end_array:
            return current;

        case token::code::value_separator:
            // Skip over separator
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.code() == token::code::end_array)
                return token::code::error_unexpected_token;
            return decoder.code();

        default:
            return token::code::error_expected_end_array;
        }
    }
    else
    {
        // Expect value
        switch (current)
        {
        case token::code::value_separator:
            return token::code::error_unexpected_token;

        case token::code::name_separator:
            return token::code::error_unexpected_token;

        case token::code::end_array:
            return current;

        case token::code::end_object:
            return token::code::error_expected_end_array;

        default:
            break;
        }
        return current;
    }
    return token::code::error_unexpected_token;
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::check_object(decoder_type& decoder)
{
    // RFC 7159, section 4
    //
    // object = begin-object [ member *( value-separator member ) ]
    //          end-object
    //
    // member = string name-separator value

    const token::code::value current = decoder.code();

    ++counter;
    if (counter % 4 == 0)
    {
        // Expect value separator
        switch (current)
        {
        case token::code::end_object:
            return current;

        case token::code::value_separator:
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.code() == token::code::end_object)
                return token::code::error_unexpected_token;
            return decoder.code();

        default:
            return token::code::error_expected_end_object;
        }
    }
    else if (counter % 4 == 2)
    {
        // Expect name separator
        if (current == token::code::name_separator)
        {
            decoder.next();
            ++counter;
            switch (decoder.code())
            {
            case token::code::end_array:
            case token::code::end_object:
                return token::code::error_unexpected_token;

            default:
                return decoder.code();
            }
        }
    }
    else
    {
        // Expect value
        switch (current)
        {
        case token::code::value_separator:
        case token::code::name_separator:
            return token::code::error_unexpected_token;

        case token::code::end_array:
            return token::code::error_expected_end_object;

        case token::code::end_object:
            return current;

        default:
            // Key must be string type
            if ((counter % 4 == 1) && (current != token::code::string))
                return token::code::error_invalid_key;
            return current;
        }
    }

    return token::code::error_unexpected_token;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
