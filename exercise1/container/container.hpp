#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  class Container
  {

  private:
    // ...

  protected:
    // ...

  public:
    ~Container()
    {
      Clear();
    }

    /* ************************************************************************ */

    Container &operator=(const Container &other) const noexcept = delete;
    Container &operator=(const Container &&other) const noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const Container &other) const noexcept = delete;
    bool operator!=(const Container &other) const noexcept = delete;

    /* ************************************************************************ */

    virtual bool Empty() noexcept = 0;

    virtual uint Size() noexcept = 0;

    virtual void Clear() = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class LinearContainer : Container
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is possible.

    /* ************************************************************************ */

    virtual Data operator[](uint index) throw std::out_of_range = 0;

    Data *Front() final;

    Data *Back() final;
  };

  /* ************************************************************************** */

  template <typename Data>
  class TestableContainer : Container
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~TestableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    virtual bool Exists(Data item) const noexcept = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class MappableContainer
  { // Must extend Container

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~MappableContainer() specifiers

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    typedef std::function<void(Data &, void *)> MapFunctor;

    // type Map(arguments) specifiers;
  };

  /* ************************************************************************** */

  template <typename Data>
  class FoldableContainer
  { // Must extend TestableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~FoldableContainer() specifiers

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // typedef std::function<void(const Data&, const void*, void*)> FoldFunctor;

    // type Fold(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from TestableContainer)

    // type Exists(argument) specifiers; // Override TestableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderMappableContainer : MappableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~PreOrderMappableContainer() specifiers

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderFoldableContainer
  { // Must extend FoldableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~PreOrderFoldableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type FoldInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderMappableContainer
  { // Must extend MappableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~PostOrderMappableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderFoldableContainer
  { // Must extend FoldableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~PostOrderFoldableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type FoldInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class InOrderMappableContainer
  { // Must extend MappableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~InOrderMappableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class InOrderFoldableContainer
  { // Must extend FoldableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~InOrderFoldableContainer() specifiers

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type FoldInOrder(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class BreadthMappableContainer
  { // Must extend MappableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~BreadthMappableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename MappableContainer<Data>::MapFunctor;

    // type MapBreadth(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    // type Map(argument) specifiers; // Override MappableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class BreadthFoldableContainer
  { // Must extend FoldableContainer<Data>

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    // ~BreadthFoldableContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types should not be possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types might not be possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    // using typename FoldableContainer<Data>::FoldFunctor;

    // type FoldBreadth(arguments) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)

    // type Fold(argument) specifiers; // Override FoldableContainer member
  };

  /* ************************************************************************** */

}

#include "container.cpp"

#endif
