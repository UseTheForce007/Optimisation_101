# Optimising Matrix Multiplication

## Journey So Far

In this project, I am exploring different methods to optimize matrix multiplication.

I have also set up benchmarks to compare the performance. The benchmarks are implemented using the Google Benchmark library, which provides a robust framework for measuring the performance of the functions under various conditions.

The results from these benchmarks will help in understanding the efficiency gains achieved through the optimization techniques applied.

## Basic Matrix Multiplication

```cpp
using Matrix = std::vector<std::vector<int>>;
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
```
This is a normal matrix multiplication function that takes two matrices as input and returns the product of the two matrices. The matrices are represented as vectors of vectors of integers.

```cpp
using FlatMatrix = std::vector<int>;
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
```
This is a flat matrix multiplication function that takes two flat matrices as input and returns the product of the two matrices. The matrices are represented as vectors of integers.

## Benchmark Results

| Benchmark                       | Time (ns)  | CPU (ns)   | Iterations |
| ------------------------------- | ---------- | ---------- | ---------- |
| BM_MatrixMultiplication/8       | 363        | 363        | 1,947,224  |
| BM_MatrixMultiplication/16      | 2,073      | 2,073      | 337,793    |
| BM_MatrixMultiplication/32      | 14,590     | 14,590     | 47,837     |
| BM_MatrixMultiplication/64      | 111,250    | 111,246    | 6,240      |
| BM_MatrixMultiplication/128     | 837,802    | 837,747    | 827        |
| BM_MatrixMultiplication/256     | 8,065,433  | 8,065,078  | 85         |
| BM_FlatMatrixMultiplication/8   | 221        | 221        | 3,175,246  |
| BM_FlatMatrixMultiplication/16  | 1,685      | 1,685      | 414,133    |
| BM_FlatMatrixMultiplication/32  | 12,569     | 12,569     | 55,222     |
| BM_FlatMatrixMultiplication/64  | 98,579     | 98,575     | 7,024      |
| BM_FlatMatrixMultiplication/128 | 2,015,356  | 2,015,252  | 351        |
| BM_FlatMatrixMultiplication/256 | 15,784,330 | 15,782,952 | 43         |