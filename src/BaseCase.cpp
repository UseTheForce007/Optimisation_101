#include "BaseCase.h"
#include <cstddef>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <random>
#include <vector>

using Matrix = std::vector<std::vector<int>>;
using FlatMatrix = std::vector<int>;

Matrix multiply(const Matrix &A, const Matrix &B) {
  size_t n = A.size();
  Matrix C(n, std::vector<int>(n, 0));

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      for (size_t k = 0; k < n; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return C;
}

FlatMatrix multiply_flat(const FlatMatrix &A, const FlatMatrix &B, size_t n) {
  FlatMatrix C(n * n, 0);

  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      for (size_t k = 0; k < n; ++k) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }

  return C;
}

FlatMatrix create_random_flat_matrix(size_t n, int seed) {
  FlatMatrix matrix(n * n);
  std::mt19937 gen(seed);
  std::uniform_int_distribution<> dis(1, 100);

  for (size_t i = 0; i < n * n; ++i) {
    matrix[i] = dis(gen);
  }

  return matrix;
}
