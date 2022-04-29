#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Vector : virtual public LinearContainer<Data>,
                 virtual public PreOrderMappableContainer<Data>,
                 virtual public PostOrderMappableContainer<Data>,
                 virtual public PreOrderFoldableContainer<Data>,
                 virtual public PostOrderFoldableContainer<Data>
  {
  protected:
    using LinearContainer<Data>::size;
    Data *array = nullptr;

  public:
    Vector() = default;
    Vector(ulong size);
    Vector(const LinearContainer<Data> &container);
    Vector(const Vector &other);
    Vector(Vector &&other) noexcept;

    virtual ~Vector();

    /* ************************************************************************ */

    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other) noexcept;

    bool operator==(const Vector &other) const noexcept;
    bool operator!=(const Vector &other) const noexcept;

    Data &operator[](const ulong index) const override;

    /* ************************************************************************ */

    void Resize(const ulong size);
    void Clear() override;
    void Clear(ulong size);
    bool Empty() const noexcept override;
    ulong Size() const noexcept override;

    /* ************************************************************************ */

    using typename MappableContainer<Data>::MapFunctor;

    void Map(MapFunctor functor, void *par) override;
    void MapPreOrder(MapFunctor functor, void *par) override;
    void MapPostOrder(MapFunctor functor, void *par) override;

    /* ************************************************************************ */

    using typename FoldableContainer<Data>::FoldFunctor;

    void Fold(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldPreOrder(FoldFunctor functor, const void *par, void *accumulator) const override;
    void FoldPostOrder(FoldFunctor functor, const void *par, void *accumulator) const override;
  };

  /* ************************************************************************** */

}

#include "vector.cpp"

#endif
