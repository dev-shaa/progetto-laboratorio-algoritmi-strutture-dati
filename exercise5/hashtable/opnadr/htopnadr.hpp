
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class HashTableOpnAdr : virtual public HashTable<Data>
  {
  protected:
    // using HashTable<Data>::???;

    ulong size = 0;
    Vector<Data> table;
    Vector<unsigned char> state;

  public:
    HashTableOpnAdr();
    HashTableOpnAdr(ulong size);
    HashTableOpnAdr(const LinearContainer<Data> &container);
    HashTableOpnAdr(ulong size, const LinearContainer<Data> &container);

    HashTableOpnAdr(const HashTableOpnAdr &other);
    HashTableOpnAdr(HashTableOpnAdr &&other) noexcept;

    virtual ~HashTableOpnAdr() = default;

    /* ************************************************************************ */

    HashTableOpnAdr &operator=(const HashTableOpnAdr &other);
    HashTableOpnAdr &operator=(HashTableOpnAdr &&other) noexcept;

    bool operator==(const HashTableOpnAdr &other) const noexcept;
    bool operator!=(const HashTableOpnAdr &other) const noexcept;

    /* ************************************************************************ */

    void Resize(ulong size) override;

    /* ************************************************************************ */

    bool Insert(const Data &value) override;
    bool Insert(Data &&value) override;
    bool Remove(const Data &value) noexcept override;

    /* ************************************************************************ */

    bool Exists(const Data &value) const noexcept override;

    using typename MappableContainer<Data>::MapFunctor;
    void Map(MapFunctor functor, void *par) override;

    using typename FoldableContainer<Data>::FoldFunctor;
    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;

    inline bool Empty() const noexcept override;
    inline ulong Size() const noexcept override;
    void Clear() override;

  public:
    // Auxiliary member functions

    // type Find(argument) specifiers;
    // type FindEmpty(argument) specifiers;
    // type Remove(argument) specifiers;

    ulong Find(const Data &value) const noexcept;
    ulong FindEmpty(const Data &value) const noexcept;
  };

  /* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
