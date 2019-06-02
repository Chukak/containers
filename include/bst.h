#ifndef BST_H
#define BST_H

#ifdef __cplusplus
#include "extensions.h"
#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <ostream>
#include <memory>

namespace bst_exception
{
class bst_is_empty : public std::runtime_error
{
public:
	explicit bst_is_empty(const char * message = "The binary search tree is empty.");
	~bst_is_empty() final = default;
};

bst_is_empty::bst_is_empty(const char * message) :
	std::runtime_error(message)
{}
}

/*
 * The `bst` class.
 * This class implements the binary search tree.
 * The `bst` class requires operators for elements:
 * 1) `<` - less.
 * 2) `>` - greater.
 */
template<typename E>
class bst
{
	static_assert(std::disjunction_v <
	              std::is_default_constructible<E>,
	              std::is_nothrow_default_constructible<E>
	              >,
	              "Type must have a trivial constructor.");
	/*
	 * The structure `Node`.
	 * Used to representing elements in memory.
	 */
	struct Node
	{
		using ptr_t = std::shared_ptr<Node>;
		friend class bst<E>;
		friend class iterator;
		/*
		 * Сonstructor.
		 */
		Node(E&& e, ptr_t r, ptr_t l, ptr_t p);
		Node(const E& e, ptr_t r, ptr_t l, ptr_t p);
		template<typename R,
		         typename L,
		         typename P>
		Node(E&& e, R r, L l, P p) :
			data(e),
			right(r),
			left(l),
			parent(p)
		{}

		E data; // a value.
	private:
		ptr_t right; // a pointer to the right element.
		ptr_t left; // a pointer to the left element.
		ptr_t parent; // a pointer to the parent of this element.
	};

	using node_ptr = std::shared_ptr<Node>;

	friend class iterator;
	/*
	 * Makes the overloaded operator `<<` friend.
	 */
	template<typename T>
	friend std::ostream& operator<<(std::ostream& stream, const bst<E>& tree);
public:
	/*
	 * Constructor.
	 */
	bst();
	/*
	 * Copy constructor.
	 * @param orig - another `Queue` class.
	 */
	bst(const bst<E>& orig);
	/*
	 * Move constructor.
	 */
	bst(bst<E>&& orig) noexcept;
	/*
	 * Constructor, for the style `bst tree = {3, 2, 1}`.
	 */
	bst(std::initializer_list<E> lst);
	/*
	 * Destructor.
	 */
	virtual ~bst();
	/*
	 * The operator `=`.
	 */
	bst<E>& operator=(const bst<E>& orig);
	/*
	 * The mode operator `=`.
	 */
	bst<E>& operator=(bst<E>&& orig) noexcept;
	/*
	 * The `insert` function.
	 * Inserts an element into the tree. If this element less than the root
	 * of the tree, the function inserts it into the left side of the tree.
	 * If this element more than the root of the tree,
	 * the function inserts in into the right side of the tree.
	 * If this element equal to the root, it doesn`t insert into the tree.
	 * @param element - an element.
	 */
	void insert(E&& element) noexcept;
	/*
	 * The same `insert` function, but for l-value.
	 */
	void insert(const E& element) noexcept;
	/*
	 * The `remove` function.
	 * Search for an element in the tree. If an element was found,
	 * removes it from the tree.
	 * If the tree is empty, throws the `BSTIsEmpty` error.
	 * @param - an element.
	 */
	void remove(const E& element);
	/*
	 * Returns the minimum element of the tree.
	 * If the tree is empty, throws the `BSTIsEmpty` error.
	 */
	E min() const;
	/*
	 * Returns the maximum element of the tree.
	 * If the tree is empty, throws the `BSTIsEmpty` error.
	 */
	E max() const;
	/*
	 * Returns the root of the tree.
	 * If the tree is empty, throws the `BSTIsEmpty` error.
	 */
	E root() const;
	/*
	 * Returns the number of elements.
	 */
	inline unsigned int count() const noexcept
	{
		return _count;
	}
	/*
	 * Returns `true` if the tree is empty, otherwise returns `false`.
	 */
	inline bool is_empty() const noexcept
	{
		return _empty;
	}
	/*
	 * The `find` function.
	 * Search for an element in the tree. If an element was found,
	 * returns `true`, otherwise `false`.
	 * If the tree is empty, returns `false`.
	 */
	bool find(const E& element) const noexcept;
	/*
	 * The `clear` function.
	 * Clears the tree.
	 */
	void clear() noexcept;
private:
	inline void set_parent(node_ptr child, node_ptr parent) const noexcept
	{
		if (child) {
			child->parent = parent;
		}
	}
	inline void set_child(node_ptr child, node_ptr parent, bool is_left) const noexcept
	{
		if (is_left) {
			parent->left = child;
			set_parent(child, parent->left);
		} else {
			parent->right = child;
			set_parent(child, parent->right);
		}
	}
private:
	node_ptr _root; // a pointer to the root of the tree.
	unsigned int _count{0}; // the numbers of elements.
	bool _empty{true};
private:
	/*
	 * Copy all the elements from an another tree.
	 */
	void assign(node_ptr from, node_ptr& to, node_ptr parent) noexcept;
	/*
	 * Destroys all the elements in the tree.
	 */
	void destroy(node_ptr n) noexcept;
public:
	/*
	 * The `iterator` class.
	 * Implements the iterator for the tree.
	 * The iterator is `forward_iterator`.
	 */
	class iterator : public std::iterator<std::forward_iterator_tag, E>
	{
		friend class bst<E>;
	private:
		/*
		 * Constructor.
		 */
		explicit iterator(node_ptr node);
		/*
		 * Sets the next element as the current element.
		 */
		void increment() noexcept;
	public:
		// value type.
		using value_type = E;
		// iterator category
		using iterator_category = std::forward_iterator_tag;
		/*
		 * Constructor.
		 */
		iterator() : current(nullptr) {}
		/*
		 * The prefix operator `++`.
		 * Increases the pointer and returns it.
		 */
		inline iterator& operator++() noexcept
		{
			increment();
			return *this;
		}
		/*
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 */
		inline iterator operator++([[maybe_unused]] int j) noexcept
		{
			increment();
			return *this;
		}
		/*
		 * The operator `*`.
		 * Returns a value from the pointer.
		 */
		inline E& operator*() const noexcept
		{
			return current->data;
		}
		/*
		 * The operator `->`.
		 * Returns a pointer to the Node.
		 */
		inline Node * operator->() const noexcept
		{
			return current.get();
		}
		/*
		 * The operator `!=`.
		 * Compares two iterators. Returns `true` if
		 * iterators aren`t the same. Otherwise returns `false`.
		 */
		inline bool operator!=(const iterator& rhs) const noexcept
		{
			return current != rhs.current;
		}
		/*
		 * The operator `!=`.
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same. Otherwise returns `false`.
		 */
		inline bool operator!=(std::nullptr_t) const noexcept
		{
			return current != nullptr;
		}
		/*
		 * The operator `==`.
		 * Compares two iterators. Returns `true` if
		 * iterators are the same. Otherwise returns `false`.
		 */
		inline bool operator==(const iterator& rhs) const noexcept
		{
			return current == rhs.current;
		}
		/*
		 * The operator `==`.
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same. Otherwise returns `false`.
		 */
		inline bool operator==(std::nullptr_t) const noexcept
		{
			return current == nullptr;
		}
	private:
		node_ptr current; // a pointer to a Node.
	};
	/*
	 * Returns the iterator to the minimum element of the tree.
	 */
	iterator begin() const noexcept
	{
		node_ptr temp = _root;
		while (temp && temp->left) {
			temp = temp->left;
		}
		return iterator(temp);
	}
	/*
	 * Returns the iterator to the parent of the root of the tree.
	 * It is usually `nullptr`.
	 */
	inline iterator end() const noexcept
	{
		return _root ? iterator(_root->parent) : iterator(_root);
	}
};

/*
 * Сonstructor.
 */
template<typename E>
bst<E>::Node::Node(E&& e, node_ptr r, node_ptr l, node_ptr p) :
	data(std::forward<E>(e)),
	right(r),
	left(l),
	parent(p)
{}

/*
 * Сonstructor.
 */
template<typename E>
bst<E>::Node::Node(const E& e, node_ptr r, node_ptr l, node_ptr p) :
	data(e),
	right(r),
	left(l),
	parent(p)
{}

/*
 * Constructor.
 * Creates a new binary search tree.
 */
template<typename E>
bst<E>::bst() :
	_root(nullptr)
{
}


/*
 * Copy constructor.
 */
template<typename E>
bst<E>::bst(const bst<E>& orig) :
	_root(nullptr),
	_count(orig._count),
	_empty(orig._empty)
{
	assign(orig._root, _root, nullptr);
}

/*
 * Move constructor.
 */
template<typename E>
bst<E>::bst(bst<E>&& orig) noexcept :
	_root(orig._root),
	_count(orig._count),
	_empty(orig._empty)
{
	orig._root = nullptr, orig._empty = true, orig._count = 0;
}

/*
 * Constructor for the style `bst tree = {3, 5, 1}`.
 */
template<typename E>
bst<E>::bst(std::initializer_list<E> lst) :
	_root(nullptr)
{
	/*
	 * Just copy all the elements.
	 */
	for (auto e : lst) {
		insert(std::move(e));
	}
}

/*
 * Destructor.
 */
template<typename E>
bst<E>::~bst()
{
	destroy(_root);
	_root = nullptr;
}

/*
 * The operator `=`.
 */
template<typename E>
bst<E>& bst<E>::operator=(const bst<E>& orig)
{
	destroy(_root);
	_empty = orig._empty, _count = orig._count;
	assign(orig._root, _root, nullptr);
}

/*
 * The mode operator `=`.
 */
template<typename E>
bst<E>& bst<E>::operator=(bst<E>&& orig) noexcept
{
	destroy(_root);
	_root = orig._root, _empty = orig._empty, _count = orig._count;
	orig._root = nullptr, orig._empty = true, orig._count = 0;
}

/*
 * Copy all the elements from an another tree.
 */
template<typename E>
void bst<E>::assign(node_ptr from, node_ptr& to, node_ptr parent) noexcept
{
	if (from) {
		to = make_shared_ptr<Node>(from->data, nullptr, nullptr, parent);
		assign(from->right, to->right, to);
		assign(from->left, to->left, to);
	}
}

/*
 * Destroys all the elements in the tree.
 */
template<typename E>
void bst<E>::destroy(node_ptr n) noexcept
{
	if (n) {
		destroy(n->left); // destroys all left elements.
		destroy(n->right); // destroys all right elements.
		n.reset();
	}
}

/*
 * The `insert` function.
 * Inserts an element into the tree. If this element less than the root,
 * the function inserts it into the left side of the tree.
 * If an element more than the root,
 * the function inserts it into the right side of the tree.
 */
template<typename E>
void bst<E>::insert(E&& element) noexcept
{
	if (_empty) {
		// this code is `std::make_shared<Node>(Node(...))`.
		_root = make_shared_ptr<Node>(std::forward<E>(element), nullptr, nullptr, nullptr);
		_empty = false;
	} else {
		node_ptr parent(nullptr), temp(_root);
		bool is_left = false;
		while (temp) {
			if (element == temp->data) {
				// is element is in the tree.
				return;
			}
			is_left = element < temp->data;
			if (is_left) {
				// the left side of the tree.
				parent = temp;
				temp = temp->left;
			} else  {
				// the right side of the tree.
				parent = temp;
				temp = temp->right;
			}
		}

		if (is_left) {
			parent->left = make_shared_ptr<Node>(std::forward<E>(element), nullptr, nullptr, parent);
		} else {
			parent->right = make_shared_ptr<Node>(std::forward<E>(element), nullptr, nullptr, parent);
		}
	}
	++_count;
}

template<typename E>
void bst<E>::insert(const E& element) noexcept
{
	insert(E(element));
}

/*
 * The `remove` function.
 * Search for an element in the tree. If an element was found,
 * removes it from the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
 */
template<typename E>
void bst<E>::remove(const E& element)
{
	if (_empty) {
		throw bst_exception::bst_is_empty();
	}
	node_ptr temp = _root, parent = nullptr;
	bool is_left = false;
	// search for an element in the tree.
	while (temp) {
		if (temp->data == element) {
			break;
		}
		is_left = temp->data > element;
		if (is_left) {
			parent = temp;
			temp = temp->left;
		} else {
			parent = temp;
			temp = temp->right;
		}
	}
	// if an element was not found.
	if (!temp) {
		return ;
	}
	// case 1.
	// If the right child and the left child is nullptr.
	// Just removes it.
	if (!(temp->left) && !(temp->right)) {
		if (!parent) {
			if (temp == _root) {
				_root = nullptr;
				_empty = true;
			}
		} else {
			set_child(nullptr, parent, is_left);
		}
		temp.reset();
	} else if (!(temp->left) || !(temp->right)) {
		// case 2.
		// If the right child or the left child is nullptr.
		// Removes this node, and replaces it with the right or left child.
		node_ptr child = temp->left ? temp->left : temp->right;
		if (!parent) {
			if (temp == _root) {
				_root = child;
			}
		} else {
			set_child(child, parent, is_left);
		}
		temp.reset();
	} else {
		// case 3.
		// If the right child and the left child is not nullptr.
		// Removes this Node, and replaces it with the left child.
		// And replaces the left child with the right child.
		node_ptr parent_rep_node = temp, rep_node = temp->left;
		is_left = true;
		while (rep_node->right) {
			parent_rep_node = rep_node;
			rep_node = rep_node->right;
			is_left = false;
		}
		temp->data = rep_node->data;
		if (is_left) {
			if (!rep_node->right) {
				temp->left = rep_node->left;
				set_parent(rep_node->left, temp->left);
			}
		} else {
			parent_rep_node->right = rep_node->left;
			set_parent(rep_node->left, parent_rep_node->right);
		}
		rep_node.reset();
	}
	--_count;
	//_empty = _count == 0;
}

/*
 * Returns the minimum element of the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
 */
template<typename E>
E bst<E>::min() const
{
	if (_empty) {
		throw bst_exception::bst_is_empty();
	}
	if (!_root->left) {
		return _root->data;
	}
	node_ptr temp = _root->left;
	while (temp->left) {
		temp = temp->left;
	}
	return temp->data;
}

/*
 * Returns the maximum element of the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
 */
template<typename E>
E bst<E>::max() const
{
	if (_empty) {
		throw bst_exception::bst_is_empty();
	}
	if (!_root->right) {
		return _root->data;
	}
	node_ptr temp = _root->right;
	while (temp->right) {
		temp = temp->right;
	}
	return temp->data;
}

/*
 * Returns the root of the tree.
 * If the tree is empty, throws the `BSTIsEmpty` error.
 */
template<typename E>
E bst<E>::root() const
{
	if (_empty) {
		throw bst_exception::bst_is_empty();
	}
	return _root->data;
}

/*
 * The `find` function.
 * Search for an element in the tree. If an element was found,
 * returns `true`, otherwise `false`.
 * If the tree is empty, returns `false`.
 */
template<typename E>
bool bst<E>::find(const E& element) const noexcept
{
	node_ptr temp = _root;
	while (temp) {
		if (element == temp->data) {
			return true;
		}
		if (element < temp->data) {
			temp = temp->left;
		} else {
			temp = temp->right;
		}
	}
	return false;
}

/*
 * Clears the tree.
 */
template<typename E>
void bst<E>::clear() noexcept
{
	if (_empty) {
		return ;
	}
	destroy(_root);
	_root = nullptr;
	_count = 0;
	_empty = true;
}

/*
 * Constructor.
 */
template<typename E>
bst<E>::iterator::iterator(node_ptr node) :
	current(node)
{}

/*
 * Sets the next element as the current element.
 */
template<typename E>
void bst<E>::iterator::increment() noexcept
{
	// checks the right child.
	if (current->right) {
		current = current->right;
		// find the minimum element of the right child.
		while (current->left) {
			current = current->left;
		}
	} else {
		node_ptr parent = current->parent; // parent.
		while (parent && current == parent->right) {
			current = parent;
			parent = parent->parent;
		}
		// if all the elements is visited.
		if (!parent) {
			current = parent;
			return ;
		}
		if (current->right != parent) {
			current = parent;
		}
	}
}

/*
 * The overloaded `<<` operator for the binary search tree.
 * Prints all elements from the binary search tree
 * in the format: `[1, ...,100]`.
 * Returns ostream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, const bst<T>& tree)
{
	stream << "[";
	std::size_t i = 0;
	for (auto it = tree.begin(); it != tree.end(); it++) {
		stream << it->data << ( i + 1 < tree._count ? ", " : "");
		++i;
	}
	stream << "]";
	return stream;
}

#endif /* __cplusplus */

#endif /* BST_H */