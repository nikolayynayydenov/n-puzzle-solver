#include "Board.h"


Board::Board(vector<vector<int>> tiles, int n, int iZero, int jZero)
{
	this->tiles = tiles;
	this->n = n;

	if (iZero == -1 || jZero == -1) {
		this->setZero();
	}
	else {
		this->iZero = iZero;
		this->jZero = jZero;
	}
}

Board::Board(const Board& other)
{
	this->tiles = other.tiles;
	this->n = other.n;

	if (other.iZero == -1 || other.jZero == -1) {
		this->setZero();
	}
	else {
		this->iZero = other.iZero;
		this->jZero = other.jZero;
	}
}

Board::Board()
{
	this->iZero = 0;
	this->jZero = 0;
	this->n = 0;
	vector<vector<int>> v;
	this->tiles = v;
}

Board::~Board()
{
}

int Board::heuristic()
{
	int sum = 0;

	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			sum += manhattanDistance(i, j);
		}
	}

	return sum;
}

int Board::manhattanDistance(int i, int j)
{
	if (this->tiles[i][j] == 0) {
		return 0;
	}

	int targetI = floor((tiles[i][j] - 1) / this->n);
	int targetJ = (tiles[i][j] - 1) % this->n;

	return abs(i - targetI) + abs(j - targetJ);
}


pair<Board, string> Board::swipeLeft()
{
	if (!this->canSwipeLeft()) {
		throw exception("Can't swipe left");
	}

	vector<vector<int>> newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero][jZero + 1];
	newTiles[iZero][jZero + 1] = 0;

	Board b(newTiles, this->n);
	pair<Board, string> pr(b, "left");
	return pr;
}

pair<Board, string> Board::swipeRight()
{
	if (!this->canSwipeRight()) {
		throw exception("Can't swipe right");
	}

	vector<vector<int>> newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero][jZero - 1];
	newTiles[iZero][jZero - 1] = 0;

	Board b(newTiles, this->n);
	pair<Board, string> pr(b, "right");
	return pr;
}

pair<Board, string> Board::swipeUp()
{
	if (!this->canSwipeUp()) {
		throw exception("Can't swipe up");
	}

	vector<vector<int>> newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero + 1][jZero];
	newTiles[iZero + 1][jZero] = 0;

	Board b(newTiles, this->n);
	pair<Board, string> pr(b, "up");
	return pr;
}

pair<Board, string> Board::swipeDown()
{
	if (!this->canSwipeDown()) {
		throw exception("Can't swipe down");
	}

	vector<vector<int>> newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero - 1][jZero];
	newTiles[iZero - 1][jZero] = 0;

	Board b(newTiles, this->n);
	pair<Board, string> pr(b, "down");
	return pr;
}

vector<pair<Board, string>> Board::neighbours()
{
	vector<pair<Board, string>> neighbours;

	if (this->canSwipeLeft()) {
		neighbours.push_back(this->swipeLeft());
	}

	if (this->canSwipeRight()) {
		neighbours.push_back(this->swipeRight());
	}

	if (this->canSwipeUp()) {
		neighbours.push_back(this->swipeUp());
	}

	if (this->canSwipeDown()) {
		neighbours.push_back(this->swipeDown());
	}

	return neighbours;
}

bool Board::canSwipeLeft() const
{
	return this->jZero < n - 1;
}

bool Board::canSwipeRight() const
{
	return this->jZero > 0;
}

bool Board::canSwipeDown() const
{
	return this->iZero > 0;
}

bool Board::canSwipeUp() const
{
	return this->iZero < n - 1;
}

void Board::print()
{
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			cout << this->tiles[i][j] << " ";
		}

		cout << endl;
	}

	cout << endl;
}

void Board::setZero()
{
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			if (this->tiles[i][j] == 0) {
				this->iZero = i;
				this->jZero = j;
				return;
			}
		}
	}
	throw exception("This board does not contain zero");
}

vector<vector<int>> Board::copyTiles()
{
	vector<vector<int>> newTiles = tiles;

	return newTiles;
}

bool Board::isEqualTo(Board other)
{
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			if (this->tiles[i][j] != other.tiles[i][j]) {
				return false;
			}
		}
	}
	return true;
}

int Board::inversionsCount() const
{
	int index = 0;
	int count = 0;

	int* arr = new int[this->n * this->n];

	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			arr[index] = this->tiles[i][j];
			index++;
		}
	}

	for (int i = 0; i < this->n * this->n - 1; i++) {
		if (arr[i] == 0) {
			continue;
		}
		for (int j = i + 1; j < this->n * this->n; j++) {
			if (arr[j] == 0) {
				continue;
			}
			if (arr[i] > arr[j]) {
				count++;
			}
		}
	}

	delete[] arr;

	return count;
}