#include <benchmark/benchmark.h>
#include <memory>

#include <algorithm>
#include <random>
#include <time.h>

#define ARRAY_SIZE 256000

using namespace std;
struct A
{
    char array[256000] = {};
};

struct B
{
    char array[256000] = {};
};

A copy_a(const B& b)
{
    A ret;
    std::copy(begin(b.array), end(b.array), begin(ret.array));
    return ret;
}

void copy_b(const B& b, A& a)
{
    std::copy(begin(b.array), end(b.array), begin(a.array));
}

void copy_c(A& a, const B& b)
{
    std::copy(begin(b.array), end(b.array), begin(a.array));
}

void copy_d(A& __restrict__ a, const B& __restrict__ b)
{
    std::copy(begin(b.array), end(b.array), begin(a.array));
}

auto p_i = std::make_shared<int>(1);



static void bm_copy_a(benchmark::State& state)
{
    A a;
    B b;
    srand (time(NULL));
    // for (auto& v : b.array)
    // {
    //     v = static_cast<char>(rand() % 256);
    // }

    for (auto _ : state)
    {
        b.array[rand() % ARRAY_SIZE] = static_cast<char>(rand() % 256);
        a = copy_a(b);
    }

    volatile char c = a.array[rand() % ARRAY_SIZE];
}

static void bm_copy_b(benchmark::State& state)
{
    A a;
    B b;
    srand (time(NULL));
    for (auto& v : b.array)
    {
        v = static_cast<char>(rand() % 256);
    }

    for (auto _ : state)
    {
        copy_b(b, a);
    }
    volatile char c = a.array[rand() % ARRAY_SIZE];
}

static void bm_copy_c(benchmark::State& state)
{
    A a;
    B b;
    srand (time(NULL));
    for (auto& v : b.array)
    {
        v = static_cast<char>(rand() % 256);
    }

    for (auto _ : state)
    {
        copy_c(a, b);
    }
    volatile char c = a.array[rand() % ARRAY_SIZE];
}

static void bm_copy_d(benchmark::State& state)
{
    A a;
    B b;
    srand (time(NULL));
    for (auto& v : b.array)
    {
        v = static_cast<char>(rand() % 256);
    }
    
    for (auto _ : state)
    {
        copy_d(a, b);
    }
    volatile char c = a.array[rand() % ARRAY_SIZE];
}

// Register the function as a benchmark
BENCHMARK(bm_copy_a);
BENCHMARK(bm_copy_b);
BENCHMARK(bm_copy_c);
BENCHMARK(bm_copy_d);

// Run the benchmark
BENCHMARK_MAIN();