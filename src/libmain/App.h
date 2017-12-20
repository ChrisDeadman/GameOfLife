#ifndef GAMEOFLIFE_APP_H
#define GAMEOFLIFE_APP_H

#include "World.h"
#include "Matrix2D.h"

#include <thread>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class App {
private:
    const shared_ptr<World> world;
    const unsigned int width;
    const unsigned int height;

    Matrix2D<shared_ptr<RectangleShape>> drawables;

public:
    App(shared_ptr<World> world, unsigned int width, unsigned int height);

    thread run();

private:
    void updateCells();
};

#endif //GAMEOFLIFE_APP_H
