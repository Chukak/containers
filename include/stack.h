/**
 * @file stack.h
 *
 * Contains the class `Stack`.
 */
#ifndef STACK_H
#define STACK_H

#ifdef __cplusplus
#include "extensions.h"
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <memory>

/**
 * The stack is the structure "Last-In-First-Out".
 * @tparam Type type of elements.
 */
template<typename Type>
class Stack
{
	static_assert(std::disjunction_v <
	              std::is_default_constructible<Type>,
	              std::is_nothrow_default_constructible<Type>
	              >,
	              "Type must have a trivial constructor.");
	/**
	 * The structure `Node`.
	 * Used to represent elements in memory.
	 */
	struct Node
	{
		friend class Stack<Type>;
		friend class iterator;
		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream, const Stack<T>& s);
		/**
		 * Constructor.
		 */
		Node(Type&& v, std::shared_ptr<Node> p);
		Node(const Type& v, std::shared_ptr<Node> p);

		Type value; //! a value.
	private:
		std::shared_ptr<Node> prev; //! the pointer to the previous element.
	};
private:
	using node_ptr = std::shared_ptr<Node>;
	/**
	 * Makes the overloaded operator `<<` friend.
	 */
	template<typename T>
	friend std::ostream& operator<<(std::ostream& stream, const Stack<T>& s);
public:
	/**
	 * Constructor.
	 */
	Stack();
	/**
	 * Copy constructor.
	 * @param orig - another `Stack` class.
	 */
	Stack(const Stack<Type>& orig);
	/**
	 * Move constructor.
	 * @param orig - another `Stack` class.
	 */
	Stack(Stack<Type>&& orig) noexcept;
	/**
	 * Constructor.
	 * @param lst initializer list ({ ... }).
	 */
	Stack(std::initializer_list<Type> lst);
	/**
	 * Destructor.
	 */
	virtual ~Stack();
	/**
	 * The operator `=`.
	 * @param orig the `Stack` class, l-value.
	 * @return this class.
	 */
	Stack<Type>& operator=(const Stack<Type>& orig);
	/**
	 * The move operator `=`.
	 * @param orig the `Stack` class, l-value.
	 * @return this class.
	 */
	Stack<Type>& operator=(Stack<Type>&& orig) noexcept;
	/**
	 * Inserts a new elements into the stack.
	 * @param element - a new element.
	 */
	void push(Type&& element);
	/**
	 * The same `insert` function, but for l-value.
	 * @param element - a new element.
	 */
	void push(const Type& element);
	/**
	 * Removes the first element from the stack.
	 * @return the first element of the stack.
	 */
	Type pop() noexcept;
	/**
	 * @return the number of elements.
	 */
	inline unsigned int count() const noexcept
	{
		return _count;
	}
	/**
	 * @return the first element in the stack.
	 */
	Type front() const noexcept;
	/**
	 * @return `true` if the stack is empty, otherwise returns `false`.
	 */
	inline bool is_empty() const noexcept
	{
		return _empty;
	}
private:
	/**
	 * Copy all the elements to this stack.
	 */
	void assign(node_ptr front);
	/**
	 * Removes all the elements.
	 */
	void destroy();
private:
	node_ptr _front; //! a pointer to the first element.
	unsigned int _count{0}; //! the numbers of elements.
	bool _empty{true};
public:
	/**
	 * Implements the iterator of the stackc class.
	 * The iterator is `forward_iterator`.
	 */
	class iterator : public std::iterator<std::forward_iterator_tag, Type>
	{
		/**
		 * Makes the Stack class friend.
		 */
		friend class Stack<Type>;
	private:
		/**
		 * Constructor.
		 */
		explicit iterator(node_ptr node);
	public:
		using value_type = Type; //! iterator value type.
		using iterator_category = std::forward_iterator_tag; //! iterator category
	public:
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
			_node = _node->prev;
			return *this;
		}
		/**
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 * @return incremented iterator.
		 */
		inline iterator operator++([[maybe_unused]] int j) noexcept
		{
			_node = _node->prev;
			return *this;
		}
		/**
		 * Returns a value from the pointer.
		 * @return a value.
		 */
		inline Type& operator*() const noexcept
		{
			return _node->value;
		}
		/**
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
		 * @return result of comparison
		 */
		inline bool operator!=(const iterator& rhs) const noexcept
		{
			return _node != rhs._node;
		}
		/**
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same, otherwise `false`.
		 * @return result of comparison
		 */
		inline bool operator!=(std::nullptr_t) const noexcept
		{
			return _node != nullptr;
		}
		/**
		 * Compares two iterators. Returns `true` if
		 * iterators are the same, otherwise `false`.
		 * @param rhs another iterator.
		 * @return result of comparison
		 */
		inline bool operator==(const iterator& rhs) const noexcept
		{
			return _node == rhs._node;
		}
		/**
		 * The operator `==`.
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same, otherwise `false`.
		 * @return result of comparison
		 */
		inline bool operator==(std::nullptr_t) const noexcept
		{
			return _node == nullptr;
		}
	private:
		node_ptr _node; //! a pointer to a Node.
	};
public:
	/**
	 * @return the iterator to the first element in the stack.
	 */
	inline iterator begin() const noexcept
	{
		return iterator(_front);
	}
	/**
	 * Return the iterator to the end of the stack.
	 * It is usually `nullptr`.
	 * @return iterator.
	 */
	inline iterator end() const noexcept
	{
		return iterator(nullptr);
	}
};

/*
 * Constructor
 */
template<typename Type>
Stack<Type>::Node::Node(Type&& v, std::shared_ptr<Node> p) :
	value(std::forward<Type>(v)),
	prev(p)
{}

/*
 * Constructor
 */
template<typename Type>
Stack<Type>::Node::Node(const Type& v, std::shared_ptr<Node> p) :
	value(v),
	prev(p)
{}

/*
 * Default constructor.
 */
template<typename Type>
Stack<Type>::Stack() :
	_front(nullptr)
{
}

/*
 * Copy constructor.
 */
template<typename Type>
Stack<Type>::Stack(const Stack<Type>& orig) :
	_front(nullptr),
	_count(orig._count),
	_empty(orig._empty)
{
	assign(orig._front);
}

/*
 * Move constructor.
 */
template<typename Type>
Stack<Type>::Stack(Stack<Type>&& orig) noexcept :
	_front(orig._front),
	_count(orig._count),
	_empty(orig._empty)
{
	orig._front = nullptr, orig._count = 0, orig._empty = true;
}

/*
 * Constructor, using initializer list.
 */
template<typename Type>
Stack<Type>::Stack(std::initializer_list<Type> lst) :
	_front(nullptr)
{
	/*
	 * Just copy all the elements.
	 */
	for (auto element : lst) {
		push(std::move(element));
	}
}

/*
 * Destructor.
 * Removes all the elements from memory.
 */
template<typename Type>
Stack<Type>::~Stack()
{
	destroy();
}

/*
 * The operator `=`.
 */
template<typename Type>
Stack<Type>& Stack<Type>::operator=(const Stack<Type>& orig)
{
	destroy();
	_count = orig._count, _empty = orig._empty;
	assign(orig._front);
	return *this;
}

/*
 * The move operator `=`.
 */
template<typename Type>
Stack<Type>& Stack<Type>::operator=(Stack<Type>&& orig) noexcept
{
	_front = orig._front, _count = orig._count, _empty = orig._empty;
	orig._front = nullptr, orig._count = 0, orig._empty = true;
	return *this;
}

/*
 * The `push` function.
 * Inserts a new element into the stack.
 * Increases the size of the stack.
 */
template<typename Type>
void Stack<Type>::push(Type&& element)
{
	node_ptr new_node(make_shared_ptr<Node>(std::forward<Type>(element), nullptr)); // a new pointer.
	if (_empty) {
		_front = new_node;
		_empty = false;
	} else {
		new_node->prev = _front; // sets the previous element.
		_front = new_node; // sets the first element.
	}
	_count++;
}

template<typename Type>
void Stack<Type>::push(const Type& element)
{
	push(Type(element));
}

/*
 * The `pop` function.
 * Removes the first element from the stack.
 * Reduces the size of the stack.
 * If the stack is empty, the result has an undefined behavior.
 */
template<typename Type>
Type Stack<Type>::pop() noexcept
{
	Type value;
	if (!_empty) {
		node_ptr old = _front;
		value = _front->value;
		_front = _front->prev;
		old.reset();
		// checks if the stack is empty.
		_empty = (--_count) == 0;
	}
	return value;
}

/*
 * The `front` function.
 * Returns the first element of the stack.
 * If the stack is empty, the result has an undefined behavior.
 */
template<typename Type>
Type Stack<Type>::front() const noexcept
{
	return _front != nullptr ? _front->value : Type();
}

/*
 * Copy all the elements to this stack.
 */
template<typename Type>
void Stack<Type>::assign(node_ptr front)
{
	if (!_empty) {
		_front = make_shared_ptr<Node>(front->value, nullptr);
		node_ptr t = _front, temp = front->prev; // gets a pointer to the previous element.
		while (temp) {
			t->prev = make_shared_ptr<Node>(temp->value, nullptr);
			temp = temp->prev;
			t = t->prev;
		}
	}
}

/*
 * Removes all the elements.
 */
template<typename Type>
void Stack<Type>::destroy()
{
	while (_front) {
		node_ptr old = _front; // a pointer to the current element.
		_front = _front->prev; // a pointer to the previous element.
		old.reset();
	}
}

/**
 * The overloaded `<<` operator for the stack.
 * Prints all the elements of the stack in the format: `(1, ...,100)`.
 * @param stream std::ostream.
 * @param s stack.
 * @return std::ostream.
 */
template<typename Type>
std::ostream& operator<<(std::ostream& stream, const Stack<Type>& s)
{
	stream << "(";
	std::size_t i = 0;
	for (auto it = s.begin(); it != s.end(); ++it) {
		stream << it->value << (i + 1 < s._count ? ", " : "");
		++i;
	}
	stream << ")";
	return stream;
}

/*
 * Constructor.
 */
template<typename Type> Stack<Type>::iterator::iterator(node_ptr node) :
	_node(node)
{}

#endif /* __cplusplus */


/*
 * A declaration the structure `stack` for C.
 */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef NULL
#define NULL ((void *)0)
#endif /* NULL */

namespace pure_c
{
/**
 * The node structure for the stack.
 */
typedef struct stack_node
{
	void * value; //! a pointer to a value.
	stack_node * prev; //! a pointer to the next node.
} stack_node;
/**
 * The structure `stack`.
 * The stack is the structure "Last-In-First-Out".
 */
typedef struct
{
	stack_node * front; //! a pointer to the first node.
	unsigned int count; //! a pointer to the last node.
	int empty;
} stack;
/**
 * The `stack_create_stack` function.
 * @return a new stack.
 */
stack * stack_create();
/**
 * Inserts a new element into the stack.
 * @param s a pointer to the stack.
 * @param element a pointer to the element.
 */
void stack_push(stack * s, const void * element);
/**
 * Removes the first element from the stack.
 * Returns a pointer to the deleted element.
 * If the stack is empty, returns the `NULL` pointer.
 * @param s a pointer to the stack.
 * @return the deleted element.
 */
void * stack_pop(stack * s);
/**
 * Returns a pointer to the first element of the stack.
 * If the stack is empty, returns the `NULL` pointer.
 * @param s - a pointer to the stack.
 * @return the first element.
 */
void * stack_front(stack * s);
/**
 * Returns the size of the stack.
 * Use this function, if necessary.
 * Or instead this function, use `stack->count`.
 * @param s a pointer to the stack.
 * @return the number of elements.
 */
unsigned int stack_count(stack * s);
/**
 * Removes the stack from memory.
 * @param s a pointer to the stack.
 */
void stack_delete(stack * s);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STACK_H */
