#include <iostream>
#include <functional>
#include <string>

#include "./utilities.hpp"
#include "../bst/bst.hpp"
#include "../binarytree/binarytree.hpp"
#include "../iterator/iterator.hpp"

using namespace std;

#define CMD_QUIT 'q'
#define CMD_HELP 'h'
#define CMD_EMPTY 'e'
#define CMD_SIZE 's'
#define CMD_PRINT 'o'
#define CMD_CLEAR 'c'
#define CMD_INSERT 'i'
#define CMD_REMOVE 'r'
#define CMD_FOLD 'f'
#define CMD_PREDECESSOR 'p'
#define CMD_SUCCESSOR 'n'
#define CMD_FIND 't'

/* ************************************************************************** */

template <typename Data>
void printMap(const Data &value, void *_)
{
    cout << value << " ";
}

template <typename Data>
void printTree(lasd::BinaryTree<Data> &tree, TraverseType type)
{
    if (tree.Empty())
    {
        cout << "tree is empty\n";
        return;
    }

    switch (type)
    {
    case PreOrder:
        tree.MapPreOrder(&printMap<Data>, nullptr);
        break;
    case PostOrder:
        tree.MapPostOrder(&printMap<Data>, nullptr);
        break;
    case InOrder:
        tree.MapInOrder(&printMap<Data>, nullptr);
        break;
    case Breadth:
        tree.MapBreadth(&printMap<Data>, nullptr);
        break;
    }

    cout << "\n";
}

template <typename Data>
void foldTreeOp(lasd::BinaryTree<Data> &tree, TraverseType type, function<void(const Data &, const void *, void *)> foldFunctor, Data &result)
{
    int n;

    if (cin >> n)
    {
        switch (type)
        {
        case PreOrder:
            tree.FoldPreOrder(foldFunctor, (void *)&n, (void *)&result);
            break;
        case PostOrder:
            tree.FoldPostOrder(foldFunctor, (void *)&n, (void *)&result);
            break;
        case InOrder:
            tree.FoldInOrder(foldFunctor, (void *)&n, (void *)&result);
            break;
        case Breadth:
            tree.FoldBreadth(foldFunctor, (void *)&n, (void *)&result);
            break;
        }

        cout << "result is: " << result << endl;
    }
    else
    {
        handleInvalidInput();
    }
}

template <typename Data>
lasd::BST<Data> generateTree(ulong size, function<Data()> getRandomValue)
{
    lasd::BST<Data> tree;

    for (ulong i = 0; i < size; i++)
        tree.Insert(getRandomValue());

    return tree;
}

/* ************************************************************************** */

void printTreeCommands(string foldDescription)
{
    cout << "available tree commands:\n"
         << "- " << CMD_QUIT << " to return to main menu\n"
         << "- " << CMD_HELP << " to print this helper\n"
         << "- " << CMD_EMPTY << " to check if tree is empty\n"
         << "- " << CMD_SIZE << " to print tree size\n"
         << "- " << CMD_CLEAR << " to clear the tree\n"
         << "- " << CMD_ROOT << " to access the root\n"
         << "- " << CMD_PRINT << " ['pr'eorder/'po'storder/'in'order/'br'eadth] to print all elements of the tree\n"
         << "- " << CMD_FOLD << " ['pr'eorder/'po'storder/'in'order/'br'eadth] [n] to get " << foldDescription << "\n"
         << "- " << CMD_ITERATOR << " ['pr'eorder/'po'storder/'in'order/'br'eadth] to traverse via iterator"
         << endl;
}

template <typename Data>
void treeMenu(lasd::BST<Data> &tree, function<void(const Data &, const void *, void *)> foldFunctor, string foldDescription, Data &result)
{
    char command;
    // string command;
    Data bufferValue;
    TraverseType bufferTraverseMode;
    bool exitRequest = false;

    printTreeCommands(foldDescription);

    do
    {
        cout << ">";

        if (cin >> command)
        {
            switch (command)
            {
            case CMD_QUIT:
                exitRequest = true;
                break;
            case CMD_HELP:
                printTreeCommands(foldDescription);
                break;
            case CMD_EMPTY:
                cout << "tree is" << (tree.Empty() ? " " : " not ") << "empty\n";
                break;
            case CMD_SIZE:
                cout << "tree has " << tree.Size() << " node(s)\n";
                break;
            case CMD_CLEAR:
                tree.Clear();
                cout << "tree has been cleared\n";
                break;
            case CMD_PRINT:
                if (cin >> bufferTraverseMode)
                    printTree(tree, bufferTraverseMode);
                else
                    handleInvalidInput();

                break;
            case CMD_INSERT:
                Data valueToInsert;

                if (cin >> valueToInsert)
                    tree.Insert(valueToInsert);
                else
                    handleInvalidInput();

                break;
            case CMD_REMOVE:
                Data valueToRemove;

                if (cin >> valueToRemove)
                    tree.Remove(valueToRemove);
                else
                    handleInvalidInput();

                break;
            case CMD_PREDECESSOR:
                // todo: remove, data&remove, data

                break;
            case CMD_MAX:
                // todo: remove, data&remove, data

                break;
            case CMD_FOLD:
                if (cin >> bufferTraverseMode)
                    foldTreeOp(tree, bufferTraverseMode, foldFunctor, result);
                else
                    handleInvalidInput();

                break;
            case CMD_FIND:
                if (cin >> bufferValue)
                    cout << "value is" << (tree.Exists(bufferValue) ? " " : " not ") << "contained in the tree\n";
                else
                    handleInvalidInput();

                break;
            default:
                std::cerr << "no command found\n";
                break;
            }
        }
        else
        {
            handleInvalidInput();
        }
    } while (!exitRequest);
}

/* ************************************************************************** */

void printInfo()
{
    cout << "available commands:\n- q to return to main menu\n- c ['v'ector/'l'inked] ['i'nt/'f'loat/'s'tring] [size] to create a new tree\n";
}

void manualTest()
{
    char command;
    DataType datatype;
    ulong size;
    bool exitRequest = false;

    do
    {
        printInfo();
        cout << ">";

        if (cin >> command)
        {
            if (command == 'q')
                break;
            else if (command == 'c' && cin >> datatype >> size)
            {
                flushLine();

                switch (datatype)
                {
                case DataType::Int:
                {
                    int prod = 1;
                    treeMenu<int>(generateTree<int>(size, &getRandomInt), "to apply a map function (3*n)", &foldInt, "product of int < n", prod);
                    break;
                }
                case DataType::Float:
                {
                    float sum = 0;
                    treeMenu<float>(generateTree<float>(size, &getRandomFloat), "to apply a map function (n^3 for float)", &foldFloat, "sum of float > n", sum);
                    break;
                }
                case DataType::String:
                {
                    string concat;
                    treeMenu<string>(generateTree<string>(size, &getRandomString), "[prefix] to apply prefix to all strings", &foldString, "concat of string shorter than n", concat);
                    break;
                }
                }
            }
            else
            {
                handleInvalidInput();
            }
        }
        else
        {
            handleInvalidInput();
        }

    } while (!exitRequest);
}
