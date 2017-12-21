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
    const String fontFilePath;

    shared_ptr<Matrix2D<RectangleShape>> rectangles;

public:
    App(shared_ptr<World> world, unsigned int width, unsigned int height, string fontFilePath);

    App(const App &that) = delete; // Forbid copying

    thread run();

private:
    shared_ptr<Matrix2D<RectangleShape>> createCells(shared_ptr<Matrix2D<CellState>> cellStates);

    void updateCells(shared_ptr<Matrix2D<CellState>> cellStates);
};

#endif //GAMEOFLIFE_APP_H
