
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    BST<Data>::BST(const LinearContainer<Data> &container)
    {
        for (ulong i = 0; i < container.Size(); i++)
            Insert(container[i]);
    }

    template <typename Data>
    BST<Data>::BST(const BST<Data> &other)
    {
        // todo: implementation
    }

    template <typename Data>
    BST<Data>::BST(BST<Data> &&other) noexcept
    {
        // todo: implementation
    }

    template <typename Data>
    BST<Data> &BST<Data>::operator=(const BST<Data> &other)
    {
        BinaryTreeLnk<Data>::operator=(other);
        return *this;
    }

    template <typename Data>
    BST<Data> &BST<Data>::operator=(BST<Data> &&other) noexcept
    {
        BinaryTreeLnk<Data>::operator=(std::move(other));
        return *this;
    }

    template <typename Data>
    bool BST<Data>::operator==(const BST<Data> &other) const noexcept
    {
        if (Size() != other.Size())
            return false;

        BTInOrderIterator<Data> thisIterator(*this);
        BTInOrderIterator<Data> otherIterator(other);

        while (!thisIterator.Terminated() && *thisIterator == *otherIterator)
        {
            ++thisIterator;
            ++otherIterator;
        }

        return thisIterator.Terminated();
    }

    template <typename Data>
    bool BST<Data>::operator!=(const BST<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    bool BST<Data>::Exists(const Data &value) const noexcept
    {
        NodeLnk *node = root;

        while (node != nullptr && node->Element() != value)
            node = value < node->Element() ? node->leftChild : node->rightChild;

        return node != nullptr;
    }

    /* ************************************************************************** */

}
