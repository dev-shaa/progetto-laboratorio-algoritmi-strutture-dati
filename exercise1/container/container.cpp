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

    // TODO: cleanup
    template <typename Data>
    void setFlagIfValuesAreEquals(const Data &data, const void *value, void *exists)
    {
        if (data == *((Data *)value))
            *((bool *)exists) = true;
    }

    template <typename Data>
    bool FoldableContainer<Data>::Exists(const Data &item) const noexcept
    {
        bool exists = false;
        Fold(&setFlagIfValuesAreEquals<Data>, &item, &exists);
        return exists;
    }

    /* ************************************************************************** */

    template <typename Data>
    void PreOrderMappableContainer<Data>::Map(MapFunctor fun, void *par)
    {
        MapInOrder(fun, par);
    }

    /* ************************************************************************** */

}