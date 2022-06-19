#include "CellGrid.hpp"
#include "font.hpp"


CellGrid::CellGrid() {
    if (!m_font.loadFromMemory(Air_Americana_ttf, Air_Americana_ttf_size))
        throw std::runtime_error("Cannot find Air Americana font!");
    m_cells.push_back({});
    m_iterator = m_cells.begin();
}

ui CellGrid::getGeneration() const {
    return m_generation;
}

bool CellGrid::isAliveAtPosition(int x, int y) const {
    return m_iterator->find({x, y}) != m_iterator->end();
}

bool CellGrid::isEmpty() const {
    return m_iterator->empty();
}

void CellGrid::invertLifeAtPosition(ui x, ui y) {
    if (isAliveAtPosition(x, y)) {
        m_iterator->erase({x, y});
        return;
    }
    m_iterator->insert({x, y});
}

void CellGrid::goToNextGeneration() {
    if (m_generation < m_cells.size()-1) {
        ++m_iterator;
        ++m_generation;
        return;
    }

    cellMatrix newCells;
    for (auto it = m_iterator->begin(); it != m_iterator->end(); ++it) {
        cellCoors coors = *it;
        for (int x = coors.first-1; x <= coors.first+1; ++x) {
            for (int y = coors.second-1; y <= coors.second+1; ++y) {
                ui neighbours = countAdjacentSquares(x, y);
                if (isAliveAtPosition(x, y)) {
                    if (neighbours == 2U || neighbours == 3U) {
                        newCells.insert({x, y});
                    }
                } else if (neighbours == 3U) {
                    newCells.insert({x, y});
                }
            }
        }
    }

    m_cells.push_back(newCells);
    ++m_iterator;
    ++m_generation;
}

ui CellGrid::countAdjacentSquares(int i, int j) const {
    ui count = 0U;

    for (int x = i-1; x <= i+1; ++x) {
        for (int y = j-1; y <= j+1; ++y) {
            if (x == i && y == j) continue;
            if (isAliveAtPosition(x, y)) ++count;
        }
    }

    return count;
}

void CellGrid::show(sf::RenderWindow& window) const {
    sf::Vector2u size = window.getSize();

    for (ui i = 0U; i < size.y / CELL_SIZE + 1; ++i) {
        for (ui j = 0U; j < size.x / CELL_SIZE + 1; ++j) {
            sf::RectangleShape square({CELL_SIZE, CELL_SIZE});
            square.setOutlineColor({128, 128, 128});
            square.setOutlineThickness(1);
            square.setFillColor((isAliveAtPosition(i, j))? sf::Color::Black: sf::Color::White);
            square.setPosition({(float) j * CELL_SIZE, (float) i * CELL_SIZE});
            window.draw(square);
        }
    }

    sf::Text generationText;
    generationText.setFont(m_font);
    generationText.setFillColor({255, 0, 0});
    generationText.setString(std::to_string(m_generation));
    generationText.setPosition({10, 10});
    window.draw(generationText);
}

void CellGrid::reset() {
    cellMatrix first = m_cells.front();
    m_cells.clear();
    m_cells.push_back(first);
    m_iterator = m_cells.begin();
    m_generation = 0U;
}

void CellGrid::goToPreviousGeneration() {
    if (m_generation == 0U) return;
    --m_iterator;
    --m_generation;
}

void CellGrid::goToLastGeneration() {
    m_iterator = m_cells.end();
    --m_iterator;
    m_generation = m_cells.size()-1;
}

void CellGrid::goToFirstGeneration() {
    m_iterator = m_cells.begin();
    m_generation = 0U;
}

bool CellGrid::isResetted() const {
    return (m_cells.size() == 1);
}
