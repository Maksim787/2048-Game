#pragma once
#include "SFML/Graphics.hpp"
const float screenX = 500;
const float screenY = 500;

enum Direction : int { Up, Right, Down, Left };

struct Point {
    Point(int x, int y);
    int x, y;
};

void print(sf::Vector2f v);
void print(std::vector<std::vector<int>> grid);