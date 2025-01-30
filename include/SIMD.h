#ifndef SIMD_H
#define SIMD_H

#include <cstddef>
#include <immintrin.h>
#include <vector>

using FlatMatrix = std::vector<int>;

FlatMatrix SIMD(const FlatMatrix &A, const FlatMatrix &B, size_t n,
                size_t block_size = 16);

#endif // SIMD_H