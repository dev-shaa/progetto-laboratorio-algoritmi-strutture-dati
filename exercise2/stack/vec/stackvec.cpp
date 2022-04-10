
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    StackVec<Data>::StackVec() : Vector<Data>(8)
    {
    }

    template <typename Data>
    StackVec<Data>::StackVec(const LinearContainer<Data> &container) : Vector<Data>(container)
    {
    }

    template <typename Data>
    StackVec<Data>::StackVec(const StackVec &other) : Vector<Data>(other)
    {
    }

    template <typename Data>
    StackVec<Data>::StackVec(StackVec &&other) noexcept : Vector<Data>(other)
    {
    }

    /* ************************************************************************** */

    template <typename Data>
    const Data &StackVec<Data>::Top() const
    {
        if (Empty())
            throw std::length_error("can't get top because stack is empty");

        return Vector<Data>::operator[](size - 1);
    }

    template <typename Data>
    Data &StackVec<Data>::Top()
    {
        if (Empty())
            throw std::length_error("can't get top because stack is empty");

        return Vector<Data>::operator[](size - 1);
    }

    template <typename Data>
    void StackVec<Data>::Pop()
    {
        if (Empty())
            throw new std::length_error("can't pop because stack is empty");

        size--; // doesn't actually remove the element
        Reduce();
    }

    template <typename Data>
    Data &StackVec<Data>::TopNPop()
    {
        Data *top = &Top();
        Pop();
        return *top;
    }

    template <typename Data>
    void StackVec<Data>::Push(const Data &value)
    {
        if (size + 1 == capacity)
            Expand();

        Vector<Data>::operator[](size) = value;
        size++;
    }

    template <typename Data>
    void StackVec<Data>::Push(Data &&value) noexcept
    {
        if (size + 1 == capacity)
            Expand();

        Vector<Data>::operator[](size) = std::move(value);
        size++;
    }

    template <typename Data>
    void StackVec<Data>::Expand()
    {
        Vector<Data>::Resize(2 * capacity);
        capacity *= 2;
    }

    template <typename Data>
    void StackVec<Data>::Reduce()
    {
        // NOTE: when should we reduce?

        if (size > capacity / 4)
            return;

        Vector<Data>::Resize(capacity / 4);
        capacity /= 4;
    }

    /* ************************************************************************** */

    template <typename Data>
    inline bool StackVec<Data>::Empty() const noexcept
    {
        return size == 0;
    }

    template <typename Data>
    inline ulong StackVec<Data>::Size() const noexcept
    {
        return size;
    }

    template <typename Data>
    void StackVec<Data>::Clear()
    {
        Vector<Data>::Clear();
        size = 0;
        capacity = 0;
    }

    /* ************************************************************************** */

}
