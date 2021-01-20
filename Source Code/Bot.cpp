#include "Bot.h"
#include <iostream>

Bot::Bot(float speed) : curr_state(0), speed(speed) {}

Direction Bot::getTurn() {
    curr_state = (curr_state + 1) % 4;
    return Direction(curr_state);
}
bool Bot::addElapsedTime(float elapsedTime) {
    timer += elapsedTime * speed;
    if (timer > 1) {
        timer = 0;
        return true;
    }
    return false;
}
void Bot::setSpeed(float speed) {
    if (speed > 0.1)
        this->speed = speed;
    std::cout << "Bot speed: " << this->speed << "\n";
}
float Bot::getSpeed() {
    return speed;
}