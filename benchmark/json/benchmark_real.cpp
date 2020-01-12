///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <benchmark/benchmark.h>
#include <trial/protocol/buffer/string.hpp>
#include <trial/protocol/json/reader.hpp>

namespace json = trial::protocol::json;

//-----------------------------------------------------------------------------

template <std::size_t N>
void value_double(benchmark::State& state)
{
    std::string input(N, '7');
    input += ".0";
    json::reader reader(input);
    double result;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(result = reader.value<double>());
    }
}

BENCHMARK_TEMPLATE(value_double, 1);
BENCHMARK_TEMPLATE(value_double, 2);
BENCHMARK_TEMPLATE(value_double, 3);
BENCHMARK_TEMPLATE(value_double, 4);
BENCHMARK_TEMPLATE(value_double, 5);
BENCHMARK_TEMPLATE(value_double, 6);
BENCHMARK_TEMPLATE(value_double, 7);
BENCHMARK_TEMPLATE(value_double, 8);
BENCHMARK_TEMPLATE(value_double, 9);
BENCHMARK_TEMPLATE(value_double, 10);
BENCHMARK_TEMPLATE(value_double, 11);
BENCHMARK_TEMPLATE(value_double, 12);
BENCHMARK_TEMPLATE(value_double, 13);
BENCHMARK_TEMPLATE(value_double, 14);
BENCHMARK_TEMPLATE(value_double, 15);
BENCHMARK_TEMPLATE(value_double, 16);
BENCHMARK_TEMPLATE(value_double, 17);
BENCHMARK_TEMPLATE(value_double, 18);
BENCHMARK_TEMPLATE(value_double, 19);
BENCHMARK_TEMPLATE(value_double, 20);
BENCHMARK_TEMPLATE(value_double, 20);
BENCHMARK_TEMPLATE(value_double, 21);
BENCHMARK_TEMPLATE(value_double, 22);
BENCHMARK_TEMPLATE(value_double, 23);
BENCHMARK_TEMPLATE(value_double, 24);
BENCHMARK_TEMPLATE(value_double, 25);
BENCHMARK_TEMPLATE(value_double, 26);
BENCHMARK_TEMPLATE(value_double, 27);
BENCHMARK_TEMPLATE(value_double, 28);
BENCHMARK_TEMPLATE(value_double, 30);
BENCHMARK_TEMPLATE(value_double, 31);
BENCHMARK_TEMPLATE(value_double, 32);

BENCHMARK_MAIN();
