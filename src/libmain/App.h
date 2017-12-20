#ifndef GAMEOFLIFE_APP_H
#define GAMEOFLIFE_APP_H

#include "World.h"

#include <thread>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

typedef shared_ptr<shared_ptr<RectangleShape>[]> DRAWABLE_DIMENSION;

class App {
private:
    const shared_ptr<World> world;
    const unsigned int width;
    const unsigned int height;

    const shared_ptr<DRAWABLE_DIMENSION[]> drawables;

public:
    App(shared_ptr<World> world, unsigned int width, unsigned int height);

    thread run();

private:
    void updateCell(int row, int column, CellState cellState);
};

#endif //GAMEOFLIFE_APP_H
