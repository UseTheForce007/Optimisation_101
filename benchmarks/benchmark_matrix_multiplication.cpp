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

BENCHMARK_MAIN();
