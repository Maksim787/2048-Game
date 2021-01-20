#include "BlockDrawer.h"
#include <iostream>
#include <cmath>


BlockDrawer::BlockDrawer(sf::RenderWindow& window, sf::Vector2f position, float gridSize, float blockSize, float lineThickness) :
    window(window), position(position), gridSize(gridSize), blockSize(blockSize), lineThickness(lineThickness) {
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Can not load font\n";
    }
    block.setSize(sf::Vector2f(blockSize, blockSize));

    text.setFont(font);
    text.setCharacterSize(static_cast<unsigned int>(blockSize / 2));
    text.setFillColor(sf::Color::Black);
}
void BlockDrawer::drawBlock(int x, int y, int number) {
    sf::Color blockColor;
    switch (number) {
    case 0:
        blockColor = sf::Color(255, 255, 255);
        break;
    case 2:
        blockColor = sf::Color(238, 228, 218);
        break;
    case 4:
        blockColor = sf::Color(236, 224, 200);
        break;
    case 8:
        blockColor = sf::Color(242, 177, 121);
        break;
    case 16:
        blockColor = sf::Color(236, 141, 83);
        break;
    case 32:
        blockColor = sf::Color(246, 123, 96);
        break;
    case 64:
        blockColor = sf::Color(233, 86, 59);
        break;
    case 128:
        blockColor = sf::Color(243, 217, 107);
        break;
    case 256:
        blockColor = sf::Color(239, 210, 72);
        break;
    case 512:
        blockColor = sf::Color(228, 192, 42);
        break;
    case 1024:
        blockColor = sf::Color(227, 186, 20);
        break;
    case 2048:
        blockColor = sf::Color(236, 196, 0);
        break;
    case 4096:
        blockColor = sf::Color(254, 61, 62);
        break;
    default:
        blockColor = sf::Color(255, 32, 33);
        break;
    }

    block.setPosition(position + sf::Vector2f(static_cast<float>(x), static_cast<float>(y)) * blockSize);
    block.setFillColor(blockColor);
    window.draw(block);

    text.setPosition(position + sf::Vector2f(static_cast<float>(x), static_cast<float>(y)) * blockSize);
    text.setString(std::to_string(number));
    sf::FloatRect textRect = text.getGlobalBounds();
    text.move((blockSize - textRect.width) / 2, (blockSize - textRect.height) / 2);
    window.draw(text);
}
void BlockDrawer::drawLines() {
    sf::RectangleShape line;
    line.setFillColor(lineColor);
    line.setSize(sf::Vector2f(gridSize * blockSize, lineThickness));
    line.setPosition(0, -lineThickness / 2);
    for (float i = 0; i <= gridSize + 0.1; ++i) {
        window.draw(line);
        line.move(0, blockSize);
    }
    line.setSize(sf::Vector2f(lineThickness, gridSize * blockSize));
    line.setPosition(-lineThickness / 2, 0);
    for (float i = 0; i <= gridSize + 0.1; ++i) {
        window.draw(line);
        line.move(blockSize, 0);
    }
}

void BlockDrawer::makeRGB(int& rgbValue) {
    rgbValue = std::max(std::min(rgbValue, 255), 0);
}
