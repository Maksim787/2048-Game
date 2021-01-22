#pragma once
#include "SFML/Graphics.hpp"
#include "BlockDrawer.h"
#include "History.h"

class Grid {
public:
    Grid(sf::RenderWindow& window, BlockDrawer& blockDrawer, int gridSize, bool& gameOver, bool& pause);
    void transpose();
    void reverse();
    void move(enum Direction direction);
    const std::vector<std::vector<int>>& getGrid();
    State getState();
    void setState(const State& state);
    void undo();
    void addBlock();
    void draw();
private:
    std::vector<std::vector<int>> grid;
    BlockDrawer& blockDrawer;
    History history;
    bool& gameOver;
    bool& pause;
};