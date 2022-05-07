
namespace lasd
{

#ifndef DEFAULT_QUEUE_SIZE
#define DEFAULT_QUEUE_SIZE 5ul

    /* ************************************************************************** */

    template <typename Data>
    QueueVec<Data>::QueueVec() : Vector<Data>(DEFAULT_QUEUE_SIZE)
    {
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data> &container) : Vector<Data>(std::max(container.Size() + 1, DEFAULT_QUEUE_SIZE))
    {
        for (ulong i = 0; i < container.Size(); i++)
            array[++tail] = container[i];
    }

    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec &other) : Vector<Data>(std::max(other.Size() + 1, DEFAULT_QUEUE_SIZE))
    {
        for (ulong i = 0; i < other.Size(); i++)
            array[++tail] = other.array[(other.head + i) % other.size];
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
        if (this != &other)
        {
            Vector<Data>::Clear(std::max(other.Size() + 1, DEFAULT_QUEUE_SIZE));
            head = 1;
            tail = 0;

            for (ulong i = 0; i < other.Size(); i++)
                array[++tail] = other.array[(other.head + i) % other.size];
        }

        return *this;
    }

    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(QueueVec &&other) noexcept
    {
        if (this != &other)
        {
            Vector<Data>::operator=(std::move(other));
            std::swap(head, other.head);
            std::swap(tail, other.tail);
        }

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
    inline Data &QueueVec<Data>::Head()
    {
        return const_cast<Data &>(const_cast<const QueueVec<Data> *>(this)->Head());
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

        Data *value = new Data(std::move(array[head]));
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
        std::swap(array[tail], value);
    }

    /* ************************************************************************** */

    template <typename Data>
    inline bool QueueVec<Data>::Empty() const noexcept
    {
        return size == 0 || (tail + 1ul) % size == head;
    }

    template <typename Data>
    inline ulong QueueVec<Data>::Size() const noexcept
    {
        return size == 0 ? 0 : (tail + size - head + 1ul) % size;
    }

    template <typename Data>
    void QueueVec<Data>::Clear()
    {
        Vector<Data>::Clear(DEFAULT_QUEUE_SIZE);
        head = 1;
        tail = 0;
    }

    /* ************************************************************************** */

    template <typename Data>
    inline void QueueVec<Data>::EnsureCapacity()
    {
        if (size == 0 || (tail + 2) % size == head)
            Resize();
    }

    template <typename Data>
    inline void QueueVec<Data>::Reduce()
    {
        if (size > DEFAULT_QUEUE_SIZE && Size() < size / 4)
            Resize();
    }

    template <typename Data>
    void QueueVec<Data>::Resize()
    {
        ulong newSize = std::max(DEFAULT_QUEUE_SIZE, Size() * 2 + 1);
        Data *newArray = new Data[newSize];
        ulong newTail = 0;

        for (ulong i = 0; i < Size(); i++)
            std::swap(newArray[++newTail], array[(head + i) % size]);

        delete[] array;
        size = newSize;
        array = newArray;
        head = 1;
        tail = newTail;
    }

#undef DEFAULT_QUEUE_SIZE
#endif

}
