
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    StackVec<Data>::StackVec() : Vector<Data>(8)
    {
        top = -1;
    }

    template <typename Data>
    StackVec<Data>::StackVec(const LinearContainer<Data> &container) : Vector<Data>(container)
    {
        top = container.Size() - 1;
    }

    template <typename Data>
    StackVec<Data>::StackVec(const StackVec &other) : Vector<Data>(other)
    {
        top = other.top;
    }

    template <typename Data>
    StackVec<Data>::StackVec(StackVec &&other) noexcept : Vector<Data>(other)
    {
        std::swap(top, other.top);
    }

    /* ************************************************************************** */

    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(const StackVec &other)
    {
        Vector<Data>::operator=(other);
        top = other.top;
        return *this;
    }

    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(StackVec &&other) noexcept
    {
        Vector<Data>::operator=(std::move(other));
        std::swap(top, other.top);
        return *this;
    }

    template <typename Data>
    bool StackVec<Data>::operator==(const StackVec &other) const noexcept
    {
        if (top != other.top)
            return false;

        for (ulong i = 0; i <= top; i++)
        {
            if (array[i] != other.array[i])
                return false;
        }

        return true;
    }

    template <typename Data>
    bool StackVec<Data>::operator!=(const StackVec &other) const noexcept
    {
        return !(*this == other);
    }

    /* ************************************************************************** */

    template <typename Data>
    const Data &StackVec<Data>::Top() const
    {
        if (Empty())
            throw std::length_error("can't get top because stack is empty");

        return array[top];
    }

    template <typename Data>
    Data &StackVec<Data>::Top()
    {
        if (Empty())
            throw std::length_error("can't get top because stack is empty");

        return array[top];
    }

    template <typename Data>
    void StackVec<Data>::Pop()
    {
        if (Empty())
            throw std::length_error("can't pop because stack is empty");

        top--;
        TryReduce();
    }

    template <typename Data>
    Data &StackVec<Data>::TopNPop()
    {
        if (Empty())
            throw std::length_error("can't pop because stack is empty");

        Data *value = &array[top--];
        TryReduce();

        return *value;
    }

    template <typename Data>
    void StackVec<Data>::Push(const Data &value)
    {
        TryExpand();
        array[++top] = value;
    }

    template <typename Data>
    void StackVec<Data>::Push(Data &&value) noexcept
    {
        TryExpand();
        array[++top] = std::move(value);
    }

    template <typename Data>
    void StackVec<Data>::TryExpand()
    {
        // when expanding, double the capacity of the old array

        if (top == size)
            Vector<Data>::Resize(size * 2);
    }

    template <typename Data>
    void StackVec<Data>::TryReduce()
    {
        // the array capacity should be twice the number of elements in it
        // to reduce, check if the elements are a quarter of the capacity and half it

        if (top < size / 4)
            Vector<Data>::Resize(size / 2);
    }

    /* ************************************************************************** */

    template <typename Data>
    inline bool StackVec<Data>::Empty() const noexcept
    {
        return top == -1;
    }

    template <typename Data>
    inline ulong StackVec<Data>::Size() const noexcept
    {
        return top + 1;
    }

    template <typename Data>
    void StackVec<Data>::Clear()
    {
        top = -1;
        TryReduce();
    }

    /* ************************************************************************** */

}
