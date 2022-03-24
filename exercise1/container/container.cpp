#include "container.hpp"

namespace lasd
{

    /* ************************************************************************** */

    // ...

    template <typename Data>
    Data *LinearContainer<Data>::Front()
    {
        if (Empty())
            throw std::length_error("can't access front item because container is empty");

        return this[0];
    }

    template <typename Data>
    Data *LinearContainer<Data>::Back()
    {
        if (Empty())
            throw std::length_error("can't access back item because container is empty");

        return this[Size() - 1];
    }

    /* ************************************************************************** */

}
