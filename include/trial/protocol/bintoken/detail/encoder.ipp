#ifndef TRIAL_PROTOCOL_BINTOKEN_DETAIL_ENCODER_IPP
#define TRIAL_PROTOCOL_BINTOKEN_DETAIL_ENCODER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <trial/protocol/buffer/base.hpp>
#include <trial/protocol/bintoken/token.hpp>
#include <trial/protocol/bintoken/error.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace detail
{

template <typename T>
encoder::encoder(T& output)
    : buffer(new typename buffer::traits<T>::buffer_type(output))
{
}

template <typename T>
encoder::size_type encoder::value()
{
    static_assert(sizeof(T) == 0, "Type not supported");
    throw bintoken::error(incompatible_type);
}

template <>
inline encoder::size_type encoder::value<token::null>()
{
    return write(token::null::code);
}

template <>
inline encoder::size_type encoder::value<token::begin_record>()
{
    return write(token::begin_record::code);
}

template <>
inline encoder::size_type encoder::value<token::end_record>()
{
    return write(token::end_record::code);
}

template <>
inline encoder::size_type encoder::value<token::begin_array>()
{
    return write(token::begin_array::code);
}

template <>
inline encoder::size_type encoder::value<token::end_array>()
{
    return write(token::end_array::code);
}

template <>
inline encoder::size_type encoder::value<token::begin_assoc_array>()
{
    return write(token::begin_assoc_array::code);
}

template <>
inline encoder::size_type encoder::value<token::end_assoc_array>()
{
    return write(token::end_assoc_array::code);
}

inline encoder::size_type encoder::value(bool data)
{
    return write(data ? token::code::true_value : token::code::false_value);
}

inline encoder::size_type encoder::value(token::int8::type data)
{
    if (data >= -32)
    {
        return write(data);
    }
    else
    {
        const value_type token(token::int8::code);
        const size_type size = sizeof(token) + sizeof(std::int8_t);
        if (buffer->grow(size))
        {
            buffer->write(token);
            buffer->write(data);
            return size;
        }
    }
    return 0;
}

inline encoder::size_type encoder::value(token::int16::type data)
{
    const value_type token(token::int16::code);
    const size_type size = sizeof(token) + sizeof(std::int16_t);
    if (buffer->grow(size))
    {
        buffer->write(token);
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::int32::type data)
{
    const value_type token(token::int32::code);
    const size_type size = sizeof(token) + sizeof(std::int32_t);
    if (buffer->grow(size))
    {
        buffer->write(token);
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::int64::type data)
{
    const value_type token(token::int64::code);
    const size_type size = sizeof(token) + sizeof(std::int64_t);
    if (buffer->grow(size))
    {
        buffer->write(token);
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::float32::type data)
{
    // IEEE 754 single precision
    const value_type token(token::float32::code);
    const size_type size = sizeof(token) + sizeof(token::float32::type);
    if (buffer->grow(size))
    {
        buffer->write(token);
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(token::float64::type data)
{
    // IEEE 754 double precision
    const value_type token(token::float64::code);
    const size_type size = sizeof(token) + sizeof(token::float64::type);
    if (buffer->grow(size))
    {
        buffer->write(token);
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::value(const string_view_type& data)
{
    const std::string::size_type length = data.size();
    size_type size = 0;

    if (length < static_cast<std::string::size_type>(std::numeric_limits<std::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint8_t) + length))
            return 0;
        buffer->write(token::code::string8);
        size = write_length(static_cast<std::uint8_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<std::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint16_t) + length))
            return 0;
        buffer->write(token::code::string16);
        size = write_length(static_cast<std::uint16_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<std::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint32_t) + length))
            return 0;
        buffer->write(token::code::string32);
        size = write_length(static_cast<std::uint32_t>(length));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint64_t) + length))
            return 0;
        buffer->write(token::code::string64);
        size = write_length(static_cast<std::uint64_t>(length));
    }

    buffer->write(view_type(reinterpret_cast<const value_type *>(data.data()),
                            data.size()));
    return sizeof(value_type) + size + length;
}

inline encoder::size_type encoder::value(const char *data,
                                         size_type size)
{
    return value(string_view_type(data, size));
}

inline encoder::size_type encoder::value(const char *data)
{
    return value(string_view_type(data));
}

inline auto encoder::array(const token::int8::type *data,
                           size_type length) -> size_type
{
    size_type size = 0;

    if (length < static_cast<std::string::size_type>(std::numeric_limits<std::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint8_t) + length))
            return 0;
        buffer->write(token::code::array8_int8);
        size = write_length(static_cast<std::uint8_t>(length));
        if (length == 0)
            return sizeof(value_type) + size;
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<std::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint16_t) + length))
            return 0;
        buffer->write(token::code::array16_int8);
        size = write_length(static_cast<std::uint16_t>(length));
    }
    else if (length < static_cast<std::string::size_type>(std::numeric_limits<std::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint32_t) + length))
            return 0;
        buffer->write(token::code::array32_int8);
        size = write_length(static_cast<std::uint32_t>(length));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint64_t) + length))
            return 0;
        buffer->write(token::code::array64_int8);
        size = write_length(static_cast<std::uint64_t>(length));
    }

    buffer->write(view_type(reinterpret_cast<const value_type *>(data), length));
    return sizeof(value_type) + size + length;
}

inline auto encoder::array(const token::int16::type *data,
                           size_type length) -> size_type
{
    size_type size = 0;
    size_type length_size = length * sizeof(*data);

    if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint8_t) + length_size))
            return 0;
        buffer->write(token::code::array8_int16);
        size = write_length(static_cast<std::uint8_t>(length_size));
        if (length_size == 0)
            return sizeof(value_type) + size;
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint16_t) + length_size))
            return 0;
        buffer->write(token::code::array16_int16);
        size = write_length(static_cast<std::uint16_t>(length_size));
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint32_t) + length_size))
            return 0;
        buffer->write(token::code::array32_int16);
        size = write_length(static_cast<std::uint32_t>(length_size));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint64_t) + length_size))
            return 0;
        buffer->write(token::code::array64_int16);
        size = write_length(static_cast<std::uint64_t>(length_size));
    }

    for (size_type i = 0; i < length; ++i)
    {
        endian_write(data[i]);
    }
    return sizeof(value_type) + size + length_size;
}

inline auto encoder::array(const token::int32::type *data,
                           size_type length) -> size_type
{
    size_type size = 0;
    size_type length_size = length * sizeof(*data);

    if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint8_t) + length_size))
            return 0;
        buffer->write(token::code::array8_int32);
        size = write_length(static_cast<std::uint8_t>(length_size));
        if (length_size == 0)
            return sizeof(value_type) + size;
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint16_t) + length_size))
            return 0;
        buffer->write(token::code::array16_int32);
        size = write_length(static_cast<std::uint16_t>(length_size));
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint32_t) + length_size))
            return 0;
        buffer->write(token::code::array32_int32);
        size = write_length(static_cast<std::uint32_t>(length_size));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint64_t) + length_size))
            return 0;
        buffer->write(token::code::array64_int32);
        size = write_length(static_cast<std::uint64_t>(length_size));
    }

    for (size_type i = 0; i < length; ++i)
    {
        endian_write(data[i]);
    }
    return sizeof(value_type) + size + length_size;
}

inline auto encoder::array(const token::int64::type *data,
                           size_type length) -> size_type
{
    size_type size = 0;
    size_type length_size = length * sizeof(*data);

    if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint8_t) + length_size))
            return 0;
        buffer->write(token::code::array8_int64);
        size = write_length(static_cast<std::uint8_t>(length_size));
        if (length_size == 0)
            return sizeof(value_type) + size;
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint16_t) + length_size))
            return 0;
        buffer->write(token::code::array16_int64);
        size = write_length(static_cast<std::uint16_t>(length_size));
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint32_t) + length_size))
            return 0;
        buffer->write(token::code::array32_int64);
        size = write_length(static_cast<std::uint32_t>(length_size));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint64_t) + length_size))
            return 0;
        buffer->write(token::code::array64_int64);
        size = write_length(static_cast<std::uint64_t>(length_size));
    }

    for (size_type i = 0; i < length; ++i)
    {
        endian_write(data[i]);
    }
    return sizeof(value_type) + size + length_size;
}

inline auto encoder::array(const token::float32::type *data,
                           size_type length) -> size_type
{
    size_type size = 0;
    size_type length_size = length * sizeof(*data);

    if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint8_t) + length_size))
            return 0;
        buffer->write(token::code::array8_float32);
        size = write_length(static_cast<std::uint8_t>(length_size));
        if (length_size == 0)
            return sizeof(value_type) + size;
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint16_t) + length_size))
            return 0;
        buffer->write(token::code::array16_float32);
        size = write_length(static_cast<std::uint16_t>(length_size));
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint32_t) + length_size))
            return 0;
        buffer->write(token::code::array32_float32);
        size = write_length(static_cast<std::uint32_t>(length_size));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint64_t) + length_size))
            return 0;
        buffer->write(token::code::array64_float32);
        size = write_length(static_cast<std::uint64_t>(length_size));
    }

    for (size_type i = 0; i < length; ++i)
    {
        endian_write(data[i]);
    }
    return sizeof(value_type) + size + length_size;
}

inline auto encoder::array(const token::float64::type *data,
                           size_type length) -> size_type
{
    size_type size = 0;
    size_type length_size = length * sizeof(*data);

    if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint8_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint8_t) + length_size))
            return 0;
        buffer->write(token::code::array8_float64);
        size = write_length(static_cast<std::uint8_t>(length_size));
        if (length_size == 0)
            return sizeof(value_type) + size;
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint16_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint16_t) + length_size))
            return 0;
        buffer->write(token::code::array16_float64);
        size = write_length(static_cast<std::uint16_t>(length_size));
    }
    else if (length_size < static_cast<std::string::size_type>(std::numeric_limits<std::uint32_t>::max()))
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint32_t) + length_size))
            return 0;
        buffer->write(token::code::array32_float64);
        size = write_length(static_cast<std::uint32_t>(length_size));
    }
    else
    {
        if (!buffer->grow(sizeof(value_type) + sizeof(std::uint64_t) + length_size))
            return 0;
        buffer->write(token::code::array64_float64);
        size = write_length(static_cast<std::uint64_t>(length_size));
    }

    for (size_type i = 0; i < length; ++i)
    {
        endian_write(data[i]);
    }
    return sizeof(value_type) + size + length_size;
}

inline encoder::size_type encoder::write_length(std::uint8_t data)
{
    return write(data);
}

inline encoder::size_type encoder::write_length(std::uint16_t data)
{
    const size_type size = sizeof(std::int16_t);
    if (buffer->grow(size))
    {
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write_length(std::uint32_t data)
{
    const size_type size = sizeof(std::int32_t);
    if (buffer->grow(size))
    {
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write_length(std::uint64_t data)
{
    const size_type size = sizeof(std::int64_t);
    if (buffer->grow(size))
    {
        endian_write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write(value_type data)
{
    const size_type size = sizeof(data);
    if (buffer->grow(size))
    {
        buffer->write(data);
        return size;
    }
    return 0;
}

inline encoder::size_type encoder::write(const view_type& data)
{
    const size_type size = data.size();
    if (buffer->grow(size))
    {
        buffer->write(data);
        return size;
    }
    return 0;
}

inline void encoder::endian_write(std::int16_t data)
{
    const std::uint16_t endian = UINT16_C(0x0100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
}

inline void encoder::endian_write(std::uint16_t data)
{
    const std::uint16_t endian = UINT16_C(0x0100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
}

inline void encoder::endian_write(std::int32_t data)
{
    const std::uint32_t endian = UINT32_C(0x03020100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
}

inline void encoder::endian_write(std::uint32_t data)
{
    const std::uint32_t endian = UINT32_C(0x03020100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
}

inline void encoder::endian_write(std::int64_t data)
{
    const std::uint64_t endian = UINT64_C(0x0706050403020100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[4]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[5]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[6]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[7]]));
}

inline void encoder::endian_write(std::uint64_t data)
{
    const std::uint64_t endian = UINT64_C(0x0706050403020100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[4]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[5]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[6]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[7]]));
}

inline void encoder::endian_write(token::float32::type data)
{
    const std::uint32_t endian = UINT32_C(0x03020100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
}

inline void encoder::endian_write(token::float64::type data)
{
    const std::uint64_t endian = UINT64_C(0x0706050403020100);
    value_type *data_buffer = (value_type *)&data;
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[0]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[1]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[2]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[3]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[4]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[5]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[6]]));
    buffer->write(static_cast<value_type>(data_buffer[((value_type *)&endian)[7]]));
}

} // namespace detail
} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_DETAIL_ENCODER_IPP
