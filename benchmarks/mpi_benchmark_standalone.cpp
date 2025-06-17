#include "BaseCase.h"
#include "Parallel.h"
#include <chrono>
#include <iostream>
#include <mpi.h>
#include <vector>

using FlatMatrix = std::vector<int>;

void benchmarkMPIMultiplier() {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    std::cout << "🚀 MPI Matrix Multiplication Benchmark 🚀\n";
    std::cout << "Number of MPI processes: " << size << std::endl;
    std::cout << "==========================================\n";
  }

  // Test different matrix sizes
  std::vector<size_t> matrix_sizes = {512, 1024, 2048, 4096};
  const size_t block_size = 16; // Fixed block size

  for (size_t n : matrix_sizes) {
    if (rank == 0) {
      std::cout << "\nMatrix Size: " << n << "x" << n
                << ", Block Size: " << block_size << std::endl;
    }

    // Create test matrices
    FlatMatrix A = create_random_flat_matrix(n, 42);
    FlatMatrix B = create_random_flat_matrix(n, 41);

    // Warm up run
    ParallelBlockingMPIRows(A, B, n, block_size);

    // Benchmark runs
    const int num_runs = 3;
    double total_time = 0.0;

    for (int run = 0; run < num_runs; ++run) {
      auto start_time = std::chrono::high_resolution_clock::now();
      FlatMatrix C = ParallelBlockingMPIRows(A, B, n, block_size);
      auto end_time = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
          end_time - start_time);
      total_time += duration.count();

      if (rank == 0 && run == 0) {
        // Verify result is not empty
        bool hasNonZero = false;
        for (size_t i = 0; i < std::min(C.size(), size_t(100)); ++i) {
          if (C[i] != 0) {
            hasNonZero = true;
            break;
          }
        }
        if (!hasNonZero) {
          std::cout << "  ⚠️  Warning: Result appears to be all zeros"
                    << std::endl;
        }
      }
    }

    if (rank == 0) {
      double avg_time = total_time / num_runs;
      double gflops = (2.0 * n * n * n) / (avg_time * 1000.0); // GFLOPS

      std::cout << "  Average time: " << avg_time / 1000.0 << " ms"
                << std::endl;
      std::cout << "  Performance: " << gflops << " GFLOPS" << std::endl;
    }
  }

  if (rank == 0) {
    std::cout << "\n🎯 Benchmark completed!" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  try {
    benchmarkMPIMultiplier();
  } catch (const std::exception &e) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  MPI_Finalize();
  return 0;
}
