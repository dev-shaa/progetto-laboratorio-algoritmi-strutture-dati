#include <iostream>
#include <functional>
#include <string>
#include <random>
#include <algorithm>
#include "./utilities.hpp"

#define INVALID_INPUT_MSG "invalid input\n"

/* ************************************************************************** */

int getRandomIntRange(int min, int max)
{
    std::default_random_engine gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}

int getRandomInt()
{
    return getRandomIntRange(0, 100);
}

double getRandomDoubleRange(double min, double max)
{
    std::default_random_engine gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(min, max);

    return dist(gen);
}

double getRandomDouble()
{
    return getRandomDoubleRange(0.0, 100.0);
}

std::string getRandomStringRange(uint min, uint max)
{
    std::mt19937 generator(std::random_device{}());
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::shuffle(alphabet.begin(), alphabet.end(), generator);

    return alphabet.substr(0, getRandomIntRange(min, max));
}

std::string getRandomString()
{
    return getRandomStringRange(1, 16);
}

/* ************************************************************************** */

void foldInt(const int &value, const void *n, void *product)
{
    if (value < *((int *)n))
        *((int *)product) *= value;
}

void foldDouble(const double &value, const void *n, void *sum)
{
    if (value > *((int *)n))
        *((double *)sum) += value;
}

void foldString(const std::string &value, const void *n, void *concatenation)
{
    if (value.size() <= *((int *)n))
        (*(std::string *)concatenation) += value;
}

/* ************************************************************************** */

void flushLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void handleInvalidInput()
{
    flushLine();
    std::cerr << INVALID_INPUT_MSG;
}
