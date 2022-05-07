#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

int getRandomIntRange(int min, int max);
int getRandomInt();

float getRandomFloatRange(float min, float max);
float getRandomFloat();

std::string getRandomStringRange(uint min, uint max);
std::string getRandomString();

/* ************************************************************************** */

void foldInt(const int &value, const void *n, void *product);
void foldFloat(const float &value, const void *n, void *sum);
void foldString(const std::string &value, const void *n, void *concatenation);

void mapInt(int &value, void *_);
void mapFloat(float &value, void *_);
void mapString(std::string &value, void *prefix);

/* ************************************************************************** */

void flushLine();

void handleInvalidInput();

enum Implementation
{
    Vector,
    Link
};

std::istream &operator>>(std::istream &input, Implementation &implementation);

enum DataType
{
    Int,
    Float,
    String
};

std::istream &operator>>(std::istream &input, DataType &dataType);

enum TraverseType
{
    PreOrder,
    PostOrder,
    InOrder,
    Breadth
};

std::istream &operator>>(std::istream &input, TraverseType &traverseType);

#endif