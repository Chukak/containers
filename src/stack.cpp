#include "stack.h"
#include <cstring>
#include <stdexcept>
#include <new>

namespace pure_c
{

/*
 * Creates a new pointer.
 * Copies a value from the another pointer to a new pointer.
 * Returns the new pointer.
 */
static void * copy_value(const void * pointer)
{
	void * p = ::operator new (sizeof(void *));
	std::memcpy(p, pointer, sizeof(void *));
	return p;
}

/*
 * Checks the pointer to the stack.
 * If the pointer to the stack is NULL, throws the `runtime_error` exception.
 */
static void check_stack(const void * s)
{
	if (!s) {
		throw std::runtime_error("The pointer to `stack` is NULL. ");
	}
}

/*
 * Checks the pointer to the element.
 * If a pointer is NULL, throws `runtime_error` exception.
 */
static void check_element(const void * e)
{
	if (!e) {
		throw std::runtime_error("The pointer to an element is NULL.");
	}
}

/*
 * Creates a stack and returns a pointer to it.
 */
stack * stack_create()
{
	stack * s = new stack();
	s->front = NULL;
	s->empty = 1;
	s->count = 0;
	return s;
}

/*
 * Removes the stack and all the elements from memory.
 */
void stack_delete(stack * s)
{
	check_stack(s);
	while (s->front) {
		stack_node * old = s->front;
		s->front = s->front->prev;
		::operator delete (old->value);
		delete old;
	}
	delete s;
}

/*
 * Inserts a new element into the stack.
 * Increases the size of the stack.
 */
void stack_push(stack * s, const void * element)
{
	check_stack(s);
	check_element(element);
	stack_node * new_node = new stack_node(); // a new node.
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
 * Removes the last element from the stack and returns the deleted element.
 * Reduces the size of the stack.
 */
void * stack_pop(stack * s)
{
	check_stack(s);
	void * value = NULL;
	if (!s->empty) {
		stack_node * temp = s->front;
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
void * stack_front(stack * s)
{
	check_stack(s);
	void * value = NULL;
	if (s->front != NULL) {
		value = copy_value(s->front->value);
	}
	return value;
}

/*
 * Returns the size of the stack.
 */
unsigned int stack_count(stack * s)
{
	return s->count;
}
}
