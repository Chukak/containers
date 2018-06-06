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
     * A constructor.
     */
    Queue();
    /*
     * A constructor, creates the `sueue` class from another `queue` class.
     * @param orig - a constant link to another `Stack` class.
     */
    Queue(const Queue<Elem> &orig);
    /*
     * A constructor, for the style `Queue q = {1, 2, 3}`.
     */
    Queue(std::initializer_list<Elem> lst);
    /*
     * A destructor.
     */
    virtual ~Queue();
    
    /*
     * An `enqueue` function.
     * Puts an element in the queue.
     * @param element - a constant link to the value.
     */
    void enqueue(const Elem &element);
    /*
     * A `dequeue` funciton.
     * Removes the first element from the queue. 
     */
    Elem dequeue();
    /*
     * Returns the number of elements.
     */
    unsigned int count() const { return qnum_of_elements; };
    
    /*
     * Returns the first element from the queue.
     */
    Elem front() const;
    /*
     * Returns the last element from the queue.
     */
    Elem back() const;
    
    /*
     * Returns `true` if the queue is empty, otherwise returns `false`. 
     */
    bool empty() const { return qempty; }
private:
    /*
     * A linked list structure.
     * Used to represent elements in memory.
     */
    struct Node {
        Elem value; // a value.
        Node *next; // a pointer to the next `Node` structure.

        /*
         * A constructor.
         */
        Node(const Elem &v, Node *n) : value(v), next(n) {}
    };
    
    Node *qfront; // a pointer to the first element.
    Node *qback; // a pointer to the last element.
    unsigned int qnum_of_elements; // the numbers of elements.
    bool qempty;
    
public:
    
    /*
     * The `iterator` class.
     * Determines the iterator for the `Queue` class.
     */
    class iterator : public std::iterator<std::forward_iterator_tag, Elem> {
        /*
         * Sets the friend class.
         */
        friend class Queue<Elem>;
        
    private:
        /*
         * A constructor.
         */
        iterator(Node *node) : m_node(node) {}
        
    public:
        // value type.
        typedef Elem value_type;
        // iterator category
        typedef std::forward_iterator_tag iterator_category;
        
        /*
         * A constructor.
         */
        iterator() : m_node(0) {}
        
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
         * The operator `*`.
         * Returns a value from the pointer.
         */
        Elem& operator*() const 
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
         * The operator `==`.
         * Compares two iterators. Returns `true` if 
         * iterators are the same. Otherwise returns `false`.
         */
        bool operator==(const iterator& rhs) const 
        { 
            return m_node == rhs.m_node;
        }
        
    private:
        Node *m_node; // a pointer to a Node.
    };
    
    /*
     * Returns the iterator to the beginning of the queue.
     */
    iterator begin() const { return iterator(qfront); }
    
    /*
     * Returns the iterator to the end of the queue. 
     * The iterator points to the element after the 
     * last element from the queue.
     */
    iterator end() const { return iterator(qback->next); }
};

/*
 * A costructor.
 * Creates a new `Queue` class. 
 */
template<typename Elem>
Queue<Elem>::Queue()
{
    qfront = NULL; // a pointer to the first element
    qback = NULL; // a pointer to the last element
    qnum_of_elements = 0; // the numbers of elements
    qempty = true; 
}

/*
 * A constructor.
 * Creates a new `Queue` class from the another `Queue` class.
 */
template<typename Elem>
Queue<Elem>::Queue(const Queue<Elem> &orig) : 
    qfront(NULL),
    qback(NULL),
    qnum_of_elements(orig.qnum_of_elements),
    qempty(false)
{
    /*
     * If an original class is empty, returns from constructor.
     */
    if (orig.empty()) {
        qempty = true;
        return ; 
    }
    Node *t = orig.qfront; // copy a pointer to the first element.
    qfront = new Node(t->value, NULL); // creates a new pointer.
    qback = qfront;
    t = t->next; // gets a pointer to the next element.
    while (t) {
        Node *new_node = new Node(t->value, NULL);
        qback->next = new_node;
        qback = new_node;
        t = t->next;
    } 
}

/*
 * A constructor, for the style `Queue q = {1, 2, 3}`.
 */
template<typename Elem>
Queue<Elem>::Queue(std::initializer_list<Elem> lst) :
    qfront(NULL), 
    qback(NULL),
    qnum_of_elements(0),
    qempty(true)
{
    /*
     * Just copy all the elements.
     */
    for (auto element : lst) {
        enqueue(element);
    }
}

/*
 * A destructor.
 * Removes all the elements from memory.
 */
template<typename Elem>
Queue<Elem>::~Queue() 
{
    Node *old = NULL;
    while (qfront) {
        old = qfront; // a pointer to a current element.
        qfront = qfront->next; // a pointer to the next element.
        delete old;
    }
}

/*
 * An `enqueue` function.
 * Puts an element in the queue at the end.
 * Increases the size of the queue.
 */
template<typename Elem>
void Queue<Elem>::enqueue(const Elem &element) 
{
    Node *new_node = new Node(element, NULL); // a new pointer to an element.
    if (qempty) { 
        qfront = new_node; // front == back.
        qback = new_node;
        qempty = false;
    } else {
        qback->next = new_node; // sets the next element.
        qback = new_node; // sets the last element.
    }
    qnum_of_elements++;
}

/*
 * A `dequeue` function.
 * Removes the first element from the queue.
 * Reduces the size of the queue.
 * If the queue is empty, the result has undefined behavior.
 */
template<typename Elem>
Elem Queue<Elem>::dequeue() 
{
    Node *temp = NULL;
    Elem value; 
    if (!qempty) {
        temp = qfront;
        value = qfront->value;
        qfront = qfront->next; // sets a new front element.
        delete temp;
        qnum_of_elements--;
    }
    // checks if the queue is empty.
    qempty = qnum_of_elements == 0 ? true : false; 
    return value;
}

/*
 * A `front` function.
 * Returns a front element from the queue.
 * If the queue is empty, the result has undefined behavior.
 */
template<typename Elem>
Elem Queue<Elem>::front() const
{
    Elem value;
    if (qfront != NULL) {
        value = qfront->value;
    }
    return value;
}

/*
 * A `back` function.
 * Returns a back element from the queue.
 * If the queue is empty, the result has undefined behavior.
 */
template<typename Elem>
Elem Queue<Elem>::back() const
{
    Elem value;
    if (qback != NULL) {
        value = qback->value;
    }
    return value;
}

/*
 * THe overloaded `<<` operator for the Queue class.
 * Prints all elements from the queue in the format: `(1, ...,100)`.
 * Returns ostream.
 */
template<typename Elem>
std::ostream& operator<<(std::ostream& stream, const Queue<Elem>& q)
{
    auto *t = q.qfront;
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
     * Node structure for the queue.
     */
    struct q_node {
        void *value; // a pointer to a value.
        q_node *next; // a pointer to the next node.
    };
    
    /*
     * The structure of `queue`.
     * The queue is the structure "First-In-First-Out". 
     * 
     */
    typedef struct {
        q_node *qfront; // a pointer to the first node.
        q_node *qback; // a pointer to the last node.
        unsigned int count; 
        int empty;
    } queue;
    
    /*
     * An `q_create_queue` function.
     * Creates a queue and returns a pointer to it.
     */
    queue *q_create_queue(void);
    
    /*
     * An `q_enqueue` function.
     * Puts an element in the queue.
     * Takes two arguments:
     * `q` - a pointer to the queue.
     * `element` - a pointer to the element.
     */
    void q_enqueue(queue *q, const void *element);
    /*
     * An `q_dequeue` function.
     * Removes the first element in the queue. 
     * Returns a pointer to the deleted element.
     * If the queue is empty, returns the `NULL` pointer.
     * Takes one arguments:
     * `q` - a pointer to the queue.
     */
    void *q_dequeue(queue *q);
    
    /*
     * An `q_front` function.
     * Returns a pointer to the first element from the queue.
     * If the queue is empty, returns the `NULL` pointer.
     * Takes one arguments:
     * `q` - a pointer to the queue.
     */
    void *q_front(queue *q);
    /*
     * An `q_back` function.
     * Returns a pointer to the last element from the queue.
     * If the queue is empty, returns the `NULL` pointer.
     * Takes one arguments:
     * `q` - a pointer to the queue.
     */
    void *q_back(queue *q);
    
    /*
     * An `q_count` function.
     * Returns the size of the queue.
     * Takes one arguments:
     * `q` - a pointer to the queue.
     * Use this function, if necessary.
     * Or instead this function, use `queue->count`.
     */
    unsigned int q_count(queue *q);
    
    /*
     * An `q_delete_queue` function.
     * Removes the queue from memory.
     * `q` - a pointer to the queue.
     */
    void q_delete_queue(queue *q);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUEUE_H */
