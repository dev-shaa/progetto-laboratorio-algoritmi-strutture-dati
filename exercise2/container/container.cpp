namespace lasd
{

    /* ************************************************************************** */

    inline bool Container::Empty() const noexcept
    {
        return size == 0;
    }

    inline ulong Container::Size() const noexcept
    {
        return size;
    }

    /* ************************************************************************** */

    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer &other) const noexcept
    {
        if (size != other.size)
            return false;

        ulong i = 0;
        bool equals = true;

        while (i < size && equals)
        {
            equals = (*this)[i] == other[i];
            i++;
        }

        return equals;
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

        return (*this)[size - 1];
    }

    /* ************************************************************************** */

    template <typename Data>
    void setFlagIfEqual(const Data &value, const void *otherData, void *flag)
    {
        if (value == *((Data *)otherData))
            *((bool *)flag) = true;
    }

    template <typename Data>
    bool FoldableContainer<Data>::Exists(const Data &value) const noexcept
    {
        bool exists = false;
        Fold(&setFlagIfEqual<Data>, &value, &exists);
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