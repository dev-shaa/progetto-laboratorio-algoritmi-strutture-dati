#include <iostream>
#include <functional>
#include <string>
#include <random>
#include <algorithm>

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

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}