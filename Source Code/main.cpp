#include "SFML/Graphics.hpp"
#include "GlobalObjects.h"
#include "BlockDrawer.h"
#include "Grid.h"
#include "Bot.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(screenX), static_cast<unsigned int>(screenY)), "2048");
    const float blockSize = 100;
    const float lineThickness = 10;
    window.setFramerateLimit(50);
    while (window.isOpen()) {
        std::cout << "Starting game!\n";
        bool gameOver = false;
        bool pause = false;
        bool useAI = false;
        sf::Clock clock;
        BlockDrawer blockDrawer(window, sf::Vector2f(0, 0), static_cast<int>(screenX / blockSize), blockSize, lineThickness);
        Grid grid(window, blockDrawer, static_cast<int>(screenX / blockSize), gameOver, pause);
        Bot bot(2);
        while (window.isOpen() && (!gameOver || pause)) {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                //case sf::Event::LostFocus:
                //    pause = true;
                //    break;
                //case sf::Event::GainedFocus:
                //    pause = false;
                //    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::R:
                        gameOver = true;
                        break;
                    case sf::Keyboard::P:
                    case sf::Keyboard::Space:
                        pause = !pause;
                        break;
                    case sf::Keyboard::A:
                        useAI = !useAI;
                        break;
                    case sf::Keyboard::U:
                        grid.undo();
                        break;
                    case sf::Keyboard::Left:
                        grid.move(Direction::Left);
                        break;
                    case sf::Keyboard::Right:
                        grid.move(Direction::Right);
                        break;
                    case sf::Keyboard::Up:
                        grid.move(Direction::Up);
                        break;
                    case sf::Keyboard::Down:
                        grid.move(Direction::Down);
                        break;
                    }
                    break;
                }
            }
            float elapsedTime = clock.restart().asSeconds();
            if (pause) continue;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) bot.setSpeed(bot.getSpeed() * 1.03);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) bot.setSpeed(bot.getSpeed() * 0.97);
            if (useAI && bot.addElapsedTime(elapsedTime)) grid.move(bot.getTurn());
            window.clear();
            grid.draw();
            window.display();
        }
    }

    return 0;
}