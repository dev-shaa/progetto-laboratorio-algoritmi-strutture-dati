namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    List<Data>::Node::Node(Data &item, Node *next)
    {
        this->item = item;
        this->next = next;
    }

    template <typename Data>
    bool List<Data>::Node::operator==(const Node &other) const
    {
        return item == other.item && next == other.next;
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node &other) const
    {
        return !(*this == other);
    }

    /* ************************************************************************** */

    template <typename Data>
    List<Data>::List(const LinearContainer<Data> &linearContainer)
    {
        for (ulong i = linearContainer.Size() - 1; i >= 0; i--)
            InsertAtFront(linearContainer[i]);
    }

    template <typename Data>
    List<Data>::List(const List &list)
    {
        // TODO: implementa
    }

    template <typename Data>
    List<Data>::List(List &&other) noexcept
    {
        std::swap(start, other.start);
        std::swap(end, other.end);
        std::swap(size, other.size);
    }

    template <typename Data>
    List<Data>::~List()
    {
        Clear();
    }

    /* ************************************************************************** */

    template <typename Data>
    List<Data> &List<Data>::operator=(const List &other)
    {
        // TODO: copy

        return *this;
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(List &&other) noexcept
    {
        std::swap(start, other.start);
        std::swap(end, other.end);
        std::swap(size, other.size);

        return *this;
    }

    template <typename Data>
    bool List<Data>::operator==(const List &other) const noexcept
    {
        // TODO: implementa

        if (size != other.Size())
            return false;

        // Node *thisNode;
        // Node *otherNode;

        // while (thisNode != nullptr)
        // {
        //     /* code */
        // }

        return true;
    }

    template <typename Data>
    bool List<Data>::operator!=(const List &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &List<Data>::operator[](const ulong index) const
    {
        if (index > size)
            throw std::out_of_range("index out of range");

        Node *current = start;

        for (ulong i = 0; i < index; i++)
            current = current->next;

        return current->item;
    }

    /* ************************************************************************** */

    template <typename Data>
    Data &List<Data>::Front() const
    {
        if (Container::Empty())
            throw std::length_error("Can't access front item because container is empty");

        return start->item;
    }

    template <typename Data>
    Data &List<Data>::Back() const
    {
        if (Container::Empty())
            throw std::length_error("Can't access back item because container is empty");

        return end->item;
    }

    template <typename Data>
    void List<Data>::Clear()
    {
        Node *next;

        while (start != nullptr)
        {
            next = start->next;
            delete start;
            start = next;
        }

        end = nullptr;
        size = 0;
    }

    /* ************************************************************************** */

    template <typename Data>
    void List<Data>::InsertAtFront(Data item)
    {
        // TODO: copy
        start = new Node(item, start);
        size++;
    }

    // template <typename Data>
    // void List<Data>::InsertAtFront(Data &item)
    // {
    //     // TODO: move
    // }

    template <typename Data>
    void List<Data>::RemoveFromFront()
    {
        if (Container::Empty())
            throw std::length_error("can't remove front item because container is empty");

        Node *next = start->next;
        delete start;
        start = next;
    }

    template <typename Data>
    Data &List<Data>::FrontNRemove()
    {
        if (Container::Empty())
            throw std::length_error("can't remove front item because container is empty");

        Node *temp = start;
        Data &item = start->item;

        start = start->next;
        delete temp;

        return item;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &item)
    {
        Node *newEnd = new Node(item, nullptr);
        end->next = newEnd;
        end = newEnd;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data item)
    {
        if (Container::Empty())
            InsertAtFront(item);

        size++;
    }

    /* ************************************************************************** */

    template <typename Data>
    void List<Data>::Map(MapFunctor functor, void *par)
    {
        MapPreOrder(functor, par);
    }

    template <typename Data>
    void List<Data>::MapPreOrder(MapFunctor functor, void *par)
    {
        Node *current = start;

        while (current != nullptr)
        {
            functor(current->item, par);
            current = current->next;
        }
    }

    template <typename Data>
    void List<Data>::MapPostOrder(MapFunctor functor, void *par)
    {
        AuxMapPostOrder(functor, par, start);
    }

    template <typename Data>
    void List<Data>::AuxMapPostOrder(MapFunctor functor, void *par, Node *node)
    {
        if (node == nullptr)
            return;

        AuxMapPostOrder(functor, par, node->next);
        functor(node->item, par);
    }

    /* ************************************************************************** */

    template <typename Data>
    void List<Data>::Fold(FoldFunctor functor, const void *foo, void *accumulator) const
    {
        FoldPreOrder(functor, foo, accumulator);
    }

    template <typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor functor, const void *foo, void *accumulator) const
    {
        Node *current = start;

        while (current != nullptr)
        {
            functor(current->item, foo, accumulator);
            current = current->next;
        }
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(FoldFunctor functor, const void *foo, void *accumulator) const
    {
        AuxFoldPostOrder(functor, foo, accumulator, start);
    }

    template <typename Data>
    void List<Data>::AuxFoldPostOrder(FoldFunctor functor, const void *par, void *accumulator, Node *node) const
    {
        if (node == nullptr)
            return;

        AuxFoldPostOrder(functor, par, accumulator, node->next);
        functor(node->item, par, accumulator);
    }

    /* ************************************************************************** */

}
