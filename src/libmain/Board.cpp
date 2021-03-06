#include "Board.h"

#include <random>

using namespace std;

Board::Board(const unsigned int rows, const unsigned int columns) :
        rows(rows),
        columns(columns),
        cellStates(make_shared<Matrix2D<CellState>>(rows, columns)) {

    for (unsigned int row = 0; row < this->rows; row++) {
        for (unsigned int column = 0; column < this->columns; column++) {
            this->cellStates->setValue(row, column, dead);
        }
    }
}

const shared_ptr<Matrix2D<CellState>> Board::getCellStates() {
    return this->cellStates;
}

unsigned int Board::getAliveNeighbors(const int row, const int column) {
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

        if ((r < 0 || (unsigned int)r >= this->rows) ||
            (c < 0 || (unsigned int)c >= this->columns)) {
            continue;
        }
        if (this->cellStates->getValue((unsigned int)r, (unsigned int)c) == alive) {
            ++aliveNeighbors;
        }
    }

    return aliveNeighbors;
}

void Board::randomize(long seed) {
    // standard mersenne_twister_engine
    mt19937 gen(static_cast<unsigned long>(seed));
    // uniform distribution >= 0 and <= 1
    uniform_int_distribution<> dis(0, 1);

    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int column = 0; column < columns; ++column) {
            auto state = dis(gen) > 0 ? alive : dead;
            this->cellStates->setValue(row, column, state);
        }
    }
}
