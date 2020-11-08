#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <string> 
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



size_t split(const std::string& txt, std::vector<std::string>& strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
}

int** readMatrix(int n)
{
	int** matrix = new int* [n];

	string str;
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[n];

		for (int j = 0; j < n; j++)
		{
			cin >> matrix[i][j];
		}

	}

	return matrix;
}

void freeMatrix(int** matrix, int n)
{
	for (int i = 0; i < n; ++i) {
		delete[] matrix[i];
	}

	delete[] matrix;
}

int** get8Matrix()
{
	int** matrix = new int* [3];

	matrix[0] = new int[3];
	matrix[0][0] = 4;
	matrix[0][1] = 3;
	matrix[0][2] = 7;

	matrix[1] = new int[3];
	matrix[1][0] = 2;
	matrix[1][1] = 1;
	matrix[1][2] = 5;

	matrix[2] = new int[3];
	matrix[2][0] = 0;
	matrix[2][1] = 6;
	matrix[2][2] = 8;

	return matrix;
}

int** get15Matrix()
{
	int** matrix = new int* [4];
	matrix[0] = new int[4];
	matrix[0][0] = 15;
	matrix[0][1] = 2;
	matrix[0][2] = 1;
	matrix[0][3] = 12;

	matrix[1] = new int[4];
	matrix[1][0] = 8;
	matrix[1][1] = 5;
	matrix[1][2] = 6;
	matrix[1][3] = 11;

	matrix[2] = new int[4];
	matrix[2][0] = 4;
	matrix[2][1] = 9;
	matrix[2][2] = 10;
	matrix[2][3] = 7;

	matrix[3] = new int[4];
	matrix[3][0] = 3;
	matrix[3][1] = 14;
	matrix[3][2] = 13;
	matrix[3][3] = 0;

	//matrix[0] = new int[4];
	//matrix[0][0] = 6;
	//matrix[0][1] = 13;
	//matrix[0][2] = 7;
	//matrix[0][3] = 10;

	//matrix[1] = new int[4];
	//matrix[1][0] = 8;
	//matrix[1][1] = 9;
	//matrix[1][2] = 11;
	//matrix[1][3] = 0;

	//matrix[2] = new int[4];
	//matrix[2][0] = 15;
	//matrix[2][1] = 2;
	//matrix[2][2] = 12;
	//matrix[2][3] = 5;

	//matrix[3] = new int[4];
	//matrix[3][0] = 14;
	//matrix[3][1] = 3;
	//matrix[3][2] = 1;
	//matrix[3][3] = 4;

	return matrix;
}


int main()
{
	int n = 15;
	//cin >> n;
	int** matrix = get15Matrix();
	//int** matrix = readMatrix(n);
	int targetBlankIndex = -1; // currently not working
	//printMatrix(matrix, n);
	try {
		PuzzleSolver* ps = new PuzzleSolver(matrix, sqrt(n + 1), targetBlankIndex);
		ps->solve();
	}
	catch (exception& ex) {
		cout << "An error occured: " << ex.what() << endl;
	}

	freeMatrix(matrix, n);

	return 0;
}