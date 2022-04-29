
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
    bool BinaryTreeVec<Data>::NodeVec::operator==(const BinaryTreeVec<Data>::NodeVec &other) const noexcept
    {
        // todo: implementation
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::NodeVec::operator==(const BinaryTreeVec<Data>::NodeVec &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    const Data &BinaryTreeVec<Data>::NodeVec::Element() const noexcept
    {
        return value;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
    {
        return vector[2 * index + 1] == nullptr;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
    {
        return vector[2 * index + 2] == nullptr;
    }

    // template <typename Data>
    // Node &BinaryTreeVec<Data>::NodeVec::LeftChild() const
    // {
    // }

    // template <typename Data>
    // Node &BinaryTreeVec<Data>::NodeVec::RightChild() const
    // {
    // }

    /* ************************************************************************** */

}
