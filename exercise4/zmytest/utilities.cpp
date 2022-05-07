#include <iostream>
#include <functional>
#include <string>
#include <random>
#include <algorithm>
#include "utilities.hpp"

#define INVALID_INPUT_MSG "invalid input\n"

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

std::string getRandomStringRange(uint min, uint max)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::shuffle(alphabet.begin(), alphabet.end(), generator);

    return alphabet.substr(0, getRandomIntRange(min, max));
}

std::string getRandomString()
{
    return getRandomStringRange(1, 8);
}

/* ************************************************************************** */

void mapInt(int &value, void *_)
{
    value *= 3;
}

void mapFloat(float &value, void *_)
{
    value *= value * value;
}

void mapString(std::string &value, void *prefix)
{
    value = (*(std::string *)prefix) + value;
}

void foldInt(const int &value, const void *n, void *product)
{
    if (value < *((int *)n))
        *((int *)product) *= value;
}

void foldFloat(const float &value, const void *n, void *sum)
{
    if (value > *((int *)n))
        *((float *)sum) += value;
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

std::istream &operator>>(std::istream &input, Implementation &implementation)
{
    std::string stringInput;
    input >> stringInput;

    if (stringInput == "v" || stringInput == "vector")
        implementation = Vector;
    else if (stringInput == "l" || stringInput == "linked")
        implementation = Link;
    else
        input.setstate(std::ios::failbit);

    return input;
}

std::istream &operator>>(std::istream &input, DataType &dataType)
{
    std::string stringInput;
    input >> stringInput;

    if (stringInput == "i" || stringInput == "int")
        dataType = Int;
    else if (stringInput == "f" || stringInput == "float")
        dataType = Float;
    else if (stringInput == "s" || stringInput == "string")
        dataType = String;
    else
        input.setstate(std::ios::failbit);

    return input;
}

std::istream &operator>>(std::istream &input, TraverseType &traverseType)
{
    std::string stringInput;
    input >> stringInput;

    if (stringInput == "pr" || stringInput == "preorder")
        traverseType = PreOrder;
    else if (stringInput == "po" || stringInput == "postorder")
        traverseType = PostOrder;
    else if (stringInput == "in" || stringInput == "inorder")
        traverseType = InOrder;
    else if (stringInput == "br" || stringInput == "breadth")
        traverseType = Breadth;
    else
        input.setstate(std::ios::failbit);

    return input;
}