
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
    Hash<Data> hashFunction;
    ulong a = 1;
    ulong b = 0;

  protected:
    HashTable();
    HashTable(const HashTable &other);
    HashTable(HashTable &&other) noexcept;

    HashTable &operator=(const HashTable &other);
    HashTable &operator=(HashTable &&other) noexcept;

  public:
    virtual ~HashTable() = default;

    bool operator==(const HashTable &other) const noexcept;
    bool operator!=(const HashTable &other) const noexcept;

    virtual void Resize(ulong size) = 0;

  protected:
    virtual inline ulong HashKey(const Data &value, const ulong &capacity) const noexcept;
  };

  /* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
