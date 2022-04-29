
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
    BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::operator=(const BinaryTreeVec<Data>::NodeVec &other)
    {
        if (this != &other)
        {
            value = other.value;
            index = other.index;
        }

        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::operator=(BinaryTreeVec<Data>::NodeVec &&other) noexcept
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
    bool BinaryTreeVec<Data>::NodeVec::operator==(const BinaryTreeVec<Data>::NodeVec &other) const noexcept
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
        return nodes[2 * index + 1] == nullptr;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
    {
        return nodes[2 * index + 2] == nullptr;
    }

    // template <typename Data>
    // BinaryTree<Data>::Node &BinaryTreeVec<Data>::NodeVec::LeftChild() const
    // {
    //     if (!HasLeftChild())
    //         throw std::length_error("accessing empty child");

    //     return vector[2 * index + 1];
    // }

    // template <typename Data>
    // Node &BinaryTreeVec<Data>::NodeVec::RightChild() const
    // {
    //     if (!HasRightChild())
    //         throw std::length_error("accessing empty child");

    //     return vector[2 * index + 2];
    // }

    /* ************************************************************************** */

    template <typename Data>
    void BinaryTreeVec<Data>::MapBreadth(MapFunctor functor, void *par)
    {
        for (ulong i = 0; i < nodes.Size(); i++)
        {
            if (nodes[i] != nullptr)
                functor(nodes[i].Element(), par);
        }
    }

}
