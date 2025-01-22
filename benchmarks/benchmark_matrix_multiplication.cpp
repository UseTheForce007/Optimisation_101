#include "matrix_multiplication.h"
#include <benchmark/benchmark.h>

static void BM_MatrixMultiplication(benchmark::State &state) {
  size_t n = state.range(0);
  Matrix A(n, std::vector<int>(n, 1));
  Matrix B(n, std::vector<int>(n, 1));

  for (auto _ : state) {
    Matrix C = multiply(A, B);
    benchmark::DoNotOptimize(C);
  }
}

BENCHMARK(BM_MatrixMultiplication)->RangeMultiplier(2)->Range(8, 8 << 5);

static void BM_FlatMatrixMultiplication(benchmark::State &state) {
  size_t n = state.range(0);
  FlatMatrix A(n * n, 1);
  FlatMatrix B(n * n, 1);

  for (auto _ : state) {
    FlatMatrix C = multiply_flat(A, B, n);
    benchmark::DoNotOptimize(C);
  }
}

BENCHMARK(BM_FlatMatrixMultiplication)->RangeMultiplier(2)->Range(8, 8 << 5);

BENCHMARK_MAIN();
