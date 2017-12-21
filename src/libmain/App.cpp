#include <cmath>
#include "App.h"
#include "TimeUtil.h"
#include "SFMLUtil.h"

App::App(const shared_ptr<World> world, const unsigned int width, const unsigned int height, const string fontFilePath) :
        world(world),
        width(width),
        height(height),
        fontFilePath(fontFilePath),
        rectangles(createCells(world->getBoard()->getCellStates())) {
}

thread App::run() {
    printf("starting up...\n");

    thread thread([this]() {
        auto window = make_shared<RenderWindow>(VideoMode(this->width, this->height), "Conway's Game of Life");
        window->setVerticalSyncEnabled(true);

        Font font;
        font.loadFromFile(this->fontFilePath);

        Text fpsText;
        fpsText.setFont(font);
        fpsText.setCharacterSize(44);
        fpsText.setPosition(30, 30);
        setColor(fpsText, Color::Magenta);

        Text tickDurationText;
        tickDurationText.setFont(font);
        tickDurationText.setCharacterSize(32);
        tickDurationText.setPosition(30, 80);
        setColor(tickDurationText, Color::Red);

        Text drawDurationText;
        drawDurationText.setFont(font);
        drawDurationText.setCharacterSize(32);
        drawDurationText.setPosition(30, 120);
        setColor(drawDurationText, Color::Red);

        Clock clock;

        printf("started.\n");

        while (window->isOpen()) {
            Time frameDuration = clock.restart();

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

            Time tickDuration = measureDuration(clock, [this]() {
                this->world->tick();
            });

            window->clear();

            Time drawDuration = measureDuration(clock, [this, window]() {
                auto cellStates = world->getBoard()->getCellStates();
                this->updateCells(cellStates);

                for (int row = 0; row < cellStates->getRows(); row++) {
                    for (int column = 0; column < cellStates->getColumns(); column++) {
                        window->draw((*this->rectangles)(row, column));
                    }
                }
            });

            fpsText.setString("FPS: " + to_string((int) round(1.f / frameDuration.asSeconds())));
            window->draw(fpsText);

            tickDurationText.setString(L"Δt World: " + to_string(tickDuration.asMilliseconds()) + "ms");
            window->draw(tickDurationText);

            drawDurationText.setString(L"Δt Draw: " + to_string(drawDuration.asMilliseconds()) + "ms");
            window->draw(drawDurationText);

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

            auto &&rect = (*this->rectangles)(row, column);
            rect.setPosition(posX, posY);
            rect.setSize(Vector2f(colWidth, rowHeight));

            switch ((*cellStates)(row, column)) {
                case alive:
                    rect.setFillColor(Color::Green);
                    break;
                case dead:
                    rect.setFillColor(Color::Transparent);
                    break;
            }
        }
    }
}
