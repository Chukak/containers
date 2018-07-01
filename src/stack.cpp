#include "stack.h"
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
 * Checks a pointer to the stack.
 * If a pointer to the stack is NULL, throws the `runtime_error` error.
 */
static void check_stack(const void *s) 
{
    if (!s) {
        throw std::runtime_error("The pointer to `stack` is NULL. ");
    }
}

/*
 * Creates a stack and returns a pointer to it.
 */
stack *s_create_stack()
{
    stack *s = new stack();
    s->front = NULL;
    s->empty = 1;
    s->count = 0;
    return s;
}

/*
 * Removes the stack and all the elements from memory.
 */
void s_delete_stack(stack *s)
{
    check_stack(s);
    s_node *old = NULL;
    while (s->front) {
        old = s->front;
        s->front = s->front->prev;
        ::operator delete(old->value);
        delete old;
    }
    delete s;
}

/*
 * Inserts an element into the stack.
 * Increases the size of the stack.
 */
void s_push(stack *s, const void *element)
{
    check_stack(s);
    // if a pointer is NULL, throws `runtime_error`.
    if (!element) {
        throw std::runtime_error("The pointer to an element is NULL.");
    }
    s_node *new_node = new s_node(); // a new node.
    new_node->prev = NULL;
    new_node->value = copy_value(element); // copies a value.
    if (s->empty) {
        s->front = new_node;
        s->empty = 0;
    } else {
        new_node->prev = s->front;
        s->front = new_node;
    }
    s->count++;
}

/*
 * Removes the last element of the stack and returns the deleted element.
 * Reduces the size of the stack.
 */
void *s_pop(stack *s) 
{
    check_stack(s);
    s_node *temp = NULL;
    void *value = NULL;
    if (!s->empty) {
        temp = s->front;
        value = copy_value(s->front->value); // gets a value from the element.
        s->front = s->front->prev;
        delete temp;
        s->count--;
    }
    s->empty = s->count == 0 ? 1 : 0;
    return value;
}


/*
 * Returns the first element of the stack.
 */
void *s_front(stack *s)
{
    check_stack(s);
    void *value = NULL;
    if (s->front != NULL) {
        value = copy_value(s->front->value);
    }
    return value;
}

/*
 * Returns the size of the stack.
 */
unsigned int s_count(stack *s) 
{
    return s->count;
}
