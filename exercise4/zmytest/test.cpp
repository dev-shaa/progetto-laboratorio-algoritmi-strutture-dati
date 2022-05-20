#include <iostream>
#include <functional>
#include <string>

#include "./utilities.hpp"
#include "../bst/bst.hpp"
#include "../binarytree/binarytree.hpp"
#include "../iterator/iterator.hpp"
#include "../list/list.hpp"
#include "../queue/queue.hpp"

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
#define CMD_MIN_READ 10
#define CMD_MIN_REMOVE 11
#define CMD_MIN_READ_REMOVE 12
#define CMD_MAX_READ 20
#define CMD_MAX_REMOVE 21
#define CMD_MAX_READ_REMOVE 22
#define CMD_PREDECESSOR_READ 30
#define CMD_PREDECESSOR_REMOVE 31
#define CMD_PREDECESSOR_READ_REMOVE 32
#define CMD_SUCCESSOR_READ 40
#define CMD_SUCCESSOR_REMOVE 41
#define CMD_SUCCESSOR_READ_REMOVE 42

#define PREORDER 0
#define POSTORDER 1
#define INORDER 2
#define BREADTH 3

#define CMD_TREE_INT 1
#define CMD_TREE_FLOAT 2
#define CMD_TREE_STRING 3

/* ************************************************************************** */

template <typename Data>
bool getData(Data &buffer)
{
    if (cin >> buffer)
    {
        return true;
    }
    else
    {
        handleInvalidInput();
        return false;
    }
}

template <typename Data>
void printMap(const Data &value, void *_)
{
    cout << value << " ";
}

template <typename Data>
void printTree(lasd::BinaryTree<Data> &tree, int traverseMode)
{
    if (tree.Empty())
    {
        cout << "tree is empty\n";
        return;
    }

    switch (traverseMode)
    {
    case PREORDER:
        cout << "printing in preorder: ";
        tree.MapPreOrder(&printMap<Data>, nullptr);
        break;
    case POSTORDER:
        cout << "printing in postorder: ";
        tree.MapPostOrder(&printMap<Data>, nullptr);
        break;
    case INORDER:
        cout << "printing in order: ";
        tree.MapInOrder(&printMap<Data>, nullptr);
        break;
    case BREADTH:
        cout << "printing breadth: ";
        tree.MapBreadth(&printMap<Data>, nullptr);
        break;
    default:
        cout << "traverse mode not valid";
        break;
    }

    cout << "\n";
}

template <typename Data>
void foldTreeOp(lasd::BinaryTree<Data> &tree, int traverseMode, function<void(const Data &, const void *, void *)> foldFunctor, Data &result)
{
    int n;

    if (getData<int>(n))
    {
        switch (traverseMode)
        {
        case PREORDER:
            tree.FoldPreOrder(foldFunctor, (void *)&n, (void *)&result);
            break;
        case POSTORDER:
            tree.FoldPostOrder(foldFunctor, (void *)&n, (void *)&result);
            break;
        case INORDER:
            tree.FoldInOrder(foldFunctor, (void *)&n, (void *)&result);
            break;
        case BREADTH:
            tree.FoldBreadth(foldFunctor, (void *)&n, (void *)&result);
            break;
        default:
            cout << "traverse mode not valid\n";
            return;
        }

        cout << "result is: " << result << endl;
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
         << "- " << CMD_PRINT << " [" << PREORDER << "/" << POSTORDER << "/" << INORDER << "/" << BREADTH << "] to print all elements of the tree in pre/post/in/breadth\n"
         << "- " << CMD_INSERT << " [value] to insert the element in the tree\n"
         << "- " << CMD_REMOVE << " [value] to remove the element from the tree\n"
         << "- " << CMD_FIND << " [value] to check if the element is in the tree\n\n"
         << "- " << CMD_FOLD << " [" << PREORDER << "/" << POSTORDER << "/" << INORDER << "/" << BREADTH << "] [n] to get " << foldDescription << " in pre/post/in/breadth\n\n"
         << "- " << CMD_MIN_READ << " to read the min\n"
         << "- " << CMD_MIN_REMOVE << " to remove the min\n"
         << "- " << CMD_MIN_READ_REMOVE << " to read and remove the min\n\n"
         << "- " << CMD_MAX_READ << " to read the max\n"
         << "- " << CMD_MAX_REMOVE << " to remove the max\n"
         << "- " << CMD_MAX_READ_REMOVE << " to read and remove the max\n\n"
         << "- " << CMD_PREDECESSOR_READ << " [value] to read the predecessor\n"
         << "- " << CMD_PREDECESSOR_REMOVE << " [value] to remove the predecessor\n"
         << "- " << CMD_PREDECESSOR_READ_REMOVE << " [value] to read and remove the predecessor\n\n"
         << "- " << CMD_SUCCESSOR_READ << " [value] to read the successor\n"
         << "- " << CMD_SUCCESSOR_REMOVE << " [value] to remove the successor\n"
         << "- " << CMD_SUCCESSOR_READ_REMOVE << " [value] to read and remove the successor\n\n";
}

template <typename Data>
void treeMenu(lasd::BST<Data> tree, function<void(const Data &, const void *, void *)> foldFunctor, string foldDescription, Data &result)
{
    int command;
    int bufferTraverseMode;
    Data bufferValue;

    printTreeCommands(foldDescription);

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
                    if (getData<int>(bufferTraverseMode))
                        printTree(tree, bufferTraverseMode);

                    break;
                case CMD_INSERT:
                    if (getData<Data>(bufferValue))
                    {
                        tree.Insert(bufferValue);
                        cout << bufferValue << " inserted\n";
                    }

                    break;
                case CMD_REMOVE:
                    if (getData<Data>(bufferValue))
                    {
                        tree.Remove(bufferValue);
                        cout << bufferValue << " removed\n";
                    }

                    break;
                case CMD_FIND:
                    if (getData<Data>(bufferValue))
                        cout << "value is" << (tree.Exists(bufferValue) ? " " : " not ") << "contained in the tree\n";

                    break;
                case CMD_MIN_READ:
                    cout << "min: " << tree.Min() << "\n";
                    break;
                case CMD_MIN_REMOVE:
                    tree.RemoveMin();
                    std::cout << "min removed\n";
                    break;
                case CMD_MIN_READ_REMOVE:
                    cout << tree.MinNRemove() << " removed\n";
                    break;
                case CMD_MAX_READ:
                    cout << "max: " << tree.Max() << "\n";
                    break;
                case CMD_MAX_REMOVE:
                    tree.RemoveMax();
                    std::cout << "max removed\n";
                    break;
                case CMD_MAX_READ_REMOVE:
                    cout << tree.MaxNRemove() << " removed\n";
                    break;
                case CMD_PREDECESSOR_READ:
                    if (getData<Data>(bufferValue))
                        cout << "predecessor: " << tree.Predecessor(bufferValue) << "\n";

                    break;
                case CMD_PREDECESSOR_REMOVE:
                    if (getData<Data>(bufferValue))
                    {
                        tree.RemovePredecessor(bufferValue);
                        std::cout << "predecessor removed\n";
                    }

                    break;
                case CMD_PREDECESSOR_READ_REMOVE:
                    if (getData<Data>(bufferValue))
                        cout << tree.PredecessorNRemove(bufferValue) << " removed\n";

                    break;
                case CMD_SUCCESSOR_READ:
                    if (getData<Data>(bufferValue))
                        cout << "successor: " << tree.Successor(bufferValue) << "\n";

                    break;
                case CMD_SUCCESSOR_REMOVE:
                    if (getData<Data>(bufferValue))
                    {
                        tree.RemoveSuccessor(bufferValue);
                        std::cout << "successor removed\n";
                    }

                    break;
                case CMD_SUCCESSOR_READ_REMOVE:
                    if (getData<Data>(bufferValue))
                        cout << tree.SuccessorNRemove(bufferValue) << " removed\n";

                    break;
                case CMD_FOLD:
                    if (getData<int>(bufferTraverseMode))
                        foldTreeOp(tree, bufferTraverseMode, foldFunctor, result);

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
    cout << "available commands:\n"
         << "- " << CMD_QUIT << " to return to main menu\n"
         << "- " << CMD_TREE_INT << " [size] to create a new int tree\n"
         << "- " << CMD_TREE_FLOAT << " [size] to create a new float tree\n"
         << "- " << CMD_TREE_STRING << " [size] to create a new string tree\n";
}

void manualTest()
{
    int command;
    ulong size;

    do
    {
        printInfo();
        cout << ">";

        if (getData<int>(command))
        {
            if (command == CMD_QUIT)
            {
                break;
            }
            else if (getData<ulong>(size))
            {
                cout << "\n";

                switch (command)
                {
                case CMD_TREE_INT:
                {
                    int prod = 1;
                    treeMenu<int>(generateTree<int>(size, &getRandomInt), &foldInt, "product of int < n", prod);
                    break;
                }
                case CMD_TREE_FLOAT:
                {
                    float sum = 0;
                    treeMenu<float>(generateTree<float>(size, &getRandomFloat), &foldFloat, "sum of float > n", sum);
                    break;
                }
                case CMD_TREE_STRING:
                {
                    string concat;
                    treeMenu<string>(generateTree<string>(size, &getRandomString), &foldString, "concat of string shorter than n", concat);
                    break;
                }
                }
            }
        }
    } while (true);
}