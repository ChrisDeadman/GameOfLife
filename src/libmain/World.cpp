#include "World.h"

using namespace std;

World::World(const unsigned int rows, const unsigned int columns, const shared_ptr<RuleSet> ruleSet, const shared_ptr<WorkerPool> workerPool) :
        board1(make_shared<Board>(rows, columns)),
        board2(make_shared<Board>(rows, columns)),
        ruleSet(ruleSet),
        workerPool(workerPool) {

    this->currentBoard = this->board1;
    this->nextBoard = this->board2;

    auto seed = time(nullptr);
    this->currentBoard->randomize(seed);
    this->nextBoard->randomize(seed + 1);
}

const shared_ptr<Board> World::getBoard() {
    return this->currentBoard;
}

void World::tick() {
    auto currentCellStates = this->currentBoard->getCellStates();
    auto nextCellStates = this->nextBoard->getCellStates();

    auto rows = currentCellStates->getRows();
    auto columns = currentCellStates->getColumns();

    this->workerPool->parallel_for(0U, rows, [&](unsigned int firstRow, unsigned int nextRow) {
        for (int row = firstRow; row < nextRow; row++) {
            for (int col = 0; col < columns; col++) {
                auto aliveNeighbors = this->currentBoard->getAliveNeighbors(row, col);
                auto currentState = (*currentCellStates)(row, col);
                (*nextCellStates)(row, col) = this->ruleSet->evaluateNewState(currentState, aliveNeighbors);
            }
        }
    });

    auto oldBoard = this->currentBoard;
    this->currentBoard = this->nextBoard;
    this->nextBoard = oldBoard;
}
