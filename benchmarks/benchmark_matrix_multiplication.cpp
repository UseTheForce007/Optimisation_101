#include "BaseCase.h"
#include <benchmark/benchmark.h>
#include <random>

// Helper function to flatten a matrix
FlatMatrix flattenMatrix(const Matrix &mat) {
  size_t n = mat.size();
  FlatMatrix flat(n * n);
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < n; ++j)
      flat[i * n + j] = mat[i][j];
  return flat;
}

// Benchmark with flat matrices
static void BM_FlatMatrixMultiplication(benchmark::State &state) {
  size_t n = state.range(0);
  FlatMatrix A = create_random_flat_matrix(n, 42);
  FlatMatrix B = create_random_flat_matrix(n, 41);
  for (auto _ : state) {
    FlatMatrix C = multiply_flat(A, B, n);
    // benchmark::DoNotOptimize(C);
  }
}

BENCHMARK(BM_FlatMatrixMultiplication)
    ->RangeMultiplier(2)
    ->Range(512, 4096)
    ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();