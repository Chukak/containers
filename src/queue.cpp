#include "queue.h"
#include "extensions.h"

namespace pure_c
{
/*
 * Creates a new queue and returns the pointer to queue.
 */
queue *queue_create()
{
    queue *q = (queue *)std::malloc(sizeof(queue));
    q->_front = NULL;
    q->_back = NULL;
    q->empty = 1;
    q->count = 0;
    return q;
}

/*
 * Removes the queue and all the elements from memory.
 */
void queue_delete(queue *q)
{
    while(q->_front) {
        queue_node *old = q->_front;
        q->_front = q->_front->next;
        free(old->value);
        free(old);
    }
    free(q);
}

/*
 * Inserts a new element into the queue.
 * Increases the size of the queue.
 */
void queue_enqueue(queue *q, const void *element, size_t length)
{
    queue_node *new_node = (queue_node *)std::malloc(sizeof(queue_node)); // a new node.
    new_node->next = NULL;
    new_node->value = pure_c::copy_memory_block(element, length); // copy a value.
    new_node->_aligned = length;
    if(q->empty) {
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
 * Removes the first element from the queue and returns this element.
 * Reduces the size of the queue.
 */
void *queue_dequeue(queue *q)
{
    void *value = NULL;
    if(!q->empty) {
        queue_node *temp = q->_front;
        value = pure_c::copy_memory_block(q->_front->value, q->_front->_aligned); // gets a value from the element.
        q->_front = q->_front->next;
        free(temp->value);
        free(temp);
        q->count--;
    }
    if(!q->count) {
        q->_back = NULL;
        q->empty = 1;
    }
    return value;
}

/*
 * Returns the first element of the queue.
 */
void *queue_front(queue *q)
{
    void *value = NULL;
    if(q->_front != NULL) {
        value = pure_c::copy_memory_block(q->_front->value, q->_front->_aligned);
    }
    return value;
}

/*
 * Returns the last element of the queue.
 */
void *queue_back(queue *q)
{
    void *value = NULL;
    if(q->_back != NULL) {
        value = pure_c::copy_memory_block(q->_back->value, q->_front->_aligned);
    }
    return value;
}

/*
 * Returns the size of the queue.
 */
unsigned int queue_count(queue *q)
{
    return q->count;
}
} // namespace pure_c
