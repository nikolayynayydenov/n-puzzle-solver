#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Graph
{
public:
	Graph(int);
	~Graph();
	void addNode(int**);
	void addEdge(int**, int**);
	bool nodeExists(int**);
	void printNode(int**);
	bool nodesAreEqual(int**, int**);
	void printNodes();
private:
	vector<vector<int**>> graph;
	int n; // The size of the board (the size of each node)
};

