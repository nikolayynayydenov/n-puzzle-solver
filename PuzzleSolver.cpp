#include "PuzzleSolver.h"

PuzzleSolver::PuzzleSolver(int** initState, int n, int targetZeroIndex)
{
	this->n = n;
	this->found = false;
	this->setTargetZeroSquare(targetZeroIndex);

	pair<int, int> coords = this->getInitStateCoords(matrixToVector(initState));

	this->initState = Board(matrixToVector(initState), n, coords.first, coords.second);
	this->setGoalState();
}

PuzzleSolver::~PuzzleSolver()
{
	// TODO
}

vector<vector<int>> PuzzleSolver::matrixToVector(int** matrix)
{
	vector<vector<int>> v;
	for (int i = 0; i < this->n; i++)
	{
		vector<int> innerV;

		for (int j = 0; j < this->n; j++)
		{
			innerV.push_back(matrix[i][j]);
		}

		v.push_back(innerV);
	}

	return v;

}

void PuzzleSolver::setTargetZeroSquare(int targetZeroIndex)
{
	if (targetZeroIndex == -1) {
		this->iTargetZero = this->n - 1;
		this->jTargetZero = this->n - 1;
	}
	else if (targetZeroIndex >= 0 && targetZeroIndex < this->n * this->n) {
		this->iTargetZero = (int)floor(targetZeroIndex / this->n);
		this->jTargetZero = targetZeroIndex % this->n;
	}
	else {
		throw exception("Invalid value for zero square");
	}
}

pair<int, int> PuzzleSolver::getInitStateCoords(vector<vector<int>> initState)
{
	pair<int, int> coords;
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			if (initState[i][j] == 0) {
				coords.first = i;
				coords.second = j;
				return coords;
			}
		}
	}

	throw exception("Matrix doesn't have a zero");
}

// TODO: fix
bool PuzzleSolver::isSolvable()
{
	return true;
	int count = this->initState.inversionsCount();
	if (this->n % 2 == 0) {
		// event
		return count % 2 != 0;
	}
	else {
		// odd
		pair<int, int> coords = this->getInitStateCoords(this->initState.tiles);
		return (count + coords.first) % 2 == 0;
	}
}

void PuzzleSolver::solve()
{
	if (!this->isSolvable()) {
		cout << "The puzzle is not solvable" << endl;
		return;
	}

	//cout << "Solving started" << endl;

	int threshold = this->initState.heuristic();

	while (true) {
		vector<pair<Board, string>> path;
		int result = this->search(this->initState, 0, threshold, path);

		if (result == this->FOUND) {
			break;
		}

		// TODO: check if endless loop

		threshold = result;

		visited.clear();
	}

	//cout << "Solving ended" << endl;
}

int PuzzleSolver::search(Board board, int cost, int threshold, vector<pair<Board, string>> path)
{
	for (vector<pair<Board, string>>::iterator it = path.begin(); it != path.end(); ++it) {
		if ((*it).first.isEqualTo(board)) {
			return this->VISITED;
		}
	}

	int heuristic = board.heuristic();
	int f = cost + heuristic;

	if (f > threshold) {
		return f;
	}

	if (heuristic == 0) {
		cout << path.size() << endl;
		for (vector<pair<Board, string>>::iterator it = path.begin(); it != path.end(); ++it) {
			cout << (*it).second << endl;
		}
		return this->FOUND;
	}

	vector<pair<Board, string>> neighbours = board.neighbours();

	int min = numeric_limits<int>::max();

	for (auto neighbour : neighbours) {
		//neighbour->print();
		if (rand() % 1000 == 0) {
			cout << "Threshold " << threshold << ", cost " << cost << endl;
		}
		pair<Board, string> pr(board, neighbour.second);
		path.push_back(pr);
		// TODO: check if visited here
		int temp = this->search(neighbour.first, cost + 1, threshold, path); // Do we really add 1 as cost
		path.pop_back();
		if (temp == this->FOUND) {
			return this->FOUND;
		}

		if (temp == this->VISITED) {
			continue;
		}

		if (temp < min) {
			min = temp;
		}
	}
	//cout << "Path count: " << path.size() << endl;
	return min;
}

void PuzzleSolver::setGoalState()
{
	vector<vector<int>> tiles;
	int counter = 1;

	for (int i = 0; i < this->n; i++)
	{
		vector<int> tilesRow;
		for (int j = 0; j < this->n; j++)
		{
			if (i == this->iTargetZero && j == this->jTargetZero) {
				tilesRow.push_back(0);
			}
			else {
				tilesRow.push_back(counter);
				counter++;
			}
		}
		tiles.push_back(tilesRow);
	}

	this->goalState = Board(tiles, this->n, this->iTargetZero, this->jTargetZero);
}