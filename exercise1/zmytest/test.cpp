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

template <typename Data>
void check_exists(const lasd::TestableContainer<Data> &container, const Data &value)
{
    std::cout << value << " is" << (container.Exists(value) ? " " : " not ") << "contained." << std::endl;
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

template <typename Data>
void vectorTest(ulong size, std::function<void(Data &, void *)> randomGenerator, std::function<Data(string)> dataGetter, std::function<void(Data &, void *)> mapFunctor, std::function<void(const Data &, const void *, void *)> foldFunctor)
{
    lasd::Vector<Data> vec(size);
    std::string command, arg;

    vec.Map(randomGenerator, nullptr);

    std::cout << "available commands:\n- show \t| [all/front/back/index]\n- check \t| [value]\n- resize \t| [new size]\n- map \t| 2*n for integers, n^2 for floats and uppercase for strings)\n- fold\n- cancel" << std::endl;

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
                    print_all(vec);
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
                Data value = dataGetter(arg);
                check_exists<Data>(vec, value);
            }
            else if (command == "resize")
            {
                std::cin >> arg;
                ulong value = std::stoul(arg);
                vec.Resize(value);
            }
            else if (command == "map")
            {
                vec.Map(mapFunctor, nullptr);
            }
            else if (command == "fold")
            {
                // int sum = 0;
                // vec.Fold(foldFunctor, (void *)vec.Size(), (void *)&sum);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    } while (true);
}

#pragma region ints

int get_random_int()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);

    return dist(rng);
}

void int_rand_aux(int &value, void *_)
{
    value = get_random_int();
}

void int_map_aux(int &value, void *_)
{
    value *= 2;
}

void int_fold_aux(const int &value, const void *n, void *sum)
{
    if (value < *((int *)n))
        *((int *)sum) += value;
}

int string_to_int(std::string value)
{
    return std::stoi(value);
}

#pragma endregion

#pragma region floats

float get_random_float()
{
    // TODO: implementa
    return 0;
}

#pragma endregion

#pragma region strings

std::string get_random_string()
{
    std::string str("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

    std::random_device rd;
    std::mt19937 generator(rd());

    std::shuffle(str.begin(), str.end(), generator);

    return str.substr(0, 16); // assumes 32 < number of characters in str
}

void string_rand_aux(string &value, void *_)
{
    value = get_random_string();
}

void string_map_aux(string &value, void *_)
{
    // uppercase

    transform(value.begin(), value.end(), value.begin(), ::toupper);
}

void string_fold_aux(const string &value, const void *n, void *concatenation)
{
    // concatenazione per le stringhe con lunghezza minore o uguale a n

    if (value.size() <= *((int *)n))
        (*(string *)concatenation) += value;
}

string return_self(string value)
{
    return value;
}

#pragma endregion

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
                vectorTest<int>(size, &int_rand_aux, &string_to_int, &int_map_aux, &int_fold_aux);
            else if (dataType == STRING_INPUT)
                vectorTest<string>(size, &string_rand_aux, &return_self, &string_map_aux, &string_fold_aux);
            // else if (dataType == STRING_INPUT)
            // stringVectorTest(size);
        }
        // else if (containerType == LIST_INPUT)
        //     listTest(dataType, size);
        // else
        // {
        //     std::cout << "Please insert a valid input" << std::endl;
        //     validInput = false;
        // }
    }
}