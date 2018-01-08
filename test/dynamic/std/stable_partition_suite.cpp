///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2017 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <trial/protocol/core/detail/lightweight_test.hpp>
#include <trial/dynamic/variable.hpp>
#include <trial/dynamic/functional.hpp>

using namespace trial::dynamic;

//-----------------------------------------------------------------------------
// std::stable_partition
//-----------------------------------------------------------------------------

void partition_null()
{
    variable data;
    auto where = std::stable_partition(data.begin(), data.end(), is<nullable>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<nullable>()), true);
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void partition_boolean()
{
    variable data(true);
    auto where = std::stable_partition(data.begin(), data.end(), is<boolean>());
    TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
    TRIAL_PROTOCOL_TEST(where == data.end());
}

void partition_integer()
{
    {
        variable data(2);
        auto where = std::stable_partition(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(2U);
        auto where = std::stable_partition(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void partition_real()
{
    {
        variable data(3.0f);
        auto where = std::stable_partition(data.begin(), data.end(), is<real>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<real>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(3.0);
        auto where = std::stable_partition(data.begin(), data.end(), is<real>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<real>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(3.0L);
        auto where = std::stable_partition(data.begin(), data.end(), is<real>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<real>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void partition_string()
{
    {
        variable data("alpha");
        auto where = std::stable_partition(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(L"bravo");
        auto where = std::stable_partition(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(u"charlie");
        auto where = std::stable_partition(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
    {
        variable data(U"delta");
        auto where = std::stable_partition(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
        TRIAL_PROTOCOL_TEST(where == data.end());
    }
}

void partition_array()
{
    variable data = { null, true, 2, 3.0, "alpha", L"bravo", u"charlie", U"delta" };
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<nullable>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<nullable>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == null);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == true);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == 2);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<real>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<real>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == 3.0);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == "alpha");
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<wstring>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<wstring>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == L"bravo");
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<u16string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u16string>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == u"charlie");
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<u32string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<u32string>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == U"delta");
    }
}

void partition_map_value()
{
    variable data =
        {
            { "alpha", null },
            { "bravo", true },
            { "charlie", 2 },
            { "delta", 3.0 },
            { "echo", "hydrogen" },
            { "foxtrot", L"helium" },
            { "golf", array::make({ 5 }) },
            { "hotel", map::make({ {"alice", 6} }) }
        };
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<nullable>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<nullable>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == null);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<boolean>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<boolean>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == true);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<integer>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<integer>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == 2);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<real>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<real>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == 3.0);
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<string>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<string>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(*data.begin() == "hydrogen");
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<array>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<array>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(data.begin()->is<array>());
        TRIAL_PROTOCOL_TEST(data.begin().key() == "alpha");
    }
    {
        auto where = std::stable_partition(data.begin(), data.end(), is<map>());
        TRIAL_PROTOCOL_TEST_EQUAL(std::is_partitioned(data.begin(), data.end(), is<map>()), true);
        TRIAL_PROTOCOL_TEST_EQUAL(std::distance(data.begin(), where), 1);
        TRIAL_PROTOCOL_TEST(data.begin()->is<map>());
        TRIAL_PROTOCOL_TEST(data.begin().key() == "alpha");
    }
}

int main()
{
    partition_null();
    partition_boolean();
    partition_integer();
    partition_real();
    partition_string();
    partition_array();
    partition_map_value();

    return boost::report_errors();
}
