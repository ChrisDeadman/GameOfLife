#include "RuleSet.h"

CellState overPopulationRule(const CellState currentState, const unsigned int aliveNeighbors) {
    return (aliveNeighbors <= 3) ? currentState : dead;
}

CellState underPopulationRule(const CellState currentState, const unsigned int aliveNeighbors) {
    return aliveNeighbors >= 2 ? currentState : dead;
}

CellState reproductionRule(const CellState currentState, const unsigned int aliveNeighbors) {
    return aliveNeighbors == 3 ? alive : currentState;
}

CellState RuleSet::evaluateNewState(const CellState currentState, const unsigned int aliveNeighbors) {
    CellState newState = currentState;
    newState = overPopulationRule(newState, aliveNeighbors);
    newState = underPopulationRule(newState, aliveNeighbors);
    newState = reproductionRule(newState, aliveNeighbors);
    return newState;
}
