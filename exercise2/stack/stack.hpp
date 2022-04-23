
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Stack : virtual public Container
  {
  public:
    virtual ~Stack() = default;

    /* ************************************************************************ */

    Stack &operator=(const Stack &other) = delete;
    Stack &operator=(Stack &&other) noexcept = delete;

    bool operator==(const Stack &other) const noexcept = delete;
    bool operator!=(const Stack &other) const noexcept = delete;

    /* ************************************************************************ */

    virtual const Data &Top() const = 0;
    virtual Data &Top() = 0;
    virtual void Pop() = 0;
    virtual Data &TopNPop() = 0;
    virtual void Push(const Data &value) = 0;
    virtual void Push(Data &&value) = 0;
  };

  /* ************************************************************************** */

}

#endif
