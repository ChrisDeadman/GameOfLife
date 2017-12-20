#ifndef GAMEOFLIFE_APP_H
#define GAMEOFLIFE_APP_H

#include "World.h"

#include <thread>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class App {
private:
    World *world;
    unsigned int width;
    unsigned int height;

public:
    App(World *world, unsigned int width, unsigned int height);

    thread run();

private:
    Drawable *createCell(int row, int column, CellState cellState);
};

#endif //GAMEOFLIFE_APP_H
