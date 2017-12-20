#include "World.h"

#include <random>

using namespace std;

World::World(int rows, int columns, RuleSet ruleSet) {
    this->ruleSet = ruleSet;
    this->board1 = new Board(rows, columns);
    this->board2 = new Board(rows, columns);
    this->currentBoard = this->board1;
    this->nextBoard = this->board2;

    this->currentBoard->randomize();
}

World::~World() {
    delete board1;
    delete board2;
}

Board *World::getBoard() {
    return this->currentBoard;
}

void World::tick() {
    for (int row = 0; row < this->currentBoard->getRows(); row++) {
        for (int col = 0; col < this->currentBoard->getColumns(); col++) {
            auto aliveNeighbors = this->currentBoard->getAliveNeighbors(row, col);
            auto currentState = this->currentBoard->getCellState(row, col);
            auto newState = this->ruleSet.evaluateNewState(currentState, aliveNeighbors);
            this->nextBoard->setCellState(row, col, newState);
        }
    }

    auto oldBoard = this->currentBoard;
    this->currentBoard = this->nextBoard;
    this->nextBoard = oldBoard;
}
