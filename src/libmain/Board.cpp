#include "Board.h"

#include <random>

using namespace std;

Board::Board(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;

    this->cellStates = new CellState *[this->rows];
    for (int row = 0; row < this->rows; row++) {
        this->cellStates[row] = new CellState[this->columns];
        for (int column = 0; column < this->columns; column++) {
            this->cellStates[row][column] = dead;
        }
    }
}

Board::~Board() {
    delete this->cellStates;
}

int Board::getRows() {
    return rows;
}

int Board::getColumns() {
    return columns;
}

CellState Board::getCellState(int row, int column) {
    return this->cellStates[row][column];
}

void Board::setCellState(int row, int column, CellState state) {
    this->cellStates[row][column] = state;
}

unsigned int Board::getAliveNeighbors(int row, int column) {
    const int num_neighbors = 8;
    const int neighbors[num_neighbors][2] = {{row - 1, column - 1},
                                             {row - 1, column + 1},
                                             {row - 1, column},
                                             {row,     column - 1},
                                             {row,     column + 1},
                                             {row + 1, column},
                                             {row + 1, column + 1},
                                             {row + 1, column - 1}};

    unsigned int aliveNeighbors = 0;

    for (int idx = 0; idx < num_neighbors; idx++) {
        int r = neighbors[idx][0];
        int c = neighbors[idx][1];

        if ((r < 0 || r >= this->rows) ||
            (c < 0 || c >= this->columns)) {
            continue;
        }
        if (this->cellStates[r][c] == alive) {
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
            this->cellStates[row][column] = dis(gen) > 0 ? alive : dead;
        }
    }
}
