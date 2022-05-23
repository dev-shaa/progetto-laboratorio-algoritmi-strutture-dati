
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Hash
  {

  public:
    virtual ulong operator()(const Data &value) const noexcept = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class HashTable : virtual public DictionaryContainer<Data>, virtual public MappableContainer<Data>, virtual public FoldableContainer<Data>
  {
  private:
    // ...

  protected:
    // using DictionaryContainer<Data>::???;
    // ...

  public:
    // Destructor
    virtual ~HashTable() = default;

    /* ************************************************************************ */

    HashTable &operator=(const HashTable &other) = delete;
    HashTable &operator=(HashTable &&other) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract binary tree is possible.
    // type operator!=(argument) specifiers; // Comparison of abstract binary tree is possible.
    bool operator==(const HashTable &other) const noexcept;
    bool operator!=(const HashTable &other) const noexcept;

    /* ************************************************************************ */

    virtual void Resize(ulong size) = 0;

  protected:
    virtual ulong HashKey(ulong key) const noexcept;
  };

  /* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
