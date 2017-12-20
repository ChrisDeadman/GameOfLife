#include "RuleSet.h"

const CellState overPopulationRule(const CellState currentState, const unsigned int aliveNeighbors) {
    return (aliveNeighbors <= 3) ? currentState : dead;
}

const CellState underPopulationRule(const CellState currentState, const unsigned int aliveNeighbors) {
    return aliveNeighbors >= 2 ? currentState : dead;
}

const CellState reproductionRule(const CellState currentState, const unsigned int aliveNeighbors) {
    return aliveNeighbors == 3 ? alive : currentState;
}

const CellState RuleSet::evaluateNewState(const CellState currentState, const unsigned int aliveNeighbors) {
    auto newState = currentState;
    newState = overPopulationRule(newState, aliveNeighbors);
    newState = underPopulationRule(newState, aliveNeighbors);
    newState = reproductionRule(newState, aliveNeighbors);
    return newState;
}
