
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

    struct NodeLnk : BinaryTree<Data>::Node
    {
    protected:
      Data value;
      NodeLnk *leftChild = nullptr, *rightChild = nullptr;

    public:
      NodeLnk(const Data &value, NodeLnk *leftChild, NodeLnk *rightChild);
      NodeLnk(const NodeLnk &other);
      NodeLnk(NodeLnk &&other) noexcept;

      virtual ~NodeLnk();

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

      typename BinaryTree<Data>::Node &LeftChild() const override;  // (concrete function must throw std::out_of_range when not existent)
      typename BinaryTree<Data>::Node &RightChild() const override; // same
    };

    NodeLnk *root = nullptr;
    ulong nodesCount = 0;

  public:
    BinaryTreeLnk() = default;
    BinaryTreeLnk(const LinearContainer<Data> &container);
    BinaryTreeLnk(const BinaryTreeLnk &other);
    BinaryTreeLnk(BinaryTreeLnk &&other) noexcept;

    virtual ~BinaryTreeLnk();

    /* ************************************************************************ */

    BinaryTreeLnk &operator=(const BinaryTreeLnk &other);
    BinaryTreeLnk &operator=(BinaryTreeLnk &&other) noexcept;

    bool operator==(const BinaryTreeLnk &other) const noexcept;
    bool operator!=(const BinaryTreeLnk &other) const noexcept;

    /* ************************************************************************ */

    typename BinaryTree<Data>::Node &Root() const override;

    bool Empty() const noexcept override;
    ulong Size() const noexcept override;
    void Clear() override;
  };

  /* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
