
#include "../queue/lst/queuelst.hpp"

namespace lasd
{

    template <typename Data>
    bool BinaryTree<Data>::Node::operator==(const BinaryTree<Data>::Node &other) const noexcept
    {
        return Element() == other.Element() &&
               ((HasLeftChild() && other.HasLeftChild() && LeftChild() == other.LeftChild()) || (!HasLeftChild() && !other.HasLeftChild())) &&
               ((HasRightChild() && other.HasRightChild() && RightChild() == other.RightChild()) || (!HasRightChild() && !other.HasRightChild()));
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
    bool BinaryTree<Data>::operator==(const BinaryTree<Data> &other) const noexcept
    {
        return Root() == other.Root();
    }

    template <typename Data>
    bool BinaryTree<Data>::operator!=(const BinaryTree<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    void BinaryTree<Data>::Map(MapFunctor functor, void *par)
    {
        MapPreOrder(functor, par);
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(MapFunctor functor, void *par)
    {
        // todo: implementation
        MapPreOrderAux(functor, par, Root());
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrderAux(MapFunctor functor, void *par, Node &node)
    {
        // visit node

        // visit left
        if (node.HasLeftChild())
            MapPreOrderAux(functor, par, node.LeftChild());

        // visit right
        if (node.HasRightChild())
            MapPreOrderAux(functor, par, node.RightChild());
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(MapFunctor functor, void *par)
    {
        // todo: implementation
        MapPostOrderAux(functor, par, Root());
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrderAux(MapFunctor functor, void *par, Node &node)
    {
        // visit left
        if (node.HasLeftChild())
            MapPostOrderAux(functor, par, node.LeftChild());

        // visit right
        if (node.HasRightChild())
            MapPostOrderAux(functor, par, node.RightChild());

        // visit node
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(MapFunctor functor, void *par)
    {
        // todo: implementation
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrderAux(MapFunctor functor, void *par, Node &node)
    {
        // visit left
        if (node.HasLeftChild())
            MapInOrderAux(functor, par, node.LeftChild());

        // visit node

        // visit right
        if (node.HasRightChild())
            MapInOrderAux(functor, par, node.RightChild());
    }

    template <typename Data>
    void BinaryTree<Data>::MapBreadth(MapFunctor functor, void *par)
    {
        // todo: implementation
    }

    template <typename Data>
    void BinaryTree<Data>::MapBreadthAux(MapFunctor functor, void *par, Node &node)
    {
        // todo: implementation
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
