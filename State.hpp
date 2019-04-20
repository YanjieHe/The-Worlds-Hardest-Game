#ifndef STATE_HPP
#define STATE_HPP
#include <array>
#include <vector>
class State
{
  public:
    std::vector<double> positions;
    std::array<double, 4> scores; // four directions: up, down, left, right
    State();
    State(std::vector<double> positions, std::array<double, 4> scores);
};

#endif // STATE_HPP
