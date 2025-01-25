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

### Benchmark Results

Total number of elements = N * N

| Benchmark                             | Time (ns) | CPU (ns)  | Iterations |
| ------------------------------------- | --------- | --------- | ---------- |
| BM_MatrixMultiplication_Random/8      | 395 ns    | 395 ns    | 1,795,230  |
| BM_MatrixMultiplication_Random/16     | 2,270 ns  | 2,270 ns  | 305,677    |
| BM_MatrixMultiplication_Random/32     | 16,134 ns | 16,134 ns | 42,623     |
| BM_FlatMatrixMultiplication_Random/8  | 201 ns    | 201 ns    | 3,445,345  |
| BM_FlatMatrixMultiplication_Random/16 | 1,452 ns  | 1,452 ns  | 476,767    |
| BM_FlatMatrixMultiplication_Random/32 | 10,411 ns | 10,409 ns | 66,010     |

## Using an Array instead of a Vector
[Link to the array code](include/SafeArray.h)

[Link to the matrix multiplication with array](src/SafeArray.cpp)

### Benchmark Results

Total number of elements = N

| Benchmark                              | Time (ns) | CPU (ns)  | Iterations |
| -------------------------------------- | --------- | --------- | ---------- |
| BM_SafeArrayMultiplication_Random/64   | 289 ns    | 289 ns    | 2,451,525  |
| BM_SafeArrayMultiplication_Random/256  | 2,307 ns  | 2,301 ns  | 308,611    |
| BM_SafeArrayMultiplication_Random/1024 | 18,615 ns | 18,585 ns | 36,599     |

### Attempted Optimisation

- Flattening the Matrix
- Using an Array instead of a Vector
- Fixed Size Array

### Conlusion

- 1D is still faster than 2D
- Current Vector implementation is faster than the Array implementation
- Will focus on optimising the Vector implementation instead

## Cache Blocking 

MultiplyFlatMem with BLOCK SIZE = 32

[Code](src/MemoryAllocation.cpp)

### Benchmark Results

| Benchmark                        | Time (ns)        | CPU (ns)         | Iterations |
| -------------------------------- | ---------------- | ---------------- | ---------- |
| BM_FlatMatrixMultiplication/32   | 12,168 ns        | 12,167 ns        | 56,025     |
| BM_FlatMatrixMultiplication/64   | 85,585 ns        | 85,582 ns        | 8,099      |
| BM_FlatMatrixMultiplication/128  | 2,144,447 ns     | 2,144,336 ns     | 326        |
| BM_FlatMatrixMultiplication/256  | 16,740,721 ns    | 16,739,794 ns    | 42         |
| BM_FlatMatrixMultiplication/512  | 251,166,479 ns   | 251,159,662 ns   | 3          |
| BM_FlatMatrixMultiplication/1024 | 3,989,131,536 ns | 3,988,868,152 ns | 1          |
| BM_MultiplyFlatMem/32            | 17,314 ns        | 17,314 ns        | 40,165     |
| BM_MultiplyFlatMem/64            | 129,237 ns       | 129,235 ns       | 5,387      |
| BM_MultiplyFlatMem/128           | 1,021,522 ns     | 1,021,520 ns     | 680        |
| BM_MultiplyFlatMem/256           | 9,133,922 ns     | 9,133,807 ns     | 73         |
| BM_MultiplyFlatMem/512           | 194,211,950 ns   | 194,203,834 ns   | 4          |
| BM_MultiplyFlatMem/1024          | 2,365,241,710 ns | 2,365,162,738 ns | 1          |

### Attempted Optimisation

- Cache Blocking
