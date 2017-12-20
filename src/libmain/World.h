#ifndef GAMEOFLIFE_WORLD_H
#define GAMEOFLIFE_WORLD_H

#include "Board.h"
#include "RuleSet.h"

#include <memory>

using namespace std;

class World {
private:
    const shared_ptr<Board> board1;
    const shared_ptr<Board> board2;
    const shared_ptr<RuleSet> ruleSet;

    shared_ptr<Board> currentBoard;
    shared_ptr<Board> nextBoard;

public:
    World(int rows, int columns, shared_ptr<RuleSet> ruleSet);

    const shared_ptr<Board> getBoard();

    void tick();
};

#endif //GAMEOFLIFE_WORLD_H
