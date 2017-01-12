#ifndef TRIAL_PROTOCOL_BINTOKEN_DETAIL_DECODER_IPP
#define TRIAL_PROTOCOL_BINTOKEN_DETAIL_DECODER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <string>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace detail
{

namespace pattern
{

const decoder::value_type mask = 0xF8;
const decoder::value_type len8 = 0xA8;
const decoder::value_type len16 = 0xB8;
const decoder::value_type len32 = 0xC8;
const decoder::value_type len64 = 0xD8;

} // namespace pattern

//-----------------------------------------------------------------------------
// decoder::overloader
//-----------------------------------------------------------------------------

template <typename ReturnType>
struct decoder::overloader
{
};

template <>
struct decoder::overloader<token::boolean>
{
    typedef token::boolean::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        switch (decoder.code())
        {
        case token::code::true_value:
            return true;

        case token::code::false_value:
            return false;

        default:
            throw bintoken::error(invalid_value);
        }
    }
};

template <>
struct decoder::overloader<token::int8>
{
    typedef token::int8::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        assert(decoder.code() == token::int8::code);
        assert(decoder.literal().size() == sizeof(return_type));
        return static_cast<return_type>(decoder.literal().front());
    }
};

template <>
struct decoder::overloader<token::int16>
{
    typedef token::int16::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        assert(decoder.code() == token::int16::code);
        assert(decoder.literal().size() == sizeof(return_type));
        const boost::uint16_t endian = UINT16_C(0x0100);
        return_type result = 0;
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[0]] = static_cast<boost::uint8_t>(decoder.literal()[0]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[1]] = static_cast<boost::uint8_t>(decoder.literal()[1]);
        return result;
    }
};

template <>
struct decoder::overloader<token::int32>
{
    typedef token::int32::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        assert(decoder.code() == token::int32::code);
        assert(decoder.literal().size() == sizeof(return_type));
        const boost::uint32_t endian = UINT32_C(0x03020100);
        return_type result = 0;
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[0]] = static_cast<boost::uint8_t>(decoder.literal()[0]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[1]] = static_cast<boost::uint8_t>(decoder.literal()[1]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[2]] = static_cast<boost::uint8_t>(decoder.literal()[2]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[3]] = static_cast<boost::uint8_t>(decoder.literal()[3]);
        return result;
    }
};

template <>
struct decoder::overloader<token::int64>
{
    typedef token::int64::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        assert(decoder.code() == token::int64::code);
        assert(decoder.literal().size() == sizeof(return_type));
        const boost::uint64_t endian = UINT64_C(0x0706050403020100);
        return_type result = 0;
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[0]] = static_cast<boost::uint8_t>(decoder.literal()[0]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[1]] = static_cast<boost::uint8_t>(decoder.literal()[1]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[2]] = static_cast<boost::uint8_t>(decoder.literal()[2]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[3]] = static_cast<boost::uint8_t>(decoder.literal()[3]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[4]] = static_cast<boost::uint8_t>(decoder.literal()[4]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[5]] = static_cast<boost::uint8_t>(decoder.literal()[5]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[6]] = static_cast<boost::uint8_t>(decoder.literal()[6]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[7]] = static_cast<boost::uint8_t>(decoder.literal()[7]);
        return result;
    }
};

template <>
struct decoder::overloader<token::float32>
{
    typedef token::float32::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        // IEEE 754 single precision
        assert(decoder.code() == token::float32::code);
        assert(decoder.literal().size() == sizeof(return_type));
        const boost::uint32_t endian = UINT32_C(0x03020100);
        return_type result = 0;
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[0]] = static_cast<boost::uint8_t>(decoder.literal()[0]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[1]] = static_cast<boost::uint8_t>(decoder.literal()[1]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[2]] = static_cast<boost::uint8_t>(decoder.literal()[2]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[3]] = static_cast<boost::uint8_t>(decoder.literal()[3]);
        return result;
    }
};

template <>
struct decoder::overloader<token::float64>
{
    typedef token::float64::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        assert(decoder.code() == token::float64::code);
        assert(decoder.literal().size() == sizeof(return_type));
        const boost::uint64_t endian = UINT64_C(0x0706050403020100);
        return_type result = 0;
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[0]] = static_cast<boost::uint8_t>(decoder.literal()[0]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[1]] = static_cast<boost::uint8_t>(decoder.literal()[1]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[2]] = static_cast<boost::uint8_t>(decoder.literal()[2]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[3]] = static_cast<boost::uint8_t>(decoder.literal()[3]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[4]] = static_cast<boost::uint8_t>(decoder.literal()[4]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[5]] = static_cast<boost::uint8_t>(decoder.literal()[5]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[6]] = static_cast<boost::uint8_t>(decoder.literal()[6]);
        ((volatile boost::uint8_t *)&result)[((boost::uint8_t *)&endian)[7]] = static_cast<boost::uint8_t>(decoder.literal()[7]);
        return result;
    }
};

template <>
struct decoder::overloader<token::string>
{
    typedef token::string::type return_type;

    static return_type decode(const detail::decoder& decoder)
    {
        return return_type(decoder.literal().begin(),
                           decoder.literal().end());
    }
};

//-----------------------------------------------------------------------------
// decoder
//-----------------------------------------------------------------------------

template <typename T>
decoder::decoder(const T& input)
    : input(buffer::traits<T>::view_cast(input))
{
    current.code = token::code::end;
    next();
}

inline void decoder::code(token::code::value v) BOOST_NOEXCEPT
{
    current.code = v;
}

inline token::code::value decoder::code() const BOOST_NOEXCEPT
{
    return current.code;
}

inline token::symbol::value decoder::symbol() const BOOST_NOEXCEPT
{
    return token::symbol::convert(current.code);
}

inline token::category::value decoder::category() const BOOST_NOEXCEPT
{
    return token::category::convert(current.code);
}

inline boost::system::error_code decoder::error() const BOOST_NOEXCEPT
{
    return bintoken::make_error_code(to_errc(code()));
}

inline const decoder::view_type& decoder::literal() const BOOST_NOEXCEPT
{
    return current.view;
}

template <typename Tag>
typename Tag::type decoder::value() const
{
    return overloader<Tag>::decode(*this);
}

inline void decoder::next() BOOST_NOEXCEPT
{
    // FIXME: return if error

    if (input.empty())
    {
        current.code = token::code::end;
        return;
    }

    const value_type element = input.front();
    if ((element & 0x80) == 0x00)
    {
        // Small positive integer
        current.code = token::code::int8;
        current.view = input.substr(0, 1);
        input.remove_prefix(1);
    }
    else if ((element & 0xE0) == 0xE0)
    {
        // Small negative integer
        current.code = token::code::int8;
        current.view = input.substr(0, 1);
        input.remove_prefix(1);
    }
    else
    {
        assert(element & 0x80);

        input.remove_prefix(1); // Skip token

        switch (element)
        {
        case token::code::null:
            current.code = advance<token::null>();
            break;

        case token::code::false_value:
        case token::code::true_value:
            current.code = advance<token::boolean>(element);
            break;

        case token::code::begin_record:
            current.code = advance<token::begin_record>();
            break;

        case token::code::end_record:
            current.code = advance<token::end_record>();
            break;

        case token::code::begin_array:
            current.code = advance<token::begin_array>();
            break;

        case token::code::end_array:
            current.code = advance<token::end_array>();
            break;

        case token::code::begin_assoc_array:
            current.code = advance<token::begin_assoc_array>();
            break;

        case token::code::end_assoc_array:
            current.code = advance<token::end_assoc_array>();
            break;

        case token::code::int8:
            current.code = advance<token::int8>();
            break;

        case token::code::int16:
            current.code = advance<token::int16>();
            break;

        case token::code::int32:
            current.code = advance<token::int32>();
            break;

        case token::code::int64:
            current.code = advance<token::int64>();
            break;

        case token::code::float32:
            current.code = advance<token::float32>();
            break;

        case token::code::float64:
            current.code = advance<token::float64>();
            break;

        case token::code::string8:
        case token::code::string16:
        case token::code::string32:
        case token::code::string64:
            current.code = next_string(element);
            break;

        case token::code::binary8:
        case token::code::binary16:
        case token::code::binary32:
        case token::code::binary64:
            current.code = next_binary(element);
            break;
        }
    }
}

inline token::code::value decoder::next_string(value_type element) BOOST_NOEXCEPT
{
    if (input.empty())
        return token::code::end;

    switch (element & pattern::mask)
    {
    case pattern::len8:
        current.code = advance<token::int8>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::string8,
                    static_cast<boost::uint8_t>(value<token::int8>()));

    case pattern::len16:
        current.code = advance<token::int16>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::string16,
                    static_cast<boost::uint16_t>(value<token::int16>()));

    case pattern::len32:
        current.code = advance<token::int32>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::string32,
                    static_cast<boost::uint32_t>(value<token::int32>()));

    case pattern::len64:
        current.code = advance<token::int64>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::string64, value<token::int64>());
    }
    return token::code::error_unknown_token;
}

inline token::code::value decoder::next_binary(value_type element) BOOST_NOEXCEPT
{
    if (input.empty())
        return token::code::end;

    switch (element & pattern::mask)
    {
    case pattern::len8:
        current.code = advance<token::int8>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::binary8,
                    static_cast<boost::uint8_t>(value<token::int8>()));

    case pattern::len16:
        current.code = advance<token::int16>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::binary16,
                    static_cast<boost::uint16_t>(value<token::int16>()));

    case pattern::len32:
        current.code = advance<token::int32>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::binary32,
                    static_cast<boost::uint32_t>(value<token::int32>()));

    case pattern::len64:
        current.code = advance<token::int64>();
        if (category() == token::category::status)
            return current.code;
        return next(token::code::binary64, value<token::int64>());
    }
    return token::code::error_unknown_token;
}

inline token::code::value decoder::next(value_type element, boost::int64_t size) BOOST_NOEXCEPT
{
    if (size < 0)
        return token::code::error_negative_length;

    if (boost::int64_t(input.size()) < size)
        return token::code::end;

    current.view = input.substr(0, size);
    input.remove_prefix(size);

    return static_cast<token::code::value>(element);
}

template <typename Tag>
token::code::value decoder::advance() BOOST_NOEXCEPT
{
    if (input.size() < Tag::size)
        return token::code::end;

    current.view = input.substr(0, Tag::size);
    input.remove_prefix(Tag::size);
    return Tag::code;
}

template <typename Tag>
token::code::value decoder::advance(value_type element) BOOST_NOEXCEPT
{
    if (input.size() < Tag::size)
        return token::code::end;

    current.view = input.substr(0, Tag::size);
    input.remove_prefix(Tag::size);
    return static_cast<token::code::value>(element);
}

} // namespace detail
} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_DETAIL_DECODER_IPP
