#pragma once
#include "vector"
#include "list"
#include "set"
#include <SFML/Graphics.hpp>

typedef unsigned int ui;
typedef std::pair<int, int> cellCoors;
typedef std::set<cellCoors> cellMatrix;

constexpr ui CELL_SIZE = 20U;


class CellGrid {
    std::list<cellMatrix> m_cells;
    std::list<cellMatrix>::iterator m_iterator;
    ui m_generation = 0U;
    sf::Font m_font;

public:
    CellGrid();

    ui getGeneration() const;
    bool isAliveAtPosition(int, int) const;
    bool isResetted() const;
    bool isEmpty() const;

    void invertLifeAtPosition(ui, ui);

    void show(sf::RenderWindow&) const;
    void reset();

    void goToPreviousGeneration();
    void goToNextGeneration();
    void goToLastGeneration();
    void goToFirstGeneration();

private:
    ui countAdjacentSquares(int, int) const;
};
