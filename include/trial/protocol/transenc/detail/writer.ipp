#ifndef TRIAL_PROTOCOL_TRANSENC_WRITER_IPP
#define TRIAL_PROTOCOL_TRANSENC_WRITER_IPP

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
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <trial/protocol/buffer/base.hpp>

namespace trial
{
namespace protocol
{
namespace transenc
{

//-----------------------------------------------------------------------------
// writer::overloader
//-----------------------------------------------------------------------------

template <typename T, typename Enable>
struct writer::overloader
{
    static writer::size_type value(writer& self, const T& data)
    {
        return self.encoder.value(buffer::traits<T>::view_cast(data));
    }
};

template <>
struct writer::overloader<bool>
{
    static writer::size_type value(writer& self, bool data)
    {
        return self.encoder.value(data);
    }
};

template <typename T>
struct writer::overloader<T,
                          typename boost::enable_if_c<boost::is_integral<T>::value &&
                                                      boost::is_signed<T>::value &&
                                                      !boost::is_same<T, bool>::value>::type>
{
    static writer::size_type value(writer& self, T data)
    {
        if ((data <= std::numeric_limits<boost::int8_t>::max()) &&
            (data >= std::numeric_limits<boost::int8_t>::min()))
        {
            return self.encoder.value(static_cast<boost::int8_t>(data));
        }
        else if ((data <= std::numeric_limits<boost::int16_t>::max()) &&
                 (data >= std::numeric_limits<boost::int16_t>::min()))
        {
            return self.encoder.value(static_cast<boost::int16_t>(data));
        }
        else if ((data <= std::numeric_limits<boost::int32_t>::max()) &&
                 (data >= std::numeric_limits<boost::int32_t>::min()))
        {
            return self.encoder.value(static_cast<boost::int32_t>(data));
        }
        else
        {
            return self.encoder.value(static_cast<boost::int64_t>(data));
        }
    }
};

template <typename T>
struct writer::overloader<T,
                          typename boost::enable_if_c<boost::is_integral<T>::value &&
                                                      !boost::is_signed<T>::value &&
                                                      !boost::is_same<T, bool>::value>::type>
{
    static writer::size_type value(writer& self, T data)
    {
        if (data <= std::numeric_limits<boost::int8_t>::max())
        {
            return self.encoder.value(static_cast<boost::int8_t>(data));
        }
        else if (data <= std::numeric_limits<boost::int16_t>::max())
        {
            return self.encoder.value(static_cast<boost::int16_t>(data));
        }
        else if (data <= std::numeric_limits<boost::int32_t>::max())
        {
            return self.encoder.value(static_cast<boost::int32_t>(data));
        }
        else
        {
            return self.encoder.value(static_cast<boost::int64_t>(data));
        }
    }
};

template <typename T>
struct writer::overloader<T,
                          typename boost::enable_if< boost::is_floating_point<T> >::type>
{
    static writer::size_type value(writer& self, T data)
    {
        return self.encoder.value(data);
    }
};

template <typename CharT, std::size_t N>
struct writer::overloader<CharT[N],
                          typename boost::enable_if< buffer::is_text<CharT[N]> >::type>
{
    typedef CharT (type)[N];
    static writer::size_type value(writer& self, const type& data)
    {
        return self.encoder.value(data, N - 1); // Drop terminating zero
    }
};

template <>
struct writer::overloader<writer::string_view_type>
{
    typedef writer::string_view_type type;
    static writer::size_type value(writer& self, const type& data)
    {
        return self.encoder.value(data);
    }
};

template <>
struct writer::overloader<std::string>
{
    typedef std::string type;
    static writer::size_type value(writer& self, const type& data)
    {
        return self.encoder.value(data);
    }
};

template <typename T>
struct writer::overloader<T,
                          typename boost::enable_if< buffer::is_binary<T> >::type>
{
    static writer::size_type value(writer& self, const T& data)
    {
        return self.encoder.binary(buffer::traits<T>::view_cast(data));
    }
};

template <>
struct writer::overloader<token::null>
{
    static writer::size_type value(writer& self)
    {
        return self.encoder.value<token::null>();
    }
};

template <typename T>
struct writer::overloader<T,
                          typename boost::enable_if< token::is_structural<T> >::type>
{
    static writer::size_type value(writer& self)
    {
        return self.encoder.value<T>();
    }
};

//-----------------------------------------------------------------------------
// writer
//-----------------------------------------------------------------------------

template <typename T>
writer::writer(T& buffer)
    : encoder(buffer)
{
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

} // namespace transenc
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_TRANSENC_WRITER_IPP
