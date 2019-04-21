#ifndef AI_HPP
#define AI_HPP
#include "BPNeuralNetwork.hpp"
#include "State.hpp"
#include <Eigen/Cholesky>
#include <vector>
class Choice
{
  public:
    int direction;
    double score;
    Choice(int direction, double score) : direction{direction}, score{score}
    {
    }
};

class AI
{
  public:
    std::vector<State> states;
    std::vector<std::vector<State>> data;
    BPNeuralNetwork network;
    double alpha = 0.9;
    AI(int numOfInput);
    void AddState(State state);
    double ComputeScore(State& lastState, State& currentState);
    static int ManhattanDistance(int x0, int y0, int x1, int y1);
    void Update(double score);
    void StartNewRound();
    std::vector<double> MakeDecision(State& state);
};

#endif // AI_HPP
