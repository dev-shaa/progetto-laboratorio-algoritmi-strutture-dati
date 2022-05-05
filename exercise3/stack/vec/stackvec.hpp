
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class StackVec : virtual public Stack<Data>, virtual protected Vector<Data>
  {

  protected:
    using Vector<Data>::array;
    using Vector<Data>::size;
    ulong top = -1;

  public:
    StackVec();
    StackVec(const LinearContainer<Data> &container);

    StackVec(const StackVec &list);
    StackVec(StackVec &&list) noexcept;

    virtual ~StackVec() = default;

    /* ************************************************************************ */

    StackVec &operator=(const StackVec &other);
    StackVec &operator=(StackVec &&other) noexcept;

    bool operator==(const StackVec &other) const noexcept;
    bool operator!=(const StackVec &other) const noexcept;

    /* ************************************************************************ */

    const Data &Top() const override;
    Data &Top() override;
    void Pop() override;
    Data &TopNPop() override;
    void Push(const Data &value) override;
    void Push(Data &&value) noexcept override;

    /* ************************************************************************ */

    bool Empty() const noexcept override;
    ulong Size() const noexcept override;
    void Clear() override;

  protected:
    void Expand();
    void Reduce();
  };

  /* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
