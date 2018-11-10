///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/algorithm/visit.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// dynamic::visit
//-----------------------------------------------------------------------------

namespace explicit_suite
{

struct visitor
{
    token::code::value operator()(nullable)
    {
        return token::code::null;
    }

    token::code::value operator()(bool)
    {
        return token::code::boolean;
    }

    token::code::value operator()(signed char)
    {
        return token::code::signed_char;
    }

    token::code::value operator()(unsigned char)
    {
        return token::code::unsigned_char;
    }

    token::code::value operator()(signed short int)
    {
        return token::code::signed_short_integer;
    }

    token::code::value operator()(unsigned short int)
    {
        return token::code::unsigned_short_integer;
    }

    token::code::value operator()(signed int)
    {
        return token::code::signed_integer;
    }

    token::code::value operator()(unsigned int)
    {
        return token::code::unsigned_integer;
    }

    token::code::value operator()(signed long int)
    {
        return token::code::signed_long_integer;
    }

    token::code::value operator()(unsigned long int)
    {
        return token::code::unsigned_long_integer;
    }

    token::code::value operator()(signed long long int)
    {
        return token::code::signed_long_long_integer;
    }

    token::code::value operator()(unsigned long long int)
    {
        return token::code::unsigned_long_long_integer;
    }

    token::code::value operator()(float)
    {
        return token::code::real;
    }

    token::code::value operator()(double)
    {
        return token::code::long_real;
    }

    token::code::value operator()(long double)
    {
        return token::code::long_long_real;
    }

    token::code::value operator()(const variable::string_type&)
    {
        return token::code::string;
    }

    token::code::value operator()(const variable::wstring_type&)
    {
        return token::code::wstring;
    }

    token::code::value operator()(const variable::u16string_type&)
    {
        return token::code::u16string;
    }

    token::code::value operator()(const variable::u32string_type&)
    {
        return token::code::u32string;
    }

    token::code::value operator()(const variable::array_type&)
    {
        return token::code::array;
    }

    token::code::value operator()(const variable::map_type&)
    {
        return token::code::map;
    }
};

void visit_null()
{
    variable data;
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);
}

void visit_boolean()
{
    variable data(true);
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::boolean);
}

void visit_integer()
{
    {
        signed char value = 2;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_char);
    }
    {
        unsigned char value = 2U;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_char);
    }
    {
        signed short int value = 2;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_short_integer);
    }
    {
        unsigned short int value = 2U;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_short_integer);
    }
    {
        signed int value = 2;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_integer);
    }
    {
        unsigned int value = 2U;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_integer);
    }
    {
        signed long int value = 2L;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_long_integer);
    }
    {
        unsigned long int value = 2UL;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_long_integer);
    }
    {
        signed long long int value = 2LL;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_long_long_integer);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_long_long_integer);
    }
}

void visit_real()
{
    {
        variable data(3.0f);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::real);
    }
    {
        variable data(3.0);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::long_real);
    }
    {
        variable data(3.0L);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::long_long_real);
    }
}

void visit_string()
{
    {
        variable data("alpha");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::string);
    }
    {
        variable data(L"bravo");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::wstring);
    }
    {
        variable data(u"charlie");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::u16string);
    }
    {
        variable data(U"delta");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::u32string);
    }
}

void visit_array()
{
    variable data = array::make();
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::array);
}

void visit_map()
{
    variable data = map::make();
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::map);
}

void run()
{
    visit_null();
    visit_boolean();
    visit_integer();
    visit_real();
    visit_string();
    visit_array();
    visit_map();
}

} // namespace explicit_suite

//-----------------------------------------------------------------------------

namespace implicit_value_suite
{

struct visitor
{
    template <typename T>
    token::code::value operator()(T value)
    {
        variable data(std::move(value));
        return data.code();
    }
};

void visit_null()
{
    variable data;
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);    
}

void visit_boolean()
{
    variable data(true);
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::boolean);    
}

void visit_integer()
{
    {
        signed char value = 2;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_char);
    }
    {
        unsigned char value = 2U;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_char);
    }
    {
        signed short int value = 2;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_short_integer);
    }
    {
        unsigned short int value = 2U;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_short_integer);
    }
    {
        signed int value = 2;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_integer);
    }
    {
        unsigned int value = 2U;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_integer);
    }
    {
        signed long int value = 2L;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_long_integer);
    }
    {
        unsigned long int value = 2UL;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_long_integer);
    }
    {
        signed long long int value = 2LL;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_long_long_integer);
    }
    {
        unsigned long long int value = 2ULL;
        variable data(value);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_long_long_integer);
    }
}

void visit_real()
{
    {
        variable data(3.0f);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::real);
    }
    {
        variable data(3.0);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::long_real);
    }
    {
        variable data(3.0L);
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::long_long_real);
    }
}

void visit_string()
{
    {
        variable data("alpha");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::string);
    }
    {
        variable data(L"bravo");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::wstring);
    }
    {
        variable data(u"charlie");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::u16string);
    }
    {
        variable data(U"delta");
        visitor vis;
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::u32string);
    }
}

void visit_array()
{
    variable data = array::make();
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::array);
}

void visit_map()
{
    variable data = map::make();
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::map);
}

void run()
{
    visit_null();
    visit_boolean();
    visit_integer();
    visit_real();
    visit_string();
    visit_array();
    visit_map();
}

} // namespace implicit_value_suite

//-----------------------------------------------------------------------------

namespace implicit_const_reference_suite
{

struct visitor
{
    // User-provided constructor needed for const instantiation
    visitor() = default;

    template <typename T>
    token::code::value operator()(const T&) const
    {
        return token::code::null;
    }
};

void visit()
{
    variable data("alpha");
    const visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);
}

void run()
{
    visit();
}

} // namespace implicit_const_reference_suite

//-----------------------------------------------------------------------------

namespace implicit_lvalue_reference_suite
{

struct visitor
{
    template <typename T>
    token::code::value operator()(T& value)
    {
        // Changes value (but not type)
        value = {};
        return token::code::null;
    }
};

void visit_boolean()
{
    variable data(true);
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);
    TRIAL_PROTOCOL_TEST(data == false);
}

void visit_string()
{
    variable data("alpha");
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);
    TRIAL_PROTOCOL_TEST(data == "");
}

void run()
{
    visit_boolean();
    visit_string();
}

} // namespace implicit_lvalue_reference_suite

//-----------------------------------------------------------------------------

namespace implicit_rvalue_reference_suite
{

struct visitor
{
    template <typename T>
    token::code::value operator()(T&&)
    {
        return token::code::null;
    }

    token::code::value operator()(const variable::string_type&)
    {
        // Overload is not selected because T&& takes precedence
        assert(false);
        return token::code::string;
    }
};

void visit_null()
{
    variable data;
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);
}

void visit_string()
{
    variable data("alpha");
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);
}

void run()
{
    visit_null();
    visit_string();
}

} // namespace implicit_rvalue_reference_suite

//-----------------------------------------------------------------------------

namespace partial_suite
{

struct visitor
{
    template <typename T>
    token::code::value operator()(const T&)
    {
        return token::code::string;
    }

    token::code::value operator()(nullable)
    {
        return token::code::null;
    }

    token::code::value operator()(bool)
    {
        return token::code::boolean;
    }

    token::code::value operator()(signed int)
    {
        return token::code::signed_integer;
    }

    token::code::value operator()(unsigned int)
    {
        return token::code::unsigned_integer;
    }

    token::code::value operator()(const variable::array_type&)
    {
        return token::code::array;
    }

    token::code::value operator()(const variable::map_type&)
    {
        return token::code::map;
    }
};

void visit_null()
{
    variable data;
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::null);
}

void visit_boolean()
{
    variable data(true);
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::boolean);
}

void visit_integer()
{
    visitor vis;
    // Matching
    {
        variable data(2);
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::signed_integer);
    }
    {
        variable data(2U);
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::unsigned_integer);
    }
    // Non-matching
    {
        variable data(2L);
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::string);
    }
    {
        variable data(2UL);
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::string);
    }
}

void visit_real()
{
    visitor vis;
    // Non-matching
    {
        variable data(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::string);
    }
}

void visit_array()
{
    variable data = array::make({ null, true, 2, 3.0, "alpha" });
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::array);
}

void visit_map()
{
    variable data = map::make(
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 3.0 },
            { "echo", "hydrogen" }
        });
    visitor vis;
    TRIAL_PROTOCOL_TEST_EQUAL(visit(vis, data), token::code::map);
}

void run()
{
    visit_null();
    visit_boolean();
    visit_integer();
    visit_real();
    visit_array();
    visit_map();
}

} // namespace partial_suite

//-----------------------------------------------------------------------------

namespace recursive_suite
{

struct visitor
{
    template <typename T>
    void operator()(const T&)
    {
        ++count;
    }

    void operator()(const variable::array_type& array)
    {
        for (auto& element : array)
        {
            visit(*this, element);
        }
    }

    void operator()(const variable::map_type& map)
    {
        for (auto& pair : map)
        {
            // Ignore key (pair.first)
            visit(*this, pair.second);
        }
    }

    int count {0};
};

void visit_empty_array()
{
    variable data = array::make();
    visitor vis;
    visit(vis, data);
    TRIAL_PROTOCOL_TEST_EQUAL(vis.count, 0);
}

void visit_array()
{
    const variable data = { null, true, 2, 3.0, "alpha", array::make({4, 5, 6}) };
    visitor vis;
    visit(vis, data);
    TRIAL_PROTOCOL_TEST_EQUAL(vis.count, 8);
}

void visit_map()
{
    variable data =
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 3.0 },
            { "echo", "hydrogen" },
            { "foxtrot", map::make("golf", 4) }
        };
    visitor vis;
    visit(vis, data);
    TRIAL_PROTOCOL_TEST_EQUAL(vis.count, 6);
}

void run()
{
    visit_empty_array();
    visit_array();
    visit_map();
}

} // namespace recursive_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    explicit_suite::run();
    implicit_value_suite::run();
    implicit_const_reference_suite::run();
    implicit_lvalue_reference_suite::run();
    implicit_rvalue_reference_suite::run();
    partial_suite::run();
    recursive_suite::run();

    return boost::report_errors();
}
