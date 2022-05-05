
#include "../../queue/vec/queuevec.hpp"

namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data &value)
    {
        this->value = value;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const BinaryTreeLnk<Data>::NodeLnk &other)
    {
        value = other.value;

        if (other.HasLeftChild())
            leftChild = new NodeLnk(other.LeftChild());

        if (other.HasRightChild())
            rightChild = new NodeLnk(other.RightChild());
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(BinaryTreeLnk<Data>::NodeLnk &&other) noexcept
    {
        std::swap(value, other.value);
        std::swap(leftChild, other.leftChild);
        std::swap(rightChild, other.rightChild);
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::~NodeLnk()
    {
        delete leftChild;
        delete rightChild;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const BinaryTreeLnk<Data>::NodeLnk &other)
    {
        if (this != &other)
        {
            delete leftChild;
            delete rightChild;

            value = other.value;

            if (other.HasLeftChild())
                leftChild = new NodeLnk(other.LeftChild());

            if (other.HasRightChild())
                rightChild = new NodeLnk(other.RightChild());
        }

        return *this;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(BinaryTreeLnk<Data>::NodeLnk &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(value, other.value);
            std::swap(leftChild, other.leftChild);
            std::swap(rightChild, other.rightChild);
        }

        return *this;
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::operator==(const BinaryTreeLnk<Data>::NodeLnk &other) const noexcept
    {
        return BinaryTree<Data>::Node::operator==(other);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const BinaryTreeLnk<Data>::NodeLnk &other) const noexcept
    {
        return BinaryTree<Data>::Node::operator!=(other);
    }

    template <typename Data>
    Data &BinaryTreeLnk<Data>::NodeLnk::Element() noexcept
    {
        return const_cast<Data &>(const_cast<const BinaryTreeLnk<Data>::NodeLnk *>(this)->Element());
    }

    template <typename Data>
    const Data &BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept
    {
        return value;
    }

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept
    {
        return leftChild != nullptr;
    }

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept
    {
        return rightChild != nullptr;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::LeftChild() const
    {
        if (!HasLeftChild())
            throw std::out_of_range("node doesn't have a left child");

        return *leftChild;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::RightChild() const
    {
        if (!HasRightChild())
            throw std::out_of_range("node doesn't have a right child");

        return *rightChild;
    }

    /* ************************************************************************** */

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data> &container)
    {
        if (container.Empty())
            return;

        root = new NodeLnk(container.Front());

        QueueVec<NodeLnk *> queue;
        queue.Enqueue(root);

        ulong i = 1;

        while (i < container.Size())
        {
            NodeLnk *parent = queue.HeadNDequeue();
            NodeLnk *leftChild = nullptr, *rightChild = nullptr;

            leftChild = new NodeLnk(container[i++]);
            queue.Enqueue(leftChild);

            if (i < container.Size())
            {
                rightChild = new NodeLnk(container[i++]);
                queue.Enqueue(rightChild);
            }

            parent->leftChild = leftChild;
            parent->rightChild = rightChild;
        }

        nodesCount = container.Size();
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> &other)
    {
        if (other.Empty())
            return;

        root = new NodeLnk(*(other.root));
        nodesCount = other.nodesCount;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> &&other) noexcept
    {
        std::swap(root, other.root);
        std::swap(nodesCount, other.nodesCount);
    }

    template <typename Data>
    BinaryTreeLnk<Data>::~BinaryTreeLnk()
    {
        delete root;
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> &other)
    {
        if (this != &other && !other.Empty())
        {
            delete root;
            root = other.Empty() ? nullptr : new NodeLnk(*(other.root));
            nodesCount = other.nodesCount;
        }

        return *this;
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(root, other.root);
            std::swap(nodesCount, other.nodesCount);
        }

        return *this;
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data> &other) const noexcept
    {
        return BinaryTree<Data>::operator==(other);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data> &other) const noexcept
    {
        return BinaryTree<Data>::operator!=(other);
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeLnk<Data>::Root() const
    {
        if (Empty())
            throw std::out_of_range("trying to access root of empty tree");

        return *root;
    };

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::Empty() const noexcept
    {
        return root == nullptr;
    };

    template <typename Data>
    inline ulong BinaryTreeLnk<Data>::Size() const noexcept
    {
        return nodesCount;
    };

    template <typename Data>
    void BinaryTreeLnk<Data>::Clear()
    {
        delete root;
        root = nullptr;
        nodesCount = 0;
    };

}
