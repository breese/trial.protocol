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

#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/math/special_functions/round.hpp>
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

template <typename ReturnType, typename Enable>
struct reader::overloader
{
};

// Integers (not booleans)

template <typename ReturnType>
struct reader::overloader<ReturnType,
                          typename boost::enable_if_c< boost::is_integral<ReturnType>::value && !boost::is_same<ReturnType, bool>::value >::type>
{
    inline static ReturnType value(const reader& self)
    {
        return self.integral_value<ReturnType>();
    }
};

// Floating-point numbers

template <typename ReturnType>
struct reader::overloader<ReturnType,
                          typename boost::enable_if< boost::is_floating_point<ReturnType> >::type>
{
    inline static ReturnType value(const reader& self)
    {
        return self.floating_value<ReturnType>();
    }
};

// Booleans

template <typename ReturnType>
struct reader::overloader<ReturnType,
                          typename boost::enable_if< boost::is_same<ReturnType, bool> >::type>
{
    inline static ReturnType value(const reader& self)
    {
        return self.bool_value<ReturnType>();
    }
};

// Strings

template <>
struct reader::overloader<std::string>
{
    typedef std::string return_type;

    inline static return_type value(const reader& self)
    {
        return self.string_value<return_type>();
    }
};

//-----------------------------------------------------------------------------
// reader
//-----------------------------------------------------------------------------

inline reader::reader(const view_type& input)
    : decoder(input)
{
    stack.push(token::code::end);
}

inline reader::reader(const reader& other)
    : decoder(other.decoder)
{
    stack.push(token::code::end);
}

inline reader::size_type reader::level() const BOOST_NOEXCEPT
{
    assert(stack.size() > 0);
    return stack.size() - 1;
}

inline token::code::value reader::code() const BOOST_NOEXCEPT
{
    return decoder.code();
}

inline token::symbol::value reader::symbol() const BOOST_NOEXCEPT
{
    return decoder.symbol();
}

inline token::category::value reader::category() const BOOST_NOEXCEPT
{
    return decoder.category();
}

inline boost::system::error_code reader::error() const BOOST_NOEXCEPT
{
    return decoder.error();
}

inline bool reader::next()
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

inline bool reader::next(token::code::value expect)
{
    const token::code::value current = code();
    if (current != expect)
    {
        decoder.code(token::code::error_unexpected_token);
        return false;
    }
    return next();
}

template <typename T>
T reader::value() const
{
    typedef typename boost::remove_cv<typename boost::decay<T>::type>::type return_type;
    return overloader<return_type>::value(*this);
}

inline const reader::view_type& reader::literal() const BOOST_NOEXCEPT
{
    return decoder.literal();
}

template <typename ReturnType>
ReturnType reader::bool_value() const
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

template <typename ReturnType>
ReturnType reader::integral_value() const
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

    case token::code::floating:
        typedef typename protocol::detail::integer_to_floating<typename boost::make_signed<ReturnType>::type>::type floating_return_type;
        return ReturnType(boost::math::round(decoder.template value<floating_return_type>()));

    default:
        decoder.code(token::code::error_invalid_value);
        throw json::error(error());
    }
}

template <typename ReturnType>
ReturnType reader::floating_value() const
{
    switch (decoder.code())
    {
    case token::code::integer:
        typedef typename protocol::detail::floating_to_integer<ReturnType>::type integer_return_type;
        return ReturnType(decoder.template value<integer_return_type>());

    case token::code::floating:
        return decoder.template value<ReturnType>();

    default:
        decoder.code(token::code::error_invalid_value);
        throw json::error(error());
    }
}

template <typename ReturnType>
ReturnType reader::string_value() const
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

inline reader::frame::frame(token::code::value scope)
    : scope(scope),
      counter(0)
{
}

inline bool reader::frame::is_array() const
{
    return scope == token::code::end_array;
}

inline bool reader::frame::is_object() const
{
    return scope == token::code::end_object;
}

inline token::code::value reader::frame::next(decoder_type& decoder)
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

inline token::code::value reader::frame::check_outer(decoder_type& decoder)
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

inline token::code::value reader::frame::check_array(decoder_type& decoder)
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

inline token::code::value reader::frame::check_object(decoder_type& decoder)
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
