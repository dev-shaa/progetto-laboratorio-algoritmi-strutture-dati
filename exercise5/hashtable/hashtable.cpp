#include <string>

namespace lasd
{

#define PRIME_FACTOR 18446744073709551557ul // biggest prime smaller than 2^64 according to this site: https://bit.ly/3z34gag

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
            return value * value; // idk
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
                hash = ((hash << 5) + hash) + value[i]; /* hash * 33 + c */

            return hash;
        }
    };

    template <typename Data>
    HashTable<Data>::HashTable(ulong capacity)
    {
        GenerateFactors(capacity);
    }

    template <typename Data>
    HashTable<Data>::HashTable(const HashTable &other)
    {
        a = other.a;
        b = other.b;
        capacity = other.capacity;
    }

    template <typename Data>
    HashTable<Data>::HashTable(HashTable &&other) noexcept
    {
        std::swap(a, other.a);
        std::swap(b, other.b);
        std::swap(capacity, other.capacity);
    }

    template <typename Data>
    HashTable<Data> &HashTable<Data>::operator=(const HashTable &other)
    {
        if (this != &other)
        {
            a = other.a;
            b = other.b;
            capacity = other.capacity;
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
            std::swap(capacity, other.capacity);
        }

        return *this;
    }

    template <typename Data>
    void HashTable<Data>::GenerateFactors(ulong capacity)
    {
        this->capacity = capacity;

        default_random_engine gen(random_device{}());
        uniform_int_distribution<ulong> mulDist(1, PRIME_FACTOR);
        uniform_int_distribution<ulong> addDist(0, PRIME_FACTOR);

        a = mulDist(gen);
        b = addDist(gen);
    }

    template <typename Data>
    inline ulong HashTable<Data>::HashKey(const Data &value) const noexcept
    {
        return ((a * hashFunction(value) + b) % PRIME_FACTOR) % capacity;
    }

    /* ************************************************************************** */

#undef PRIME_FACTOR

}
