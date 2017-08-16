#ifndef TRIAL_PROTOCOL_DYNAMIC_BOOST_ANY_HPP
#define TRIAL_PROTOCOL_DYNAMIC_BOOST_ANY_HPP

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
#include <trial/protocol/dynamic/variable.hpp>
#include <trial/protocol/dynamic/convert.hpp>

namespace trial
{
namespace protocol
{
namespace dynamic
{
namespace detail
{

template <typename CharT>
struct convert_overloader<basic_variable<CharT>, boost::any>
{
    static basic_variable<CharT> convert(const boost::any& any,
                                         std::error_code& error)
    {
        if (any.empty())
            return dynamic::null;

        if (any.type() == typeid(bool))
            return boost::any_cast<bool>(any);

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

        if (any.type() == typeid(const CharT *))
            return boost::any_cast<const CharT *>(any);

        if (any.type() == typeid(std::basic_string<CharT>))
            return boost::any_cast<std::basic_string<CharT>>(any);

        error = dynamic::make_error_code(dynamic::incompatible_type);
        return null;
    }
};

} // namespace detail
} // namespace dynamic
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DYNAMIC_BOOST_ANY_HPP
