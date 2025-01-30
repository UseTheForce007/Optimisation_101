#include "SIMD.h"

FlatMatrix SIMD(const FlatMatrix &A, const FlatMatrix &B, size_t n,
                size_t block_size) {
  FlatMatrix C(n * n, 0);
  for (size_t i = 0; i < n; i += block_size) {
    for (size_t j = 0; j < n; j += block_size) {
      for (size_t k = 0; k < n; k += block_size) {
        for (size_t ii = i; ii < i + block_size; ii++) {
          for (size_t jj = j; jj < j + block_size; jj += 8) {
            __m256i c_vec = _mm256_loadu_si256(
                (__m256i *)&C[ii * n + jj]); // Unaligned load
            for (size_t kk = k; kk < k + block_size; kk++) {
              __m256i a_vec =
                  _mm256_set1_epi32(A[ii * n + kk]); // Broadcast A[ii][kk]
              __m256i b_vec = _mm256_loadu_si256(
                  (__m256i *)&B[kk * n + jj]); // Unaligned load

              __m256i mul_vec = _mm256_mullo_epi32(a_vec, b_vec);
              c_vec = _mm256_add_epi32(c_vec, mul_vec); // Accumulate into c_vec
            }
            _mm256_storeu_si256((__m256i *)&C[ii * n + jj],
                                c_vec); // Unaligned store
          }
        }
      }
    }
  }
  return C;
}