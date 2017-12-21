#include "Board.h"

#include <random>

using namespace std;

Board::Board(const unsigned int rows, const unsigned int columns) :
        rows(rows),
        columns(columns),
        cellStates(make_shared<Matrix2D<CellState>>(rows, columns)) {

    for (int row = 0; row < this->rows; row++) {
        for (int column = 0; column < this->columns; column++) {
            (*this->cellStates)(row, column) = dead;
        }
    }
}

const shared_ptr<Matrix2D<CellState>> Board::getCellStates() {
    return this->cellStates;
}

const unsigned int Board::getAliveNeighbors(const int row, const int column) {
    const int neighbors[][2] = {{row - 1, column - 1},
                                {row - 1, column + 1},
                                {row - 1, column},
                                {row,     column - 1},
                                {row,     column + 1},
                                {row + 1, column},
                                {row + 1, column + 1},
                                {row + 1, column - 1}};

    unsigned int aliveNeighbors = 0;

    for (auto neighbor : neighbors) {
        int r = neighbor[0];
        int c = neighbor[1];

        if ((r < 0 || r >= this->rows) ||
            (c < 0 || c >= this->columns)) {
            continue;
        }
        if ((*this->cellStates)(r, c) == alive) {
            ++aliveNeighbors;
        }
    }

    return aliveNeighbors;
}

void Board::randomize() {
    random_device rd;                      // used to obtain a seed for the random number engine
    mt19937 gen(rd());                     // standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0, 1);  // uniform distribution >= 0 and <= 1

    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            (*this->cellStates)(row, column) = dis(gen) > 0 ? alive : dead;
        }
    }
}
