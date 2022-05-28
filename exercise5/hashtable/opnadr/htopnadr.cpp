namespace lasd
{

#define EMPTY '\0'
#define FULL '\1'
#define REMOVED '\2'
#define DEFAULT_HASH_TABLE 8ul

    /* ************************************************************************** */

    ulong RoundToPowerOfTwo(ulong v)
    {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v |= v >> 32;
        v++;
        return v;
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr() : HashTableOpnAdr(DEFAULT_HASH_TABLE)
    {
    }

    template <typename Data>
    HashTableOpnAdr<Data>::HashTableOpnAdr(ulong size) : HashTable<Data>()
    {
        size = RoundToPowerOfTwo(size);
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
        // fix initialization

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
        if (Size() == table.Size())
            Resize(2 * Size());

        ulong start = this->HashKey(value, table.Size());
        ulong current = start;

        bool encounteredFreeSpace = false;
        ulong freeSpace;

        bool inserted = false;

        for (ulong i = 0; i < table.Size(); i++)
        {
            // the value is not in the map
            if (state[current] == EMPTY)
            {
                ulong positionToInsert = encounteredFreeSpace ? freeSpace : current;
                table[positionToInsert] = value;
                state[positionToInsert] = FULL;
                return true;
            }

            // the value is in the map
            if (table[current] == value && state[current] == FULL)
            {
                if (encounteredFreeSpace)
                {
                    table[freeSpace] = value;
                    state[freeSpace] = FULL;
                    state[current] = REMOVED;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            if (state[current] == REMOVED && !encounteredFreeSpace)
            {
                encounteredFreeSpace = true;
                freeSpace = current;
            }

            current = (start + ((i * i + i) / 2)) % table.Size();
        }

        if (encounteredFreeSpace)
        {
        }

        // if (i < Size())
        // {
        //     if (encounteredFreeSpace)
        //     {
        //         state[positionToInsert] = REMOVED;
        //         current = positionToInsert;
        //     }

        //     // insert into table[current]
        // }

        // if (state[current] == EMPTY)
        // {
        //     std::swap(table[current], value);
        //     state[current] = FULL;
        //     inserted = true;
        // }

        return inserted;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Insert(Data &&value)
    {
        if (Size() == table.Size())
            Resize(2 * Size());

        ulong start = this->HashKey(value, table.Size());
        ulong current = start;

        bool encounteredFreeSpace = false;
        ulong freeSpacePosition;

        bool inserted = false;

        for (ulong i = 0; i < Size() && (state[current] != EMPTY || (table[current] != value && state[current] == FULL)); i++)
        {
            if (state[current] == REMOVED && !encounteredFreeSpace)
            {
                encounteredFreeSpace = true;
                freeSpacePosition = current;
            }

            current = (start + ((i * i + i) / 2)) % table.Size();
        }

        // if (state[current] == EMPTY)
        // {
        //     std::swap(table[current], value);
        //     state[current] = FULL;
        //     inserted = true;
        // }

        return inserted;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Remove(const Data &value) noexcept
    {
        ulong start = this->HashKey(value, table.Size());
        ulong current = start;
        bool removed = false;

        for (ulong i = 0; state[current] != EMPTY && table[current] != value; i++)
            current = (start + ((i * i + i) / 2)) % table.Size();

        if (table[current] == value)
        {
            state[current] = REMOVED;
            removed = true;
        }

        return removed;
    }

    template <typename Data>
    bool HashTableOpnAdr<Data>::Exists(const Data &value) const noexcept
    {
        ulong start = this->HashKey(value, table.Size());
        ulong current = start;

        for (ulong i = 0; state[current] != EMPTY && table[current] != value; i++)
            current = (start + ((i * i + i) / 2)) % table.Size();

        return table[current] == value;
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
        std::swap(*this, newTable);
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
        table.Clear(DEFAULT_HASH_TABLE);
        state.Clear(DEFAULT_HASH_TABLE);
        size = 0;
    }

    template <typename Data>
    ulong HashTableOpnAdr<Data>::Find(const Data &value) const noexcept
    {
        ulong start = this->HashKey(value, table.Size());
        ulong current = start;

        for (ulong i = 0; i < Size() && state[current] != EMPTY && table[current] != value; i++)
            current = (start + ((i * i + i) / 2)) % table.Size();

        return table[current] == value;
    }

    /* ************************************************************************** */

#undef DEFAULT_HASH_TABLE

}
