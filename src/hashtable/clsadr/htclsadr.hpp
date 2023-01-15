
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../vector/vector.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class HashTableClsAdr : virtual public HashTable<Data>
  {
  protected:
    ulong size = 0;
    Vector<BST<Data>> table;

  public:
    HashTableClsAdr();
    HashTableClsAdr(ulong size);
    HashTableClsAdr(const LinearContainer<Data> &container);
    HashTableClsAdr(ulong size, const LinearContainer<Data> &container);

    HashTableClsAdr(const HashTableClsAdr &other);
    HashTableClsAdr(HashTableClsAdr &&other) noexcept;

    virtual ~HashTableClsAdr() = default;

    /* ************************************************************************ */

    HashTableClsAdr &operator=(const HashTableClsAdr &other);
    HashTableClsAdr &operator=(HashTableClsAdr &&other) noexcept;

    bool operator==(const HashTableClsAdr &other) const noexcept;
    bool operator!=(const HashTableClsAdr &other) const noexcept;

    /* ************************************************************************ */

    void Resize(ulong size) override;

    /* ************************************************************************ */

    bool Insert(const Data &value) override;
    bool Insert(Data &&value) override;
    bool Remove(const Data &value) noexcept override;

    bool Insert(const LinearContainer<Data> &container) override;
    bool Insert(LinearContainer<Data> &&container) override;
    bool Remove(const LinearContainer<Data> &container) noexcept override;

    /* ************************************************************************ */

    bool Exists(const Data &value) const noexcept override;

    using typename MappableContainer<Data>::MapFunctor;
    void Map(MapFunctor functor, void *par) override;

    using typename FoldableContainer<Data>::FoldFunctor;
    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;

    inline bool Empty() const noexcept override;
    inline ulong Size() const noexcept override;
    void Clear() override;
  };

  /* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
