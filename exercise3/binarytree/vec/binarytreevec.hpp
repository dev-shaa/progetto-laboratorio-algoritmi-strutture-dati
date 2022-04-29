
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
  private:
    // ...

  protected:
    // using BinaryTree<Data>::???;

    struct NodeVec : Node
    {

    private:
      Data value;
      ulong index;

    protected:
      // ...

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

      Node &LeftChild() const override;  // (concrete function must throw std::out_of_range when not existent)
      Node &RightChild() const override; // same
    };

    Vector<NodeVec *> nodes;

  public:
    BinaryTreeVec();
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

    Node &Root() const override; // (throw std::length_error when empty)

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
