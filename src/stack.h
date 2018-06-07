#ifndef STACK_H
#define STACK_H

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
 * The `Stack` class.
 * The stack is the structure "Last-In-First-Out". 
 */
template<typename Elem>
class Stack {
    /*
     * Sets the friend function for the overloaded operator `<<`.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream, const Stack<T>& s);
    
public:
    /*
     * A constructor.
     */
    Stack();
    /*
     * A constructor, creates the `Stack` class from another `Stack` class.
     * @param orig - a constant link to another `Stack` class.
     */
    Stack(const Stack<Elem> &orig);
    /*
     * A constructor, for the style `Stack s = {1, 2, 3}`.
     */
    Stack(std::initializer_list<Elem> lst);
    /*
     * A destructor.
     */
    virtual ~Stack();
    
    /*
     * An `push` function.
     * Added an element in the stack.
     * @param element - a constant link to the value.
     */
    void push(const Elem &element);
    /*
     * A `pop` funciton.
     * Removes the first element from the stack. 
     */
    Elem pop();
    /*
     * Returns the number of _count.
     */
    uint count() { return _count; }
    
    /*
     * Returns the first element from the stack.
     */
    Elem front() const;
    
    /*
     * Returns `true` if the stack is empty, otherwise returns `false`. 
     */
    bool is_empty() const { return empty; }
    
private:
    /*
     * A linked list structure.
     * Used to represent _count in memory.
     */
    struct Node {
        friend class Stack<Elem>;
        
        friend struct iterator;
        
        template<typename T>
        friend std::ostream& operator<<(std::ostream& stream, const Stack<T>& s);
        
        Elem value; // a value.
    private:
        Node *prev; // a pointer to the previous `Node` structure.
        
        /*
         * A constructor.
         */
        Node(const Elem &v, Node *n) : value(v), prev(n) {}
    };
    
    Node *_front; // a pointer to the first element.
    uint _count; // the numbers of _count.
    bool empty;
    
public:
    class iterator;
    
    /*
     * The `iterator` class.
     * Determines the iterator for the `Stack` class.
     */
    class iterator : public std::iterator<std::forward_iterator_tag, Elem> {
        /*
         * Sets the friend class.
         */
        friend class Stack<Elem>;
        
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
            m_node = m_node->prev;
            return *this;
        }
        
        /*
         * The postfix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++(int hunk) 
        {
            m_node = m_node->prev;
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
    };
    
    /*
     * Returns the iterator to the beginning of the stack.
     */
    iterator begin() const { return iterator(_front); }
    
    /*
     * Returns the iterator to the end of the stack. 
     */
    iterator end() const { return iterator(nullptr); }
};

/*
 * A costructor.
 * Creates a new `Stack` class. 
 */
template<typename Elem>
Stack<Elem>::Stack()
{
    _front = NULL; // a pointer to the first element
    _count = 0; // the numbers of _count
    empty = true;
}

/*
 * A constructor.
 * Creates a new `Queue` class from the another `Stack` class.
 */
template<typename Elem>
Stack<Elem>::Stack(const Stack<Elem> &orig) :
    _front(NULL),
    _count(orig._count),
    empty(false)
{
    /*
     * If an original class is empty, returns from constructor.
     */
    if (orig.empty()) {
        empty = true;
        return ;
    }
    _front = new Node(orig._front->value, NULL); // copy a pointer to the first element.
    Node *t = _front;
    Node *temp = orig._front->prev; // gets a pointer to the previous element.
    while (temp) {
        t->prev = new Node(temp->value, NULL);
        temp = temp->prev;
        t = t->prev;
    }
}

/*
 * A constructor, for the style `Stack s = {1, 2, 3}`.
 */
template<typename Elem>
Stack<Elem>::Stack(std::initializer_list<Elem> lst) :
    _front(NULL), 
    _count(0),
    empty(true)
{
    /*
     * Just copy all the _count.
     */
    for (auto element : lst) {
        push(element);
    }
}

/*
 * A destructor.
 * Removes all the _count from memory.
 */
template<typename Elem>
Stack<Elem>::~Stack() 
{
    Node *old = NULL;
    while (_front) {
        old = _front; // a pointer to a current element.
        _front = _front->prev; // a pointer to the previous element.
        delete old;
    }
}

/*
 * A `push` function.
 * Added an element in the stack at the begining.
 * Increases the size of the stack.
 */
template<typename Elem>
void Stack<Elem>::push(const Elem& element)
{
    Node *new_node = new Node(element, NULL); // a new pointer to an element.
    if (empty) {
        _front = new_node; // front == back.
        empty = false;
    } else {
        new_node->prev = _front; // sets the previous element.
        _front = new_node; // sets the first element.
    }
    _count++;
}

/*
 * A `pop` function.
 * Removes the first element from the stack.
 * Reduces the size of the stack.
 * If the stack is empty, the result has undefined behavior.
 */
template<typename Elem>
Elem Stack<Elem>::pop()
{
    Node *temp = NULL;
    Elem value;
    if (!empty) {
        temp = _front;
        value = _front->value;
        _front = _front->prev; // sets a new front element.
        delete temp;
        _count--;
    }
    // checks if the stack is empty.
    empty = _count == 0 ? true : false;
    return value;
}

/*
 * A `front` function.
 * Returns a front element from the stack.
 * If the stack is empty, the result has undefined behavior.
 */
template<typename Elem>
Elem Stack<Elem>::front() const
{
    Elem value;
    if (_front != NULL) {
        value = _front->value;
    }
    return value;
}

/*
 * The overloaded `<<` operator for the Stack class.
 * Prints all _count from the stack in the format: `(1, ...,100)`.
 * Returns ostream.
 */
template<typename Elem>
std::ostream& operator<<(std::ostream& stream, const Stack<Elem>& s)
{
    auto *t = s._front;
    stream << "(";
    while(t) {
        stream << t->value << ", ";
        t = t->prev;
    }
    stream << "\b\b";
    stream << "";
    stream << ")";
    return stream;
}

#endif /* __cplusplus */


/*
 * A declaration the structure `stack` for C.
 */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
#ifndef NULL
#define NULL ((void *)0)
#endif
  
    typedef struct s_node s_node;
    
    /*
     * Node structure for the stack.
     */
    struct s_node {
        void *value; // a pointer to a value.
        s_node *prev; // a pointer to the next node.
    };
    
    /*
     * The structure of `stack`.
     * The queue is the structure "Last-In-First-Out". 
     * 
     */
    typedef struct {
        s_node *front; // a pointer to the first node.
        uint count; // a pointer to the last node.
        int empty;
    } stack;
    
    /*
     * A `s_create_stack` function.
     * Creates a stack and returns a pointer to it.
     */
    stack *s_create_stack();
    
    /*
     * A `s_push` function.
     * Added an element in the stack.
     * Takes two arguments:
     * `s` - a pointer to the stack.
     * `element` - a pointer to the element.
     */
    void s_push(stack *s, const void *element);
    /*
     * A `s_pop` function.
     * Removes the first element in the stack. 
     * Returns a pointer to the deleted element.
     * If the stack is empty, returns the `NULL` pointer.
     * Takes one arguments:
     * `s` - a pointer to the stack.
     */
    void *s_pop(stack *s);
    
    /*
     * A `s_front` function.
     * Returns a pointer to the first element from the stack.
     * If the stack is empty, returns the `NULL` pointer.
     * Takes one arguments:
     * `s` - a pointer to the stack.
     */
    void *s_front(stack *s);
    
    /*
     * A `s_count` function.
     * Returns the size of the stack.
     * Takes one arguments:
     * `s` - a pointer to the stack.
     * Use this function, if necessary.
     * Or instead this function, use `stack->count`.
     */
    uint s_count(stack *s);
    
    /*
     * A `s_delete_stack` function.
     * Removes the stack from memory.
     * `s` - a pointer to the stack.
     */
    void s_delete_stack(stack *s);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STACK_H */
