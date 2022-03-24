#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Vector : LinearContainer<Data>, PreOrderMappableContainer<Data>, PostOrderMappableContainer<Data>, PreOrderFoldableContainer<Data>, PostOrderFoldableContainer<Data>
  {

  private:
    // ...
    Data *array;

  protected:
    // using LinearContainer<Data>::???;

    // ...

  public:
    // Default constructor
    // Vector() specifiers;
    Vector()
    {
      Vector(10);
    }

    /* ************************************************************************ */

    // Specific constructors
    // Vector(argument) specifiers; // A vector with a given initial dimension
    // Vector(argument) specifiers; // A vector obtained from a LinearContainer

    Vector(uint capacity)
    {
      array = new Data[capacity];
      // TODO: set size
    }

    /* ************************************************************************ */

    // Copy constructor
    // Vector(argument) specifiers;

    // Move constructor
    // Vector(argument) specifiers;

    /* ************************************************************************ */

    // Destructor
    // ~Vector() specifiers;

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

    // type Resize(argument) specifiers; // Resize the vector to a given size

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    // type Clear() specifiers; // Override Container member
    void Clear() override
    {
      delete array;
      // TODO: set size
    }

    /* ************************************************************************ */

    Data operator[](uint index) override throw std::out_of_range
    {
      if (index < 0 || index > Size())
        throw std::out_of_range("index out of range");

      return array[index];
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
  };

  /* ************************************************************************** */

}

#include "vector.cpp"

#endif
