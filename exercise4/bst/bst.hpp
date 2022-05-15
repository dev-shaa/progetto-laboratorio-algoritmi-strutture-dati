
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BST : virtual public BinaryTreeLnk<Data>, virtual public DictionaryContainer<Data>
  {
  protected:
    using BinaryTreeLnk<Data>::NodeLnk;
    using BinaryTreeLnk<Data>::root;
    using BinaryTreeLnk<Data>::nodesCount;

  public:
    BST();
    BST(const LinearContainer<Data> &container);
    BST(const BST &other);
    BST(BST &&other)
    noexcept;

    virtual ~BST() = default;

    /* ************************************************************************ */

    BST &operator=(const BST &other);
    BST &operator=(BST &&other) noexcept;

    bool operator==(const BST &other) const noexcept;
    bool operator!=(const BST &other) const noexcept;

    /* ************************************************************************ */

    // throw std::length_error when empty

    const Data &Min() const;
    Data &MinNRemove();
    void RemoveMin();

    const Data &Max() const;
    Data &MaxNRemove();
    void RemoveMax();

    // throw std::length_error when not found

    const Data &Predecessor(const Data &value) const;
    Data &PredecessorNRemove(const Data &value);
    void RemovePredecessor(const Data &value);

    const Data &Successor(const Data &value) const;
    Data &SuccessorNRemove(const Data &value);
    void RemoveSuccessor(const Data &value);

    /* ************************************************************************ */

    void Insert(const Data &value) override;
    void Insert(Data &&value) override;
    void Remove(const Data &value) override;
    bool Exists(const Data &value) const noexcept override;

  protected:
    // Auxiliary member functions

    void Insert(NodeLnk *node) noexcept;
    void Remove(NodeLnk *node) noexcept;

    // type DataNDelete(argument) specifiers;
    Data &DataNDelete(NodeLnk *node);

    // type Detach(argument) specifiers;

    // type DetachMin(argument) specifiers;
    // type DetachMax(argument) specifiers;

    // type Skip2Left(argument) specifiers;
    // type Skip2Right(argument) specifiers;

    NodeLnk *Skip2Left(NodeLnk *&node) noexcept;
    NodeLnk *Skip2Right(NodeLnk *&node) noexcept;

    NodeLnk *&Detach(NodeLnk *&root) noexcept;
    NodeLnk *&DetachMin(NodeLnk *&root) noexcept;

    NodeLnk *&FindPointerToMin(NodeLnk *&root) const noexcept;
    NodeLnk *&FindPointerToMax(NodeLnk *&root) const noexcept;
    NodeLnk *FindPointerTo(NodeLnk *root, const Data &value) const noexcept;

    // type FindPointerToMin(argument) specifiers; // Both mutable & unmutable versions
    // type FindPointerToMax(argument) specifiers; // Both mutable & unmutable versions
    // type FindPointerTo(argument) specifiers; // Both mutable & unmutable versions

    // type FindPointerToPredecessor(argument) specifiers; // Both mutable & unmutable versions
    // type FindPointerToSuccessor(argument) specifiers; // Both mutable & unmutable versions
  };

  /* ************************************************************************** */

}

#include "bst.cpp"

#endif
