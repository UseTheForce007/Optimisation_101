#include "BaseCase.h"
#include "MemoryAllocation.h"
#include <benchmark/benchmark.h>

// ...existing code...

static void BM_MultiplyFlatMem(benchmark::State &state) {
  size_t n = state.range(0);
  FlatMatrix A = create_random_flat_matrix(n, 42);
  FlatMatrix B = create_random_flat_matrix(n, 42);

  for (auto _ : state) {
    FlatMatrix C = multiply_flat_mem(A, B, n);
    // benchmark::DoNotOptimize(C);
  }
}

BENCHMARK(BM_MultiplyFlatMem)->RangeMultiplier(2)->Range(32, 1024);
