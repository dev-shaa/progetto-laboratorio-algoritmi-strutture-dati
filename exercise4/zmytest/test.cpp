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

// /* ************************************************************************** */

// template <typename Data>
// void printMap(const Data &value, void *_)
// {
//     cout << value << " ";
// }

// template <typename Data>
// void printTree(lasd::BinaryTree<Data> &tree, TraverseType type)
// {
//     if (tree.Empty())
//     {
//         cout << "tree is empty\n";
//         return;
//     }

//     switch (type)
//     {
//     case PreOrder:
//         tree.MapPreOrder(&printMap<Data>, nullptr);
//         break;
//     case PostOrder:
//         tree.MapPostOrder(&printMap<Data>, nullptr);
//         break;
//     case InOrder:
//         tree.MapInOrder(&printMap<Data>, nullptr);
//         break;
//     case Breadth:
//         tree.MapBreadth(&printMap<Data>, nullptr);
//         break;
//     }

//     cout << "\n";
// }

// template <typename Data>
// void foldTreeOp(lasd::BinaryTree<Data> &tree, TraverseType type, function<void(const Data &, const void *, void *)> foldFunctor, Data &result)
// {
//     int n;

//     if (cin >> n)
//     {
//         switch (type)
//         {
//         case PreOrder:
//             tree.FoldPreOrder(foldFunctor, (void *)&n, (void *)&result);
//             break;
//         case PostOrder:
//             tree.FoldPostOrder(foldFunctor, (void *)&n, (void *)&result);
//             break;
//         case InOrder:
//             tree.FoldInOrder(foldFunctor, (void *)&n, (void *)&result);
//             break;
//         case Breadth:
//             tree.FoldBreadth(foldFunctor, (void *)&n, (void *)&result);
//             break;
//         }

//         cout << "result is: " << result << endl;
//     }
//     else
//     {
//         handleInvalidInput();
//     }
// }

// template <typename Data>
// lasd::BST<Data> generateTree(ulong size, function<Data()> getRandomValue)
// {
//     lasd::BST<Data> tree;

//     for (ulong i = 0; i < size; i++)
//         tree.Insert(getRandomValue());

//     return tree;
// }

// template <typename Data>
// bool getData(Data &buffer)
// {
//     if (cin >> buffer)
//     {
//         return true;
//     }
//     else
//     {
//         handleInvalidInput();
//         return false;
//     }
// }

// /* ************************************************************************** */

// #define CMD_QUIT 0
// #define CMD_HELP 1
// #define CMD_EMPTY 2
// #define CMD_SIZE 3
// #define CMD_PRINT 4
// #define CMD_CLEAR 5
// #define CMD_INSERT 6
// #define CMD_REMOVE 7
// #define CMD_FIND 8
// #define CMD_MIN_READ 9
// #define CMD_MIN_REMOVE 10
// #define CMD_MIN_READ_REMOVE 11
// #define CMD_MAX_READ 12
// #define CMD_MAX_REMOVE 13
// #define CMD_MAX_READ_REMOVE 14
// #define CMD_PREDECESSOR_READ 15
// #define CMD_PREDECESSOR_REMOVE 16
// #define CMD_PREDECESSOR_READ_REMOVE 17
// #define CMD_SUCCESSOR_READ 18
// #define CMD_SUCCESSOR_REMOVE 19
// #define CMD_SUCCESSOR_READ_REMOVE 20
// #define CMD_FOLD 21

// void printTreeCommands(string foldDescription)
// {
//     // cout << "available tree commands:\n"
//     //      << "- " << CMD_QUIT << " to return to main menu\n"
//     //      << "- " << CMD_HELP << " to print this helper\n"
//     //      << "- " << CMD_EMPTY << " to check if tree is empty\n"
//     //      << "- " << CMD_SIZE << " to print tree size\n"
//     //      << "- " << CMD_CLEAR << " to clear the tree\n"
//     //      << "- " << CMD_ROOT << " to access the root\n"
//     //      << "- " << CMD_PRINT << " ['pr'eorder/'po'storder/'in'order/'br'eadth] to print all elements of the tree\n"
//     //      << "- " << CMD_FOLD << " ['pr'eorder/'po'storder/'in'order/'br'eadth] [n] to get " << foldDescription << "\n"
//     //      << "- " << CMD_ITERATOR << " ['pr'eorder/'po'storder/'in'order/'br'eadth] to traverse via iterator\n"
// }

// template <typename Data>
// void treeMenu(lasd::BST<Data> tree, function<void(const Data &, const void *, void *)> foldFunctor, string foldDescription, Data &result)
// {
//     int command;
//     Data bufferValue;
//     TraverseType bufferTraverseMode;
//     bool exitRequest = false;

//     printTreeCommands(foldDescription);

//     do
//     {
//         cout << ">";

//         if (cin >> command)
//         {
//             try
//             {
//                 switch (command)
//                 {
//                 case CMD_QUIT:
//                     exitRequest = true;
//                     break;
//                 case CMD_HELP:
//                     printTreeCommands(foldDescription);
//                     break;
//                 case CMD_EMPTY:
//                     cout << "tree is" << (tree.Empty() ? " " : " not ") << "empty\n";
//                     break;
//                 case CMD_SIZE:
//                     cout << "tree has " << tree.Size() << " node(s)\n";
//                     break;
//                 case CMD_CLEAR:
//                     tree.Clear();
//                     cout << "tree has been cleared\n";
//                     break;
//                 case CMD_PRINT:
//                     if (getData<TraverseType>(bufferTraverseMode))
//                         printTree(tree, bufferTraverseMode);

//                     break;
//                 case CMD_INSERT:
//                     if (getData<Data>(bufferValue))
//                     {
//                         tree.Insert(bufferValue);
//                         cout << "value inserted\n";
//                     }

//                     break;
//                 case CMD_REMOVE:
//                     if (getData<Data>(bufferValue))
//                     {
//                         tree.Remove(bufferValue);
//                         cout << "value removed\n";
//                     }

//                     break;
//                 case CMD_FIND:
//                     if (getData<Data>(bufferValue))
//                         cout << "value is" << (tree.Exists(bufferValue) ? " " : " not ") << "contained in the tree\n";

//                     break;
//                 case CMD_MIN_READ:
//                     cout << tree.Min() << "\n";
//                     break;
//                 case CMD_MIN_REMOVE:
//                     tree.RemoveMin();
//                     std::cout << "min removed\n";
//                     break;
//                 case CMD_MIN_READ_REMOVE:
//                     cout << tree.MinNRemove() << " removed\n";
//                     break;
//                 case CMD_MAX_READ:
//                     cout << tree.Max() << "\n";
//                     break;
//                 case CMD_MAX_REMOVE:
//                     tree.RemoveMax();
//                     std::cout << "max removed\n";
//                     break;
//                 case CMD_MAX_READ_REMOVE:
//                     cout << tree.MaxNRemove() << " removed\n";
//                     break;
//                 case CMD_PREDECESSOR_READ:
//                     if (getData<Data>(bufferValue))
//                         cout << tree.Predecessor(bufferValue) << "\n";

//                     break;
//                 case CMD_PREDECESSOR_REMOVE:
//                     if (getData<Data>(bufferValue))
//                     {
//                         tree.RemovePredecessor(bufferValue);
//                         std::cout << "predecessor removed\n";
//                     }

//                     break;
//                 case CMD_PREDECESSOR_READ_REMOVE:
//                     if (getData<Data>(bufferValue))
//                         cout << tree.PredecessorNRemove(bufferValue) << " removed\n";

//                     break;
//                 case CMD_SUCCESSOR_READ:
//                     if (getData<Data>(bufferValue))
//                         cout << tree.Successor(bufferValue) << "\n";

//                     break;
//                 case CMD_SUCCESSOR_REMOVE:
//                     if (getData<Data>(bufferValue))
//                     {
//                         tree.RemoveSuccessor(bufferValue);
//                         std::cout << "successor removed\n";
//                     }

//                     break;
//                 case CMD_SUCCESSOR_READ_REMOVE:
//                     if (getData<Data>(bufferValue))
//                         cout << tree.SuccessorNRemove(bufferValue) << " removed\n";

//                     break;
//                 case CMD_FOLD:
//                     if (getData<TraverseType>(bufferTraverseMode))
//                         foldTreeOp(tree, bufferTraverseMode, foldFunctor, result);

//                     break;
//                 default:
//                     std::cerr << "no command found\n";
//                     break;
//                 }
//             }
//             catch (const std::exception &e)
//             {
//                 std::cerr << "an exception occurred: " << e.what() << '\n';
//             }
//         }
//         else
//         {
//             handleInvalidInput();
//         }
//     } while (!exitRequest);
// }

// /* ************************************************************************** */

// void printInfo()
// {
//     cout << "available commands:\n- " << CMD_QUIT << " to return to main menu\n- c ['v'ector/'l'inked] ['i'nt/'f'loat/'s'tring] [size] to create a new tree\n";
// }

// void manualTest()
// {
//     int command;
//     DataType datatype;
//     ulong size;
//     bool exitRequest = false;

//     do
//     {
//         printInfo();
//         cout << ">";

//         if (cin >> command)
//         {
//             if (command == CMD_QUIT)
//                 exitRequest = true;
//             else if (command == 'c' && cin >> datatype >> size)
//             {
//                 flushLine();

//                 switch (datatype)
//                 {
//                 case DataType::Int:
//                 {
//                     int prod = 1;
//                     treeMenu<int>(generateTree<int>(size, &getRandomInt), &foldInt, "product of int < n", prod);
//                     break;
//                 }
//                 case DataType::Float:
//                 {
//                     float sum = 0;
//                     treeMenu<float>(generateTree<float>(size, &getRandomFloat), &foldFloat, "sum of float > n", sum);
//                     break;
//                 }
//                 case DataType::String:
//                 {
//                     string concat;
//                     treeMenu<string>(generateTree<string>(size, &getRandomString), &foldString, "concat of string shorter than n", concat);
//                     break;
//                 }
//                 }
//             }
//             else
//             {
//                 handleInvalidInput();
//             }
//         }
//         else
//         {
//             handleInvalidInput();
//         }

//     } while (!exitRequest);
// }

void manualTest()
{
    // lasd::BinaryTree<int> *tree = new lasd::BinaryTreeLnk<int>();

    // std::cout << "empty: " << tree->Empty() << std::endl;
    // std::cout << "size: " << tree->Size() << std::endl;
    // std::cout << "exists: " << tree->Exists(0) << std::endl;

    lasd::List<int> lst;
    lst.InsertAtFront(0);
    lst.InsertAtBack(1);
    lst.InsertAtBack(2);

    lasd::BinaryTree<int> *tree = new lasd::BinaryTreeLnk<int>(lst);

    std::cout << "empty: " << tree->Empty() << std::endl;
    std::cout << "size: " << tree->Size() << std::endl;
    std::cout << "exists: " << tree->Exists(0) << std::endl;
    tree->Clear();
    std::cout << "empty: " << tree->Empty() << std::endl;
    std::cout << "size: " << tree->Size() << std::endl;
    std::cout << "exists: " << tree->Exists(0) << std::endl;
}