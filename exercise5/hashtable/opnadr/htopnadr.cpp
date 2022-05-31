
namespace lasd
{

#define DEFAULT_SIZE 4ul
#define EMPTY '\0'
#define FULL '\1'
#define REMOVED '\2'

    /* ************************************************************************** */

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr() : HashTableOpnAdr(DEFAULT_SIZE)
    {
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(ulong size) : HashTable<Data>()
    {
        if (size < DEFAULT_SIZE)
        {
            size = DEFAULT_SIZE;
        }
        else
        {
            // rounding unsigned long to power of 2
            size--;
            size |= size >> 1;
            size |= size >> 2;
            size |= size >> 4;
            size |= size >> 8;
            size |= size >> 16;
            size |= size >> 32;
            size++;
        }

        table.Clear(size);
        state.Clear(size);
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data> &container) : HashTableOpnAdr(container.Size(), container)
    {
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(ulong size, const LinearContainer<Data> &container) : HashTableOpnAdr(std::max(size, container.Size()))
    {
        DictionaryContainer<Data>::Insert(container);
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr &other) : HashTable<Data>(other)
    {
        size = other.size;
        table = other.table;
        state = other.state;
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr &&other) noexcept : HashTable<Data>(std::move(other))
    {
        table.Clear(DEFAULT_SIZE);
        state.Clear(DEFAULT_SIZE);

        std::swap(size, other.size);
        std::swap(table, other.table);
        std::swap(state, other.state);
    }

    template <typename Data>
    HashTableOpnAdr<Data> &HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr &other)
    {
        if (this != &other)
        {
            HashTable<Data>::operator=(other);
            size = other.size;
            table = other.table;
            state = other.state;
        }

        return *this;
    }

    template <typename Data>
    HashTableOpnAdr<Data> &HashTableOpnAdr<Data>::operator=(HashTableOpnAdr &&other) noexcept
    {
        if (this != &other)
        {
            HashTable<Data>::operator=(std::move(other));
            std::swap(size, other.size);
            std::swap(table, other.table);
            std::swap(state, other.state);
        }

        return *this;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr &other) const noexcept
    {
        return HashTable<Data>::operator==(other);
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(const Data &value)
    {
        if (Size() * 2 >= table.Size())
            Resize(2 * table.Size());

        ulong position = FindEmptyToInsert(value);

        if (position != table.Size())
        {
            table[position] = value;
            state[position] = FULL;
            size++;
            return true;
        }

        return false;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(Data &&value)
    {
        if (Size() * 2 >= table.Size())
            Resize(2 * table.Size());

        ulong position = FindEmptyToInsert(value);

        if (position != table.Size())
        {
            table[position] = std::move(value);
            state[position] = FULL;
            size++;
            return true;
        }

        return false;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data &value) noexcept
    {
        ulong position = Find(value);

        if (position != table.Size())
        {
            state[position] = REMOVED;
            size--;
            return true;
        }

        return false;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Exists(const Data &value) const noexcept
    {
        return Find(value) != table.Size();
    }

    template <typename Data>
    void RehashOpnAdr(Data &value, void *newTable)
    {
        ((HashTableOpnAdr<Data> *)newTable)->Insert(std::move(value));
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Resize(ulong size)
    {
        HashTableOpnAdr<Data> newTable(std::max(size, Size()));
        Map(&RehashOpnAdr<Data>, (void *)&newTable);
        *this = std::move(newTable);
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Map(MapFunctor functor, void *par)
    {
        for (ulong i = 0; i < table.Size(); i++)
            if (state[i] == FULL)
                functor(table[i], par);
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Fold(FoldFunctor functor, const void *par, void *accumulator) const
    {
        for (ulong i = 0; i < table.Size(); i++)
            if (state[i] == FULL)
                functor(table[i], par, accumulator);
    }

    template <typename Data>
    inline bool HashTableOpnAdr<Data>::Empty() const noexcept
    {
        return size == 0;
    }

    template <typename Data>
    inline ulong HashTableOpnAdr<Data>::Size() const noexcept
    {
        return size;
    }

    template <typename Data>
    void HashTableOpnAdr<Data>::Clear()
    {
        table.Clear(DEFAULT_SIZE);
        state.Clear(DEFAULT_SIZE);
        size = 0;
    }

    template <typename Data>
    ulong HashTableOpnAdr<Data>::Find(const Data &value) const noexcept
    {
        ulong start = this->HashKey(value, table.Size());
        ulong current;

        for (ulong i = 0; i < table.Size(); i++)
        {
            current = (start + ((i * i + i) / 2)) % table.Size();

            if (state[current] == EMPTY)
                return table.Size();

            if (table[current] == value && state[current] == FULL)
                return current;
        }

        return table.Size();
    }

    template <typename Data>
    ulong HashTableOpnAdr<Data>::FindEmptyToInsert(const Data &value) const noexcept
    {
        ulong start = this->HashKey(value, table.Size());
        ulong current, freeSpace;
        bool encounteredFreeSpace = false;

        for (ulong i = 0; i < table.Size(); i++)
        {
            current = (start + ((i * i + i) / 2)) % table.Size();

            if (state[current] == EMPTY)
                return encounteredFreeSpace ? freeSpace : current;

            if (table[current] == value && state[current] == FULL)
            {
                // we can make a little optimization by moving the value in the first free space, to speed up future searches
                if (encounteredFreeSpace)
                {
                    state[current] = REMOVED;
                    table[freeSpace] = std::move(table[current]);
                    state[freeSpace] = FULL;
                }

                return table.Size();
            }

            // the value may be already in the table further ahead, but in any case remember this spot
            if (state[current] == REMOVED && !encounteredFreeSpace)
            {
                encounteredFreeSpace = true;
                freeSpace = current;
            }
        }

        return encounteredFreeSpace ? freeSpace : table.Size();
    }

    /* ************************************************************************** */

#undef DEFAULT_SIZE
#undef EMPTY
#undef FULL
#undef REMOVED

}
