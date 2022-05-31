
namespace lasd
{

#define DEFAULT_SIZE 4ul

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr() : HashTableClsAdr(DEFAULT_SIZE)
    {
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(ulong size) : HashTable<Data>()
    {
        table.Clear(std::max(1ul, size));
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data> &container) : HashTableClsAdr(container.Size(), container)
    {
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(ulong size, const LinearContainer<Data> &container) : HashTableClsAdr(size)
    {
        DictionaryContainer<Data>::Insert(container);
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr &other) : HashTable<Data>(other)
    {
        size = other.size;
        table = other.table;
    }

    template <typename Data>
    HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr &&other) noexcept : HashTable<Data>(std::move(other))
    {
        std::swap(size, other.size);
        std::swap(table, other.table);
    }

    template <typename Data>
    HashTableClsAdr<Data> &HashTableClsAdr<Data>::operator=(const HashTableClsAdr &other)
    {
        if (this != &other)
        {
            HashTable<Data>::operator=(other);
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
            HashTable<Data>::operator=(std::move(other));
            std::swap(size, other.size);
            std::swap(table, other.table);
        }

        return *this;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr &other) const noexcept
    {
        return HashTable<Data>::operator==(other);
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(const Data &value)
    {
        bool inserted = table[this->HashKey(value, table.Size())].Insert(value);

        if (inserted)
            size++;

        return inserted;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Insert(Data &&value)
    {
        bool inserted = table[this->HashKey(value, table.Size())].Insert(std::move(value));

        if (inserted)
            size++;

        return inserted;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Remove(const Data &value) noexcept
    {
        bool removed = table[this->HashKey(value, table.Size())].Remove(value);

        if (removed)
            size--;

        return removed;
    }

    template <typename Data>
    bool HashTableClsAdr<Data>::Exists(const Data &value) const noexcept
    {
        return table[this->HashKey(value, table.Size())].Exists(value);
    }

    template <typename Data>
    void RehashingClsAdr(Data &value, void *newTable)
    {
        ((HashTableClsAdr<Data> *)newTable)->Insert(std::move(value));
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Resize(ulong size)
    {
        HashTableClsAdr<Data> newTable(size);
        Map(&RehashingClsAdr<Data>, (void *)&newTable);
        std::swap(*this, newTable);
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Map(MapFunctor functor, void *par)
    {
        for (ulong i = 0; i < table.Size(); i++)
            table[i].Map(functor, par);
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Fold(FoldFunctor functor, const void *par, void *accumulator) const
    {
        for (ulong i = 0; i < table.Size(); i++)
            table[i].Fold(functor, par, accumulator);
    }

    template <typename Data>
    inline bool HashTableClsAdr<Data>::Empty() const noexcept
    {
        return size == 0;
    }

    template <typename Data>
    inline ulong HashTableClsAdr<Data>::Size() const noexcept
    {
        return size;
    }

    template <typename Data>
    void HashTableClsAdr<Data>::Clear()
    {
        table.Clear(DEFAULT_SIZE);
        size = 0;
    }

#undef DEFAULT_SIZE

}
