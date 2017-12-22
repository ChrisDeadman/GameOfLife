#ifndef GAMEOFLIFE_APP_H
#define GAMEOFLIFE_APP_H

#include "World.h"
#include "Matrix2D.h"

#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

class App {
private:
    int width;
    int height;

    TTF_Font *bigFont;
    TTF_Font *smallFont;

    const shared_ptr<World> world;
public:
    App(shared_ptr<World> world, string fontFilePath);

    App(const App &that) = delete; // Forbid copying

    ~App();

    thread run();

private:
    void mainLoop(SDL_Window *pRenderer, SDL_Renderer *pSDL_renderer);

    void renderCells(SDL_Renderer *renderer, shared_ptr<Matrix2D<CellState>> &cellStates);
};

#endif //GAMEOFLIFE_APP_H
