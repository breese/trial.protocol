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
using float32_t = boost::float32_t;
using float64_t = boost::float64_t;
#if defined(BOOST_CSTDFLOAT_HAS_FLOAT128_NATIVE_TYPE)
using float128_t = boost::float128_t;
#endif
#else
using float32_t = float;
using float64_t = double;
using float128_t = long double;
#endif

} // namespace detail
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_DETAIL_CSTDFLOAT_HPP
