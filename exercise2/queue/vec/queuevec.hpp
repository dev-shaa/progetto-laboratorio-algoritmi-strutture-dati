
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data>
  {
  protected:
    using Vector<Data>::array;
    using Vector<Data>::size;
    ulong head;
    ulong tail;

  public:
    QueueVec();
    QueueVec(const LinearContainer<Data> &container);

    QueueVec(const QueueVec &other);
    QueueVec(QueueVec &&other) noexcept;

    virtual ~QueueVec() = default;

    /* ************************************************************************ */

    QueueVec &operator=(const QueueVec &other);
    QueueVec &operator=(QueueVec &&other) noexcept;

    bool operator==(const QueueVec &other) const noexcept;
    bool operator!=(const QueueVec &other) const noexcept;

    /* ************************************************************************ */

    const Data &Head() const override; // returns top but unmodifiable
    Data &Head() override;
    void Dequeue() override;
    Data &HeadNDequeue() override;
    void Enqueue(const Data &value) override;
    void Enqueue(Data &&value) override;

    /* ************************************************************************ */

    inline bool Empty() const noexcept override;
    inline ulong Size() const noexcept override;
    void Clear();

  protected:
    // Auxiliary member functions

    void Expand();
    void Reduce();
    bool Full();

    // type Expand() specifiers;
    // type Reduce() specifiers;
    // type SwapVectors(arguments) specifiers;
  };

  /* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
