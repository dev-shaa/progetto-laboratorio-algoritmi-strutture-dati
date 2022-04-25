
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Queue : virtual public Container
  {
  public:
    virtual ~Queue() = default;

    /* ************************************************************************ */

    virtual Queue &operator=(const Queue &other) = delete;
    virtual Queue &operator=(Queue &&other) noexcept = delete;

    bool operator==(const Queue &other) const noexcept = delete;
    bool operator!=(const Queue &other) const noexcept = delete;

    /* ************************************************************************ */

    virtual const Data &Head() const = 0; // returns top but unmodifiable
    virtual Data &Head() = 0;
    virtual void Dequeue() = 0;
    virtual Data &HeadNDequeue() = 0;
    virtual void Enqueue(const Data &value) = 0;
    virtual void Enqueue(Data &&value) = 0;
  };

  /* ************************************************************************** */

}

#endif
