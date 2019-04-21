#include "AI.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
AI::AI(int numOfInput) : network(numOfInput, {3, 3, 3}, 4)
{
}

void AI::AddState(State state)
{
    states.push_back(state);
}

int AI::ManhattanDistance(int x0, int y0, int x1, int y1)
{
    return std::abs(x0 - x1) + std::abs(y0 - y1);
}

void AI::Update(double score)
{
    using namespace std;
}

void AI::StartNewRound()
{
    data.push_back(states);
    states.clear();
}

std::vector<double> AI::MakeDecision(State& state)
{
    return {};
}
