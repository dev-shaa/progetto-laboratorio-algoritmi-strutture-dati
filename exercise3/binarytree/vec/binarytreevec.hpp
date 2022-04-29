
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"
#include "../container/container.hpp"

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

    Vector<NodeVec *> vector;

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

    // Specific member functions (inherited from BinaryTree)

    // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)

    Node &Root() const override;

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    // type Clear() specifiers; // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthMappableContainer)

    // type MapBreadth(arguments) specifiers; // Override BreadthMappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from BreadthFoldableContainer)

    // type FoldBreadth(arguments) specifiers; // Override BreadthFoldableContainer member
  };

  /* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
