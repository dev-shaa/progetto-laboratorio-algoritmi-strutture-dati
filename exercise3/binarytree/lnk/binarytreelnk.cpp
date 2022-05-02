
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data &value, NodeLnk *leftChild, NodeLnk *rightChild)
    {
        this->value = value;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const BinaryTreeLnk<Data>::NodeLnk &other)
    {
        value = other.value;
        leftChild = other.leftChild;
        rightChild = other.rightChild;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(BinaryTreeLnk<Data>::NodeLnk &&other) noexcept
    {
        std::swap(value, other.value);
        std::swap(leftChild, other.leftChild);
        std::swap(rightChild, other.rightChild);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const BinaryTreeLnk<Data>::NodeLnk &other)
    {
        if (this != &other)
        {
            value = other.value;
            leftChild = other.leftChild;
            rightChild = other.rightChild;
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
        return BinaryTree<Data>::operator==(other);
    }

    template <typename Data>
    bool BinaryTreeLnk<Data>::NodeLnk::operator!=(const BinaryTreeLnk<Data>::NodeLnk &other) const noexcept
    {
        return BinaryTree<Data>::operator!=(other);
    }

    template <typename Data>
    const Data &BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept
    {
        return value;
    }

    template <typename Data>
    Data &BinaryTreeLnk<Data>::NodeLnk::Element() noexcept
    {
        return const_cast<Data &>(const_cast<const BinaryTreeLnk<Data>::NodeLnk *>(this)->Element());
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
    typename BinaryTree<Data>::Node &BinaryTreeLnk<Data>::NodeLnk::LeftChild() const
    {
        if (!HasLeftChild())
            throw std::out_of_range("node doesn't have left child");

        return *leftChild;
    }

    template <typename Data>
    typename BinaryTree<Data>::Node &BinaryTreeLnk<Data>::NodeLnk::RightChild() const
    {
        if (!HasRightChild())
            throw std::out_of_range("node doesn't have right child");

        return *rightChild;
    }

    /* ************************************************************************** */

}
