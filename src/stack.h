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
#include <memory>

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
     * Constructor.
     */
    Stack();
    
    /*
     * Copy constructor.
     * @param orig - another `Stack` class.
     */
    Stack(const Stack<Elem> &orig);
    
    /*
     * Move constructor.
     */
    Stack(Stack<Elem> &&orig);
    
    /*
     * Constructor, for the style `Stack s = {1, 2, 3}`.
     */
    explicit Stack(std::initializer_list<Elem> lst);
    
    /*
     * Destructor.
     */
    virtual ~Stack();
    
    /*
     * The `push` function.
     * Inserts an element into the stack.
     * @param element - an element.
     */
    void push(const Elem &element);
    
    /*
     * The `pop` funciton.
     * Removes the first element of the stack. 
     */
    Elem pop() noexcept;
    
    /*
     * Returns the number of elements.
     */
    uint count() const noexcept { return _count; }
    
    /*
     * Returns the first element of the stack.
     */
    Elem front() const noexcept;
    
    /*
     * Returns `true` if the stack is empty, otherwise returns `false`. 
     */
    bool is_empty() const noexcept { return empty; }
    
private:
    /*
     * A linked list structure.
     * Used to represent elements in memory.
     */
    struct Node {
        friend class Stack<Elem>;
        
        friend class iterator;
        
        template<typename T>
        friend std::ostream& operator<<(std::ostream& stream, const Stack<T>& s);
        
        Elem value; // a value.
    private:
        std::shared_ptr<Node> prev; // a pointer to the previous element.
        
        /*
         * Constructor.
         */
        Node(const Elem &v, std::shared_ptr<Node> n) : value(v), prev(n) {}
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
    uint _count; // the numbers of elements.
    bool empty;
    
public:
    class iterator;
    
    /*
     * The `iterator` class.
     * Implements the iterator for the stack.
     * The iperator is `forward_iterator`.
     */
    class iterator : public std::iterator<std::forward_iterator_tag, Elem> {
        /*
         * Sets the friend class.
         */
        friend class Stack<Elem>;
        
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
            m_node = m_node->prev;
            return *this;
        }
        
        /*
         * The postfix operator `++`.
         * Increases the pointer and returns it. 
         */
        iterator& operator++(int j) noexcept
        {
            m_node = m_node->prev;
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
     * Returns the iterator to the first element of the stack.
     */
    iterator begin() const noexcept { return iterator(_front); }
    
    /*
     * Returns the iterator to the end of the stack. 
     * It is usually `nullptr`.
     */
    iterator end() const noexcept { return iterator(nullptr); }
};

/*
 * Constructor.
 * Creates a new `Stack` class. 
 */
template<typename Elem>
Stack<Elem>::Stack() :
    _front(sptr(NULL)),
    _count(0),
    empty(true)
{
}

/*
 * Constructor.
 * Creates a new `Stack` class from the another `Stack` class.
 */
template<typename Elem>
Stack<Elem>::Stack(const Stack<Elem> &orig) :
    _front(sptr(NULL)),
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
    _front = make_sptr(Node(orig._front->value, NULL)); // copy a pointer to the first element.
    sptr t = _front;
    sptr temp = orig._front->prev; // gets a pointer to the previous element.
    while (temp) {
        t->prev = make_sptr(Node(temp->value, NULL));
        temp = temp->prev;
        t = t->prev;
    }
}

/*
 * Move constructor.
 */
template<typename Elem>
Stack<Elem>::Stack(Stack<Elem>&& orig) :
    _front(orig._front),
    _count(orig._count),
    empty(orig.empty)
{
    orig._front = sptr(NULL);
    orig._count = 0;
    orig.empty = true;
}


/*
 * Constructor, for the style `Stack s = {1, 2, 3}`.
 */
template<typename Elem>
Stack<Elem>::Stack(std::initializer_list<Elem> lst) :
    _front(sptr(NULL)), 
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
 * Destructor.
 * Removes all the elements from memory.
 */
template<typename Elem>
Stack<Elem>::~Stack() 
{
    //sptr old = sptr(NULL);
    while (_front) {
        sptr old = _front; // a pointer to the current element.
        _front = _front->prev; // a pointer to the previous element.
        old.reset();
    }
}

/*
 * The `push` function.
 * inserts an element into the stack at the beginning.
 * Increases the size of the stack.
 */
template<typename Elem>
void Stack<Elem>::push(const Elem& element)
{
    sptr new_node = make_sptr(Node(element, NULL)); // a new pointer.
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
 * The `pop` function.
 * Removes the first element of the stack.
 * Reduces the size of the stack.
 * If the stack is empty, the result has an undefined behavior.
 */
template<typename Elem>
Elem Stack<Elem>::pop() noexcept
{
    //sptr old = sptr(NULL);
    Elem value;
    if (!empty) {
        sptr old= _front;
        value = _front->value;
        _front = _front->prev;
        old.reset();
        _count--;
    }
    // checks if the stack is empty.
    empty = _count == 0 ? true : false;
    return value;
}

/*
 * The `front` function.
 * Returns the first element of the stack.
 * If the stack is empty, the result has an undefined behavior.
 */
template<typename Elem>
Elem Stack<Elem>::front() const noexcept
{
    Elem value;
    if (_front != NULL) {
        value = _front->value;
    }
    return value;
}

/*
 * The overloaded `<<` operator for the stack.
 * Prints all the elements of the stack in the format: `(1, ...,100)`.
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
     * The node structure for the stack.
     */
    struct s_node {
        void *value; // a pointer to a value.
        s_node *prev; // a pointer to the next node.
    };
    
    /*
     * The structure `stack`.
     * The stack is the structure "Last-In-First-Out". 
     * 
     */
    typedef struct {
        s_node *front; // a pointer to the first node.
        uint count; // a pointer to the last node.
        int empty;
    } stack;
    
    /*
     * The `s_create_stack` function.
     * Creates a stack and returns a pointer to it.
     */
    stack *s_create_stack();
    
    /*
     * The `s_push` function.
     * Inserts an element into the stack.
     * Takes two arguments:
     * `s` - a pointer to the stack.
     * `element` - a pointer to the element.
     */
    void s_push(stack *s, const void *element);
    
    /*
     * The `s_pop` function.
     * Removes the first element in the stack. 
     * Returns a pointer to the deleted element.
     * If the stack is empty, returns the `NULL` pointer.
     * Takes one argument:
     * `s` - a pointer to the stack.
     */
    void *s_pop(stack *s);
    
    /*
     * The `s_front` function.
     * Returns a pointer to the first element from the stack.
     * If the stack is empty, returns the `NULL` pointer.
     * Takes one argument:
     * `s` - a pointer to the stack.
     */
    void *s_front(stack *s);
    
    /*
     * The `s_count` function.
     * Returns the size of the stack.
     * Takes one argument:
     * `s` - a pointer to the stack.
     * Use this function, if necessary.
     * Or instead this function, use `stack->count`.
     */
    uint s_count(stack *s);
    
    /*
     * The `s_delete_stack` function.
     * Removes the stack from memory.
     * Takes one argument:
     * `s` - a pointer to the stack.
     */
    void s_delete_stack(stack *s);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STACK_H */
