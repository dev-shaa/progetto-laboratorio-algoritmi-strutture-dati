namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    List<Data>::Node::Node(const Data &value)
    {
        this->value = value;
    }

    template <typename Data>
    List<Data>::Node::Node(Data &&value) noexcept
    {
        std::swap(this->value, value);
    }

    template <typename Data>
    List<Data>::Node::Node(const Node &other)
    {
        value = other.value;
        next = other.next;
    }

    template <typename Data>
    List<Data>::Node::Node(Node &&other) noexcept
    {
        std::swap(value, other.value);
        std::swap(value, other.next);
    }

    template <typename Data>
    typename List<Data>::Node &List<Data>::Node::operator=(const Node &other)
    {
        if (this != &other)
        {
            value = other.value;
            next = other.next;
        }

        return *this;
    }

    template <typename Data>
    typename List<Data>::Node &List<Data>::Node::operator=(Node &&other) noexcept
    {
        if (this != &other)
        {
            value = std::move(other.value);
            next = std::move(other.next);
        }

        return *this;
    }

    template <typename Data>
    bool List<Data>::Node::operator==(const Node &other) const noexcept
    {
        return value == other.value && *next == *(other.next);
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node &other) const noexcept
    {
        return !(*this == other);
    }

    /* ************************************************************************** */

    template <typename Data>
    List<Data>::List(const LinearContainer<Data> &linearContainer)
    {
        for (ulong i = 0; i < linearContainer.Size(); i++)
            InsertAtBack(linearContainer[i]);
    }

    template <typename Data>
    List<Data>::List(const List &other)
    {
        Node *current = other.start;

        while (current != nullptr)
        {
            InsertAtBack(current->value);
            current = current->next;
        }
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
        if (this != &other)
        {
            Clear();

            for (Node *temp = other.start; temp != nullptr; temp = temp->next)
                InsertAtBack(temp->value);
        }

        return *this;
    }

    template <typename Data>
    List<Data> &List<Data>::operator=(List &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(start, other.start);
            std::swap(end, other.end);
            std::swap(size, other.size);
        }

        return *this;
    }

    template <typename Data>
    bool List<Data>::operator==(const List &other) const noexcept
    {
        if (size != other.size)
            return false;

        Node *thisNode = start;
        Node *otherNode = other.start;

        while (thisNode != nullptr)
        {
            if (thisNode->value != otherNode->value)
                return false;

            thisNode = thisNode->next;
            otherNode = otherNode->next;
        }

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
        if (index >= size)
            throw std::out_of_range("index out of range");

        Node *current = start;

        for (ulong i = 0; i < index; i++)
            current = current->next;

        return current->value;
    }

    /* ************************************************************************** */

    template <typename Data>
    Data &List<Data>::Front() const
    {
        if (size == 0)
            throw std::length_error("Can't access front value because container is empty");

        return start->value;
    }

    template <typename Data>
    Data &List<Data>::Back() const
    {
        if (size == 0)
            throw std::length_error("Can't access back value because container is empty");

        return end->value;
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
    void List<Data>::InsertAtFront(const Data &value)
    {
        Node *newStart = new Node(value);
        newStart->next = start;
        start = newStart;

        if (start->next == nullptr)
            end = start;

        size++;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data &&value) noexcept
    {
        Node *newStart = new Node(std::move(value));
        newStart->next = start;
        start = newStart;

        if (start->next == nullptr)
            end = start;

        size++;
    }

    template <typename Data>
    void List<Data>::RemoveFromFront()
    {
        if (size == 0)
            throw std::length_error("can't remove front value because container is empty");

        Node *next = start->next;
        delete start;
        start = next;

        size--;
    }

    template <typename Data>
    Data &List<Data>::FrontNRemove()
    {
        if (size == 0)
            throw std::length_error("can't remove front value because container is empty");

        Data *value = new Data(std::move(Front()));

        Node *temp = start;
        start = start->next;
        delete temp;

        size--;

        return *value;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &value)
    {
        if (size == 0)
        {
            InsertAtFront(value);
        }
        else
        {
            Node *newNode = new Node(value);
            end->next = newNode;
            end = newNode;
            size++;
        }
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&value) noexcept
    {
        if (size == 0)
        {
            InsertAtFront(value);
        }
        else
        {
            Node *newNode = new Node(std::move(value));
            end->next = newNode;
            end = newNode;
            size++;
        }
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
            functor(current->value, par);
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
        functor(node->value, par);
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
            functor(current->value, foo, accumulator);
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
        functor(node->value, par, accumulator);
    }

    /* ************************************************************************** */

}
