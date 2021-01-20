#include "GlobalObjects.h"
#include <iostream>

Point::Point(int x, int y) : x(x), y(y) {}

void print(sf::Vector2f v) {
    std::cout << v.x << " " << v.y << "\n";
}
void print(std::vector<std::vector<int>> grid) {
    for (size_t y = 0; y < grid.size(); ++y) {
        std::copy(grid[y].begin(), grid[y].end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
    }
}