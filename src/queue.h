#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#endif
#endif

#ifdef __cplusplus
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <memory>

using uint = unsigned int;

/*
 * The `Queue` class.
 * The queue is the structure "First-In-First-Out". 
 */
template<typename Elem>
class Queue {
    /*
     * Sets the friend function for the overloaded operator `<<`.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream, const Queue<T>& q);
    
public:
    
    /*
     * Constructor.
     */
    Queue();
    
    /*
     * Copy constructor.
     * @param orig - another `Queue` class.
     */
    Queue(const Queue<Elem>& orig);
    
    /*
     * The operator `=`.
     */
    Queue<Elem>& operator=(const Queue<Elem>& orig);
    
    /*
     * Move constructor.
     */
    Queue(Queue<Elem> &&orig);
    
    /*
     * Constructor, for the style `Queue q = {1, 2, 3}`.
     */
    explicit Queue(std::initializer_list<Elem> lst);
    
    /*
     * Destructor.
     */
    virtual ~Queue();
    
    /*
     * The `enqueue` function.
     * Inserts an element into the queue.
     * @param element - an element.
     */
    void enqueue(const Elem &element);
    
    /*
     * The `dequeue` funciton.
     * Removes the first element of the queue and returns it. 
     */
    Elem dequeue() noexcept;
    
    /*
     * Returns the number of elements.
     */
    uint count() const noexcept { return _count; };
    
    /*
     * Returns the first element of the queue.
     */
    Elem front() const noexcept;
    /*
     * Returns the last element of the queue.
     */
    Elem back() const noexcept;
    
    /*
     * Returns `true` if the queue is empty, otherwise returns `false`. 
     */
    bool is_empty() const noexcept { return empty; }
    
    /*
     * The `clear` function.
     * Clears the queue.
     */
    void clear() noexcept;
private:
    
    /*
     * A linked list structure.
     * Used to represent elements in memory.
     */
    struct Node {
        friend class Queue<Elem>;
        
        friend class iterator;
        
        template<typename T>
        friend std::ostream& operator<<(std::ostream& stream, const Queue<T>& q);
        
        Elem value; // a value.
    private:
        std::shared_ptr<Node> next; // a pointer to the next `Node` structure.

        /*
         * Constructor.
         */
        Node(const Elem &v, std::shared_ptr<Node> n) : value(v), next(n) {}
    };
    
    using sptr = std::shared_ptr<Node>;
    
    /*
     * Pseudonym for code: `std::make_shared<Node>(Node(...))`.
     */
    template<typename... Args>
    auto make_sptr(Args&&... args) 
    -> decltype(std::make_shared<Node>(std::forward<Args>(args)...))
    {
        return std::make_shared<Node>(std::forward<Args>(args)...);
    }
    
    sptr _front; // a pointer to the first element.
    sptr _back; // a pointer to the last element.
    uint _count; // the numbers of elements.
    bool empty;
    
public:
    class iterator;
    
    /*
     * The `iterator` class.
     * Implements the iterator for the queue.
     * The iterator is `forward_iterator`.
     */
    class iterator : public std::iterator<std::forward_iterator_tag, Elem> {
        
        friend class Queue<Elem>;
        
    private:
        /*
         * Constructor.
         */
        explicit iterator(sptr node) : m_node(node) {}
        
    public:
        // value type.
        typedef Elem value_type;
        // iterator category
        typedef std::forward_iterator_tag iterator_category;
        
        /*
         * Constructor.
         */
        iterator() : m_node(0) {}
        
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
        iterator operator++(int j) noexcept
        {
            m_node = m_node->next;
            return *this;
        }
        
        /*
         * The operator `*`.
         * Returns a value from the pointer.
         */
        Elem& operator*() const noexcept
        {
            return m_node->value;
        }
        
        /*
         * The operator `->`.
         * Returns a pointer to the Node.
         */
        Node* operator->() const noexcept
        {
            return m_node.get();
        }
        
        /*
         * The operator `!=`.
         * Compares two iterators. Returns `true` if 
         * iterators aren`t the same. Otherwise returns `false`.
         */
        bool operator!=(const iterator& rhs) const noexcept
        { 
            return m_node != rhs.m_node;
        }
        
        /*
         * The operator `!=`.
         * Returns `true` if the current iterator and `nullptr`
         * aren`t the same. Otherwise returns `false`.
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
        sptr m_node; // a pointer to a Node.
    };
    
    /*
     * Returns the iterator to the first element of the queue.
     */
    iterator begin() const noexcept { return iterator(_front); }
    
    /*
     * Returns the iterator to the end of the queue. 
     * The iterator points to the element after the 
     * last element from the queue.
     */
    iterator end() const noexcept
    { 
        return _back ? iterator(_back->next) : iterator(_back); 
    }
};

/*
 * Costructor.
 * Creates a new `Queue` class. 
 */
template<typename Elem>
Queue<Elem>::Queue() :
    _front(sptr(NULL)),
    _back(sptr(NULL)),
    _count(0),
    empty(true)
{
}

/*
 * Constructor.
 * Creates a new `Queue` class from another `Queue` class.
 */
template<typename Elem>
Queue<Elem>::Queue(const Queue<Elem> &orig) : 
    _front(sptr(NULL)),
    _back(sptr(NULL)),
    _count(orig._count),
    empty(false)
{
    /*
     * If an original class is empty, returns from constructor.
     */
    if (orig.empty) {
        empty = true;
        return ; 
    }
    sptr t = orig._front; // copy a pointer to the first element.
    _front = make_sptr(Node(t->value, NULL)); // creates a new pointer.
    _back = _front;
    t = t->next; // gets a pointer to the next element.
    while (t) {
        sptr new_node = make_sptr(Node(t->value, NULL));
        _back->next = new_node;
        _back = new_node;
        t = t->next;
    } 
}

/*
 * The operator `=`.
 */
template<typename Elem>
Queue<Elem>& Queue<Elem>::operator=(const Queue<Elem>& orig)
{
    if (this == &orig) {
        return *this;
    }
    _front = orig._front;
    _back = orig._back;
    _count = orig._count;
    empty = orig.empty;
    return *this;
}

/*
 * Move constructor.
 */
template<typename Elem>
Queue<Elem>::Queue(Queue<Elem>&& orig) :
    _front(orig._front),
    _back(orig._back),
    _count(orig._count),
    empty(orig.empty)
{
    orig._front = sptr(NULL);
    orig._back = sptr(NULL);
    orig._count = 0;
    orig.empty = true;
}

/*
 * Constructor, for the style `Queue q = {1, 2, 3}`.
 */
template<typename Elem>
Queue<Elem>::Queue(std::initializer_list<Elem> lst) :
    _front(sptr(NULL)), 
    _back(sptr(NULL)),
    _count(0),
    empty(true)
{
    /*
     * Just copy all the elements.
     */
    for (auto element : lst) {
        enqueue(element);
    }
}

/*
 * Destructor.
 * Removes all the elements from memory.
 */
template<typename Elem>
Queue<Elem>::~Queue() 
{
    //sptr old = sptr(NULL);
    while (_front) {
        sptr old = _front; // a pointer to the current element.
        _front = _front->next; // a pointer to the next element.
        old.reset();
    }
}

/*
 * The `enqueue` function.
 * Inserts an element into the queue at the end.
 * Increases the size of the queue.
 */
template<typename Elem>
void Queue<Elem>::enqueue(const Elem &element) 
{
    sptr new_node = make_sptr(Node(element, NULL)); // a new pointer.
    if (empty) { 
        _front = new_node; 
        _back = new_node;
        empty = false;
    } else {
        _back->next = new_node; // sets the next element.
        _back = new_node; // sets the last element.
    }
    _count++;
}

/*
 * The `dequeue` function.
 * Removes the first element of the queue.
 * Reduces the size of the queue.
 * If the queue is empty, the result has an undefined behavior.
 */
template<typename Elem>
Elem Queue<Elem>::dequeue() noexcept
{
    //sptr old = NULL;
    Elem value; 
    if (!empty) {
        sptr old = _front;
        value = _front->value;
        _front = _front->next; 
        old.reset();
        _count--;
    }
    // checks if the queue is empty.
    empty = _count == 0 ? true : false; 
    return value;
}

/*
 * The `front` function.
 * Returns the first element of the queue.
 * If the queue is empty, the result has an undefined behavior.
 */
template<typename Elem>
Elem Queue<Elem>::front() const noexcept
{
    Elem value;
    if (_front) {
        value = _front->value;
    }
    return value;
}

/*
 * The `back` function.
 * Returns the last element from the queue.
 * If the queue is empty, the result has an undefined behavior.
 */
template<typename Elem>
Elem Queue<Elem>::back() const noexcept
{
    Elem value;
    if (_back) {
        value = _back->value;
    }
    return value;
}

/*
 * The `clear` function.
 * Clears the queue.
 */
template<typename Elem>
void Queue<Elem>::clear() noexcept
{
    while (_front) {
        sptr old = _front; // a pointer to the current element.
        _front = _front->next; // a pointer to the next element.
        old.reset();
    }
    _front = sptr(NULL);
    _back = sptr(NULL);
    empty = true;
    _count = 0;
}

/*
 * The overloaded `<<` operator for the queue.
 * Prints all the elements from the queue in the format: `(1, ...,100)`.
 * Returns ostream.
 */
template<typename Elem>
std::ostream& operator<<(std::ostream& stream, const Queue<Elem>& q)
{
    auto *t = q._front;
    stream << "(";
    while(t) {
        stream << t->value << ", ";
        t = t->next;
    }
    stream << "\b\b";
    stream << "";
    stream << ")";
    return stream;
}

#endif /* __cplusplus */

/*
 * A declaration the structure `queue` for C.
 */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
#ifndef NULL
#define NULL ((void *)0)
#endif
    
    typedef struct q_node q_node;
    
    /*
     * The node structure for the queue.
     */
    struct q_node {
        void *value; // a pointer to a value.
        q_node *next; // a pointer to the next node.
    };
    
    /*
     * The structure `queue`.
     * The queue is the structure "First-In-First-Out". 
     * 
     */
    typedef struct {
        q_node *_front; // a pointer to the first node.
        q_node *_back; // a pointer to the last node.
        uint count; 
        int empty;
    } queue;
    
    /*
     * The `q_create_queue` function.
     * Creates a queue and returns a pointer to it.
     */
    queue *q_create_queue(void);
    
    /*
     * The `q_enqueue` function.
     * Inserts an element into the queue.
     * Takes two arguments:
     * `q` - a pointer to the queue.
     * `element` - a pointer to the element.
     */
    void q_enqueue(queue *q, const void *element);
    /*
     * The `q_dequeue` function.
     * Removes the first element of the queue. 
     * Returns a pointer to the deleted element.
     * If the queue is empty, returns the `NULL` pointer.
     * Takes one argument:
     * `q` - a pointer to the queue.
     */
    void *q_dequeue(queue *q);
    
    /*
     * The `q_front` function.
     * Returns a pointer to the first element of the queue.
     * If the queue is empty, returns the `NULL` pointer.
     * Takes one argument:
     * `q` - a pointer to the queue.
     */
    void *q_front(queue *q);
    /*
     * The `q_back` function.
     * Returns a pointer to the last element of the queue.
     * If the queue is empty, returns the `NULL` pointer.
     * Takes one argument:
     * `q` - a pointer to the queue.
     */
    void *q_back(queue *q);
    
    /*
     * The `q_count` function.
     * Returns the size of the queue.
     * Takes one argument:
     * `q` - a pointer to the queue.
     * Use this function, if necessary.
     * or instead this function, use `queue->count`.
     */
    uint q_count(queue *q);
    
    /*
     * The `q_delete_queue` function.
     * Removes the queue from memory.
     * Takes one argument:
     * `q` - a pointer to the queue.
     */
    void q_delete_queue(queue *q);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUEUE_H */
