#include <iostream>
#include <functional>
#include <string>
#include <random>
#include <algorithm>
#include "utilities.hpp"

/* ************************************************************************** */

int getRandomIntRange(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

int getRandomInt()
{
    return getRandomIntRange(0, 100);
}

int getIntFromString(const std::string &value)
{
    return std::stoi(value);
}

float getRandomFloatRange(float min, float max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(min, max);

    return dist(rng);
}

float getRandomFloat()
{
    return getRandomFloatRange(0, 100);
}

float getFloatFromString(const std::string &value)
{
    return std::stof(value);
}

std::string getRandomStringRange(uint min, uint max)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::shuffle(alphabet.begin(), alphabet.end(), generator);

    return alphabet.substr(0, getRandomIntRange(min, max));
}

std::string getRandomString()
{
    return getRandomStringRange(1, 32);
}

std::string getSameString(const std::string &value)
{
    return value;
}

/* ************************************************************************** */

void foldInt(const int &value, const void *n, void *product)
{
    if (value < *((int *)n))
        *((int *)product) *= value;
}

void mapInt(int &value, void *_)
{
    value *= 3;
}

void foldFloat(const float &value, const void *n, void *sum)
{
    if (value > *((ulong *)n))
        *((float *)sum) += value;
}

void mapFloat(float &value, void *_)
{
    value *= value * value;
}

void foldString(const std::string &value, const void *n, void *concatenation)
{
    if (value.size() <= *((uint *)n))
        (*(std::string *)concatenation) += value;
}

void mapString(std::string &value, void *prefix)
{
    value = (*(std::string *)prefix) + value;
}

/* ************************************************************************** */

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::istream &operator>>(std::istream &input, Implementation &implementation)
{
    std::string stringInput;
    input >> stringInput;

    if (stringInput == "v")
        implementation = Vector;
    else if (stringInput == "l")
        implementation = Link;
    else
        input.setstate(std::ios::failbit);

    return input;
}

std::istream &operator>>(std::istream &input, DataType &dataType)
{
    std::string stringInput;
    input >> stringInput;

    if (stringInput == "i")
        dataType = Int;
    else if (stringInput == "f")
        dataType = Float;
    else if (stringInput == "s")
        dataType = String;
    else
        input.setstate(std::ios::failbit);

    return input;
}

std::istream &operator>>(std::istream &input, TraverseType &traverseType)
{
    std::string stringInput;
    input >> stringInput;

    if (stringInput == "pr")
        traverseType = PreOrder;
    else if (stringInput == "po")
        traverseType = PostOrder;
    else if (stringInput == "in")
        traverseType = InOrder;
    else if (stringInput == "br")
        traverseType = Breadth;
    else
        input.setstate(std::ios::failbit);

    return input;
}