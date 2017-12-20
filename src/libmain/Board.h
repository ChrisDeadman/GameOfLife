#ifndef GAMEOFLIFE_BOARD_H
#define GAMEOFLIFE_BOARD_H

#include "CellState.h"

class Board {

private:

    int rows;
    int columns;
    CellState **cellStates;

public:

    Board(int rows, int columns);

    virtual ~Board();

    int getRows();

    int getColumns();

    CellState getCellState(int row, int column);

    void setCellState(int row, int column, CellState state);

    unsigned int getAliveNeighbors(int row, int column);

    void randomize();
};

#endif //GAMEOFLIFE_BOARD_H
