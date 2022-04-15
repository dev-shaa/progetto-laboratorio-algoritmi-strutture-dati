
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    QueueVec<Data>::QueueVec() : Vector<Data>(5)
    {
        head = 1;
        tail = 0;
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data> &container) : Vector<Data>(container.Size() + 1)
    {
        for (ulong i = 0; i < container.Size(); i++)
            array[i] = container[i];

        head = 0;
        tail = container.Size() - 1;
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec &other) : Vector<Data>(other.Size() + 1)
    {
        for (ulong i = other.head; i != other.tail; i = (i + 1) % other.size)
            Enqueue(other.array[i]);
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(QueueVec &&other) noexcept : Vector<Data>(std::move(other))
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }

    /* ************************************************************************** */

    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(const QueueVec &other)
    {
        // TODO: copy implementation

        return *this;
    }

    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(QueueVec &&other) noexcept
    {
        Vector<Data>::operator=(std::move(other));
        std::swap(head, other.head);
        std::swap(tail, other.tail);

        return *this;
    }

    template <typename Data>
    bool QueueVec<Data>::operator==(const QueueVec &other) const noexcept
    {
        ulong i = head;

        while (i != tail - 1 && array[i] == other.array[i])
            i = (i + 1) % size;

        return i == tail - 1;
    }

    template <typename Data>
    bool QueueVec<Data>::operator!=(const QueueVec &other) const noexcept
    {
        return !(*this == other);
    }

    /* ************************************************************************** */

    template <typename Data>
    const Data &QueueVec<Data>::Head() const
    {
        if (Empty())
            throw std::length_error("can't get value because queue is empty");

        return array[head];
    }

    template <typename Data>
    Data &QueueVec<Data>::Head()
    {
        if (Empty())
            throw std::length_error("can't get value because queue is empty");

        return array[head];
    }

    template <typename Data>
    void QueueVec<Data>::Dequeue()
    {
        if (Empty())
            throw std::length_error("can't dequeue because queue is empty");

        head = (head + 1) % size;
        Reduce();
    }

    template <typename Data>
    Data &QueueVec<Data>::HeadNDequeue()
    {
        if (Empty())
            throw std::length_error("can't dequeue because queue is empty");

        Data *value = &(array[head]);
        head = (head + 1) % size;
        Reduce();
        return *value;
    }

    template <typename Data>
    void QueueVec<Data>::Enqueue(const Data &value)
    {
        Expand();
        tail = (tail + 1) % size;
        array[tail] = value;
    }

    template <typename Data>
    void QueueVec<Data>::Enqueue(Data &&value)
    {
        Expand();
        tail = (tail + 1) % size;
        array[tail] = std::move(value);
    }

    /* ************************************************************************** */

    template <typename Data>
    inline bool QueueVec<Data>::Empty() const noexcept
    {
        return tail == head - 1;
    }

    template <typename Data>
    inline ulong QueueVec<Data>::Size() const noexcept
    {
        return (tail + size - head + 1) % size;
    }

    template <typename Data>
    void QueueVec<Data>::Clear()
    {
        head = 1;
        tail = 0;
        Vector<Data>::Resize(5);
    }

    /* ************************************************************************** */

    template <typename Data>
    void QueueVec<Data>::Expand()
    {
        if (!Full())
            return;

        Data *newArray = new Data[tail * 2 + 1];

        for (ulong i = head, j = 0; i != tail; i = (i + 1) % size, j++)
            newArray[j] = array[i];

        delete[] array;
        array = newArray;
        size = tail * 2 + 1;

        head = 0;
        tail = size - 2;
    }

    template <typename Data>
    void QueueVec<Data>::Reduce()
    {
        // reduce capacity
    }

    template <typename Data>
    inline bool QueueVec<Data>::Full()
    {
        return ((tail + 2) % size) == head;
    }

}
