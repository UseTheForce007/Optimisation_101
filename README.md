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

| Benchmark                               | Time (ns)        | CPU (ns)         | Iterations |
| --------------------------------------- | ---------------- | ---------------- | ---------- |
| BM_MatrixMultiplication_Random/64       | 121,687 ns       | 121,681 ns       | 5,781      |
| BM_MatrixMultiplication_Random/256      | 8,825,548 ns     | 8,825,185 ns     | 79         |
| BM_MatrixMultiplication_Random/1024     | 979,737,614 ns   | 979,688,995 ns   | 1          |
| BM_FlatMatrixMultiplication_Random/64   | 79,133 ns        | 79,125 ns        | 8,794      |
| BM_FlatMatrixMultiplication_Random/256  | 15,697,405 ns    | 15,696,589 ns    | 45         |
| BM_FlatMatrixMultiplication_Random/1024 | 3,889,675,488 ns | 3,889,346,404 ns | 1          |

## Using an Array instead of a Vector
[Link to the array code](include/SafeArray.h)

[Link to the matrix multiplication with array](src/SafeArray.cpp)

## Benchmark Results

| Benchmark                              | Time (ns) | CPU (ns)  | Iterations |
| -------------------------------------- | --------- | --------- | ---------- |
| BM_SafeArrayMultiplication_Random/64   | 468 ns    | 467 ns    | 1,475,142  |
| BM_SafeArrayMultiplication_Random/256  | 4,088 ns  | 4,088 ns  | 172,892    |
| BM_SafeArrayMultiplication_Random/1024 | 41,929 ns | 41,923 ns | 17,341     |


## Optimisation

- Flattening the Matrix
- Using an Array instead of a Vector
- Fixed Size Array
