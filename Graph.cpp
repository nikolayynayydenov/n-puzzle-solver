#include "Graph.h"


Graph::Graph(int n)
{
	this->n = n;
}

Graph::~Graph()
{
	// TODO
}

void Graph::addNode(int** node)
{
	if (nodeExists(node)) {
		return;
	}

	vector<int**> newAdjList;
	newAdjList.push_back(node);
	graph.push_back(newAdjList);

}

void Graph::addEdge(int** from, int** to)
{

	for (vector<int**>& nodeList : this->graph) {
		int** currentNode = nodeList.front();

		if (nodesAreEqual(from, currentNode)) {
			nodeList.push_back(to);
			return;
		}
	}

	throw "Non existent node";
}

bool Graph::nodeExists(int** node)
{
	for (vector<int**> const& nodeList : this->graph) {
		int** currentNode = nodeList.front();

		if (nodesAreEqual(node, currentNode)) {
			return true;
		}
	}

	return false;
}

void Graph::printNode(int** node)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << node[i][j] << " ";
		}
		cout << endl;
	}
}

void Graph::printNodes()
{
	for (vector<int**> const& nodeList : graph)
	{
		printNode(nodeList.front());
	}
}

bool Graph::nodesAreEqual(int** node, int** otherNode)
{
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			if (node[i][j] != otherNode[i][j]) {
				return false;
			}
		}
	}
	return true;
}