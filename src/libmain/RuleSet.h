#ifndef GAMEOFLIFE_RULESET_H
#define GAMEOFLIFE_RULESET_H

#include "CellState.h"

class RuleSet {
public:
    CellState evaluateNewState(CellState currentState, unsigned int aliveNeighbors);
};

#endif //GAMEOFLIFE_RULESET_H
