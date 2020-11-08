#pragma once

#include <iostream>
#include <algorithm>
#include <limits>
#include <math.h>
#include "Board.h"

using namespace std;

class PuzzleSolver
{
public:
	PuzzleSolver(int**, int, int);
	~PuzzleSolver();
	void setTargetZeroSquare(int);
	pair<int, int> getInitStateCoords(int**);
	bool isSolvable();
	void solve(); 
	int search(Board*, int, int, vector<Board*>);
private:

	static const int VISITED = -1;
	static const int FOUND = -2;

	Board* initState;
	Board* goalState;
	vector<Board*> visited;
	bool found; // goal state is reached
	int n; // board size
	int iTargetZero; // blank square target position i
	int jTargetZero; // blank square target position j
	void setGoalState();
};

