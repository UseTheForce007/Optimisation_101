#include "BaseCase.h"
#include <SafeArray.h>
#include <iostream>

int main() {
  Matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
  Matrix C = multiply(A, B);

  constexpr size_t MATRIX_DIM = 8; // 8x8 matrix

  const SafeArray<int, 64> matrixFirst; // 8x8 = 64 elements
  const SafeArray<int, 64> matrixSecond;
  SafeArray<int, 64> resultMatrix;

  ArrayMulTemplate(matrixFirst, matrixSecond, resultMatrix, MATRIX_DIM);

  // std::cout << "Result of matrix multiplication:" << std::endl;
  // for (const auto& row : C) {
  //     for (const auto& elem : row) {
  //         std::cout << elem << " ";
  //     }
  //     std::cout << std::endl;
  // }

  return 0;
}
