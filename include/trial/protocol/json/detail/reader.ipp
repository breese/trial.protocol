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
#include <trial/protocol/core/detail/type_traits.hpp>

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
                            !core::detail::is_bool<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_reader<CharT>& self)
    {
        ReturnType result;
        value(self, result);
        return result;
    }

    inline static void value(const basic_reader<CharT>& self,
                             ReturnType& output)
    {
        switch (self.decoder.code())
        {
        case token::detail::code::integer:
        {
            self.decoder.value(output);
            if (self.symbol() == token::symbol::error)
            {
                throw json::error(self.error());
            }
        }
        break;

        case token::detail::code::real:
            using real_return_type = typename core::detail::make_floating_point<typename std::make_signed<ReturnType>::type>::type;
            output = ReturnType(std::round(self.decoder.template value<real_return_type>()));
            break;

        default:
            self.decoder.code(token::detail::code::error_invalid_value);
            throw json::error(self.error());
        }
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
        ReturnType result;
        value(self, result);
        return result;
    }

    inline static void value(const basic_reader<CharT>& self,
                             ReturnType& output)
    {
        switch (self.decoder.code())
        {
        case token::detail::code::integer:
            using integer_return_type = typename core::detail::make_integral<ReturnType>::type;
            output = ReturnType(self.decoder.template value<integer_return_type>());
            break;

        case token::detail::code::real:
            return self.decoder.value(output);

        default:
            self.decoder.code(token::detail::code::error_invalid_value);
            throw json::error(self.error());
        }
    }
};

// Booleans

template <typename CharT>
template <typename ReturnType>
struct basic_reader<CharT>::overloader<
    ReturnType,
    typename std::enable_if<core::detail::is_bool<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_reader<CharT>& self)
    {
        ReturnType result;
        value(self, result);
        return result;
    }

    inline static void value(const basic_reader<CharT>& self,
                             ReturnType& output)
    {
        switch (self.decoder.code())
        {
        case token::detail::code::true_value:
            output = true;
            break;

        case token::detail::code::false_value:
            output = false;
            break;

        default:
            self.decoder.code(token::detail::code::error_invalid_value);
            throw json::error(self.error());
        }
    }
};

// Strings

template <typename CharT>
template <typename CharTraits, typename Allocator>
struct basic_reader<CharT>::overloader<
    std::basic_string<CharT, CharTraits, Allocator>>
{
    using return_type = std::basic_string<CharT, CharTraits, Allocator>;

    inline static return_type value(const basic_reader<CharT>& self)
    {
        return_type result;
        value(self, result);
        return result;
    }

    inline static void value(const basic_reader<CharT>& self,
                             return_type& output)
    {
        switch (self.decoder.code())
        {
        case token::detail::code::string:
            return self.decoder.value(output);

        default:
            self.decoder.code(token::detail::code::error_invalid_value);
            throw json::error(self.error());
        }
    }
};

//-----------------------------------------------------------------------------
// basic_reader
//-----------------------------------------------------------------------------

template <typename CharT>
basic_reader<CharT>::basic_reader()
{
    stack.push(token::detail::code::end);
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const view_type& input)
    : decoder(input.begin(), input.end())
{
    stack.push(token::detail::code::end);
    decoder.code(stack.top().check_outer(decoder));
}

template <typename CharT>
auto basic_reader<CharT>::level() const BOOST_NOEXCEPT -> size_type
{
    assert(stack.size() > 0);
    return stack.size() - 1;
}

template <typename CharT>
token::code::value basic_reader<CharT>::code() const BOOST_NOEXCEPT
{
    return token::detail::convert(decoder.code());
}

template <typename CharT>
token::symbol::value basic_reader<CharT>::symbol() const BOOST_NOEXCEPT
{
    return token::symbol::convert(code());
}

template <typename CharT>
token::category::value basic_reader<CharT>::category() const BOOST_NOEXCEPT
{
    return token::category::convert(code());
}

template <typename CharT>
std::error_code basic_reader<CharT>::error() const BOOST_NOEXCEPT
{
    return decoder.error();
}

template <typename CharT>
bool basic_reader<CharT>::next()
{
    const token::detail::code::value current = decoder.code();
    switch (current)
    {
    case token::detail::code::begin_array:
        stack.push(token::detail::code::end_array);
        break;

    case token::detail::code::end_array:
        if (stack.empty())
        {
            decoder.code(token::detail::code::error_unbalanced_end_array);
            return false;
        }
        if (!stack.top().is_array())
        {
            decoder.code(token::detail::code::error_expected_end_array);
            return false;
        }
        stack.pop();
        break;

    case token::detail::code::begin_object:
        stack.push(token::detail::code::end_object);
        break;

    case token::detail::code::end_object:
        if (stack.empty())
        {
            decoder.code(token::detail::code::error_unbalanced_end_object);
            return false;
        }
        if (!stack.top().is_object())
        {
            decoder.code(token::detail::code::error_expected_end_object);
            return false;
        }
        stack.pop();
        break;

    default:
        break;
    }

    if (stack.empty())
    {
        decoder.code(token::detail::code::error_unexpected_token);
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
        decoder.code(token::detail::code::error_unexpected_token);
        return false;
    }
    return next();
}

template <typename CharT>
bool basic_reader<CharT>::next(const view_type& view)
{
    decoder = decoder_type(view.data(), view.size());
    return (category() != token::category::status);
}

template <typename CharT>
template <typename T>
T basic_reader<CharT>::value() const
{
    using return_type = typename std::remove_cv<typename std::decay<T>::type>::type;
    return basic_reader<CharT>::overloader<return_type>::value(*this);
}

template <typename CharT>
template <typename T>
void basic_reader<CharT>::value(T& output) const
{
    using return_type = typename std::remove_cv<typename std::decay<T>::type>::type;
    basic_reader<CharT>::overloader<return_type>::value(*this, output);
}

template <typename CharT>
auto basic_reader<CharT>::literal() const BOOST_NOEXCEPT -> view_type
{
    return view_type(decoder.literal().data(), decoder.literal().size());
}

template <typename CharT>
auto basic_reader<CharT>::tail() const BOOST_NOEXCEPT -> view_type
{
    return view_type(decoder.tail().data(), decoder.tail().size());
}

//-----------------------------------------------------------------------------
// reader::frame
//-----------------------------------------------------------------------------

template <typename CharT>
basic_reader<CharT>::frame::frame(token::detail::code::value scope)
    : scope(scope),
      counter(0)
{
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_array() const
{
    return scope == token::detail::code::end_array;
}

template <typename CharT>
bool basic_reader<CharT>::frame::is_object() const
{
    return scope == token::detail::code::end_object;
}

template <typename CharT>
token::detail::code::value basic_reader<CharT>::frame::next(decoder_type& decoder)
{
    decoder.next();

    switch (scope)
    {
    case token::detail::code::end:
        return check_outer(decoder);

    case token::detail::code::end_array:
        return check_array(decoder);

    case token::detail::code::end_object:
        return check_object(decoder);

    default:
        return token::detail::code::error_unexpected_token;
    }
}

template <typename CharT>
token::detail::code::value basic_reader<CharT>::frame::check_outer(decoder_type& decoder)
{
    // RFC 7159, section 2
    //
    // JSON-text = value

    switch (decoder.code())
    {
    case token::detail::code::value_separator:
    case token::detail::code::name_separator:
        return token::detail::code::error_unexpected_token;

    case token::detail::code::end_array:
        return token::detail::code::error_unbalanced_end_array;
        
    case token::detail::code::end_object:
        return token::detail::code::error_unbalanced_end_object;
        
    case token::detail::code::end:
        return decoder.code();

    default:
        // Only accept one token in the outer scope
        ++counter;
        if (counter > 1)
            return token::detail::code::error_unexpected_token;
        return decoder.code();
    }
}

template <typename CharT>
token::detail::code::value basic_reader<CharT>::frame::check_array(decoder_type& decoder)
{
    // RFC 7159, section 5
    //
    // array = begin-array [ value *( value-separator value ) ] end-array

    const token::detail::code::value current = decoder.code();

    ++counter;
    if (counter % 2 == 0)
    {
        // Expect separator
        switch (current)
        {
        case token::detail::code::end_array:
            return current;

        case token::detail::code::value_separator:
            // Skip over separator
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.code() == token::detail::code::end_array)
                return token::detail::code::error_unexpected_token;
            return decoder.code();

        default:
            return token::detail::code::error_expected_end_array;
        }
    }
    else
    {
        // Expect value
        switch (current)
        {
        case token::detail::code::value_separator:
            return token::detail::code::error_unexpected_token;

        case token::detail::code::name_separator:
            return token::detail::code::error_unexpected_token;

        case token::detail::code::end_array:
            return current;

        case token::detail::code::end_object:
            return token::detail::code::error_expected_end_array;

        default:
            break;
        }
        return current;
    }
    return token::detail::code::error_unexpected_token;
}

template <typename CharT>
token::detail::code::value basic_reader<CharT>::frame::check_object(decoder_type& decoder)
{
    // RFC 7159, section 4
    //
    // object = begin-object [ member *( value-separator member ) ]
    //          end-object
    //
    // member = string name-separator value

    const token::detail::code::value current = decoder.code();

    ++counter;
    if (counter % 4 == 0)
    {
        // Expect value separator
        switch (current)
        {
        case token::detail::code::end_object:
            return current;

        case token::detail::code::value_separator:
            decoder.next();
            ++counter;
            // Prohibit trailing separator
            if (decoder.code() == token::detail::code::end_object)
                return token::detail::code::error_unexpected_token;
            return decoder.code();

        default:
            return token::detail::code::error_expected_end_object;
        }
    }
    else if (counter % 4 == 2)
    {
        // Expect name separator
        if (current == token::detail::code::name_separator)
        {
            decoder.next();
            ++counter;
            switch (decoder.code())
            {
            case token::detail::code::end_array:
            case token::detail::code::end_object:
                return token::detail::code::error_unexpected_token;

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
        case token::detail::code::value_separator:
        case token::detail::code::name_separator:
            return token::detail::code::error_unexpected_token;

        case token::detail::code::end_array:
            return token::detail::code::error_expected_end_object;

        case token::detail::code::end_object:
            return current;

        default:
            // Key must be string type
            if ((counter % 4 == 1) && (current != token::detail::code::string))
                return token::detail::code::error_invalid_key;
            return current;
        }
    }

    return token::detail::code::error_unexpected_token;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
