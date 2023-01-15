
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class QueueLst : virtual public Queue<Data>, virtual protected List<Data>
  {
  protected:
    using List<Data>::start;
    using List<Data>::size;

  public:
    QueueLst();
    QueueLst(const LinearContainer<Data> &container);

    QueueLst(const QueueLst &other);
    QueueLst(QueueLst &&other) noexcept;

    virtual ~QueueLst() = default;

    /* ************************************************************************ */

    QueueLst &operator=(const QueueLst &other);
    QueueLst &operator=(QueueLst &&other) noexcept;

    bool operator==(const QueueLst &other) const noexcept;
    bool operator!=(const QueueLst &other) const noexcept;

    /* ************************************************************************ */

    const Data &Head() const override;
    Data &Head() override;
    void Dequeue() override;
    Data &HeadNDequeue() override;
    void Enqueue(const Data &value) override;
    void Enqueue(Data &&value) override;

    /* ************************************************************************ */

    inline bool Empty() const noexcept override;
    inline ulong Size() const noexcept override;
    void Clear() override;
  };

  /* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
