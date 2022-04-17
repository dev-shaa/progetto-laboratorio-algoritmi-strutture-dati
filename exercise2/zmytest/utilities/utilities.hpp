#include <string>

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

/* ************************************************************************** */

int GetRandomInt();
int GetIntFromString(const std::string &value);

float GetRandomFloat();
float GetFloatFromString(const std::string &value);

std::string GetRandomString();
std::string GetSameString(const std::string &value);

void FlushInputBuffer();

/* ************************************************************************** */

#endif
