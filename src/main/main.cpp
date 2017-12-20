#include "App.h"

const int NUM_ROWS = 216;
const int NUM_COLUMNS = 384;

int main() {
    World world(NUM_ROWS, NUM_COLUMNS, RuleSet());

    VideoMode videoMode = VideoMode::getDesktopMode();

    App app(&world, videoMode.width, videoMode.height);

    auto thread = app.run();

    thread.join();

    return 0;
}
