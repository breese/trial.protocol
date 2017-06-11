#ifndef TRIAL_PROTOCOL_BINTOKEN_WRITER_IPP
#define TRIAL_PROTOCOL_BINTOKEN_WRITER_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cstdint>
#include <limits>
#include <trial/protocol/detail/type_traits.hpp>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace bintoken
{

//-----------------------------------------------------------------------------
// writer::overloader
//-----------------------------------------------------------------------------

template <typename T, typename Enable>
struct writer::overloader
{
    static size_type value(writer& self, const T& data)
    {
        return self.encoder.value(buffer::traits<T>::view_cast(data));
    }
};

template <>
struct writer::overloader<bool>
{
    static size_type value(writer& self, bool data)
    {
        return self.encoder.value(data);
    }
};

template <typename T>
struct writer::overloader<
    T,
    typename std::enable_if<std::is_integral<T>::value &&
                            std::is_signed<T>::value &&
                            !protocol::detail::is_bool<T>::value>::type>
{
    static size_type value(writer& self, T data)
    {
        if ((data <= std::numeric_limits<std::int8_t>::max()) &&
            (data >= std::numeric_limits<std::int8_t>::min()))
        {
            return self.encoder.value(static_cast<std::int8_t>(data));
        }
        else if ((data <= std::numeric_limits<std::int16_t>::max()) &&
                 (data >= std::numeric_limits<std::int16_t>::min()))
        {
            return self.encoder.value(static_cast<std::int16_t>(data));
        }
        else if ((data <= std::numeric_limits<std::int32_t>::max()) &&
                 (data >= std::numeric_limits<std::int32_t>::min()))
        {
            return self.encoder.value(static_cast<std::int32_t>(data));
        }
        else
        {
            return self.encoder.value(static_cast<std::int64_t>(data));
        }
    }

    static size_type binary(writer& self, const T *data, size_type size)
    {
        return self.encoder.binary(data, size);
    }
};

template <typename T>
struct writer::overloader<
    T,
    typename std::enable_if<std::is_integral<T>::value &&
                            !std::is_signed<T>::value &&
                            !protocol::detail::is_bool<T>::value>::type>
{
    static size_type value(writer& self, T data)
    {
        if (data <= std::numeric_limits<std::uint8_t>::max())
        {
            return self.encoder.value(std::int8_t(data));
        }
        else if (data <= std::numeric_limits<std::uint16_t>::max())
        {
            return self.encoder.value(std::int16_t(data));
        }
        else if (data <= std::numeric_limits<std::uint32_t>::max())
        {
            return self.encoder.value(std::int32_t(data));
        }
        else
        {
            return self.encoder.value(std::int64_t(data));
        }
    }

    static size_type binary(writer& self, const T *data, size_type size)
    {
        return self.encoder.binary(data, size);
    }
};

template <typename T>
struct writer::overloader<
    T,
    typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    static size_type value(writer& self, T data)
    {
        return self.encoder.value(data);
    }
};

// String literals
template <typename CharT, std::size_t N>
struct writer::overloader<CharT[N]>
{
    using type = CharT[N];

    static size_type value(writer& self, const type& data)
    {
        return self.encoder.value(data, N - 1); // Drop terminating zero
    }
};

template <>
struct writer::overloader<writer::string_view_type>
{
    using type = string_view_type;
    static size_type value(writer& self, const type& data)
    {
        return self.encoder.value(data);
    }
};

template <>
struct writer::overloader<std::string>
{
    using type = std::string;
    static size_type value(writer& self, const type& data)
    {
        return self.encoder.value(data);
    }
};

template <>
struct writer::overloader<token::null>
{
    static size_type value(writer& self)
    {
        return self.encoder.value<token::null>();
    }
};

template <>
struct writer::overloader<token::begin_record>
{
    using type = token::begin_record;

    static size_type value(writer& self)
    {
        self.stack.push(token::code::end_record);
        return self.encoder.value<type>();
    }
};

template <>
struct writer::overloader<token::end_record>
{
    using type = token::end_record;

    static size_type value(writer& self)
    {
        self.validate_scope(token::code::end_record, unexpected_token);
        size_type result = self.encoder.value<type>();
        self.stack.pop();
        return result;
    }
};

template <>
struct writer::overloader<token::begin_array>
{
    using type = token::begin_array;

    static size_type value(writer& self)
    {
        self.stack.push(token::code::end_array);
        return self.encoder.value<type>();
    }
};

template <>
struct writer::overloader<token::end_array>
{
    using type = token::end_array;

    static size_type value(writer& self)
    {
        self.validate_scope(token::code::end_array, unexpected_token);
        size_type result = self.encoder.value<type>();
        self.stack.pop();
        return result;
    }
};

template <>
struct writer::overloader<token::begin_assoc_array>
{
    using type = token::begin_assoc_array;

    static size_type value(writer& self)
    {
        self.stack.push(token::code::end_assoc_array);
        return self.encoder.value<type>();
    }
};

template <>
struct writer::overloader<token::end_assoc_array>
{
    using type = token::end_assoc_array;

    static size_type value(writer& self)
    {
        self.validate_scope(token::code::end_assoc_array, unexpected_token);
        size_type result = self.encoder.value<type>();
        self.stack.pop();
        return result;
    }
};

//-----------------------------------------------------------------------------
// writer
//-----------------------------------------------------------------------------

template <typename T>
writer::writer(T& buffer)
    : encoder(buffer)
{
    stack.push(token::code::end_array);
}

template <typename T>
writer::size_type writer::value(const T& data)
{
    return overloader<T>::value(*this, data);
}

template <typename T>
writer::size_type writer::value()
{
    return overloader<T>::value(*this);
}

template <typename T>
auto writer::binary(const T *data, size_type size) -> size_type
{
    return overloader<T>::binary(*this, data, size);
}

inline void writer::validate_scope(token::code::value code,
                                   enum bintoken::errc e)
{
    if ((stack.size() < 2) || (stack.top() != code))
    {
        throw bintoken::error(bintoken::make_error_code(e));
    }
}

} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_WRITER_IPP
