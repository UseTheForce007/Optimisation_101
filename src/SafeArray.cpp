#include "SafeArray.h"
#include <cstddef>

template <typename T, unsigned int N>
void ArrayMulTemplate(const SafeArray<T, N> &matrixA,
                      const SafeArray<T, N> &matrixB, SafeArray<T, N> &result,
                      size_t dimension) {
  for (size_t i = 0; i < dimension; ++i) {
    for (size_t j = 0; j < dimension; ++j) {
      for (size_t k = 0; k < dimension; ++k) {
        result[i * dimension + j] +=
            matrixA[i * dimension + k] * matrixB[k * dimension + j];
      }
    }
  }
}

// Explicit template instantiation
template void ArrayMulTemplate<int, 64>(const SafeArray<int, 64> &,
                                        const SafeArray<int, 64> &,
                                        SafeArray<int, 64> &, size_t);
template void ArrayMulTemplate<int, 256>(const SafeArray<int, 256> &,
                                         const SafeArray<int, 256> &,
                                         SafeArray<int, 256> &, size_t);

template void ArrayMulTemplate<int, 1024>(const SafeArray<int, 1024> &,
                                          const SafeArray<int, 1024> &,
                                          SafeArray<int, 1024> &, size_t);