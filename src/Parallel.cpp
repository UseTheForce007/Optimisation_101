#include "Parallel.h"
#include <algorithm>
#include <immintrin.h> // AVX2 SIMD
#include <iostream>
#include <mpi.h>
#include <vector>

using FlatMatrix = std::vector<int>;

// 🚀 Function to multiply a BLOCK using AVX2 SIMD 🚀
void MultiplyBlock(const FlatMatrix &A, const FlatMatrix &B, FlatMatrix &C,
                   size_t n, size_t block_size, size_t i, size_t j) {
  for (size_t k = 0; k < n; k += block_size) {
    for (size_t ii = i; ii < std::min(i + block_size, n); ++ii) {
      for (size_t jj = j; jj < std::min(j + block_size, n); jj += 8) {
        // Load 8 integers from C
        __m256i c_vec = _mm256_loadu_si256(
            reinterpret_cast<const __m256i *>(&C[ii * n + jj]));

        for (size_t kk = k; kk < std::min(k + block_size, n); ++kk) {
          // Load 8 integers from B
          __m256i b_vec = _mm256_loadu_si256(
              reinterpret_cast<const __m256i *>(&B[kk * n + jj]));

          // Broadcast A[ii, kk] (single value) into all lanes
          __m256i a_val = _mm256_set1_epi32(A[ii * n + kk]);

          // Multiply A[ii, kk] * B[kk, jj:jj+7] using SIMD
          __m256i result = _mm256_mullo_epi32(a_val, b_vec);

          // Accumulate into C
          c_vec = _mm256_add_epi32(c_vec, result);
        }
        // Store the result back into C
        _mm256_storeu_si256(reinterpret_cast<__m256i *>(&C[ii * n + jj]),
                            c_vec);
      }
    }
  }
}

FlatMatrix ParallelBlockingMPIRows(const FlatMatrix &A, const FlatMatrix &B,
                                   size_t n, size_t block_size) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Calculate rows per process
  size_t rows_per_process = n / size;
  size_t start_row = rank * rows_per_process;
  size_t end_row = (rank == size - 1) ? n : start_row + rows_per_process;

  // Local result matrix (only for assigned rows)
  FlatMatrix local_C((end_row - start_row) * n, 0);

  // Process blocks within assigned row range
  for (size_t i = start_row; i < end_row; i += block_size) {
    for (size_t j = 0; j < n; j += block_size) {
      // Adjust block multiplication for local indexing
      for (size_t k = 0; k < n; k += block_size) {
        for (size_t ii = i; ii < std::min(i + block_size, end_row); ++ii) {
          for (size_t jj = j; jj < std::min(j + block_size, n); jj += 8) {
            size_t local_ii = ii - start_row;
            __m256i c_vec = _mm256_loadu_si256(
                reinterpret_cast<const __m256i *>(&local_C[local_ii * n + jj]));

            for (size_t kk = k; kk < std::min(k + block_size, n); ++kk) {
              __m256i b_vec = _mm256_loadu_si256(
                  reinterpret_cast<const __m256i *>(&B[kk * n + jj]));
              __m256i a_val = _mm256_set1_epi32(A[ii * n + kk]);
              __m256i result = _mm256_mullo_epi32(a_val, b_vec);
              c_vec = _mm256_add_epi32(c_vec, result);
            }
            _mm256_storeu_si256(
                reinterpret_cast<__m256i *>(&local_C[local_ii * n + jj]),
                c_vec);
          }
        }
      }
    }
  }

  // Gather all results at master process
  FlatMatrix C;
  if (rank == 0) {
    C.resize(n * n, 0);
    // Copy local result
    std::copy(local_C.begin(), local_C.end(), C.begin());

    // Receive from other processes
    for (int src = 1; src < size; ++src) {
      size_t src_start = src * rows_per_process;
      size_t src_rows = (src == size - 1) ? n - src_start : rows_per_process;
      MPI_Recv(C.data() + src_start * n, src_rows * n, MPI_INT, src, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  } else {
    MPI_Send(local_C.data(), (end_row - start_row) * n, MPI_INT, 0, 0,
             MPI_COMM_WORLD);
  }

  return C;
}
