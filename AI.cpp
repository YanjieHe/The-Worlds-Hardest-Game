#include "AI.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

AI::AI(int numOfInput, int sizeOfPopulation)
    : numOfInput{numOfInput}, DNAList(sizeOfPopulation),
      scoreList(sizeOfPopulation, 0), generator(std::random_device()()),
      distribution(0, 1), network(numOfInput, {9, 9, 9}, 4)
{
    srand(NULL);
    int n = GetDNA(network).size();
    for (int i = 0; i < sizeOfPopulation; i++)
    {
        DNAList.at(i) = vector<double>(n);
        for (int k = 0; k < n; k++)
        {
            DNAList[i][k] = distribution(generator) * 2 - 1;
        }
    }
    SetDNA(network, DNAList.at(networkIndex));
}

void AI::UpdateScore(double score)
{
    scoreList.at(networkIndex) = std::max(scoreList.at(networkIndex), score);
}

void AI::Select()
{
    int n = DNAList.size();
    vector<vector<double>> newList;
    for (int i = 0; i < n - 1; i = i + 2)
    {
        double sum = scoreList.at(i) + scoreList.at(i + 1);
        if (distribution(generator) <= scoreList.at(i) / sum)
        {
            newList.push_back(DNAList.at(i));
        }
        else
        {
            newList.push_back(DNAList.at(i + 1));
        }
    }
    for (int i = 0; i < n / 2; i++)
    {
        newList.push_back(newList.at(i));
    }
    DNAList = newList;
    for (int i = 0; i < n; i++)
    {
        scoreList.at(i) = 0;
    }
}

void AI::Crossover(int a, int b)
{
    std::vector<double>& A = DNAList.at(a);
    std::vector<double>& B = DNAList.at(b);
    int point			   = rand() % static_cast<int>(A.size());
    for (int i = 0; i <= point; i++)
    {
        double number = distribution(generator);
        double tb	 = A[i] * (1 - number) + B[i] * number;
        double ta	 = B[i] * (1 - number) + A[i] * number;
        A[i]		  = ta;
        B[i]		  = tb;
    }
}

void AI::Mutate(int index)
{
    // TO DO
    std::vector<double>& DNA = DNAList.at(index);
    double max				 = *(std::max_element(DNA.begin(), DNA.end()));
    double min				 = *(std::min_element(DNA.begin(), DNA.end()));
    for (int i = 0; i < DNA.size(); i++)
    {
        DNA[i] = distribution(generator) * (max - min);
    }
}

void AI::NextNetwork()
{
    networkIndex = (networkIndex + 1) % static_cast<int>(DNAList.size());
    SetDNA(network, DNAList.at(networkIndex));
}

std::vector<double> AI::MakeDecision(State& state)
{
    std::vector<double> input;
    for (int i = 0; i < state.positions.size(); i++)
    {
        input.push_back(state.positions[i]);
    }
    network.SetInput(input);
    network.FeedForward();
    auto output = network.GetOutput();
    vector<double> result;
    result.reserve(output.rows());
    for (int i = 0; i < output.rows(); i++)
    {
        result.push_back(output(i));
    }
    return result;
}

std::vector<double> AI::GetDNA(BPNeuralNetwork& network)
{
    std::vector<double> DNA;
    for (auto& matrix : network.weights)
    {
        for (int row = 0; row < matrix.rows(); row++)
        {
            for (int col = 0; col < matrix.cols(); col++)
            {
                DNA.push_back(matrix(row, col));
            }
        }
    }
    return DNA;
}

void AI::SetDNA(BPNeuralNetwork& network, std::vector<double>& DNA)
{
    int index = 0;

    for (auto& matrix : network.weights)
    {
        for (int row = 0; row < matrix.rows(); row++)
        {
            for (int col = 0; col < matrix.cols(); col++)
            {
                matrix(row, col) = DNA[index];
                index++;
            }
        }
    }
}

int AI::ManhattanDistance(int x0, int y0, int x1, int y1)
{
    return std::abs(x0 - x1) + std::abs(y0 - y1);
}
