#pragma once
#include "GlobalObjects.h"

class Bot {
public:
    Bot(float speed);
    Direction getTurn();
    bool addElapsedTime(float elapsedTime);
    void setSpeed(float speed);
    float getSpeed();
private:
    int curr_state;
    float speed;
    float timer;
};

