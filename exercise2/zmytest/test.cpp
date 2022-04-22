#include <iostream>
#include <functional>
#include <string>
#include <random>
#include <algorithm>

#include "../stack/stack.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"

#include "../queue/queue.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

using namespace std;

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

void flushInputBuffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/* ************************************************************************** */

enum Implementation
{
    VECTOR = 0,
    LIST = 1
};

void printStackHelp()
{
    cout << "available commands:\n- cancel\n- help\n- push [value]\n- pop\n- top\n- topnpop\n- empty\n- size\n- clear" << endl;
}

void printQueueHelp()
{
    cout << "available commands:\n- cancel\n- help\n- enqueue [value]\n- dequeue\n- head\n- headdequeue\n- empty\n- size\n- clear" << endl;
}

template <typename Data>
void stackTest(Implementation implementation, ulong initialSize, function<Data()> getRandomValue, function<Data(const string &)> stringToValue)
{
    lasd::Stack<Data> *stack;

    switch (implementation)
    {
    case VECTOR:
        stack = new lasd::StackVec<Data>();
        break;
    case LIST:
        stack = new lasd::StackLst<Data>();
        break;
    }

    for (ulong i = 0; i < initialSize; i++)
        stack->Push(getRandomValue());

    string command, arg;

    printStackHelp();

    do
    {
        flushInputBuffer();
        cout << ">";
        cin >> command;

        try
        {
            if (command == "cancel")
                break;
            else if (command == "help")
                printStackHelp();
            else if (command == "push")
            {
                cin >> arg;
                stack->Push(stringToValue(arg));
            }
            else if (command == "pop")
                stack->Pop();
            else if (command == "top")
                cout << stack->Top() << endl;
            else if (command == "topnpop")
                cout << stack->TopNPop() << endl;
            else if (command == "empty")
                cout << "stack is" << (stack->Empty() ? " " : " not ") << "empty" << endl;
            else if (command == "size")
                cout << "stack has size " << stack->Size() << endl;
            else if (command == "clear")
                stack->Clear();
            else
                cout << command << ": no command found" << endl;
        }
        catch (const exception &e)
        {
            cerr << "an exception occurred: " << e.what() << endl;
        }
    } while (true);

    delete stack;
}

template <typename Data>
void queueTest(Implementation implementation, ulong initialSize, function<Data()> getRandomValue, function<Data(const string &)> stringToValue)
{
    lasd::Queue<Data> *queue;

    switch (implementation)
    {
    case VECTOR:
        queue = new lasd::QueueVec<Data>();
        break;
    case LIST:
        queue = new lasd::QueueLst<Data>();
        break;
    }

    for (ulong i = 0; i < initialSize; i++)
        queue->Enqueue(getRandomValue());

    string command, arg;

    printQueueHelp();

    do
    {
        flushInputBuffer();
        cout << ">";
        cin >> command;

        try
        {
            if (command == "cancel")
                break;
            else if (command == "help")
                printStackHelp();
            else if (command == "enqueue")
            {
                cin >> arg;
                queue->Enqueue(stringToValue(arg));
            }
            else if (command == "dequeue")
                queue->Dequeue();
            else if (command == "headdequeue")
                cout << queue->HeadNDequeue() << endl;
            else if (command == "head")
                cout << queue->Head() << endl;
            else if (command == "empty")
                cout << "queue is" << (queue->Empty() ? " " : " not ") << "empty" << endl;
            else if (command == "size")
                cout << "queue has size " << queue->Size() << endl;
            else if (command == "clear")
                queue->Clear();
            else
                cout << command << ": no command found" << endl;
        }
        catch (const exception &e)
        {
            cerr << "an exception occurred: " << e.what() << endl;
        }

    } while (true);

    delete queue;
}

void manualTest()
{
    string command, structure, implementation, dataType;
    ulong size;

    cout << "available commands:\n- exit\n- create ['stack'/'queue'] ['vector'/'list'] ['int'/'float'/'string'] [size]\n>";

    do
    {
        flushInputBuffer();

        cin >> command;

        if (command == "create")
        {
            cin >> structure >> implementation >> dataType >> size;

            Implementation impl = implementation == "vector" ? VECTOR : LIST;

            if (structure == "stack")
            {
                if (dataType == "int")
                    stackTest<int>(impl, size, &getRandomInt, &getIntFromString);
                else if (dataType == "float")
                    stackTest<float>(impl, size, &getRandomFloat, &getFloatFromString);
                else if (dataType == "string")
                    stackTest<string>(impl, size, &getRandomString, &getSameString);
            }
            else if (structure == "queue")
            {
                if (dataType == "int")
                    queueTest<int>(impl, size, &getRandomInt, &getIntFromString);
                else if (dataType == "float")
                    queueTest<float>(impl, size, &getRandomFloat, &getFloatFromString);
                else if (dataType == "string")
                    queueTest<string>(impl, size, &getRandomString, &getSameString);
            }
        }

    } while (command != "exit");
}