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
    void setFlagIfEqual(const Data &data, const void *otherData, void *flag)
    {
        if (data == *((Data *)otherData))
            *((bool *)flag) = true;
    }

    template <typename Data>
    bool FoldableContainer<Data>::Exists(const Data &item) const noexcept
    {
        bool exists = false;
        Fold(&setFlagIfEqual<Data>, &item, &exists);
        return exists;
    }

    /* ************************************************************************** */

    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void *par)
    {
        MapPreOrder(fun, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void PreOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void *foo, void *accumulator) const
    {
        FoldPreOrder(fun, foo, accumulator);
    }

    /* ************************************************************************** */

    template <typename Data>
    void PostOrderMappableContainer<Data>::Map(MapFunctor fun, void *par)
    {
        MapPostOrder(fun, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void PostOrderFoldableContainer<Data>::Fold(FoldFunctor fun, const void *foo, void *accumulator) const
    {
        FoldPostOrder(fun, foo, accumulator);
    }

    /* ************************************************************************** */

    template <typename Data>
    void BreadthMappableContainer<Data>::Map(MapFunctor fun, void *par)
    {
        MapBreadth(fun, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void BreadthFoldableContainer<Data>::Fold(FoldFunctor fun, const void *foo, void *accumulator) const
    {
        FoldBreadth(fun, foo, accumulator);
    }

}