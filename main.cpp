#include "CellGrid.hpp"
#include "iostream"

constexpr ui FRAMERATE_LIMIT = 60U;
constexpr bool MOUSE_CURSOR_VISIBLE = true;
constexpr ui WIDTH = 1800;
constexpr ui HEIGHT = 1200;
constexpr ui NUMBER_OF_ROWS = 60U;
constexpr ui NUMBER_OF_COLS = 90U;
constexpr ui MAX_GENERATIONS = 100000U;


int main() {
    // Create new window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game Of Life");
    window.setFramerateLimit(FRAMERATE_LIMIT);
    window.setMouseCursorVisible(MOUSE_CURSOR_VISIBLE);

    CellGrid grid;
    bool run = false;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Right) {
                    run = false;
                    if (grid.getGeneration() < MAX_GENERATIONS)
                        grid.goToNextGeneration();
                }
                if (event.key.code == sf::Keyboard::Left) {
                    run = false;
                    grid.goToPreviousGeneration();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    run = false;
                    grid.goToLastGeneration();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    run = false;
                    grid.goToFirstGeneration();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    if (grid.getGeneration() < MAX_GENERATIONS) run = !run;
                }
                if (event.key.code == sf::Keyboard::Backspace) {
                    run = false;
                    grid.reset();
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (grid.isResetted() && event.mouseButton.button == sf::Mouse::Left) {
                    ui i = event.mouseButton.y / CELL_SIZE;
                    ui j = event.mouseButton.x / CELL_SIZE;
                    grid.invertLifeAtPosition(i, j);
                }
            }

            if (event.type == sf::Event::Resized) {
                // Update the view to the new size of the window
                window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
        }

        window.clear({255, 255, 255});
        grid.show(window);
        window.display();
        if (run) {
            if (grid.getGeneration() >= MAX_GENERATIONS) run = false;
            else grid.goToNextGeneration();
        }
    }

    return 0;
}
