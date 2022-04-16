
namespace lasd
{

#define DEFAULT_QUEUE_LENGTH 5

    /* ************************************************************************** */

    template <typename Data>
    QueueVec<Data>::QueueVec() : Vector<Data>(DEFAULT_QUEUE_LENGTH)
    {
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data> &container) : Vector<Data>(container.Size() + 1 < DEFAULT_QUEUE_LENGTH ? DEFAULT_QUEUE_LENGTH : container.Size() + 1)
    {
        for (ulong i = 0; i < container.Size(); i++)
            Enqueue(container[i]);
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec &other) : Vector<Data>(other.Size() + 1 < DEFAULT_QUEUE_LENGTH ? DEFAULT_QUEUE_LENGTH : other.Size() + 1)
    {
        for (ulong i = 0; i < other.Size(); i++)
            Enqueue(other.array[(other.head + i) % other.size]);
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
        Clear();

        for (ulong i = 0; i < other.Size(); i++)
            Enqueue(other.array[(other.head + i) % other.size]);

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
        if (Size() != other.Size())
            return false;

        ulong i = 0;

        while (i < Size() && array[(head + i) % size] == other.array[(other.head + i) % other.size])
            i++;

        return i == Size();
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
        EnsureCapacity();
        tail = (tail + 1) % size;
        array[tail] = value;
    }

    template <typename Data>
    void QueueVec<Data>::Enqueue(Data &&value)
    {
        EnsureCapacity();
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
        Vector<Data>::Clear(DEFAULT_QUEUE_LENGTH);
        head = 1;
        tail = 0;
    }

    /* ************************************************************************** */

    template <typename Data>
    void QueueVec<Data>::EnsureCapacity()
    {
        if (!Full())
            return;

        ulong newTail = 0;
        ulong newSize = Size() * 2 + 1;
        Data *newArray = new Data[newSize];

        for (ulong i = 0; i < Size(); i++)
        {
            newTail++;
            newArray[newTail] = std::move(array[(head + i) % size]);
        }

        delete[] array;
        array = newArray;
        size = newSize;

        head = 1;
        tail = newTail;
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
