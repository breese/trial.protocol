#ifndef TRIAL_PROTOCOL_JSON_TYPES_HPP
#define TRIAL_PROTOCOL_JSON_TYPES_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2015 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

namespace trial
{
namespace protocol
{
namespace json
{

struct null_t {};
const null_t null = null_t();

struct begin_array_t {};
const begin_array_t begin_array = begin_array_t();
struct end_array_t {};
const end_array_t end_array = end_array_t();

struct begin_object_t {};
const begin_object_t begin_object = begin_object_t();
struct end_object_t {};
const end_object_t end_object = end_object_t();

} // namespace json
} // namespace protocol
} // namespace trial

#endif // TRIAL_PROTOCOL_JSON_TYPES_HPP
