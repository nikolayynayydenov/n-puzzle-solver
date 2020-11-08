#include "PuzzleSolver.h"

PuzzleSolver::PuzzleSolver(int** initState, int n, int targetZeroIndex)
{
	this->n = n;
	this->found = false;
	this->setTargetZeroSquare(targetZeroIndex);

	pair<int, int> coords = this->getInitStateCoords(initState);

	this->initState = new Board(initState, n, coords.first, coords.second);
	this->setGoalState();
}

PuzzleSolver::~PuzzleSolver()
{
	// TODO
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

pair<int, int> PuzzleSolver::getInitStateCoords(int** initState)
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

bool PuzzleSolver::isSolvable()
{
	return true;
	int count = this->initState->inversionsCount();
	if (this->n % 2 == 0) {
		// event
		return count % 2 != 0;
	}
	else {
		// odd
		pair<int, int> coords = this->getInitStateCoords(this->initState->tiles);
		return (count + coords.first) % 2 == 0;
	}
}

void PuzzleSolver::solve()
{
	if (!this->isSolvable()) {
		cout << "The puzzle is not solvable" << endl;
		return;
	}

	cout << "Solving started" << endl;

	int threshold = this->initState->heuristic();

	while (true) {
		vector<Board*> path;
		int result = this->search(this->initState, 0, threshold, path);

		if (result == this->FOUND) {
			break;
		}

		// TODO: check if endless loop

		threshold = result;

		visited.clear();
	}

	cout << "Solving ended" << endl;
}

int PuzzleSolver::search(Board* board, int cost, int threshold, vector<Board*> path)
{
	for (vector<Board*>::iterator it = path.begin(); it != path.end(); ++it) {
		if ((*it)->isEqualTo(board)) {
			return this->VISITED;
		}
	}

	path.push_back(board);

	int heuristic = board->heuristic();
	int f = cost + heuristic;

	if (f > threshold) {
		return f;
	}

	if (heuristic == 0) {
		board->print();
		return this->FOUND;
	}

	vector<Board*> neighbours = board->neighbours();

	int min = numeric_limits<int>::max();
	int count = 1;
	for (Board* const& neighbour : neighbours) {
		//neighbour->print();
		//cout << "Threshold " << threshold << ", neighbour " << count++ << ", cost " << cost << endl;
		path.push_back(board);
		// TODO: check if visited here
		int temp = this->search(neighbour, cost + 1, threshold, path); // Do we really add 1 as cost
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
	int** tiles = new int* [this->n];
	int counter = 1;

	for (int i = 0; i < this->n; i++)
	{
		tiles[i] = new int[this->n];
		for (int j = 0; j < this->n; j++)
		{
			if (i == this->iTargetZero && j == this->jTargetZero) {
				tiles[i][j] = 0;
			}
			else {
				tiles[i][j] = counter;
				counter++;
			}
		}
	}

	this->goalState = new Board(tiles, this->n, this->iTargetZero, this->jTargetZero);
}