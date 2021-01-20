#include "History.h"

State::State(const std::vector<std::vector<int>>& grid) : grid(grid) {}

void History::setState(const State& state) {
    states.push(state);
}
State History::getState() {
    State retVal = states.top();
    states.pop();
    return retVal;
}
bool History::empty() {
    return states.empty();
}