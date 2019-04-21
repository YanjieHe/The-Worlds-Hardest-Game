#include "State.hpp"

State::State() : left{0}, right{0}, up{0}, down{0}
{
}

State::State(std::vector<double> positions, double left, double right,
             double up, double down)
    : positions{positions}, left{left}, right{right}, up{up}, down{down}
{
}
