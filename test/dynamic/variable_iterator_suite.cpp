///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <iterator>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/protocol/dynamic/variable.hpp>

using namespace trial::protocol::dynamic;

//-----------------------------------------------------------------------------
// ForwardIterator concept
//-----------------------------------------------------------------------------

namespace concept_suite
{

void iterator_move_constructible()
{
    static_assert(std::is_move_constructible<variable::iterator>::value, "is_move_constructible");
}

void iterator_copy_constructible()
{
    static_assert(std::is_copy_constructible<variable::iterator>::value, "is_copy_constructible");
}

void iterator_copy_assignable()
{
    static_assert(std::is_copy_assignable<variable::iterator>::value, "is_copy_assignable");
}

void iterator_destructible()
{
    static_assert(std::is_destructible<variable::iterator>::value, "is_destructible");
}

void iterator_swappable()
{
    using std::swap;
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    variable::iterator b = data.end();
    swap(a, b);
    TRIAL_PROTOCOL_TEST(a == data.end());
    TRIAL_PROTOCOL_TEST(b == data.begin());
}

void iterator_traits()
{
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::value_type, variable::iterator::value_type>::value, "value_type");
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::difference_type, variable::iterator::difference_type>::value, "difference_type");
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::reference, variable::iterator::reference>::value, "reference");
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::pointer, variable::iterator::pointer>::value, "pointer");
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::iterator_category, variable::iterator::iterator_category>::value, "iterator_category");
}

void iterator_dereferenceable()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    variable result = *a;
    TRIAL_PROTOCOL_TEST(result == true);
}

void iterator_incrementable()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    variable::iterator& b = ++a;
    TRIAL_PROTOCOL_TEST(b == a);
    TRIAL_PROTOCOL_TEST(b != data.begin());
}

void input_iterator_equality_comparable()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    variable::iterator b = data.begin();
    variable::iterator c = data.begin();
    TRIAL_PROTOCOL_TEST(a == a);
    TRIAL_PROTOCOL_TEST(a == b);
    TRIAL_PROTOCOL_TEST(b == a);
    TRIAL_PROTOCOL_TEST(b == c);
    TRIAL_PROTOCOL_TEST(a == c);

    variable::iterator d = data.end();
    TRIAL_PROTOCOL_TEST(a != d);
}

void input_iterator_dereferenceable()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    TRIAL_PROTOCOL_TEST_EQUAL((*a).size(), 1);
    TRIAL_PROTOCOL_TEST_EQUAL(a->size(), 1);
}

void input_iterator_post_incrementable()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    variable::iterator b = a++;
    TRIAL_PROTOCOL_TEST(a != data.begin());
    TRIAL_PROTOCOL_TEST(b == data.begin());
}

void forward_iterator_default_constructible()
{
    static_assert(std::is_default_constructible<variable::iterator>::value, "default constructible");
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    variable::iterator b;
    TRIAL_PROTOCOL_TEST(a != b);
    TRIAL_PROTOCOL_TEST(b != a);
    b = a;
    TRIAL_PROTOCOL_TEST(a == b);
    TRIAL_PROTOCOL_TEST(b == a);
}

void forward_iterator_multipass()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    variable::iterator b = a;
    TRIAL_PROTOCOL_TEST(a == b);
    ++a;
    ++b;
    TRIAL_PROTOCOL_TEST(a == b);
    TRIAL_PROTOCOL_TEST(*a == *b);
}

void run()
{
    // [iterator.iterators]
    iterator_move_constructible();
    iterator_copy_constructible();
    iterator_copy_assignable();
    iterator_destructible();
    iterator_swappable();
    iterator_traits();
    iterator_dereferenceable();
    iterator_incrementable();

    // [input.iterators]
    input_iterator_equality_comparable();
    input_iterator_dereferenceable();
    input_iterator_post_incrementable();

    // [forward.iterators]
    forward_iterator_default_constructible();
    forward_iterator_multipass();
}

} // namespace concept_suite

//-----------------------------------------------------------------------------
// std::iterator_traits
//-----------------------------------------------------------------------------

namespace iterator_traits_suite
{

void test_difference_type()
{
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::difference_type, variable::iterator::difference_type>::value,
                  "variable::iterator::difference_type");
    static_assert(std::is_same<std::iterator_traits<variable::const_iterator>::difference_type, variable::const_iterator::difference_type>::value,
                  "variable::const_iterator::difference_type");
}

void test_value_type()
{
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::value_type, variable::iterator::value_type>::value,
                  "variable::iterator::value_type");
    static_assert(std::is_same<std::iterator_traits<variable::const_iterator>::value_type, variable::const_iterator::value_type>::value,
                  "variable::const_iterator::value_type");
}

void test_pointer()
{
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::pointer, variable::iterator::pointer>::value,
                  "variable::iterator::pointer");
    static_assert(std::is_same<std::iterator_traits<variable::const_iterator>::pointer, variable::const_iterator::pointer>::value,
                  "variable::const_iterator::pointer");
}

void test_reference()
{
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::reference, variable::iterator::reference>::value,
                  "variable::iterator::reference");
    static_assert(std::is_same<std::iterator_traits<variable::const_iterator>::reference, variable::const_iterator::reference>::value,
                  "variable::const_iterator::reference");
}

void test_iterator_category()
{
    static_assert(std::is_same<std::iterator_traits<variable::iterator>::iterator_category, variable::iterator::iterator_category>::value,
                  "variable::iterator::iterator_category");
    static_assert(std::is_same<std::iterator_traits<variable::const_iterator>::iterator_category, variable::const_iterator::iterator_category>::value,
                  "variable::const_iterator::iterator_category");
}

void run()
{
    test_difference_type();
    test_value_type();
    test_pointer();
    test_reference();
    test_iterator_category();
}

} // namespace iterator_traits_suite

//-----------------------------------------------------------------------------
// std::begin
//-----------------------------------------------------------------------------

namespace begin_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST(data.begin() == data.end());
}

void test_const_null()
{
    const variable data;
    TRIAL_PROTOCOL_TEST(data.begin() == data.end());
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_boolean()
{
    const variable data(true);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_integer()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_integer()
{
    const variable data(0);
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_number()
{
    {
        variable data(0.0f);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
    }
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
    }
    {
        variable data(0.0L);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
    }
}

void test_const_number()
{
    {
        const variable data(0.0f);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
    }
    {
        const variable data(0.0);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
    }
    {
        const variable data(0.0L);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
    }
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_string()
{
    const variable data("alpha");
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_array()
{
    variable data = array::make({ true, 1, 2.0, "alpha" });
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_array()
{
    const variable data = array::make({ true, 1, 2.0, "alpha" });
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_map()
{
    variable data = map::make(
        {
            {"key", "alpha"}
        });
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void test_const_map()
{
    const variable data = map::make(
        {
            {"key", "alpha"}
        });
    TRIAL_PROTOCOL_TEST(data.begin() != data.end());
}

void convert_to_const()
{
    variable data = array::make({ true, 1, 2.0, "alpha" });
    // Conversion from iterator to const_iterator
    variable::const_iterator begin = data.begin();
    variable::const_iterator end = data.end();
    TRIAL_PROTOCOL_TEST(begin != end);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(begin, end), 4);
}

void run()
{
    test_null();
    test_const_null();
    test_boolean();
    test_const_boolean();
    test_integer();
    test_const_integer();
    test_number();
    test_const_number();
    test_string();
    test_const_string();
    test_array();
    test_const_array();
    test_map();
    test_const_map();
    convert_to_const();
}

} // namespace begin_suite

//-----------------------------------------------------------------------------
// operator++()
//-----------------------------------------------------------------------------

namespace pre_increment_suite
{

void test_null()
{
    {
        variable data;
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where == data.end());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data;
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where == data.end());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_boolean()
{
    {
        variable data(true);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(true);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_integer()
{
    {
        variable data(2);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(2);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_number()
{
    {
        variable data(3.0f);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0f);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(3.0f);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0f);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(3.0);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(3.0);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(3.0L);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(3.0L);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_string()
{
    {
        variable data("alpha");
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data("alpha");
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_array()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha" });
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = array::make({ true, 2, 3.0, "alpha" });
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_array_number()
{
    {
        variable data = array::make({ 1.0f, 2.0, 3.0L });
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 1.0f);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 2.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = array::make({ 1.0f, 2.0, 3.0L });
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 1.0f);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 2.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_map()
{
    {
        variable data = map::make(
            {
                {"alpha", true},
                {"bravo", 2},
                {"charlie", 3.0},
                {"delta", "hydrogen"}
            });
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 8);
        TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = map::make(
            {
                {"alpha", true},
                {"bravo", 2},
                {"charlie", 3.0},
                {"delta", "hydrogen"}
            });
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 8);
        TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_array_number();
    test_map();
}

} // namespace pre_increment_suite

//-----------------------------------------------------------------------------
// operator++(int)
//-----------------------------------------------------------------------------

namespace post_increment_suite
{

void test_null()
{
    {
        variable data;
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::iterator result = where++;
        TRIAL_PROTOCOL_TEST(result == data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data;
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::const_iterator result = where++;
        TRIAL_PROTOCOL_TEST(result == data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_boolean()
{
    {
        variable data(true);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        variable::iterator result = where++;
        TRIAL_PROTOCOL_TEST(result != data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(true);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        variable::const_iterator result = where++;
        TRIAL_PROTOCOL_TEST(result != data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_integer()
{
    {
        variable data(2);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        variable::iterator result = where++;
        TRIAL_PROTOCOL_TEST(result != data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(2);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        variable::const_iterator result = where++;
        TRIAL_PROTOCOL_TEST(result != data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_number()
{
    {
        variable data(3.0f);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0f);
        variable::iterator result = where++;
        TRIAL_PROTOCOL_TEST(result != data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(3.0);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        variable::iterator result = where++;
        TRIAL_PROTOCOL_TEST(result != data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(3.0L);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        variable::iterator result = where++;
        TRIAL_PROTOCOL_TEST(result != data.end());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_string()
{
    variable data("alpha");
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(result != data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    TRIAL_PROTOCOL_TEST(*where == variable(true));
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(true));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    TRIAL_PROTOCOL_TEST(*where == variable(2));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(2));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    TRIAL_PROTOCOL_TEST(*where == variable(3.0));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(3.0));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
    TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable("alpha"));
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_map()
{
    variable data = map::make(
        {
            {"alpha", true},
            {"bravo", 2},
            {"charlie", 3.0},
            {"delta", "hydrogen"}
        });
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    TRIAL_PROTOCOL_TEST(*where == variable(true));
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(true));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    TRIAL_PROTOCOL_TEST(*where == variable(2));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(2));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    TRIAL_PROTOCOL_TEST(*where == variable(3.0));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(3.0));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 8);
    TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable("hydrogen"));
    TRIAL_PROTOCOL_TEST(where == data.end());
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

} // namespace post_increment_suite

//-----------------------------------------------------------------------------
// Dereference
//-----------------------------------------------------------------------------

namespace dereference_suite
{

void get_null()
{
    {
        variable data;
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == null);
    }
    {
        const variable data;
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == null);
    }
}

void get_boolean()
{
    {
        variable data(true);
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == true);
    }
    {
        const variable data(true);
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == true);
    }
}

void get_integer()
{
    {
        const signed int value = 0;
        variable data(value);
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == value);
    }
    {
        const unsigned int value = 0U;
        variable data(value);
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == value);
    }
}

void get_number()
{
    {
        const float value = 0.0f;
        variable data(value);
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == value);
    }
    {
        const double value = 0.0;
        variable data(value);
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == value);
    }
    {
        const long double value = 0.0L;
        variable data(value);
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == value);
    }
}

void get_string()
{
    variable data("alpha");
    auto where = data.begin();
    TRIAL_PROTOCOL_TEST(*where == "alpha");
}

void get_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.begin();
    TRIAL_PROTOCOL_TEST(where->is<bool>());
    TRIAL_PROTOCOL_TEST(*where == true);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<int>());
    TRIAL_PROTOCOL_TEST(*where == 2);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<float>());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<string>());
    TRIAL_PROTOCOL_TEST(*where == "alpha");
}

void get_map()
{
    variable data = map::make(
        {
            {"alpha", true},
            {"bravo", 2},
            {"charlie", 3.0},
            {"delta", "hydrogen"}
        });
    auto where = data.begin();
    TRIAL_PROTOCOL_TEST(where->is<bool>());
    TRIAL_PROTOCOL_TEST(*where == true);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<int>());
    TRIAL_PROTOCOL_TEST(*where == 2);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<float>());
    TRIAL_PROTOCOL_TEST(*where == 3.0);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->is<string>());
    TRIAL_PROTOCOL_TEST(*where == "hydrogen");
}

void run()
{
    // get_null(); // FIXME: Crashes
    get_boolean();
    get_integer();
    get_number();
    get_string();
    get_array();
    get_map();
}

} // namespace dereference_suite

//-----------------------------------------------------------------------------
// std::distance
//-----------------------------------------------------------------------------

namespace distance_suite
{

void test_null()
{
    variable data;
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 0);
}

void test_boolean()
{
    variable data(true);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_integer()
{
    variable data(0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_number()
{
    variable data(0.0);
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_string()
{
    variable data("alpha");
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 4);
}

void test_array_nulls()
{
    variable data = array::make({ null, null, null });
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 3);
}

void test_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 3);
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_array();
    test_array_nulls();
    test_map();
}

} // namespace distance_suite

//-----------------------------------------------------------------------------
// Range-based for loop
//-----------------------------------------------------------------------------

namespace range_for_suite
{

void sum_null()
{
    variable data;
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 0);
}

void sum_boolean()
{
    variable data(true);
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void sum_integer()
{
    variable data(0);
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void sum_number()
{
    variable data(0.0);
    variable::size_type size = 0;
    for (auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void sum_string()
{
    variable data("alpha");
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 5);
}

void sum_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1 + 1 + 1 + 5);
}

void sum_array_nulls()
{
    variable data = array::make({ null, null, null });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 0 + 0 + 0);
}

void sum_array_array()
{
    variable data = array::make({ array::make({ 1 }), array::make({ 2, 3 }) });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1 + 2);
}

void sum_map()
{
    variable data = map::make(
        {
            {"alpha", "hydrogen"},
            {"bravo", "helium"},
            {"charlie", "lithium"}
        });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 8 + 6 + 7);
}

void sum_map_array()
{
    variable data = map::make(
        {
            { "alpha", array::make({ 1 }) },
            { "bravo", array::make({ 2, 3, 4 }) },
            { "charlie", array::make() }
        });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1 + 3 + 0);
}

void sum_map_map()
{
    variable data = map::make(
        {
            { "alpha", map::make({{ "alice", 1 }}) },
            { "bravo", map::make({{ "alice", true }, { "bob", 2 }}) },
            { "charlie", map::make() }
        });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1 + 2 + 0);
}

void run()
{
    sum_null();
    sum_boolean();
    sum_integer();
    sum_number();
    sum_string();
    sum_array();
    sum_array_nulls();
    sum_array_array();
    sum_map();
    sum_map_array();
    sum_map_map();
}

} // namespace range_for_suite

//-----------------------------------------------------------------------------
// key_iterator
//-----------------------------------------------------------------------------

namespace key_iterator_suite
{

void iterate_null()
{
    variable data;
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_boolean()
{
    variable data(true);
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_integer()
{
    variable data(2);
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_number()
{
    {
        variable data(3.0f);
        auto where = data.key_begin();
        TRIAL_PROTOCOL_TEST(where != data.key_end());
        TRIAL_PROTOCOL_TEST(*where == 0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable data(3.0);
        auto where = data.key_begin();
        TRIAL_PROTOCOL_TEST(where != data.key_end());
        TRIAL_PROTOCOL_TEST(*where == 0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable data(3.0L);
        auto where = data.key_begin();
        TRIAL_PROTOCOL_TEST(where != data.key_end());
        TRIAL_PROTOCOL_TEST(*where == 0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
}

void iterate_string()
{
    variable data("alpha");
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 1);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 2);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 3);
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_map()
{
    variable data = map::make(
        {
            {"key", "alpha"}
        });
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == "key");
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void run()
{
    iterate_null();
    iterate_boolean();
    iterate_integer();
    iterate_number();
    iterate_string();
    iterate_array();
    iterate_map();
}

} // namespace key_iterator_suite

//-----------------------------------------------------------------------------
// variable::find()
//-----------------------------------------------------------------------------

namespace find_suite
{

void find_null()
{
    // Null is a zero-sized container, so find always returns end()
    variable data;
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_boolean()
{
    variable data(true);
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({true}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_boolean()
{
    const variable data(true);
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(array::make({true}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(map::make("alpha", true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_integer()
{
    variable data(2);
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({2}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", 2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_integer()
{
    const variable data(2);
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(array::make({2}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(map::make("alpha", 2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_number()
{
    variable data(3.0);
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({3.0}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", 3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_number()
{
    const variable data(3.0);
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(array::make({3.0}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(map::make("alpha", 3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_string()
{
    variable data("hydrogen");
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(std::string("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_string()
{
    const variable data("hydrogen");
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::string("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(std::string("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_array()
{
    variable data = array::make({ null, true, 2, 3.0, "hydrogen" });
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_array()
{
    const variable data = array::make({ null, true, 2, 3.0, "hydrogen" });
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_array_with_array()
{
    variable data = array::make({ null, true, 2, 3.0, "hydrogen", array::make({ "helium" }) });
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find("helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_array_with_map()
{
    variable data = array::make({ null, true, 2, 3.0, "hydrogen", map::make("bravo", "helium") });
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find("helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("bravo", "helium"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
}

void find_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"}
        });
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_map()
{
    const variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"}
        });
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::const_iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::const_iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::const_iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::const_iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_map_with_array()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", array::make({ "helium" })}
        });
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find("helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_map_with_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", map::make("golf", "helium")}
        });
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
    }
    {
        variable::iterator where = data.find(false);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(false));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 2);
    }
    {
        variable::iterator where = data.find(22);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(22));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 3);
    }
    {
        variable::iterator where = data.find(33.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(33.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("hydrogen");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find(variable("hydrogen"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 4);
    }
    {
        variable::iterator where = data.find("helium");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find("alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable("alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(map::make("golf", "helium"));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
}

void run()
{
    find_null();
    find_boolean();
    find_const_boolean();
    find_integer();
    find_const_integer();
    find_number();
    find_const_number();
    find_string();
    find_const_string();
    find_array();
    find_const_array();
    find_array_with_array();
    find_array_with_map();
    find_map();
    find_const_map();
    find_map_with_array();
    find_map_with_map();
}

} // namespace find_suite

//-----------------------------------------------------------------------------
// variable::key::find()
//-----------------------------------------------------------------------------

namespace key_find_suite
{

void find_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"}
        });
    {
        variable::key_iterator where = data.key_find("alpha");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 0);
    }
    {
        variable::key_iterator where = data.key_find(null);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = data.key_find("bravo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 1);
    }
    {
        variable::key_iterator where = data.key_find(true);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = data.key_find("charlie");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 2);
    }
    {
        variable::key_iterator where = data.key_find(2);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = data.key_find("delta");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 3);
    }
    {
        variable::key_iterator where = data.key_find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
    {
        variable::key_iterator where = data.key_find("echo");
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.key_begin(), where), 4);
    }
    {
        variable::key_iterator where = data.key_find("hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.key_end());
    }
}

void run()
{
    find_map();
}

} // namespace key_find_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    concept_suite::run();
    iterator_traits_suite::run();
    begin_suite::run();
    pre_increment_suite::run();
    post_increment_suite::run();
    dereference_suite::run();
    distance_suite::run();
    range_for_suite::run();
    key_iterator_suite::run();

    find_suite::run();
    key_find_suite::run();

    return boost::report_errors();
}
