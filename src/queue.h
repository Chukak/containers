#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL nullptr
#endif

template<typename Elem>
struct Node {
    Elem value;
    Node *next;
    
    Node(const Elem &v, Node *n) : value(v), next(n) {}
};

template<typename Elem>
class Queue {
public:
    Queue();
    Queue(const Queue<Elem> &orig);
    virtual ~Queue();
    
    void enqueue(const Elem &element);
    Elem dequeue();
    int count() const { return qnum_of_elements; };
    
    Elem front() const { return qfront->value; }
    Elem back() const { return qback->value; }
    
    bool empty() const { return qempty; }
private:
    Node<Elem> *qfront;
    Node<Elem> *qback;
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
qnum_of_elements(orig.count())
{
}

template<typename Elem>
Queue<Elem>::~Queue() 
{
    Node<Elem> *old = NULL;
    while (qfront) {
        old = qfront;
        qfront = qfront->next;
        delete old;
    }
}

template<typename Elem>
void Queue<Elem>::enqueue(const Elem &element) 
{
    Node<Elem> *new_node = new Node<Elem>(element, NULL);
    if (qempty) {
        std::cout << "da2" << "\n";
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
    Node<Elem> *temp = NULL;
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


#endif /* QUEUE_H */
