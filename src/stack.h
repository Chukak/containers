#ifndef STACK_H
#define STACK_H

#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#else
#define NULL (void *)0
#endif
#endif

#ifdef __cplusplus
template<typename Elem>
class Stack {
public:
    Stack();
    Stack(const Stack<Elem> &orig);
    virtual ~Stack();
    
    void push(const Elem &element);
    Elem pop();
    unsigned int count() { return elements; }
    
    Elem front() const;
    
    bool empty() const { return sempty; }
    
private:
    struct Node {
        Elem value;
        Node *prev;

        Node(const Elem &v, Node *n) : value(v), prev(n) {}
    };
    
    Node *sfront;
    unsigned int elements;
    bool sempty;
};

template<typename Elem>
Stack<Elem>::Stack()
{
    sfront = NULL;
    elements = 0;
    sempty = true;
}

template<typename Elem>
Stack<Elem>::Stack(const Stack<Elem> &orig) : 
elements(orig.count())
{
}

template<typename Elem>
Stack<Elem>::~Stack() 
{
    Node *old = NULL;
    while (sfront) {
        old = sfront;
        sfront = sfront->prev;
        delete old;
    }
}

template<typename Elem>
void Stack<Elem>::push(const Elem& element)
{
    Node *new_node = new Node(element, NULL);
    if (sempty) {
        sfront = new_node;
        sempty = false;
    } else {
        new_node->prev = sfront;
        sfront = new_node;
    }
    elements++;
}

template<typename Elem>
Elem Stack<Elem>::pop()
{
    Node *temp = NULL;
    Elem value;
    if (!sempty) {
        temp = sfront;
        value = sfront->value;
        sfront = sfront->prev;
        delete temp;
        elements--;
    }
    sempty = elements == 0 ? true : false;
    return value;
}

template<typename Elem>
Elem Stack<Elem>::front() const
{
    Elem value;
    if (sfront != NULL) {
        value = sfront->value;
    }
    return value;
}
#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    struct s_node {
        void *value;
        s_node *prev;
    };
    
    struct stack {
        s_node *front;
        unsigned int count;
        int empty;
    };
    
    stack *s_create_stack();
    
    void s_push(stack *s, const void *element);
    void *s_pop(stack *s);
    
    void *s_front(stack *s);
    
    unsigned int s_count(stack *s);
    
    void s_delete_stack(stack *s);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STACK_H */
