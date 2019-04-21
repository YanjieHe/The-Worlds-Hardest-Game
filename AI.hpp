#ifndef AI_HPP
#define AI_HPP
#include "State.hpp"
#include <vector>
class AI
{
  public:
    std::vector<State> states;
    AI();
    void AddState(State state);
};

#endif // AI_HPP
