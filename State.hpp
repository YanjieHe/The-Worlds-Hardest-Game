#ifndef STATE_HPP
#define STATE_HPP
#include <array>
#include <vector>

class State
{
  public:
    // The first and second integers are the coordinate of square position
    // The third and fourth integers are the coordinate of destination position
    std::vector<int> positions;
    std::array<double, 4> actions; // up, down, left, right

    State();
    State(std::vector<int> positions, std::array<double, 4> actions);
};

#endif // STATE_HPP
