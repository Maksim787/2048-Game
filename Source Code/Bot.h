#pragma once
#include "GlobalObjects.h"
#include <vector>

class Strategy {
public:
    virtual Direction getTurn(const std::vector<std::vector<int>>& grid) = 0;
};

class AllDirection : public Strategy {
public:
    AllDirection();
    Direction getTurn(const std::vector<std::vector<int>>& grid);
private:
    int curr_state;
};

class MostDirection :public Strategy {
public:
    Direction getTurn(const std::vector<std::vector<int>>& grid);
private:
    void checkNumber(int num, int& prev_num, int& direction);
    int max(int a, int b, int c);
};

class Bot {
public:
    Bot(Strategy& strategy, float speed);
    Direction getTurn(const std::vector<std::vector<int>>& grid);
    bool addElapsedTime(float elapsedTime);
    void setSpeed(float speed);
    float getSpeed();
private:
    Strategy& strategy;
    float speed;
    float timer;
};

