#pragma once

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Board
{
public:
	Board(vector<vector<int>>, int, int iZero = -1, int jZero = -1);
	Board(const Board&);
	Board();
	~Board();
	//void cleanUp();
	int heuristic();
	int manhattanDistance(int, int);
	pair<Board, string> swipeLeft();
	pair<Board, string> swipeRight();
	pair<Board, string> swipeUp();
	pair<Board, string> swipeDown();
	vector<pair<Board, string>> neighbours();
	bool canSwipeLeft() const;
	bool canSwipeRight() const;
	bool canSwipeUp() const;
	bool canSwipeDown() const;
	void print();	
	vector<vector<int>> copyTiles();
	bool isEqualTo(Board);
	int inversionsCount() const;

	int n;
	vector<vector<int>> tiles; 
private:
	
	int iZero;
	int jZero;

	void setZero();
	
}; 