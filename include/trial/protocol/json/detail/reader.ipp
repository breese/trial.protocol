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
#include <trial/protocol/core/detail/config.hpp>
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
        throw_on_error(value(self, result));
        return result;
    }

    inline static json::errc value(const basic_reader<CharT>& self,
                                   ReturnType& output) noexcept
    {
        switch (self.decoder.code())
        {
        case token::code::true_value:
            output = true;
            return no_error;

        case token::code::false_value:
            output = false;
            return no_error;

        default:
            return json::invalid_value;
        }
    }
};

// Signed integers

template <typename CharT>
template <typename ReturnType>
struct basic_reader<CharT>::overloader<
    ReturnType,
    typename std::enable_if<std::is_integral<ReturnType>::value &&
                            std::is_signed<ReturnType>::value &&
                            !core::detail::is_bool<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_reader<CharT>& self)
    {
        ReturnType result;
        throw_on_error(value(self, result));
        return result;
    }

    inline static json::errc value(const basic_reader<CharT>& self,
                                   ReturnType& output) noexcept
    {
        switch (self.decoder.code())
        {
        case token::code::integer:
            return self.decoder.signed_value(output);

        case token::code::real:
        {
            using real_return_type = typename core::detail::make_floating_point<typename std::make_signed<ReturnType>::type>::type;
            real_return_type result = {};
            self.decoder.real_value(result);
            output = ReturnType(std::round(result));
            return json::no_error;
        }

        default:
            return json::invalid_value;
        }
    }
};

// Unsigned integers

template <typename CharT>
template <typename ReturnType>
struct basic_reader<CharT>::overloader<
    ReturnType,
    typename std::enable_if<std::is_integral<ReturnType>::value &&
                            std::is_unsigned<ReturnType>::value &&
                            !core::detail::is_bool<ReturnType>::value>::type>
{
    inline static ReturnType value(const basic_reader<CharT>& self)
    {
        ReturnType result;
        throw_on_error(value(self, result));
        return result;
    }

    inline static json::errc value(const basic_reader<CharT>& self,
                                   ReturnType& output) noexcept
    {
        switch (self.decoder.code())
        {
        case token::code::integer:
            return self.decoder.unsigned_value(output);

        case token::code::real:
        {
            using real_return_type = typename core::detail::make_floating_point<typename std::make_signed<ReturnType>::type>::type;
            real_return_type result = {};
            self.decoder.real_value(result);
            output = ReturnType(std::round(result));
            return json::no_error;
        }

        default:
            return json::invalid_value;
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
        throw_on_error(value(self, result));
        return result;
    }

    inline static json::errc value(const basic_reader<CharT>& self,
                                   ReturnType& output) noexcept
    {
        switch (self.decoder.code())
        {
        case token::code::integer:
        {
            using integer_return_type = typename core::detail::make_integral<ReturnType>::type;
            integer_return_type result = {};
            const auto errc = self.decoder.signed_value(result);
            if (errc == no_error)
                output = ReturnType(result);
            return errc;
        }

        case token::code::real:
            output = {};
            self.decoder.real_value(output);
            return json::no_error;

        default:
            return json::invalid_value;
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
        throw_on_error(value(self, result));
        return result;
    }

    inline static json::errc value(const basic_reader<CharT>& self,
                                   return_type& output) noexcept
    {
        switch (self.decoder.code())
        {
        case token::code::string:
        case token::code::key:
            self.decoder.string_value(output);
            return json::no_error;
        default:
            return json::invalid_value;
        }
    }
};

//-----------------------------------------------------------------------------
// basic_reader
//-----------------------------------------------------------------------------

template <typename CharT>
basic_reader<CharT>::basic_reader()
{
    stack.push(token::null{});
}

template <typename CharT>
basic_reader<CharT>::basic_reader(const view_type& input)
    : decoder(input.begin(), input.end())
{
    stack.push(token::null{});
    switch (decoder.code())
    {
    case token::code::begin_array:
        stack.push(token::begin_array{});
        break;

    case token::code::end_array:
        decoder.code(token::code::error_unbalanced_end_array);
        break;

    case token::code::begin_object:
        stack.push(token::begin_object{});
        break;

    case token::code::end_object:
        decoder.code(token::code::error_unbalanced_end_object);
        break;

    default:
        break;
    }
}

template <typename CharT>
auto basic_reader<CharT>::level() const noexcept -> size_type
{
    assert(stack.size() > 0);
    return stack.size() - 1;
}

template <typename CharT>
token::code::value basic_reader<CharT>::code() const noexcept
{
    return decoder.code();
}

template <typename CharT>
token::symbol::value basic_reader<CharT>::symbol() const noexcept
{
    return token::symbol::convert(code());
}

template <typename CharT>
token::category::value basic_reader<CharT>::category() const noexcept
{
    return token::category::convert(code());
}

template <typename CharT>
std::error_code basic_reader<CharT>::error() const noexcept
{
    return decoder.error();
}

template <typename CharT>
bool basic_reader<CharT>::next()
{
    decoder.next();
    return next_frame();
}

template <typename CharT>
bool basic_reader<CharT>::next_frame()
{
    auto& frame = stack.top();
    const auto ret = (frame.*frame.next)(decoder);
    switch (ret)
    {
    case token::code::begin_array:
        stack.push(token::begin_array{});
        decoder.code(ret);
        break;

    case token::code::begin_object:
        stack.push(token::begin_object{});
        decoder.code(ret);
        break;

    case token::code::end_array:
    case token::code::end_object:
        stack.pop();
        break;

    default:
        decoder.code(ret);
        break;
    }

    return code() >= token::code::null;
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
template <typename T>
auto basic_reader<CharT>::value(T& output) const noexcept -> json::errc
{
    using return_type = typename std::remove_cv<typename std::decay<T>::type>::type;
    return basic_reader<CharT>::overloader<return_type>::value(*this, output);
}

template <typename CharT>
template <typename Collector>
auto basic_reader<CharT>::string(Collector& collector) const noexcept -> json::errc
{
    if (decoder.code() == token::code::string)
    {
        decoder.string_value(collector);
        return errc::no_error;
    }
    return errc::incompatible_type;
}

template <typename CharT>
auto basic_reader<CharT>::literal() const noexcept -> view_type
{
    return view_type(decoder.literal().data(), decoder.literal().size());
}

template <typename CharT>
auto basic_reader<CharT>::tail() const noexcept -> view_type
{
    return view_type(decoder.tail().data(), decoder.tail().size());
}

//-----------------------------------------------------------------------------
// reader::frame
//-----------------------------------------------------------------------------

template <typename CharT>
basic_reader<CharT>::frame::frame(token::null) noexcept
    : next(&frame::next_outer)
{
}

template <typename CharT>
basic_reader<CharT>::frame::frame(token::begin_array) noexcept
    : next(&frame::next_array)
{
}

template <typename CharT>
basic_reader<CharT>::frame::frame(token::begin_object) noexcept
    : next(&frame::next_object)
{
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next_outer(decoder_type& decoder) noexcept
{
    // RFC 8259, section 2
    //
    // JSON-text = value

    switch (decoder.code())
    {
    case token::code::end_array:
        return token::code::error_unbalanced_end_array;
        
    case token::code::end_object:
        return token::code::error_unbalanced_end_object;
        
    case token::code::error_value_separator:
    case token::code::error_name_separator:
    case token::code::end:
        return decoder.code();

    default:
        // Only accept one token in the outer scope
        return token::code::error_unexpected_token;
    }
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next_array(decoder_type& decoder) noexcept
{
    // RFC 8259, section 5
    //
    // array = begin-array [ value *( value-separator value ) ] end-array

    const token::code::value current = decoder.code();
    switch (current)
    {
    case token::code::end_array:
        return current;

    case token::code::end_object:
    case token::code::end:
        return token::code::error_expected_end_array;

    default:
        next = &frame::next_array_value;
        return current;
    }
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next_array_value(decoder_type& decoder) noexcept
{
    const token::code::value current = decoder.code();
    if (TRIAL_LIKELY(current == token::code::error_value_separator))
    {
        // Skip over separator
        decoder.assume_next();
        // Prohibit trailing separator
        if (decoder.code() == token::code::end_array)
            return token::code::error_unexpected_token;
        return decoder.code();
    }
    else if (current == token::code::end_array)
    {
        return current;
    }
    return token::code::error_expected_end_array;
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next_object(decoder_type& decoder) noexcept
{
    // RFC 8259, section 4
    //
    // object = begin-object [ member *( value-separator member ) ]
    //          end-object
    //
    // member = string name-separator value

    const auto current = decoder.code();
    switch (current)
    {
    case token::code::error_value_separator:
    case token::code::error_name_separator:
        return token::code::error_unexpected_token;

    case token::code::end_array:
    case token::code::end:
        return token::code::error_expected_end_object;

    case token::code::end_object:
        return current;

    default:
        // Key must be string type
        if (current != token::code::string)
            return token::code::error_invalid_key;
        next = &frame::next_object_key;
        return token::code::key;
    }
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next_object_key(decoder_type& decoder) noexcept
{
    if (decoder.code() == token::code::error_name_separator)
    {
        decoder.assume_next();
        switch (decoder.code())
        {
        case token::code::end_array:
        case token::code::end_object:
            return token::code::error_unexpected_token;

        default:
            next = &frame::next_object_value;
            return decoder.code();
        }
    }
    return token::code::error_unexpected_token;
}

template <typename CharT>
token::code::value basic_reader<CharT>::frame::next_object_value(decoder_type& decoder) noexcept
{
    const auto current = decoder.code();
    if (TRIAL_LIKELY(current == token::code::error_value_separator))
    {
        decoder.assume_next();
        switch (decoder.code())
        {
        case token::code::end_object:
            // Prohibit trailing separator
            return token::code::error_unexpected_token;
        case token::code::string:
            next = &frame::next_object_key;
            return token::code::key;
        default:
            return decoder.code();
        }
    }
    else if (current == token::code::end_object)
    {
        return current;
    }
    return token::code::error_expected_end_object;
}

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_DETAIL_READER_IPP
