#ifndef PARALLEL_H
#define PARALLEL_H

#include "BaseCase.h"

using FlatMatrix = std::vector<int>;
void MultiplyBlock(const FlatMatrix &A, const FlatMatrix &B, FlatMatrix &C,
                   size_t n, size_t block_size, size_t i, size_t j);

FlatMatrix ParallelBlockingMPIRows(const FlatMatrix &A, const FlatMatrix &B,
                                   size_t n, size_t block_size);
#endif // PARALLEL_H