
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr() : HashTableClsAdr(5)
    {
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(ulong size)
    {
        table.Clear(size);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data> container)
    {
        // todo: impl
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(ulong size, const LinearContainer<Data> container) : HashTableClsAdr(size)
    {
        Insert(container);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr &other)
    {
        size = other.size;
        table = other.table;
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr &&other) noexcept
    {
        std::swap(size, other.size);
        std::swap(table, other.table);
    }

    template <typename Data>
    HashTableClsAdr<Data> &HashTableClsAdr<Data>::operator=(const HashTableClsAdr &other)
    {
        if (this != &other)
        {
            size = other.size;
            table = other.table;
        }

        return *this;
    }

    template <typename Data>
    HashTableClsAdr<Data> &HashTableClsAdr<Data>::operator=(HashTableClsAdr &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(size, other.size);
            std::swap(table, other.table);
        }

        return *this;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept
    {
        }

    template <typename Data>
    bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data &value)
    {
        bool inserted = table[HashKey(value)].Insert(value);

        if (inserted)
            size++;

        return inserted;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(Data &&value)
    {
        bool inserted = table[HashKey(value)].Insert(std::move(value));

        if (inserted)
            size++;

        return inserted;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data &value) noexcept
    {
        bool removed = table[HashKey(value)].Remove(value);

        if (removed)
            size--;

        return removed;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data &value) const noexcept
    {
        return table[HashKey(value)].Exists(value);
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Resize(ulong size)
    {
        HashTableClsAdr<Data> newTable(size);

        Map(&MoveToTable<Data>, (void *)&newTable);

        std::swap(table, newTable);
    }

    template <typename Data>
    void HashTableClsAdr<Data>::MoveToTable(Data &value, void *newTable)
    {
        ((HashTableClsAdr *)newTable)->Insert(std::move(value));
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Map(MapFunctor functor, void *par)
    {
        for (ulong i = 0; i < table.Size(); i++)
            table[i].Map(functor, par);
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Empty() const noexcept
    {
        return size == 0;
    }

    template <typename Data>
    ulong HashTableClsAdr<Data>::Size() const noexcept
    {
        return size;
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Clear()
    {
        table.Clear();
        size = 0;
    }

    /* ************************************************************************** */

}
