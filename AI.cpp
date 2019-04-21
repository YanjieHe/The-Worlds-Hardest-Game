#include "AI.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
;
AI::AI(int numOfInput)
    : network(numOfInput, {3, 3, 3}, 4), numOfInput{numOfInput}
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
    cout << "update: " << score << endl;
    int n = static_cast<int>(states.size());
    for (int i = n - 1; i >= 0; i--)
    {
        states[i].actions[states[i].choice] += score;

        score = score * discount;
    }
}

void AI::StartNewRound()
{
    VectorXd input(numOfInput);
    VectorXd output(4);
    for (int k = 0; k < 20; k++)
    {
        for (auto& state : states)
        {
            double max = *std::max_element(state.positions.begin(),
                                           state.positions.end());
            double min = *std::min_element(state.positions.begin(),
                                           state.positions.end());
            cout << "X = ";
            for (int i = 0; i < numOfInput; i++)
            {
                input(i) = state.positions[i] / 1000.0;
                cout << input(i) << " ";
            }
            cout << endl;
            //                Standardize(state.actions);
            cout << "Y: ";
            for (int i = 0; i < 4; i++)
            {
                output(i) = state.actions[i];
                cout << output(i) << " ";
            }
            cout << endl;
            network.input = input;
            network.Backpropagation(output);
        }
    }
    states.clear();
}

std::vector<double> AI::MakeDecision(State& state)
{
    VectorXd input(numOfInput);
    double max =
        *std::max_element(state.positions.begin(), state.positions.end());
    double min =
        *std::min_element(state.positions.begin(), state.positions.end());
    for (int i = 0; i < numOfInput; i++)
    {
        input(i) = state.positions[i] / 1000.0;
    }
    network.input = input;
    network.FeedForward();
    VectorXd output = network.output;
    std::vector<double> result(4);
    cout << "evaluate = ";
    for (int i = 0; i < 4; i++)
    {
        result[i] = output(i);
        cout << result[i] << " ";
    }
    cout << endl;
    return result;
}

void AI::Standardize(std::array<double, 4>& numbers)
{
    double max = *std::max_element(numbers.begin(), numbers.end());
    double min = *std::min_element(numbers.begin(), numbers.end());
    for (int i = 0; i < numbers.size(); i++)
    {
        numbers[i] = (numbers[i] - min) / (max - min);
    }
}
