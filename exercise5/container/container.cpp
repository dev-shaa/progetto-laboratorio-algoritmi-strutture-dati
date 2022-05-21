namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer &other) const noexcept
    {
        if (Size() != other.Size())
            return false;

        ulong i = 0;

        while (i < Size() && (*this)[i] == other[i])
            i++;

        return i == Size();
    }

    template <typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &LinearContainer<Data>::Front() const
    {
        if (Empty())
            throw std::length_error("Can't access front item because container is empty");

        return (*this)[0];
    }

    template <typename Data>
    Data &LinearContainer<Data>::Back() const
    {
        if (Empty())
            throw std::length_error("Can't access back item because container is empty");

        return (*this)[Size() - 1];
    }

    /* ************************************************************************** */

    template <typename Data>
    bool DictionaryContainer<Data>::Insert(const LinearContainer<Data> &container)
    {
        bool inserted = false;

        for (ulong i = 0; i < other.Size(); i++)
        {
            if (Insert(other[i]))
                inserted = true;
        }

        return inserted;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::Insert(LinearContainer<Data> &&container)
    {
        bool inserted = false;

        for (ulong i = 0; i < other.Size(); i++)
        {
            if (Insert(std::move(other[i])))
                inserted = true;
        }

        return inserted;
    }

    template <typename Data>
    bool DictionaryContainer<Data>::Remove(const LinearContainer<Data> &container) noexcept
    {
        bool removed = false;

        for (ulong i = 0; i < other.Size(); i++)
        {
            if (Remove(other[i]))
                removed = true;
        }

        return removed;
    }

    /* ************************************************************************** */

    template <typename Data>
    void SetFlagIfEqual(const Data &value, const void *otherData, void *flag)
    {
        if (value == *((Data *)otherData))
            *((bool *)flag) = true;
    }

    template <typename Data>
    bool FoldableContainer<Data>::Exists(const Data &value) const noexcept
    {
        bool exists = false;
        Fold(&SetFlagIfEqual<Data>, &value, &exists);
        return exists;
    }

    /* ************************************************************************** */

    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFunctor functor, void *par)
    {
        MapPreOrder(functor, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void PreOrderFoldableContainer<Data>::Fold(FoldFunctor functor, const void *par, void *accumulator) const
    {
        FoldPreOrder(functor, par, accumulator);
    }

    /* ************************************************************************** */

    template <typename Data>
    void PostOrderMappableContainer<Data>::Map(MapFunctor functor, void *par)
    {
        MapPostOrder(functor, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void PostOrderFoldableContainer<Data>::Fold(FoldFunctor functor, const void *par, void *accumulator) const
    {
        FoldPostOrder(functor, par, accumulator);
    }

    /* ************************************************************************** */

    template <typename Data>
    void InOrderMappableContainer<Data>::Map(MapFunctor functor, void *par)
    {
        MapInOrder(functor, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void InOrderFoldableContainer<Data>::Fold(FoldFunctor functor, const void *par, void *accumulator) const
    {
        FoldInOrder(functor, par, accumulator);
    }

    /* ************************************************************************** */

    template <typename Data>
    void BreadthMappableContainer<Data>::Map(MapFunctor functor, void *par)
    {
        MapBreadth(functor, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void BreadthFoldableContainer<Data>::Fold(FoldFunctor functor, const void *par, void *accumulator) const
    {
        FoldBreadth(functor, par, accumulator);
    }

}