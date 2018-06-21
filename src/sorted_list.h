#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#endif
#endif

#ifdef __cplusplus
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <functional>

using uint = unsigned int;

/*
 * The `sorted_list` class.
 * Keeps elements in sort order.
 * For the order to be sorted, the class requires operators for elements:
 * 1) `<` - less.
 * 2) `>` - greater.
 * 3) `<=` - less or equal.
 * 4) `>=` - greater or equal.
 * 
 * By default, the `<` and `<=` operators are used to compare elements.
 * If the list is reverse, the `>` and `>=` operators are used.
 */
template<typename Num>
class sorted_list {
    
    using custom_func = std::function<bool(Num, Num, Num)>;
    
    /*
     * Sets the friend function for the overloaded operator `<<`.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream, 
            const sorted_list<T>& list);
    
public:
    
    /*
     * A constructor.
     * @param func - a custom function to compare elements.
     */
    sorted_list(const custom_func& func = nullptr); 
    
    /*
     * A constructor, creates the `sorted_list` class from another 
     * `sorted_list` class.
     * @param orig - a constant link to another `sorted_list` class.
     */
    sorted_list(const sorted_list<Num> &orig);
    
    /*
     * A constructor, for the style `sorted_list list = {3, 2, 1}`.
     * @param func - a custom function to compare elements.
     */
    sorted_list(std::initializer_list<Num> lst, 
            const custom_func& func = nullptr);
    
    /*
     * A destructor.
     */
    virtual ~sorted_list();
    
    /*
     * The `push` function.
     * Inserts an element to the list in a special position 
     * to save the list in sorted order.
     * Returns a position of this element.
     * @param element - a constant link to the value.
     */
    uint push(const Num &element);
    
    /*
     * The `pop_back` function.
     * Removes the last element from the list and returns it.
     */
    Num pop_back() noexcept;
    
    /*
     * The `pop_front` function.
     * Removes the first element from the list and returns it.
     */
    Num pop_front() noexcept;
    
    /*
     * The `remove` function.
     * Removes an element from a special position and returns it.
     * This function checks the range of the list. If the range
     * is invalid or the list is empty, raises the `out_of_range` error.
     * @param pos - a position from which the element will be deleted.
     */
    Num remove(int pos);
    
    /*
     * Returns the first element from the list.
     * If the list is empty, the result has undefined behavior.
     */
    Num front() const noexcept;
    
    /*
     * Returns the back element from the list.
     * If the list is empty, the result has undefined behavior.
     */
    Num back() const noexcept;
    
    /*
     * Returns `true` if the list is reverse, otherwise returns `false`.
     */
    bool is_reversed() const noexcept { return reversed; }
    
    /*
     * Returns `true` if the list is empty, otherwise returns `false`.
     */
    bool is_empty() const noexcept { return empty; }
    
    /*
     * The `reverse` function.
     * Changes the order of the list on reverse.
     * For example: `{1, 2, 3}` --> `{3, 2, 1}`.
     */
    void reverse() noexcept;
    
    /*
     * Returns the number of elements.
     */
    uint count() const noexcept { return _count; }
    
    /*
     * The `clear` function.
     * Clears the list.
     */
    void clear() noexcept;
    
    /*
     * The `at` function.
     * Returns an element from the position.
     * This function checks the range of the list. If the range
     * is invalid or the list is empty, raises the `out_of_range` error.
     * @param pos - a position.
     */
    Num at(int pos) const;
    
    /*
     * The overloaded operator `[]`.
     * Returns an element from the position.
     * This function does not checks the range of list. If the range
     * is invalid, the result has undefined behavior.
     * @param pos - a position.
     */
    Num operator[](int pos) const noexcept;
    
private:
    
    /*
     * Returns a result which has undefined behavior.
     */
    Num undefined_behavior() const noexcept { return Num(); };
    
    /*
     * Returns `true` if out of range, otherwise `false`.
     */
    bool is_out_of_range(int pos) const
    { 
        return (pos < 0 || static_cast<uint>(pos) > _count) 
                || !(_count);
    }
    
    /*
     * Calls the custom function for comparison elements.
     * Increments a position.
     * @param element - constant link to a value.
     * @param pos - a pointer to the position.
     * The custom function must get 3 arguments and must return true or false. 
     * Also, the custom function must have the operator `<=` or `>=` 
     * to compare a new element with the next element. 
     * Without this operator, the list can not work correctly.
     */
    void push_with_custom_func(const Num& element, uint *pos);
    
    /*
     * A linked list structure.
     * Used to represent elements in memory.
     */
    struct Node {
        friend class sorted_list<Num>;
        
        friend class iterator;
        
        template<typename T>
        friend std::ostream& operator<<(std::ostream& stream, 
        const sorted_list<T>& list);
        
        Num value; // a value.
    private:
        Node *next; // a pointer to the next node.
        Node *prev; // a pointer to the prev node.
        
        /*
         * A constructor.
         */
        Node(const Num &e, Node *n, Node *p) : value(e), next(n), prev(p) {}
    };
    
    Node *_front; // a pointer to the first element.
    Node *_back; // a pointer to the last element.
    uint _count; // the numbers of elements
    bool empty;
    bool reversed;
    custom_func cmp_func;
    
private:
    
    /*
     * Enumeration for selecting elements.
     * Used in the comparison function `cmp_operator`.
     */
    enum class index {
        FIRST, // the first element. 
        LAST, // any element between the first and last.
        MIDDLE // the last element.
    };
    
    /*
     * Comparison function.
     * Compares an element from a node with an element.
     * Used to sort elements in the list.
     * @param head - a node
     * @param element - an element
     * @param ind - a selected element, first, last, or middle.
     */
    bool cmp_operator(Node *head, Num element, 
            index ind = index::MIDDLE) const noexcept
    {
        if (ind == index::LAST) {
            // compares the last element.
            return reversed ? _back->value > element : _back->value < element; 
        } else if (ind == index::FIRST){
            // compares the first element.
            return reversed ? _front->value < element : _front->value > element;
        } else {
            // compares the middle element.
            // Calls the function `greater` if the list is reverse,
            // otherwise calls the function `less`.
            return reversed ? greater(head, element) : less(head, element); 
        }
    }
    
    /*
     * Comparison function.
     * Used when the order of the list is standard.
     * @param head - a node.
     * @param element - an element.
     */
    bool less(Node *head, Num element) const
    {
        return (head->value <= element && 
                head->next && 
                head->next->value >= element);
    }
    
    /*
     * Comparison function.
     * Used when the order of the list is standard.
     * @param head - a node.
     * @param element - an element.
     */
    bool greater(Node *head, Num element) const
    {
        return (head->value >= element && 
                head->next &&
                head->next->value <= element);
    }
    
public:    
    class iterator;
    
    /*
     * The `iterator` class.
     * Determines the iterator for the sorted list.
     */
    class iterator : public std::iterator<std::bidirectional_iterator_tag, Num> {
        /*
         * Sets the friend class.
         */
        friend class sorted_list<Num>;
        
    private:
        /*
         * A constructor.
         */
        iterator(Node *node, Node *end) : m_node(node), _end(end) {}
        
    public:
        // value type.
        typedef Num value_type;
        // iterator category
        typedef std::bidirectional_iterator_tag iterator_category;
        
        /*
         * A constructor.
         */
        iterator() : m_node(nullptr), _end(nullptr) {}
        
        /*
         * The prefix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++() noexcept
        {
            m_node = m_node->next;
            return *this;
        }
        
        /*
         * The postfix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++(int j) noexcept
        {
            m_node = m_node->next;
            return *this;
        }
        
        /*
         * The prefix operator `--`.
         * Reduces the pointer and returns it. 
         */
        iterator& operator--() noexcept
        {
            if (m_node == nullptr || 
                    m_node == NULL) {
                m_node = _end;
            } else {
                m_node = m_node->prev; 
            }
            return *this;
        }
        
        /*
         * The postfix operator `--`.
         * Reduces the pointer and returns it. 
         */
        iterator& operator--(int j) noexcept
        {
            if (m_node == nullptr || 
                    m_node == NULL) {
                m_node = _end;
            } else {
                m_node = m_node->prev;
            }
            return *this;
        }
        
        /*
         * The operator `*`.
         * Returns a value from the pointer.
         */
        Num& operator*() const noexcept
        {
            return m_node->value;
        }
        
        /*
         * The operator `->`.
         * Returns a pointer to the Node.
         */
        Node* operator->() const noexcept
        {
            return m_node;
        }
        
        /*
         * The operator `!=`.
         * Compares two iterators. Returns `true` if 
         * iterators are not the same. Otherwise returns `false`.
         */
        bool operator!=(const iterator& rhs) const noexcept
        { 
            return m_node != rhs.m_node;
        }
        
        /*
         * The operator `!=`.
         * Returns `true` if the current iterator and `nullptr`
         * are the same. Otherwise returns `false`.
         */
        bool operator!=(std::nullptr_t) const noexcept
        { 
            return m_node != nullptr;
        }
        
        /*
         * The operator `==`.
         * Compares two iterators. Returns `true` if 
         * iterators are the same. Otherwise returns `false`.
         */
        bool operator==(const iterator& rhs) const noexcept
        { 
            return m_node == rhs.m_node;
        }
        
        /*
         * The operator `==`.
         * Returns `true` if the current iterator and `nullptr`
         * are the same. Otherwise returns `false`.
         */
        bool operator==(std::nullptr_t) const noexcept
        { 
            return m_node == nullptr;
        }
        
    private:
        Node *m_node; // a pointer to a Node.
        Node *_end;
    };
    
    /*
     * Returns the iterator to the beginning of the queue.
     */
    iterator begin() const noexcept { return iterator(_front, _back); }
    
    /*
     * Returns the iterator to the end of the queue. 
     * The iterator points to the element after the 
     * last element from the queue.
     */
    iterator end() const noexcept
    { 
        return _back ? iterator(_back->next, _back) : iterator(_back, _back); 
    }
};

/*
 * A constructor.
 * Creates a new `sorted_list` class.
 */
template<typename Num>
sorted_list<Num>::sorted_list(const custom_func& func) :
            _front(NULL),
        _back(NULL),
        _count(0),
        empty(true),
        reversed(false),
        cmp_func(func)
{
}

/*
 * A constructor.
 * Creates a new `sorted_list` class from another `sorted_list` class.
 */
template<typename Num>
sorted_list<Num>::sorted_list(const sorted_list<Num>& orig) :
    _front(NULL),
    _back(NULL),
    _count(orig._count),
    empty(false),
    reversed(false)
{
    /*
     * If an original class is empty, returns from constructor.
     */
    if (orig.empty) {
        empty = true;
        return ;
    }
    Node *t = orig._front; // copy a pointer to the first element.
    _front = new Node(t->value, NULL, NULL); // creates a new pointer.
    _back = _front;
    t = t->next; // gets a pointer to the next element.
    while (t) {
        Node *new_node = new Node(t->value, NULL, _back);
        _back->next = new_node;
        _back = new_node;
        t = t->next;
    }
}

/*
 * A constructor for the style `sorted_list list = {3, 5, 1}`.
 */
template<typename Num>
sorted_list<Num>::sorted_list(std::initializer_list<Num> lst, 
        const custom_func& func) :
    _front(NULL),
    _back(NULL),
    _count(0),
    empty(true),
    reversed(false),
    cmp_func(func)
{
    /*
     * Just copy all the elements.
     */
    for (auto element : lst) {
        push(element);
    }
}

/*
 * A destructor.
 * Removes all the elements from memory.
 */
template<typename Num>
sorted_list<Num>::~sorted_list()
{
    while (_front) {
        Node *old = _front; // a pointer to the current element.
        _front = _front->next; // a pointer to the next element.
        delete old;
    }
}

/*
 * The `push` function.
 * Inserts an element to the list in a special position 
 * to save the list in sorted order.
 * Returns a position of this element.
 */
template<typename Num>
uint sorted_list<Num>::push(const Num& element)
{
    uint pos = 0;
    
    if (!empty) {
        if (cmp_func != nullptr) {
            push_with_custom_func(element, &pos);
            return pos;
        }
        /* 
         * Compare the first element from the list with a new element.
         * if a new element `<` (`>` if the list is reverse) 
         * than the first element, a new element inserts in the position `0`.
         */ 
        if (cmp_operator(NULL, element, index::FIRST)) {
            Node *new_node = new Node(element, _front, NULL);
            _front->prev = new_node; // sets the old first element.
            _front = new_node; // changes the first element.
        /* 
         * Compare the last element from the list with a new element.
         * if a new element `>` (`<` if the list is reverse) 
         * than the last element, a new element inserts in the last position.
         */
        } else if (cmp_operator(NULL, element, index::LAST)) {
            Node *new_node = new Node(element, NULL, _back);
            _back->next = new_node; // sets the old lst element.
            _back = new_node; // changes the last element.
            pos = _count - 1;
        } else {
            /* 
             * Compare all the elements from the list with a new element.
             * if a new element `<` (`>` if the list is reverse) 
             * than any element, a new element inserts in this position.
             */
            Node *head = _front;
            while (head && pos <= _count) {
                if (cmp_operator(head, element)) {
                    /*
                     * Creates a new node with arguments:
                     * 1) element - an element.
                     * 2) head->next - a pointer to the next node.
                     * 3) head - a pointer to the previous node.
                     */
                    Node *new_node = new Node(element, head->next, head);
                    /* 
                     * Changes the pointer to the previous node
                     * from the next element.
                     */
                    head->next->prev = new_node; 
                    head->next = new_node;
                    break;
                }
                head = head->next;
                pos++;
            } 
        }
    } else {
        Node *new_node = new Node(element, NULL, NULL);
        _front = new_node; 
        _back = new_node;
        empty = false;
    }
    _count++;
    return pos;
}

/*
 * Calls the user function for comparison elements.
 * Increments a position. 
 * A custom function must have 3 arguments.
 */
template<typename Num>
void sorted_list<Num>::push_with_custom_func(const Num& element, uint *pos)
{
    /* 
     * Compare the first element from the list with a new element.
     * Call the custom function with 3 parameters: 
     * `func(a new element, the first element, the first element)`.
     * If a new element more than the first element, 
     * a new element inserts in the position `0`.
     */ 
    if (cmp_func(element, _front->value, _front->value)) {
        Node *new_node = new Node(element, _front, NULL);
        _front->prev = new_node;
        _front = new_node;
    /* 
     * Compare the last element from the list with a new element.
     * Call the custom function with 3 parameters: 
     * `func(the last element, a new element, a new element)`.
     */
    } else if(cmp_func(_back->value, element, element)) {
        Node *new_node = new Node(element, NULL, _back);
        _back->next = new_node;
        _back = new_node;
        *pos = _count - 1;
    } else {
        /* 
         * Compare all the elements from the list with a new element.
         * A new element must be more/(less/equal) than the prevoius element, and
         * less/(more/equal) than the next element. For example: 2 < 3 <= 4, 
         * or in the reversed list: 4 > 3 >= 2.
         * Call the custom function with 3 parameters: 
         * `func(the previous element, a new element, a next element)`.
         */
        Node *head = _front;
        while (head && head->next &&
                *pos <= _count) {
            if (cmp_func(head->value, element, head->next->value)) {
                Node *new_node = new Node(element, head->next, head);
                head->next->prev = new_node;
                head->next = new_node;
                break;
            }
            head = head->next;
            (*pos)++;
        }
    }
    _count++;
}

/*
 * The `pop_back` function.
 * Removes the last element from the list and returns it.
 * If the list is empty, the result has undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::pop_back() noexcept
{
    if (!empty) {
        Num value;
        Node *temp = _back;
        if (_back == _front) {
            // Gets a value from the last element.
            if (_back) {
                value = _back->value;
            }
            // Removes the element from memory.
            _back = NULL;
            delete temp;
            _front = NULL;
        } else {
            value = _back->value;
            /* 
             * Changes the pointer to the next node
             * from the previous element.
             */ 
            _back->prev->next = NULL;
            _back = _back->prev; 
            delete temp; 
        }
        _count--;
        empty = _count == 0 ? true : false;
        return value;
    }
    // Returns it, is the list is empty.
    return undefined_behavior();
}

/*
 * The `pop_front` function.
 * Removes the first element from the list and returns it.
 * If the list is empty, the result has undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::pop_front() noexcept
{
    if (!empty) {
        Num value;
        Node *temp = _front;
        if (_front == _back) {
            // Gets a value from the last element.
            if (_front) {
                value = _back->value;
            }
            // Removes the element from memory.
            _front = NULL;
            delete temp;
            temp = _back;
            _back = NULL;
        } else {
            value = _front->value;
            /* 
             * Changes the pointer to the previous node
             * from the next element.
             */
            _front->next->prev = NULL;
            _front = _front->next; 
            delete temp; 
        }
        _count--;
        empty = _count == 0 ? true : false;
        return value;
    }
    // Returns it, is the list is empty.
    return undefined_behavior();
}

/*
 * The `remove` function.
 * Removes an element from a special position and returns it.
 * This function checks the range of the list. If the range
 * is invalid or the list is empty, raises the `out_of_range` error.
 */
template<typename Num>
Num sorted_list<Num>::remove(int pos)
{
    // Checks the range of the list.
    // If the range is invalid, raises the `out_of_range` error.
    if (is_out_of_range(pos)) { 
        throw std::out_of_range("Error: list index out of range.");
    }
    Node *head = _front;
    // Gets element from the position.
    while (head && pos--) {
        head = head->next;
    }
    Node *old = head;
    // Gets a value from the element.
    Num value = head->value;
    // Changes the pointer to the next element from the previous element.
    if (head->prev) {
        head->prev->next = head->next; 
    // if the list has only one element.
    } else {
        _front = head->next;
    }
    // Changes the pointer to the previous element from the next element.
    if (head->next) {
        head->next->prev = head->prev; 
    // if the list has only one element.
    } else {
        _back = head->prev;
    }
    delete old;
    _count--;
    return value; 
}

/*
 * Returns the first element from the list.
 * If the list is empty, the result has undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::front() const noexcept
{
    return _front ? _front->value : undefined_behavior();
}

/*
 * Returns the last element from the list.
 * If the list is empty, the result has undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::back() const noexcept
{
    return _back ? _back->value : undefined_behavior();
}

/*
 * The `reverse` function.
 * Changes the order of the list on reverse.
 */
template<typename Num>
void sorted_list<Num>::reverse() noexcept
{
    if (!empty) {
        Node *t = _back;
        Node *old = _back;
        // Creates the first element from the last element.
        _front = new Node(t->value, NULL, NULL);
        // Removes the last element.
        delete old;
        _back = _front;
        // Sets the previous element.
        t = t->prev;
        while (t) {
            Node *new_node = new Node(t->value, NULL, _back);
            old = t;
            _back->next = new_node;
            // Sets the last element.
            _back = new_node;
            t = t->prev;
            delete old;
        }
    }
    reversed = reversed ? false : true;
}

/*
 * The `clear` function.
 * Clears the list.
 */
template<typename Num>
void sorted_list<Num>::clear() noexcept
{
    while (_front) {
        Node *old = _front;
        _front = _front->next;
        delete old;
    }
    _front = NULL;
    _back = NULL;
    _count = 0;
    empty = true;
    reversed = false;
}

/*
 * The `at` function.
 * Returns an element from the position.
 * This function checks the range of the list. If the range
 * is invalid or the list is empty, raises the `out_of_range` error.
 */
template<typename Num>
Num sorted_list<Num>::at(int pos) const
{
    // Checks the range of the list.
    // If the range is invalid, raises the `out_of_range` error.
    if (is_out_of_range(pos)) {
        throw std::out_of_range("Error: list index out of range.");
    }
    Node *head = _front;
    // Gets element from the position.
    while (head && pos--) {
        head = head->next;
    }
    return head->value;
 }

/*
 * The overloaded operator `[]`.
 * Returns an element from the position.
 * This function does not checks the range of list. If the range
 * is invalid, the result has undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::operator[](int pos) const noexcept
{
    
    Node *head = _front;
    while (head && pos--) {
        head = head->next;
    }
    return pos <= 0 ? head->value : undefined_behavior();
}

/*
 * The overloaded `<<` operator for the sorted list.
 * Prints all elements from the sorted list in the format: `[1, ...,100]`.
 * Returns ostream.
 */
template<typename Num>
std::ostream& operator<<(std::ostream& stream, const sorted_list<Num>& list)
{
    auto *t = list._front;
    stream << "[";
    while(t) {
        stream << t->value << ", ";
        t = t->next;
    }
    stream << "\b\b";
    stream << "";
    stream << "]";
    return stream;
}

#endif /* __cplusplus */

#endif /* SORTED_LIST_H */
