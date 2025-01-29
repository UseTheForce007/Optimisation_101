#include "BaseCase.h"
#include "Blocking.h"
#include <iostream>

int main() {
  constexpr size_t n = 1024;
  FlatMatrix A = create_random_flat_matrix(n, 42);
  FlatMatrix B = create_random_flat_matrix(n, 41);
  FlatMatrix C = Blocking(A, B, n);
  return 0;
}
