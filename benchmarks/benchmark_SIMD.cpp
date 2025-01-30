#include "BaseCase.h"
#include "SIMD.h"
#include <benchmark/benchmark.h>

// Benchmark with SIMD
static void BM_SIMD(benchmark::State &state) {
  size_t n = state.range(0);
  FlatMatrix A = create_random_flat_matrix(n, 42);
  FlatMatrix B = create_random_flat_matrix(n, 41);
  for (auto _ : state) {
    FlatMatrix C = SIMD(A, B, n);
    // benchmark::DoNotOptimize(C);
  }
}

BENCHMARK(BM_SIMD)->RangeMultiplier(2)->Range(32, 1024)->Unit(
    benchmark::kMillisecond);
