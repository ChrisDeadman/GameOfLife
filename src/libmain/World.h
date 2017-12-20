#ifndef GAMEOFLIFE_WORLD_H
#define GAMEOFLIFE_WORLD_H

#include "Board.h"
#include "RuleSet.h"

class World {

private:
    RuleSet ruleSet;

    Board *board1;
    Board *board2;
    Board *currentBoard;
    Board *nextBoard;

public:

    World(int rows, int columns, RuleSet ruleSet);

    virtual ~World();

    Board *getBoard();

    void tick();
};

#endif //GAMEOFLIFE_WORLD_H
