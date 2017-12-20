#include "App.h"

App::App(World *world, unsigned int width, unsigned int height) {
    this->world = world;
    this->width = width;
    this->height = height;
}

thread App::run() {
    printf("starting up...\n");

    thread thread([this]() {
        RenderWindow window(VideoMode(this->width, this->height), "Conway's Game of Life");
        window.setVerticalSyncEnabled(true);

        printf("started.\n");

        while (window.isOpen()) {
            Event event{};
            while (window.pollEvent(event)) {
                if (event.type == Event::KeyPressed) {
                    printf("randomizing...\n");
                    this->world->getBoard()->randomize();
                }

                if (event.type == Event::Closed) {
                    window.close();
                }
            }

            this->world->tick();

            window.clear();

            for (int row = 0; row < world->getBoard()->getRows(); row++) {
                for (int col = 0; col < world->getBoard()->getColumns(); col++) {
                    Drawable *cell = this->createCell(row, col, this->world->getBoard()->getCellState(row, col));
                    window.draw(*cell);
                    delete (cell);
                }
            }

            window.display();
        }
        printf("exiting.\n");
    });

    return thread;
}

Drawable *App::createCell(int row, int column, CellState cellState) {
    const float rowPos = (float) this->height / world->getBoard()->getRows() * row;
    const float colPos = (float) this->width / world->getBoard()->getColumns() * column;

    const float rowHeight = (float) this->height / world->getBoard()->getRows();
    const float colWidth = (float) this->width / world->getBoard()->getColumns();

    RectangleShape *rect = new RectangleShape(Vector2f(colWidth, rowHeight));
    rect->setPosition(colPos, rowPos);

    switch (cellState) {
        case alive:
            rect->setFillColor(Color::Green);
            break;
        case dead:
            rect->setFillColor(Color::Black);
            break;
    }

    return rect;
}
