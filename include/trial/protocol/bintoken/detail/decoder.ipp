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
#include <cstring> // std::memcpy
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
    using return_type = token::boolean::type;

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
    using return_type = token::int8::type;

    static return_type decode(const detail::decoder& self)
    {
        assert(self.code() == token::int8::code);
        assert(self.literal().size() == sizeof(return_type));
        return static_cast<return_type>(self.literal().front());
    }

    static size_type decode(const detail::decoder& self,
                            return_type *output,
                            size_type output_length)
    {
        switch (self.code())
        {
        case token::code::int8:
            if (output_length < 1)
                return 0;
            *output = decode(self);
            return 1;

        case token::code::array8_int8:
        case token::code::array16_int8:
        case token::code::array32_int8:
        case token::code::array64_int8:
            {
                const auto size = std::min(self.literal().size(), output_length);
                std::memcpy(output, self.literal().data(), size);
                return size;
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }
};

template <>
struct decoder::overloader<token::int16>
{
    using return_type = token::int16::type;

    static return_type decode(const detail::decoder& self)
    {
        assert(self.code() == token::int16::code);
        return endian(self.literal());
    }

    static size_type decode(const detail::decoder& self,
                            return_type *output,
                            size_type output_length)
    {
        switch (self.code())
        {
        case token::code::int16:
            if (output_length < 1)
                return 0;
            *output = decode(self);
            return 1;

        case token::code::array8_int16:
        case token::code::array16_int16:
        case token::code::array32_int16:
        case token::code::array64_int16:
            {
                auto view = self.literal();
                const auto size = std::min(view.size() / token::int16::size, output_length);
                for (size_type i = 0; i < size; ++i)
                {
                    output[i] = endian(view_type(&view[i * token::int16::size], token::int16::size));
                }
                return size;
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }

    static return_type endian(const view_type& view)
    {
        assert(view.size() == sizeof(return_type));
        const std::uint16_t endian = UINT16_C(0x0100);
        return_type result = 0;
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[0]] = static_cast<std::uint8_t>(view[0]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[1]] = static_cast<std::uint8_t>(view[1]);
        return result;
    }
};

template <>
struct decoder::overloader<token::int32>
{
    using return_type = token::int32::type;

    static return_type decode(const detail::decoder& self)
    {
        assert(self.code() == token::int32::code);
        return endian(self.literal());
    }

    static size_type decode(const detail::decoder& self,
                            return_type *output,
                            size_type output_length)
    {
        switch (self.code())
        {
        case token::code::int32:
            if (output_length < 1)
                return 0;
            *output = decode(self);
            return 1;

        case token::code::array8_int32:
        case token::code::array16_int32:
        case token::code::array32_int32:
        case token::code::array64_int32:
            {
                auto view = self.literal();
                const auto size = std::min(view.size() / token::int32::size, output_length);
                for (size_type i = 0; i < size; ++i)
                {
                    output[i] = endian(view_type(&view[i * token::int32::size], token::int32::size));
                }
                return size;
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }

    static return_type endian(const view_type& view)
    {
        assert(view.size() == sizeof(return_type));
        const std::uint32_t endian = UINT32_C(0x03020100);
        return_type result = 0;
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[0]] = static_cast<std::uint8_t>(view[0]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[1]] = static_cast<std::uint8_t>(view[1]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[2]] = static_cast<std::uint8_t>(view[2]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[3]] = static_cast<std::uint8_t>(view[3]);
        return result;
    }
};

template <>
struct decoder::overloader<token::int64>
{
    using return_type = token::int64::type;

    static return_type decode(const detail::decoder& self)
    {
        assert(self.code() == token::int64::code);
        return endian(self.literal());
    }

    static size_type decode(const detail::decoder& self,
                            return_type *output,
                            size_type output_length)
    {
        switch (self.code())
        {
        case token::code::int64:
            if (output_length < 1)
                return 0;
            *output = decode(self);
            return 1;

        case token::code::array8_int64:
        case token::code::array16_int64:
        case token::code::array32_int64:
        case token::code::array64_int64:
            {
                auto view = self.literal();
                const auto size = std::min(view.size() / token::int64::size, output_length);
                for (size_type i = 0; i < size; ++i)
                {
                    output[i] = endian(view_type(&view[i * token::int64::size], token::int64::size));
                }
                return size;
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }

    static return_type endian(const view_type& view)
    {
        assert(view.size() == sizeof(return_type));
        const std::uint64_t endian = UINT64_C(0x0706050403020100);
        return_type result = 0;
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[0]] = static_cast<std::uint8_t>(view[0]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[1]] = static_cast<std::uint8_t>(view[1]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[2]] = static_cast<std::uint8_t>(view[2]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[3]] = static_cast<std::uint8_t>(view[3]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[4]] = static_cast<std::uint8_t>(view[4]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[5]] = static_cast<std::uint8_t>(view[5]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[6]] = static_cast<std::uint8_t>(view[6]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[7]] = static_cast<std::uint8_t>(view[7]);
        return result;
    }
};

template <>
struct decoder::overloader<token::float32>
{
    using return_type = token::float32::type;

    static return_type decode(const detail::decoder& self)
    {
        // IEEE 754 single precision
        assert(self.code() == token::float32::code);
        return endian(self.literal());
    }

    static size_type decode(const detail::decoder& self,
                            return_type *output,
                            size_type output_length)
    {
        switch (self.code())
        {
        case token::code::float32:
            if (output_length < 1)
                return 0;
            *output = decode(self);
            return 1;

        case token::code::array8_float32:
        case token::code::array16_float32:
        case token::code::array32_float32:
        case token::code::array64_float32:
            {
                auto view = self.literal();
                const auto size = std::min(view.size() / token::float32::size, output_length);
                for (size_type i = 0; i < size; ++i)
                {
                    output[i] = endian(view_type(&view[i * token::float32::size], token::float32::size));
                }
                return size;
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }

    static return_type endian(const view_type& view)
    {
        assert(view.size() == sizeof(return_type));
        const std::uint32_t endian = UINT32_C(0x03020100);
        return_type result = 0;
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[0]] = static_cast<std::uint8_t>(view[0]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[1]] = static_cast<std::uint8_t>(view[1]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[2]] = static_cast<std::uint8_t>(view[2]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[3]] = static_cast<std::uint8_t>(view[3]);
        return result;
    }
};

template <>
struct decoder::overloader<token::float64>
{
    using return_type = token::float64::type;

    static return_type decode(const detail::decoder& self)
    {
        assert(self.code() == token::float64::code);
        return endian(self.literal());
    }

    static size_type decode(const detail::decoder& self,
                            return_type *output,
                            size_type output_length)
    {
        switch (self.code())
        {
        case token::code::float64:
            if (output_length < 1)
                return 0;
            *output = decode(self);
            return 1;

        case token::code::array8_float64:
        case token::code::array16_float64:
        case token::code::array32_float64:
        case token::code::array64_float64:
            {
                auto view = self.literal();
                const auto size = std::min(view.size() / token::float64::size, output_length);
                for (size_type i = 0; i < size; ++i)
                {
                    output[i] = endian(view_type(&view[i * token::float64::size], token::float64::size));
                }
                return size;
            }

        default:
            throw bintoken::error(invalid_value);
        }
    }

    static return_type endian(const view_type& view)
    {
        assert(view.size() == sizeof(return_type));
        const std::uint64_t endian = UINT64_C(0x0706050403020100);
        return_type result = 0;
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[0]] = static_cast<std::uint8_t>(view[0]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[1]] = static_cast<std::uint8_t>(view[1]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[2]] = static_cast<std::uint8_t>(view[2]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[3]] = static_cast<std::uint8_t>(view[3]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[4]] = static_cast<std::uint8_t>(view[4]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[5]] = static_cast<std::uint8_t>(view[5]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[6]] = static_cast<std::uint8_t>(view[6]);
        ((volatile std::uint8_t *)&result)[((std::uint8_t *)&endian)[7]] = static_cast<std::uint8_t>(view[7]);
        return result;
    }
};

template <>
struct decoder::overloader<token::string>
{
    using return_type = token::string::type;

    static return_type decode(const detail::decoder& decoder)
    {
        return return_type(decoder.literal().begin(),
                           decoder.literal().end());
    }
};

//-----------------------------------------------------------------------------
// decoder
//-----------------------------------------------------------------------------

decoder::decoder(view_type view)
    : input(std::move(view))
{
    current.code = token::code::end;
    next();
}

template <typename T>
decoder::decoder(const T& input)
    : decoder(buffer::traits<T>::view_cast(input))
{
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

inline std::error_code decoder::error() const BOOST_NOEXCEPT
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

inline auto decoder::array(token::int8::type *buffer, size_type size) -> size_type
{
    return overloader<token::int8>::decode(*this, buffer, size);
}

inline auto decoder::array(token::int16::type *buffer, size_type size) -> size_type
{
    return overloader<token::int16>::decode(*this, buffer, size);
}

inline auto decoder::array(token::int32::type *buffer, size_type size) -> size_type
{
    return overloader<token::int32>::decode(*this, buffer, size);
}

inline auto decoder::array(token::int64::type *buffer, size_type size) -> size_type
{
    return overloader<token::int64>::decode(*this, buffer, size);
}

inline auto decoder::array(token::float32::type *buffer, size_type size) -> size_type
{
    return overloader<token::float32>::decode(*this, buffer, size);
}

inline auto decoder::array(token::float64::type *buffer, size_type size) -> size_type
{
    return overloader<token::float64>::decode(*this, buffer, size);
}

//-----------------------------------------------------------------------------

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

        case token::code::array8_int8:
        case token::code::array16_int8:
        case token::code::array32_int8:
        case token::code::array64_int8:
            current.code = next_length(element, token::int8::size);
            break;

        case token::code::array8_int16:
        case token::code::array16_int16:
        case token::code::array32_int16:
        case token::code::array64_int16:
            current.code = next_length(element, token::int16::size);
            break;

        case token::code::array8_int32:
        case token::code::array16_int32:
        case token::code::array32_int32:
        case token::code::array64_int32:
            current.code = next_length(element, token::int32::size);
            break;

        case token::code::array8_int64:
        case token::code::array16_int64:
        case token::code::array32_int64:
        case token::code::array64_int64:
            current.code = next_length(element, token::int64::size);
            break;

        case token::code::array8_float32:
        case token::code::array16_float32:
        case token::code::array32_float32:
        case token::code::array64_float32:
            current.code = next_length(element, token::float32::size);
            break;

        case token::code::array8_float64:
        case token::code::array16_float64:
        case token::code::array32_float64:
        case token::code::array64_float64:
            current.code = next_length(element, token::float64::size);
            break;

        case token::code::string8:
        case token::code::string16:
        case token::code::string32:
        case token::code::string64:
            current.code = next_length(element, token::int8::size);
            break;
        }
    }
}

inline token::code::value decoder::next_length(value_type element, size_type size_alignment) BOOST_NOEXCEPT
{
    if (input.empty())
        return token::code::end;

    switch (element & pattern::mask)
    {
    case pattern::len8:
        {
            current.code = advance<token::int8>();
            if (category() == token::category::status)
                return current.code;
            const size_type size = static_cast<uint8_t>(value<token::int8>());
            if (size % size_alignment != 0)
                return token::code::error_invalid_length;
            return next(element, size);
        }

    case pattern::len16:
        {
            current.code = advance<token::int16>();
            if (category() == token::category::status)
                return current.code;
            const size_type size = static_cast<uint16_t>(value<token::int16>());
            if (size % size_alignment != 0)
                return token::code::error_invalid_length;
            return next(element, size);
        }

    case pattern::len32:
        {
            current.code = advance<token::int32>();
            if (category() == token::category::status)
                return current.code;
            const size_type size = static_cast<uint32_t>(value<token::int32>());
            if (size % size_alignment != 0)
                return token::code::error_invalid_length;
            return next(element, size);
        }

    case pattern::len64:
        {
            current.code = advance<token::int64>();
            if (category() == token::category::status)
                return current.code;
            const size_type size = value<token::int64>();
            if (size % size_alignment != 0)
                return token::code::error_invalid_length;
            return next(element, value<token::int64>());
        }
    }
    return token::code::error_unknown_token;
}

inline token::code::value decoder::next(value_type element, std::int64_t size) BOOST_NOEXCEPT
{
    if (size < 0)
        return token::code::error_negative_length;

    if (std::int64_t(input.size()) < size)
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
