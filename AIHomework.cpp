#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <map>
#include <stdlib.h>  
#include <algorithm>
#include <string>
#include "./Graph.h"
#include "./PuzzleSolver.h"

using namespace std;

int** createRandomMatrix(int n)
{
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand();
		}
	}

	return matrix;
}

void printMatrix(int** matrix, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void freeMatrix(int** matrix, int n)
{
	for (int i = 0; i < n; ++i) {
		delete[] matrix[i];
	}

	delete[] matrix;
}


int main()
{
	const int n = 3;

	//cin >> n;

	int** matrix = new int* [n];

	matrix[0] = new int[n];
	matrix[0][0] = 4;
	matrix[0][1] = 3;
	matrix[0][2] = 7;

	matrix[1] = new int[n];
	matrix[1][0] = 2;
	matrix[1][1] = 1;
	matrix[1][2] = 5;

	matrix[2] = new int[n];
	matrix[2][0] = 0;
	matrix[2][1] = 6;
	matrix[2][2] = 8;

	//matrix[0] = new int[n];
	//matrix[0][0] = 15;
	//matrix[0][1] = 2;
	//matrix[0][2] = 1;
	//matrix[0][3] = 12;

	//matrix[1] = new int[n];
	//matrix[1][0] = 8;
	//matrix[1][1] = 5;
	//matrix[1][2] = 6;
	//matrix[1][3] = 11;

	//matrix[2] = new int[n];
	//matrix[2][0] = 4;
	//matrix[2][1] = 9;
	//matrix[2][2] = 10;
	//matrix[2][3] = 7;

	//matrix[3] = new int[n];
	//matrix[3][0] = 3;
	//matrix[3][1] = 14;
	//matrix[3][2] = 13;
	//matrix[3][3] = 0;

	//matrix[0] = new int[n];
	//matrix[0][0] = 6;
	//matrix[0][1] = 13;
	//matrix[0][2] = 7;
	//matrix[0][3] = 10;

	//matrix[1] = new int[n];
	//matrix[1][0] = 8;
	//matrix[1][1] = 9;
	//matrix[1][2] = 11;
	//matrix[1][3] = 0;

	//matrix[2] = new int[n];
	//matrix[2][0] = 15;
	//matrix[2][1] = 2;
	//matrix[2][2] = 12;
	//matrix[2][3] = 5;

	//matrix[3] = new int[n];
	//matrix[3][0] = 14;
	//matrix[3][1] = 3;
	//matrix[3][2] = 1;
	//matrix[3][3] = 4;

	int targetBlankIndex = -1; // currently not working

	try {
		PuzzleSolver* ps = new PuzzleSolver(matrix, n, targetBlankIndex);
		ps->solve();
	}
	catch (exception& ex) {
		cout << "An error occured: " << ex.what() << endl;
	}


	freeMatrix(matrix, n);

	return 0;
}
/*
5 3 1
2 4 6
7 8 0
*/
