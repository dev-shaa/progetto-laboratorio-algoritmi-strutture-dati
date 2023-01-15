
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
    using typename BinaryTreeLnk<Data>::NodeLnk;
    using BinaryTreeLnk<Data>::root;
    using BinaryTreeLnk<Data>::nodesCount;

  public:
    BST() = default;
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

    const Data &Min() const;
    Data &MinNRemove();
    void RemoveMin();

    const Data &Max() const;
    Data &MaxNRemove();
    void RemoveMax();

    const Data &Predecessor(const Data &value) const;
    Data &PredecessorNRemove(const Data &value);
    void RemovePredecessor(const Data &value);

    const Data &Successor(const Data &value) const;
    Data &SuccessorNRemove(const Data &value);
    void RemoveSuccessor(const Data &value);

    /* ************************************************************************ */

    bool Insert(const Data &value) override;
    bool Insert(Data &&value) override;
    bool Remove(const Data &value) noexcept override;

    bool Insert(const LinearContainer<Data> &container) override;
    bool Insert(LinearContainer<Data> &&container) override;
    bool Remove(const LinearContainer<Data> &container) noexcept override;

    bool Exists(const Data &value) const noexcept override;

  protected:
    Data &DataNDelete(NodeLnk *node);

    NodeLnk *Detach(NodeLnk *&node) noexcept;
    NodeLnk *DetachMin(NodeLnk *&root) noexcept;
    NodeLnk *DetachMax(NodeLnk *&root) noexcept;

    NodeLnk *Skip2Left(NodeLnk *&node) noexcept;
    NodeLnk *Skip2Right(NodeLnk *&node) noexcept;

    NodeLnk *&FindPointerToMin(NodeLnk *&root) noexcept;
    NodeLnk *const &FindPointerToMin(NodeLnk *const &root) const noexcept;

    NodeLnk *&FindPointerToMax(NodeLnk *&root) noexcept;
    NodeLnk *const &FindPointerToMax(NodeLnk *const &root) const noexcept;

    NodeLnk *&FindPointerTo(NodeLnk *&root, const Data &value) noexcept;
    NodeLnk *const &FindPointerTo(NodeLnk *const &root, const Data &value) const noexcept;

    NodeLnk **FindPointerToPredecessor(NodeLnk *&root, const Data &value) noexcept;
    NodeLnk *const *FindPointerToPredecessor(NodeLnk *const &root, const Data &value) const noexcept;

    NodeLnk **FindPointerToSuccessor(NodeLnk *&root, const Data &value) noexcept;
    NodeLnk *const *FindPointerToSuccessor(NodeLnk *const &root, const Data &value) const noexcept;
  };

  /* ************************************************************************** */

}

#include "bst.cpp"

#endif
