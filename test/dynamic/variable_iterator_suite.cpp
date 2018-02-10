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
#include <trial/dynamic/variable.hpp>

using namespace trial::dynamic;

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

void bidirectional_iterator_decrementable()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    ++a;
    variable::iterator& b = --a;
    TRIAL_PROTOCOL_TEST(b == a);
    TRIAL_PROTOCOL_TEST(b == data.begin());
}

void bidirectional_iterator_post_decrementable()
{
    variable data = array::make({ true, 2, 3.0, "alpha" });
    variable::iterator a = data.begin();
    ++a;
    variable::iterator b = a--;
    TRIAL_PROTOCOL_TEST(a == data.begin());
    TRIAL_PROTOCOL_TEST(b != data.begin());
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

    // [bidirectional.iterators]
    bidirectional_iterator_decrementable();
    bidirectional_iterator_post_decrementable();
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

void test_real()
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
        variable data(u"charlie");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(u"charlie");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
}

void test_u32string()
{
    {
        variable data(U"delta");
        TRIAL_PROTOCOL_TEST(data.begin() != data.end());
        TRIAL_PROTOCOL_TEST(data.cbegin() != data.cend());
    }
    {
        const variable data(U"delta");
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
    test_real();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
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

void test_real()
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
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data("alpha");
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
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
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(L"bravo");
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_u16string()
{
    {
        variable data(u"charlie");
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(u"charlie");
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_u32string()
{
    {
        variable data(U"delta");
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data(U"delta");
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_array()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"delta"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"delta"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_array_real()
{
    {
        variable data = array::make({ 1.0f, 2.0, 3.0L });
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where->same<float>());
        TRIAL_PROTOCOL_TEST(*where == 1.0f);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == 2.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<long double>());
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = array::make({ 1.0f, 2.0, 3.0L });
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where->same<float>());
        TRIAL_PROTOCOL_TEST(*where == 1.0f);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == 2.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<long double>());
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
                {"foxtrot", u"lithium"},
                {"golf", U"beryllium"}
            });
        variable::iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"beryllium"));
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
                {"foxtrot", u"lithium"},
                {"golf", U"beryllium"}
            });
        variable::const_iterator where = data.begin();
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"beryllium"));
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_real();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_array_real();
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

void test_real()
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
    TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(result != data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_wstring()
{
    variable data(L"bravo");
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(result != data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_u16string()
{
    variable data(u"charlie");
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(result != data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_u32string()
{
    variable data(U"delta");
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(result != data.end());
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void test_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where->same<bool>());
    TRIAL_PROTOCOL_TEST(*where == variable(true));
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(true));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<int>());
    TRIAL_PROTOCOL_TEST(*where == variable(2));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(2));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<double>());
    TRIAL_PROTOCOL_TEST(*where == variable(3.0));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(3.0));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable("alpha"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(L"bravo"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(u"charlie"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(U"delta"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(U"delta"));
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
            {"foxtrot", u"lithium"},
            {"golf", U"beryllium"}
        });
    variable::iterator where = data.begin();
    TRIAL_PROTOCOL_TEST(where->same<bool>());
    TRIAL_PROTOCOL_TEST(*where == variable(true));
    variable::iterator result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(true));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<int>());
    TRIAL_PROTOCOL_TEST(*where == variable(2));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(2));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<double>());
    TRIAL_PROTOCOL_TEST(*where == variable(3.0));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(3.0));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable("hydrogen"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(L"helium"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(u"lithium"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(U"beryllium"));
    result = where++;
    TRIAL_PROTOCOL_TEST(*result == variable(U"beryllium"));
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_real();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_map();
}

} // namespace post_increment_suite

//-----------------------------------------------------------------------------
// operator--()
//-----------------------------------------------------------------------------

namespace pre_decrement_suite
{

void test_null()
{
    {
        variable data;
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data;
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void test_boolean()
{
    {
        variable data(true);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    }
    {
        const variable data(true);
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    }
}

void test_integer()
{
    {
        variable data(2);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    }
    {
        const variable data(2);
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
    }
}

void test_real()
{
    {
        variable data(3.0f);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0f);
    }
    {
        const variable data(3.0f);
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0f);
    }
    {
        variable data(3.0);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
    }
    {
        const variable data(3.0);
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
    }
    {
        variable data(3.0L);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
    }
    {
        const variable data(3.0L);
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
    }
}

void test_string()
{
    {
        variable data("alpha");
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    }
    {
        const variable data("alpha");
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    }
}

void test_wstring()
{
    {
        variable data(L"bravo");
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    }
    {
        const variable data(L"bravo");
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    }
}

void test_u16string()
{
    {
        variable data(u"charlie");
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    }
    {
        const variable data(u"charlie");
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    }
}

void test_u32string()
{
    {
        variable data(U"delta");
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    }
    {
        const variable data(U"delta");
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    }
}

void test_array()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"delta"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
    }
    {
        const variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"delta"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
    }
}

void test_array_real()
{
    {
        variable data = array::make({ 1.0f, 2.0, 3.0L });
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<long double>());
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == 2.0);
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<float>());
        TRIAL_PROTOCOL_TEST(*where == 1.0f);
    }
    {
        const variable data = array::make({ 1.0f, 2.0, 3.0L });
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<long double>());
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == 2.0);
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<float>());
        TRIAL_PROTOCOL_TEST(*where == 1.0f);
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
                {"foxtrot", u"lithium"},
                {"golf", U"beryllium"}
            });
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"beryllium"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
    }
    {
        const variable data = map::make(
            {
                {"alpha", true},
                {"bravo", 2},
                {"charlie", 3.0},
                {"delta", "hydrogen"},
                {"echo", L"helium"},
                {"foxtrot", u"lithium"},
                {"golf", U"beryllium"}
            });
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(U"beryllium"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
        TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
        TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<double>());
        TRIAL_PROTOCOL_TEST(*where == variable(3.0));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<int>());
        TRIAL_PROTOCOL_TEST(*where == variable(2));
        --where;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->same<bool>());
        TRIAL_PROTOCOL_TEST(*where == variable(true));
    }
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_real();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_array_real();
    test_map();
}

} // namespace pre_decrement_suite

//-----------------------------------------------------------------------------
// operator--(int)
//-----------------------------------------------------------------------------

namespace post_decrement_suite
{

void test_null()
{
    {
        variable data;
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::iterator result = where--;
        TRIAL_PROTOCOL_TEST(where == data.end());
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
    {
        const variable data;
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::const_iterator result = where--;
        TRIAL_PROTOCOL_TEST(where == data.end());
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
}

void test_boolean()
{
    {
        variable data(true);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::iterator result = where--;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
    {
        const variable data(true);
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::const_iterator result = where--;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
}

void test_integer()
{
    {
        variable data(2);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::iterator result = where--;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
    {
        const variable data(2);
        variable::const_iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::const_iterator result = where--;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
}

void test_real()
{
    {
        variable data(3.0f);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::iterator result = where--;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0f);
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
    {
        variable data(3.0);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::iterator result = where--;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
    {
        variable data(3.0L);
        variable::iterator where = data.end();
        TRIAL_PROTOCOL_TEST(where == data.end());
        variable::iterator result = where--;
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST_EQUAL(where->size(), 1);
        TRIAL_PROTOCOL_TEST(*where == 3.0L);
        TRIAL_PROTOCOL_TEST(result == data.end());
    }
}

void test_string()
{
    variable data("alpha");
    variable::iterator where = data.end();
    TRIAL_PROTOCOL_TEST(where == data.end());
    variable::iterator result = where--;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    TRIAL_PROTOCOL_TEST(result == data.end());
}

void test_wstring()
{
    variable data(L"bravo");
    variable::iterator where = data.end();
    TRIAL_PROTOCOL_TEST(where == data.end());
    variable::iterator result = where--;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    TRIAL_PROTOCOL_TEST(result == data.end());
}

void test_u16string()
{
    variable data(u"charlie");
    variable::iterator where = data.end();
    TRIAL_PROTOCOL_TEST(where == data.end());
    variable::iterator result = where--;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    TRIAL_PROTOCOL_TEST(result == data.end());
}

void test_u32string()
{
    variable data(U"delta");
    variable::iterator where = data.end();
    TRIAL_PROTOCOL_TEST(where == data.end());
    variable::iterator result = where--;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    TRIAL_PROTOCOL_TEST(result == data.end());
}

void test_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    variable::iterator where = data.end();
    TRIAL_PROTOCOL_TEST(where == data.end());
    variable::iterator result = where--;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(U"delta"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(U"delta"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(u"charlie"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(u"charlie"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(L"bravo"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(L"bravo"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable("alpha"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable("alpha"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<double>());
    TRIAL_PROTOCOL_TEST(*where == variable(3.0));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(3.0));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<int>());
    TRIAL_PROTOCOL_TEST(*where == variable(2));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(2));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<bool>());
    TRIAL_PROTOCOL_TEST(*where == variable(true));
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
            {"foxtrot", u"lithium"},
            {"golf", U"beryllium"}
        });
    variable::iterator where = data.end();
    TRIAL_PROTOCOL_TEST(where == data.end());
    variable::iterator result = where--;
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u32string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(U"beryllium"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(U"beryllium"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::u16string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(u"lithium"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(u"lithium"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::wstring_type>());
    TRIAL_PROTOCOL_TEST(*where == variable(L"helium"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(L"helium"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<variable::string_type>());
    TRIAL_PROTOCOL_TEST(*where == variable("hydrogen"));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable("hydrogen"));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<double>());
    TRIAL_PROTOCOL_TEST(*where == variable(3.0));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(3.0));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<int>());
    TRIAL_PROTOCOL_TEST(*where == variable(2));
    result = where--;
    TRIAL_PROTOCOL_TEST(*result == variable(2));
    TRIAL_PROTOCOL_TEST(where != data.end());
    TRIAL_PROTOCOL_TEST(where->same<bool>());
    TRIAL_PROTOCOL_TEST(*where == variable(true));
}

void run()
{
    test_null();
    test_boolean();
    test_integer();
    test_real();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
    test_array();
    test_map();
}

} // namespace post_decrement_suite

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

void get_real()
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
        variable data(L"bravo");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
    }
    {
        const variable data(L"bravo");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
    }
}

void get_u16string()
{
    {
        variable data(u"charlie");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
    }
    {
        const variable data(u"charlie");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
    }
}

void get_u32string()
{
    {
        variable data(U"delta");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == U"delta");
    }
    {
        const variable data(U"delta");
        auto where = data.begin();
        TRIAL_PROTOCOL_TEST(*where == U"delta");
    }
}

void get_array()
{
    {
        variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(where.value() == U"delta");
        TRIAL_PROTOCOL_TEST(*where == U"delta");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        const variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(where.value() == U"delta");
        TRIAL_PROTOCOL_TEST(*where == U"delta");
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
                {"foxtrot", u"lithium"},
                {"golf", U"beryllium"}
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(where.key() == "golf");
        TRIAL_PROTOCOL_TEST(where.value() == U"beryllium");
        TRIAL_PROTOCOL_TEST(*where == U"beryllium");
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
                {"foxtrot", u"lithium"},
                {"golf", U"beryllium"}
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
        TRIAL_PROTOCOL_TEST(where != data.end());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(where.key() == "golf");
        TRIAL_PROTOCOL_TEST(where.value() == U"beryllium");
        TRIAL_PROTOCOL_TEST(*where == U"beryllium");
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

void overwrite_real()
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
    variable data(u"charlie");
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_u32string()
{
    variable data(U"delta");
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST(data == null);
}

void overwrite_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    auto where = data.begin();
    *where = null;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 7);
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
            {"foxtrot", L"helium"},
            {"golf", u"lithium"},
            {"hotel", U"beryllium"}
        });
    auto where = data.begin();
    *where = 42;
    TRIAL_PROTOCOL_TEST_EQUAL(data.size(), 8);
    TRIAL_PROTOCOL_TEST(data["alpha"] == 42);
}

void run()
{
    get_null();
    get_boolean();
    get_integer();
    get_real();
    get_string();
    get_wstring();
    get_u16string();
    get_u32string();
    get_array();
    get_map();

    overwrite_boolean();
    overwrite_integer();
    overwrite_real();
    overwrite_string();
    overwrite_wstring();
    overwrite_u16string();
    overwrite_u32string();
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

void test_real()
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

void test_u32string()
{
    variable data(U"delta");
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 1);
}

void test_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), data.end()), 7);
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
    test_real();
    test_string();
    test_wstring();
    test_u16string();
    test_u32string();
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

void sum_real()
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
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void sum_wstring()
{
    variable data(L"bravo");
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void sum_u16string()
{
    variable data(u"charlie");
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void sum_u32string()
{
    variable data(U"delta");
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 1);
}

void sum_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
    variable::size_type size = 0;
    for (const auto& value : data)
    {
        size += value.size();
    }
    TRIAL_PROTOCOL_TEST_EQUAL(size, 7);
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
    TRIAL_PROTOCOL_TEST_EQUAL(size, 3);
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
    sum_real();
    sum_string();
    sum_wstring();
    sum_u16string();
    sum_u32string();
    sum_array();
    sum_array_nulls();
    sum_array_array();
    sum_map();
    sum_map_array();
    sum_map_map();
}

} // namespace range_for_suite

//-----------------------------------------------------------------------------
// reverse_iterator
//-----------------------------------------------------------------------------

namespace reverse_iterator_suite
{

void iterate_null()
{
    {
        variable data;
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data;
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data;
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where == data.crend());
    }
}

void iterate_boolean()
{
    {
        variable data(true);
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data(true);
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data(true);
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_integer()
{
    {
        variable data(2);
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data(2);
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data(2);
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_real()
{
    {
        variable data(3.0);
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data(3.0);
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data(3.0);
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_string()
{
    {
        variable data("alpha");
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data("alpha");
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data("alpha");
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_wstring()
{
    {
        variable data(L"bravo");
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data(L"bravo");
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data(L"bravo");
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_u16string()
{
    {
        variable data(u"charlie");
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data(u"charlie");
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data(u"charlie");
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_u32string()
{
    {
        variable data(U"delta");
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"delta");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data(U"delta");
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"delta");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data(U"delta");
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"delta");
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_array()
{
    {
        variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"delta");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<nullable>());
        TRIAL_PROTOCOL_TEST(*where == null);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"delta");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<nullable>());
        TRIAL_PROTOCOL_TEST(*where == null);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data = array::make({ null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"delta");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"charlie");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"bravo");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "alpha");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<nullable>());
        TRIAL_PROTOCOL_TEST(*where == null);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void iterate_map()
{
    {
        variable data = map::make(
            {
                {"alpha", null},
                {"bravo", true},
                {"charlie", 2},
                {"delta", 3.0},
                {"echo", "hydrogen"},
                {"foxtrot", L"helium"},
                {"golf", u"lithium"},
                {"hotel", U"beryllium"}
            });
        variable::reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"beryllium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"lithium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"helium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "hydrogen");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<nullable>());
        TRIAL_PROTOCOL_TEST(*where == null);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        const variable data = map::make(
            {
                {"alpha", null},
                {"bravo", true},
                {"charlie", 2},
                {"delta", 3.0},
                {"echo", "hydrogen"},
                {"foxtrot", L"helium"},
                {"golf", u"lithium"},
                {"hotel", U"beryllium"}
            });
        variable::const_reverse_iterator where = data.rbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"beryllium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"lithium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"helium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "hydrogen");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<nullable>());
        TRIAL_PROTOCOL_TEST(*where == null);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
    {
        variable data = map::make(
            {
                {"alpha", null},
                {"bravo", true},
                {"charlie", 2},
                {"delta", 3.0},
                {"echo", "hydrogen"},
                {"foxtrot", L"helium"},
                {"golf", u"lithium"},
                {"hotel", U"beryllium"}
            });
        variable::const_reverse_iterator where = data.crbegin();
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u32string>());
        TRIAL_PROTOCOL_TEST(*where == U"beryllium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<u16string>());
        TRIAL_PROTOCOL_TEST(*where == u"lithium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<wstring>());
        TRIAL_PROTOCOL_TEST(*where == L"helium");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<string>());
        TRIAL_PROTOCOL_TEST(*where == "hydrogen");
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<real>());
        TRIAL_PROTOCOL_TEST(*where == 3.0);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<integer>());
        TRIAL_PROTOCOL_TEST(*where == 2);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<boolean>());
        TRIAL_PROTOCOL_TEST(*where == true);
        ++where;
        TRIAL_PROTOCOL_TEST(where != data.rend());
        TRIAL_PROTOCOL_TEST(where->is<nullable>());
        TRIAL_PROTOCOL_TEST(*where == null);
        ++where;
        TRIAL_PROTOCOL_TEST(where == data.rend());
    }
}

void run()
{
    iterate_null();
    iterate_boolean();
    iterate_integer();
    iterate_real();
    iterate_string();
    iterate_wstring();
    iterate_u16string();
    iterate_u32string();
    iterate_array();
    iterate_map();
}

} // namespace reverse_iterator_suite

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

void iterate_real()
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

void iterate_u32string()
{
    variable data(U"delta");
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 0);
    ++where;
    TRIAL_PROTOCOL_TEST(where == data.key_end());
}

void iterate_array()
{
    variable data = array::make({ true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" });
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
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == 6);
    TRIAL_PROTOCOL_TEST(where.key() == 6);
    TRIAL_PROTOCOL_TEST(where.value() == U"delta");
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

void erase_base()
{
    variable data = map::make(
        {
            {"key", "alpha"}
        });
    auto where = data.key_begin();
    TRIAL_PROTOCOL_TEST(where != data.key_end());
    TRIAL_PROTOCOL_TEST(*where == "key");
    auto it = data.erase(where.base());
    TRIAL_PROTOCOL_TEST(it == data.end());
}

void run()
{
    iterate_null();
    iterate_boolean();
    iterate_integer();
    iterate_real();
    iterate_string();
    iterate_wstring();
    iterate_u16string();
    iterate_u32string();
    iterate_array();
    iterate_map();

    erase_base();
}

} // namespace key_iterator_suite

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
    pre_decrement_suite::run();
    post_decrement_suite::run();
    dereference_suite::run();
    distance_suite::run();
    range_for_suite::run();
    reverse_iterator_suite::run();
    key_iterator_suite::run();

    return boost::report_errors();
}
