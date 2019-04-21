#include "State.hpp"

State::State()
{
}

State::State(std::vector<int> positions, std::array<double, 4> actions)
    : positions{positions}, actions{actions}, choice{-1}
{
}
