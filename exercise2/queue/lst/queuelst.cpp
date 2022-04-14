
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    QueueLst<Data>::QueueLst() : List<Data>()
    {
    }

    template <typename Data>
    QueueLst<Data>::QueueLst(const LinearContainer<Data> &container) : List<Data>(container)
    {
    }

    template <typename Data>
    QueueLst<Data>::QueueLst(const QueueLst &other) : List<Data>(other)
    {
    }

    template <typename Data>
    QueueLst<Data>::QueueLst(QueueLst &&other) noexcept : List<Data>(std::move(other))
    {
    }

    /* ************************************************************************** */

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst &other)
    {
        List<Data>::operator=(other);
        return *this;
    }

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(QueueLst &&other) noexcept
    {
        List<Data>::operator=(std::move(other));
        return *this;
    }

    template <typename Data>
    bool QueueLst<Data>::operator==(const QueueLst &other) const noexcept
    {
        return List<Data>::operator==(other);
    }

    template <typename Data>
    bool QueueLst<Data>::operator!=(const QueueLst &other) const noexcept
    {
        return !(*this == other);
    }

    /* ************************************************************************** */

    template <typename Data>
    const Data &QueueLst<Data>::Head() const
    {
        return List<Data>::Front();
    }

    template <typename Data>
    Data &QueueLst<Data>::Head()
    {
        return List<Data>::Front();
    }

    template <typename Data>
    void QueueLst<Data>::Dequeue()
    {
        List<Data>::RemoveFromFront();
    }

    template <typename Data>
    Data &QueueLst<Data>::HeadNDequeue()
    {
        return List<Data>::FrontNRemove();
    }

    template <typename Data>
    void QueueLst<Data>::Enqueue(const Data &value)
    {
        List<Data>::InsertAtBack(value);
    }

    template <typename Data>
    void QueueLst<Data>::Enqueue(Data &&value)
    {
        List<Data>::InsertAtBack(std::move(value));
    }

    /* ************************************************************************** */

    template <typename Data>
    void QueueLst<Data>::Clear()
    {
        List<Data>::Clear();
    }

}
