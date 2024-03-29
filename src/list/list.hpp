#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class List : virtual public LinearContainer<Data>,
               virtual public PreOrderMappableContainer<Data>,
               virtual public PostOrderMappableContainer<Data>,
               virtual public PreOrderFoldableContainer<Data>,
               virtual public PostOrderFoldableContainer<Data>
  {
  protected:
    struct Node
    {
      Data value;
      Node *next = nullptr;

      /* ********************************************************************** */

      Node() = default;
      Node(const Data &value);
      Node(Data &&value) noexcept;
      Node(const Node &node);
      Node(Node &&node) noexcept;

      virtual ~Node() = default;

      /* ********************************************************************** */

      Node &operator=(const Node &other);
      Node &operator=(Node &&other) noexcept;

      bool operator==(const Node &other) const noexcept;
      bool operator!=(const Node &other) const noexcept;
    };

    ulong size = 0;
    Node *start = nullptr;
    Node *end = nullptr;

  public:
    List() = default;
    List(const LinearContainer<Data> &linearContainer);
    List(const List &list);
    List(List &&list) noexcept;

    virtual ~List();

    /* ************************************************************************ */

    List &operator=(const List &other);
    List &operator=(List &&other) noexcept;

    bool operator==(const List &other) const noexcept;
    bool operator!=(const List &other) const noexcept;

    Data &operator[](const ulong index) const override;

    /* ************************************************************************ */

    void InsertAtFront(const Data &item);
    void InsertAtFront(Data &&item) noexcept;
    void RemoveFromFront();
    Data &FrontNRemove();
    void InsertAtBack(const Data &item);
    void InsertAtBack(Data &&item) noexcept;

    /* ************************************************************************ */

    Data &Front() const override;
    Data &Back() const override;
    void Clear() override;
    bool Empty() const noexcept override;
    ulong Size() const noexcept override;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    void Map(MapFunctor functor, void *par) override;
    void MapPreOrder(MapFunctor functor, void *par) override;
    void MapPostOrder(MapFunctor functor, void *par) override;

    /* ************************************************************************ */

    using typename FoldableContainer<Data>::FoldFunctor;

    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldPreOrder(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldPostOrder(FoldFunctor functor, const void *par, void *accumulator) const override;

  private:
    void InsertNodeAtFront(Node *node) noexcept;
    void InsertNodeAtBack(Node *node) noexcept;

  protected:
    void AuxMapPostOrder(MapFunctor functor, void *par, Node *node);
    void AuxFoldPostOrder(FoldFunctor functor, const void *par, void *accumulator, Node *node) const;
  };

  /* ************************************************************************** */

}

#include "list.cpp"

#endif