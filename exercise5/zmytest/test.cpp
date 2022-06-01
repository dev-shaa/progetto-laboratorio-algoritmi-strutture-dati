#include <iostream>
#include <functional>
#include <string>

#include "../vector/vector.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"
#include "./utilities.hpp"

using namespace std;

#define CMD_QUIT 0
#define CMD_HELP 1
#define CMD_EMPTY 2
#define CMD_SIZE 3
#define CMD_PRINT 4
#define CMD_CLEAR 5
#define CMD_INSERT 6
#define CMD_REMOVE 7
#define CMD_FIND 8
#define CMD_FOLD 9

#define CMD_HASH_INT 1
#define CMD_HASH_DOUBLE 2
#define CMD_HASH_STRING 3

#define HASH_TABLE_OPN 0
#define HASH_TABLE_CLS 1

/* ************************************************************************** */

template <typename Data>
bool getData(Data &buffer)
{
    if (cin >> buffer)
        return true;

    handleInvalidInput();
    return false;
}

template <typename Data>
void printMap(const Data &value, void *_)
{
    cout << value << " ";
}

template <typename Data>
void printHashTable(lasd::HashTable<Data> &hashTable)
{
    if (hashTable.Empty())
        cout << "hashmap is empty";
    else
        hashTable.Map(&printMap<Data>, nullptr);

    cout << "\n";
}

template <typename Data>
void foldHashTable(lasd::HashTable<Data> &hashTable, function<void(const Data &, const void *, void *)> foldFunctor, Data &result)
{
    int n;

    if (getData<int>(n))
    {
        hashTable.Fold(foldFunctor, (void *)&n, (void *)&result);
        cout << "result is: " << result << endl;
    }
}

template <typename Data>
lasd::HashTable<Data> *generateHashTable(ulong size, int type, function<Data()> getRandomValue)
{
    lasd::HashTable<Data> *table;

    switch (type)
    {
    case HASH_TABLE_OPN:
        table = new lasd::HashTableOpnAdr<Data>();
    default:
        table = new lasd::HashTableClsAdr<Data>();
    }

    for (ulong i = 0; i < size; i++)
        while (!table->Insert(getRandomValue()))
            ;

    return table;
}

/* ************************************************************************** */

void printHashTableCommands(string foldDescription)
{
    cout << "available tree commands:\n- "
         << CMD_QUIT << " to return to main menu\n- "
         << CMD_HELP << " to print this helper\n- "
         << CMD_EMPTY << " to check if table is empty\n- "
         << CMD_SIZE << " to print table size\n- "
         << CMD_PRINT << " to print all the elements of table\n- "
         << CMD_CLEAR << " to clear the table\n- "
         << CMD_INSERT << " [value] to insert the element in the table\n- "
         << CMD_REMOVE << " [value] to remove the element from the table\n- "
         << CMD_FIND << " [value] to check if the element is in the table\n- "
         << CMD_FOLD << " [n] to get " << foldDescription << "\n";
}

template <typename Data>
void hashTableMenu(lasd::HashTable<Data> &hashTable, function<void(const Data &, const void *, void *)> foldFunctor, string foldDescription, Data &result)
{
    int command;
    Data valueBuffer;

    printHashTableCommands(foldDescription);

    do
    {
        cout << ">";

        if (cin >> command)
        {
            try
            {
                switch (command)
                {
                case CMD_QUIT:
                    return;
                case CMD_HELP:
                    printHashTableCommands(foldDescription);
                    break;
                case CMD_EMPTY:
                    cout << "hash table is" << (hashTable.Empty() ? " " : " not ") << "empty\n";
                    break;
                case CMD_SIZE:
                    cout << "hash table has " << hashTable.Size() << " element(s)\n";
                    break;
                case CMD_CLEAR:
                    hashTable.Clear();
                    cout << "hash table has been cleared\n";
                    break;
                case CMD_PRINT:
                    printHashTable(hashTable);
                    break;
                case CMD_INSERT:
                    if (getData<Data>(valueBuffer))
                    {
                        hashTable.Insert(valueBuffer);
                        cout << valueBuffer << " inserted\n";
                    }

                    break;
                case CMD_REMOVE:
                    if (getData<Data>(valueBuffer))
                    {
                        hashTable.Remove(valueBuffer);
                        cout << valueBuffer << " removed\n";
                    }

                    break;
                case CMD_FIND:
                    if (getData<Data>(valueBuffer))
                        cout << "value is" << (hashTable.Exists(valueBuffer) ? " " : " not ") << "contained in the hash table\n";

                    break;
                case CMD_FOLD:
                    foldHashTable(hashTable, foldFunctor, result);
                    break;
                default:
                    std::cerr << "no command found\n";
                    break;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "an exception occurred: " << e.what() << '\n';
            }
        }
        else
        {
            handleInvalidInput();
        }
    } while (true);
}

/* ************************************************************************** */

void printInfo()
{
    cout << "available commands:\n- "
         << CMD_QUIT << " to return to main menu\n- "
         << CMD_HASH_INT << " [" << HASH_TABLE_OPN << " for open/" << HASH_TABLE_CLS << " for closed] [size] to create a int hash table\n- "
         << CMD_HASH_DOUBLE << " [" << HASH_TABLE_OPN << " for open/" << HASH_TABLE_CLS << " for closed] [size] to create a double hash table\n- "
         << CMD_HASH_STRING << " [" << HASH_TABLE_OPN << " for open/" << HASH_TABLE_CLS << " for closed] [size] to create a string hash table\n";
}

void manualTest()
{
    int command;
    int implementation;
    ulong size;

    do
    {
        printInfo();
        cout << ">";

        if (getData<int>(command))
        {
            if (command == CMD_QUIT)
                break;

            if (getData<int>(implementation) && getData<ulong>(size))
            {
                cout << "\n";

                switch (command)
                {
                case CMD_HASH_INT:
                {
                    int prod = 1;
                    hashTableMenu<int>(*generateHashTable<int>(size, implementation, &getRandomInt), &foldInt, "product of int < n", prod);
                    break;
                }
                case CMD_HASH_DOUBLE:
                {
                    double sum = 0;
                    hashTableMenu<double>(*generateHashTable<double>(size, implementation, &getRandomDouble), &foldDouble, "sum of float > n", sum);
                    break;
                }
                case CMD_HASH_STRING:
                {
                    string concat;
                    hashTableMenu<string>(*generateHashTable<string>(size, implementation, &getRandomString), &foldString, "concat of string shorter than n", concat);
                    break;
                }
                default:
                    cout << "no command found\n";
                    break;
                }
            }
        }
    } while (true);
}

// void manualTest()
// {
// }