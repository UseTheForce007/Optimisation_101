#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

#include <cstddef>
#include <vector>
using FlatMatrix = std::vector<int>;
FlatMatrix multiply_flat_mem(const FlatMatrix &A, const FlatMatrix &B,
                             size_t n);

#endif // MEMORY_ALLOCATION_H