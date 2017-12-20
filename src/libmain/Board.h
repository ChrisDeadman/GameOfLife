#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H

#include "CellState.h"

#include <memory>

using namespace std;

typedef unique_ptr<CellState[]> CELL_STATE_DIMENSION;

class Board {
private:
    const int rows;
    const int columns;

    const unique_ptr<CELL_STATE_DIMENSION[]> cellStates;

public:
    Board(int rows, int columns);

    const int getRows() const;

    const int getColumns() const;

    const CellState getCellState(int row, int column);

    void setCellState(int row, int column, CellState state);

    const unsigned int getAliveNeighbors(int row, int column);

    void randomize();
};

#endif //GAMEOFLIFE_BOARD_H
