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

    Matrix2D<shared_ptr<CellState>> cellStates;

public:
    Board(unsigned int rows, unsigned int columns);

    const unsigned int getRows() const;

    const unsigned int getColumns() const;

    const CellState getCellState(int row, int column);

    void setCellState(int row, int column, CellState state);

    const unsigned int getAliveNeighbors(int row, int column);

    void randomize();
};

#endif //GAMEOFLIFE_BOARD_H
