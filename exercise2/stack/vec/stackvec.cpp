
namespace lasd
{

#ifndef DEFAULT_STACK_SIZE
#define DEFAULT_STACK_SIZE 5ul

    /* ************************************************************************** */

    template <typename Data>
    StackVec<Data>::StackVec() : Vector<Data>(DEFAULT_STACK_SIZE)
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

        ulong i = 0;

        while (i <= top && array[i] == other.array[i])
            i++;

        return i > top;
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
    inline Data &StackVec<Data>::Top()
    {
        return const_cast<Data &>(const_cast<const StackVec<Data> *>(this)->Top());
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
        std::swap(array[++top], value);
    }

    template <typename Data>
    void StackVec<Data>::TryExpand()
    {
        if (top == size - 1)
            Vector<Data>::Resize(size * 2);
    }

    template <typename Data>
    void StackVec<Data>::TryReduce()
    {
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

#undef DEFAULT_STACK_SIZE
#endif

}
