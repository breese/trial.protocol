#ifndef TRIAL_PROTOCOL_CORE_DETAIL_CSTDFLOAT_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_CSTDFLOAT_HPP

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
#include <boost/math/cstdfloat/cstdfloat_types.hpp>
#endif

namespace trial
{
namespace protocol
{
namespace detail
{

#if defined(BOOST_FLOAT32_C)
using float32_t = boost::float32_t;
#else
using float32_t = float;
#endif

#if defined(BOOST_FLOAT64_C)
using float64_t = boost::float64_t;
#else
using float64_t = double;
#endif

} // namespace detail
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_CORE_DETAIL_CSTDFLOAT_HPP
