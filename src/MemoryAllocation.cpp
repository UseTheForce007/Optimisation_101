#include "MemoryAllocation.h"
#include <algorithm>
#include <cstddef>
#include <vector>

#define BLOCK_SIZE 32

FlatMatrix multiply_flat_mem(const FlatMatrix &A, const FlatMatrix &B,
                             size_t n) {
  FlatMatrix C(n * n, 0);
  for (size_t i = 0; i < n; i += BLOCK_SIZE) {
    for (size_t j = 0; j < n; j += BLOCK_SIZE) {
      for (size_t k = 0; k < n; k += BLOCK_SIZE) {
        for (size_t ii = i; ii < std::min(i + BLOCK_SIZE, n); ++ii) {
          for (size_t jj = j; jj < std::min(j + BLOCK_SIZE, n); ++jj) {
            for (size_t kk = k; kk < std::min(k + BLOCK_SIZE, n); ++kk) {
              C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
            }
          }
        }
      }
    }
  }
  return C;
}