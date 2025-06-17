# Optimising Matrix Multiplication
## Journey So Far

In this project, I am exploring different methods to optimize matrix multiplication for square matrices.

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

MultiplyFlatBlock

[Code](src/Blocking.cpp)

### Benchmark Results
## Benchmark Results

| Benchmark                            | Time        | CPU         | Iterations |
| ------------------------------------ | ----------- | ----------- | ---------- |
| BM_FlatMatrixMultiplication/32       | 0.012 ms    | 0.012 ms    | 60464      |
| BM_FlatMatrixMultiplication/64       | 0.088 ms    | 0.088 ms    | 7841       |
| BM_FlatMatrixMultiplication/128      | 2.22 ms     | 2.22 ms     | 314        |
| BM_FlatMatrixMultiplication/256      | 16.6 ms     | 16.6 ms     | 41         |
| BM_FlatMatrixMultiplication/512      | 238 ms      | 237 ms      | 3          |
| **BM_FlatMatrixMultiplication/1024** | **4133 ms** | **4126 ms** | 1          |
| BM_MultiplyFlatBlock/32/16           | 0.019 ms    | 0.019 ms    | 37559      |
| BM_MultiplyFlatBlock/64/16           | 0.147 ms    | 0.147 ms    | 4715       |
| BM_MultiplyFlatBlock/128/16          | 1.18 ms     | 1.18 ms     | 591        |
| BM_MultiplyFlatBlock/256/16          | 9.52 ms     | 9.52 ms     | 73         |
| BM_MultiplyFlatBlock/512/16          | 88.1 ms     | 88.1 ms     | 8          |
| **BM_MultiplyFlatBlock/1024/16**     | **1878 ms** | **1877 ms** | 1          |
| BM_MultiplyFlatBlock/32/32           | 0.018 ms    | 0.018 ms    | 40094      |
| BM_MultiplyFlatBlock/64/32           | 0.139 ms    | 0.139 ms    | 5063       |
| BM_MultiplyFlatBlock/128/32          | 1.12 ms     | 1.12 ms     | 606        |
| BM_MultiplyFlatBlock/256/32          | 10.1 ms     | 10.1 ms     | 67         |
| BM_MultiplyFlatBlock/512/32          | 202 ms      | 202 ms      | 3          |
| **BM_MultiplyFlatBlock/1024/32**     | **2455 ms** | **2452 ms** | 1          |
| BM_MultiplyFlatBlock/32/64           | 0.017 ms    | 0.017 ms    | 41280      |
| BM_MultiplyFlatBlock/64/64           | 0.136 ms    | 0.136 ms    | 5091       |
| BM_MultiplyFlatBlock/128/64          | 1.22 ms     | 1.22 ms     | 571        |
| BM_MultiplyFlatBlock/256/64          | 17.8 ms     | 17.8 ms     | 39         |
| BM_MultiplyFlatBlock/512/64          | 204 ms      | 203 ms      | 3          |
| **BM_MultiplyFlatBlock/1024/64**     | **2583 ms** | **2581 ms** | 1          |

### Attempted Optimisation
- Cache Blocking with different block sizes

### Conclusion
- Cache Blocking with block size 16 is the fastest
- Total Speedup at matrix Dim (1024) : 4133 ms / 1878 ms = 2.2x

## SIMD

[SIMD](src/SIMD.cpp)

### Benchmark Results

| Benchmark                        | Time (ms) | CPU (ms) | Iterations |
| -------------------------------- | --------- | -------- | ---------- |
| BM_SIMD/32                       | 0.001     | 0.001    | 471,691    |
| BM_SIMD/64                       | 0.011     | 0.011    | 60,121     |
| BM_SIMD/128                      | 0.095     | 0.095    | 7,435      |
| BM_SIMD/256                      | 0.790     | 0.790    | 873        |
| BM_SIMD/512                      | 9.86      | 9.86     | 70         |
| **BM_SIMD/1024**                 | **225**   | **225**  | 3          |
| BM_MultiplyFlatBlock/32/16       | 0.017     | 0.017    | 40,411     |
| BM_MultiplyFlatBlock/64/16       | 0.137     | 0.137    | 4,765      |
| BM_MultiplyFlatBlock/128/16      | 1.10      | 1.10     | 632        |
| BM_MultiplyFlatBlock/256/16      | 8.78      | 8.78     | 79         |
| BM_MultiplyFlatBlock/512/16      | 81.6      | 81.6     | 8          |
| **BM_MultiplyFlatBlock/1024/16** | **1789**  | **1789** | 1          |

### Attempted Optimisation
- Using SIMD instructions to perform 8 multiplications at once
- Using Cache Blocking with block size 16

### Conclusion
- Improved performance further by using SIMD instructions
- Total Speedup at matrix Dim (1024) : 1789 ms / 225 ms = 7.9x

## Using Open MPI
[Open MPI] (src/Parallel.cpp)
### Benchmark Results
🚀 MPI Matrix Multiplication Benchmark 🚀
Number of MPI processes: 8
==========================================

| Matrix Size | Block Size | Average Time (ms) | Performance (GFLOPS) |
| ----------- | ---------- | ----------------- | -------------------- |
| 512 x 512   | 16         | 2.89              | 93.02                |
| 1024 x 1024 | 16         | 41.61             | 51.61                |
| 2048 x 2048 | 16         | 328.00            | 52.38                |
| 4096 x 4096 | 16         | 3013.40           | 45.61                |

### Attempted Optimisation
- Using Open MPI to parallelize the matrix multiplication
- Using Cache Blocking with block size 16
- Using SIMD instructions to perform 8 multiplications at once

### Conclusion
- Improved performance further by using Open MPI to parallelize the matrix multiplication

## Updated Benchmark Results

### SIMD

| Benchmark    | Time (ms) | CPU (ms) | Iterations |
| ------------ | --------- | -------- | ---------- |
| BM_SIMD/512  | 11.5      | 11.5     | 60         |
| BM_SIMD/1024 | 224       | 224      | 3          |
| BM_SIMD/2048 | 2929      | 2929     | 1          |
| BM_SIMD/4096 | 23572     | 23571    | 1          |

### Cache Blocking

| Benchmark                    | Time (ms) | CPU (ms) | Iterations |
| ---------------------------- | --------- | -------- | ---------- |
| BM_MultiplyFlatBlock/512/16  | 82.3      | 82.3     | 9          |
| BM_MultiplyFlatBlock/1024/16 | 1786      | 1786     | 1          |
| BM_MultiplyFlatBlock/2048/16 | 14212     | 14211    | 1          |
| BM_MultiplyFlatBlock/4096/16 | 149143    | 149135   | 1          |
| BM_MultiplyFlatBlock/512/32  | 208       | 208      | 3          |
| BM_MultiplyFlatBlock/1024/32 | 2428      | 2428     | 1          |
| BM_MultiplyFlatBlock/2048/32 | 19331     | 19330    | 1          |
| BM_MultiplyFlatBlock/4096/32 | 183507    | 183498   | 1          |
| BM_MultiplyFlatBlock/512/64  | 231       | 231      | 3          |
| BM_MultiplyFlatBlock/1024/64 | 2642      | 2641     | 1          |
| BM_MultiplyFlatBlock/2048/64 | 21104     | 21103    | 1          |
| BM_MultiplyFlatBlock/4096/64 | 198452    | 198440   | 1          |

### Flat Matrix Multiplication

| Benchmark                        | Time (ms) | CPU (ms) | Iterations |
| -------------------------------- | --------- | -------- | ---------- |
| BM_FlatMatrixMultiplication/512  | 345       | 345      | 2          |
| BM_FlatMatrixMultiplication/1024 | 3750      | 3750     | 1          |
| BM_FlatMatrixMultiplication/2048 | 50526     | 50523    | 1          |
| BM_FlatMatrixMultiplication/4096 | 422479    | 422448   | 1          |