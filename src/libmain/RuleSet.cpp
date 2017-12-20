#include "RuleSet.h"

CellState overPopulationRule(CellState currentState, unsigned int aliveNeighbors) {
    return (aliveNeighbors <= 3) ? currentState : dead;
}

CellState underPopulationRule(CellState currentState, unsigned int aliveNeighbors) {
    return aliveNeighbors >= 2 ? currentState : dead;
}

CellState reproductionRule(CellState currentState, unsigned int aliveNeighbors) {
    return aliveNeighbors == 3 ? alive : currentState;
}

CellState RuleSet::evaluateNewState(CellState currentState, unsigned int aliveNeighbors) {
    currentState = overPopulationRule(currentState, aliveNeighbors);
    currentState = underPopulationRule(currentState, aliveNeighbors);
    currentState = reproductionRule(currentState, aliveNeighbors);
    return currentState;
}
