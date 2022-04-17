#include <string>

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

/* ************************************************************************** */

int GetRandomInt();
// int GetRandomInt(int min, int max);
int GetIntFromString(const std::string &value);

float GetRandomFloat();
// float GetRandomFloat(float min, float max);
float GetFloatFromString(const std::string &value);

std::string GetRandomString();
// std::string GetRandomString(uint min, uint max);
std::string GetSameString(const std::string &value);

void FlushInputBuffer();

/* ************************************************************************** */

#endif
