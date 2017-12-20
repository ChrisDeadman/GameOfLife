#include "World.h"

using namespace std;

World::World(const int rows, const int columns, shared_ptr<RuleSet> const ruleSet) :
        board1(make_shared<Board>(rows, columns)),
        board2(make_shared<Board>(rows, columns)),
        ruleSet(ruleSet) {

    this->currentBoard = this->board1;
    this->nextBoard = this->board2;
    
    this->currentBoard->randomize();
}

const shared_ptr<Board> World::getBoard() {
    return this->currentBoard;
}

void World::tick() {
    for (int row = 0; row < this->currentBoard->getRows(); row++) {
        for (int col = 0; col < this->currentBoard->getColumns(); col++) {
            auto aliveNeighbors = this->currentBoard->getAliveNeighbors(row, col);
            auto currentState = this->currentBoard->getCellState(row, col);
            auto newState = this->ruleSet->evaluateNewState(currentState, aliveNeighbors);
            this->nextBoard->setCellState(row, col, newState);
        }
    }

    auto oldBoard = this->currentBoard;
    this->currentBoard = this->nextBoard;
    this->nextBoard = oldBoard;
}
