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
      Data item;
      Node *next;

      /* ********************************************************************** */

      Node(Data &item, Node *next);

      Node(const Node &other);
      Node(Node &&other) noexcept;

      virtual ~Node() = default;

      /* ********************************************************************** */

      bool operator==(const Node &other) const;
      bool operator!=(const Node &other) const;

      /* ********************************************************************** */

      // Specific member functions

      // ...
    };

    using LinearContainer<Data>::size;

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

    void InsertAtFront(Data item); // copy of the value
    // void InsertAtFront(Data &item); // move of the value
    void RemoveFromFront();
    Data &FrontNRemove();

    void InsertAtBack(Data &item); // copy
    void InsertAtBack(Data item);  // move

    /* ************************************************************************ */

    // TODO: override front and back

    Data &Front() const override;
    Data &Back() const override;

    void Clear() override;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    void Map(MapFunctor, void *) override;
    void MapPreOrder(MapFunctor functor, void *) override;
    void MapPostOrder(MapFunctor functor, void *) override;

    /* ************************************************************************ */

    using typename FoldableContainer<Data>::FoldFunctor;

    void Fold(FoldFunctor functor, const void *, void *accumulator) const override;
    void FoldPreOrder(FoldFunctor functor, const void *, void *accumulator) const override;
    void FoldPostOrder(FoldFunctor functor, const void *, void *accumulator) const override;

  protected:
    void AuxMapPostOrder(MapFunctor functor, void *par, Node *node);
    void AuxFoldPostOrder(FoldFunctor functor, const void *par, void *accumulator, Node *node) const;
  };

  /* ************************************************************************** */

}

#include "list.cpp"

#endif