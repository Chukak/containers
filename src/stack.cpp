#include "stack.h"
#include <cstring>
#include <new>


static void *copy_value(const void *pointer)
{
    void *p = ::operator new(sizeof(void *));
    std::memcpy(p, pointer, sizeof(void *));
    return p;
}

stack *s_create_stack()
{
    stack *s = new stack();
    s->front = NULL;
    s->empty = 1;
    s->count = 0;
    return s;
}

void s_delete_stack(stack *s)
{
    s_node *old = NULL;
    while (s->front) {
        old = s->front;
        s->front = s->front->prev;
        ::operator delete(old->value);
        delete old;
    }
    delete s;
}

void s_push(stack *s, const void *element)
{
    s_node *new_node = new s_node();
    new_node->prev = NULL;
    new_node->value = copy_value(element);
    if (s->empty) {
        s->front = new_node;
        s->empty = 0;
    } else {
        new_node->prev = s->front;
        s->front = new_node;
    }
    s->count++;
}

void *s_pop(stack *s) 
{
    s_node *temp = NULL;
    void *value = NULL;
    if (!s->empty) {
        temp = s->front;
        value = s->front->value;
        s->front = s->front->prev;
        delete temp;
        s->count--;
    }
    s->empty = s->count == 0 ? 1 : 0;
    return value;
}


void *s_front(stack *s)
{
    void *value = NULL;
    if (s->front != NULL) {
        value = s->front->value;
    }
    return value;
}
