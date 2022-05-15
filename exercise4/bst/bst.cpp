
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
    BST<Data>::BST(const BST<Data> &other) : BinaryTreeLnk<Data>(other)
    {
    }

    template <typename Data>
    BST<Data>::BST(BST<Data> &&other) noexcept : BinaryTreeLnk<Data>(std::move(other))
    {
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

    /* ************************************************************************** */

    template <typename Data>
    const Data &BST<Data>::Min() const
    {
        if (Empty())
            throw std::length_error("can't access min because tree is empty");

        return FindPointerToMin()->Element();
    }

    template <typename Data>
    Data &BST<Data>::MinNRemove()
    {
        if (Empty())
            throw std::length_error("can't access min because tree is empty");

        // todo:implementation
    }

    template <typename Data>
    void BST<Data>::RemoveMin()
    {
        if (Empty())
            throw std::length_error("can't remove min because tree is empty");

        // todo:implementation
    }

    /* ************************************************************************** */

    template <typename Data>
    void BST<Data>::Insert(const Data &value)
    {
        // todo: implementation
    }

    template <typename Data>
    void BST<Data>::Insert(Data &&value)
    {
        // todo: implementation
    }

    template <typename Data>
    void BST<Data>::Remove(const Data &value)
    {
        // todo: implementation
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

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BST<Data>::FindPointerToMin(typename BinaryTreeLnk<Data>::NodeLnk *node) const noexcept
    {
        NodeLnk *node = root;

        while (node != nullptr && node->HasLeftChild())
            node = node->leftChild;

        return node;
    }

}
