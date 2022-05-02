
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTreeLnk : virtual public BinaryTree<Data>
  {

  private:
    // ...

  protected:
    // using BinaryTree<Data>::???;

    struct NodeLnk : Node
    {
    protected:
      Data value;
      NodeLnk *leftChild = nullptr, *rightChild = nullptr;

    public:
      NodeLnk(const Data &value, NodeLnk *leftChild, NodeLnk *rightChild);
      NodeLnk(const NodeLnk &other);
      NodeLnk(NodeLnk &&other) noexcept;

      virtual ~NodeLnk() = default;

      /* ********************************************************************** */

      NodeLnk &operator=(const NodeLnk &other);
      NodeLnk &operator=(NodeLnk &&other) noexcept;

      bool operator==(const NodeLnk &other) const noexcept;
      bool operator!=(const NodeLnk &other) const noexcept;

      /* ********************************************************************** */

      Data &Element() noexcept override;
      const Data &Element() const noexcept override;

      bool HasLeftChild() const noexcept override;
      bool HasRightChild() const noexcept override;

      Node &LeftChild() const override;  // (concrete function must throw std::out_of_range when not existent)
      Node &RightChild() const override; // same
    };

  public:
    // Default constructor
    // BinaryTreeLnk() specifiers;

    /* ************************************************************************ */

    // Specific constructors
    // BinaryTreeLnk(argument) specifiers; // A binary tree obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    // BinaryTreeLnk(argument) specifiers;

    // Move constructor
    // BinaryTreeLnk(argument) specifiers;

    /* ************************************************************************ */

    virtual ~BinaryTreeLnk() = default;

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;

    /* ************************************************************************ */

    // Specific member functions (inherited from BinaryTree)

    // type Root() specifiers; // Override BinaryTree member (throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    // type Clear() specifiers; // Override Container member
  };

  /* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
