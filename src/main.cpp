#include "BaseCase.h"
#include "Parallel.h"
#include <iostream>
#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  // Example usage of ParallelBlockingMPIRows
  size_t n = 64;         // Size of the matrix
  size_t block_size = 8; // Block size for multiplication

  FlatMatrix A = create_random_flat_matrix(n, 42);
  FlatMatrix B = create_random_flat_matrix(n, 41);
  FlatMatrix C = ParallelBlockingMPIRows(A, B, n, block_size);

  if (C.empty()) {
    std::cerr << "Error: Result matrix is empty." << std::endl;
  } else {
    std::cout << "Matrix multiplication completed successfully." << std::endl;
  }

  MPI_Finalize();
  return 0;
}