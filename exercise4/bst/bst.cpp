
namespace lasd
{

    /* ************************************************************************** */

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
