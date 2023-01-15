
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    BST<Data>::BST(const LinearContainer<Data> &container)
    {
        Insert(container);
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
        if (this->Size() != other.Size())
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
        if (this->Empty())
            throw std::length_error("can't access min because tree is empty");

        return FindPointerToMin(root)->Element();
    }

    template <typename Data>
    Data &BST<Data>::MinNRemove()
    {
        if (this->Empty())
            throw std::length_error("can't access min because tree is empty");

        return DataNDelete(DetachMin(root));
    }

    template <typename Data>
    void BST<Data>::RemoveMin()
    {
        if (this->Empty())
            throw std::length_error("can't access min because tree is empty");

        delete DetachMin(root);
    }

    template <typename Data>
    const Data &BST<Data>::Max() const
    {
        if (this->Empty())
            throw std::length_error("can't access max because tree is empty");

        return FindPointerToMax(root)->Element();
    }

    template <typename Data>
    Data &BST<Data>::MaxNRemove()
    {
        if (this->Empty())
            throw std::length_error("can't access max because tree is empty");

        return DataNDelete(DetachMax(root));
    }

    template <typename Data>
    void BST<Data>::RemoveMax()
    {
        if (this->Empty())
            throw std::length_error("can't remove max because tree is empty");

        delete DetachMax(root);
    }

    /* ************************************************************************** */

    template <typename Data>
    const Data &BST<Data>::Predecessor(const Data &value) const
    {
        NodeLnk *const *predecessor = FindPointerToPredecessor(root, value);

        if (predecessor == nullptr)
            throw std::length_error("can't find predecessor of value");

        return (*predecessor)->Element();
    }

    template <typename Data>
    Data &BST<Data>::PredecessorNRemove(const Data &value)
    {
        NodeLnk **predecessor = FindPointerToPredecessor(root, value);

        if (predecessor == nullptr)
            throw std::length_error("can't find predecessor of value");

        return DataNDelete(Detach(*predecessor));
    }

    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data &value)
    {
        NodeLnk **predecessor = FindPointerToPredecessor(root, value);

        if (predecessor == nullptr)
            throw std::length_error("can't find predecessor of value");

        delete Detach(*predecessor);
    }

    template <typename Data>
    const Data &BST<Data>::Successor(const Data &value) const
    {
        NodeLnk *const *successor = FindPointerToSuccessor(root, value);

        if (successor == nullptr)
            throw std::length_error("can't find successor of value");

        return (*successor)->Element();
    }

    template <typename Data>
    Data &BST<Data>::SuccessorNRemove(const Data &value)
    {
        NodeLnk **successor = FindPointerToSuccessor(root, value);

        if (successor == nullptr)
            throw std::length_error("can't find predecessor of value");

        return DataNDelete(Detach(*successor));
    }

    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data &value)
    {
        NodeLnk **successor = FindPointerToSuccessor(root, value);

        if (successor == nullptr)
            throw std::length_error("can't find predecessor of value");

        delete Detach(*successor);
    }

    /* ************************************************************************** */

    template <typename Data>
    bool BST<Data>::Insert(const Data &value)
    {
        NodeLnk *&pointer = FindPointerTo(root, value);

        if (pointer == nullptr)
        {
            pointer = new NodeLnk(value);
            nodesCount++;
            return true;
        }

        return false;
    }

    template <typename Data>
    bool BST<Data>::Insert(Data &&value)
    {
        NodeLnk *&pointer = FindPointerTo(root, value);

        if (pointer == nullptr)
        {
            pointer = new NodeLnk(std::move(value));
            nodesCount++;
            return true;
        }

        return false;
    }

    template <typename Data>
    bool BST<Data>::Remove(const Data &value) noexcept
    {
        NodeLnk *detachedNode = Detach(FindPointerTo(root, value));
        delete detachedNode;
        return detachedNode != nullptr;
    }

    template <typename Data>
    bool BST<Data>::Insert(const LinearContainer<Data> &container)
    {
        return DictionaryContainer<Data>::Insert(container);
    }

    template <typename Data>
    bool BST<Data>::Insert(LinearContainer<Data> &&container)
    {
        return DictionaryContainer<Data>::Insert(std::move(container));
    }

    template <typename Data>
    bool BST<Data>::Remove(const LinearContainer<Data> &container) noexcept
    {
        return DictionaryContainer<Data>::Remove(container);
    }

    template <typename Data>
    bool BST<Data>::Exists(const Data &value) const noexcept
    {
        return FindPointerTo(root, value) != nullptr;
    }

    /* ************************************************************************** */

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMin(NodeLnk *&root) noexcept
    {
        return const_cast<NodeLnk *&>(const_cast<const BST<Data> *>(this)->FindPointerToMin(root));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMin(NodeLnk *const &root) const noexcept
    {
        NodeLnk *const *minPointerReference = &root;
        NodeLnk *current = root;

        if (current != nullptr)
        {
            while (current->HasLeftChild())
            {
                minPointerReference = &current->leftChild;
                current = current->leftChild;
            }
        }

        return *minPointerReference;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMax(NodeLnk *&root) noexcept
    {
        return const_cast<NodeLnk *&>(const_cast<const BST<Data> *>(this)->FindPointerToMax(root));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMax(NodeLnk *const &root) const noexcept
    {
        NodeLnk *const *maxPointerReference = &root;
        NodeLnk *current = root;

        if (current != nullptr)
        {
            while (current->HasRightChild())
            {
                maxPointerReference = &current->rightChild;
                current = current->rightChild;
            }
        }

        return *maxPointerReference;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerTo(NodeLnk *&root, const Data &value) noexcept
    {
        return const_cast<NodeLnk *&>(const_cast<const BST<Data> *>(this)->FindPointerTo(root, value));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerTo(NodeLnk *const &root, const Data &value) const noexcept
    {
        NodeLnk *const *pointerReference = &root;
        NodeLnk *currentNode = root;

        while (currentNode != nullptr && currentNode->Element() != value)
        {
            if (value < currentNode->Element())
            {
                pointerReference = &currentNode->leftChild;
                currentNode = currentNode->leftChild;
            }
            else
            {
                pointerReference = &currentNode->rightChild;
                currentNode = currentNode->rightChild;
            }
        }

        return *pointerReference;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToPredecessor(NodeLnk *&root, const Data &value) noexcept
    {
        return const_cast<NodeLnk **>(const_cast<const BST<Data> *>(this)->FindPointerToPredecessor(root, value));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToPredecessor(NodeLnk *const &root, const Data &value) const noexcept
    {
        NodeLnk *const *predecessorPointerReference = &root;
        NodeLnk *const *predecessor = nullptr;
        NodeLnk *current = root;

        while (current != nullptr && current->Element() != value)
        {
            if (value < current->Element())
            {
                predecessorPointerReference = &current->leftChild;
                current = current->leftChild;
            }
            else
            {
                predecessor = predecessorPointerReference;
                predecessorPointerReference = &current->rightChild;
                current = current->rightChild;
            }
        }

        return (current == nullptr || !current->HasLeftChild()) ? predecessor : &FindPointerToMax(current->leftChild);
    }

    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToSuccessor(NodeLnk *&root, const Data &value) noexcept
    {
        return const_cast<NodeLnk **>(const_cast<const BST<Data> *>(this)->FindPointerToSuccessor(root, value));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToSuccessor(NodeLnk *const &root, const Data &value) const noexcept
    {
        NodeLnk *const *successorPointerReference = &root;
        NodeLnk *const *successor = nullptr;
        NodeLnk *current = root;

        while (current != nullptr && current->Element() != value)
        {
            if (value < current->Element())
            {
                successor = successorPointerReference;
                successorPointerReference = &current->leftChild;
                current = current->leftChild;
            }
            else
            {
                successorPointerReference = &current->rightChild;
                current = current->rightChild;
            }
        }

        return (current == nullptr || !current->HasRightChild()) ? successor : &FindPointerToMin(current->rightChild);
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Detach(NodeLnk *&node) noexcept
    {
        if (node == nullptr)
            return nullptr;

        if (!node->HasLeftChild())
            return Skip2Right(node);

        if (!node->HasRightChild())
            return Skip2Left(node);

        NodeLnk *detachedNode = DetachMin(node->rightChild);
        node->Element() = detachedNode->Element();
        return detachedNode;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMin(NodeLnk *&root) noexcept
    {
        return Skip2Right(FindPointerToMin(root));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMax(NodeLnk *&root) noexcept
    {
        return Skip2Left(FindPointerToMax(root));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Skip2Left(NodeLnk *&node) noexcept
    {
        NodeLnk *detachedNode = nullptr;

        if (node != nullptr)
        {
            std::swap(detachedNode, node->leftChild);
            std::swap(detachedNode, node);
            nodesCount--;
        }

        return detachedNode;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Skip2Right(NodeLnk *&node) noexcept
    {
        NodeLnk *detachedNode = nullptr;

        if (node != nullptr)
        {
            std::swap(detachedNode, node->rightChild);
            std::swap(detachedNode, node);
            nodesCount--;
        }

        return detachedNode;
    }

    template <typename Data>
    Data &BST<Data>::DataNDelete(NodeLnk *node)
    {
        Data *value = new Data(std::move(node->Element()));
        delete node;
        return *value;
    }

}
