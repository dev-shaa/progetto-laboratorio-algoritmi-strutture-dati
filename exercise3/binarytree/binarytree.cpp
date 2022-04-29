
#include "../queue/lst/queuelst.hpp"

namespace lasd
{

    template <typename Data>
    bool BinaryTree<Data>::Node::operator==(const BinaryTree<Data>::Node &other) const noexcept
    {
        // todo: implementation
    }

    template <typename Data>
    bool BinaryTree<Data>::Node::operator!=(const BinaryTree<Data>::Node &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept
    {
        return !HasLeftChild() && !HasRightChild();
    }

    /* ************************************************************************** */

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &tree)
    {
        elements = new QueueLst<Data>();

        // fill elements

        temp = new QueueLst<Data>(elements);
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator &iterator)
    {
        elements = iterator.elements;
        temp = iterator.temp;
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator &&iterator) noexcept
    {
        std::swap(elements, iterator.elements);
        std::swap(temp, iterator.temp);
    }

    template <typename Data>
    BTPreOrderIterator<Data>::~BTPreOrderIterator()
    {
        delete elements;
        delete temp;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator &other)
    {
        if (this != &other)
        {
            elements = other.elements;
            temp = other.temp;
        }

        return *this;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(BTPreOrderIterator &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(elements, iterator.elements);
            std::swap(temp, iterator.temp);
        }

        return *this;
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator &other) const noexcept
    {
        return *temp == *(other.temp);
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &BTPreOrderIterator<Data>::operator*()
    {
        if (Terminated())
            throw std::length_error("terminated");

        return elements->Head();
    }

    template <typename Data>
    void BTPreOrderIterator<Data>::operator++()
    {
        if (Terminated())
            throw std::length_error("terminated");

        elements->Dequeue();
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::Terminated() const noexcept
    {
        return elements->Empty();
    }

    template <typename Data>
    void BTPreOrderIterator<Data>::Reset() noexcept
    {
        delete elements;
        elements = new QueueLst<Data>(temp);
    }

    /* ************************************************************************** */

}
