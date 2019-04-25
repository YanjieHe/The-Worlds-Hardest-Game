#ifndef AI_HPP
#define AI_HPP
#include "BPNeuralNetwork.hpp"
#include "State.hpp"
#include <Eigen/Cholesky>
#include <random>
#include <vector>

class Choice
{
  public:
    int direction;
    double score;
    Choice() : direction{0}, score{0}
    {
    }
    Choice(int direction, double score) : direction{direction}, score{score}
    {
    }
};

class AI
{
  public:
    int numOfInput;
    std::vector<std::vector<double>> DNAList;
    std::vector<double> scoreList;
    int networkIndex = 0;
    std::mt19937 generator;
    std::uniform_real_distribution<double> distribution;
    BPNeuralNetwork network;

    AI(int numOfInput, int sizeOfPopulation);
    void UpdateScore(double score);
    void Select();
    void Crossover(int a, int b);
    void Mutate(int index);
    void NextNetwork();
    static int ManhattanDistance(int x0, int y0, int x1, int y1);
    std::vector<double> MakeDecision(State& state);
    static std::vector<double> GetDNA(BPNeuralNetwork& network);
    static void SetDNA(BPNeuralNetwork& network, std::vector<double>& DNA);
};

#endif // AI_HPP
