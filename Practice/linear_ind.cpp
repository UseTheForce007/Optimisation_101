#include <chrono>

#include <iostream>
#include <random>
#include <vector>
using namespace std;


int index(int row, int col, int num_col)
{
    return (row * num_col + col);
}



int main() {

    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    // Create a 2D vector to store the random matrix
    
    vector<double> matrix1(500* 500);
    vector<double> matrix2(500 * 500);

    // Generate random numbers and fill the matrix
    for (int i = 0; i < 500*500; i++) {
        
        matrix1[i] = dist(gen);
        matrix2[i] = dist(gen);
    }



    int num_col1 = 500; int num_col2 = 500;
    int num_row1 = 500; int num_row2 = 500;


    auto start_time = std::chrono::high_resolution_clock::now();

    // Your code to be timed
  vector<double> C(num_row1*num_col2);

    for (int i = 0; i < num_row1; i++)
    {
        for (int j = 0; j < num_col2; j++)
        {
            int sum = 0;
            for (int k = 0; k < num_col1; k++)
            {
                int ind_1 = index(i, k, num_col1);
                int ind_2 = index(k, j, num_col2);
                int result_ind = index(i, j, num_col2);
                C[result_ind] += matrix1[ind_1] * matrix2[ind_2];
            }
            
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Execution time: " << duration << " milliseconds" << std::endl;



    return 0;
}