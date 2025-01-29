#include "Blocking.h"
#include <algorithm>
#include <cstddef>
#include <vector>

// #define BLOCK_SIZE 32

FlatMatrix Blocking(const FlatMatrix &A, const FlatMatrix &B, size_t n,
                    size_t block_size) {
  FlatMatrix C(n * n, 0);
  for (size_t i = 0; i < n; i += block_size) {
    for (size_t j = 0; j < n; j += block_size) {
      for (size_t k = 0; k < n; k += block_size) {
        for (size_t ii = i; ii < std::min(i + block_size, n); ++ii) {
          for (size_t jj = j; jj < std::min(j + block_size, n); ++jj) {
            for (size_t kk = k; kk < std::min(k + block_size, n); ++kk) {
              C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
            }
          }
        }
      }
    }
  }
  return C;
}