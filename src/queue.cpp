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
 * If a pointer to the queue is NULL, throws the `runtime_error` error.
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
    q->_front = NULL;
    q->_back = NULL;
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
    while (q->_front) {
        old = q->_front;
        q->_front = q->_front->next;
        ::operator delete(old->value);
        delete old;
    }
    delete q;
}

/*
 * Inserts an element into the queue.
 * Increases the size of the queue.
 */
void q_enqueue(queue *q, const void *element)
{
    check_queue(q);
    // if a pointer is NULL, throws `runtime_error`.
    if (!element) {
        throw std::runtime_error("The pointer to an element is NULL.");
    }
    q_node *new_node = new q_node(); // a new node.
    new_node->next = NULL;
    new_node->value = copy_value(element); // copies a value.
    if (q->empty) {
        q->_front = new_node;
        q->_back = new_node;
        q->empty = 0;
    } else {
        q->_back->next = new_node;
        q->_back = new_node;
    }
    q->count++;
}

/*
 * Removes the first element of the queue and returns this element.
 * Reduces the size of the queue.
 */
void *q_dequeue(queue *q) 
{
    check_queue(q);
    q_node *temp = NULL;
    void *value = NULL;
    if (!q->empty) {
        temp = q->_front;
        value = copy_value(q->_front->value); // gets a value from the element.
        q->_front = q->_front->next;
        delete temp;
        q->count--;
    }
    if (!q->count) {
        q->_back = NULL;
        q->empty = 1;
    }
    return value;
}

/*
 * Returns the first element of the queue.
 */
void *q_front(queue *q)
{
    check_queue(q);
    void *value = NULL;
    if (q->_front != NULL) {
        value = copy_value(q->_front->value);
    }
    return value;
}

/*
 * Returns the last element of the queue.
 */
void *q_back(queue *q)
{
    check_queue(q);
    void *value = NULL;
    if (q->_back != NULL) {
        value = copy_value(q->_back->value);
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
