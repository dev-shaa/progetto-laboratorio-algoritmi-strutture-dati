
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

        return FindPointerToMin(root)->Element();
    }

    template <typename Data>
    Data &BST<Data>::MinNRemove()
    {
        if (Empty())
            throw std::length_error("can't access min because tree is empty");

        return DataNDelete(Skip2Right(FindPointerToMin(root)));
    }

    template <typename Data>
    void BST<Data>::RemoveMin()
    {
        if (Empty())
            throw std::length_error("can't access min because tree is empty");

        delete Skip2Right(FindPointerToMin(root));
    }

    template <typename Data>
    const Data &BST<Data>::Max() const
    {
        if (Empty())
            throw std::length_error("can't access max because tree is empty");

        return FindPointerToMax(root)->Element();
    }

    template <typename Data>
    Data &BST<Data>::MaxNRemove()
    {
        if (Empty())
            throw std::length_error("can't access max because tree is empty");

        return DataNDelete(Skip2Left(FindPointerToMax(root)));
    }

    template <typename Data>
    void BST<Data>::RemoveMax()
    {
        if (Empty())
            throw std::length_error("can't remove max because tree is empty");

        delete Skip2Left(FindPointerToMax(root));
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

        NodeLnk *curr = root;
        NodeLnk *cand = nullptr;

        // find node with value
        while (curr != nullptr && curr->Element() != value)
        {
            if (curr->Element() < value)
            {
                curr = curr->rightChild;
            }
            else
            {
                cand = curr;
                curr = curr->leftChild;
            }
        }

        // find successor
        return (curr == nullptr || !curr->HasRightChild()) ? cand->Element() : FindPointerToMin(curr->rightChild)->Element();
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
    void BST<Data>::Remove(const Data &value)
    {
        NodeLnk *node = FindPointerTo(root, value);

        if (node != nullptr)
        {
            NodeLnk *temp = node;

            if (!node->HasLeftChild())
            {
                Skip2Right(node);
            }
            else if (!node->HasRightChild())
            {
                Skip2Left(node);
            }
            else
            {
                temp = FindPointerToMin(node->rightChild);
                node->Element() = temp->Element();

                // delete min of node right subtree
                // rt->setRight(deletemin(rt->right()));
            }

            delete temp;
            nodesCount--;
        }
    }

    template <typename Data>
    bool BST<Data>::Exists(const Data &value) const noexcept
    {
        return FindPointerTo(root, value) != nullptr;
    }

    /* ************************************************************************** */

    template <typename Data>
    void BST<Data>::Insert(typename BST<Data>::NodeLnk *node) noexcept
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
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMin(NodeLnk *&root) const noexcept
    {
        // return root->HasLeftChild() ? FindPointerToMin(root->leftChild) : root;

        NodeLnk **ptr = &root;
        NodeLnk *cur = root;

        if (cur != nullptr)
        {
            while (cur->HasLeftChild())
            {
                ptr = &cur->leftChild;
                cur = cur->leftChild;
            }
        }

        return *ptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::FindPointerToMax(const typename BST<Data>::NodeLnk *&root) const noexcept
    {
        while (root->HasRightChild())
            root = root->rightChild;

        return root;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk *root, const Data &value) const noexcept
    {
        while (root != nullptr && node->Element() != value)
            root = value < root->Element() ? root->leftChild : root->rightChild;

        return root;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Skip2Left(NodeLnk *&nodeToDetach) noexcept
    {
        NodeLnk *temp = nullptr;

        if (nodeToDetach != nullptr)
        {
            std::swap(temp, nodeToDetach->leftChild);
            std::swap(temp, nodeToDetach);
            nodesCount--;
        }

        return temp;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Skip2Right(NodeLnk *&nodeToDetach) noexcept
    {
        NodeLnk *temp = nullptr;

        if (nodeToDetach != nullptr)
        {
            std::swap(temp, nodeToDetach->rightChild);
            std::swap(temp, nodeToDetach);
            nodesCount--;
        }

        return temp;
    }

    template <typename Data>
    Data &BST<Data>::DataNDelete(NodeLnk *node) noexcept
    {
        Data *value = new Data(std::move(node->Element()));
        delete removedNode;
        return *value;
    }

}
