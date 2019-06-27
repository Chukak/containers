/**
 * @file queue.h
 *
 * Contains the class `Queue`.
 */
#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
#include "extensions.h"
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <memory>

/**
 * The `Queue` class.
 * The queue is the structure "First-In-First-Out".
 * @tparam Type type of elements.
 */
template<typename Type>
class Queue
{
	static_assert(std::disjunction_v <
	              std::is_default_constructible<Type>,
	              std::is_nothrow_default_constructible<Type>
	              >,
	              "Type must have a trivial constructor.");
	/**
	 * The structure `Node`. The node is a linked list structure.
	 * Used to represent elements in memory.
	 */
	struct Node
	{
		friend class Queue<Type>;
		friend class iterator;
		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Queue<T>& q);
		/**
		 * Constructor.
		 */
		Node(Type&& v, std::shared_ptr<Node> n);
		Node(const Type& v, std::shared_ptr<Node> n);

		Type value; //! a value.
	private:
		std::shared_ptr<Node> next; //! a pointer to the next node.
	};
private:
	using node_ptr = std::shared_ptr<Node>;
	/**
	 * Make the overloaded operator `<<` friend.
	 */
	template<typename T>
	friend std::ostream& operator<<(std::ostream& stream, const Queue<T>& q);
public:
	/**
	 * Default constructor.
	 */
	Queue();
	/**
	 * Copy constructor.
	 * @param orig another `Queue` class.
	 */
	Queue(const Queue<Type>& orig);
	/**
	 * Move constructor.
	 * @param orig another `Queue` class.
	 */
	Queue(Queue<Type>&& orig) noexcept;
	/**
	 * Constructor.
	 * @param lst initializer list ({ ... }).
	 */
	Queue(std::initializer_list<Type> lst);
	/**
	 * Destructor.
	 */
	virtual ~Queue();
	/**
	 * The operator `=`.
	 * @param orig the `Queue` class, l-value.
	 * @return this class.
	 */
	Queue<Type>& operator=(const Queue<Type>& orig);
	/**
	 * The move operator `=`.
	 * @param orig the `Queue` class, r-value.
	 * @return this class.
	 */
	Queue<Type>& operator=(Queue<Type>&& orig) noexcept;
	/**
	 * Inserts a new element into the queue.
	 * @param element a new element.
	 */
	void enqueue(Type&& element);
	/**
	 * The same `insert` function, but for l-value.
	 * @param element a new element.
	 */
	void enqueue(const Type& element);
	/**
	 * Removes the first element from the queue and returns it.
	 * @return the first element of the queue.
	 */
	Type dequeue() noexcept;
	/**
	 * @return the number of elements.
	 */
	inline unsigned int count() const noexcept
	{
		return _count;
	}
	/**
	 * @return the first element in the queue.
	 */
	Type front() const noexcept;
	/**
	 * @return the last element in the queue.
	 */
	Type back() const noexcept;
	/**
	 * @return `true` if the queue is empty, otherwise `false`.
	 */
	inline bool is_empty() const noexcept
	{
		return _empty;
	}
	/**
	 * Clears the queue.
	 */
	void clear() noexcept;
private:
	/**
	 * Copy all the elements to this queue.
	 */
	void assign(node_ptr front);
private:
	node_ptr _front; //! a pointer to the first element.
	node_ptr _back; //! a pointer to the last element.
	unsigned int _count{0}; //! the numbers of elements.
	bool _empty{true};

public:
	/**
	 * Implements the iterator of the queue.
	 * The iterator is `forward_iterator`.
	 */
	class iterator : public std::iterator<std::forward_iterator_tag, Type>
	{
		/**
		 * Make the Queue class friend.
		 */
		friend class Queue<Type>;
	private:
		/**
		 * Constructor.
		 */
		explicit iterator(node_ptr node);
	public:
		using value_type = Type; //! iterator value type.
		using iterator_category = std::forward_iterator_tag; //! iterator category
		/**
		 * Default constructor.
		 */
		iterator() = default;
		/**
		 * The prefix operator `++`.
		 * Increases the pointer and returns it.
		 * @return incremented iterator.
		 */
		inline iterator& operator++() noexcept
		{
			_node = _node->next;
			return *this;
		}
		/**
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 * @return incremented iterator.
		 */
		inline iterator operator++([[maybe_unused]] int j) noexcept
		{
			_node = _node->next;
			return *this;
		}
		/**
		 * The operator `*`.
		 * Returns a value from the pointer.
		 * @return a value.
		 */
		inline Type& operator*() const noexcept
		{
			return _node->value;
		}
		/**
		 * The operator `->`.
		 * Returns a pointer to the Node.
		 * @return the node.
		 */
		inline Node * operator->() const noexcept
		{
			return _node.get();
		}
		/**
		 * Compares two iterators. Returns `true` if
		 * iterators aren`t the same, otherwise `false`.
		 * @param rhs another iterator.
		 * @return result of comparison.
		 */
		inline bool operator!=(const iterator& rhs) const noexcept
		{
			return _node != rhs._node;
		}
		/**
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same, otherwise `false`.
		 * @return result of comparison.
		 */
		inline bool operator!=(std::nullptr_t) const noexcept
		{
			return _node != nullptr;
		}
		/**
		 * Compares two iterators. Returns `true` if
		 * iterators are the same, otherwise `false`.
		 * @param rhs another iterator.
		 * @return result of comparison.
		 */
		inline bool operator==(const iterator& rhs) const noexcept
		{
			return _node == rhs._node;
		}
		/**
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same, otherwise `false`.
		 * @return result of comparison.
		 */
		inline bool operator==(std::nullptr_t) const noexcept
		{
			return _node == nullptr;
		}
	private:
		node_ptr _node; //! a pointer to the Node.
	};
public:
	/**
	 * Returns the iterator to the first element of the queue.
	 * @return iterator
	 */
	inline iterator begin() const noexcept
	{
		return iterator(_front);
	}
	/**
	 * Returns the iterator to the end of the queue.
	 * The iterator points to the element after the
	 * last element from the queue.
	 * @return iterator
	 */
	inline iterator end() const noexcept
	{
		return _back ? iterator(_back->next) : iterator(_back);
	}
};

/*
 * Constructor
 */
template<typename Type>
Queue<Type>::Node::Node(Type&& v, std::shared_ptr<Node> n) :
	value(std::forward<Type>(v)),
	next(n)
{}

/*
 * Constructor
 */
template<typename Type>
Queue<Type>::Node::Node(const Type& v, std::shared_ptr<Node> n) :
	value(v),
	next(n)
{}

/*
 * Costructor.
 * Creates a new queue.
 */
template<typename Type>
Queue<Type>::Queue() :
	_front(nullptr),
	_back(nullptr)
{
}

/*
 * Copy constructor.
 */
template<typename Type>
Queue<Type>::Queue(const Queue<Type>& orig) :
	_front(nullptr),
	_back(nullptr),
	_count(orig._count),
	_empty(orig._empty)
{
	assign(orig._front);
}

/*
 * Move constructor.
 */
template<typename Type>
Queue<Type>::Queue(Queue<Type>&& orig) noexcept :
	_front(orig._front),
	_back(orig._back),
	_count(orig._count),
	_empty(orig._empty)
{
	orig._front = nullptr, orig._back = nullptr, orig._count = 0, orig._empty = true;
}

/*
 * Constructor using initializer list.
 */
template<typename Type>
Queue<Type>::Queue(std::initializer_list<Type> lst) :
	_front(nullptr),
	_back(nullptr)
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
template<typename Type>
Queue<Type>::~Queue()
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
	clear();
	_count = orig._count, _empty = orig.empty;
	assign(orig._front);
	return *this;
}

/*
 * The move operator `=`.
 */
template<typename Type>
Queue<Type>& Queue<Type>::operator=(Queue<Type>&& orig) noexcept
{
	_front = orig._front, _back = orig._back, _count = orig._count, _empty = orig.empty;
	orig._front = nullptr, orig._back = nullptr, orig._count = 0, orig._empty = true;
	return *this;
}

/*
 * The `enqueue` function.
 * Inserts a new element into the queue.
 * Increases the size of the queue.
 */
template<typename Type>
void Queue<Type>::enqueue(Type&& element)
{
	node_ptr new_node = make_shared_ptr<Node>(std::forward<Type>(element), nullptr); // a new pointer.
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
	return _front != nullptr ? _front->value : Type();
}

/*
 * The `back` function.
 * Returns the last element in the queue.
 * If the queue is empty, the result has an undefined behavior.
 */
template<typename Type>
Type Queue<Type>::back() const noexcept
{
	return _back != nullptr ? _back->value : Type();
}

/*
 * Copy all the elements to this queue.
 */
template<typename Type>
void Queue<Type>::assign(node_ptr front)
{
	if (!_empty) {
		node_ptr t = front; // a pointer to the first element.
		_front = _back = make_shared_ptr<Node>(t->value, nullptr); // creates a new pointer.
		t = t->next; // gets a pointer to the next element.
		while (t) {
			node_ptr new_node = make_shared_ptr<Node>(t->value, nullptr);
			_back->next = new_node;
			_back = new_node;
			t = t->next;
		}
	}
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
	_front = nullptr, _back = nullptr, _empty = true, _count = 0;
}

/**
 * The overloaded `<<` operator for the queue.
 * Prints all the elements from the queue in the format: `(1, ...,100)`.
 * @param stream std::ostream.
 * @param q the queue.
 * @return std::ostream.
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
/**
 * The node structure for the queue.
 */
typedef struct queue_node {
	void * value; //! a pointer to the value.
	queue_node * next; //! a pointer to the next node.
} queue_node;
/**
 * The structure `queue`.
 * The queue is the structure "First-In-First-Out".
 */
typedef struct {
	queue_node * _front; //! a pointer to the first node.
	queue_node * _back; //! a pointer to the last node.
	unsigned int count;
	int empty;
} queue;
/**
 * Creates a new queue and returns the pointer to queue.
 * @return a new queue.
 */
queue * queue_create(void);
/**
 * Inserts a new element into the queue.
 * @param q the pointer to the queue.
 * @param element the pointer to the element.
 */
void queue_enqueue(queue * q, const void * element);
/**
 * Removes the first element from the queue.
 * Returns the pointer to the deleted element.
 * If the queue is empty, returns the `NULL` pointer.
 * @param q the pointer to the queue.
 * @return the deleted element.
 */
void * queue_dequeue(queue * q);
/**
 * Returns a pointer to the first element in the queue.
 * If the queue is empty, returns the `NULL` pointer.
 * @param q a pointer to the queue.
 * @return the first element.
 */
void * queue_front(queue * q);
/**
 * Returns a pointer to the last element in the queue.
 * If the queue is empty, returns the `NULL` pointer.
 * @param q a pointer to the queue.
 * @return the last element.
 */
void * queue_back(queue * q);
/**
 * Returns the size of the queue.
 * Use this function, if necessary.
 * or instead this function, use `queue->count`.
 * @param q a pointer to the queue.
 * @return the number of elements.
 */
unsigned int queue_count(queue * q);
/**
 * The `queue_delete_queue` function.
 * Removes the queue from memory.
 * @param q a pointer to the queue.
 */
void queue_delete(queue * q);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* QUEUE_H */
