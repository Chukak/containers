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

using uint = unsigned int;

/*
 */
template<typename Num>
class sorted_list {
    
public:
    
    /*
     */
    sorted_list();
    
    /*
     */
    sorted_list(const sorted_list<Num> &orig);
    
    /*
     */
    sorted_list(std::initializer_list<Num> lst);
    
    /*
     */
    virtual ~sorted_list();
    
    /*
     */
    uint push(const Num &element);
    
    /*
     */
    Num pop_back();
    
    /*
     */
    Num pop_front();
    
    /*
     */
    Num remove(int pos);
    
    /*
     */
    Num front() const;
    
    /*
     */
    Num back() const ;
    
    /*
     */
    bool is_reversed() const { return reversed; }
    
    /*
     */
    bool is_empty() const { return empty; }
    
    /*
     */
    void reverse();
    
    /*
     */
    uint count() const { return _count; }
    
    /*
     */
    void clear();
    
    /*
     */
    Num at(int pos) const;
    
    /*
     */
    Num operator[](int pos) const;
    
private:
    
    /*
     */
    Num undefined_behavior() const { return Num(); };
    
    /*
     */
    bool is_out_of_range(int pos) const 
    { 
        return (pos < 0 || static_cast<uint>(pos) > _count) 
                || !(_count);
    }
    
    /*
     */
    struct Node {
        friend class sorted_list<Num>;
        
        Num value;
    private:
        Node *next;
        Node *prev;
        
        Node(const Num &e, Node *n, Node *p) : value(e), next(n), prev(p) {}
    };
    
    Node *_front;
    Node *_back;
    uint _count;
    bool empty;
    bool reversed;
    
private:
    
    /*
     */
    enum index {
        FIRST,
        LAST,
        MIDDLE
    };
    
    /*
     */
    bool cmp_operator(Node *head, Num element, index ind = index::MIDDLE)
    {
        if (ind == index::LAST) {
            return reversed ? _back->value > element : _back->value < element; 
        } else if (ind == index::FIRST){
            return reversed ? _front->value < element : _front->value > element;
        } else {
            return reversed ? greater(head, element) : less(head, element); 
        }
    }
    
    /*
     */
    bool less(Node *head, Num element) 
    {
        return (head->value <= element && 
                head->next && 
                head->next->value >= element);
    }
    
    /*
     */
    bool greater(Node *head, Num element)
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
    class iterator : public std::iterator<std::forward_iterator_tag, Num> {
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
        typedef std::forward_iterator_tag iterator_category;
        
        /*
         * A constructor.
         */
        iterator() : m_node(nullptr), _end(nullptr) {}
        
        /*
         * The prefix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++() 
        {
            m_node = m_node->next;
            return *this;
        }
        
        /*
         * The postfix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++(int j) 
        {
            m_node = m_node->next;
            return *this;
        }
        
        /*
         * The prefix operator `--`.
         * Reduces the pointer and returns it. 
         */
        iterator& operator--() 
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
        iterator& operator--(int j) 
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
        Num& operator*() const 
        {
            return m_node->value;
        }
        
        /*
         * The operator `->`.
         * Returns a pointer to the Node.
         */
        Node* operator->() const 
        {
            return m_node;
        }
        
        /*
         * The operator `!=`.
         * Compares two iterators. Returns `true` if 
         * iterators are not the same. Otherwise returns `false`.
         */
        bool operator!=(const iterator& rhs) const 
        { 
            return m_node != rhs.m_node;
        }
        
        /*
         * The operator `!=`.
         * Returns `true` if the current iterator and `nullptr`
         * are the same. Otherwise returns `false`.
         */
        bool operator!=(std::nullptr_t) const 
        { 
            return m_node != nullptr;
        }
        
        /*
         * The operator `==`.
         * Compares two iterators. Returns `true` if 
         * iterators are the same. Otherwise returns `false`.
         */
        bool operator==(const iterator& rhs) const 
        { 
            return m_node == rhs.m_node;
        }
        
        /*
         * The operator `==`.
         * Returns `true` if the current iterator and `nullptr`
         * are the same. Otherwise returns `false`.
         */
        bool operator==(std::nullptr_t) const 
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
    iterator begin() const { return iterator(_front, _back); }
    
    /*
     * Returns the iterator to the end of the queue. 
     * The iterator points to the element after the 
     * last element from the queue.
     */
    iterator end() const 
    { 
        return _back ? iterator(_back->next, _back) : iterator(_back, _back); 
    }
};

/*
 */
template<typename Num>
sorted_list<Num>::sorted_list()
{
    _front = NULL;
    _back = NULL;
    _count = 0;
    empty = true;
    reversed = false;
}

/*
 */
template<typename Num>
sorted_list<Num>::sorted_list(const sorted_list<Num>& orig) :
    _front(NULL),
    _back(NULL),
    _count(orig._count),
    empty(false),
    reversed(false)
{
    if (orig.empty) {
        empty = true;
        return ;
    }
    Node *t = orig._front;
    _front = new Node(t->value, NULL, NULL);
    _back = _front;
    t = t->next;
    while (t) {
        Node *new_node = new Node(t->value, NULL, _back);
        _back->next = new_node;
        _back = new_node;
        t = t->next;
    }
}

/*
 */
template<typename Num>
sorted_list<Num>::sorted_list(std::initializer_list<Num> lst) :
    _front(NULL),
    _back(NULL),
    _count(0),
    empty(true),
    reversed(false)
{
    for (auto element : lst) {
        push(element);
    }
}

/*
 */
template<typename Num>
sorted_list<Num>::~sorted_list()
{
    while (_front) {
        Node *old = _front;
        _front = _front->next;
        delete old;
    }
}

/*
 */
template<typename Num>
uint sorted_list<Num>::push(const Num& element)
{
    uint pos = 0;
    if (!empty) {
        if (cmp_operator(NULL, element, index::FIRST)) {
            Node *new_node = new Node(element, _front, NULL);
            _front->prev = new_node;
            _front = new_node;
        } else if (cmp_operator(NULL, element, index::LAST)) {
            Node *new_node = new Node(element, NULL, _back);
            _back->next = new_node;
            _back = new_node;
        } else {
            Node *head = _front;
            while (head && pos <= _count) {
                if (cmp_operator(head, element)) {
                    Node *new_node = new Node(element, head->next, head);
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
 */
template<typename Num>
Num sorted_list<Num>::pop_back()
{
    if (!empty) {
        Num value;
        Node *temp = _back;
        if (_back == _front) {
            if (_back) {
                value = _back->value;
            }
            _back = NULL;
            delete temp;
            _front = NULL;
        } else {
            value = _back->value;
            _back->prev->next = NULL;
            _back = _back->prev; 
            delete temp; 
        }
        _count--;
        empty = _count == 0 ? true : false;
        return value;
    }
    return undefined_behavior();
}

/*
 */
template<typename Num>
Num sorted_list<Num>::pop_front()
{
    if (!empty) {
        Num value;
        Node *temp = _front;
        if (_front == _back) {
            if (_front) {
                value = _back->value;
            }
            _front = NULL;
            delete temp;
            temp = _back;
            _back = NULL;
        } else {
            value = _front->value;
            _front->next->prev = NULL;
            _front = _front->next; 
            delete temp; 
        }
        _count--;
        empty = _count == 0 ? true : false;
        return value;
    }
    return undefined_behavior();
}

/*
 */
template<typename Num>
Num sorted_list<Num>::remove(int pos)
{
    
    if (is_out_of_range(pos)) { 
        throw std::out_of_range("Error: list index out of range.");
    }
    Node *head = _front;
    while (head && pos--) {
        head = head->next;
    }
    Node *old = head;
    Num value = head->value;
    if (head->prev) {
        head->prev->next = head->next; 
    } else {
        _front = head->next;
    }
    if (head->next) {
        head->next->prev = head->prev; 
    } else {
        _back = head->prev;
    }
    delete old;
    _count--;
    return value; 
}

/*
 */
template<typename Num>
Num sorted_list<Num>::front() const
{
    return _front ? _front->value : undefined_behavior();
}

/*
 */
template<typename Num>
Num sorted_list<Num>::back() const
{
    return _back ? _back->value : undefined_behavior();
}

/*
 */
template<typename Num>
void sorted_list<Num>::reverse()
{
    Node *t = _back;
    Node *old = _back;
    _front = new Node(t->value, NULL, NULL);
    delete old;
    _back = _front;
    t = t->prev;
    while (t) {
        Node *new_node = new Node(t->value, NULL, _back);
        old = t;
        _back->next = new_node;
        _back = new_node;
        t = t->prev;
        delete old;
    }
    reversed = reversed ? false : true;
}

/*
 */
template<typename Num>
void sorted_list<Num>::clear()
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
 */
template<typename Num>
Num sorted_list<Num>::at(int pos) const
{
    if (is_out_of_range(pos)) {
        throw std::out_of_range("Error: list index out of range.");
    }
    Node *head = _front;
    while (head && pos--) {
        head = head->next;
    }
    return head->value;
 }

/*
 */
template<typename Num>
Num sorted_list<Num>::operator[](int pos) const
{
    Node *head = _front;
    while (head && pos--) {
        head = head->next;
    }
    return pos <= 0 ? head->value : undefined_behavior();
}

#endif /* __cplusplus */

#endif /* SORTED_LIST_H */
