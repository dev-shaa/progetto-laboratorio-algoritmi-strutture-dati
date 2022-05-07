#include <iostream>
#include <functional>
#include <string>

#include "./utilities.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../iterator/iterator.hpp"

using namespace std;

#define CMD_QUIT 'q'
#define CMD_HELP 'h'
#define CMD_EMPTY 'e'
#define CMD_SIZE 's'
#define CMD_PRINT 'p'
#define CMD_CLEAR 'c'
#define CMD_MAP 'm'
#define CMD_FOLD 'f'
#define CMD_ITERATOR 'i'
#define CMD_ROOT 'r'

#define CMD_NODE_Q 'q'
#define CMD_NODE_H 'h'
#define CMD_NODE_R 'r'
#define CMD_NODE_W 'w'
#define CMD_NODE_L_C 4
#define CMD_NODE_R_C 5
#define CMD_NODE_LEFT 'l'
#define CMD_NODE_RIGHT 'r'

#define CMD_ITERATOR_QUIT 'q'
#define CMD_ITERATOR_HELP 'h'
#define CMD_ITERATOR_TERMINATED 't'
#define CMD_ITERATOR_NEXT 'n'
#define CMD_ITERATOR_ELEMENT 'e'

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

/* ************************************************************************** */

template <typename Data>
void mapTreeOp(lasd::BinaryTree<Data> &tree, TraverseType type, function<void(Data &, void *)> foldFunctor, void *par)
{
    switch (type)
    {
    case PreOrder:
        tree.MapPreOrder(foldFunctor, par);
        break;
    case PostOrder:
        tree.MapPostOrder(foldFunctor, par);
        break;
    case InOrder:
        tree.MapInOrder(foldFunctor, par);
        break;
    case Breadth:
        tree.MapBreadth(foldFunctor, par);
        break;
    }
}

void intMapOp(lasd::BinaryTree<int> &tree, TraverseType type)
{
    mapTreeOp<int>(tree, type, &mapInt, nullptr);
}

void floatMapOp(lasd::BinaryTree<float> &tree, TraverseType type)
{
    mapTreeOp<float>(tree, type, &mapFloat, nullptr);
}

void stringMapOp(lasd::BinaryTree<string> &tree, TraverseType type)
{
    string prefix;
    cin >> prefix;
    mapTreeOp<string>(tree, type, &mapString, (void *)&prefix);
}

template <typename Data>
void foldTreeOp(lasd::BinaryTree<Data> &tree, TraverseType type, function<void(const Data &, const void *, void *)> foldFunctor)
{
    int n;

    if (cin >> n)
    {
        Data result;

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

/* ************************************************************************** */

template <typename Data>
lasd::BinaryTree<Data> *generateTree(const Implementation implementation, const ulong size, const function<Data()> getRandomValue)
{
    lasd::Vector<Data> vec(size);

    for (ulong i = 0; i < size; i++)
        vec[i] = getRandomValue();

    switch (implementation)
    {
    case Implementation::Link:
        return new lasd::BinaryTreeLnk<Data>(vec);
    default:
        return new lasd::BinaryTreeVec<Data>(vec);
    }
}

template <typename Data>
lasd::ForwardIterator<Data> *generateIterator(const lasd::BinaryTree<Data> &tree, TraverseType type)
{
    switch (type)
    {
    case TraverseType::PreOrder:
        return new lasd::BTPreOrderIterator<Data>(tree);
    case TraverseType::PostOrder:
        return new lasd::BTPostOrderIterator<Data>(tree);
    case TraverseType::InOrder:
        return new lasd::BTInOrderIterator<Data>(tree);
    default:
        return new lasd::BTBreadthIterator<Data>(tree);
    }
}

/* ************************************************************************** */

void printIteratorCommands()
{
    cout << "available iterator commands:\n"
         << "- " << CMD_ITERATOR_QUIT << " to return to tree menu\n"
         << "- " << CMD_ITERATOR_HELP << " to print this helper\n"
         << "- " << CMD_ITERATOR_TERMINATED << " to check if iterator has terminated\n"
         << "- " << CMD_ITERATOR_ELEMENT << " to print iterator's value\n"
         << "- " << CMD_ITERATOR_NEXT << " to progress the iterator"
         << endl;
}

template <typename Data>
void iteratorMenu(lasd::ForwardIterator<Data> &iterator)
{
    printIteratorCommands();

    char command;
    bool exitRequest = false;

    do
    {
        cout << ">";

        if (cin >> command)
        {
            switch (command)
            {
            case CMD_ITERATOR_QUIT:
                exitRequest = true;
                std::cout << "returned to tree menu\n";
                break;
            case CMD_ITERATOR_HELP:
                printIteratorCommands();
                break;
            case CMD_ITERATOR_TERMINATED:
                std::cout << "iterator has" << (iterator.Terminated() ? "" : " not ") << "terminated\n";
                break;
            case CMD_ITERATOR_ELEMENT:
                if (iterator.Terminated())
                    std::cout << "can't access because iterator has terminated\n";
                else
                    std::cout << "iterator's value: " << *iterator << "\n";

                break;
            case CMD_ITERATOR_NEXT:
                if (iterator.Terminated())
                    std::cout << "can't progess further because iterator has terminated\n";
                else
                {
                    ++iterator;
                    std::cout << "progressed to next element\n";
                }
                break;
            default:
                std::cerr << "invalid input\n";
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

void printNodeCommands()
{
    cout << "available node commands:\n"
         << "- " << CMD_NODE_Q << " to return to tree's menu\n"
         << "- " << CMD_NODE_H << " to print this helper\n"
         << "- " << CMD_NODE_R << " to print the node's value\n"
         << "- " << CMD_NODE_W << " [value] to write the node's value\n"
         << "- " << CMD_NODE_L_C << " to check if left child exists\n"
         << "- " << CMD_NODE_R_C << " to check if right child exists\n"
         << "- " << CMD_NODE_LEFT << " to access left child\n"
         << "- " << CMD_NODE_RIGHT << " to access right child"
         << endl;
}

template <typename Data>
void nodeMenu(typename lasd::BinaryTree<Data>::Node *node)
{
    // printNodeCommands();

    // bool exitRequest = false;
    // int command = -1;

    // while (!exitRequest)
    // {
    //     cout << ">";
    //     cin >> command;

    //     if (!std::cin)
    //     {
    //         std::cin.clear();
    //         ignoreLine();
    //         std::cerr << "invalid input\n";
    //     }
    //     else
    //     {
    //         switch (command)
    //         {
    //         case CMD_NODE_Q:
    //             exitRequest = true;
    //             break;
    //         case CMD_NODE_H:
    //             printNodeCommands();
    //             break;
    //         case CMD_NODE_R:
    //             cout << "node's value is: " << node->Element() << endl;
    //             break;
    //         case CMD_NODE_W:
    //             Data value;
    //             cin >> value;
    //             if (!std::cin)
    //             {
    //                 std::cin.clear();
    //                 ignoreLine();
    //                 std::cerr << "invalid input\n";
    //             }
    //             else
    //             {
    //                 node->Element() = value;
    //                 cout << "node's value has been updated to " << value << endl;
    //             }
    //             break;
    //         case CMD_NODE_L_C:
    //             cout << (node->HasLeftChild() ? "node doesn't have a left child" : "node has a left child") << endl;
    //             break;
    //         case CMD_NODE_R_C:
    //             cout << (node->HasRightChild() ? "node doesn't have a right child" : "node has a right child") << endl;
    //             break;
    //         case CMD_NODE_LEFT:
    //             if (node->HasLeftChild())
    //             {
    //                 node = &(node->LeftChild());
    //                 cout << "descended to left child" << endl;
    //             }
    //             else
    //             {
    //                 cout << "unable to descend to left child" << endl;
    //             }
    //             break;
    //         case CMD_NODE_RIGHT:
    //             // cout << node.Element() << endl;
    //             break;
    //         default:
    //             std::cerr << "invalid input\n";
    //             break;
    //         }
    //     }
    // }
}

/* ************************************************************************** */

void printTreeCommands(string mapDescription, string foldDescription)
{
    cout << "available tree commands:\n"
         << "- " << CMD_QUIT << " to return to main menu\n"
         << "- " << CMD_HELP << " to print this helper\n"
         << "- " << CMD_EMPTY << " to check if tree is empty\n"
         << "- " << CMD_SIZE << " to print tree size\n"
         << "- " << CMD_CLEAR << " to clear the tree\n"
         << "- " << CMD_ROOT << " to access the root\n"
         << "- " << CMD_PRINT << " ['pr'eorder/'po'storder/'in'order/'br'eadth] to print all elements of the tree\n"
         << "- " << CMD_MAP << " ['pr'eorder/'po'storder/'in'order/'br'eadth] " << mapDescription << "\n"
         << "- " << CMD_FOLD << " ['pr'eorder/'po'storder/'in'order/'br'eadth] [n] " << foldDescription << "\n"
         << "- " << CMD_ITERATOR << " ['pr'eorder/'po'storder/'in'order/'br'eadth] to traverse via iterator"
         << endl;
}

template <typename Data>
void treeMenu(lasd::BinaryTree<Data> &tree, function<void(lasd::BinaryTree<Data> &, TraverseType)> mapFunctor, string mapDescription, function<void(const Data &, const void *, void *)> foldFunctor, string foldDescription)
{
    char command;
    TraverseType traverseMode;
    bool exitRequest = false;

    printTreeCommands(mapDescription, foldDescription);

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
                printTreeCommands(mapDescription, foldDescription);
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
                if (cin >> traverseMode)
                    printTree(tree, traverseMode);
                else
                    handleInvalidInput();

                break;
            case CMD_MAP:
                if (cin >> traverseMode)
                    mapFunctor(tree, traverseMode);
                else
                    handleInvalidInput();

                break;
            case CMD_FOLD:
                if (cin >> traverseMode)
                    foldTreeOp(tree, traverseMode, foldFunctor);
                else
                    handleInvalidInput();

                break;
            case CMD_ITERATOR:
                if (cin >> traverseMode)
                    iteratorMenu<Data>(*generateIterator<Data>(tree, traverseMode));
                else
                    handleInvalidInput();

                break;
            case CMD_ROOT:
                if (tree.Empty())
                    cout << "can't access node menu because tree is empty\n";
                else
                    nodeMenu<Data>(&(tree.Root()));

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
    cout << "type tree structure to work on: ['v'ector/'l'inked] ['i'nt/'f'loat/'s'tring] [size]\n";
}

void manualTest()
{
    Implementation implementation;
    DataType datatype;
    ulong size;
    bool exitRequest = false;

    do
    {
        printInfo();
        cout << ">";

        if (cin >> implementation >> datatype >> size)
        {
            flushLine();

            switch (datatype)
            {
            case DataType::Int:
                treeMenu<int>(*generateTree<int>(implementation, size, &getRandomInt), &intMapOp, "to apply a map function (3*n)", &foldInt, "product of int < n");
                break;
            case DataType::Float:
                treeMenu<float>(*generateTree<float>(implementation, size, &getRandomFloat), &floatMapOp, "to apply a map function (n^3 for float)", &foldFloat, "sum of float > n");
                break;
            case DataType::String:
                treeMenu<string>(*generateTree<string>(implementation, size, &getRandomString), &stringMapOp, "[prefix] to apply prefix to all strings", &foldString, "concat of string shorter than n");
                break;
            }
        }
        else
        {
            handleInvalidInput();
        }
    } while (!exitRequest);
}
