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

/**
 * @brief Clears the input buffer, avoiding "overflowing" inputs.
 */
void flush_input_buffer()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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
    if (container.Empty())
        std::cout << "container is empty";
    else
        container.Map(&print_aux<Data>, nullptr);

    std::cout << std::endl;
}

template <typename Data>
void vectorTest(ulong size, std::function<void(Data &, void *)> randomGenerator,
                std::function<Data(std::string)> dataConverter,
                std::function<void(Data &, void *)> mapFunctor,
                std::function<void(const lasd::FoldableContainer<int> &, const ulong)> foldFunctor)
{
    lasd::Vector<Data> vec(size);
    std::string command, arg;

    vec.Map(randomGenerator, nullptr);

    std::cout << "available commands:" << std::endl
              << "- cancel" << std::endl
              << "- show [all/front/back/index]" << std::endl
              << "- check [value]" << std::endl
              << "- resize [new size]" << std::endl
              << "- map (2*n for integers, n^2 for floats and uppercase for strings)" << std::endl
              << "- fold [n]" << std::endl;

    do
    {
        flush_input_buffer();
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
                Data value = dataConverter(arg);
                check_exists<Data>(vec, value);
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
                // std::cin >> arg;
                // foldFunctor(vec, std::stoul(arg));
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
              std::function<void(const Data &, const void *, void *)> foldFunctor)
{
    lasd::List<Data> list;
    std::string command, arg;

    for (ulong i = 0; i < size; i++)
        list.InsertAtFront(randomGenerator());

    std::cout << "available commands:" << std::endl
              << "- cancel" << std::endl
              << "- show [all/front/back/index]" << std::endl
              << "- check [value]" << std::endl
              << "- pop" << std::endl
              << "- insert [value]" << std::endl
              << "- map (2*n for integers, n^2 for floats and uppercase for strings)" << std::endl
              << "- fold [n]" << std::endl;

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
                    print_all(list);
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
                check_exists<Data>(list, value);
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
                string string_value;
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
                // int sum = 0;
                // vec.Fold(foldFunctor, (void *)vec.Size(), (void *)&sum);
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

#pragma region ints

int get_random_int()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

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

void int_fold(const lasd::FoldableContainer<int> &container, const ulong n)
{
    int sum = 0;
    container.Fold(&int_fold_aux, (void *)&n, (void *)&sum);
    std::cout << "sum of numbers: " << sum << std::endl;
}

int string_to_int(std::string value)
{
    return std::stoi(value);
}

#pragma endregion

#pragma region floats

float get_random_float()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(0, 100);

    return dist(rng);
}

void float_rand_aux(float &value, void *_)
{
    value = get_random_float();
}

void float_map_aux(float &value, void *_)
{
    value *= value; // x^2
}

void float_fold_aux(const float &value, const void *n, void *product)
{
    if (value > *((float *)n))
        *((float *)product) *= value;
}

void float_fold(const lasd::FoldableContainer<float> &container, const ulong n)
{
    int product = 1;
    container.Fold(&float_fold_aux, (void *)&n, (void *)&product);
    std::cout << "product of numbers: " << product << std::endl;
}

float string_to_float(std::string value)
{
    return std::stof(value);
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

void string_rand_aux(std::string &value, void *_)
{
    value = get_random_string();
}

void string_map_aux(std::string &value, void *_)
{
    transform(value.begin(), value.end(), value.begin(), ::toupper); // uppercase
}

void string_fold_aux(const std::string &value, const void *n, void *concatenation)
{
    // concatenazione per le stringhe con lunghezza minore o uguale a n

    if (value.size() <= *((int *)n))
        (*(std::string *)concatenation) += value;
}

void string_fold(const lasd::FoldableContainer<std::string> &container, const ulong n)
{
    std::string concatenation;
    container.Fold(&string_fold_aux, (void *)&n, (void *)&concatenation);
    std::cout << "concatenation of strings: " << concatenation << std::endl;
}

std::string return_self(std::string value)
{
    return value;
}

#pragma endregion

void myTest()
{
    // TODO: float

    ulong size;
    std::string containerType, dataType;
    bool validInput = false;

    std::string command;

    std::cout << "Select container type: (\"" << VECTOR_INPUT << "\", \"" << LIST_INPUT << "\"), data type (\"" << INT_INPUT << "\", \"" << FLOAT_INPUT << "\", \"" << STRING_INPUT << "\") and the size (bigger than 1):" << std::endl
              << ">";

    do
    {
        validInput = true;

        flush_input_buffer();
        std::cin >> containerType >> dataType >> size;

        if (containerType == VECTOR_INPUT)
        {
            if (dataType == INT_INPUT)
                vectorTest<int>(size, &int_rand_aux, &string_to_int, &int_map_aux, &int_fold);
            else if (dataType == FLOAT_INPUT)
                vectorTest<float>(size, &float_rand_aux, &string_to_float, &float_map_aux, &float_fold);
            else if (dataType == STRING_INPUT)
                vectorTest<std::string>(size, &string_rand_aux, &return_self, &string_map_aux, &string_fold);
        }
        else if (containerType == LIST_INPUT)
        {
            // if (dataType == INT_INPUT)
            //     listTest<int>(size, &int_rand_aux, &string_to_int, &int_map_aux, &int_fold);
            // else if (dataType == STRING_INPUT)
            //     listTest<string>(size, &string_rand_aux, &return_self, &string_map_aux, &string_fold);
        }
    } while (!validInput);
}