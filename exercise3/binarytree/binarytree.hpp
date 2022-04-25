
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

#include "../iterator/iterator.hpp"

// #include "..."

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

  private:
    // ...

  protected:
    // using InOrder/BreadthMappableContainer<Data>::???;

    // ...

  public:
    struct Node
    {
    protected:
      Data value;
      Node *leftChild = nullptr, *rightChild = nullptr;

    public:
      friend class BinaryTree<Data>;

      /* ********************************************************************** */

      virtual ~Node() = default;

      /* ********************************************************************** */

      Node &operator=(const Node &other) = delete;
      Node &operator=(Node &&other) noexcept = delete;

      bool operator==(const Node &other) const noexcept; // Comparison of abstract types is possible, but should not be visible.
      bool operator!=(const Node &other) const noexcept;

      /* ********************************************************************** */

      virtual Data &Element() noexcept;
      virtual const Data &Element() const noexcept;

      virtual bool IsLeaf() const noexcept;
      virtual bool HasLeftChild() const noexcept;
      virtual bool HasRightChild() const noexcept;

      virtual Node &LeftChild() const;  // (concrete function must throw std::out_of_range when not existent)
      virtual Node &RightChild() const; // same
    };

    /* ************************************************************************ */

    virtual ~BinaryTree() = default;

    /* ************************************************************************ */

    BinaryTree &operator=(const BinaryTree &other) = delete;
    BinaryTree &operator=(BinaryTree &&other) noexcept = delete;

    bool operator==(const BinaryTree &other) const noexcept;
    bool operator!=(const BinaryTree &other) const noexcept;

    /* ************************************************************************ */

    virtual Node &Root() const;

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
    // Auxiliary member functions (for PreOrderMappableContainer)

    // type MapPreOrder(arguments) specifiers; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PreOrderFoldableContainer)

    // type FoldPreOrder(arguments) specifiers; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderMappableContainer)

    // type MapPostOrder(arguments) specifiers; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for PostOrderFoldableContainer)

    // type FoldPostOrder(arguments) specifiers; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderMappableContainer)

    // type MapInOrder(arguments) specifiers; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for InOrderFoldableContainer)

    // type FoldInOrder(arguments) specifiers; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthMappableContainer)

    // type MapBreadth(arguments) specifiers; // Accessory function executing from one node of the tree

    /* ************************************************************************ */

    // Auxiliary member functions (for BreadthFoldableContainer)

    // type FoldBreadth(arguments) specifiers; // Accessory function executing from one node of the tree
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPreOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    BTPreOrderIterator(const BinaryTree<Data> &tree);
    BTPreOrderIterator(const BTPreOrderIterator &iterator);
    BTPreOrderIterator(BTPreOrderIterator &&iterator) noexcept;

    virtual ~BTPreOrderIterator() = default;

    /* ************************************************************************ */

    BTPreOrderIterator &operator=(const BTPreOrderIterator &other);
    BTPreOrderIterator &operator=(BTPreOrderIterator &&other) noexcept;

    bool operator==(const BTPreOrderIterator &other) const noexcept;
    bool operator!=(const BTPreOrderIterator &other) const noexcept;

    Data &operator*() override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTPostOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    BTPostOrderIterator(const BinaryTree<Data> &tree);
    BTPostOrderIterator(const BTPostOrderIterator &iterator);
    BTPostOrderIterator(BTPostOrderIterator &&iterator) noexcept;

    virtual ~BTPostOrderIterator() = default;

    /* ************************************************************************ */

    BTPostOrderIterator &operator=(const BTPostOrderIterator &other);
    BTPostOrderIterator &operator=(BTPostOrderIterator &&other) noexcept;

    bool operator==(const BTPostOrderIterator &other) const noexcept;
    bool operator!=(const BTPostOrderIterator &other) const noexcept;

    Data &operator*() override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTInOrderIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {

  private:
    // ...

  protected:
    // ...

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

    Data &operator*() override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BTBreadthIterator : virtual public ForwardIterator<Data>, virtual public ResettableIterator<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    BTInOrderIterator(const BinaryTree<Data> &tree);
    BTBreadthIterator(const BTBreadthIterator &iterator);
    BTBreadthIterator(BTBreadthIterator &&iterator) noexcept;

    virtual ~BTBreadthIterator() = default;

    /* ************************************************************************ */

    BTBreadthIterator &operator=(const BTBreadthIterator &other);
    BTBreadthIterator &operator=(BTBreadthIterator &&other) noexcept;

    bool operator==(const BTBreadthIterator &other) const noexcept;
    bool operator!=(const BTBreadthIterator &other) const noexcept;

    Data &operator*() override;
    void operator++() override;

    /* ************************************************************************ */

    bool Terminated() const noexcept override;
    void Reset() noexcept override;
  };

  /* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
