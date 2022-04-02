namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    Vector<Data>::Vector(ulong size)
    {
        array = new Data[size];
        this->size = size;
    }

    template <typename Data>
    Vector<Data>::Vector(LinearContainer<Data> &container)
    {
        size = container.Size();
        array = new Data[size];

        for (ulong i = 0; i < size; i++)
            array[i] = container[i];
    }

    template <typename Data>
    Vector<Data>::Vector(const Vector &other)
    {
        size = other.size;
        array = new Data[size];
        std::copy(other.array, other.array + size, array);
    }

    template <typename Data>
    Vector<Data>::Vector(Vector &&other) noexcept
    {
        std::swap(size, other.size);
        std::swap(array, other.array);
    }

    template <typename Data>
    Vector<Data>::~Vector()
    {
        delete[] array;
    }

    /* ************************************************************************** */

    template <typename Data>
    Vector<Data> &Vector<Data>::operator=(const Vector &other)
    {
        size = other.size;
        delete[] array;
        array = new Data[size];
        std::copy(other.array, other.array + size, array);

        return *this;
    }

    template <typename Data>
    Vector<Data> &Vector<Data>::operator=(Vector &&other) noexcept
    {
        std::swap(size, other.size);
        std::swap(array, other.array);

        return *this;
    }

    template <typename Data>
    bool Vector<Data>::operator==(const Vector &other) const noexcept
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
    bool Vector<Data>::operator!=(const Vector &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &Vector<Data>::operator[](const ulong index) const
    {
        if (index > size)
            throw std::out_of_range("index out of range");

        return array[index];
    }

    /* ************************************************************************** */

    template <typename Data>
    void Vector<Data>::Resize(const ulong size)
    {
        if (size == 0)
        {
            Clear();
        }
        else
        {
            // TODO: implementa
        }
    }

    template <typename Data>
    void Vector<Data>::Clear()
    {
        delete[] array;
        size = 0;
    }

    /* ************************************************************************** */

    template <typename Data>
    void Vector<Data>::Map(MapFunctor functor, void *par)
    {
        MapPreOrder(functor, par);
    }

    template <typename Data>
    void Vector<Data>::MapPreOrder(MapFunctor functor, void *par)
    {
        for (ulong i = 0; i < size; i++)
            functor(array[i], par);
    }

    template <typename Data>
    void Vector<Data>::MapPostOrder(MapFunctor functor, void *par)
    {
        for (ulong i = size - 1; i >= 0; i--)
            functor(array[i], par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void Vector<Data>::Fold(FoldFunctor functor, const void *foo, void *accumulator) const
    {
        FoldPreOrder(functor, foo, accumulator);
    }

    template <typename Data>
    void Vector<Data>::FoldPreOrder(FoldFunctor functor, const void *foo, void *accumulator) const
    {
        for (ulong i = 0; i < size; i++)
            functor(array[i], foo, accumulator);
    }

    template <typename Data>
    void Vector<Data>::FoldPostOrder(FoldFunctor functor, const void *foo, void *accumulator) const
    {
        for (ulong i = size - 1; i >= 0; i--)
            functor(array[i], foo, accumulator);
    }

    /* ************************************************************************** */

}