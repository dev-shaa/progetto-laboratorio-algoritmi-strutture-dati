// #include <iostream>
// #include <functional>
// #include <string>
// #include <random>
// #include <algorithm>

// #include "../vector/vector.hpp"
// #include "../queue/vec/queuevec.hpp"
// #include "../binarytree/binarytree.hpp"
// #include "../binarytree/vec/binarytreevec.hpp"

// using namespace std;

// /* ************************************************************************** */

// int getRandomIntRange(int min, int max)
// {
//     std::random_device dev;
//     std::mt19937 rng(dev());
//     std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

//     return dist(rng);
// }

// int getRandomInt()
// {
//     return getRandomIntRange(0, 100);
// }

// int getIntFromString(const std::string &value)
// {
//     return std::stoi(value);
// }

// float getRandomFloatRange(float min, float max)
// {
//     std::random_device dev;
//     std::mt19937 rng(dev());
//     std::uniform_real_distribution<> dist(min, max);

//     return dist(rng);
// }

// float getRandomFloat()
// {
//     return getRandomFloatRange(0, 100);
// }

// float getFloatFromString(const std::string &value)
// {
//     return std::stof(value);
// }

// std::string getRandomStringRange(uint min, uint max)
// {
//     std::random_device rd;
//     std::mt19937 generator(rd());

//     std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
//     std::shuffle(alphabet.begin(), alphabet.end(), generator);

//     return alphabet.substr(0, getRandomIntRange(min, max));
// }

// std::string getRandomString()
// {
//     return getRandomStringRange(1, 32);
// }

// std::string getSameString(const std::string &value)
// {
//     return value;
// }

// void flushInputBuffer()
// {
//     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
// }

// /* ************************************************************************** */

// void foldInt(const int &value, const void *n, void *product)
// {
//     if (value < *((int *)n))
//         *((int *)product) *= value;
// }

// void mapInt(int &value, void *_)
// {
//     value *= 3;
// }

// void foldFloat(const float &value, const void *n, void *sum)
// {
//     if (value > *((ulong *)n))
//         *((float *)sum) += value;
// }

// void mapFloat(float &value, void *_)
// {
//     value *= value * value;
// }

// void foldString(const string &value, const void *n, void *concatenation)
// {
//     if (value.size() <= *((uint *)n))
//         (*(string *)concatenation) += value;
// }

// void mapString(string &value, void *prefix)
// {
//     value = (*(string *)prefix) + value;
// }

// /* ************************************************************************** */

// template <typename Data>
// void printMap(const Data &value, void *_)
// {
//     cout << value << " ";
// }

// template <typename Data>
// void printTree(lasd::BinaryTree<Data> &tree)
// {
//     tree.Map(&printMap<int>, nullptr);
//     tree.MapPreOrder(&printMap<int>, nullptr);
//     tree.MapPostOrder(&printMap<int>, nullptr);
//     tree.MapInOrder(&printMap<int>, nullptr);
//     tree.MapBreadth(&printMap<int>, nullptr);
// }

// template <typename Data>
// lasd::BinaryTree<Data> *generateTree(ulong size, function<Data()> getRandomValue)
// {
//     lasd::Vector<Data> vec(size);

//     for (ulong i = 0; i < size; i++)
//         vec[i] = getRandomValue();

//     return new lasd::BinaryTreeVec<Data>(vec);
// }

// /* ************************************************************************** */

// void foo()
// {
//     lasd::BinaryTreeVec<int> tree;

//     cout << tree.Size() << endl;
//     cout << tree.Empty() << endl;

//     lasd::BinaryTreeVec cop(tree);

//     printTree<int>(cop);

//     lasd::BinaryTree<float> *f = generateTree<float>(10, &getRandomFloat);

//     cout << f->Exists(2) << endl;
// }

// #define EXIT_COMMAND 0
// #define VEC_INT 1
// #define VEC_FLT 2
// #define VEC_STR 3
// #define LNK_INT 4
// #define LNK_FLT 5
// #define LNK_STR 6

// void manualTest()
// {
//     int command;
//     ulong size;

//     do
//     {
//         try
//         {
//             flushInputBuffer();

//             // printManualTestHelp();
//             cout << ">";
//             cin >> command;

//             if (command != EXIT_COMMAND)
//             {
//                 cin >> size;
//                 // cin >> structure >> implementation >> dataType >> stringSize;
//                 // size = std::stoul(stringSize);

//                 // switch (structure)
//                 // {
//                 // case Structure::STACK:
//                 //     switch (dataType)
//                 //     {
//                 //     case DataType::INT:
//                 //         stackTest<int>(implementation, size, &getRandomInt, &getIntFromString);
//                 //         break;

//                 //     case DataType::FLOAT:
//                 //         stackTest<float>(implementation, size, &getRandomFloat, &getFloatFromString);
//                 //         break;

//                 //     case DataType::STRING:
//                 //         stackTest<string>(implementation, size, &getRandomString, &getSameString);
//                 //         break;
//                 //     }
//                 //     break;

//                 // case Structure::QUEUE:
//                 //     switch (dataType)
//                 //     {
//                 //     case DataType::INT:
//                 //         queueTest<int>(implementation, size, &getRandomInt, &getIntFromString);
//                 //         break;

//                 //     case DataType::FLOAT:
//                 //         queueTest<float>(implementation, size, &getRandomFloat, &getFloatFromString);
//                 //         break;

//                 //     case DataType::STRING:
//                 //         queueTest<string>(implementation, size, &getRandomString, &getSameString);
//                 //         break;
//                 //     }
//                 //     break;
//                 // }
//             }
//         }
//         catch (...)
//         {
//         }
//     } while (command != EXIT_COMMAND);
// }