#include "State.hpp"

State::State() : actions()
{
}

State::State(std::vector<int> positions, std::array<double, 4> actions)
    : positions{positions}, actions{actions}
{
}
