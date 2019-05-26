#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#ifdef __cplusplus
#define NULL nullptr
#endif
#endif

#ifdef __cplusplus
#include "extensions.h"
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <memory>

/*
 * The `Queue` class.
 * The queue is the structure "First-In-First-Out".
 */
template<typename Type>
class Queue
{
	/*
	 * A linked list structure.
	 * Used to represent elements in memory.
	 */
	struct Node {
		friend class Queue<Type>;
		friend class iterator;
		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Queue<T>& q);

		Type value; // a value.
	private:
		std::shared_ptr<Node> next; // a pointer to the next node.
		/*
		 * Constructor.
		 */
		Node(Type&& v, std::shared_ptr<Node> n);
		Node(const Type& v, std::shared_ptr<Node> n);
	};
private:
	using node_ptr = std::shared_ptr<Node>;
	/*
	 * Make the overloaded operator `<<` friend.
	 */
	template<typename T>
	friend std::ostream& operator<<(std::ostream& stream, const Queue<T>& q);
public:
	/*
	 * Constructor.
	 */
	Queue();
	/*
	 * Copy constructor.
	 * @param orig - another `Queue` class.
	 */
	Queue(const Queue<Type>& orig);
	/*
	 * Move constructor.
	 */
	Queue(Queue<Type>&& orig) noexcept;
	/*
	 * Constructor, for the initializer list.
	 */
	Queue(std::initializer_list<Type> lst);
	/*
	 * Destructor.
	 */
	virtual ~Queue();
	/*
	 * The operator `=`.
	 */
	Queue<Type>& operator=(const Queue<Type>& orig);
	/*
	 * The mode operator `=`.
	 */
	Queue<Type>& operator=(Queue<Type>&& orig) noexcept;
	/*
	 * The `enqueue` function.
	 * Inserts an element into the queue.
	 * @param element - an element.
	 */
	void enqueue(Type&& element);
	/*
	 * The same `insert` function, but for l-value.
	 */
	void enqueue(const Type& element);
	/*
	 * The `dequeue` funciton.
	 * Removes the first element from the queue and returns it.
	 */
	Type dequeue() noexcept;
	/*
	 * Returns the number of elements.
	 */
	inline unsigned int count() const noexcept
	{
		return _count;
	}
	/*
	 * Returns the first element in the queue.
	 */
	Type front() const noexcept;
	/*
	 * Returns the last element in the queue.
	 */
	Type back() const noexcept;
	/*
	 * Returns `true` if the queue is empty, otherwise returns `false`.
	 */
	inline bool is_empty() const noexcept
	{
		return _empty;
	}
	/*
	 * The `clear` function.
	 * Clears the queue.
	 */
	void clear() noexcept;
private:
	node_ptr _front; // a pointer to the first element.
	node_ptr _back; // a pointer to the last element.
	unsigned int _count; // the numbers of elements.
	bool _empty;

public:
	/*
	 * The `iterator` class.
	 * Implements the iterator of the queue.
	 * The iterator is `forward_iterator`.
	 */
	class iterator : public std::iterator<std::forward_iterator_tag, Type>
	{
		/*
		 *  Make the Queue class friend.
		 */
		friend class Queue<Type>;
	private:
		/*
		 * Constructor.
		 */
		explicit iterator(node_ptr node);
	public:
		using value_type = Type; // value type.
		using iterator_category = std::forward_iterator_tag; // iterator category
		/*
		 * Default constructor.
		 */
		iterator() = default;
		/*
		 * The prefix operator `++`.
		 * Increases the pointer and returns it.
		 */
		inline iterator& operator++() noexcept
		{
			_node = _node->next;
			return *this;
		}
		/*
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 */
		inline iterator operator++([[maybe_unused]] int j) noexcept
		{
			_node = _node->next;
			return *this;
		}
		/*
		 * The operator `*`.
		 * Returns a value from the pointer.
		 */
		inline Type& operator*() const noexcept
		{
			return _node->value;
		}
		/*
		 * The operator `->`.
		 * Returns a pointer to the Node.
		 */
		inline Node * operator->() const noexcept
		{
			return _node.get();
		}
		/*
		 * The operator `!=`.
		 * Compares two iterators. Returns `true` if
		 * iterators aren`t the same. Otherwise returns `false`.
		 */
		inline bool operator!=(const iterator& rhs) const noexcept
		{
			return _node != rhs._node;
		}
		/*
		 * The operator `!=`.
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same. Otherwise returns `false`.
		 */
		inline bool operator!=(std::nullptr_t) const noexcept
		{
			return _node != nullptr;
		}
		/*
		 * The operator `==`.
		 * Compares two iterators. Returns `true` if
		 * iterators are the same. Otherwise returns `false`.
		 */
		inline bool operator==(const iterator& rhs) const noexcept
		{
			return _node == rhs._node;
		}
		/*
		 * The operator `==`.
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same. Otherwise returns `false`.
		 */
		inline bool operator==(std::nullptr_t) const noexcept
		{
			return _node == nullptr;
		}
	private:
		node_ptr _node; // a pointer to a Node.
	};
public:
	/*
	 * Returns the iterator to the first element of the queue.
	 */
	inline iterator begin() const noexcept
	{
		return iterator(_front);
	}
	/*
	 * Returns the iterator to the end of the queue.
	 * The iterator points to the element after the
	 * last element from the queue.
	 */
	inline iterator end() const noexcept
	{
		return _back ? iterator(_back->next) : iterator(_back);
	}
};

/*
 * Constructor
 */
template<typename Type> Queue<Type>::Node::Node(Type&& v, std::shared_ptr<Node> n) :
	value(v),
	next(n)
{}

/*
 * Constructor
 */
template<typename Type> Queue<Type>::Node::Node(const Type& v, std::shared_ptr<Node> n) :
	value(v),
	next(n)
{}

/*
 * Costructor.
 * Creates a new `Queue` class.
 */
template<typename Type> Queue<Type>::Queue() :
	_front(node_ptr(NULL)),
	_back(node_ptr(NULL)),
	_count(0),
	_empty(true)
{
}

/*
 * Constructor.
 * Creates a new `Queue` class from an another `Queue` class.
 */
template<typename Type> Queue<Type>::Queue(const Queue<Type>& orig) :
	_front(node_ptr(NULL)),
	_back(node_ptr(NULL)),
	_count(orig._count),
	_empty(orig._empty)
{
	if (!_empty) {
		node_ptr t = orig._front; // copy a pointer to the first element.
		_front = make_shared_ptr<Node>(Node(t->value, NULL)); // creates a new pointer.
		_back = _front;
		t = t->next; // gets a pointer to the next element.
		while (t) {
			node_ptr new_node = make_shared_ptr<Node>(Node(t->value, NULL));
			_back->next = new_node;
			_back = new_node;
			t = t->next;
		}
	}
}

/*
 * Move constructor.
 */
template<typename Type> Queue<Type>::Queue(Queue<Type>&& orig) noexcept :
	_front(orig._front),
	_back(orig._back),
	_count(orig._count),
	_empty(orig._empty)
{
	orig._front = node_ptr(NULL), orig._back = node_ptr(NULL), orig._count = 0, orig._empty = true;
}

/*
 * Constructor, for the style `Queue q = {1, 2, 3}`.
 */
template<typename Type> Queue<Type>::Queue(std::initializer_list<Type> lst) :
	_front(node_ptr(NULL)),
	_back(node_ptr(NULL)),
	_count(0),
	_empty(true)
{
	/*
	 * Just copy all the elements.
	 */
	for (auto element : lst) {
		enqueue(std::move(element));
	}
}

/*
 * Destructor.
 * Removes all the elements from memory.
 */
template<typename Type> Queue<Type>::~Queue()
{
	while (_front) {
		node_ptr old = _front; // a pointer to the current element.
		_front = _front->next; // a pointer to the next element.
		old.reset();
	}
}

/*
 * The operator `=`.
 */
template<typename Type>
Queue<Type>& Queue<Type>::operator=(const Queue<Type>& orig)
{
	_front = orig._front, _back = orig._back, _count = orig._count, _empty = orig.empty;
	return *this;
}

/*
 * The move operator `=`.
 */
template<typename Type>
Queue<Type>& Queue<Type>::operator=(Queue<Type>&& orig) noexcept
{
	_front = orig._front, _back = orig._back, _count = orig._count, _empty = orig.empty;
	orig._front = node_ptr(NULL), orig._back = node_ptr(NULL), orig._count = 0, orig._empty = true;
	return *this;
}

/*
 * The `enqueue` function.
 * Inserts an element into the queue.
 * Increases the size of the queue.
 */
template<typename Type>
void Queue<Type>::enqueue(Type&& element)
{
	node_ptr new_node = make_shared_ptr<Node>(Node(std::forward<Type>(element), NULL)); // a new pointer.
	if (_empty) {
		_front = _back = new_node;
		_empty = false;
	} else {
		_back->next = new_node; // sets the next element.
		_back = new_node; // sets the last element.
	}
	++_count;
}

template<typename Type>
void Queue<Type>::enqueue(const Type& element)
{
	enqueue(Type(element));
}

/*
 * The `dequeue` function.
 * Removes the first element from the queue.
 * Reduces the size of the queue.
 * If the queue is empty, the result has an undefined behavior.
 */
template<typename Type>
Type Queue<Type>::dequeue() noexcept
{
	Type value;
	if (!_empty) {
		node_ptr old = _front;
		value = _front->value;
		_front = _front->next;
		old.reset();
		_empty = --_count == 0;
		if (_empty) {
			_back.reset();
		}
	}
	return value;
}

/*
 * The `front` function.
 * Returns the first element in the queue.
 * If the queue is empty, the result has an undefined behavior.
 */
template<typename Type>
Type Queue<Type>::front() const noexcept
{
	return _front != NULL ? _front->value : Type();
}

/*
 * The `back` function.
 * Returns the last element in the queue.
 * If the queue is empty, the result has an undefined behavior.
 */
template<typename Type>
Type Queue<Type>::back() const noexcept
{
	return _back != NULL ? _back->value : Type();
}

/*
 * The `clear` function.
 * Clears the queue.
 */
template<typename Type>
void Queue<Type>::clear() noexcept
{
	while (_front) {
		node_ptr old = _front; // a pointer to the current element.
		_front = _front->next; // a pointer to the next element.
		old.reset();
	}
	_front = node_ptr(NULL), _back = node_ptr(NULL), _empty = true, _count = 0;
}

/*
 * The overloaded `<<` operator for the queue.
 * Prints all the elements from the queue in the format: `(1, ...,100)`.
 * Returns ostream.
 */
template<typename Type>
std::ostream& operator<<(std::ostream& stream, const Queue<Type>& q)
{
	stream << "(";
	std::size_t i = 0;
	for (auto it = q.begin(); it != q.end(); ++it) {
		stream << it->value << (i + 1 < q._count ? ", " : "");
		++i;
	}
	stream << ")";
	return stream;
}

/*
 * Constructor.
 */
template<typename Type> Queue<Type>::iterator::iterator(node_ptr node) :
	_node(node)
{}

#endif /* __cplusplus */

/*
 * A declaration the structure `queue` for C.
 */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NULL
#define NULL ((void *)0)
#endif

namespace pure_c
{
/*
 * The node structure for the queue.
 */
typedef struct queue_node {
	void * value; // a pointer to a value.
	queue_node * next; // a pointer to the next node.
} queue_node;
/*
 * The structure `queue`.
 * The queue is the structure "First-In-First-Out".
 *
 */
typedef struct {
	queue_node * _front; // a pointer to the first node.
	queue_node * _back; // a pointer to the last node.
	unsigned int count;
	int empty;
} queue;
/*
 * The `queue_create_queue` function.
 * Creates a queue and returns a pointer to it.
 */
queue * queue_create(void);
/*
 * The `queue_enqueue` function.
 * Inserts an element into the queue.
 * Takes two arguments:
 * `q` - a pointer to the queue.
 * `element` - a pointer to the element.
 */
void queue_enqueue(queue * q, const void * element);
/*
 * The `queue_dequeue` function.
 * Removes the first element from the queue.
 * Returns a pointer to the deleted element.
 * If the queue is empty, returns the `NULL` pointer.
 * Takes one argument:
 * `q` - a pointer to the queue.
 */
void * queue_dequeue(queue * q);
/*
 * The `queue_front` function.
 * Returns a pointer to the first element in the queue.
 * If the queue is empty, returns the `NULL` pointer.
 * Takes one argument:
 * `q` - a pointer to the queue.
 */
void * queue_front(queue * q);
/*
 * The `queue_back` function.
 * Returns a pointer to the last element in the queue.
 * If the queue is empty, returns the `NULL` pointer.
 * Takes one argument:
 * `q` - a pointer to the queue.
 */
void * queue_back(queue * q);
/*
 * The `queue_count` function.
 * Returns the size of the queue.
 * Takes one argument:
 * `q` - a pointer to the queue.
 * Use this function, if necessary.
 * or instead this function, use `queue->count`.
 */
unsigned int queue_count(queue * q);
/*
 * The `queue_delete_queue` function.
 * Removes the queue from memory.
 * Takes one argument:
 * `q` - a pointer to the queue.
 */
void queue_delete(queue * q);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUEUE_H */
