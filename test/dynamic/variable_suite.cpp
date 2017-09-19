///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <functional>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/core/detail/meta.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

#define TRIAL_PROTOCOL_HAS_TYPE(x,y)                                    \
    template <typename T, typename = void> struct x : std::false_type {}; \
    template <typename T> struct x <T, trial::protocol::core::detail::meta::void_t<typename T:: y >> : std::true_type {};

//-----------------------------------------------------------------------------
// Container concept
//-----------------------------------------------------------------------------

namespace container_concept_suite
{

TRIAL_PROTOCOL_HAS_TYPE(has_value_type, value_type)
TRIAL_PROTOCOL_HAS_TYPE(has_reference, reference)
TRIAL_PROTOCOL_HAS_TYPE(has_const_reference, const_reference)
TRIAL_PROTOCOL_HAS_TYPE(has_iterator, iterator)
TRIAL_PROTOCOL_HAS_TYPE(has_const_iterator, const_iterator)
TRIAL_PROTOCOL_HAS_TYPE(has_difference_type, difference_type)
TRIAL_PROTOCOL_HAS_TYPE(has_size_type, size_type)

void container_types()
{
    static_assert(has_value_type<variable>::value, "variable::value_type missing");

    static_assert(has_reference<variable>::value, "variable::reference missing");
    static_assert(has_const_reference<variable>::value, "variable::const_reference missing");

    static_assert(has_iterator<variable>::value, "variable::iterator missing");
    static_assert(has_const_iterator<variable>::value, "variable::const_iterator missing");

    static_assert(has_difference_type<variable>::value, "variable::difference_type missing");
    static_assert(std::is_signed<variable::difference_type>::value, "variable::difference_type must be signed");
    static_assert(std::is_same<variable::difference_type, variable::iterator::difference_type>::value, "Container and iterator must have same difference_type");
    static_assert(std::is_same<variable::difference_type, variable::const_iterator::difference_type>::value, "Container and const_iterator must have same difference_type");

    static_assert(has_size_type<variable>::value, "variable::size_type missing");
    static_assert(std::is_unsigned<variable::size_type>::value, "variable::size_type must be unsigned");
    static_assert(std::numeric_limits<variable::size_type>::max() >= std::numeric_limits<variable::difference_type>::max(), "size_type can represent any non-negative value of difference_type");
}

void container_constructible()
{
    static_assert(std::is_default_constructible<variable>::value, "is_default_constructible");
    static_assert(std::is_copy_constructible<variable>::value, "is_copy_constructible");
    static_assert(std::is_move_constructible<variable>::value, "is_move_constructible");
}

void container_destructible()
{
    static_assert(std::is_destructible<variable>::value, "is_destructible");
}

void container_assignable()
{
    static_assert(std::is_copy_assignable<variable>::value, "is_copy_assignable");
    static_assert(std::is_move_assignable<variable>::value, "is_move_assignable");
}

void run()
{
    // [container.requirements.general]
    container_types();
    container_constructible();
    container_destructible();
    container_assignable();
    // Required member functions are checked elsewhere
    //   variable::begin()
    //   variable::end()
    //   variable::cbegin()
    //   variable::cend()
    //   variable::swap()
    //   Equality operators
    //   Capacity
}

} // namespace container_concept_suite

//-----------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------

namespace ctor_suite
{

void construct_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void construct_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<boolean>(), true);
}

void construct_signed_char()
{
    signed char value = 0;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_char()
{
    unsigned char value = 0;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_signed_short_int()
{
    signed short int value = 0;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_short_int()
{
    unsigned short int value = 0;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_signed_int()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_int()
{
    variable data(0U);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_signed_long_int()
{
    variable data(0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_long_int()
{
    variable data(0UL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_signed_long_long_int()
{
    variable data(0LL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_unsigned_long_long_int()
{
    variable data(0ULL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);
}

void construct_float()
{
    variable data(1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);
}

void construct_double()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);
}

void construct_long_double()
{
    variable data(1.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);
}

void construct_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    }
    {
        variable data(std::string("alpha"));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    }
}

void construct_wstring()
{
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    }
    {
        variable data(std::wstring(L"alpha"));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    }
}

void construct_u16string()
{
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    }
    {
        variable data(std::u16string(u"alpha"));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    }
}

void construct_array_empty()
{
    {
        variable data({});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    }
    {
        variable data(array::make());
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    }
}

void construct_array_from_vector()
{
    std::vector<int> input = { 1, 2 };
    variable data = array::make(input.begin(), input.end());
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array_from_iterator()
{
    std::vector<variable> input = { 1, 2 };
    variable data = array::make(input.begin(), input.end());
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array_from_factory()
{
    variable data(array::make({false, 1, 2.0, "alpha"}));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array_from_initializer()
{
    variable data({false, 1, 2.0, "alpha"});
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_array_from_size()
{
    variable data(array::repeat(4, true));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void construct_map_empty()
{
    variable data(map::make());
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_key_null()
{
    {
        variable data(map::make({ {null, 1} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data({ {null, 1} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
}

void construct_map_key_boolean()
{
    {
        variable data(map::make({ {false, 1}, {true, 2} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data({ {false, 1}, {true, 2} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
}

void construct_map_key_integer()
{
    {
        variable data(map::make({ {1, 1}, {2, 2} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data({ {1, 1}, {2, 2} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
}

void construct_map_key_string()
{
    {
        variable data({ {"alpha", 1} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data({ {L"alpha", 1} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data({ {u"alpha", 1} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make({ {"alpha", 1} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make({ {L"alpha", 1} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make({ {u"alpha", 1} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make(std::string("alpha"), 1));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make(std::wstring(L"alpha"), 1));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make(std::u16string(u"alpha"), 1));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make("alpha", 1));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make(L"alpha", 1));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(map::make(u"alpha", 1));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
}

void construct_map_from_implicit_pair()
{
    variable data(map::make({"alpha", "hydrogen"}));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_from_explicit_pair()
{
    variable data(map::make(std::pair<std::string, std::string>("alpha", "hydrogen")));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_from_make_pair()
{
    variable data(map::make(std::make_pair("alpha", "hydrogen")));
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void construct_map_with_nested_array()
{
    {
        variable data(map::make({ {"alpha", array::make({1, 2})} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data["alpha"].is<array>(), true);
    }
    {
        variable data({ {"alpha", array::make({1, 2})} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data["alpha"].is<array>(), true);
    }
    {
        variable data({ {"alpha", {1, 2} } });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data["alpha"].is<array>(), true);
    }
}

void construct_map_with_nested_map()
{
    {
        variable data(map::make({ {"alpha", map::make({1, 2})} }));
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data["alpha"].is<map>(), true);
    }
    {
        variable data({ {"alpha", map::make({1, 2})} });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data["alpha"].is<map>(), true);
    }
    {
        variable data({ {"alpha", {{1, 2}} } });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data["alpha"].is<map>(), true);
    }
}

void construct_no_map()
{
    {
        variable data({ { "alpha" } });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].size(), 1);
    }
    {
        variable data({ { "alpha", "hydrogen", "helium" } });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].size(), 3);
    }
    {
        variable data({ { "alpha" }, { "bravo", "helium" } });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].size(), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data[1].is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data[1].size(), 2);
    }
    {
        variable data({ { "alpha", "hydrogen" }, { "bravo" } });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data[0].size(), 2);
        TRIAL_PROTOCOL_TEST_EQUAL(data[1].is<array>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data[1].size(), 1);
    }
}

void run()
{
    construct_null();

    construct_boolean();

    construct_signed_char();
    construct_unsigned_char();
    construct_signed_short_int();
    construct_unsigned_short_int();
    construct_signed_int();
    construct_unsigned_int();
    construct_signed_long_int();
    construct_unsigned_long_int();
    construct_signed_long_long_int();
    construct_unsigned_long_long_int();

    construct_float();
    construct_double();
    construct_long_double();

    construct_string();
    construct_wstring();
    construct_u16string();

    construct_array_empty();
    construct_array_from_vector();
    construct_array_from_iterator();
    construct_array_from_factory();
    construct_array_from_initializer();
    construct_array_from_size();

    construct_map_empty();
    construct_map_key_null();
    construct_map_key_boolean();
    construct_map_key_integer();
    construct_map_key_string();
    construct_map_from_implicit_pair();
    construct_map_from_explicit_pair();
    construct_map_from_make_pair();
    construct_map_with_nested_array();
    construct_map_with_nested_map();

    construct_no_map();
}

} // namespace ctor_suite

//-----------------------------------------------------------------------------
// variable::is<T>
//-----------------------------------------------------------------------------

namespace is_suite
{

void is_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<nullable>(), true);
}

void is_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<boolean>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const bool&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile bool&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<bool&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const bool&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile bool&>(), false);
}

void is_integer_with_signed_char()
{
    signed char value = 2;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed char&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed char&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed char&>(), false);
}

void is_integer_with_unsigned_char()
{
    unsigned char value = 2U;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned char&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned char&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned char&>(), false);
}

void is_integer_with_signed_short_int()
{
    signed short int value = 2;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed short int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed short int&>(), false);
}

void is_integer_with_unsigned_short_int()
{
    unsigned short int value = 2;
    variable data(value);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned short int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned short int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned short int&>(), false);
}

void is_integer_with_signed_int()
{
    variable data(2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed int&>(), false);
}

void is_integer_with_unsigned_int()
{
    variable data(2U);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned int&>(), false);
}

void is_integer_with_signed_long_int()
{
    variable data(2L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long int&>(), false);
}

void is_integer_with_unsigned_long_int()
{
    variable data(2UL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned long int&>(), false);
}

void is_integer_with_signed_long_long_int()
{
    variable data(2LL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile signed long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const signed long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile signed long long int&>(), false);
}

void is_integer_with_unsigned_long_long_int()
{
    variable data(2ULL);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<integer>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned char>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned char&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned short int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned short int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<signed long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const signed long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<unsigned long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const unsigned long long int&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long long int>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile unsigned long long int&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const unsigned long long int&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned long long int>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile unsigned long long int&>(), false);
}

void is_number_with_float()
{
    variable data(1.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile float&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const float&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile float&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), false);
}

void is_number_with_double()
{
    variable data(1.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile double&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), false);
}

void is_number_with_long_double()
{
    variable data(1.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<number>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<long double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const long double&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile long double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<float>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const float&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const double&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const long double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const long double&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile long double>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile long double&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), false);
}

void is_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::string_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::string_type&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::wstring>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::wstring_type>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::u16string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::u16string_type>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::string_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::string_type&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), false);
}

void is_wstring()
{
    variable data(L"alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::wstring>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::wstring_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::wstring_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::wstring_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::wstring_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::wstring_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::wstring_type&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::u16string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::u16string_type>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::wstring_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::wstring_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::wstring_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::wstring_type&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), false);
}

void is_u16string()
{
    variable data(u"alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::u16string>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::u16string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::u16string_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::u16string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::u16string_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::u16string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::u16string_type&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::string>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::string_type>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<std::wstring>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::wstring_type>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::u16string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::u16string_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::u16string_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::u16string_type&>(), false);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), false);
}

void is_array()
{
    variable data = array::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::array_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::array_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::array_type&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::array_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::array_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::array_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::array_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::array_type&>(), false);
}

void is_map()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<variable::map_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::map_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<const variable::map_type&>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::map_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<volatile variable::map_type&>(), true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::map_type>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::map_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<const variable::map_type&>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::map_type>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<volatile variable::map_type&>(), false);
}

void run()
{
    is_null();

    is_boolean();

    is_integer_with_signed_char();
    is_integer_with_unsigned_char();
    is_integer_with_signed_short_int();
    is_integer_with_unsigned_short_int();
    is_integer_with_signed_int();
    is_integer_with_unsigned_int();
    is_integer_with_signed_long_int();
    is_integer_with_unsigned_long_int();
    is_integer_with_signed_long_long_int();
    is_integer_with_unsigned_long_long_int();

    is_number_with_float();
    is_number_with_double();
    is_number_with_long_double();

    is_string();
    is_wstring();
    is_u16string();

    is_array();
    is_map();
}

} // namespace is_suite

//-----------------------------------------------------------------------------
// Tokens
//-----------------------------------------------------------------------------

namespace token_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::null);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::null);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::boolean);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::boolean);
}

void test_integer()
{
    {
        const signed char value = 0;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::signed_char);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const unsigned char value = 0U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::unsigned_char);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const signed short int value = 0;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::signed_short_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const unsigned short int value = 0U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::unsigned_short_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const signed int value = 0;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::signed_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const unsigned int value = 0U;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::unsigned_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const signed long int value = 0L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::signed_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const unsigned long int value = 0UL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::unsigned_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const signed long long int value = 0LL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::signed_long_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
    {
        const unsigned long long int value = 0ULL;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::unsigned_long_long_integer);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::integer);
    }
}

void test_number()
{
    {
        const float value = 0.0f;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::float_number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::number);
    }
    {
        const double value = 0.0;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::double_number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::number);
    }
    {
        const long double value = 0.0L;
        variable data(value);
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::long_double_number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::number);
    }
}

void test_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::string);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::string);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::wstring);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::wstring);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::u16string);
        TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::u16string);
    }
}

void test_array()
{
    variable data = array::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::array);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::array);
}

void test_map()
{
    variable data = map::make();
    TRIAL_PROTOCOL_TEST_EQUAL(data.code(), code::map);
    TRIAL_PROTOCOL_TEST_EQUAL(data.symbol(), symbol::map);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_map();
}

} // namespace token_suite

//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

namespace copy_suite
{

void copy_null()
{
    variable data;
    variable copy(data);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<nullable>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<nullable>(), null);
}

void copy_boolean()
{
    variable data(true);
    variable copy(data);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<bool>(), true);
}

void copy_integer()
{
    {
        signed char value = 2;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned char>(), value);
    }
    {
        signed short int value = 2;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned short int>(), value);
    }
    {
        signed int value = 2;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long long int>(), value);
    }
}

void copy_number()
{
    {
        float value = 3.0f;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<float>(), value);
    }
    {
        double value = 3.0;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<double>(), value);
    }
    {
        long double value = 3.0L;
        variable data(value);
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<long double>(), value);
    }
}

void copy_string()
{
    {
        variable data("alpha");
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<string>(), true);
    }
    {
        variable data(L"alpha");
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<wstring>(), true);
    }
    {
        variable data(u"alpha");
        variable copy(data);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<u16string>(), true);
    }
}

void copy_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(data);

    variable expect = array::make({ true, 2, 3.0, "alpha" });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void copy_array_nested()
{
    variable data = array::make({ true, array::make({ 2, 3.0 }), "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(data);

    variable expect = array::make({ true, array::make({ 2, 3.0 }), "alpha" });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void copy_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(data);

    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void copy_map_nested()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(data);

    variable expect = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });

    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(data.begin(), data.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());

    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    copy_null();
    copy_boolean();
    copy_integer();
    copy_number();
    copy_string();
    copy_array();
    copy_array_nested();
    copy_map();
    copy_map_nested();
}

} // namespace copy_suite

//-----------------------------------------------------------------------------
// Move
//-----------------------------------------------------------------------------

namespace move_suite
{

void move_null()
{
    variable data;
    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<nullable>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<nullable>(), null);
}

void move_boolean()
{
    variable data(true);
    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<bool>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.value<bool>(), true);
}

void move_integer()
{
    {
        signed char value = 2;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned char>(), value);
    }
    {
        signed short int value = 2;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned short int>(), value);
    }
    {
        signed int value = 2;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<signed long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<unsigned long long int>(), value);
    }
}

void move_number()
{
    {
        float value = 3.0f;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<float>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<float>(), value);
    }
    {
        double value = 3.0;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<double>(), value);
    }
    {
        long double value = 3.0L;
        variable data(value);
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.same<long double>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<long double>(), value);
    }
}

void move_string()
{
    {
        variable data("alpha");
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<string>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(copy.value<string>(), "alpha");
    }
    {
        variable data(L"alpha");
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<wstring>(), true);
        TRIAL_PROTOCOL_TEST(copy.value<std::wstring>() == L"alpha");
    }
    {
        variable data(u"alpha");
        variable copy(std::move(data));
        TRIAL_PROTOCOL_TEST_EQUAL(copy.is<u16string>(), true);
        TRIAL_PROTOCOL_TEST(copy.value<std::u16string>() == u"alpha");
    }
}

void move_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);

    variable expect = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void move_array_nested()
{
    variable data = array::make({ true, array::make({ 2, 3.0 }), "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<array>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);

    variable expect = array::make({ true, array::make({ 2, 3.0 }), "alpha" });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void move_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 4);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 4);

    variable expect = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void move_map_nested()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 3);

    variable copy(std::move(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.is<map>(), true);
    TRIAL_PROTOCOL_TEST_EQUAL(copy.size(), 3);

    variable expect = map::make(
        {
            { "alpha", true },
            { "nested", map::make({{ "bravo", 2}, { "charlie", 3.0 }}) },
            { "delta", "hydrogen" }
        });
    TRIAL_PROTOCOL_TEST_ALL_WITH(copy.begin(), copy.end(),
                                 expect.begin(), expect.end(),
                                 std::equal_to<variable>());
}

void run()
{
    move_null();
    move_boolean();
    move_integer();
    move_number();
    move_string();
    move_array();
    move_array_nested();
    move_map();
    move_map_nested();
}

} // namespace move_suite

//-----------------------------------------------------------------------------
// Assignment
//-----------------------------------------------------------------------------

namespace assign_suite
{

void assign_null_with_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_null_with_boolean()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    data = true;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_null_with_integer()
{
    // signed char
    {
        signed char value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    // unsigned char
    {
        unsigned char value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    // signed short int
    {
        signed short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_null_with_number()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_null_with_string()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = std::string("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = std::wstring(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = std::u16string(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
}

void assign_null_with_array()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = array::make({ true, 2 });
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    }
}

void assign_null_with_map()
{
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = map::make({{ "alpha", "hydrogen" }});
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
        data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
}

void assign_boolean_with_null()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_boolean_with_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_boolean_with_integer()
{
    // signed char
    {
        signed char value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    // unsigned char
    {
        unsigned char value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    // signed short int
    {
        signed short int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_boolean_with_number()
{
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_boolean_with_string()
{
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
}

void assign_boolean_with_array()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_boolean_with_map()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_signed_int_with_null()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_signed_int_with_boolean()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_signed_int_with_integer()
{
    signed int input = 2;

    // signed char
    {
        signed char value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    // unsigned char
    {
        unsigned char value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    // signed short int
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_signed_int_with_number()
{
    signed int input = 2;
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_signed_int_with_string()
{
    {
        signed int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        signed int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        signed int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
}

void assign_signed_int_with_array()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_signed_int_with_map()
{
    signed int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_unsigned_int_with_null()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_unsigned_int_with_boolean()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_unsigned_int_with_integer()
{
    unsigned int input = 2;

    // signed char
    {
        signed char value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    {
        signed char value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed char>(), value);
    }
    // unsigned char
    {
        unsigned char value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    {
        unsigned char value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned char>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned char>(), value);
    }
    // signed short int
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    {
        signed short int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed short int>(), value);
    }
    // unsigned short int
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    {
        unsigned short int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned short int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned short int>(), value);
    }
    // signed int
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    {
        signed int value = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), value);
    }
    // unsigned int
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    {
        unsigned int value = 2U;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), value);
    }
    // signed long int
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    {
        signed long int value = 2L;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long int>(), value);
    }
    // unsigned long int
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    {
        unsigned long int value = 2UL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long int>(), value);
    }
    // signed long long int
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    {
        signed long long int value = 2LL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed long long int>(), value);
    }
    // unsigned long long int
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = value;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(value);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned long long int>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned long long int>(), value);
    }
}

void assign_unsigned_int_with_number()
{
    unsigned int input = 2;
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_unsigned_int_with_string()
{
    {
        unsigned int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        unsigned int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        unsigned int input = 2;
        variable data(input);
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
}

void assign_unsigned_int_with_array()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_unsigned_int_with_map()
{
    unsigned int input = 2;
    variable data(input);
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_float_with_null()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_float_with_boolean()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_float_with_integer()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_float_with_number()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 1.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = 1.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        variable number(1.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_float_with_string()
{
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        variable data(3.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
}

void assign_float_with_array()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_float_with_map()
{
    variable data(3.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_double_with_null()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_double_with_boolean()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_double_with_integer()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_double_with_number()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 1.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = 1.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        variable number(1.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_double_with_string()
{
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
}

void assign_double_with_array()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_double_with_map()
{
    variable data(3.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_long_double_with_null()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_long_double_with_boolean()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_long_double_with_integer()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_long_double_with_number()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 1.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = 1.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        variable number(1.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
}

void assign_long_double_with_string()
{
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::string_type>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::wstring_type>(), true);
    }
    {
        variable data(3.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<variable::u16string_type>(), true);
    }
}

void assign_long_double_with_array()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_long_double_with_map()
{
    variable data(3.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_string_with_null()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = null;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = null;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = null;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
    }
}

void assign_string_with_boolean()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = false;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = false;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = false;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
    }
}

void assign_string_with_integer()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<int>(), true);
    }
}

void assign_string_with_number()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_string_with_string()
{
    // string - string
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = "bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    }
    // string - wstring
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = L"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    }
    // string - u16string
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = u"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    }
    // wstring - string
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = "bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    }
    // wstring - wstring
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = L"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    }
    // wstring - u16string
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = u"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    }
    // u16string - string
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = "bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    }
    // u16string - wstring
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = L"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    }
    // u16string - u16string
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = u"bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    }
}

void assign_string_with_array()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    }
}

void assign_string_with_map()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
        data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
        data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
        data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    }
}

void assign_array_with_null()
{
    variable data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_array_with_boolean()
{
    variable data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_array_with_integer()
{
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_array_with_number()
{
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_array_with_string()
{
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    }
    {
        variable data = { true, 2 };
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    }
}

void assign_array_with_array()
{
    variable data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = { 3.0, "alpha" };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_array_with_map()
{
    variable data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
    data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void assign_map_with_null()
{
    variable data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<nullable>(), true);
}

void assign_map_with_boolean()
{
    variable data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = false;
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<bool>(), true);
}

void assign_map_with_integer()
{
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 2;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<signed int>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 2U;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<unsigned int>(), true);
    }
}

void assign_map_with_number()
{
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 3.0f;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(3.0f);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(3.0f);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<float>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 3.0;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(3.0);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(3.0);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<double>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = 3.0L;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(3.0L);
        data = number;
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        variable number(3.0L);
        data = std::move(number);
        TRIAL_PROTOCOL_TEST_EQUAL(data.same<long double>(), true);
    }
}

void assign_map_with_string()
{
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = "alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<string>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = L"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<wstring>(), true);
    }
    {
        variable data = {{ "alpha", "hydrogen" }};
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
        data = u"alpha";
        TRIAL_PROTOCOL_TEST_EQUAL(data.is<u16string>(), true);
    }
}

void assign_map_with_array()
{
    variable data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = { true, 2 };
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<array>(), true);
}

void assign_map_with_map()
{
    variable data = {{ "alpha", "hydrogen" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
    data = {{ "bravo", "helium" }};
    TRIAL_PROTOCOL_TEST_EQUAL(data.is<map>(), true);
}

void run()
{
    assign_null_with_null();
    assign_null_with_boolean();
    assign_null_with_integer();
    assign_null_with_number();
    assign_null_with_string();
    assign_null_with_array();
    assign_null_with_map();

    assign_boolean_with_null();
    assign_boolean_with_boolean();
    assign_boolean_with_integer();
    assign_boolean_with_number();
    assign_boolean_with_string();
    assign_boolean_with_array();
    assign_boolean_with_map();

    assign_signed_int_with_null();
    assign_signed_int_with_boolean();
    assign_signed_int_with_integer();
    assign_signed_int_with_number();
    assign_signed_int_with_string();
    assign_signed_int_with_array();
    assign_signed_int_with_map();

    assign_unsigned_int_with_null();
    assign_unsigned_int_with_boolean();
    assign_unsigned_int_with_integer();
    assign_unsigned_int_with_number();
    assign_unsigned_int_with_string();
    assign_unsigned_int_with_array();
    assign_unsigned_int_with_map();

    assign_float_with_null();
    assign_float_with_boolean();
    assign_float_with_integer();
    assign_float_with_number();
    assign_float_with_string();
    assign_float_with_array();
    assign_float_with_map();

    assign_double_with_null();
    assign_double_with_boolean();
    assign_double_with_integer();
    assign_double_with_number();
    assign_double_with_string();
    assign_double_with_array();
    assign_double_with_map();

    assign_long_double_with_null();
    assign_long_double_with_boolean();
    assign_long_double_with_integer();
    assign_long_double_with_number();
    assign_long_double_with_string();
    assign_long_double_with_array();
    assign_long_double_with_map();

    assign_string_with_null();
    assign_string_with_boolean();
    assign_string_with_integer();
    assign_string_with_number();
    assign_string_with_string();
    assign_string_with_array();
    assign_string_with_map();

    assign_array_with_null();
    assign_array_with_boolean();
    assign_array_with_integer();
    assign_array_with_number();
    assign_array_with_string();
    assign_array_with_array();
    assign_array_with_map();

    assign_map_with_null();
    assign_map_with_boolean();
    assign_map_with_integer();
    assign_map_with_number();
    assign_map_with_string();
    assign_map_with_array();
    assign_map_with_map();
}

} // namespace assign_suite

//-----------------------------------------------------------------------------
// variable::unsafe_get
//-----------------------------------------------------------------------------

namespace unsafe_get_suite
{

void get_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(data.unsafe_get<nullable>() == null);
}

void get_const_null()
{
    const variable data;
    TRIAL_PROTOCOL_TEST(data.unsafe_get<nullable>() == null);
}

void get_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(data.unsafe_get<bool>() == true);
}

void get_const_boolean()
{
    const variable data(true);
    TRIAL_PROTOCOL_TEST(data.unsafe_get<bool>() == true);
}

void get_integer()
{
    {
        const signed char value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed char>() == value);
    }
    {
        const unsigned char value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned char>() == value);
    }
    {
        const signed short int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed short int>() == value);
    }
    {
        const unsigned short int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned short int>() == value);
    }
    {
        const signed int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed int>() == value);
    }
    {
        const unsigned int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned int>() == value);
    }
    {
        const signed long int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed long int>() == value);
    }
    {
        const unsigned long int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned long int>() == value);
    }
    {
        const signed long long int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed long long int>() == value);
    }
    {
        const unsigned long long int value{2};
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned long long int>() == value);
    }
}

void get_const_integer()
{
    {
        const signed char value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed char>() == value);
    }
    {
        const unsigned char value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned char>() == value);
    }
    {
        const signed short int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed short int>() == value);
    }
    {
        const unsigned short int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned short int>() == value);
    }
    {
        const signed int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed int>() == value);
    }
    {
        const unsigned int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned int>() == value);
    }
    {
        const signed long int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed long int>() == value);
    }
    {
        const unsigned long int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned long int>() == value);
    }
    {
        const signed long long int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<signed long long int>() == value);
    }
    {
        const unsigned long long int value{2};
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<unsigned long long int>() == value);
    }
}

void get_number()
{
    {
        const float value = 3.0f;
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<float>() == value);
    }
    {
        const double value = 3.0;
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<double>() == value);
    }
    {
        const long double value = 3.0L;
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<long double>() == value);
    }
}

void get_const_number()
{
    {
        const float value = 3.0f;
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<float>() == value);
    }
    {
        const double value = 3.0;
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<double>() == value);
    }
    {
        const long double value = 3.0L;
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<long double>() == value);
    }
}

void get_string()
{
    // string
    {
        std::string value = "alpha";
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::string_type>() == value);
    }
    // string literal
    {
        const char *value = "alpha";
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::string_type>() == value);
    }
    // wstring
    {
        std::wstring value = L"alpha";
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::wstring_type>() == value);
    }
    // wstring literal
    {
        const wchar_t *value = L"alpha";
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::wstring_type>() == value);
    }
    // u16string
    {
        std::u16string value = u"alpha";
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::u16string_type>() == value);
    }
    // u16string literal
    {
        const char16_t *value = u"alpha";
        variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::u16string_type>() == value);
    }
}

void get_const_string()
{
    // string
    {
        std::string value = "alpha";
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::string_type>() == value);
    }
    // string literal
    {
        const char *value = "alpha";
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::string_type>() == value);
    }
    // wstring
    {
        std::wstring value = L"alpha";
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::wstring_type>() == value);
    }
    // wstring literal
    {
        const wchar_t *value = L"alpha";
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::wstring_type>() == value);
    }
    // u16string
    {
        std::u16string value = u"alpha";
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::u16string_type>() == value);
    }
    // u16string literal
    {
        const char16_t *value = u"alpha";
        const variable data(value);
        TRIAL_PROTOCOL_TEST(data.unsafe_get<variable::u16string_type>() == value);
    }
}

void get_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto& result = data.unsafe_get<variable::array_type>();
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 data.begin(), data.end(),
                                 std::equal_to<variable>());
}

void get_const_array()
{
    const variable data = array::make({ true, 2, 3.0, "alpha" });
    const auto& result = data.unsafe_get<variable::array_type>();
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 data.begin(), data.end(),
                                 std::equal_to<variable>());
}

void get_map()
{
    variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    auto& result = data.unsafe_get<variable::map_type>();
    TRIAL_PROTOCOL_TEST(data["alpha"] == result.at("alpha"));
    TRIAL_PROTOCOL_TEST(data["bravo"] == result.at("bravo"));
    TRIAL_PROTOCOL_TEST(data["charlie"] == result.at("charlie"));
    TRIAL_PROTOCOL_TEST(data["delta"] == result.at("delta"));
}

void get_const_map()
{
    const variable data = map::make(
        {
            { "alpha", true },
            { "bravo", 2 },
            { "charlie", 3.0 },
            { "delta", "beryllium" }
        });
    const auto& result = data.unsafe_get<variable::map_type>();
    TRIAL_PROTOCOL_TEST(data["alpha"] == result.at("alpha"));
    TRIAL_PROTOCOL_TEST(data["bravo"] == result.at("bravo"));
    TRIAL_PROTOCOL_TEST(data["charlie"] == result.at("charlie"));
    TRIAL_PROTOCOL_TEST(data["delta"] == result.at("delta"));
}

void run()
{
    get_null();
    get_const_null();
    get_boolean();
    get_const_boolean();
    get_integer();
    get_const_integer();
    get_number();
    get_const_number();
    get_string();
    get_const_string();
    get_array();
    get_const_array();
    get_map();
    get_const_map();
}

} // namespace unsafe_get_suite

//-----------------------------------------------------------------------------
// variable::value
//-----------------------------------------------------------------------------

namespace value_suite
{

void test_null_as_null()
{
    variable data;
    std::error_code error;
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST(!error);
}

void fail_null_as_boolean()
{
    variable data;
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), bool{});
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_integer()
{
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(error), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(error), 0U);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_null_as_number()
{
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_null_as_string()
{
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<std::string>(error), std::string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == std::wstring{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data;
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == std::u16string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_null_as_array()
{
    variable data;
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_null_as_map()
{
    variable data;
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_null()
{
    variable data(false);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), false);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_boolean_as_boolean()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
}

void test_boolean_as_integer()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), int(data));
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), int(data));
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1);
    }
}

void test_boolean_as_number()
{
    {
        variable data(false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    }
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 1.0L);
    }
}

void fail_boolean_as_string()
{
    {
        variable data(false);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), false);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<std::string>(error), std::string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(false);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), false);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == std::wstring{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(false);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), false);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == std::u16string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_boolean_as_array()
{
    variable data(false);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_boolean_as_map()
{
    variable data(false);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_null()
{
    variable data(0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), 0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_integer_as_boolean()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
    {
        variable data(1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data = std::numeric_limits<signed int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data(0U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));
    }
    {
        variable data(1U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
    {
        variable data = std::numeric_limits<unsigned int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
    }
}

void test_integer_as_integer()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data = std::numeric_limits<signed int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(),
                                  std::numeric_limits<signed int>::max());
    }
    {
        variable data(0U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        variable data(1U);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data = std::numeric_limits<unsigned int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(),
                                  std::numeric_limits<unsigned int>::max());
    }
}

void test_integer_as_number()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    }
    {
        variable data(1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 1.0L);
    }
    {
        variable data = std::numeric_limits<signed int>::max();
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(),
                                  std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(),
                                  std::numeric_limits<signed int>::max());
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(),
                                  std::numeric_limits<signed int>::max());
    }
}

void fail_integer_as_string()
{
    {
        variable data(0);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), 0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<std::string>(error), std::string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), 0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == std::wstring{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), 0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == std::u16string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_integer_as_array()
{
    variable data(0);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_integer_as_map()
{
    variable data(0);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_float_as_null()
{
    variable data(0.0f);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_float_as_boolean()
{
    variable data(0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));

    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);

    data = std::numeric_limits<float>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void test_float_as_integer()
{
    {
        variable data(0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data(2.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
    }
    {
        variable data(0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        variable data(1.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data(2.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
    }
}

void test_float_as_number()
{
    variable data(0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), float(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), double(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), (long double)(data));

    data = std::numeric_limits<float>::min();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::min());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<float>::min());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<float>::min());

    data = std::numeric_limits<float>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::max());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<float>::max());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<float>::max());
}

void fail_float_as_string()
{
    {
        variable data(0.0f);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<std::string>(error), std::string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0.0f);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == std::wstring{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0.0f);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == std::u16string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_float_as_array()
{
    variable data(0.0f);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_float_as_map()
{
    variable data(0.0f);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_double_as_null()
{
    variable data(0.0);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_double_as_boolean()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));

    data = 1.0;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);

    data = std::numeric_limits<double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void test_double_as_integer()
{
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data(2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
    }
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0u);
    }
    {
        variable data(1.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data(2.0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
    }
}

void test_double_as_number()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), float(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), double(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), (long double)(data));

    data = std::numeric_limits<double>::min();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f); // Underflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<double>::min());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<double>::min());

    data = std::numeric_limits<double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::infinity()); // Overflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<double>::max());
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<double>::max());
}

void fail_double_as_string()
{
    {
        variable data(0.0);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<std::string>(error), std::string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0.0);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == std::wstring{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0.0);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == std::u16string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_double_as_array()
{
    variable data(0.0);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_double_as_map()
{
    variable data(0.0);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_long_double_as_null()
{
    variable data(0.0L);
    std::error_code error;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0);
    TRIAL_PROTOCOL_TEST(!error);
    data.value<nullable>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void test_long_double_as_boolean()
{
    variable data(0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), false);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), bool(data));

    data = 1.0L;
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);

    data = std::numeric_limits<long double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(), true);
}

void test_long_double_as_integer()
{
    {
        variable data(0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 0);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 1);
    }
    {
        variable data(2.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<signed int>(), 2);
    }
    {
        variable data(0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 0U);
    }
    {
        variable data(1.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 1U);
    }
    {
        variable data(2.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<unsigned int>(), 2U);
    }
}

void test_long_double_as_number()
{
    variable data(0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), float(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), double(data));
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), 0.0L);
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), (long double)(data));

    data = std::numeric_limits<long double>::min();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), 0.0f); // Underflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), 0.0); // Underflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<long double>::min());

    data = std::numeric_limits<long double>::max();
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(), std::numeric_limits<float>::infinity()); // Overflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(), std::numeric_limits<double>::infinity()); // Overflow
    TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(), std::numeric_limits<long double>::max());
}

void fail_long_double_as_string()
{
    {
        variable data(0.0L);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<std::string>(error), std::string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0.0L);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == std::wstring{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(0.0L);
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0);
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == std::u16string{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_long_double_as_array()
{
    variable data(0.0L);
    std::error_code error;
    data.value<array>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_long_double_as_map()
{
    variable data(0.0L);
    std::error_code error;
    data.value<map>(error);
    TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
}

void fail_string_as_null()
{
    {
        variable data("alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<std::string>(error), "alpha");
        TRIAL_PROTOCOL_TEST(!error);
        data.value<nullable>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(L"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == L"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        data.value<nullable>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(u"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == u"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        data.value<nullable>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_string_as_boolean()
{
    {
        variable data("alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), "alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), bool{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(L"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == L"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), bool{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(u"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == u"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<bool>(error), bool{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_string_as_integer()
{
    {
        variable data("alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), "alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), int{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(L"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == L"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), int{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(u"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == u"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<int>(error), int{});
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_string_as_number()
{
    {
        variable data("alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(error), "alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
        error = {};
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
        error = {};
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(L"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>(error) == L"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
        error = {};
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
        error = {};
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(u"alpha");
        std::error_code error;
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>(error) == u"alpha");
        TRIAL_PROTOCOL_TEST(!error);
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<float>(error), 0.0f);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
        error = {};
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<double>(error), 0.0);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
        error = {};
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<long double>(error), 0.0L);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void test_string_as_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "alpha");

        data = "bravo";
        TRIAL_PROTOCOL_TEST_EQUAL(data.value<string>(), "bravo");
    }
    {
        variable data(L"alpha");
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"alpha");

        data = L"bravo";
        TRIAL_PROTOCOL_TEST(data.value<std::wstring>() == L"bravo");
    }
    {
        variable data(u"alpha");
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"alpha");

        data = u"bravo";
        TRIAL_PROTOCOL_TEST(data.value<std::u16string>() == u"bravo");
    }
}

void fail_string_as_array()
{
    {
        variable data("alpha");
        std::error_code error;
        data.value<array>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(L"alpha");
        std::error_code error;
        data.value<array>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(u"alpha");
        std::error_code error;
        data.value<array>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void fail_string_as_map()
{
    {
        variable data("alpha");
        std::error_code error;
        data.value<map>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(L"alpha");
        std::error_code error;
        data.value<map>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
    {
        variable data(u"alpha");
        std::error_code error;
        data.value<map>(error);
        TRIAL_PROTOCOL_TEST_EQUAL(error, make_error_code(incompatible_type));
    }
}

void test_array_as_array()
{
    variable data = array::make({ 1, 2, 3 });
    auto result = data.value<array>();
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 data.begin(), data.end(),
                                 std::equal_to<variable>());
}

void test_array_with_size()
{
    variable data = array::repeat(4, true);
    variable result = array::make({ true, true, true, true });
    TRIAL_PROTOCOL_TEST_ALL_WITH(result.begin(), result.end(),
                                 data.begin(), data.end(),
                                 std::equal_to<variable>());
}

void run()
{
    test_null_as_null();
    fail_null_as_boolean();
    fail_null_as_integer();
    fail_null_as_number();
    fail_null_as_string();
    fail_null_as_array();
    fail_null_as_map();

    fail_boolean_as_null();
    test_boolean_as_boolean();
    test_boolean_as_integer();
    test_boolean_as_number();
    fail_boolean_as_string();
    fail_boolean_as_array();
    fail_boolean_as_map();

    fail_integer_as_null();
    test_integer_as_boolean();
    test_integer_as_integer();
    test_integer_as_number();
    fail_integer_as_string();
    fail_integer_as_array();
    fail_integer_as_map();

    fail_float_as_null();
    test_float_as_boolean();
    test_float_as_integer();
    test_float_as_number();
    fail_float_as_string();
    fail_float_as_array();
    fail_float_as_map();

    fail_double_as_null();
    test_double_as_boolean();
    test_double_as_integer();
    test_double_as_number();
    fail_double_as_string();
    fail_double_as_array();
    fail_double_as_map();

    fail_long_double_as_null();
    test_long_double_as_boolean();
    test_long_double_as_integer();
    test_long_double_as_number();
    fail_long_double_as_string();
    fail_long_double_as_array();
    fail_long_double_as_map();

    fail_string_as_null();
    fail_string_as_boolean();
    fail_string_as_integer();
    fail_string_as_number();
    test_string_as_string();
    fail_string_as_array();
    fail_string_as_map();

    test_array_as_array();
    test_array_with_size();
}

} // namespace value_suite

//-----------------------------------------------------------------------------
// Count
//-----------------------------------------------------------------------------

namespace count_suite
{

void count_null()
{
    // Null is always empty
    variable data;

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_boolean()
{
    variable data(true);

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_integer()
{
    variable data(2);

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_number()
{
    variable data(3.0);

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_string()
{
    {
        variable data("alpha");

        TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count("bravo"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("bravo")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
    }
    {
        variable data(L"alpha");

        TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"alpha"), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"alpha")), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"bravo"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"bravo")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
    }
    {
        variable data(u"alpha");

        TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(L"alpha"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(L"alpha")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"alpha"), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"alpha")), 1);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(u"bravo"), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(u"bravo")), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
        TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
    }
}

void count_array()
{
    variable data = array::make(
        { null, true, 2, 3.0, "hydrogen",
          null, true, 2, 3.0,
          null, true, 2,
          null, true,
          null });

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("hydrogen")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make({ null })), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(data), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void count_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", null},
            {"golf", true},
            {"hotel", 2},
            {"india", 3.0},
            {"juliet", null},
            {"kilo", true},
            {"lima", 2},
            {"mike", null},
            {"november", true},
            {"oscar", null}
        });

    TRIAL_PROTOCOL_TEST_EQUAL(data.count(null), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable()), 5);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(true), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(true)), 4);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(false), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(false)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(2), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(2)), 3);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(22), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(22)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(3.0), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(3.0)), 2);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(33.0), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable(33.0)), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("hydrogen"), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("hydrogen")), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count("alpha"), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(variable("alpha")), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(array::make()), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(data), 0);
    TRIAL_PROTOCOL_TEST_EQUAL(data.count(map::make()), 0);
}

void run()
{
    count_null();
    count_boolean();
    count_integer();
    count_number();
    count_string();
    count_array();
    count_map();
}

} // namespace count_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    container_concept_suite::run();

    ctor_suite::run();
    is_suite::run();
    token_suite::run();

    copy_suite::run();
    move_suite::run();
    assign_suite::run();

    unsafe_get_suite::run();
    value_suite::run();

    count_suite::run();

    return boost::report_errors();
}
