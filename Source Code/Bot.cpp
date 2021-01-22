#include "Bot.h"
#include <algorithm>
#include <iostream>

AllDirection::AllDirection() : curr_state(0) {}
Direction AllDirection::getTurn(const std::vector<std::vector<int>>& grid) {
    curr_state = (curr_state + 1) % 4;
    return Direction(curr_state);
}

Direction MostDirection::getTurn(const std::vector<std::vector<int>>& grid) {
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
    int prev_num = 0;
    // left
    for (auto y = grid.begin(); y != grid.end(); ++y) {
        for (auto x = y->begin(); x != y->end(); ++x) {
            checkNumber(*x, prev_num, left);
        }
    }
    prev_num = 0;
    // right
    for (auto y = grid.begin(); y != grid.end(); ++y) {
        for (auto x = y->rbegin(); x != y->rend(); ++x) {
            checkNumber(*x, prev_num, right);
        }
    }
    prev_num = 0;
    // up
    for (size_t x = 0; x < grid.size(); ++x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            checkNumber(grid[y][x], prev_num, up);
        }
    }
    prev_num = 0;
    // down
    for (int x = static_cast<int>(grid.size()); x >= 0; --x) {
        for (size_t y = 0; y < grid.size(); ++y) {
            checkNumber(grid[y][x], prev_num, down);
        }
    }
    std::cout << "Up: " << up << " Right: " << right << " Left: " << left << " Down: " << down << "\n";
    std::cout << "Choice: ";
    if (up >= max(left, right, down)) {
        std::cout << "Up\n\n";
        return Direction::Up;
    }
    if (right >= max(left, down, up)) {
        std::cout << "Right\n\n";
        return Direction::Right;
    }
    if (left >= max(right, down, up)) {
        std::cout << "Left\n\n";
        return Direction::Left;
    }
    if (down >= max(left, right, up)) {
        std::cout << "Down\n\n";
        return Direction::Down;
    }
}
void MostDirection::checkNumber(int num, int& prev_num, int& direction) {
    if (num != 0 && num == prev_num) {
        direction += num;
        prev_num = 0;
    }
    else {
        prev_num = num;
    }
}
int MostDirection::max(int a, int b, int c) {
    return std::max(a, std::max(b, c));
}

Bot::Bot(Strategy& strategy, float speed) : strategy(strategy), timer(0), speed(speed) {}
Direction Bot::getTurn(const std::vector<std::vector<int>>& grid) {
    return strategy.getTurn(grid);
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