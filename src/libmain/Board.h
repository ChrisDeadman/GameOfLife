#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H

#include "CellState.h"
#include "Matrix2D.h"

#include <memory>

using namespace std;

class Board {
private:
    const unsigned int rows;
    const unsigned int columns;

    shared_ptr<Matrix2D<CellState>> cellStates;

public:
    Board(unsigned int rows, unsigned int columns);

    Board(const Board &that) = delete; // Forbid copying

    const shared_ptr<Matrix2D<CellState>> getCellStates();

    const unsigned int getAliveNeighbors(int row, int column);

    void randomize();
};

#endif //GAMEOFLIFE_BOARD_H
