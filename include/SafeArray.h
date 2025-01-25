#ifndef SAFE_ARRAY_H
#define SAFE_ARRAY_H
#include <cstddef>
#include <cstring>   // for memset
#include <stdexcept> // for std::out_of_range

template <typename T, unsigned int N> class SafeArray {
protected:
  T a[N]; // Array with N elements of type T
public:
  SafeArray() {              // Constructor
    memset(a, 0, sizeof(a)); // Initialize to zero
  }
  int Size() const { // Return the size of the array
    return N;
  }
  T &operator[](unsigned int i) { // Safe [] array index operator
#ifdef DEBUG
    if (i >= N) {
      throw std::out_of_range("Index out of range");
    }
#endif
    return a[i]; // Return reference to a[i]
  }
  const T &operator[](unsigned int i) const { // Const version of operator[]
#ifdef DEBUG
    if (i >= N) {
      throw std::out_of_range("Index out of range");
    }
#endif
    return a[i]; // Return reference to a[i]
  }
};

template <typename T, unsigned int N>
void ArrayMulTemplate(const SafeArray<T, N> &matrixA,
                      const SafeArray<T, N> &matrixB, SafeArray<T, N> &result,
                      size_t dimension);

#endif // SAFE_ARRAY_H