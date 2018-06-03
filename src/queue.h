#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#endif
#endif

#ifdef __cplusplus
#include <initializer_list>

template<typename Elem>
class Queue {
public:
    Queue();
    Queue(const Queue<Elem> &orig);
    Queue(std::initializer_list<Elem> lst);
    virtual ~Queue();
    
    void enqueue(const Elem &element);
    Elem dequeue();
    unsigned int count() const { return qnum_of_elements; };
    
    Elem front() const;
    Elem back() const;
    
    bool empty() const { return qempty; }
private:
    struct Node {
        Elem value;
        Node *next;

        Node(const Elem &v, Node *n) : value(v), next(n) {}
    };
    
    Node *qfront;
    Node *qback;
    unsigned int qnum_of_elements;
    bool qempty;
    
};

template<typename Elem>
Queue<Elem>::Queue()
{
    qfront = NULL;
    qback = NULL;
    qnum_of_elements = 0;
    qempty = true;
}

template<typename Elem>
Queue<Elem>::Queue(const Queue<Elem> &orig) : 
    qfront(NULL),
    qback(NULL),
    qnum_of_elements(orig.qnum_of_elements),
    qempty(false)
{
    if (orig.empty()) {
        qempty = true;
        return ;
    }
    Node *t = orig.qfront;
    qfront = new Node(t->value, NULL);
    qback = qfront;
    t = t->next;
    while (t) {
        Node *new_node = new Node(t->value, NULL);
        qback->next = new_node;
        qback = new_node;
        t = t->next;
    } 
}

template<typename Elem>
Queue<Elem>::Queue(std::initializer_list<Elem> lst) :
    qfront(NULL), 
    qback(NULL),
    qnum_of_elements(0),
    qempty(true)
{
    for (auto element : lst) {
        enqueue(element);
    }
}

template<typename Elem>
Queue<Elem>::~Queue() 
{
    Node *old = NULL;
    while (qfront) {
        old = qfront;
        qfront = qfront->next;
        delete old;
    }
}

template<typename Elem>
void Queue<Elem>::enqueue(const Elem &element) 
{
    Node *new_node = new Node(element, NULL);
    if (qempty) {
        qfront = new_node;
        qback = new_node;
        qempty = false;
    } else {
        qback->next = new_node;
        qback = new_node;
    }
    qnum_of_elements++;
}

template<typename Elem>
Elem Queue<Elem>::dequeue() 
{
    Node *temp = NULL;
    Elem value;
    if (!qempty) {
        temp = qfront;
        value = qfront->value;
        qfront = qfront->next;
        delete temp;
        qnum_of_elements--;
    }
    qempty = qnum_of_elements == 0 ? true : false;
    return value;
}

template<typename Elem>
Elem Queue<Elem>::front() const
{
    Elem value;
    if (qfront != NULL) {
        value = qfront->value;
    }
    return value;
}

template<typename Elem>
Elem Queue<Elem>::back() const
{
    Elem value;
    if (qback != NULL) {
        value = qback->value;
    }
    return value;
}
#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
    
#ifndef NULL
#define NULL ((void *)0)
#endif
    
    typedef struct q_node q_node;
    
    struct q_node {
        void *value;
        q_node *next;
    };
    
    typedef struct {
        q_node *qfront;
        q_node *qback;
        unsigned int count;
        int empty;
    } queue;
    
    queue *q_create_queue(void);
    
    void q_enqueue(queue *q, const void *element);
    void *q_dequeue(queue *q);
    
    void *q_front(queue *q);
    void *q_back(queue *q);
    
    unsigned int q_count(queue *q);
    
    void q_delete_queue(queue *q);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUEUE_H */
