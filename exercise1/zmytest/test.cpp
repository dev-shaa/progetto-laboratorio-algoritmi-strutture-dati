#include <iostream>
#include <functional>
#include <string>
#include <random>
#include <algorithm>
#include "test.hpp"
#include "../container/container.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"

#define VECTOR_INPUT "vector"
#define LIST_INPUT "list"
#define INT_INPUT "int"
#define FLOAT_INPUT "float"
#define STRING_INPUT "string"

/**
 * @brief Clears the input buffer, avoiding "overflowing" inputs.
 */
void FlushInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename Data>
void Contains(const lasd::TestableContainer<Data> &container, const Data &value)
{
    std::cout << value << " is" << (container.Exists(value) ? " " : " not ") << "contained." << std::endl;
}

template <typename Data>
void PrintAllAux(Data &value, void *_)
{
    std::cout << value << " ";
}

template <typename Data>
void PrintAll(lasd::MappableContainer<Data> &container)
{
    if (container.Empty())
        std::cout << "container is empty";
    else
        container.Map(&PrintAllAux<Data>, nullptr);

    std::cout << std::endl;
}

template <typename Data>
void VectorTest(ulong size, std::function<void(Data &, void *)> randomGenerator,
                std::function<Data(std::string)> dataConverter,
                std::function<void(Data &, void *)> mapFunctor,
                std::function<void(const lasd::FoldableContainer<Data> &, const ulong)> foldFunctor)
{
    lasd::Vector<Data> vec(size);
    std::string command, arg;

    vec.Map(randomGenerator, nullptr);

    std::cout << "available commands:" << std::endl
              << "- cancel" << std::endl
              << "- show ['all'/'front'/'back'/index]" << std::endl
              << "- check [value]" << std::endl
              << "- resize [size]" << std::endl
              << "- map (2*n for integers, n^2 for floats and uppercase for strings)" << std::endl
              << "- fold [n] (sum of integers smaller than n, product of floats bigger than n, concatenation of strings shorter or equal than n)" << std::endl;

    do
    {
        FlushInputBuffer();
        std::cout << ">";
        std::cin >> command;

        try
        {
            if (command == "cancel")
            {
                break;
            }
            else if (command == "show")
            {
                std::cin >> arg;

                if (arg == "all")
                    PrintAll(vec);
                else if (arg == "front")
                    std::cout << vec.Front() << std::endl;
                else if (arg == "back")
                    std::cout << vec.Back() << std::endl;
                else
                    std::cout << vec[std::stoul(arg)] << std::endl;
            }
            else if (command == "check")
            {
                std::cin >> arg;
                Data value = dataConverter(arg);
                Contains<Data>(vec, value);
            }
            else if (command == "resize")
            {
                std::cin >> arg;
                vec.Resize(std::stoul(arg));
            }
            else if (command == "map")
            {
                vec.Map(mapFunctor, nullptr);
            }
            else if (command == "fold")
            {
                std::cin >> arg;
                foldFunctor(vec, std::stoul(arg));
            }
            else
            {
                std::cout << command << ": no command found" << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "An exception occurred: " << e.what() << '\n';
        }
    } while (true);
}

template <typename Data>
void listTest(ulong size, std::function<Data()> randomGenerator,
              std::function<Data(std::string)> dataGetter,
              std::function<void(Data &, void *)> mapFunctor,
              std::function<void(const lasd::FoldableContainer<Data> &, const ulong)> foldFunctor)
{
    lasd::List<Data> list;
    std::string command, arg;

    for (ulong i = 0; i < size; i++)
        list.InsertAtFront(randomGenerator());

    std::cout << "available commands:" << std::endl
              << "- cancel" << std::endl
              << "- show ['all'/'front'/'back'/index]" << std::endl
              << "- check [value]" << std::endl
              << "- frontremove" << std::endl
              << "- pop" << std::endl
              << "- insert [value]" << std::endl
              << "- map (2*n for integers, n^2 for floats and uppercase for strings)" << std::endl
              << "- fold [n] (sum of integers smaller than n, product of floats bigger than n, concatenation of strings shorter or equal than n)" << std::endl;

    do
    {
        std::cout << ">";
        std::cin >> command;

        try
        {
            if (command == "cancel")
            {
                break;
            }
            else if (command == "show")
            {
                std::cin >> arg;

                if (arg == "all")
                    PrintAll(list);
                else if (arg == "front")
                    std::cout << list.Front() << std::endl;
                else if (arg == "back")
                    std::cout << list.Back() << std::endl;
                else
                    std::cout << list[std::stoul(arg)] << std::endl;
            }
            else if (command == "check")
            {
                std::cin >> arg;
                Data value = dataGetter(arg);
                Contains<Data>(list, value);
            }
            else if (command == "frontremove")
            {
                Data value = list.FrontNRemove();
                std::cout << "removed " << value << " from list" << std::endl;
            }
            else if (command == "pop")
            {
                list.RemoveFromFront();
            }
            else if (command == "insert")
            {
                std::string string_value;
                std::cin >> arg >> string_value;
                Data value = dataGetter(string_value);

                if (arg == "front")
                    list.InsertAtFront(value);
                else if (arg == "back")
                    list.InsertAtBack(value);
            }
            else if (command == "map")
            {
                list.Map(mapFunctor, nullptr);
            }
            else if (command == "fold")
            {
                std::cin >> arg;
                foldFunctor(list, std::stoul(arg));
            }
            else
            {
                std::cout << command << ": no command found" << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "An exception occurred: " << e.what() << '\n';
        }
    } while (true);
}

#pragma region INTEGER_TEST

int GetRandomInt()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

    return dist(rng);
}

void RandomIntAux(int &value, void *_)
{
    value = GetRandomInt();
}

void MapInt(int &value, void *_)
{
    value *= 2;
}

void FoldIntAux(const int &value, const void *n, void *sum)
{
    if (value < *((int *)n))
        *((int *)sum) += value;
}

void FoldInt(const lasd::FoldableContainer<int> &container, const ulong n)
{
    int sum = 0;
    container.Fold(&FoldIntAux, (void *)&n, (void *)&sum);
    std::cout << "sum of numbers: " << sum << std::endl;
}

int GetIntFromString(std::string value)
{
    return std::stoi(value);
}

#pragma endregion

#pragma region FLOAT_TEST

float GetRandomFloat()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0, 100);

    return dist(rng);
}

void RandomFloatAux(float &value, void *_)
{
    value = GetRandomFloat();
}

void MapFloat(float &value, void *_)
{
    value *= value; // x^2
}

void FoldFloatAux(const float &value, const void *n, void *product)
{
    if (value > *((ulong *)n))
        *((float *)product) *= value;
}

void FoldFloat(const lasd::FoldableContainer<float> &container, const ulong n)
{
    float product = 1.0f;
    container.Fold(&FoldFloatAux, (void *)&n, (void *)&product);
    std::cout << "product of numbers: " << product << std::endl;
}

float GetFloatFromString(std::string value)
{
    return std::stof(value);
}

#pragma endregion

#pragma region STRING_TEST

std::string GetRandomString()
{
    std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, GetRandomInt() % 32); // assumes 32 < number of characters in str
}

void RandomStringAux(std::string &value, void *_)
{
    value = GetRandomString();
}

void MapString(std::string &value, void *_)
{
    transform(value.begin(), value.end(), value.begin(), ::toupper); // uppercase
}

void FoldStringAux(const std::string &value, const void *n, void *concatenation)
{
    // concatenazione per le stringhe con lunghezza minore o uguale a n

    if (value.size() <= *((int *)n))
        (*(std::string *)concatenation) += value;
}

void FoldString(const lasd::FoldableContainer<std::string> &container, const ulong n)
{
    std::string concatenation;
    container.Fold(&FoldStringAux, (void *)&n, (void *)&concatenation);
    std::cout << "concatenation of strings: " << concatenation << std::endl;
}

std::string ReturnSame(const std::string &value)
{
    return value;
}

#pragma endregion

void myTest()
{
    ulong size;
    std::string inputBuffer, dataType;
    bool validInput;

    std::string command;

    std::cout << "available commands:" << std::endl
              << "- exit" << std::endl
              << "- create ['" << VECTOR_INPUT << "'/'" << LIST_INPUT << "'] ['" << INT_INPUT << "'/'" << FLOAT_INPUT << "'/'" << STRING_INPUT << "'] [size]" << std::endl
              << ">";

    do
    {
        validInput = true;

        FlushInputBuffer();
        std::cin >> inputBuffer;

        if (inputBuffer == "create")
        {
            if (inputBuffer == VECTOR_INPUT)
            {
                std::cin >> dataType >> size;

                if (dataType == INT_INPUT)
                    VectorTest<int>(size, &RandomIntAux, &GetIntFromString, &MapInt, &FoldInt);
                else if (dataType == FLOAT_INPUT)
                    VectorTest<float>(size, &RandomFloatAux, &GetFloatFromString, &MapFloat, &FoldFloat);
                else if (dataType == STRING_INPUT)
                    VectorTest<std::string>(size, &RandomStringAux, &ReturnSame, &MapString, &FoldString);
            }
            else if (inputBuffer == LIST_INPUT)
            {
                std::cin >> dataType >> size;

                if (dataType == INT_INPUT)
                    listTest<int>(size, &GetRandomInt, &GetIntFromString, &MapInt, &FoldInt);
                else if (dataType == FLOAT_INPUT)
                    listTest<float>(size, &GetRandomFloat, &GetFloatFromString, &MapFloat, &FoldFloat);
                else if (dataType == STRING_INPUT)
                    listTest<std::string>(size, &GetRandomString, &ReturnSame, &MapString, &FoldString);
            }
        }
    } while (inputBuffer != "exit");
}