#include "App.h"

const int NUM_ROWS = 108;
const int NUM_COLUMNS = 192;

int main(int argc, char *argv[]) {
    const shared_ptr<RuleSet> ruleSet = make_shared<RuleSet>();
    const shared_ptr<World> world = make_shared<World>(NUM_ROWS, NUM_COLUMNS, ruleSet);
    const VideoMode videoMode = VideoMode::getDesktopMode();

    string fontFilePath(argv[0]);
    fontFilePath = fontFilePath.substr(0, fontFilePath.find_last_of("/\\"));
    fontFilePath = fontFilePath.append("/OpenSans-Regular.ttf");

    App app(world, videoMode.width, videoMode.height, fontFilePath);

    auto thread = app.run();
    thread.join();

    return 0;
}
