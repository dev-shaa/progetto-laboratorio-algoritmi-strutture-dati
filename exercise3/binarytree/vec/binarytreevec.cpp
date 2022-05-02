
namespace lasd
{

    /* ************************************************************************** */
    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &value, ulong index, Vector<NodeVec *> *nodes)
    {
        this->value = value;
        this->index = index;
        this->nodes = nodes;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const BinaryTreeVec<Data>::NodeVec &other)
    {
        value = other.value;
        index = other.index;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(BinaryTreeVec<Data>::NodeVec &&other) noexcept
    {
        std::swap(value, other.value);
        std::swap(index, other.index);
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::operator=(const BinaryTreeVec<Data>::NodeVec &other)
    {
        if (this != &other)
        {
            value = other.value;
            index = other.index;
        }

        return *this;
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::operator=(BinaryTreeVec<Data>::NodeVec &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(value, other.value);
            std::swap(index, other.index);
        }

        return *this;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::operator==(const BinaryTreeVec<Data>::NodeVec &other) const noexcept
    {
        return BinaryTree<Data>::operator==(other);
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::operator!=(const BinaryTreeVec<Data>::NodeVec &other) const noexcept
    {
        return BinaryTree<Data>::operator!=(other);
    }

    template <typename Data>
    const Data &BinaryTreeVec<Data>::NodeVec::Element() const noexcept
    {
        return value;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
    {
        ulong i = 2 * index + 1;
        return i < nodes->Size() && (*nodes)[i] != nullptr;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
    {
        ulong i = 2 * index + 2;
        return i < nodes->Size() && (*nodes)[i] != nullptr;
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeVec<Data>::NodeVec::LeftChild() const
    {
        if (!HasLeftChild())
            throw std::out_of_range("accessing non-existant child");

        return *((*nodes)[2 * index + 1]);
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeVec<Data>::NodeVec::RightChild() const
    {
        if (!HasRightChild())
            throw std::out_of_range("accessing non-existant child");

        return *((*nodes)[2 * index + 2]);
    }

    /* ************************************************************************** */

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data> &container)
    {
        nodesCount = container.Size();
        nodes.Clear(nodesCount);

        for (ulong i = 0; i < nodesCount; i++)
            nodes[i] = new NodeVec(container[i], i, &nodes);
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &other)
    {
        nodes.Clear(other.nodes.Size());

        for (ulong i = 0; i < nodes.Size(); i++)
            nodes[i] = other.nodes[i] == nullptr ? nullptr : new NodeVec(*(other.nodes[i]));

        nodesCount = other.nodesCount;
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&other) noexcept
    {
        std::swap(nodes, other.nodes);
        std::swap(nodesCount, other.nodesCount);
    }

    template <typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec()
    {
        for (ulong i = 0; i < nodes.Size(); i++)
            delete nodes[i];
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> &other)
    {
        if (this != &other)
        {
            nodes.Clear(other.nodes.Size());

            for (ulong i = 0; i < nodes.Size(); i++)
                nodes[i] = other.nodes[i] == nullptr ? nullptr : new NodeVec(*(other.nodes[i]));

            nodesCount = other.nodesCount;
        }

        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(nodes, other.nodes);
            std::swap(nodesCount, other.nodesCount);
        }

        return *this;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> &other) const noexcept
    {
        return BinaryTree<Data>::operator==(other);
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> &other) const noexcept
    {
        return BinaryTree<Data>::operator!=(other);
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeVec<Data>::Root() const
    {
        if (Empty())
            throw std::out_of_range("trying to access root of empty tree");

        return *(nodes[0]);
    };

    template <typename Data>
    inline bool BinaryTreeVec<Data>::Empty() const noexcept
    {
        return Size() == 0;
    };

    template <typename Data>
    inline ulong BinaryTreeVec<Data>::Size() const noexcept
    {
        return nodesCount;
    };

    template <typename Data>
    void BinaryTreeVec<Data>::Clear()
    {
        nodes.Clear();
    };

    template <typename Data>
    void BinaryTreeVec<Data>::MapBreadth(MapFunctor functor, void *par)
    {
        for (ulong i = 0; i < nodes.Size(); i++)
        {
            if (nodes[i] != nullptr)
                functor(nodes[i]->Element(), par);
        }
    }

    template <typename Data>
    void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor functor, const void *par, void *accumulator) const
    {
        for (ulong i = 0; i < nodes.Size(); i++)
        {
            if (nodes[i] != nullptr)
                functor(nodes[i]->Element(), par, accumulator);
        }
    }

}
