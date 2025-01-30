#include "BaseCase.h"
#include "Blocking.h"
#include "SIMD.h"
#include "SafeArray.h"
#include <cstdlib>
#include <ctime>
#include <gtest/gtest.h>

using Matrix = std::vector<std::vector<int>>;
using FlatMatrix = std::vector<int>;

bool compare_matrices(const Matrix &A, const Matrix &B) {
  if (A.size() != B.size() || A[0].size() != B[0].size())
    return false;
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[0].size(); ++j) {
      if (A[i][j] != B[i][j])
        return false;
    }
  }
  return true;
}

bool compare_flat_matrices(const FlatMatrix &A, const FlatMatrix &B) {
  if (A.size() != B.size())
    return false;
  for (size_t i = 0; i < A.size(); ++i) {
    if (A[i] != B[i])
      return false;
  }
  return true;
}

TEST(MatrixMultiplicationTest, BaseVsFlat) {
  Matrix A = {{1, 2}, {3, 4}};
  Matrix B = {{5, 6}, {7, 8}};
  Matrix C_base = multiply(A, B);

  FlatMatrix A_flat = {1, 2, 3, 4};
  FlatMatrix B_flat = {5, 6, 7, 8};
  FlatMatrix C_flat = multiply_flat(A_flat, B_flat, 2);

  Matrix C_flat_to_matrix = {{C_flat[0], C_flat[1]}, {C_flat[2], C_flat[3]}};

  EXPECT_TRUE(compare_matrices(C_base, C_flat_to_matrix));
}

TEST(MatrixMultiplicationTest, ArrayMulTemplate) {
  FlatMatrix A_flat = {1, 2, 3, 4};
  FlatMatrix B_flat = {5, 6, 7, 8};
  FlatMatrix C_flat = multiply_flat(A_flat, B_flat, 2);
  constexpr size_t MATRIX_DIM = 8; // 8x8 matrix

  const SafeArray<int, 64> matrixFirst; // 8x8 = 64 elements
  const SafeArray<int, 64> matrixSecond;
  SafeArray<int, 64> resultMatrix;

  ArrayMulTemplate(matrixFirst, matrixSecond, resultMatrix, MATRIX_DIM);

  for (size_t i = 0; i < MATRIX_DIM; ++i) {
    for (size_t j = 0; j < MATRIX_DIM; ++j) {
      EXPECT_EQ(resultMatrix[i * MATRIX_DIM + j], 0);
    }
  }
}

TEST(MatrixMultiplicationTest, FlatVsSafeArray) {
  constexpr size_t MATRIX_DIM = 8;
  FlatMatrix A_flat(MATRIX_DIM * MATRIX_DIM);
  FlatMatrix B_flat(MATRIX_DIM * MATRIX_DIM);

  std::srand(std::time(nullptr));
  for (size_t i = 0; i < MATRIX_DIM * MATRIX_DIM; ++i) {
    A_flat[i] = std::rand() % 100;
    B_flat[i] = std::rand() % 100;
  }

  FlatMatrix C_flat = multiply_flat(A_flat, B_flat, MATRIX_DIM);

  SafeArray<int, MATRIX_DIM * MATRIX_DIM> matrixFirst;
  SafeArray<int, MATRIX_DIM * MATRIX_DIM> matrixSecond;
  SafeArray<int, MATRIX_DIM * MATRIX_DIM> resultMatrix;

  for (size_t i = 0; i < MATRIX_DIM * MATRIX_DIM; ++i) {
    matrixFirst[i] = A_flat[i];
    matrixSecond[i] = B_flat[i];
  }

  ArrayMulTemplate(matrixFirst, matrixSecond, resultMatrix, MATRIX_DIM);

  for (size_t i = 0; i < MATRIX_DIM * MATRIX_DIM; ++i) {
    EXPECT_EQ(resultMatrix[i], C_flat[i]);
  }
}

TEST(MatrixMultiplicationTest, Blocking) {
  constexpr size_t MATRIX_DIM = 32;
  FlatMatrix A = create_random_flat_matrix(MATRIX_DIM, 42);
  FlatMatrix B = create_random_flat_matrix(MATRIX_DIM, 41);

  FlatMatrix C_block = Blocking(A, B, MATRIX_DIM);
  FlatMatrix C_flat = multiply_flat(A, B, MATRIX_DIM);

  EXPECT_TRUE(compare_flat_matrices(C_block, C_flat));
}

TEST(MatrixMultiplicationTest, SIMD) {
  constexpr size_t MATRIX_DIM = 32;
  FlatMatrix A = create_random_flat_matrix(MATRIX_DIM, 42);
  FlatMatrix B = create_random_flat_matrix(MATRIX_DIM, 41);

  FlatMatrix C_SIMD = SIMD(A, B, MATRIX_DIM);
  FlatMatrix C_flat = multiply_flat(A, B, MATRIX_DIM);

  EXPECT_TRUE(compare_flat_matrices(C_SIMD, C_flat));
}
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
