#include "App.h"

App::App(const shared_ptr<World> world, const unsigned int width, const unsigned int height) :
        world(world),
        width(width),
        height(height),
        drawables(createCells(world->getBoard()->getCellStates())) {
}

thread App::run() {
    printf("starting up...\n");

    thread thread([this]() {
        auto window = make_shared<RenderWindow>(VideoMode(this->width, this->height), "Conway's Game of Life");
        window->setFramerateLimit(60);

        printf("started.\n");

        while (window->isOpen()) {
            Event event{};
            while (window->pollEvent(event)) {
                if (event.type == Event::KeyPressed) {
                    printf("randomizing...\n");
                    this->world->getBoard()->randomize();
                }

                if (event.type == Event::Closed) {
                    window->close();
                }
            }

            this->world->tick();

            auto cellStates = world->getBoard()->getCellStates();

            this->updateCells(cellStates);

            window->clear();

            for (int row = 0; row < cellStates->getRows(); row++) {
                for (int column = 0; column < cellStates->getColumns(); column++) {
                    window->draw((*this->drawables)(row, column));
                }
            }

            window->display();
        }
        printf("exiting.\n");
    });

    return thread;
}

shared_ptr<Matrix2D<RectangleShape>> App::createCells(shared_ptr<Matrix2D<CellState>> cellStates) {
    const unsigned int rows = cellStates->getRows();
    const unsigned int columns = cellStates->getColumns();

    return make_shared<Matrix2D<RectangleShape>>(rows, columns);
}

void App::updateCells(shared_ptr<Matrix2D<CellState>> cellStates) {
    const unsigned int rows = cellStates->getRows();
    const unsigned int columns = cellStates->getColumns();

    const float rowHeight = (float) this->height / rows;
    const float colWidth = (float) this->width / columns;

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            const float posX = column * ((float) this->width / columns);
            const float posY = row * ((float) this->height / rows);

            auto &&rect = (*this->drawables)(row, column);
            rect.setPosition(posX, posY);
            rect.setSize(Vector2f(colWidth, rowHeight));

            switch ((*cellStates)(row, column)) {
                case alive:
                    rect.setFillColor(Color::Green);
                    break;
                case dead:
                    rect.setFillColor(Color::Black);
                    break;
            }
        }
    }
}
