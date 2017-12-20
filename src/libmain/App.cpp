#include "App.h"

App::App(shared_ptr<World> const world, const unsigned int width, const unsigned int height) :
        world(world),
        width(width),
        height(height),
        drawables(Matrix2D<shared_ptr<RectangleShape>>(world->getBoard()->getRows(), world->getBoard()->getColumns())) {

    for (int row = 0; row < world->getBoard()->getRows(); row++) {
        for (int column = 0; column < world->getBoard()->getColumns(); column++) {
            this->drawables(row, column) = make_shared<RectangleShape>();
        }
    }
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

            window->clear();

            this->updateCells();

            for (int row = 0; row < world->getBoard()->getRows(); row++) {
                for (int column = 0; column < world->getBoard()->getColumns(); column++) {
                    window->draw(*this->drawables(row, column));
                }
            }

            window->display();
        }
        printf("exiting.\n");
    });

    return thread;
}

void App::updateCells() {
    const float rowHeight = (float) this->height / world->getBoard()->getRows();
    const float colWidth = (float) this->width / world->getBoard()->getColumns();

    for (int row = 0; row < world->getBoard()->getRows(); row++) {
        for (int column = 0; column < world->getBoard()->getColumns(); column++) {
            const float posX = column * ((float) this->width / world->getBoard()->getColumns());
            const float posY = row * ((float) this->height / world->getBoard()->getRows());

            auto rect = this->drawables(row, column);
            rect->setPosition(posX, posY);
            rect->setSize(Vector2f(colWidth, rowHeight));

            switch (world->getBoard()->getCellState(row, column)) {
                case alive:
                    rect->setFillColor(Color::Green);
                    break;
                case dead:
                    rect->setFillColor(Color::Black);
                    break;
            }
        }
    }
}
