#include "App.h"

const int NUM_ROWS = 216;
const int NUM_COLUMNS = 384;

int main() {
    const shared_ptr<RuleSet> ruleSet = make_shared<RuleSet>();
    const shared_ptr<World> world = make_shared<World>(NUM_ROWS, NUM_COLUMNS, ruleSet);
    const VideoMode videoMode = VideoMode::getDesktopMode();

    App app(world, videoMode.width, videoMode.height);

    auto thread = app.run();
    thread.join();

    return 0;
}
