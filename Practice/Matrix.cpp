#include "Matrix.h"
#include <iostream>
#include <cstdlib> // For random number generation
#include <ctime>   // For seeding the random number generator

Matrix::Matrix(int size) : size(size), data(size, std::vector<int>(size, 0)) {}

Matrix::Matrix(int size, bool random) : size(size), data(size, std::vector<int>(size, 0)) {
    if (random) {
        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned>(std::time(0)));

        // Fill the matrix with random numbers between 1 and 100
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                data[i][j] = std::rand() % 100 + 1;
            }
        }
    }
}

void Matrix::display() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}