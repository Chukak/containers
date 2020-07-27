#include "stack.h"
#include "extensions.h"

namespace pure_c
{
/*
 * Creates a stack and returns a pointer to it.
 */
stack* stack_create()
{
    stack* s = (stack*)std::malloc(sizeof(stack));
    s->front = NULL;
    s->empty = 1;
    s->count = 0;
    return s;
}

/*
 * Removes the stack and all the elements from memory.
 */
void stack_delete(stack* s)
{
    while(s->front) {
        stack_node* old = s->front;
        s->front = s->front->prev;
        free(old->value);
        free(old);
    }
    free(s);
}

/*
 * Inserts a new element into the stack.
 * Increases the size of the stack.
 */
void stack_push(stack* s, const void* element, size_t length)
{
    stack_node* new_node = (stack_node*)std::malloc(sizeof(stack_node)); // a new node.
    new_node->prev = NULL;
    new_node->value = pure_c::copy_memory_block(element, length); // copies a value.
    new_node->_aligned = length;
    if(s->empty) {
        s->front = new_node;
        s->empty = 0;
    } else {
        new_node->prev = s->front;
        s->front = new_node;
    }
    s->count++;
}

/*
 * Removes the last element from the stack and returns the deleted element.
 * Reduces the size of the stack.
 */
void* stack_pop(stack* s)
{
    void* value = NULL;
    if(!s->empty) {
        stack_node* temp = s->front;
        value = pure_c::copy_memory_block(s->front->value, s->front->_aligned); // gets a value from the element.
        s->front = s->front->prev;
        free(temp->value);
        free(temp);
        s->count--;
    }
    s->empty = s->count == 0 ? 1 : 0;
    return value;
}

/*
 * Returns the first element of the stack.
 */
void* stack_front(stack* s)
{
    void* value = NULL;
    if(s->front != NULL) {
        value = pure_c::copy_memory_block(s->front->value, s->front->_aligned);
    }
    return value;
}

/*
 * Returns the size of the stack.
 */
unsigned int stack_count(stack* s)
{
    return s->count;
}
} // namespace pure_c
