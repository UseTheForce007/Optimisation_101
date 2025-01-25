#include "SafeArray.h"
#include <benchmark/benchmark.h>
#include <random>

// Helper functions
template <typename T, unsigned int N> SafeArray<T, N> createRandomSafeArray() {
  std::random_device rd;
  std::mt19937 gen(42);
  std::uniform_int_distribution<> dis(1, 100);
  SafeArray<T, N> arr;
  for (unsigned int i = 0; i < N; ++i) {
    arr[i] = dis(gen);
  }
  return arr;
}

// Benchmark function using compile-time size
template <size_t N>
static void BM_SafeArrayMultiplication_Random(benchmark::State &state) {
  const unsigned int matrixDim = static_cast<unsigned int>(std::sqrt(N));
  SafeArray<int, N> matrixFirst = createRandomSafeArray<int, N>();
  SafeArray<int, N> matrixSecond = createRandomSafeArray<int, N>();
  SafeArray<int, N> resultMatrix;

  for (auto benchIter : state) {
    ArrayMulTemplate(matrixFirst, matrixSecond, resultMatrix, matrixDim);
    // benchmark::DoNotOptimize(resultMatrix);
  }
}

// Register benchmarks for different matrix sizes
BENCHMARK(BM_SafeArrayMultiplication_Random<64>);   // 8x8
BENCHMARK(BM_SafeArrayMultiplication_Random<256>);  // 16x16
BENCHMARK(BM_SafeArrayMultiplication_Random<1024>); // 32x32

// Remove BENCHMARK_MAIN() to avoid multiple definitions of main
BENCHMARK_MAIN();
