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
  protected:
    ulong size = 0;

  public:
    virtual ~Container() = default;

    /* ************************************************************************ */

    Container &operator=(const Container &other) = delete;
    Container &operator=(Container &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const Container &other) const noexcept = delete;
    bool operator!=(const Container &other) const noexcept = delete;

    /* ************************************************************************ */

    inline virtual bool Empty() const noexcept;

    inline virtual ulong Size() const noexcept;

    virtual void Clear() = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class LinearContainer : virtual public Container
  {

  public:
    virtual ~LinearContainer() = default;

    /* ************************************************************************ */

    LinearContainer &operator=(const LinearContainer &other) = delete;
    LinearContainer &operator=(LinearContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const LinearContainer &other) const noexcept;
    bool operator!=(const LinearContainer &other) const noexcept;

    /* ************************************************************************ */

    virtual Data &operator[](const ulong index) const = 0;

    virtual Data &Front() const;

    virtual Data &Back() const;
  };

  /* ************************************************************************** */

  template <typename Data>
  class TestableContainer : virtual public Container
  {
  public:
    virtual ~TestableContainer() = default;

    /* ************************************************************************ */

    TestableContainer &operator=(const TestableContainer &other) = delete;
    TestableContainer &operator=(TestableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const TestableContainer &other) const noexcept = delete;
    bool operator!=(const TestableContainer &other) const noexcept = delete;

    /* ************************************************************************ */
    virtual bool Exists(const Data &item) const noexcept = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class MappableContainer : virtual public Container
  {
  public:
    virtual ~MappableContainer() = default;

    /* ************************************************************************ */

    MappableContainer &operator=(const MappableContainer &other) = delete;
    MappableContainer &operator=(MappableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const MappableContainer &other) const noexcept = delete;
    bool operator!=(const MappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */
    typedef std::function<void(Data &, void *)> MapFunctor;

    virtual void Map(MapFunctor, void *) = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class FoldableContainer : virtual public TestableContainer
  {
  public:
    virtual ~FoldableContainer() = default;

    /* ************************************************************************ */

    FoldableContainer &operator=(const FoldableContainer &other) = delete;
    FoldableContainer &operator=(FoldableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const FoldableContainer &other) const noexcept = delete;
    bool operator!=(const FoldableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    typedef std::function<void(const Data &, const void *, void *)> FoldFunctor;

    virtual void Fold(FoldFunctor functor, const void *initialValue, void *supportValue) const = 0;

    /* ************************************************************************ */

    virtual bool Exists(const Data &item) const noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderMappableContainer : virtual public MappableContainer
  {
  public:
    virtual ~PreOrderMappableContainer() = default;

    /* ************************************************************************ */

    PreOrderMappableContainer &operator=(const PreOrderMappableContainer &other) = delete;
    PreOrderMappableContainer &operator=(PreOrderMappableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const PreOrderMappableContainer &other) const noexcept = delete;
    bool operator!=(const PreOrderMappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapPreOrder(MapFunctor functor, void *) = 0;

    /* ************************************************************************ */

    virtual void Map(MapFunctor, void *) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderFoldableContainer : virtual public FoldableContainer
  {
  public:
    virtual ~PreOrderFoldableContainer() = default;

    /* ************************************************************************ */

    PreOrderFoldableContainer &operator=(const PreOrderFoldableContainer &other) = delete;
    PreOrderFoldableContainer &operator=(PreOrderFoldableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const PreOrderFoldableContainer &other) const noexcept = delete;
    bool operator!=(const PreOrderFoldableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void FoldInOrder(FoldFunctor, const void *, void *) = 0;

    /* ************************************************************************ */

    virtual void Fold(FoldFunctor, const void *, void *) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderMappableContainer : virtual public MappableContainer
  {
  public:
    virtual ~PostOrderMappableContainer() = default;

    /* ************************************************************************ */

    PostOrderMappableContainer &operator=(const PostOrderMappableContainer &other) = delete;
    PostOrderMappableContainer &operator=(PostOrderMappableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const PostOrderMappableContainer &other) const noexcept = delete;
    bool operator!=(const PostOrderMappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapPostOrder(MapFunctor, void *) = 0; // NOTE: doveva essere chiamato preorder?

    /* ************************************************************************ */

    virtual void Map(MapFunctor, void *) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderFoldableContainer : FoldableContainer<Data>
  {
  public:
    virtual ~PostOrderFoldableContainer() = default;

    /* ************************************************************************ */

    PostOrderFoldableContainer &operator=(const PostOrderFoldableContainer &other) = delete;
    PostOrderFoldableContainer &operator=(PostOrderFoldableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const PostOrderFoldableContainer &other) const noexcept = delete;
    bool operator!=(const PostOrderFoldableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void FoldPostOrder(FoldFunctor, const void *, void *) = 0;

    /* ************************************************************************ */

    virtual void Fold(FoldFunctor, const void *, void *) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class InOrderMappableContainer : MappableContainer<Data>
  {

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
  class InOrderFoldableContainer : virtual public FoldableContainer
  {

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
  class BreadthMappableContainer : MappableContainer<Data>
  {

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
  class BreadthFoldableContainer : FoldableContainer<Data>
  {

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
