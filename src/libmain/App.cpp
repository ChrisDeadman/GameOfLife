#include "App.h"

App::App(shared_ptr<World> const world, const unsigned int width, const unsigned int height) :
        world(world),
        width(width),
        height(height),
        drawables(shared_ptr<DRAWABLE_DIMENSION[]>(new DRAWABLE_DIMENSION[world->getBoard()->getRows()])) {

    for (int row = 0; row < world->getBoard()->getRows(); row++) {
        this->drawables[row] = DRAWABLE_DIMENSION(new shared_ptr<RectangleShape>[world->getBoard()->getColumns()]);
        for (int column = 0; column < world->getBoard()->getColumns(); column++) {
            this->drawables[row][column] = make_shared<RectangleShape>();
        }
    }
}

thread App::run() {
    printf("starting up...\n");

    thread thread([this]() {
        RenderWindow window(VideoMode(this->width, this->height), "Conway's Game of Life");
        window.setFramerateLimit(60);

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
                for (int column = 0; column < world->getBoard()->getColumns(); column++) {
                    updateCell(row, column, this->world->getBoard()->getCellState(row, column));
                    window.draw(*this->drawables[row][column]);
                }
            }

            window.display();
        }
        printf("exiting.\n");
    });

    return thread;
}

void App::updateCell(const int row, const int column, const CellState cellState) {
    const float rowPos = (float) this->height / world->getBoard()->getRows() * row;
    const float colPos = (float) this->width / world->getBoard()->getColumns() * column;

    const float rowHeight = (float) this->height / world->getBoard()->getRows();
    const float colWidth = (float) this->width / world->getBoard()->getColumns();

    auto rect = this->drawables[row][column];
    rect->setSize(Vector2f(colWidth, rowHeight));
    rect->setPosition(colPos, rowPos);

    switch (cellState) {
        case alive:
            rect->setFillColor(Color::Green);
            break;
        case dead:
            rect->setFillColor(Color::Black);
            break;
    }
}
