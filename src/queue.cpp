#include "queue.h"
#include <cstring>
#include <stdexcept>
#include <new>

/*
 * Creates a new pointer.
 * Copies a value from the another pointer to a new pointer.
 * Returns a new pointer.
 */
static void *copy_value(const void *pointer)
{
    void *p = ::operator new(sizeof(void *));
    std::memcpy(p, pointer, sizeof(void *));
    return p;
}

/*
 * Checks a pointer to the queue.
 * If a pointer to the queue is NULL, Raises `runtime_error`.
 */
static void check_queue(const void *q) 
{
    if (!q) {
        throw std::runtime_error("The pointer to `queue` is NULL. ");
    }
}

/*
 * Creates a queue and returns a pointer to it.
 */
queue *q_create_queue()
{
    queue *q = new queue();
    q->qfront = NULL;
    q->qback = NULL;
    q->empty = 1;
    q->count = 0;
    return q;
}

/*
 * Removes the queue and all the elements from memory.
 */
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

/*
 * Puts an element in the queue.
 * Increases the size of the queue.
 */
void q_enqueue(queue *q, const void *element)
{
    check_queue(q);
    // if a pointer is NULL, raises `runtime_error`.
    if (!element) {
        throw std::runtime_error("The pointer to an element is NULL.");
    }
    q_node *new_node = new q_node(); // a new node.
    new_node->next = NULL;
    new_node->value = copy_value(element); // copies a value.
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

/*
 * Removes the last element from the queue and returns the deleted element.
 * Reduces the size of the queue.
 */
void *q_dequeue(queue *q) 
{
    check_queue(q);
    q_node *temp = NULL;
    void *value = NULL;
    if (!q->empty) {
        temp = q->qfront;
        value = copy_value(q->qfront->value); // gets a value from the element.
        q->qfront = q->qfront->next;
        delete temp;
        q->count--;
    }
    if (!q->count) {
        q->qback = NULL;
        q->empty = 1;
    }
    return value;
}

/*
 * Returns a front element from the queue.
 */
void *q_front(queue *q)
{
    check_queue(q);
    void *value = NULL;
    if (q->qfront != NULL) {
        value = copy_value(q->qfront->value);
    }
    return value;
}

/*
 * Returns a back element from the queue.
 */
void *q_back(queue *q)
{
    check_queue(q);
    void *value = NULL;
    if (q->qback != NULL) {
        value = copy_value(q->qback->value);
    }
    return value;
}

/*
 * Returns the size of the queue.
 */
unsigned int q_count(queue *q) 
{
    return q->count;
}
