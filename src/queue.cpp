#include "queue.h"
#include <cstring>
#include <stdexcept>
#include <new>


static void *copy_value(const void *pointer)
{
    void *p = ::operator new(sizeof(void *));
    std::memcpy(p, pointer, sizeof(void *));
    return p;
}

static void check_queue(const void *q) 
{
    if (!q) {
        throw std::runtime_error("The pointer to `queue` is NULL.");
    }
}

queue *q_create_queue()
{
    queue *q = new queue();
    q->qfront = NULL;
    q->qback = NULL;
    q->empty = 1;
    q->count = 0;
    return q;
}

void q_delete_queue(queue *q)
{
    check_queue(q);
    q_node *old = NULL; 
    while (q->qfront) {
        old = q->qfront;
        q->qfront = q->qfront->next;
        ::operator delete(old->value);
        delete old;
    }
    delete q;
}

void q_enqueue(queue *q, const void *element)
{
    check_queue(q);
    if (!element) {
        std::runtime_error("The pointer to an element is NULL.");
    }
    q_node *new_node = new q_node();
    new_node->next = NULL;
    new_node->value = copy_value(element);
    if (q->empty) {
        q->qfront = new_node;
        q->qback = new_node;
        q->empty = 0;
    } else {
        q->qback->next = new_node;
        q->qback = new_node;
    }
    q->count++;
}

void *q_dequeue(queue *q) 
{
    check_queue(q);
    q_node *temp = NULL;
    void *value = NULL;
    if (!q->empty) {
        temp = q->qfront;
        value = q->qfront->value;
        q->qfront = q->qfront->next;
        delete temp;
        q->count--;
    }
    q->empty = q->count == 0 ? 1 : 0;
    return value;
}


void *q_front(queue *q)
{
    check_queue(q);
    void *value = NULL;
    if (q->qfront != NULL) {
        value = q->qfront->value;
    }
    return value;
}

void *q_back(queue *q)
{
    check_queue(q);
    void *value = NULL;
    if (q->qback != NULL) {
        value = q->qback->value;
    }
    return value;
}
