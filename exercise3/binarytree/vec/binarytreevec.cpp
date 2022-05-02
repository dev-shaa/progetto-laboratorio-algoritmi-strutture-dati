
namespace lasd
{

    /* ************************************************************************** */
    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &value, ulong index)
    {
        this->value = value;
        this->index = index;
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
        return i < nodes->Size() && nodes[i] != nullptr;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
    {
        ulong i = 2 * index + 2;
        return i < nodes->Size() && nodes[i] != nullptr;
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeVec<Data>::NodeVec::LeftChild() const
    {
        if (!HasLeftChild())
            throw std::out_of_range("accessing non-existant child");

        return (*nodes)[2 * index + 1];
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeVec<Data>::NodeVec::RightChild() const
    {
        if (!HasRightChild())
            throw std::out_of_range("accessing non-existant child");

        return nodes[2 * index + 2];
    }

    /* ************************************************************************** */

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data> &container)
    {
        nodes = new Vector<Data>(container.Size());

        for (ulong i = 0; i < container.Size(); i++)
            (*nodes)[i] = new NodeVec(container[i], i);
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &other)
    {
        // fixme: deep copy
        nodes = other.nodes;
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&other) noexcept
    {
        std::swap(nodes, other.nodes);
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeVec<Data>::Root() const
    {
        if (Empty())
            throw std::length_error("trying to access root of empty tree");

        return (*nodes)[0];
    };

    template <typename Data>
    bool BinaryTreeVec<Data>::Empty() const noexcept
    {
        return Size() == 0;
    };

    template <typename Data>
    ulong BinaryTreeVec<Data>::Size() const noexcept
    {
        return nodesCount;
    };

    template <typename Data>
    void BinaryTreeVec<Data>::Clear()
    {
        delete nodes;
    };

    template <typename Data>
    void BinaryTreeVec<Data>::MapBreadth(MapFunctor functor, void *par)
    {
        for (ulong i = 0; i < nodes->Size(); i++)
        {
            if ((*nodes)[i] != nullptr)
                functor((*nodes)[i]->Element(), par);
        }
    }

}
