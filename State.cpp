#include "State.hpp"

State::State()
{
}

State::State(std::vector<double> positions, std::array<double, 4> scores)
    : positions{positions}, scores{scores}
{
}
