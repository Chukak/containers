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
    Num remove(uint pos);
    
    /*
     */
    Num front();
    
    /*
     */
    Num back();
    
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
    Num at(uint pos);
    
    /*
     */
    Num operator[](uint pos);
    
private:
    
    /*
     */
    struct Node {
        friend class sorted_list<Num>;
        
        Num value;
    private:
        Node *next;
        Node *prev;
        
        Node(const Num& element, Node *n, Node *p) {}
    };
    
    Node *_front;
    Node *_back;
    uint _count;
    bool empty;
    bool reversed;

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
            }
            m_node = m_node->prev;
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
            }
            m_node = m_node->prev;
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
    iterator begin() const { return iterator(_front); }
    
    /*
     * Returns the iterator to the end of the queue. 
     * The iterator points to the element after the 
     * last element from the queue.
     */
    iterator end() const 
    { 
        return _back ? iterator(_back->next) : iterator(_back); 
    }
};

#endif /* SORTED_LIST_H */

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
    /* ... */
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
        /* ... */
    }
}

/*
 */
template<typename Num>
sorted_list<Num>::~sorted_list()
{
    /* .. */
}

/*
 */
template<typename Num>
uint sorted_list::push(const Num& element)
{
    /* ... */
}

/*
 */
template<typename Num>
Num sorted_list::pop_back()
{
    /* ... */
}

/*
 */
template<typename Num>
Num sorted_list::pop_front()
{
    /* ... */
}

/*
 */
template<typename Num>
Num sorted_list::remove(uint pos)
{
    /* ... */
}

/*
 */
template<typename Num>
Num sorted_list::front()
{
    /* ... */
}

/*
 */
template<typename Num>
Num sorted_list::back()
{
    /* ... */
}

/*
 */
template<typename Num>
void sorted_list::reverse()
{
    /* ... */
}

/*
 */
template<typename Num>
void sorted_list::clear()
{
    /* ... */
}

/*
 */
template<typename Num>
Num sorted_list::at(uint pos)
{
    /* ... */
}

/*
 */
template<typename Num>
Num sorted_list::operator[](uint pos)
{
    /* ... */
}

#endif /* __cplusplus */

#endif /* SORTED_LIST_H */
