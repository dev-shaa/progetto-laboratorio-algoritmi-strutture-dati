
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"
#include "../../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTreeVec : virtual public BinaryTree<Data>
  {
  protected:
    struct NodeVec : BinaryTree<Data>::Node
    {
    protected:
      Data value;
      ulong index;

    public:
      NodeVec(const Data &value, ulong index);
      NodeVec(const NodeVec &other);
      NodeVec(NodeVec &&other) noexcept;

      virtual ~NodeVec() = default;

      /* ********************************************************************** */

      NodeVec &operator=(const NodeVec &other);
      NodeVec &operator=(NodeVec &&other) noexcept;

      bool operator==(const NodeVec &other) const noexcept;
      bool operator!=(const NodeVec &other) const noexcept;

      /* ********************************************************************** */

      Data &Element() noexcept override;
      const Data &Element() const noexcept override;

      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;

      typename BinaryTree<Data>::Node &LeftChild() const override;
      typename BinaryTree<Data>::Node &RightChild() const override;
    };

    Vector<NodeVec *> *nodes = nullptr;
    ulong nodesCount = 0;

  public:
    BinaryTreeVec() = default;
    BinaryTreeVec(const LinearContainer<Data> &container);
    BinaryTreeVec(const BinaryTreeVec &other);
    BinaryTreeVec(BinaryTreeVec &&other) noexcept;

    virtual ~BinaryTreeVec();

    /* ************************************************************************ */

    BinaryTreeVec &operator=(const BinaryTreeVec &other);
    BinaryTreeVec &operator=(BinaryTreeVec &&other) noexcept;

    bool operator==(const BinaryTreeVec &other) const noexcept;
    bool operator!=(const BinaryTreeVec &other) const noexcept;

    /* ************************************************************************ */

    typename BinaryTree<Data>::Node &Root() const override;

    bool Empty() const noexcept override;
    ulong Size() const noexcept override;
    void Clear() override;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    void MapBreadth(MapFunctor functor, void *par) override;

    /* ************************************************************************ */

    using typename FoldableContainer<Data>::FoldFunctor;

    void FoldBreadth(FoldFunctor functor, const void *par, void *accumulator) const override;
  };

  /* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
