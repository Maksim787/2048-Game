#pragma once
#include <vector>
#include <stack>

class State {
public:
    State(const std::vector<std::vector<int>>& grid);
    std::vector<std::vector<int>> grid;
};

class History {
public:
    void setState(const State& state);
    State getState();
    bool empty();
private:
    std::stack<State> states;
};

