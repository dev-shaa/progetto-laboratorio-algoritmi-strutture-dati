
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class StackLst : virtual public Stack<Data>, virtual protected List<Data>
  {
  protected:
    using List<Data>::size;
    using List<Data>::start;

  public:
    StackLst() = default;
    StackLst(const LinearContainer<Data> &container);

    StackLst(const StackLst &list);
    StackLst(StackLst &&list) noexcept;

    virtual ~StackLst() = default;

    /* ************************************************************************ */

    StackLst &operator=(const StackLst &other);
    StackLst &operator=(StackLst &&other) noexcept;

    bool operator==(const StackLst &other) const noexcept;
    bool operator!=(const StackLst &other) const noexcept;

    /* ************************************************************************ */

    const Data &Top() const override; // returns top but unmodifiable
    Data &Top() override;
    void Pop() override;
    Data &TopNPop() override;
    void Push(const Data &value) override;
    void Push(Data &&value) noexcept override;

    /* ************************************************************************ */

    void Clear() override;
  };

  /* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
