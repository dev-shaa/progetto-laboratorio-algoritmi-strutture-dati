
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
    ulong capacity = 0;
    ulong size = 0;

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

    const Data &Top() const override; // returns top but unmodifiable
    Data &Top() override;
    void Pop() override;
    Data &TopNPop() override;
    void Push(const Data &value) override;
    void Push(Data &&value) noexcept override;

    /* ************************************************************************ */

    inline virtual bool Empty() const noexcept override;
    inline virtual ulong Size() const noexcept override;
    void Clear();

  protected:
    void Expand();
    void Reduce();
  };

  /* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
