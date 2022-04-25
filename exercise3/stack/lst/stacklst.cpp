
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
    StackLst<Data>::StackLst(StackLst &&other) noexcept : List<Data>(std::move(other))
    {
    }

    /* ************************************************************************** */

    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(const StackLst &other)
    {
        List<Data>::operator=(other);
        return *this;
    }

    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(StackLst &&other) noexcept
    {
        List<Data>::operator=(std::move(other));
        return *this;
    }

    template <typename Data>
    bool StackLst<Data>::operator==(const StackLst &other) const noexcept
    {
        return List<Data>::operator==(other);
    }

    template <typename Data>
    bool StackLst<Data>::operator!=(const StackLst &other) const noexcept
    {
        return List<Data>::operator!=(other);
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
        return const_cast<Data &>(const_cast<const StackLst<Data> *>(this)->Top());
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
        List<Data>::InsertAtFront(std::move(value));
    }

    /* ************************************************************************** */

    template <typename Data>
    void StackLst<Data>::Clear()
    {
        List<Data>::Clear();
    }

}
