#ifndef TRIAL_DYNAMIC_CONVERT_BOOST_ANY_HPP
#define TRIAL_DYNAMIC_CONVERT_BOOST_ANY_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/any.hpp>
#include <trial/dynamic/variable.hpp>
#include <trial/dynamic/convert/convert.hpp>
#include <trial/dynamic/convert/std/vector.hpp>

namespace trial
{
namespace dynamic
{
namespace convert
{

template <typename Allocator>
struct overloader<basic_variable<Allocator>, boost::any>
{
    using variable_type = basic_variable<Allocator>;

    static variable_type into(const boost::any& any,
                              std::error_code& error)
    {
        if (any.empty())
            return dynamic::null;

        if (any.type() == typeid(bool))
            return boost::any_cast<bool>(any);

        if (any.type() == typeid(signed char))
            return boost::any_cast<signed char>(any);

        if (any.type() == typeid(unsigned char))
            return boost::any_cast<unsigned char>(any);

        if (any.type() == typeid(signed short int))
            return boost::any_cast<signed short int>(any);

        if (any.type() == typeid(unsigned short int))
            return boost::any_cast<unsigned short int>(any);

        if (any.type() == typeid(signed int))
            return boost::any_cast<signed int>(any);

        if (any.type() == typeid(unsigned int))
            return boost::any_cast<unsigned int>(any);

        if (any.type() == typeid(signed long int))
            return boost::any_cast<signed long int>(any);

        if (any.type() == typeid(unsigned long int))
            return boost::any_cast<unsigned long int>(any);

        if (any.type() == typeid(signed long long int))
            return boost::any_cast<signed long long int>(any);

        if (any.type() == typeid(unsigned long long int))
            return boost::any_cast<unsigned long long int>(any);

        if (any.type() == typeid(float))
            return boost::any_cast<float>(any);

        if (any.type() == typeid(double))
            return boost::any_cast<double>(any);

        if (any.type() == typeid(long double))
            return boost::any_cast<long double>(any);

        if (any.type() == typeid(const char *))
            return boost::any_cast<const char *>(any);

        if (any.type() == typeid(const wchar_t *))
            return boost::any_cast<const wchar_t *>(any);

        if (any.type() == typeid(const char16_t *))
            return boost::any_cast<const char16_t *>(any);

        if (any.type() == typeid(const char32_t *))
            return boost::any_cast<const char32_t *>(any);

        if (any.type() == typeid(typename variable_type::string_type))
            return boost::any_cast<typename variable_type::string_type>(any);

        if (any.type() == typeid(typename variable_type::wstring_type))
            return boost::any_cast<typename variable_type::wstring_type>(any);

        if (any.type() == typeid(typename variable_type::u16string_type))
            return boost::any_cast<typename variable_type::u16string_type>(any);

        if (any.type() == typeid(typename variable_type::u32string_type))
            return boost::any_cast<typename variable_type::u32string_type>(any);

        if (any.type() == typeid(std::vector<signed char>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<signed char>>(&any));

        if (any.type() == typeid(std::vector<unsigned char>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<unsigned char>>(&any));

        if (any.type() == typeid(std::vector<signed short int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<signed short int>>(&any));

        if (any.type() == typeid(std::vector<unsigned short int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<unsigned short int>>(&any));

        if (any.type() == typeid(std::vector<signed int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<signed int>>(&any));

        if (any.type() == typeid(std::vector<unsigned int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<unsigned int>>(&any));

        if (any.type() == typeid(std::vector<signed long int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<signed long int>>(&any));

        if (any.type() == typeid(std::vector<unsigned long int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<unsigned long int>>(&any));

        if (any.type() == typeid(std::vector<signed long long int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<signed long long int>>(&any));

        if (any.type() == typeid(std::vector<unsigned long long int>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<unsigned long long int>>(&any));

        if (any.type() == typeid(std::vector<float>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<float>>(&any));

        if (any.type() == typeid(std::vector<double>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<double>>(&any));

        if (any.type() == typeid(std::vector<long double>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<long double>>(&any));

        if (any.type() == typeid(std::vector<typename variable_type::string_type>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<typename variable_type::string_type>>(&any));

        if (any.type() == typeid(std::vector<typename variable_type::wstring_type>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<typename variable_type::wstring_type>>(&any));

        if (any.type() == typeid(std::vector<typename variable_type::u16string_type>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<typename variable_type::u16string_type>>(&any));

        if (any.type() == typeid(std::vector<typename variable_type::u32string_type>))
            return convert::into<variable_type>(*boost::any_cast<std::vector<typename variable_type::u32string_type>>(&any));

        error = dynamic::make_error_code(dynamic::incompatible_type);
        return null;
    }
};

template <typename Allocator>
struct overloader<boost::any, basic_variable<Allocator>>
{
    using variable_type = basic_variable<Allocator>;

    static boost::any into(const variable_type& data,
                           std::error_code& error)
    {
        switch (data.code())
        {
        case token::code::null:
            return {};

        case token::code::boolean:
            return data.template value<bool>();

        case token::code::signed_char:
            return data.template value<signed char>();

        case token::code::unsigned_char:
            return data.template value<unsigned char>();

        case token::code::signed_short_integer:
            return data.template value<signed short int>();

        case token::code::unsigned_short_integer:
            return data.template value<unsigned short int>();

        case token::code::signed_integer:
            return data.template value<signed int>();

        case token::code::unsigned_integer:
            return data.template value<unsigned int>();

        case token::code::signed_long_integer:
            return data.template value<signed long int>();

        case token::code::unsigned_long_integer:
            return data.template value<unsigned long int>();

        case token::code::signed_long_long_integer:
            return data.template value<signed long long int>();

        case token::code::unsigned_long_long_integer:
            return data.template value<unsigned long long int>();

        case token::code::real:
            return data.template value<float>();

        case token::code::long_real:
            return data.template value<double>();

        case token::code::long_long_real:
            return data.template value<long double>();

        case token::code::string:
            return data.template value<typename variable_type::string_type>();

        case token::code::wstring:
            return data.template value<typename variable_type::wstring_type>();

        case token::code::u16string:
            return data.template value<typename variable_type::u16string_type>();

        case token::code::u32string:
            return data.template value<typename variable_type::u32string_type>();

        default:
            error = dynamic::make_error_code(dynamic::incompatible_type);
            return {};
        }
    }
};

template <typename Allocator>
struct overloader<std::vector<boost::any>, basic_variable<Allocator>>
{
    using variable_type = basic_variable<Allocator>;

    static std::vector<boost::any> into(const variable_type& input,
                                        std::error_code& error)
    {
        std::vector<boost::any> result;
        for (const auto& entry : input)
        {
            auto value = convert::into<boost::any>(entry, error);
            if (error)
                return {};

            result.push_back(std::move(value));
        }
        return result;
    }
};

} // namespace convert
} // namespace dynamic
} // namespace trial

#endif // TRIAL_DYNAMIC_CONVERT_BOOST_ANY_HPP
