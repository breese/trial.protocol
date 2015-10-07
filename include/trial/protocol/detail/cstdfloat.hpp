#ifndef TRIAL_PROTOCOL_DETAIL_CSTDFLOAT_HPP
#define TRIAL_PROTOCOL_DETAIL_CSTDFLOAT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/version.hpp>

#if BOOST_VERSION >= 105600
# define TRIAL_PROTOCOL_HEADER_BOOST_CSTDFLOAT_HPP
#endif

#if defined(TRIAL_PROTOCOL_HEADER_BOOST_CSTDFLOAT_HPP)
#include <boost/cstdfloat.hpp>
#endif

namespace trial
{
namespace protocol
{
namespace detail
{

#if defined(TRIAL_PROTOCOL_HEADER_BOOST_CSTDFLOAT_HPP)
typedef boost::float32_t float32_t;
typedef boost::float64_t float64_t;
#if defined(BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE)
typedef boost::float128_t float128_t;
#endif
#else
typedef float float32_t;
typedef double float64_t;
typedef long double float128_t;
#endif

} // namespace detail
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DETAIL_CSTDFLOAT_HPP
