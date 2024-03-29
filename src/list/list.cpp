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
            std::swap(value, other.value);
            std::swap(next, other.next);
        }

        return *this;
    }

    template <typename Data>
    bool List<Data>::Node::operator==(const Node &other) const noexcept
    {
        return value == other.value && ((next == nullptr && other.next == nullptr) || (next != nullptr && other.next != nullptr && *next == *(other.next)));
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
        for (Node *temp = other.start; temp != nullptr; temp = temp->next)
            InsertAtBack(temp->value);
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
        return Size() == other.Size() && ((start == nullptr && other.start == nullptr) || *start == *(other.start));
    }

    template <typename Data>
    bool List<Data>::operator!=(const List &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    Data &List<Data>::operator[](const ulong index) const
    {
        if (index >= Size())
            throw std::out_of_range("index out of bounds");

        Node *current = start;

        for (ulong i = 0; i < index; i++)
            current = current->next;

        return current->value;
    }

    /* ************************************************************************** */

    template <typename Data>
    Data &List<Data>::Front() const
    {
        if (Empty())
            throw std::length_error("can't access front value because list is empty");

        return start->value;
    }

    template <typename Data>
    Data &List<Data>::Back() const
    {
        if (Empty())
            throw std::length_error("can't access back value because list is empty");

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

    template <typename Data>
    inline bool List<Data>::Empty() const noexcept
    {
        return size == 0;
    }

    template <typename Data>
    inline ulong List<Data>::Size() const noexcept
    {
        return size;
    }

    /* ************************************************************************** */

    template <typename Data>
    void List<Data>::InsertNodeAtFront(Node *node) noexcept
    {
        node->next = start;
        start = node;

        if (start->next == nullptr)
            end = start;

        size++;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(const Data &value)
    {
        InsertNodeAtFront(new Node(value));
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data &&value) noexcept
    {
        InsertNodeAtFront(new Node(std::move(value)));
    }

    template <typename Data>
    void List<Data>::RemoveFromFront()
    {
        if (Empty())
            throw std::length_error("can't remove front value because container is empty");

        Node *next = start->next;
        delete start;
        start = next;

        size--;
    }

    template <typename Data>
    Data &List<Data>::FrontNRemove()
    {
        if (Empty())
            throw std::length_error("can't remove front value because container is empty");

        Data *value = new Data(std::move(Front()));

        Node *temp = start;
        start = start->next;
        delete temp;

        size--;

        return *value;
    }

    template <typename Data>
    void List<Data>::InsertNodeAtBack(Node *node) noexcept
    {
        end->next = node;
        end = node;
        size++;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &value)
    {
        if (Empty())
            InsertAtFront(value);
        else
            InsertNodeAtBack(new Node(value));
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&value) noexcept
    {
        if (Empty())
            InsertAtFront(std::move(value));
        else
            InsertNodeAtBack(new Node(std::move(value)));
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
        for (Node *temp = start; temp != nullptr; temp = temp->next)
            functor(temp->value, par);
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
        for (Node *temp = start; temp != nullptr; temp = temp->next)
            functor(temp->value, foo, accumulator);
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
