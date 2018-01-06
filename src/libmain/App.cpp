#include <cmath>
#include <numeric>
#include "App.h"
#include "SDLUtil.h"
#include "ChronoClock.h"

App::App(const shared_ptr<World> world, const string fontFilePath) :
        world(world) {

    if (SDL_Init(SDL_INIT_VIDEO)) {
        throw runtime_error("could not initialize SDL2");
    }

    if (TTF_Init()) {
        throw runtime_error("could not initialize SDL2_TTF");
    }

    this->bigFont = TTF_OpenFont(fontFilePath.c_str(), 44);
    this->smallFont = TTF_OpenFont(fontFilePath.c_str(), 32);

    if (this->bigFont == nullptr || this->smallFont == nullptr) {
        throw invalid_argument("could not load font, check if " + fontFilePath + " exists!");
    }
}

App::~App() {
    TTF_CloseFont(this->bigFont);
    TTF_CloseFont(this->smallFont);

    TTF_Quit();
    SDL_Quit();
}

thread App::run() {
    printf("starting up...\n");

    thread thread([this]() {
        SDL_Rect displayBounds{};

#if SDL_VERSION_ATLEAST(2, 0, 5)
        SDL_GetDisplayUsableBounds(0, &displayBounds);
#else
        SDL_GetDisplayBounds(0, &displayBounds);
#endif

        auto window = SDL_CreateWindow(
                "Conway's Game of Life",
                displayBounds.x,
                displayBounds.y,
                displayBounds.w,
                displayBounds.h,
                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );
        if (window == nullptr) {
            throw runtime_error("Could not create SDL window.");
        }

        SDL_GetWindowSize(window, &this->width, &this->height);

        auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            throw runtime_error("Could not create SDL renderer.");
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        printf("started.\n");

        mainLoop(window, renderer);

        printf("exiting.\n");

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    });

    return thread;
}

void App::mainLoop(SDL_Window *window, SDL_Renderer *renderer) {
    ChronoClock clock;
    bool quit = false;

    const unsigned int measureFrameCount = 60;
    vector<unsigned int> frameDurations;
    vector<unsigned int> tickDurations;
    vector<unsigned int> drawDurations;

    while (!quit) {
        frameDurations.emplace_back(duration_cast<microseconds>(clock.restart()).count());

        SDL_Event event{};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                            quit = true;
                            break;
                        default:
                            printf("randomizing...\n");
                            this->world->getBoard()->randomize();
                            break;
                    }
                    break;
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                            SDL_GetWindowSize(window, &this->width, &this->height);
                            break;
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        tickDurations.emplace_back(duration_cast<microseconds>(clock.measureDuration([this]() {
            this->world->tick();
        })).count());

        // Clear with black background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawDurations.emplace_back(duration_cast<microseconds>(clock.measureDuration([this, renderer]() {
            auto cellStates = world->getBoard()->getCellStates();
            this->renderCells(renderer, cellStates);
        })).count());

        auto frameDuration = accumulate(frameDurations.begin(), frameDurations.end(), 0U) / frameDurations.size();
        auto tickDuration = accumulate(tickDurations.begin(), tickDurations.end(), 0U) / tickDurations.size();
        auto drawDuration = accumulate(drawDurations.begin(), drawDurations.end(), 0U) / drawDurations.size();

        auto fpsText = "FPS: " + to_string((int) round(10e6 / frameDuration));
        drawText(renderer, 30, 30, this->bigFont, {255, 0, 255, 255}, fpsText);

        auto tickDurationText = "Δt World: " + to_string((unsigned int) tickDuration) + "us";
        drawText(renderer, 30, 80, this->smallFont, {255, 0, 0, 255}, tickDurationText);

        auto drawDurationText = "Δt Draw: " + to_string((unsigned int) drawDuration) + "us";
        drawText(renderer, 30, 120, this->smallFont, {255, 0, 0, 255}, drawDurationText);

        if (frameDurations.size() >= measureFrameCount) {
            frameDurations.erase(frameDurations.begin());
            tickDurations.erase(tickDurations.begin());
            drawDurations.erase(drawDurations.begin());
        }

        SDL_RenderPresent(renderer);
    }
}

void App::renderCells(SDL_Renderer *renderer, shared_ptr<Matrix2D<CellState>> &cellStates) {
    const unsigned int rows = cellStates->getRows();
    const unsigned int columns = cellStates->getColumns();

    const auto rowHeight = (int) round((float) this->height / rows);
    const auto colWidth = (int) round((float) this->width / columns);

    SDL_Rect rect{};

    // Draw living cells in green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            rect.x = column * colWidth;
            rect.y = row * rowHeight;
            rect.w = colWidth;
            rect.h = rowHeight;

            switch ((*cellStates)(row, column)) {
                case alive:
                    SDL_RenderFillRect(renderer, &rect);
                    break;
                case dead:
                    break;
            }
        }
    }
}
