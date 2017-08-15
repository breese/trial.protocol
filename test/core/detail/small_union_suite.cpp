///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <string>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/core/detail/small_union.hpp>

using namespace trial::protocol::core::detail;

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

namespace ctor_suite
{

void test_int()
{
    small_union<sizeof(int), bool, int> data{true};
    TRIAL_PROTOCOL_TEST_EQUAL(data.get<bool>(), true);
}

void test_int_with_longlong()
{
    small_union<sizeof(int), bool, int, long long> data{3LL};
    TRIAL_PROTOCOL_TEST_EQUAL(data.get<long long>(), 3LL);
}

void test_int_with_string()
{
    small_union<sizeof(int), bool, int, std::string> data{std::string("alpha")};
    TRIAL_PROTOCOL_TEST_EQUAL(data.get<std::string>(), std::string("alpha"));
}

void run()
{
    test_int();
    test_int_with_longlong();
    test_int_with_string();
}

} // namespace ctor_suite

//-----------------------------------------------------------------------------
// Visitor
//-----------------------------------------------------------------------------

namespace visitor_suite
{

using storage_type = small_union<sizeof(int), bool, int>;

struct visitor_void
{
    template <typename Which>
    static void call(storage_type& self)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
    }
};

struct const_visitor_void
{
    template <typename Which>
    static void call(const storage_type& self)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
    }
};

struct visitor_int
{
    template <typename Which>
    static int call(storage_type& self)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
        return 43;
    }
};

struct const_visitor_int
{
    template <typename Which>
    static int call(const storage_type& self)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
        return 42;
    }
};

struct visitor_void_with_int
{
    template <typename Which>
    static void call(storage_type& self, int)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
    }
};

struct const_visitor_void_with_int
{
    template <typename Which>
    static void call(const storage_type& self, int)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
    }
};

struct visitor_int_with_int
{
    template <typename Which>
    static int call(storage_type& self, int value)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
        return value;
    }
};

struct const_visitor_int_with_int
{
    template <typename Which>
    static int call(const storage_type& self, int value)
    {
        if (self.which() != storage_type::index<Which>::value)
            throw std::runtime_error("");
        return value;
    }
};

void test_void()
{
    storage_type data{true};
    data.call<visitor_void, void>();
    data.call<const_visitor_void, void>();
}

void test_const_void()
{
    const storage_type data{true};
    data.call<const_visitor_void, void>();
}

void test_void_with_int()
{
    storage_type data{true};
    data.call<visitor_void_with_int, void>(42);
    data.call<const_visitor_void_with_int, void>(42);
}

void test_const_void_with_int()
{
    storage_type data{true};
    data.call<const_visitor_void_with_int, void>(42);
}

void test_int()
{
    storage_type data{true};
    TRIAL_PROTOCOL_TEST_EQUAL((data.call<const_visitor_int, int>()), 42);
    TRIAL_PROTOCOL_TEST_EQUAL((data.call<visitor_int, int>()), 43);
}

void test_const_int()
{
    const storage_type data{true};
    TRIAL_PROTOCOL_TEST_EQUAL((data.call<const_visitor_int, int>()), 42);
}

void test_int_with_int()
{
    storage_type data{true};
    TRIAL_PROTOCOL_TEST_EQUAL((data.call<const_visitor_int_with_int, int>(42)), 42);
    TRIAL_PROTOCOL_TEST_EQUAL((data.call<visitor_int_with_int, int>(43)), 43);
}

void test_const_int_with_int()
{
    const storage_type data{true};
    TRIAL_PROTOCOL_TEST_EQUAL((data.call<const_visitor_int_with_int, int>(42)), 42);
}

void run()
{
    test_void();
    test_const_void();
    test_void_with_int();
    test_const_void_with_int();
    test_int();
    test_const_int();
    test_int_with_int();
    test_const_int_with_int();
}

} // namespace visitor_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    ctor_suite::run();
    visitor_suite::run();

    return boost::report_errors();
}
