
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Iterator
  {
  public:
    virtual ~Iterator() = default;

    /* ************************************************************************ */

    Iterator &operator=(const Iterator &other) = delete;
    Iterator &operator=(Iterator &&other) noexcept = delete;

    bool operator==(const Iterator &other) const noexcept = delete;
    bool operator!=(const Iterator &other) const noexcept = delete;

    virtual Data &operator*() const = 0;

    /* ************************************************************************ */

    virtual bool Terminated() const noexcept = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class ForwardIterator : virtual public Iterator<Data>
  {
  public:
    virtual ~ForwardIterator() = default;

    /* ************************************************************************ */

    ForwardIterator &operator=(const ForwardIterator &other) = delete;
    ForwardIterator &operator=(ForwardIterator &&other) noexcept = delete;

    bool operator==(const ForwardIterator &other) const noexcept = delete;
    bool operator!=(const ForwardIterator &other) const noexcept = delete;

    virtual void operator++() = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BackwardIterator : virtual public Iterator<Data>
  {
  public:
    virtual ~BackwardIterator() = default;

    /* ************************************************************************ */

    BackwardIterator &operator=(const BackwardIterator &other) = delete;
    BackwardIterator &operator=(BackwardIterator &&other) noexcept = delete;

    bool operator==(const BackwardIterator &other) const noexcept = delete;
    bool operator!=(const BackwardIterator &other) const noexcept = delete;

    virtual void operator--() = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BidirectionalIterator : virtual public ForwardIterator<Data>, virtual public BackwardIterator<Data>
  {
  public:
    virtual ~BidirectionalIterator() = default;

    /* ************************************************************************ */

    BidirectionalIterator &operator=(const BidirectionalIterator &other) = delete;
    BidirectionalIterator &operator=(BidirectionalIterator &&other) noexcept = delete;

    bool operator==(const BidirectionalIterator &other) const noexcept = delete;
    bool operator!=(const BidirectionalIterator &other) const noexcept = delete;

    /* ************************************************************************ */

    virtual bool Terminated() const noexcept override
    {
      return ForwardTerminated() || BackwardTerminated();
    };
    virtual bool ForwardTerminated() const noexcept = 0;
    virtual bool BackwardTerminated() const noexcept = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class ResettableIterator : virtual public Iterator<Data>
  {
  public:
    virtual ~ResettableIterator() = default;

    /* ************************************************************************ */

    ResettableIterator &operator=(const ResettableIterator &other) = delete;
    ResettableIterator &operator=(ResettableIterator &&other) noexcept = delete;

    bool operator==(const ResettableIterator &other) const noexcept = delete;
    bool operator!=(const ResettableIterator &other) const noexcept = delete;

    /* ************************************************************************ */

    virtual void Reset() noexcept = 0;
  };

  /* ************************************************************************** */

}

#endif
