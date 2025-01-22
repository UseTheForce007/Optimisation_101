#include "matrix_multiplication.h"
#include <iostream>

int main() {
  Matrix A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  Matrix B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
  Matrix C = multiply(A, B);

  // std::cout << "Result of matrix multiplication:" << std::endl;
  // for (const auto& row : C) {
  //     for (const auto& elem : row) {
  //         std::cout << elem << " ";
  //     }
  //     std::cout << std::endl;
  // }

  return 0;
}
