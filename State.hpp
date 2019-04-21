#ifndef STATE_HPP
#define STATE_HPP
#include <array>
#include <vector>
class State
{
  public:
    std::vector<double> positions;
    double left;
    double right;
    double up;
    double down;
    State();
    State(std::vector<double> positions, double left, double right, double up,
          double down);
};

#endif // STATE_HPP
