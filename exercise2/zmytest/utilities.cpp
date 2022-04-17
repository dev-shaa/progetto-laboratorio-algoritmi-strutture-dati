#include <iostream>
#include <functional>
#include <string>
#include <random>
#include <algorithm>

int GetRandomInt(int min, int max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

int GetRandomInt()
{
    return GetRandomInt(0, 100);
}

int GetIntFromString(const std::string &value)
{
    return std::stoi(value);
}

float GetRandomFloat(float min, float max)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(min, max);

    return dist(rng);
}

float GetRandomFloat()
{
    return GetRandomFloat(0, 100);
}

float GetFloatFromString(const std::string &value)
{
    return std::stof(value);
}

std::string GetRandomString(uint min, uint max)
{
    std::random_device rd;
    std::mt19937 generator(rd());

    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::shuffle(alphabet.begin(), alphabet.end(), generator);

    return alphabet.substr(0, GetRandomInt(min, max));
}

std::string GetRandomString()
{
    return GetRandomString(1, 32);
}

std::string GetSameString(const std::string &value)
{
    return value;
}

void FlushInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
