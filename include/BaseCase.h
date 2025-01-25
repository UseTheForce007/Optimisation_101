#ifndef BASE_CASE_H
#define BASE_CASE_H

#include <cstddef>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
using FlatMatrix = std::vector<int>;

Matrix multiply(const Matrix &A, const Matrix &B);
FlatMatrix multiply_flat(const FlatMatrix &A, const FlatMatrix &B, size_t n);
FlatMatrix create_random_flat_matrix(size_t n, int seed);

#endif // BASE_CASE_H
