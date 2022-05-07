namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    Vector<Data>::Vector(ulong size)
    {
        if (size == 0)
            return;

        array = new Data[size];
        this->size = size;
    }

    template <typename Data>
    Vector<Data>::Vector(const LinearContainer<Data> &container) : Vector(container.Size())
    {
        for (ulong i = 0; i < Size(); i++)
            array[i] = container[i];
    }

    template <typename Data>
    Vector<Data>::Vector(const Vector &other) : Vector(other.Size())
    {
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

    template <typename Data>
    Vector<Data> &Vector<Data>::operator=(const Vector &other)
    {
        if (this != &other)
        {
            Clear(other.Size());
            std::copy(other.array, other.array + size, array);
        }

        return *this;
    }

    template <typename Data>
    Vector<Data> &Vector<Data>::operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(size, other.size);
            std::swap(array, other.array);
        }

        return *this;
    }

    template <typename Data>
    bool Vector<Data>::operator==(const Vector &other) const noexcept
    {
        return LinearContainer<Data>::operator==(other);
    }

    template <typename Data>
    bool Vector<Data>::operator!=(const Vector &other) const noexcept
    {
        return LinearContainer<Data>::operator!=(other);
    }

    template <typename Data>
    Data &Vector<Data>::operator[](const ulong index) const
    {
        if (index >= Size())
            throw std::out_of_range("index out of bounds");

        return array[index];
    }

    template <typename Data>
    void Vector<Data>::Resize(const ulong size)
    {
        if (this->size == size)
            return;

        if (size == 0)
        {
            Clear();
        }
        else
        {
            Data *newArray = new Data[size];
            std::copy(array, array + std::min(this->size, size), newArray);

            delete[] array;
            array = newArray;
            this->size = size;
        }
    }

    template <typename Data>
    void Vector<Data>::Clear()
    {
        delete[] array;
        array = nullptr;
        size = 0;
    }

    template <typename Data>
    void Vector<Data>::Clear(ulong size)
    {
        if (size == 0)
        {
            Clear();
            return;
        }

        delete[] array;
        array = new Data[size];
        this->size = size;
    }

    template <typename Data>
    inline bool Vector<Data>::Empty() const noexcept
    {
        return size == 0;
    }

    template <typename Data>
    inline ulong Vector<Data>::Size() const noexcept
    {
        return size;
    }

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
        ulong i = size;

        while (i > 0)
        {
            i--;
            functor(array[i], par);
        }
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
        ulong i = size;

        while (i > 0)
        {
            i--;
            functor(array[i], foo, accumulator);
        }
    }

    /* ************************************************************************** */

}