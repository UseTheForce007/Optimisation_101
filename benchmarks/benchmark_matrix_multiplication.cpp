#include "BaseCase.h"
#include <benchmark/benchmark.h>
#include <random>

// Helper functions
Matrix createRandomMatrix(size_t n) {
  std::random_device rd;
  std::mt19937 gen(42); // Fixed seed for reproducibility
  std::uniform_int_distribution<> dis(1, 100);
  Matrix mat(n, std::vector<int>(n));
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < n; ++j)
      mat[i][j] = dis(gen);
  return mat;
}

// Helper function to flatten a matrix
FlatMatrix flattenMatrix(const Matrix &mat) {
  size_t n = mat.size();
  FlatMatrix flat(n * n);
  for (size_t i = 0; i < n; ++i)
    for (size_t j = 0; j < n; ++j)
      flat[i * n + j] = mat[i][j];
  return flat;
}

// Benchmark with random values
static void BM_MatrixMultiplication_Random(benchmark::State &state) {
  size_t n = state.range(0);
  Matrix A = createRandomMatrix(n);
  Matrix B = createRandomMatrix(n);
  for (auto _ : state) {
    Matrix C = multiply(A, B);
  }
}

// Benchmark with flat matrices
static void BM_FlatMatrixMultiplication_Random(benchmark::State &state) {
  size_t n = state.range(0);
  FlatMatrix A = flattenMatrix(createRandomMatrix(n));
  FlatMatrix B = flattenMatrix(createRandomMatrix(n));
  for (auto _ : state) {
    FlatMatrix C = multiply_flat(A, B, n);
    // benchmark::DoNotOptimize(C);
  }
}

BENCHMARK(BM_MatrixMultiplication_Random)->RangeMultiplier(2)->Range(32, 1024);
BENCHMARK(BM_FlatMatrixMultiplication_Random)
    ->RangeMultiplier(2)
    ->Range(32, 1024);

BENCHMARK_MAIN();