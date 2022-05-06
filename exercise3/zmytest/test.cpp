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
#include "../stack/vec/stackvec.hpp"
#include "../iterator/iterator.hpp"

using namespace std;

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

/* ************************************************************************** */

template <typename Data>
void printMap(const Data &value, void *_)
{
    cout << value << " ";
}

template <typename Data>
void printTree(lasd::BinaryTree<Data> &tree, TraverseType type)
{
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

    cout << endl;
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

void printInfo()
{
    cout << "manual test menu placeholder" << endl;
}

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

void printIteratorCommands()
{
    std::cout << "iterator menu placeholder" << std::endl;
}

template <typename Data>
void iteratorMenu(lasd::ForwardIterator<Data> &iterator)
{
    printIteratorCommands();

    bool exitRequest = false;
    int command;

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
            case 0:
                exitRequest = true;
                std::cout << "returning to tree menu\n";
                break;
            case 1:
                std::cout << "iterator has" << (iterator.Terminated() ? "" : " not ") << "terminated\n";
                break;
            case 2:
                if (iterator.Terminated())
                    std::cout << "can't access because iterator has terminated\n";
                else
                {
                    ++iterator;
                    std::cout << "progressed to next element\n";
                }
                break;
            case 3:
                if (iterator.Terminated())
                    std::cout << "can't progess further because iterator has terminated\n";
                else
                {
                    ++iterator;
                    std::cout << "progressed to next element\n";
                }
                break;
            case 4:
                ((lasd::ResettableIterator<Data> &)iterator).Reset();
                break;
            default:
                std::cerr << "invalid input\n";
                break;
            }
        }
    }
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
            case CMD_ROOT:
                if (tree.Empty())
                    cout << "can't access node menu because tree is empty" << endl;
                else
                    nodeMenu<Data>(&(tree.Root()));
                break;
            case CMD_ITERATOR:
                TraverseType traverse;

                if (cin >> traverse)
                    iteratorMenu<Data>(*generateIterator<Data>(tree, traverse));
                else
                    std::cerr << "invalid input\n";

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
        cin >> implementation >> datatype >> size;

        if (!std::cin)
        {
            std::cin.clear();
            ignoreLine();
            std::cerr << "invalid input\n";
        }
        else
        {
            switch (datatype)
            {
            case DataType::Int:
                treeMenu<int>(*generateTree<int>(implementation, size, &getRandomInt));
                break;
            case DataType::Float:
                treeMenu<float>(*generateTree<float>(implementation, size, &getRandomFloat));
                break;
            case DataType::String:
                treeMenu<string>(*generateTree<string>(implementation, size, &getRandomString));
                break;
            }
        }
    } while (!exitRequest);
}
