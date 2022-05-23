
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class HashTableClsAdr : virtual public HashTable<Data>
  {

  private:
    // ...

  protected:
    // using HashTable<Data>::???;

    // ...

    Vector<List<Data>> table;

  public:
    // Default constructor
    // HashTableClsAdr() specifiers;

    /* ************************************************************************ */

    // Specific constructors
    // HashTableClsAdr(argument) specifiers; // A hash table of a given size
    // HashTableClsAdr(argument) specifiers; // A hash table obtained from a LinearContainer
    // HashTableClsAdr(argument) specifiers; // A hash table of a given size obtained from a LinearContainer

    HashTableClsAdr();
    HashTableClsAdr(ulong size);
    HashTableClsAdr(const LinearContainer<Data> container);
    HashTableClsAdr(ulong size, const LinearContainer<Data> container);

    /* ************************************************************************ */

    // Copy constructor
    // HashTableClsAdr(argument) specifiers;

    // Move constructor
    // HashTableClsAdr(argument) specifiers;

    HashTableClsAdr(const HashTableClsAdr &other);
    HashTableClsAdr(HashTableClsAdr &&other) noexcept;

    /* ************************************************************************ */

    // Destructor
    // ~HashTableClsAdr() specifiers;
    virtual ~HashTableClsAdr();

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    HashTableClsAdr &operator=(const HashTableClsAdr &other);
    HashTableClsAdr &operator=(HashTableClsAdr &&other) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;
    bool operator==(const HashTableClsAdr &other) const noexcept;
    bool operator!=(const HashTableClsAdr &other) const noexcept;

    /* ************************************************************************ */

    void Resize(ulong size) override;

    /* ************************************************************************ */

    bool Insert(const Data &value) override;
    bool Insert(Data &&value) override;
    bool Remove(const Data &value) noexcept override;

    /* ************************************************************************ */

    bool Exists(const Data &value) const override;

    using MappableContainer<Data>::MapFunctor;
    void Map(MapFunctor functor, void *par) override;

    using FoldableContainer<Data>::FoldFunctor;
    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;

    bool Empty() const noexcept override;
    ulong Size() const noexcept override;
    void Clear() override;
  };

  /* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
