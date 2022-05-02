
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
    Data &BinaryTree<Data>::Node::Element() noexcept
    {
        return const_cast<Data &>(const_cast<const BinaryTree<Data>::Node *>(this)->Element());
    }

    template <typename Data>
    inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept
    {
        return !(HasLeftChild() || HasRightChild());
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
    bool BinaryTree<Data>::Exists(const Data &value) const noexcept
    {
        return PreOrderFoldableContainer<Data>::Exists(value);
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
    void EnqueueData(const Data &value, const void *_, void *queue)
    {
        ((Queue<Data> *)queue)->Enqueue(value);
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &tree)
    {
        this->tree = &tree;
        elements = new QueueLst<Data>();
        tree.FoldPreOrder(&EnqueueData<Data>, nullptr, elements);
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator &other)
    {
        elements = other.elements;
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator &&other) noexcept
    {
        std::swap(elements, other.elements);
    }

    template <typename Data>
    BTPreOrderIterator<Data>::~BTPreOrderIterator()
    {
        delete elements;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator &other)
    {
        if (this != &other)
        {
            elements = other.elements;
            tree = other.tree;
        }

        return *this;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(BTPreOrderIterator &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(elements, other.elements);
            std::swap(tree, other.tree);
        }

        return *this;
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator &other) const noexcept
    {
        return **this == *other;
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
            throw std::length_error("can't progess iterator because it has terminated");

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
        elements->Clear();
        tree->FoldPreOrder(&EnqueueData<Data>, nullptr, nullptr);
    }

    /* ************************************************************************** */

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> &tree)
    {
        this->tree = &tree;
        elements = new QueueLst<Data>();
        tree.FoldPostOrder(&EnqueueData<Data>, nullptr, elements);
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator &other)
    {
        elements = other.elements;
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator &&other) noexcept
    {
        std::swap(elements, other.elements);
    }

    template <typename Data>
    BTPostOrderIterator<Data>::~BTPostOrderIterator()
    {
        delete elements;
    }

    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator &other)
    {
        if (this != &other)
        {
            elements = other.elements;
            tree = other.tree;
        }

        return *this;
    }

    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(BTPostOrderIterator &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(elements, other.elements);
            std::swap(tree, other.tree);
        }

        return *this;
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator &other) const noexcept
    {
        return **this == *other;
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &BTPostOrderIterator<Data>::operator*()
    {
        if (Terminated())
            throw std::length_error("terminated");

        return elements->Head();
    }

    template <typename Data>
    void BTPostOrderIterator<Data>::operator++()
    {
        if (Terminated())
            throw std::length_error("can't progess iterator because it has terminated");

        elements->Dequeue();
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::Terminated() const noexcept
    {
        return elements->Empty();
    }

    template <typename Data>
    void BTPostOrderIterator<Data>::Reset() noexcept
    {
        elements->Clear();
        tree->FoldPostOrder(&EnqueueData<Data>, nullptr, nullptr);
    }

    /* ************************************************************************** */

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &tree)
    {
        this->tree = &tree;
        elements = new QueueLst<Data>();
        tree.FoldPostOrder(&EnqueueData<Data>, nullptr, elements);
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator &other)
    {
        elements = other.elements;
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator &&other) noexcept
    {
        std::swap(elements, other.elements);
    }

    template <typename Data>
    BTInOrderIterator<Data>::~BTInOrderIterator()
    {
        delete elements;
    }

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(const BTInOrderIterator &other)
    {
        if (this != &other)
        {
            elements = other.elements;
            tree = other.tree;
        }

        return *this;
    }

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(BTInOrderIterator &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(elements, other.elements);
            std::swap(tree, other.tree);
        }

        return *this;
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator &other) const noexcept
    {
        return **this == *other;
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &BTInOrderIterator<Data>::operator*()
    {
        if (Terminated())
            throw std::length_error("terminated");

        return elements->Head();
    }

    template <typename Data>
    void BTInOrderIterator<Data>::operator++()
    {
        if (Terminated())
            throw std::length_error("can't progess iterator because it has terminated");

        elements->Dequeue();
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept
    {
        return elements->Empty();
    }

    template <typename Data>
    void BTInOrderIterator<Data>::Reset() noexcept
    {
        elements->Clear();
        tree->FoldPostOrder(&EnqueueData<Data>, nullptr, nullptr);
    }

    /* ************************************************************************** */

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> &tree)
    {
        this->tree = &tree;
        elements = new QueueLst<Data>();
        tree.FoldPostOrder(&EnqueueData<Data>, nullptr, elements);
    }

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator &other)
    {
        elements = other.elements;
    }

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator &&other) noexcept
    {
        std::swap(elements, other.elements);
    }

    template <typename Data>
    BTBreadthIterator<Data>::~BTBreadthIterator()
    {
        delete elements;
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator=(const BTBreadthIterator &other)
    {
        if (this != &other)
        {
            elements = other.elements;
            tree = other.tree;
        }

        return *this;
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator=(BTBreadthIterator &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(elements, other.elements);
            std::swap(tree, other.tree);
        }

        return *this;
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator &other) const noexcept
    {
        return **this == *other;
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &BTBreadthIterator<Data>::operator*()
    {
        if (Terminated())
            throw std::length_error("terminated");

        return elements->Head();
    }

    template <typename Data>
    void BTBreadthIterator<Data>::operator++()
    {
        if (Terminated())
            throw std::length_error("can't progess iterator because it has terminated");

        elements->Dequeue();
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::Terminated() const noexcept
    {
        return elements->Empty();
    }

    template <typename Data>
    void BTBreadthIterator<Data>::Reset() noexcept
    {
        elements->Clear();
        tree->FoldPostOrder(&EnqueueData<Data>, nullptr, nullptr);
    }

}
