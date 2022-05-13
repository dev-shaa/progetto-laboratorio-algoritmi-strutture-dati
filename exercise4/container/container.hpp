#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <stdexcept>
#include <functional>

namespace lasd
{

  /* ************************************************************************** */

  class Container
  {
  public:
    virtual ~Container() = default;

    /* ************************************************************************ */

    Container &operator=(const Container &other) = delete;
    Container &operator=(Container &&other) noexcept = delete;

    bool operator==(const Container &other) const noexcept = delete;
    bool operator!=(const Container &other) const noexcept = delete;

    /* ************************************************************************ */

    virtual bool Empty() const noexcept = 0;
    virtual ulong Size() const noexcept = 0;
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

    bool operator==(const LinearContainer &other) const noexcept;
    bool operator!=(const LinearContainer &other) const noexcept;

    virtual Data &operator[](const ulong index) const = 0;

    /* ************************************************************************ */

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

    bool operator==(const TestableContainer &other) const noexcept = delete;
    bool operator!=(const TestableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    virtual bool Exists(const Data &value) const noexcept = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class DictionaryContainer : virtual public TestableContainer<Data>
  {
  public:
    virtual ~DictionaryContainer() = default;

    /* ************************************************************************ */

    DictionaryContainer &operator=(const DictionaryContainer &other) = delete;
    DictionaryContainer &operator=(DictionaryContainer &&other) noexcept = delete;

    bool operator==(const DictionaryContainer &other) const noexcept = delete;
    bool operator!=(const DictionaryContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    void Insert(const Data &value);
    void Insert(Data &&value);
    void Remove(const Data &value);
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

    bool operator==(const MappableContainer &other) const noexcept = delete;
    bool operator!=(const MappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    typedef std::function<void(Data &, void *)> MapFunctor;

    virtual void Map(MapFunctor functor, void *par) = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class FoldableContainer : virtual public TestableContainer<Data>
  {
  public:
    virtual ~FoldableContainer() = default;

    /* ************************************************************************ */

    FoldableContainer &operator=(const FoldableContainer &other) = delete;
    FoldableContainer &operator=(FoldableContainer &&other) noexcept = delete;

    bool operator==(const FoldableContainer &other) const noexcept = delete;
    bool operator!=(const FoldableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    typedef std::function<void(const Data &, const void *, void *)> FoldFunctor;

    virtual void Fold(FoldFunctor functor, const void *par, void *accumulator) const = 0;

    /* ************************************************************************ */

    bool Exists(const Data &value) const noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderMappableContainer : virtual public MappableContainer<Data>
  {
  public:
    virtual ~PreOrderMappableContainer() = default;

    /* ************************************************************************ */

    PreOrderMappableContainer &operator=(const PreOrderMappableContainer &other) = delete;
    PreOrderMappableContainer &operator=(PreOrderMappableContainer &&other) noexcept = delete;

    bool operator==(const PreOrderMappableContainer &other) const noexcept = delete;
    bool operator!=(const PreOrderMappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapPreOrder(MapFunctor functor, void *par) = 0;
    void Map(MapFunctor functor, void *par) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderFoldableContainer : virtual public FoldableContainer<Data>
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

    using typename FoldableContainer<Data>::FoldFunctor;

    virtual void FoldPreOrder(FoldFunctor functor, const void *par, void *accumulator) const = 0;
    virtual void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderMappableContainer : virtual public MappableContainer<Data>
  {
  public:
    virtual ~PostOrderMappableContainer() = default;

    /* ************************************************************************ */

    PostOrderMappableContainer &operator=(const PostOrderMappableContainer &other) = delete;
    PostOrderMappableContainer &operator=(PostOrderMappableContainer &&other) noexcept = delete;

    bool operator==(const PostOrderMappableContainer &other) const noexcept = delete;
    bool operator!=(const PostOrderMappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapPostOrder(MapFunctor functor, void *par) = 0;
    void Map(MapFunctor functor, void *par) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderFoldableContainer : virtual public FoldableContainer<Data>
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

    using typename FoldableContainer<Data>::FoldFunctor;

    virtual void FoldPostOrder(FoldFunctor functor, const void *par, void *accumulator) const = 0;
    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class InOrderMappableContainer : virtual public MappableContainer<Data>
  {
  public:
    virtual ~InOrderMappableContainer() = default;

    /* ************************************************************************ */

    InOrderMappableContainer &operator=(const InOrderMappableContainer &other) = delete;
    InOrderMappableContainer &operator=(InOrderMappableContainer &&other) noexcept = delete;

    bool operator==(const InOrderMappableContainer &other) const noexcept = delete;
    bool operator!=(const InOrderMappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapInOrder(MapFunctor functor, void *par) = 0;
    void Map(MapFunctor functor, void *par) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class InOrderFoldableContainer : virtual public FoldableContainer<Data>
  {
  public:
    virtual ~InOrderFoldableContainer() = default;

    /* ************************************************************************ */

    InOrderFoldableContainer &operator=(const InOrderFoldableContainer &other) = delete;
    InOrderFoldableContainer &operator=(InOrderFoldableContainer &&other) noexcept = delete;

    /* ************************************************************************ */

    bool operator==(const InOrderFoldableContainer &other) const noexcept = delete;
    bool operator!=(const InOrderFoldableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename FoldableContainer<Data>::FoldFunctor;

    virtual void FoldInOrder(FoldFunctor functor, const void *par, void *accumulator) const = 0;
    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BreadthMappableContainer : virtual public MappableContainer<Data>
  {
  public:
    virtual ~BreadthMappableContainer() = default;

    /* ************************************************************************ */

    BreadthMappableContainer &operator=(const BreadthMappableContainer &other) = delete;
    BreadthMappableContainer &operator=(BreadthMappableContainer &&other) noexcept = delete;

    bool operator==(const BreadthMappableContainer &other) const noexcept = delete;
    bool operator!=(const BreadthMappableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapBreadth(MapFunctor functor, void *par) = 0;
    void Map(MapFunctor functor, void *par) override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BreadthFoldableContainer : virtual public FoldableContainer<Data>
  {
  public:
    virtual ~BreadthFoldableContainer() = default;

    /* ************************************************************************ */

    BreadthFoldableContainer &operator=(const BreadthFoldableContainer &other) = delete;
    BreadthFoldableContainer &operator=(BreadthFoldableContainer &&other) noexcept = delete;

    bool operator==(const BreadthFoldableContainer &other) const noexcept = delete;
    bool operator!=(const BreadthFoldableContainer &other) const noexcept = delete;

    /* ************************************************************************ */

    using typename FoldableContainer<Data>::FoldFunctor;

    virtual void FoldBreadth(FoldFunctor functor, const void *par, void *accumulator) const = 0;
    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;
  };

  /* ************************************************************************** */

}

#include "container.cpp"

#endif
