#include <iostream>
#include <functional>
#include <string>
#include <algorithm>

#include "./utilities.hpp"

#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"

using namespace std;

/* ************************************************************************** */

void foldInt(const int &value, const void *n, void *product)
{
    if (value < *((int *)n))
        *((int *)product) *= value;
}

void mapInt(int &value, void *_)
{
    value *= 3;
}

void foldFloat(const float &value, const void *n, void *sum)
{
    if (value > *((ulong *)n))
        *((float *)sum) += value;
}

void mapFloat(float &value, void *_)
{
    value *= value * value;
}

void foldString(const string &value, const void *n, void *concatenation)
{
    if (value.size() <= *((uint *)n))
        (*(string *)concatenation) += value;
}

void mapString(string &value, void *prefix)
{
    value = (*(string *)prefix) + value;
}

template <typename Data>
void printMap(const Data &value, void *_)
{
    cout << value << " ";
}

/* ************************************************************************** */

template <typename Data>
void printTree(lasd::BinaryTree<Data> &tree)
{
    // cout << "default: ";
    // tree.Map(&printMap<Data>, nullptr);
    // cout << endl;

    // cout << "pre order: ";
    // tree.MapPreOrder(&printMap<Data>, nullptr);
    // cout << endl;

    // cout << "post order: ";
    // tree.MapPostOrder(&printMap<Data>, nullptr);
    // cout << endl;

    // cout << "in order: ";
    // tree.MapInOrder(&printMap<Data>, nullptr);
    // cout << endl;

    // cout << "breadth: ";
    tree.MapBreadth(&printMap<Data>, nullptr);
    cout << endl;
}

template <typename Data>
lasd::BinaryTree<Data> *generateTree(ulong size, function<Data()> getRandomValue)
{
    lasd::Vector<Data> vec(size);

    for (ulong i = 0; i < size; i++)
        vec[i] = getRandomValue();

    return new lasd::BinaryTreeVec<Data>(vec);
}

template <typename Data>
void treeTest(lasd::BinaryTree<Data> &tree, function<void(const Data &, const void *, void *)> foldFunctor, const void *par, void *acc)
{
    tree.FoldPostOrder(foldFunctor, par, acc);
}

#define CMD_QUIT 0
#define CMD_HELP 1
#define CMD_EMPTY 2
#define CMD_SIZE 3
#define CMD_PRINT 4
#define CMD_CLEAR 5
#define CMD_MAP 6
#define CMD_FOLD 7
#define CMD_ITERATOR 8
#define CMD_ROOT 9

#define CMD_NODE_Q 0
#define CMD_NODE_H 1
#define CMD_NODE_R 2
#define CMD_NODE_W 3
#define CMD_NODE_L_C 4
#define CMD_NODE_R_C 5
#define CMD_NODE_LEFT 6
#define CMD_NODE_RIGHT 7

void printTreeCommands()
{
    cout << "available tree commands:\n"
         << "- " << CMD_QUIT << " to return to main menu\n"
         << "- " << CMD_HELP << " to print this helper\n"
         << "- " << CMD_EMPTY << " to check if tree is empty\n"
         << "- " << CMD_SIZE << " to print tree size\n"
         << "- " << CMD_PRINT << " to print all elements of the tree\n"
         << "- " << CMD_CLEAR << " to clear the tree\n"
         << "- " << CMD_MAP << " to apply a map function\n"
         << "- " << CMD_FOLD << " to apply a fold function\n"
         << "- " << CMD_ITERATOR << " to traverse via iterator\n"
         << "- " << CMD_ROOT << " to access the root"
         << endl;
}

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
    printNodeCommands();

    bool exitRequest = false;
    int command = -1;

    while (!exitRequest)
    {
        cout << ">";
        cin >> command;

        if (!std::cin)
        {
            std::cin.clear();
            ignoreLine();
            std::cerr << "invalid input\n";
        }
        else
        {
            switch (command)
            {
            case CMD_NODE_Q:
                exitRequest = true;
                break;
            case CMD_NODE_H:
                printNodeCommands();
                break;
            case CMD_NODE_R:
                cout << "node's value is: " << node->Element() << endl;
                break;
            case CMD_NODE_W:
                Data value;
                cin >> value;
                if (!std::cin)
                {
                    std::cin.clear();
                    ignoreLine();
                    std::cerr << "invalid input\n";
                }
                else
                {
                    node->Element() = value;
                    cout << "node's value has been updated to " << value << endl;
                }
                break;
            case CMD_NODE_L_C:
                cout << (node->HasLeftChild() ? "node doesn't have a left child" : "node has a left child") << endl;
                break;
            case CMD_NODE_R_C:
                cout << (node->HasRightChild() ? "node doesn't have a right child" : "node has a right child") << endl;
                break;
            case CMD_NODE_LEFT:
                if (node->HasLeftChild())
                {
                    node = &(node->LeftChild());
                    cout << "descended to left child" << endl;
                }
                else
                {
                    cout << "unable to descend to left child" << endl;
                }
                break;
            case CMD_NODE_RIGHT:
                // cout << node.Element() << endl;
                break;
            default:
                std::cerr << "invalid input\n";
                break;
            }
        }
    }
}

template <typename Data>
void treeMenu(lasd::BinaryTree<Data> &tree)
{
    printTreeCommands();

    bool exitRequest = false;
    int command = -1;

    while (!exitRequest)
    {
        cout << ">";
        cin >> command;

        if (!std::cin)
        {
            std::cin.clear();
            ignoreLine();
            std::cerr << "invalid input\n";
        }
        else
        {
            switch (command)
            {
            case CMD_QUIT:
                exitRequest = true;
                break;
            case CMD_HELP:
                printTreeCommands();
                break;
            case CMD_EMPTY:
                cout << "tree is" << (tree.Empty() ? "" : " not ") << "empty" << endl;
                break;
            case CMD_SIZE:
                cout << "tree has " << tree.Size() << " node(s)" << endl;
                break;
            case CMD_PRINT:
                break;

            case CMD_EMPTY:
                break;

            case CMD_EMPTY:
                break;
            case CMD_ROOT:
                if (tree.Empty())
                    cout << "can't access node menu because tree is empty" << endl;
                else
                    nodeMenu<Data>(&(tree.Root()));
                break;

            default:
                std::cerr << "invalid input\n";
                break;
            }
        }
    }

    // empty
    // size
    // root
    // left/right
    // map
    // fold
    // clear
    // iterator
    // exists
}

/* ************************************************************************** */

void customTest()
{
    // lasd::Vector<int> foo(10);
    // for (ulong i = 0; i < foo.Size(); i++)
    //     foo[i] = getRandomIntRange(0, 10);

    // lasd::Vector<int> bar(10);
    // for (ulong i = 0; i < bar.Size(); i++)
    //     bar[i] = getRandomIntRange(0, 10);

    // for (ulong i = 0; i < foo.Size(); i++)
    //     cout << foo[i] << " ";

    // cout << endl;

    // for (ulong i = 0; i < bar.Size(); i++)
    //     cout << bar[i] << " ";

    // cout << endl;

    // std::swap(foo, bar);

    // for (ulong i = 0; i < foo.Size(); i++)
    //     cout << foo[i] << " ";

    // cout << endl;

    // for (ulong i = 0; i < bar.Size(); i++)
    //     cout << bar[i] << " ";

    // cout << endl;

    lasd::Vector<int> vec(10);

    for (ulong i = 0; i < vec.Size(); i++)
        vec[i] = i;

    lasd::BinaryTreeVec<int> bt(vec);
    printTree(bt);

    // cout << "copy" << endl;
    // lasd::BinaryTreeVec<int> cop(vec);
    // printTree(bt);
    // printTree(cop);

    cout << "move" << endl;
    lasd::BinaryTreeVec<int> mov(std::move(bt));
    printTree(bt);
    printTree(mov);

    // lasd::BinaryTree<float> *tree = generateTree<float>(6, &getRandomFloat);

    // printTree(*tree);

    // tree->MapBreadth(&mapFloat, nullptr);
    // printTree(*tree);

    // lasd::BinaryTree<float>::Node &node = tree->Root().RightChild();
    // cout << node.Element() << endl;

    // treeMenu<float>(*tree);

    // cout << tree->Empty() << endl;

    // printTree<float>(*tree);

    // lasd::List<double> lst;
    // lst.InsertAtFront(0.3);
    // lst.InsertAtBack(3.0);
    // lst.InsertAtFront(1.2);
    // lst.InsertAtBack(2.1);

    // lasd::BinaryTreeLnk<double> bt(lst);
    // lasd::BinaryTree<double>::Node &node = bt.Root();

    // cout << bt.Exists(0.3) << endl;

    // if (node.HasLeftChild())
    // {
    //     cout << node.LeftChild().Element() << endl;

    //     if (node.LeftChild().HasRightChild())
    //         cout << node.RightChild().Element() << endl;

    //     cout << node.LeftChild().IsLeaf() << endl;
    // }

    // bt.Clear();
    // cout << bt.Empty() << endl;
}

void manualTest()
{
    // int command;
    // ulong size;

    // do
    // {
    //     try
    //     {
    //         flushInputBuffer();

    //         // printManualTestHelp();
    //         cout << ">";
    //         cin >> command;

    //         if (command != EXIT_COMMAND)
    //         {
    //             cin >> size;
    //         }
    //     }
    //     catch (...)
    //     {
    //     }
    // } while (command != EXIT_COMMAND);
}
