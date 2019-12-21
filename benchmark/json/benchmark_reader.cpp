///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <array>
#include <benchmark/benchmark.h>
#include <trial/protocol/buffer/array.hpp>
#include <trial/protocol/json/reader.hpp>

namespace json = trial::protocol::json;

void parse_int16(benchmark::State& state)
{
    char input[] = "291";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int16_t>());
    }
}

void parse_int32(benchmark::State& state)
{
    char input[] = "19088743";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int32_t>());
    }
}

void parse_int64(benchmark::State& state)
{
    char input[] = "81985529216486895";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int64_t>());
    }
}

BENCHMARK(parse_int16);
BENCHMARK(parse_int32);
BENCHMARK(parse_int64);

void value_int16(benchmark::State& state)
{
    char input[] = "291";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int16_t>());
    }
}

void value_int32(benchmark::State& state)
{
    char input[] = "19088743";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int32_t>());
    }
}

void value_int64(benchmark::State& state)
{
    char input[] = "81985529216486895";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int64_t>());
    }
}

BENCHMARK(value_int16);
BENCHMARK(value_int32);
BENCHMARK(value_int64);

void parse_float(benchmark::State& state)
{
    char input[] = "291.192";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<float>());
    }
}

void parse_double(benchmark::State& state)
{
    char input[] = "291.192";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void parse_long_double(benchmark::State& state)
{
    char input[] = "291.192";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<long double>());
    }
}

BENCHMARK(parse_float);
BENCHMARK(parse_double);
BENCHMARK(parse_long_double);

void value_float(benchmark::State& state)
{
    char input[] = "291.192";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<float>());
    }
}

void value_double(benchmark::State& state)
{
    char input[] = "291.192";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<double>());
    }
}

void value_long_double(benchmark::State& state)
{
    char input[] = "291.192";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<long double>());
    }
}

BENCHMARK(value_float);
BENCHMARK(value_double);
BENCHMARK(value_long_double);

void parse_string8(benchmark::State& state)
{
    char input[] = "\"ABCDEFGH\"";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::string>());
    }
}

BENCHMARK(parse_string8);

void value_string8(benchmark::State& state)
{
    char input[] = "\"ABCDEFGH\"";
    json::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::string>());
    }
}

BENCHMARK(value_string8);

void parse_whitespaces(benchmark::State& state)
{
    char input[] = "                                                                                                                   291";
    for (auto _ : state)
    {
        json::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::uint16_t>());
    }
}

BENCHMARK(parse_whitespaces);

BENCHMARK_MAIN();
