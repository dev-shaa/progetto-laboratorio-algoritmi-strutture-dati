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
#define CMD_PRINT 'p'
#define CMD_CLEAR 'c'
#define CMD_FOLD 'f'
#define CMD_ITERATOR 'i'
#define CMD_ROOT 'r'

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

// template <typename Data>
// void applyMapToTree(lasd::BinaryTree<Data> &tree, TraverseType type, function<void(Data &, void *)> foldFunctor, void *par)
// {
//     switch (type)
//     {
//     case PreOrder:
//         tree.MapPreOrder(foldFunctor, par);
//         break;
//     case PostOrder:
//         tree.MapPostOrder(foldFunctor, par);
//         break;
//     case InOrder:
//         tree.MapInOrder(foldFunctor, par);
//         break;
//     case Breadth:
//         tree.MapBreadth(foldFunctor, par);
//         break;
//     }
// }

// void treeMapInt(lasd::BinaryTree<int> &tree, TraverseType type)
// {
//     applyMapToTree<int>(tree, type, &mapInt, nullptr);
// }

// void treeMapFloat(lasd::BinaryTree<float> &tree, TraverseType type)
// {
//     applyMapToTree<float>(tree, type, &mapFloat, nullptr);
// }

// void treeMapString(lasd::BinaryTree<string> &tree, TraverseType type)
// {
//     string prefix;
//     cin >> prefix;
//     applyMapToTree<string>(tree, type, &mapString, (void *)&prefix);
// }

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

/* ************************************************************************** */

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
                std::cout << "iterator has" << (iterator.Terminated() ? " " : " not ") << "terminated\n";
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

// void printNodeCommands()
// {
//     cout << "available node commands:\n"
//          << "- " << CMD_NODE_QUIT << " to return to tree's menu\n"
//          << "- " << CMD_NODE_HELP << " to print this helper\n"
//          << "- " << CMD_NODE_PRINT << " to print the node's value\n"
//          << "- " << CMD_NODE_WRITE << " [value] to write the node's value\n"
//          << "- " << CMD_NODE_CHECK << "['l'eft/'r'ight] to check if left or right child exists\n"
//          << "- " << CMD_NODE_LEFT << " to access left child\n"
//          << "- " << CMD_NODE_RIGHT << " to access right child"
//          << endl;
// }

// template <typename Data>
// void nodeMenu(typename lasd::BinaryTree<Data>::Node *node)
// {
//     printNodeCommands();

//     char command;
//     bool exitRequest = false;

//     do
//     {
//         cout << ">";

//         if (cin >> command)
//         {
//             switch (command)
//             {
//             case CMD_NODE_QUIT:
//                 exitRequest = true;
//                 cout << "returning to tree menu\n";
//                 break;
//             case CMD_NODE_HELP:
//                 printNodeCommands();
//                 break;
//             case CMD_NODE_PRINT:
//                 cout << "node's value is: " << node->Element() << "\n";
//                 break;
//             case CMD_NODE_WRITE:
//             {
//                 Data value;

//                 if (cin >> value)
//                 {
//                     node->Element() = value;
//                     cout << "node's value has been updated to " << value << "\n";
//                 }
//                 else
//                     handleInvalidInput();

//                 break;
//             }
//             case CMD_NODE_CHECK:
//             {
//                 string child;
//                 cin >> child;

//                 if (child == "l")
//                     cout << (node->HasLeftChild() ? "node doesn't have a left child" : "node has a left child") << "\n";
//                 else if (child == "r")
//                     cout << (node->HasRightChild() ? "node doesn't have a right child" : "node has a right child") << "\n";
//                 else
//                     cout << "type 'l' or 'r'\n";

//                 flushLine();

//                 break;
//             }
//             case CMD_NODE_LEFT:
//                 if (node->HasLeftChild())
//                 {
//                     node = &(node->LeftChild());
//                     cout << "descended to left child\n";
//                 }
//                 else
//                 {
//                     cout << "node doesn't have a left child\n";
//                 }

//                 break;
//             case CMD_NODE_RIGHT:
//                 if (node->HasRightChild())
//                 {
//                     node = &(node->RightChild());
//                     cout << "descended to right child\n";
//                 }
//                 else
//                 {
//                     cout << "node doesn't have a right child\n";
//                 }

//                 break;
//             default:
//                 std::cerr << "no command found\n";
//                 break;
//             }
//         }
//         else
//         {
//             handleInvalidInput();
//         }

//     } while (!exitRequest);
// }

/* ************************************************************************** */

template <typename Data>
lasd::BST<Data> generateTree(ulong size, function<Data()> getRandomValue)
{
    lasd::BST<Data> tree;

    for (ulong i = 0; i < size; i++)
        tree.Insert(getRandomValue());

    return tree;
}

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
         << "- " << CMD_FOLD << " ['pr'eorder/'po'storder/'in'order/'br'eadth] [n] to get " << foldDescription << "\n"
         << "- " << CMD_ITERATOR << " ['pr'eorder/'po'storder/'in'order/'br'eadth] to traverse via iterator"
         << endl;
}

template <typename Data>
void treeMenu(lasd::BST<Data> &tree, function<void(const Data &, const void *, void *)> foldFunctor, string foldDescription, Data &result)
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
                    foldTreeOp(tree, traverseMode, foldFunctor, result);
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
