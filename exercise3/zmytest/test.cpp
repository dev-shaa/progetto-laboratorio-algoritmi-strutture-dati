// #include <iostream>
// #include <functional>
// #include <string>
// #include <random>
// #include <algorithm>

// #include "../binarytree/binarytree.hpp"
// #include "../binarytree/vec/binarytreevec.hpp"
// #include "../binarytree/lnk/binarytreelnk.hpp"

// /* ************************************************************************** */

// using namespace std;

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

// enum Implementation
// {
//     VECTOR,
//     LIST
// };

// std::istream &operator>>(std::istream &input, Implementation &implementation)
// {
//     std::string stringInput;
//     input >> stringInput;

//     if (stringInput == "vector")
//         implementation = VECTOR;
//     else if (stringInput == "list")
//         implementation = LIST;
//     else
//         throw std::istream::failure("invalid Implementation read");

//     return input;
// }

// enum Structure
// {
//     STACK,
//     QUEUE
// };

// std::istream &operator>>(std::istream &input, Structure &structure)
// {
//     std::string stringInput;
//     input >> stringInput;

//     if (stringInput == "stack")
//         structure = STACK;
//     else if (stringInput == "queue")
//         structure = QUEUE;
//     else
//         throw std::istream::failure("invalid Structure read");

//     return input;
// }

// enum DataType
// {
//     INT,
//     FLOAT,
//     STRING
// };

// std::istream &operator>>(std::istream &input, DataType &dataType)
// {
//     std::string stringInput;
//     input >> stringInput;

//     if (stringInput == "int")
//         dataType = INT;
//     else if (stringInput == "float")
//         dataType = FLOAT;
//     else if (stringInput == "string")
//         dataType = STRING;
//     else
//         throw std::istream::failure("invalid Datatype read");

//     return input;
// }

// /* ************************************************************************** */

// #define MANUAL_TEST_HELP "\navailable commands:\n- exit\n- create ['vector'/'list'] ['int'/'float'/'string'] [size]\n"

// void printManualTestHelp()
// {
//     cout << MANUAL_TEST_HELP;
// }

// template <typename Data>
// void treeTest(lasd::BinaryTree<Data> &tree)
// {
//     string command, arg;

//     do
//     {
//         flushInputBuffer();
//         cout << ">";
//         cin >> command;

//         try
//         {
//             if (command == "cancel")
//                 break;
//             else if (command == "help")
//                 printStackHelp();
//             else if (command == "print")
//             {
//                 cin >> arg;
//                 // visualizzazione in ampiezza/pre-ordine/ordine/post-ordine di tutti gli elementi (effettuata per mezzo dell’opportuna funzione map)
//             }
//             else if (command == "exists")
//             {
//                 cin >> arg;
//                 // check existance
//             }
//             else if (command == "fold")
//             {
//             }
//             else if (command == "map")
//             {
//             }
//             else
//                 cout << command << ": no command found" << endl;
//         }
//         catch (const exception &e)
//         {
//             cerr << "an exception occurred: " << e.what() << endl;
//         }
//     } while (true);

//     // delete stack;
// }

// void manualTest()
// {
//     string command, stringSize;
//     Structure structure;
//     DataType dataType;
//     Implementation implementation;
//     ulong size;

//     do
//     {
//         try
//         {
//             flushInputBuffer();

//             printManualTestHelp();
//             cout << ">";
//             cin >> command;

//             if (command == "create")
//             {
//                 cin >> structure >> implementation >> dataType >> stringSize;
//                 size = std::stoul(stringSize);

//                 switch (structure)
//                 {
//                 case Structure::STACK:
//                     switch (dataType)
//                     {
//                     case DataType::INT:
//                         stackTest<int>(implementation, size, &getRandomInt, &getIntFromString);
//                         break;

//                     case DataType::FLOAT:
//                         stackTest<float>(implementation, size, &getRandomFloat, &getFloatFromString);
//                         break;

//                     case DataType::STRING:
//                         stackTest<string>(implementation, size, &getRandomString, &getSameString);
//                         break;
//                     }
//                     break;

//                 case Structure::QUEUE:
//                     switch (dataType)
//                     {
//                     case DataType::INT:
//                         queueTest<int>(implementation, size, &getRandomInt, &getIntFromString);
//                         break;

//                     case DataType::FLOAT:
//                         queueTest<float>(implementation, size, &getRandomFloat, &getFloatFromString);
//                         break;

//                     case DataType::STRING:
//                         queueTest<string>(implementation, size, &getRandomString, &getSameString);
//                         break;
//                     }
//                     break;
//                 }
//             }
//         }
//         catch (...)
//         {
//         }
//     } while (command != "exit");
// }

#include "../queue/vec/queuevec.hpp"

void foo()
{
    lasd::QueueVec<float> *que = new lasd::QueueVec<float>();

    que->Enqueue(10.1f);
    que->Enqueue(1.2f);

    lasd::QueueVec<float> cop(std::move(*que));
}