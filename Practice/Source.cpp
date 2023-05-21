#include <chrono>

#include <iostream>
#include <random>
#include <vector>
using namespace std;


//int main() {
//
//    // Create a random number generator
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<double> dist(0.0, 1.0);
//
//    // Create a 2D vector to store the random matrix
//    std::vector<std::vector<double>> matrix1(500, std::vector<double>(500));
//
//    // Generate random numbers and fill the matrix
//    for (int i = 0; i < 500; i++) {
//        for (int j = 0; j < 500; j++) {
//            matrix1[i][j] = dist(gen);
//        }
//    }
//
//    std::vector<std::vector<double>> matrix2(500, std::vector<double>(500));
//    for (int i = 0; i < 500; i++) {
//        for (int j = 0; j < 500; j++) {
//            matrix2[i][j] = dist(gen);
//        }
//    }
//
//
//    int m = 3;
//    int n = 3;
//    int a[3][3] = { { 1,2,3},{4,5,6} ,{7,8,9} };
//	int b[3][3] = { { 1,2,3},{4,5,6} ,{7,8,9} };
//
//    int numRows1 = sizeof(matrix1) / sizeof(matrix1[0]);
//    int numCols1 = sizeof(matrix1[0]) / sizeof(matrix1[0][0]);
//
//    int numRows2 = sizeof(matrix2) / sizeof(matrix2[0]);
//    int numCols2 = sizeof(matrix2[0]) / sizeof(matrix2[0][0]);
//
//    auto start_time = std::chrono::high_resolution_clock::now();
//
//    // Your code to be timed
//    std::vector<std::vector<double>> C(500, std::vector<double>(500));
//
//    for (int i = 0; i < 500; i++)
//    {
//        for (int j = 0; j < 500; j++)
//        {
//            int sum = 0;
//            for (int k = 0; k < 500; k++)
//            {
//                sum += matrix1[i][k] * matrix2[k][j];
//            }
//            C[i][j] = sum;
//        }
//    }
//    auto end_time = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
//    std::cout << "Execution time: " << duration << " milliseconds" << std::endl;
//
//    
//
//    return 0;
//}