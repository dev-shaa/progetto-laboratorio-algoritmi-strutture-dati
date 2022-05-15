
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

        NodeLnk *node = root;

        while (node->HasLeftChild())
            node = node->leftChild;

        return node->Element();
    }

    template <typename Data>
    Data &BST<Data>::MinNRemove()
    {
        if (Empty())
            throw std::length_error("can't access min because tree is empty");

        // todo: implementation
    }

    template <typename Data>
    void BST<Data>::RemoveMin()
    {
        if (Empty())
            throw std::length_error("can't remove min because tree is empty");

        // what if min has right child?

        // NodeLnk *parent = nullptr;
        // NodeLnk *current = root;

        // while (current->HasLeftChild())
        // {
        //     parent = current;
        //     current = current->leftChild;
        // }

        // if (parent == nullptr)
        //     root = nullptr;
        // else
        //     parent->leftChild = nullptr;

        // delete current;
        // nodesCount--;
    }

    template <typename Data>
    const Data &BST<Data>::Max() const
    {
        if (Empty())
            throw std::length_error("can't access max because tree is empty");

        NodeLnk *node = root;

        while (node->HasRightChild())
            node = node->rightChild;

        return node->Element();
    }

    template <typename Data>
    Data &BST<Data>::MaxNRemove()
    {
        if (Empty())
            throw std::length_error("can't access max because tree is empty");

        // todo:implementation
    }

    template <typename Data>
    void BST<Data>::RemoveMax()
    {
        if (Empty())
            throw std::length_error("can't remove max because tree is empty");

        // todo:implementation
    }

    template <typename Data>
    const Data &BST<Data>::Predecessor(const Data &value) const
    {
        if (Empty())
            throw std::length_error("can't access predecessor because tree is empty");

        // todo: implementation
    }

    template <typename Data>
    Data &BST<Data>::PredecessorNRemove(const Data &value)
    {
        if (Empty())
            throw std::length_error("can't access predecessor because tree is empty");

        // todo: implementation
    }

    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data &value)
    {
        if (Empty())
            throw std::length_error("can't remove predecessor because tree is empty");

        // todo: implementation
    }

    template <typename Data>
    const Data &BST<Data>::Successor(const Data &value) const
    {
        if (Empty())
            throw std::length_error("can't access successor because tree is empty");

        // todo: implementation
    }

    template <typename Data>
    Data &BST<Data>::SuccessorNRemove(const Data &value)
    {
        if (Empty())
            throw std::length_error("can't access successor because tree is empty");

        // todo: implementation
    }

    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data &value)
    {
        if (Empty())
            throw std::length_error("can't remove successor because tree is empty");

        // todo: implementation
    }

    /* ************************************************************************** */

    template <typename Data>
    void BST<Data>::Insert(const Data &value)
    {
        Insert(new NodeLnk(value));
    }

    template <typename Data>
    void BST<Data>::Insert(Data &&value)
    {
        Insert(new NodeLnk(std::move(value)));
    }

    template <typename Data>
    void BST<Data>::Insert(NodeLnk *node) noexcept
    {
        if (Empty())
        {
            root = node;
        }
        else
        {
            NodeLnk *parent = nullptr;
            NodeLnk *current = root;

            while (current != nullptr)
            {
                parent = current;
                current = value < current->Element() ? current->leftChild : current->rightChild;
            }

            if (value < parent->Element())
                parent->leftChild = node;
            else
                parent->rightChild = node;
        }

        nodesCount++;
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

    // template <typename Data>
    // void BST<Data>::DetachMin(NodeLnk *node) noexcept
    // {
    //     if (node == nullptr)
    //         return;

    //     Node *parent = nullptr;

    //     while (node->HasLeftChild())
    //         node = node->leftChild;
    // }

    // template <typename Data>
    // BST<Data>::NodeLnk *BST<Data>::FindPointerToMin(NodeLnk *node) const noexcept
    // {
    //     if (node != nullptr)
    //     {
    //         while (node->HasLeftChild())
    //             node = node->leftChild;
    //     }

    //     return node;
    // }

    // template <typename Data>
    // typename BinaryTreeLnk<Data>::NodeLnk *BST<Data>::FindPointerToMax(typename BinaryTreeLnk<Data>::NodeLnk *node) const noexcept
    // {
    //     if (node != nullptr)
    //     {
    //         while (node->HasRightChild())
    //             node = node->rightChild;
    //     }

    //     return node;
    // }

}
