#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <cstddef>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
using FlatMatrix = std::vector<int>;

Matrix multiply(const Matrix &A, const Matrix &B);
FlatMatrix multiply_flat(const FlatMatrix &A, const FlatMatrix &B, size_t n);

#endif // MATRIX_MULTIPLICATION_H
