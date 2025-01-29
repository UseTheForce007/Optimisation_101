#ifndef BLOCKING_H
#define BLOCKING_H

#include <cstddef>
#include <vector>
using FlatMatrix = std::vector<int>;
FlatMatrix Blocking(const FlatMatrix &A, const FlatMatrix &B, size_t n,
                    size_t block_size = 32);

#endif // BLOCKING_H