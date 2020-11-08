#pragma once

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Board
{
public:
	Board(int**, int, int iZero = -1, int jZero = -1);
	Board(const Board&);
	~Board();
	int heuristic();
	int manhattanDistance(int, int);
	Board* swipeLeft();
	Board* swipeRight();
	Board* swipeUp();
	Board* swipeDown();
	vector<Board*> neighbours();
	bool canSwipeLeft() const;
	bool canSwipeRight() const;
	bool canSwipeUp() const;
	bool canSwipeDown() const;
	void print();	
	int** copyTiles();
	bool isEqualTo(Board*);
	int inversionsCount() const;

	int n;
	int** tiles; 
private:
	
	int iZero;
	int jZero;

	void setZero();
	
}; 