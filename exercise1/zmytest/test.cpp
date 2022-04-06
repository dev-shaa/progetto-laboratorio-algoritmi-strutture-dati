#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <random>
#include <algorithm>
#include <sstream>
#include "test.hpp"
#include "../container/container.hpp"
#include "../vector/vector.hpp"
#include "../list/list.hpp"

using namespace std;

#define VECTOR_INPUT "vector"
#define LIST_INPUT "list"
#define INT_INPUT "int"
#define FLOAT_INPUT "float"
#define STRING_INPUT "string"

// - scelta della struttura (vettore vs lista) e del relativo tipo di dati da gestire (interi, ecc.);
// - popolamento della struttura precedentemente scelta con n valori del tipo opportuno generati casualmente, dove n è un parametro dato dall’utente in ingresso;
// - visualizzazione dell’elemento iniziale, finale o avente uno specifico indice;
// - visualizzazione di tutti gli elementi (effettuata per mezzo della funzione map);
// - controllo di esistenza di un dato valore;
// - calcolo di una delle seguenti funzioni (effettuato per mezzo delle funzioni fold) e relativa visualizzazione del risultato:
//      - somma per gli interi minori di n, prodotto per i float maggiori di n, e concatenazione per le stringhe con lunghezza minore o uguale a n, dove n è un parametro dato dall’utente in ingresso;
// - applicazione di una delle seguenti funzioni a tutti gli elementi: 2n per gli interi, n^2 per i float, e “uppercase” per le stringhe.

// Da un opportuno menu, dovrà essere inoltre possibile operare sulla struttura scelta attraverso
// le funzioni di libreria di cui ai punti (4) e (5). Infine, è necessario prevedere l’accesso alla
// funzionalità di test prevista dal docente.

int get_random_int()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);

    return dist(rng);
}

// float get_random_float()
// {
//     std::random_device dev;
//     std::mt19937 rng(dev());
//     std::uniform_real_distribution<std::mt19937::result_type> dist(1, 1000);

//     return dist(rng);
// }

std::string random_string()
{
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 32); // assumes 32 < number of characters in str
}

template <typename Data>
void check_exists(const lasd::TestableContainer<Data> &container, const Data &value)
{
    std::cout << "Value " << value << " is " << (container.Exists(value) ? "" : "not") << " contained." << std::endl;
}

template <typename Data>
void print_aux(Data &value, void *_)
{
    std::cout << value << " ";
}

template <typename Data>
void print_all(lasd::MappableContainer<Data> &container)
{
    std::cout << "[";
    container.Map(&print_aux<Data>, nullptr);
    std::cout << "]" << endl;
}

void intListTest()
{
}

void floatListTest()
{
}

void stringListTest()
{
}

void listTest(std::string dataType, ulong size)
{
}

template <typename Data>
void vectorTest(ulong size, std::function<void(Data &, void *)> randomGenerator, std::function<void(Data &, void *)> mapFunctor, std::function<void(const Data &, const void *, void *)> foldFunctor)
{
    lasd::Vector<Data> vec(size);
    std::string in, arg;

    vec.Map(randomGenerator, nullptr);

    do
    {
        std::cout << ">";
        std::cin >> in;

        if (in == "exit")
            break;

        if (in == "show")
        {
            std::cin >> arg;

            try
            {
                if (arg == "all")
                    print_all(vec);
                else if (arg == "front")
                    std::cout << vec.Front() << std::endl;
                else if (arg == "back")
                    std::cout << vec.Back() << std::endl;
                else
                    std::cout << vec[std::stoul(arg)] << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
        else if (in == "check")
        {
            std::cin >> arg;

            int value = std::stoi(arg);
            check_exists(vec, value);
        }
        else if (in == "resize")
        {
            std::cin >> arg;

            ulong value = std::stoul(arg);
            vec.Resize(value);
        }
        else if (in == "map")
        {
            vec.Map(mapFunctor, nullptr);
        }
        else if (in == "fold")
        {
            int sum = 0;
            vec.Fold(foldFunctor, (void *)vec.Size(), (void *)&sum);
        }

    } while (true);
}

void int_rand_aux(int &value, void *_)
{
    value = get_random_int();
}

void int_map_aux(int &value, void *_)
{
    value *= 2;
}

void int_fold_aux(const int &value, const void *n, void *accumulator)
{
    if (value < *((int *)n))
        *((int *)accumulator) += value;
}

void floatVectorTest(ulong size)
{
}

void stringVectorTest(ulong size)
{
}

void myTest()
{
    ulong size;
    std::string containerType, dataType;
    bool validInput = false;

    string command;

    std::cout << "Select container type: (\"" << VECTOR_INPUT << "\", \"" << LIST_INPUT << "\"), data type (\"" << INT_INPUT << "\", \"" << FLOAT_INPUT << "\", \"" << STRING_INPUT << "\") and the size (bigger than 1):" << std::endl
              << ">";

    while (!validInput)
    {
        validInput = true;
        std::cin >> containerType >> dataType >> size;

        if (containerType == VECTOR_INPUT)
        {
            if (dataType == INT_INPUT)
                vectorTest<int>(size, &int_rand_aux, &int_map_aux, &int_fold_aux);
            else if (dataType == FLOAT_INPUT)
                floatVectorTest(size);
            else if (dataType == STRING_INPUT)
                stringVectorTest(size);
        }
        else if (containerType == LIST_INPUT)
            listTest(dataType, size);
        else
        {
            std::cout << "Please insert a valid input" << std::endl;
            validInput = false;
        }
    }
}