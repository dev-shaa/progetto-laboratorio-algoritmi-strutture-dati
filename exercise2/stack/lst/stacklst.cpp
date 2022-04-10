
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    StackLst<Data>::StackLst(const LinearContainer<Data> &container) : List<Data>(container)
    {
    }

    template <typename Data>
    StackLst<Data>::StackLst(const StackLst &other) : List<Data>(other)
    {
    }

    template <typename Data>
    StackLst<Data>::StackLst(StackLst &&other) noexcept : List<Data>(other)
    {
    }

    /* ************************************************************************** */

    template <typename Data>
    bool StackLst<Data>::operator==(const StackLst &other) const noexcept
    {
        if (size != other.size)
            return false;

        return *start == *(other.start);
    }

    template <typename Data>
    bool StackLst<Data>::operator!=(const StackLst &other) const noexcept
    {
        return !(*this == other);
    }

    /* ************************************************************************** */

    template <typename Data>
    const Data &StackLst<Data>::Top() const
    {
        return List<Data>::Front();
    }

    template <typename Data>
    Data &StackLst<Data>::Top()
    {
        return List<Data>::Front();
    }

    template <typename Data>
    void StackLst<Data>::Pop()
    {
        List<Data>::RemoveFromFront();
    }

    template <typename Data>
    Data &StackLst<Data>::TopNPop()
    {
        return List<Data>::FrontNRemove();
    }

    template <typename Data>
    void StackLst<Data>::Push(const Data &value)
    {
        List<Data>::InsertAtFront(value);
    }

    template <typename Data>
    void StackLst<Data>::Push(Data &&value) noexcept
    {
        List<Data>::InsertAtFront(value);
    }

    /* ************************************************************************** */

}
