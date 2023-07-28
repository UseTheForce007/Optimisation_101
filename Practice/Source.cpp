#include <chrono>
#include "Matrix.h"
#include <iostream>
#include <random>
#include <vector>
using namespace std;



int main() {
	int N = 500;
	
	Matrix matrix1(N);
	Matrix matrix2(N);
	Matrix matrix3(N,true);

	auto start = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				matrix3.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
			}
		}
	}

	
	auto end = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

	start = chrono::high_resolution_clock::now();

	for (int j = 0; j < N; ++j) {
		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				matrix3.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
			}
		}
	}


	end = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

	start = chrono::high_resolution_clock::now();

	for (int i = 0; i < N; ++i) {
		for (int k = 0; k < N; k++) {
			for (int j = 0; j < N; j++) {
				matrix3.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
			}
		}
	}

	end = chrono::high_resolution_clock::now();
	cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

	return 0;
}