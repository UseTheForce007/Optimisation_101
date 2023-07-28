#pragma once

#include <vector>


class Matrix {
public:
    Matrix(int size);
    Matrix(int size, bool random);

    void display() const;
    int size;
    std::vector<std::vector<int>> data;
};
