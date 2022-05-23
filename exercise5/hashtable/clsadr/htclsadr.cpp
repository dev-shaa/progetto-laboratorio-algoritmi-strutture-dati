
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
    bool HashTableClsAdr<Data>::Insert(const Data &value)
    {
        Hash<Data> hashFunction;
        ulong key = HashKey(hashFunction(value));
        table[key].InsertAtBack(value);
    }

    /* ************************************************************************** */

}
