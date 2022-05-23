#include <string>

namespace lasd
{

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
    class Hash<std::string>
    {

    public:
        ulong operator()(const std::string &value) const noexcept
        {
            // hashing function: djb2
            // http://www.cse.yorku.ca/~oz/hash.html

            unsigned long hash = 5381;

            for (ulong i = 0; i < value.length(); i++)
                hash = ((hash << 5) + hash) + value[i]; /* hash * 33 + c */

            return hash;
        }
    };

    /* ************************************************************************** */

}
