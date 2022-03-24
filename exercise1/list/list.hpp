
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class List : LinearContainer<Data>, PreOrderMappableContainer<Data>, PostOrderMappableContainer<Data>, PreOrderFoldableContainer<Data>, PostOrderFoldableContainer<Data>
  {

  private:
    // ...

  protected:
    // using LinearContainer<Data>::???;

    struct Node
    {
      Data item;
      Node *next;

      /* ********************************************************************** */

      // Specific constructors
      // ...

      /* ********************************************************************** */

      // Copy constructor
      // ...

      // Move constructor
      // ...

      /* ********************************************************************** */

      // Destructor
      // ...

      /* ********************************************************************** */

      // Comparison operators
      // ...

      bool operator==(const Node &other)
      {
        return item == other.item;
      }

      /* ********************************************************************** */

      // Specific member functions

      // ...
    };

    // ...

  public:
    // Default constructor
    // List() specifiers;
    List()
    {
    }

    /* ************************************************************************ */

    // Specific constructor
    // List(argument) specifiers; // A list obtained from a LinearContainer
    List(LinearContainer linearContainer)
    {
    }

    /* ************************************************************************ */

    // Copy constructor
    // List(argument) specifiers;

    // Move constructor
    // List(argument) specifiers;

    /* ************************************************************************ */

    // Destructor
    // ~List() specifiers;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;

    /* ************************************************************************ */

    // Specific member functions

    // type InsertAtFront(argument) specifier; // Copy of the value
    // type InsertAtFront(argument) specifier; // Move of the value
    // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
    // type FrontNRemove() specifier; // (must throw std::length_error when empty)

    // type InsertAtBack(argument) specifier; // Copy of the value
    // type InsertAtBack(argument) specifier; // Move of the value

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    // type Clear() specifiers; // Override Container member

    void Clear() override
    {
    }

    /* ************************************************************************ */

    Data operator[](uint index) override throw std::out_of_range
    {
      if (index < 0 || index > Size())
        throw std::out_of_range("index out of range");

      // TODO: implementa
    }

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // using typename MappableContainer<Data>::MapFunctor;

    // type Map(arguments) specifiers; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderMappableContainer)

    // type MapPreOrder(arguments) specifiers; // Override PreOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderMappableContainer)

    // type MapPostOrder(arguments) specifiers; // Override PostOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // using typename FoldableContainer<Data>::FoldFunctor;

    // type Fold(arguments) specifiers; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PreOrderFoldableContainer)

    // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from PostOrderFoldableContainer)

    // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member

  protected:
    // Auxiliary member functions (for PreOrderMappableContainer & PostOrderMappableContainer)

    // type MapPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
    // type MapPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards

    /* ************************************************************************ */

    // Auxiliary member functions (for PreOrderFoldableContainer & PostOrderFoldableContainer)

    // type FoldPreOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
    // type FoldPostOrder(arguments) specifiers; // Accessory function executing from one point of the list onwards
  };

  /* ************************************************************************** */

}

#include "list.cpp"

#endif
