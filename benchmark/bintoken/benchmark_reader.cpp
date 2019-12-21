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
#include <trial/protocol/bintoken/reader.hpp>

namespace bintoken = trial::protocol::bintoken;

void parse_int16(benchmark::State& state)
{
    std::uint8_t input[] = { 0xB2, 0x23, 0x01 };
    for (auto _ : state)
    {
        bintoken::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int16_t>());
    }
}

void parse_int32(benchmark::State& state)
{
    std::uint8_t input[] = { 0xC4, 0x67, 0x45, 0x23, 0x01 };
    for (auto _ : state)
    {
        bintoken::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int32_t>());
    }
}

void parse_int64(benchmark::State& state)
{
    std::uint8_t input[] = { 0xD6, 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
    for (auto _ : state)
    {
        bintoken::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::int64_t>());
    }
}

BENCHMARK(parse_int16);
BENCHMARK(parse_int32);
BENCHMARK(parse_int64);

void value_int16(benchmark::State& state)
{
    std::uint8_t input[] = { 0xB2, 0x23, 0x01 };
    bintoken::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int16_t>());
    }
}

void value_int32(benchmark::State& state)
{
    std::uint8_t input[] = { 0xC4, 0x67, 0x45, 0x23, 0x01 };
    bintoken::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int32_t>());
    }
}

void value_int64(benchmark::State& state)
{
    std::uint8_t input[] = { 0xD6, 0xEF, 0xCD, 0xAB, 0x89, 0x67, 0x45, 0x23, 0x01 };
    bintoken::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::int64_t>());
    }
}

BENCHMARK(value_int16);
BENCHMARK(value_int32);
BENCHMARK(value_int64);

void parse_string8(benchmark::State& state)
{
    std::uint8_t input[] = { 0xA9, 0x08, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 };
    for (auto _ : state)
    {
        bintoken::reader reader(input);
        benchmark::DoNotOptimize(reader.value<std::string>());
    }
}

void value_string8(benchmark::State& state)
{
    std::uint8_t input[] = { 0xA9, 0x08, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 };
    bintoken::reader reader(input);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.value<std::string>());
    }
}

BENCHMARK(parse_string8);
BENCHMARK(value_string8);

void value_compact_array8(benchmark::State& state)
{
    std::uint8_t input[] = { 0xA8, 0x08, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 };
    bintoken::reader reader(input);
    std::array<std::int8_t, sizeof(input)> output;
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(reader.array<std::int8_t>(output.data(), output.size()));
    }
}

void parse_compact_array8(benchmark::State& state)
{
    std::uint8_t input[] = { 0xA8, 0x08, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 };
    std::array<std::int8_t, sizeof(input)> output;
    for (auto _ : state)
    {
        bintoken::reader reader(input);
        benchmark::DoNotOptimize(reader.array<std::int8_t>(output.data(), output.size()));
    }
}

BENCHMARK(parse_compact_array8);
BENCHMARK(value_compact_array8);

BENCHMARK_MAIN();
