#include "Board.h"


Board::Board(int** tiles, int n, int iZero, int jZero)
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

Board::~Board()
{
	for (int i = 0; i < this->n; i++)
	{
		delete[] this->tiles[i];
	}

	delete[] this->tiles;
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


Board* Board::swipeLeft()
{
	if (!this->canSwipeLeft()) {
		throw exception("Can't swipe left");
	}

	int** newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero][jZero + 1];
	newTiles[iZero][jZero + 1] = 0;

	return new Board(newTiles, this->n);
}

Board* Board::swipeRight()
{
	if (!this->canSwipeRight()) {
		throw exception("Can't swipe right");
	}

	int** newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero][jZero - 1];
	newTiles[iZero][jZero - 1] = 0;

	return new Board(newTiles, this->n);
}

Board* Board::swipeUp()
{
	if (!this->canSwipeUp()) {
		throw exception("Can't swipe up");
	}

	int** newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero + 1][jZero];
	newTiles[iZero + 1][jZero] = 0;

	return new Board(newTiles, this->n);
}

Board* Board::swipeDown()
{
	if (!this->canSwipeDown()) {
		throw exception("Can't swipe down");
	}

	int** newTiles = this->copyTiles();
	newTiles[iZero][jZero] = newTiles[iZero - 1][jZero];
	newTiles[iZero - 1][jZero] = 0;

	return new Board(newTiles, this->n);
}

vector<Board*> Board::neighbours()
{
	vector<Board*> neighbours;

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

int** Board::copyTiles()
{
	int** newTiles = new int* [this->n];

	for (int i = 0; i < this->n; i++)
	{
		newTiles[i] = new int[this->n];
		for (int j = 0; j < this->n; j++)
		{
			newTiles[i][j] = this->tiles[i][j];
		}
	}

	return newTiles;
}

bool Board::isEqualTo(Board* other)
{
	for (int i = 0; i < this->n; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			if (this->tiles[i][j] != other->tiles[i][j]) {
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