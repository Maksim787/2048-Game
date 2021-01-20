#include "Grid.h"
#include "GlobalObjects.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstdlib>

Grid::Grid(sf::RenderWindow& window, BlockDrawer& blockDrawer, int gridSize, bool& gameOver, bool& pause) :
    blockDrawer(blockDrawer), gameOver(gameOver), pause(pause) {
    grid = std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));
}
void Grid::transpose() {
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = y + 1; x < grid.size(); ++x) {
            std::swap(grid[y][x], grid[x][y]);
        }
    }
}
void Grid::reverse() {
    for (size_t y = 0; y < grid.size(); ++y) {
        std::reverse(grid[y].begin(), grid[y].end());
    }
}
void Grid::move(enum Direction direction) {
    if (pause)
        return;
    if (!gameOver)
        history.setState(getState());
    bool doTranspose = false;
    bool doReverse = false;
    if (direction == Direction::Up || direction == Direction::Down)
        doTranspose = true;
    if (direction == Direction::Right || direction == Direction::Down)
        doReverse = true;
    if (doTranspose)
        transpose();
    if (doReverse)
        reverse();

    for (size_t y = 0; y < grid.size(); ++y) {
        std::vector<int> numbers;
        std::copy_if(grid[y].begin(), grid[y].end(), std::back_inserter(numbers), [](int el) { return el != 0; });
        std::for_each(grid[y].begin(), grid[y].end(), [](int& el) { el = 0; });
        std::vector<int> new_numbers;
        if (!numbers.empty()) {
            new_numbers.push_back(numbers[0]);
            bool addedDuplicate = false;
            for (size_t i = 1; i < numbers.size(); ++i) {
                if (numbers[i] == new_numbers.back() && !addedDuplicate) {
                    new_numbers.back() *= 2;
                    addedDuplicate = true;
                }
                else {
                    new_numbers.push_back(numbers[i]);
                    addedDuplicate = false;
                }
            }
        }
        std::copy(new_numbers.begin(), new_numbers.end(), grid[y].begin());
    }

    if (doReverse)
        reverse();
    if (doTranspose)
        transpose();

    addBlock();
    //std::cout << "Grid:\n";
    //print(grid);
}
State Grid::getState() {
    return State(grid);
}
void Grid::setState(const State& state) {
    grid = state.grid;
    gameOver = false;
    pause = false;
}
void Grid::undo() {
    if (!history.empty())
        setState(history.getState());
}
void Grid::addBlock() {
    std::vector<Point> empty;
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid.size(); ++x) {
            if (grid[y][x] == 0) {
                empty.emplace_back(x, y);
            }
        }
    }
    if (empty.empty()) {
        gameOver = true;
        pause = true;
        return;
    }
    Point pos = empty[rand() % empty.size()];
    grid[pos.y][pos.x] = 2;
    //std::cout << "Added point at: Y: " << pos.y << " X: " << pos.x << "\n";
}
void Grid::draw() {
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid.size(); ++x) {
            blockDrawer.drawBlock(x, y, grid[y][x]);
        }
    }
    blockDrawer.drawLines();
}
