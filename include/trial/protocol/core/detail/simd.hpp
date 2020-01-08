#ifndef TRIAL_PROTOCOL_CORE_DETAIL_SIMD_HPP
#define TRIAL_PROTOCOL_CORE_DETAIL_SIMD_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2020 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#if __SSE2__
# define TRIAL_PROTOCOL_USE_SSE2 1
#endif

#if defined(TRIAL_PROTOCOL_USE_SSE2)
# include <emmintrin.h>
#endif

#endif // TRIAL_PROTOCOL_CORE_DETAIL_SIMD_HPP
