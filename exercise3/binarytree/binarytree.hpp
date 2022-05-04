
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../iterator/iterator.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../stack/lst/stacklst.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTree : virtual public PreOrderMappableContainer<Data>,
                     virtual public PostOrderMappableContainer<Data>,
                     virtual public InOrderMappableContainer<Data>,
                     virtual public BreadthMappableContainer<Data>,
                     virtual public PreOrderFoldableContainer<Data>,
                     virtual public PostOrderFoldableContainer<Data>,
                     virtual public InOrderFoldableContainer<Data>,
                     virtual public BreadthFoldableContainer<Data>
  {
  public:
    struct Node
    {
    protected:
      bool operator==(const Node &other) const noexcept;
      bool operator!=(const Node &other) const noexcept;

    public:
      friend class BinaryTree<Data>;

      /* ********************************************************************** */

      virtual ~Node() = default;

      /* ********************************************************************** */

      Node &operator=(const Node &other) = delete;
      Node &operator=(Node &&other) noexcept = delete;

      /* ********************************************************************** */

      virtual Data &Element() noexcept = 0;
      virtual const Data &Element() const noexcept = 0;

      virtual bool IsLeaf() const noexcept;
      virtual bool HasLeftChild() const noexcept = 0;
      virtual bool HasRightChild() const noexcept = 0;

      virtual Node &LeftChild() const = 0;
      virtual Node &RightChild() const = 0;
    };

    /* ************************************************************************ */

    virtual ~BinaryTree() = default;

    /* ************************************************************************ */

    BinaryTree &operator=(const BinaryTree &other) = delete;
    BinaryTree &operator=(BinaryTree &&other) noexcept = delete;

    bool operator==(const BinaryTree &other) const noexcept;
    bool operator!=(const BinaryTree &other) const noexcept;

    /* ************************************************************************ */

    virtual Node &Root() const = 0;

    bool Exists(const Data &value) const noexcept override;
    bool Empty() const noexcept = 0;
    ulong Size() const noexcept = 0;
    void Clear() = 0;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    void Map(MapFunctor functor, void *par) override;
    void MapPreOrder(MapFunctor functor, void *par) override;
    void MapPostOrder(MapFunctor functor, void *par) override;
    void MapInOrder(MapFunctor functor, void *par) override;
    void MapBreadth(MapFunctor functor, void *par) override;

    /* ************************************************************************ */

    using typename FoldableContainer<Data>::FoldFunctor;

    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldPreOrder(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldPostOrder(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldInOrder(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldBreadth(FoldFunctor functor, const void *par, void *accumulator) const override;

  protected:
    void MapPreOrderAux(MapFunctor functor, void *par, Node &node);
    void MapPostOrderAux(MapFunctor functor, void *par, Node &node);
    void MapInOrderAux(MapFunctor functor, void *par, Node &node);

    void FoldPreOrderAux(FoldFunctor functor, const void *par, void *accumulator, Node &node) const;
    void FoldPostOrderAux(FoldFunctor functor, const void *par, void *accumulator, Node &node) const;
    void FoldInOrderAux(FoldFunctor functor, const void *par, void *accumulator, Node &node) const;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPreOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {
  protected:
    StackLst<typename BinaryTree<Data>::Node *> nodes;
    typename BinaryTree<Data>::Node *root = nullptr;

  public:
    BTPreOrderIterator(const BinaryTree<Data> &tree);
    BTPreOrderIterator(const BTPreOrderIterator &other);
    BTPreOrderIterator(BTPreOrderIterator &&other) noexcept;

    virtual ~BTPreOrderIterator() = default;

    /* ************************************************************************ */

    BTPreOrderIterator &operator=(const BTPreOrderIterator &other);
    BTPreOrderIterator &operator=(BTPreOrderIterator &&other) noexcept;

    bool operator==(const BTPreOrderIterator &other) const noexcept;
    bool operator!=(const BTPreOrderIterator &other) const noexcept;

    Data &operator*() const override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPostOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {
  protected:
    StackLst<typename BinaryTree<Data>::Node *> nodes;
    StackLst<bool> expanded;
    typename BinaryTree<Data>::Node *root = nullptr;

  public:
    BTPostOrderIterator(const BinaryTree<Data> &tree);
    BTPostOrderIterator(const BTPostOrderIterator &other);
    BTPostOrderIterator(BTPostOrderIterator &&other) noexcept;

    virtual ~BTPostOrderIterator() = default;

    /* ************************************************************************ */

    BTPostOrderIterator &operator=(const BTPostOrderIterator &other);
    BTPostOrderIterator &operator=(BTPostOrderIterator &&other) noexcept;

    bool operator==(const BTPostOrderIterator &other) const noexcept;
    bool operator!=(const BTPostOrderIterator &other) const noexcept;

    Data &operator*() const override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTInOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {
  protected:
    StackLst<typename BinaryTree<Data>::Node *> nodes;
    typename BinaryTree<Data>::Node *root = nullptr;

    void PushLeftSubTree(typename BinaryTree<Data>::Node *root);

  public:
    BTInOrderIterator(const BinaryTree<Data> &tree);
    BTInOrderIterator(const BTInOrderIterator &iterator);
    BTInOrderIterator(BTInOrderIterator &&iterator) noexcept;

    virtual ~BTInOrderIterator() = default;

    /* ************************************************************************ */

    BTInOrderIterator &operator=(const BTInOrderIterator &other);
    BTInOrderIterator &operator=(BTInOrderIterator &&other) noexcept;

    bool operator==(const BTInOrderIterator &other) const noexcept;
    bool operator!=(const BTInOrderIterator &other) const noexcept;

    Data &operator*() const override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTBreadthIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {
  protected:
    QueueLst<typename BinaryTree<Data>::Node *> nodes;
    typename BinaryTree<Data>::Node *root = nullptr;

  public:
    BTBreadthIterator(const BinaryTree<Data> &tree);
    BTBreadthIterator(const BTBreadthIterator &other);
    BTBreadthIterator(BTBreadthIterator &&other) noexcept;

    virtual ~BTBreadthIterator() = default;

    /* ************************************************************************ */

    BTBreadthIterator &operator=(const BTBreadthIterator &other);
    BTBreadthIterator &operator=(BTBreadthIterator &&other) noexcept;

    bool operator==(const BTBreadthIterator &other) const noexcept;
    bool operator!=(const BTBreadthIterator &other) const noexcept;

    Data &operator*() const override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
