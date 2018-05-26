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
#include <trial/protocol/core/detail/type_traits.hpp>
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

template <std::size_t N>
template <typename T, typename Enable>
struct basic_writer<N>::overloader
{
    static size_type value(basic_writer&, const T&)
    {
        static_assert(sizeof(T) == 0, "No specialization found for T");
        return 0;
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<core::detail::is_bool<T>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self, T data)
    {
        return self.encoder.value(data);
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_integral<T>::value &&
                            std::is_signed<T>::value &&
                            !core::detail::is_bool<T>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self, T data)
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

    static size_type array(basic_writer<N>& self, const T *data, size_type size)
    {
        return self.encoder.array(data, size);
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_integral<T>::value &&
                            !std::is_signed<T>::value &&
                            !core::detail::is_bool<T>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self, T data)
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

    static size_type array(basic_writer<N>& self, const T *data, size_type size)
    {
        using signed_type = typename std::make_signed<T>::type;

        return self.encoder.array(reinterpret_cast<const signed_type *>(data),
                                  size);
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_floating_point<T>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self, T data)
    {
        return self.encoder.value(data);
    }

    static size_type array(basic_writer<N>& self, const T *data, size_type size)
    {
        return self.encoder.array(data, size);
    }
};

// String literals
template <std::size_t N>
template <typename CharT, std::size_t M>
struct basic_writer<N>::overloader<CharT[M]>
{
    using type = CharT[M];
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self, const type& data)
    {
        return self.encoder.value(data, M - 1); // Drop terminating zero
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, typename basic_writer<N>::string_view_type>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self, const T& data)
    {
        return self.encoder.value(data);
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, std::string>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self, const T& data)
    {
        return self.encoder.value(data);
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::null>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self)
    {
        return self.encoder.template value<token::null>();
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_record>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self)
    {
        self.stack.push(token::code::end_record);
        return self.encoder.template value<T>();
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_record>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self)
    {
        self.validate_scope(token::code::end_record, unexpected_token);
        size_type result = self.encoder.template value<T>();
        self.stack.pop();
        return result;
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_array>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self)
    {
        self.stack.push(token::code::end_array);
        return self.encoder.template value<T>();
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_array>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self)
    {
        self.validate_scope(token::code::end_array, unexpected_token);
        size_type result = self.encoder.template value<T>();
        self.stack.pop();
        return result;
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::begin_assoc_array>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self)
    {
        self.stack.push(token::code::end_assoc_array);
        return self.encoder.template value<T>();
    }
};

template <std::size_t N>
template <typename T>
struct basic_writer<N>::overloader<
    T,
    typename std::enable_if<std::is_same<T, token::end_assoc_array>::value>::type>
{
    using size_type = typename basic_writer<N>::size_type;

    static size_type value(basic_writer<N>& self)
    {
        self.validate_scope(token::code::end_assoc_array, unexpected_token);
        size_type result = self.encoder.template value<T>();
        self.stack.pop();
        return result;
    }
};

//-----------------------------------------------------------------------------
// writer
//-----------------------------------------------------------------------------

template <std::size_t N>
template <typename T>
basic_writer<N>::basic_writer(T& buffer)
    : encoder(buffer)
{
    stack.push(token::code::end_array);
}

template <std::size_t N>
template <typename T>
auto basic_writer<N>::value(const T& data) -> size_type
{
    return overloader<T>::value(*this, data);
}

template <std::size_t N>
template <typename T>
auto basic_writer<N>::value() -> size_type
{
    return overloader<T>::value(*this);
}

template <std::size_t N>
template <typename T>
auto basic_writer<N>::array(const T *data, size_type size) -> size_type
{
    return overloader<T>::array(*this, data, size);
}

template <std::size_t N>
void basic_writer<N>::validate_scope(token::code::value code,
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
