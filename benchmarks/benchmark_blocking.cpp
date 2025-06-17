#include "BaseCase.h"
#include "Blocking.h"
#include <benchmark/benchmark.h>

// ...existing code...

static void BM_MultiplyFlatBlock(benchmark::State &state) {
  size_t n = state.range(0);
  size_t block_size = state.range(1);
  FlatMatrix A = create_random_flat_matrix(n, 42);
  FlatMatrix B = create_random_flat_matrix(n, 41);

  for (auto _ : state) {
    FlatMatrix C = Blocking(A, B, n, block_size);
    // benchmark::DoNotOptimize(C);
  }
}

BENCHMARK(BM_MultiplyFlatBlock)
    ->ArgsProduct({{512, 1024, 2048, 4096}, {16, 32, 64}})
    ->Unit(benchmark::kMillisecond);
