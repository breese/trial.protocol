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
    {
        variable data;
        TRIAL_PROTOCOL_TEST(data.begin() == data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() == data.cend());
    }
    {
        const variable data;
        TRIAL_PROTOCOL_TEST(data.begin() == data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() == data.cend());
    }
}

void test_boolean()
{
    {
        variable data(true);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(true);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_integer()
{
    {
        variable data(0);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(0);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_number()
{
    {
        variable data(0.0f);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(0.0f);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        variable data(0.0);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(0.0);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        variable data(0.0L);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(0.0L);
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_string()
{
    {
        variable data("alpha");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data("alpha");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_wstring()
{
    {
        variable data(L"bravo");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(L"bravo");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_u16string()
{
    {
        variable data(u"bravo");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(u"bravo");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_array()
{
    {
        variable data = array::make({ true, 1, 2.0, "alpha" });
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data = array::make({ true, 1, 2.0, "alpha" });
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_map()
{
    {
        variable data = map::make(
            {
                {"key", "alpha"}
            });
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data = map::make(
            {
                {"key", "alpha"}
            });
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
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
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
    test_array();
    test_map();
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

void test_wstring()
{
    {
        variable data(L"bravo");
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(L"bravo");
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_u16string()
{
    {
        variable data(u"bravo");
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(u"bravo");
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
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 7);
        TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
        TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 7);
        TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
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
                {"delta", "hydrogen"},
                {"echo", L"helium"},
                {"foxtrot", u"lithium"}
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 6);
        TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 7);
        TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = map::make(
            {
                {"alpha", true},
                {"bravo", 2},
                {"charlie", 3.0},
                {"delta", "hydrogen"},
                {"echo", L"helium"},
                {"foxtrot", u"lithium"}
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 6);
        TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 7);
        TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
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
    test_wstring();
    test_u16string();
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

void test_wstring()
{
    variable data(L"alpha");
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(result != data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_u16string()
{
    variable data(u"alpha");
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(result != data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
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
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 5);
    TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(L"bravo"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 7);
    TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(u"charlie"));
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_map()
{
    variable data = map::make(
        {
            {"alpha", true},
            {"bravo", 2},
            {"charlie", 3.0},
            {"delta", "hydrogen"},
            {"echo", L"helium"},
            {"foxtrot", u"lithium"}
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
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 6);
    TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(L"helium"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 7);
    TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(u"lithium"));
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_number();
    test_string();
    test_wstring();
    test_u16string();
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
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data;
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void get_boolean()
{
    {
        variable data(true);
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where.value() == true);
        TRIAL_PROTOCOL_TEST(*where == true);
    }
    {
        const variable data(true);
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where.value() == true);
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
    {
        variable data("alpha");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == "alpha");
    }
    {
        const variable data("alpha");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == "alpha");
    }
}

void get_wstring()
{
    {
        variable data(L"alpha");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == L"alpha");
    }
    {
        const variable data(L"alpha");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == L"alpha");
    }
}

void get_u16string()
{
    {
        variable data(u"alpha");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == u"alpha");
    }
    {
        const variable data(u"alpha");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == u"alpha");
    }
}

void get_array()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(where->is<bool>());
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(where.key(),
                                        error,
                                        "incompatible type");
        TRIAL_PROTOCOL_TEST(where.value() == true);
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<int>());
        TRIAL_PROTOCOL_TEST(where.value() == 2);
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<float>());
        TRIAL_PROTOCOL_TEST(where.value() == 3.0);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(where.value() == "alpha");
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(where.value() == L"bravo");
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(where.value() == u"charlie");
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(where->is<bool>());
        TRIAL_PROTOCOL_TEST_THROW_EQUAL(where.key(),
                                        error,
                                        "incompatible type");
        TRIAL_PROTOCOL_TEST(where.value() == true);
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<int>());
        TRIAL_PROTOCOL_TEST(where.value() == 2);
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<float>());
        TRIAL_PROTOCOL_TEST(where.value() == 3.0);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(where.value() == "alpha");
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(where.value() == L"bravo");
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(where.value() == u"charlie");
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void get_map()
{
    {
        variable data = map::make(
            {
                {"alpha", true},
                {"bravo", 2},
                {"charlie", 3.0},
                {"delta", "hydrogen"},
                {"echo", L"helium"},
                {"foxtrot", u"lithium"}
            });
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(where->is<bool>());
        TRIAL_PROTOCOL_TEST(where.key() == "alpha");
        TRIAL_PROTOCOL_TEST(where.value() == true);
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<int>());
        TRIAL_PROTOCOL_TEST(where.key() == "bravo");
        TRIAL_PROTOCOL_TEST(where.value() == 2);
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<float>());
        TRIAL_PROTOCOL_TEST(where.key() == "charlie");
        TRIAL_PROTOCOL_TEST(where.value() == 3.0);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(where.key() == "delta");
        TRIAL_PROTOCOL_TEST(where.value() == "hydrogen");
        TRIAL_PROTOCOL_TEST(*where == "hydrogen");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(where.key() == "echo");
        TRIAL_PROTOCOL_TEST(where.value() == L"helium");
        TRIAL_PROTOCOL_TEST(*where == L"helium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(where.key() == "foxtrot");
        TRIAL_PROTOCOL_TEST(where.value() == u"lithium");
        TRIAL_PROTOCOL_TEST(*where == u"lithium");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = map::make(
            {
                {"alpha", true},
                {"bravo", 2},
                {"charlie", 3.0},
                {"delta", "hydrogen"},
                {"echo", L"helium"},
                {"foxtrot", u"lithium"}
            });
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(where->is<bool>());
        TRIAL_PROTOCOL_TEST(where.key() == "alpha");
        TRIAL_PROTOCOL_TEST(where.value() == true);
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<int>());
        TRIAL_PROTOCOL_TEST(where.key() == "bravo");
        TRIAL_PROTOCOL_TEST(where.value() == 2);
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<float>());
        TRIAL_PROTOCOL_TEST(where.key() == "charlie");
        TRIAL_PROTOCOL_TEST(where.value() == 3.0);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(where.key() == "delta");
        TRIAL_PROTOCOL_TEST(where.value() == "hydrogen");
        TRIAL_PROTOCOL_TEST(*where == "hydrogen");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(where.key() == "echo");
        TRIAL_PROTOCOL_TEST(where.value() == L"helium");
        TRIAL_PROTOCOL_TEST(*where == L"helium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(where.key() == "foxtrot");
        TRIAL_PROTOCOL_TEST(where.value() == u"lithium");
        TRIAL_PROTOCOL_TEST(*where == u"lithium");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void overwrite_boolean()
{
    variable data(true);
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_integer()
{
    variable data(2);
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_number()
{
    variable data(3.0);
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_string()
{
    variable data("alpha");
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_wstring()
{
    variable data(L"bravo");
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_u16string()
{
    variable data(u"bravo");
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo" });
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 5);
    TRIAL_PROTOCOL_TEST(data[0] == null);
}

void overwrite_map()
{
    variable data = map::make(
        {
            {"alpha", null},
            {"bravo", true},
            {"charlie", 2},
            {"delta", 3.0},
            {"echo", "hydrogen"},
            {"foxtrot", L"helium"}
        });
    auto where = data.begin();
    *where = 42;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 6);
    TRIAL_PROTOCOL_TEST(data["alpha"] == 42);
}

void run()
{
    get_null();
    get_boolean();
    get_integer();
    get_number();
    get_string();
    get_wstring();
    get_u16string();
    get_array();
    get_map();

    overwrite_boolean();
    overwrite_integer();
    overwrite_number();
    overwrite_string();
    overwrite_wstring();
    overwrite_u16string();
    overwrite_array();
    overwrite_map();
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

void test_wstring()
{
    variable data(L"bravo");
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_u16string()
{
    variable data(u"charlie");
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 6);
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
    test_wstring();
    test_u16string();
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

void sum_wstring()
{
    variable data(L"bravo");
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 5);
}

void sum_u16string()
{
    variable data(u"charlie");
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 7);
}

void sum_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1 + 1 + 1 + 5 + 5 + 7);
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
    sum_wstring();
    sum_u16string();
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

void iterate_wstring()
{
    variable data(L"bravo");
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_u16string()
{
    variable data(u"charlie");
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie" });
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    TRIAL_PROTOCOL_TEST(where.key() == 0);
    TRIAL_PROTOCOL_TEST(where.value() == true);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 1);
    TRIAL_PROTOCOL_TEST(where.key() == 1);
    TRIAL_PROTOCOL_TEST(where.value() == 2);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 2);
    TRIAL_PROTOCOL_TEST(where.key() == 2);
    TRIAL_PROTOCOL_TEST(where.value() == 3.0);
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 3);
    TRIAL_PROTOCOL_TEST(where.key() == 3);
    TRIAL_PROTOCOL_TEST(where.value() == "alpha");
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 4);
    TRIAL_PROTOCOL_TEST(where.key() == 4);
    TRIAL_PROTOCOL_TEST(where.value() == L"bravo");
    ++where;
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 5);
    TRIAL_PROTOCOL_TEST(where.key() == 5);
    TRIAL_PROTOCOL_TEST(where.value() == u"charlie");
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
    iterate_wstring();
    iterate_u16string();
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
    // null - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - boolean
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - integer
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - number
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - string
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
    // null - wstring
    {
        variable::iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - u16string
    {
        variable::iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - array
    {
        variable::iterator where = data.find(array::make());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // null - map
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
    // boolean - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - boolean
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
    // boolean - integer
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - number
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - string
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
    // boolean - wstring
    {
        variable::iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u16string
    {
        variable::iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - array
    {
        variable::iterator where = data.find(array::make({true}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - map
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
    // boolean - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - boolean
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
    // boolean - integer
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - number
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - string
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
    // boolean - wstring
    {
        variable::const_iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - u16string
    {
        variable::const_iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - array
    {
        variable::const_iterator where = data.find(array::make({true}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // boolean - map
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
    // integer - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - boolean
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - integer
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
    // integer - number
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - string
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
    // integer - wstring
    {
        variable::iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u16string
    {
        variable::iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - array
    {
        variable::iterator where = data.find(array::make({2}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - map
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
    // integer - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - boolean
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - integer
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
    // integer - number
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - string
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
    // integer - wstring
    {
        variable::const_iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - u16string
    {
        variable::const_iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - array
    {
        variable::const_iterator where = data.find(array::make({2}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // integer - map
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
    // number - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - boolean
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - integer
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - number
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
    // number - string
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
    // number - wstring
    {
        variable::iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - u16string
    {
        variable::iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - array
    {
        variable::iterator where = data.find(array::make({3.0}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - map
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
    // number - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - boolean
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - integer
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - number
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
    // number - string
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
    // number - wstring
    {
        variable::const_iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - u16string
    {
        variable::const_iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - array
    {
        variable::const_iterator where = data.find(array::make({3.0}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // number - map
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
    // string - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - boolean
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - integer
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - number
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - string
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
    // string - wstring
    {
        variable::iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u16string
    {
        variable::iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - map
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
    // string - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - boolean
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - integer
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - number
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - string
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
    // string - wstring
    {
        variable::const_iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - u16string
    {
        variable::const_iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - array
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // string - map
    {
        variable::const_iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_wstring()
{
    variable data(L"hydrogen");
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // wstring - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - boolean
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - integer
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - number
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - string
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
    // wstring - wstring
    {
        variable::iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(L"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(variable(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - u16string
    {
        variable::iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - map
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_wstring()
{
    const variable data(L"hydrogen");
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // wstring - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - boolean
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - integer
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - number
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - string
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
    // wstring - wstring
    {
        variable::const_iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(L"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(std::wstring(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(variable(L"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - u16string
    {
        variable::const_iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - array
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // wstring - map
    {
        variable::const_iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_u16string()
{
    variable data(u"hydrogen");
    {
        variable::iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // u16string - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - boolean
    {
        variable::iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - integer
    {
        variable::iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - number
    {
        variable::iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - string
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
    // u16string - wstring
    {
        variable::iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - u16string
    {
        variable::iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(u"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(std::u16string(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::iterator where = data.find(variable(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - map
    {
        variable::iterator where = data.find(map::make("alpha", "hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void find_const_u16string()
{
    const variable data(L"hydrogen");
    {
        variable::const_iterator where = data.find(data);
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    // u16string - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - boolean
    {
        variable::const_iterator where = data.find(true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(true));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - integer
    {
        variable::const_iterator where = data.find(2);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(2));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - number
    {
        variable::const_iterator where = data.find(3.0);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(3.0));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - string
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
    // u16string - wstring
    {
        variable::const_iterator where = data.find(L"hydrogen");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::wstring(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(L"hydrogen"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - u16string
    {
        variable::const_iterator where = data.find(u"hydrogen");
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(u"alpha");
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(std::u16string(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(std::u16string(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::const_iterator where = data.find(variable(u"hydrogen"));
        TRIAL_PROTOCOL_TEST(where != data.end());
    }
    {
        variable::const_iterator where = data.find(variable(u"alpha"));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - array
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // u16string - map
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
    // array - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
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
    // array - integer
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
    // array - number
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
    // array - string
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
    // array - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
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
    // array - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
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
    // array - integer
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
    // array - number
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
    // array - string
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
    // array - array
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
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
    // array - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
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
    // array - integer
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
    // array - number
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
    // array - string
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
    // array - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    // array - map
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
    // array - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // array - boolean
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
    // array - integer
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
    // array - number
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
    // array - string
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
    // array - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // array - map
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
    // map - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
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
    // map - integer
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
    // map - number
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
    // map - string
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
    // map - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
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
    // map - null
    {
        variable::const_iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::const_iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
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
    // map - integer
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
    // map - number
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
    // map - string
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
    // map - array
    {
        variable::const_iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
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
    // map - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
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
    // map - integer
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
    // map - number
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
    // map - string
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
    // map - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 5);
    }
    // map - map
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
    // map - null
    {
        variable::iterator where = data.find(null);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    {
        variable::iterator where = data.find(variable());
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 0);
    }
    // map - boolean
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
    // map - integer
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
    // map - number
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
    // map - string
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
    // map - array
    {
        variable::iterator where = data.find(array::make({"hydrogen"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable::iterator where = data.find(array::make({"helium"}));
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    // map - map
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

    return boost::report_errors();
}
