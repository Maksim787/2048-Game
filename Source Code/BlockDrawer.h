#pragma once
#include "SFML/Graphics.hpp"

class BlockDrawer {
public:
    BlockDrawer(sf::RenderWindow& window, sf::Vector2f position, float gridSize, float blockSize, float lineThickness);
    void drawBlock(int x, int y, int number);
    void drawLines();
    void makeRGB(int& rgbValue);
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape block;
    const sf::Vector2f position;
    const float gridSize;
    const float blockSize;
    const float lineThickness;
    const sf::Color lineColor = sf::Color(187, 174, 157);
};
