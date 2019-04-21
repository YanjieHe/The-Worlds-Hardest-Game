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
    if (!states.empty())
    {
        int n = static_cast<int>(states.size());
        cout << "states's scores = (";
        for (int i = n - 1; i >= 0; i--)
        {
            State& state = states.at(i);
            int index =
                std::max_element(state.actions.begin(), state.actions.end()) -
                state.actions.begin();
            state.actions.at(index) += score;
            cout << index << ": " << state.actions.at(index) << " ";
            score = alpha * score; // 0 <= alpha <= 1
        }
        cout << ")" << endl;
    }
}

void AI::StartNewRound()
{
    data.push_back(states);
    states.clear();
    VectorXd input(16);
    VectorXd output(4);
    for (auto& states : data)
    {
        for (auto& state : states)
        {
            for (int i = 0; i < state.positions.size(); i++)
            {
                input(i) = state.positions[i];
            }
            for (int i = 0; i < 4; i++)
            {
                output(i) = state.actions[i];
            }
            network.input = input;
            network.Backpropagation(output);
        }
    }
}

std::vector<double> AI::MakeDecision(State& state)
{
    using namespace std;
    VectorXd input(state.positions.size());
    cout << "( ";
    for (int s : state.positions)
    {
        cout << s << " ";
    }
    cout << ")" << endl;
    for (int i = 0; i < state.positions.size(); i++)
    {
        input(i) = state.positions[i];
    }
    network.input = input;
    network.FeedForward();
    VectorXd output(4);
    network.Backpropagation(output);
    vector<double> result{output(0), output(1), output(2), output(3)};
    for (auto item : result)
    {
        cout << item << " ";
    }
    cout << endl;
    return result;
}
