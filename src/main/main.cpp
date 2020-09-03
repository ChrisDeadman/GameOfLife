#include <SDL.h>
#include <WorkerPool.h>
#include "App.h"

const int NUM_ROWS = 108;
const int NUM_COLUMNS = 192;

int main(int argc, char *argv[]) {
    if (argc < 1) {
        return -1;
    }
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_INFO);

    string fontFilePath(argv[0]);
    fontFilePath = fontFilePath.substr(0, fontFilePath.find_last_of("/\\"));
    fontFilePath = fontFilePath.append("/OpenSans-Regular.ttf");

    auto numWorkers = WorkerPool::getConcurentThreadsSupported();
    if (numWorkers > 4) {
        numWorkers /= 2;
    }

    const shared_ptr<RuleSet> ruleSet = make_shared<RuleSet>();
    const shared_ptr<WorkerPool> workerPool = make_shared<WorkerPool>(numWorkers);
    const shared_ptr<World> world = make_shared<World>(NUM_ROWS, NUM_COLUMNS, ruleSet, workerPool);

    App app(world, fontFilePath);

    auto thread = app.run();
    thread.join();

    return 0;
}
