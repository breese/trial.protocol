#ifndef TRIAL_PROTOCOL_BINTOKEN_TOKEN_IPP
#define TRIAL_PROTOCOL_BINTOKEN_TOKEN_IPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <type_traits>

namespace trial
{
namespace protocol
{
namespace bintoken
{
namespace token
{

//-----------------------------------------------------------------------------
// Token types
//-----------------------------------------------------------------------------

inline symbol::value symbol::convert(code::value value)
{
    switch (value)
    {
    case code::end:
        return symbol::end;

    case code::error_unknown_token:
    case code::error_unexpected_token:
    case code::error_invalid_length:
    case code::error_negative_length:
    case code::error_overflow:
    case code::error_invalid_value:
    case code::error_expected_end_record:
    case code::error_expected_end_array:
    case code::error_expected_end_assoc_array:
        return symbol::error;

    case code::null:
        return symbol::null;

    case code::false_value:
    case code::true_value:
        return symbol::boolean;

    case code::int8:
    case code::int16:
    case code::int32:
    case code::int64:
        return symbol::integer;

    case code::float32:
    case code::float64:
        return symbol::real;

    case code::string8:
    case code::string16:
    case code::string32:
    case code::string64:
        return symbol::string;

    case code::array8_int8:
    case code::array16_int8:
    case code::array32_int8:
    case code::array64_int8:
    case code::array8_int16:
    case code::array16_int16:
    case code::array32_int16:
    case code::array64_int16:
    case code::array8_int32:
    case code::array16_int32:
    case code::array32_int32:
    case code::array64_int32:
    case code::array8_int64:
    case code::array16_int64:
    case code::array32_int64:
    case code::array64_int64:
    case code::array8_float32:
    case code::array16_float32:
    case code::array32_float32:
    case code::array64_float32:
    case code::array8_float64:
    case code::array16_float64:
    case code::array32_float64:
    case code::array64_float64:
        return symbol::array;

    case code::begin_record:
        return symbol::begin_record;

    case code::end_record:
        return symbol::end_record;

    case code::begin_array:
        return symbol::begin_array;

    case code::end_array:
        return symbol::end_array;

    case code::deprecated_begin_assoc_array:
    case code::begin_assoc_array:
        return symbol::begin_assoc_array;

    case code::deprecated_end_assoc_array:
    case code::end_assoc_array:
        return symbol::end_assoc_array;
    }
    return symbol::error;
}

inline category::value category::convert(symbol::value value)
{
    switch (value)
    {
    case symbol::end:
    case symbol::error:
        return category::status;

    case symbol::null:
        return category::nullable;

    case symbol::boolean:
    case symbol::integer:
    case symbol::real:
    case symbol::string:
    case symbol::array:
        return category::data;

    case symbol::begin_record:
    case symbol::end_record:
    case symbol::begin_array:
    case symbol::end_array:
    case symbol::begin_assoc_array:
    case symbol::end_assoc_array:
        return category::structural;
    }
    return category::status;
}

inline category::value category::convert(code::value value)
{
    return category::convert(symbol::convert(value));
}

//-----------------------------------------------------------------------------
// Token tags
//-----------------------------------------------------------------------------

inline bool null::same(token::code::value v)
{
    return (v == code);
}

inline bool begin_record::same(token::code::value v)
{
    return (v == code);
}

inline bool end_record::same(token::code::value v)
{
    return (v == code);
}

inline bool begin_array::same(token::code::value v)
{
    return (v == code);
}

inline bool end_array::same(token::code::value v)
{
    return (v == code);
}

inline bool begin_assoc_array::same(token::code::value v)
{
    return (v == code);
}

inline bool end_assoc_array::same(token::code::value v)
{
    return (v == code);
}

inline bool deprecated_begin_assoc_array::same(token::code::value v)
{
    return (v == code);
}

inline bool deprecated_end_assoc_array::same(token::code::value v)
{
    return (v == code);
}

inline bool boolean::same(token::code::value v)
{
    switch (v)
    {
    case token::code::true_value:
    case token::code::false_value:
        return true;

    default:
        return false;
    }
}

inline bool int8::same(token::code::value v)
{
    return (v == code);
}

inline bool int16::same(token::code::value v)
{
    return (v == code);
}

inline bool int32::same(token::code::value v)
{
    return (v == code);
}

inline bool int64::same(token::code::value v)
{
    return (v == code);
}

inline bool float32::same(token::code::value v)
{
    return (v == code);
}

inline bool float64::same(token::code::value v)
{
    return (v == code);
}

inline bool string::same(token::code::value v)
{
    switch (v)
    {
    case token::code::string8:
    case token::code::string16:
    case token::code::string32:
    case token::code::string64:
        return true;

    default:
        return false;
    }
}

//-----------------------------------------------------------------------------
// Token traits
//-----------------------------------------------------------------------------

// is_structural specializations

template <>
struct is_structural<token::begin_record>
{
    static const bool value = true;
};

template <>
struct is_structural<token::end_record>
{
    static const bool value = true;
};

template <>
struct is_structural<token::begin_array>
{
    static const bool value = true;
};

template <>
struct is_structural<token::end_array>
{
    static const bool value = true;
};

template <>
struct is_structural<token::begin_assoc_array>
{
    static const bool value = true;
};

template <>
struct is_structural<token::end_assoc_array>
{
    static const bool value = true;
};

// is_tag specializations

template <>
struct is_tag<token::null>
{
    static const bool value = true;
};

template <>
struct is_tag<token::begin_record>
{
    static const bool value = true;
};

template <>
struct is_tag<token::end_record>
{
    static const bool value = true;
};

template <>
struct is_tag<token::begin_array>
{
    static const bool value = true;
};

template <>
struct is_tag<token::end_array>
{
    static const bool value = true;
};

template <>
struct is_tag<token::begin_assoc_array>
{
    static const bool value = true;
};

template <>
struct is_tag<token::end_assoc_array>
{
    static const bool value = true;
};

template <>
struct is_tag<token::deprecated_begin_assoc_array>
{
    static const bool value = true;
};

template <>
struct is_tag<token::deprecated_end_assoc_array>
{
    static const bool value = true;
};

template <>
struct is_tag<token::boolean>
{
    static const bool value = true;
};

template <>
struct is_tag<token::int8>
{
    static const bool value = true;
};

template <>
struct is_tag<token::int16>
{
    static const bool value = true;
};

template <>
struct is_tag<token::int32>
{
    static const bool value = true;
};

template <>
struct is_tag<token::int64>
{
    static const bool value = true;
};

template <>
struct is_tag<token::float32>
{
    static const bool value = true;
};

template <>
struct is_tag<token::float64>
{
    static const bool value = true;
};

template <>
struct is_tag<token::string>
{
    static const bool value = true;
};

// type_cast specializations

template <typename T>
struct type_cast<T,
                 typename std::enable_if<is_tag<T>::value>::type>
{
    using type = typename T::type;
};

} // namespace token
} // namespace bintoken
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_BINTOKEN_TOKEN_IPP
