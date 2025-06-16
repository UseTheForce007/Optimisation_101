#include "BaseCase.h"
#include "Parallel.h"
#include <benchmark/benchmark.h>

// Note: This benchmark should only be run in a single-process context
// For MPI benchmarks, use the standalone mpi_benchmark executable

// Benchmark for MPI Parallel Matrix Multiplication (single process mode)
static void BM_ParallelBlockingMPIRows_SingleProcess(benchmark::State &state) {
  size_t n = state.range(0);
  size_t block_size = 64; // Fixed block size for consistency

  FlatMatrix A = create_random_flat_matrix(n, 42);
  FlatMatrix B = create_random_flat_matrix(n, 41);

  for (auto _ : state) {
    // This will run with only one MPI process (rank 0)
    FlatMatrix C = ParallelBlockingMPIRows(A, B, n, block_size);
    benchmark::DoNotOptimize(C);
  }

  // Set custom counters for better analysis
  state.counters["MatrixSize"] = n;
  state.counters["BlockSize"] = block_size;
  state.counters["Operations"] =
      benchmark::Counter(2.0 * n * n * n, benchmark::Counter::kIsRate);
}

// Register benchmark - smaller sizes since this runs in single process mode
BENCHMARK(BM_ParallelBlockingMPIRows_SingleProcess)
    ->RangeMultiplier(2)
    ->Range(32, 256)
    ->Unit(benchmark::kMillisecond)
    ->UseRealTime();
