#include <string>

namespace lasd
{

#define FRACTIONAL_BIT 16777216ul
#define PRIME_FACTOR 4294967291ul // biggest prime smaller than 2^32 according to this site: https://bit.ly/3wVgCzL

    /* ************************************************************************** */

    template <>
    class Hash<int>
    {

    public:
        ulong operator()(const int &value) const noexcept
        {
            return value * value; // idk
        }
    };

    template <>
    class Hash<double>
    {

    public:
        ulong operator()(const double &value) const noexcept
        {
            // todo: impl
            // https://youtu.be/jSbsbKnYFJA?t=3169

            long intPart = floor(value);
            long fracPart = FRACTIONAL_BIT * (value - intPart);
            return intPart * fracPart;
        }
    };

    template <>
    class Hash<std::string>
    {

    public:
        ulong operator()(const std::string &value) const noexcept
        {
            // hashing function: djb2
            // https://bit.ly/3wSH7Wz

            unsigned long hash = 5381;

            for (ulong i = 0; i < value.length(); i++)
                hash = ((hash << 5) + hash) + value[i];

            return hash;
        }
    };

    template <typename Data>
    HashTable<Data>::HashTable()
    {
        std::default_random_engine gen(std::random_device{}());
        std::uniform_int_distribution<ulong> mulDist(1, PRIME_FACTOR);
        std::uniform_int_distribution<ulong> addDist(0, PRIME_FACTOR);

        a = mulDist(gen);
        b = addDist(gen);
    }

    template <typename Data>
    HashTable<Data>::HashTable(const HashTable &other)
    {
        a = other.a;
        b = other.b;
    }

    template <typename Data>
    HashTable<Data>::HashTable(HashTable &&other) noexcept
    {
        std::swap(a, other.a);
        std::swap(b, other.b);
    }

    template <typename Data>
    HashTable<Data> &HashTable<Data>::operator=(const HashTable &other)
    {
        if (this != &other)
        {
            a = other.a;
            b = other.b;
        }

        return *this;
    }

    template <typename Data>
    HashTable<Data> &HashTable<Data>::operator=(HashTable &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(a, other.a);
            std::swap(b, other.b);
        }

        return *this;
    }

    template <typename Data>
    void FindInTable(const Data &value, const void *table, void *result)
    {
        if (!((HashTable<Data> *)table)->Exists(value))
            *(bool *)result = false;
    }

    template <typename Data>
    bool HashTable<Data>::operator==(const HashTable &other) const noexcept
    {
        if (this->Size() != other.Size())
            return false;

        bool result = true;
        this->Fold(&FindInTable<Data>, (void *)&other, (void *)&result);
        return result;
    }

    template <typename Data>
    bool HashTable<Data>::operator!=(const HashTable &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    inline ulong HashTable<Data>::HashKey(const Data &value, const ulong &capacity) const noexcept
    {
        return ((a * hashFunction(value) + b) % PRIME_FACTOR) % capacity;
    }

    /* ************************************************************************** */

#undef PRIME_FACTOR

}
