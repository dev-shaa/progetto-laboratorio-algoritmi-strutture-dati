#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

int getRandomIntRange(int min, int max);
int getRandomInt();

double getRandomDoubleRange(double min, double max);
double getRandomDouble();

std::string getRandomStringRange(uint min, uint max);
std::string getRandomString();

/* ************************************************************************** */

void foldInt(const int &value, const void *n, void *product);
void foldDouble(const double &value, const void *n, void *sum);
void foldString(const std::string &value, const void *n, void *concatenation);

/* ************************************************************************** */

void flushLine();
void handleInvalidInput();

#endif