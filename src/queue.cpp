#include "queue.h"
#include <cstring>
#include <stdexcept>
#include <new>

namespace pure_c
{
/*
 * Creates a new pointer.
 * Copies a value from the another pointer to a new pointer.
 * Returns a new pointer.
 */
static void * copy_value(const void * pointer)
{
	void * p = ::operator new (sizeof(void *));
	std::memcpy(p, pointer, sizeof(void *));
	return p;
}

/*
 * Checks a pointer to the queue.
 * If a pointer to the queue is NULL, throws the `runtime_error` error.
 */
static void check_queue(const void * q)
{
	if (!q) {
		throw std::runtime_error("The pointer to `queue` is NULL. ");
	}
}

/*
 * Checks the pointer to the element.
 * If a pointer is NULL, throws `runtime_error`.
 */
static void check_element(const void * e)
{
	if (!e) {
		throw std::runtime_error("The pointer to an element is NULL.");
	}
}

/*
 * Creates a new queue and returns the pointer to queue.
 */
queue * queue_create()
{
	queue * q = new queue();
	q->_front = NULL;
	q->_back = NULL;
	q->empty = 1;
	q->count = 0;
	return q;
}

/*
 * Removes the queue and all the elements from memory.
 */
void queue_delete(queue * q)
{
	check_queue(q);
	while (q->_front) {
		queue_node * old = q->_front;
		q->_front = q->_front->next;
		::operator delete (old->value);
		delete old;
	}
	delete q;
}

/*
 * Inserts a new element into the queue.
 * Increases the size of the queue.
 */
void queue_enqueue(queue * q, const void * element)
{
	check_queue(q);
	check_element(element);
	queue_node * new_node = new queue_node(); // a new node.
	new_node->next = NULL;
	new_node->value = copy_value(element); // copy a value.
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
 * Removes the first element from the queue and returns this element.
 * Reduces the size of the queue.
 */
void * queue_dequeue(queue * q)
{
	check_queue(q);
	void * value = NULL;
	if (!q->empty) {
		queue_node * temp = q->_front;
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
void * queue_front(queue * q)
{
	check_queue(q);
	void * value = NULL;
	if (q->_front != NULL) {
		value = copy_value(q->_front->value);
	}
	return value;
}

/*
 * Returns the last element of the queue.
 */
void * queue_back(queue * q)
{
	check_queue(q);
	void * value = NULL;
	if (q->_back != NULL) {
		value = copy_value(q->_back->value);
	}
	return value;
}

/*
 * Returns the size of the queue.
 */
unsigned int queue_count(queue * q)
{
	return q->count;
}
}
