
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
  protected:
    // using DictionaryContainer<Data>::???;
    Hash<Data> hashFunction;

  public:
    virtual ~HashTable() = default;

    /* ************************************************************************ */

    HashTable &operator=(const HashTable &other) = delete;
    HashTable &operator=(HashTable &&other) noexcept = delete;

    bool operator==(const HashTable &other) const noexcept; // possible
    bool operator!=(const HashTable &other) const noexcept; // possible

    /* ************************************************************************ */

    virtual void Resize(ulong size) = 0;

  protected:
    virtual ulong HashKey(Data value) const noexcept;
  };

  /* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
