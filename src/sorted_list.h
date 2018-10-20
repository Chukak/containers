#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#ifndef NULL
	#ifdef __cplusplus
		#define NULL nullptr
	#endif
#endif

#ifdef __cplusplus
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <functional>
#include <memory>

using uint = unsigned int;

/*
 * The `sorted_list` class.
 * Saves elements in sort order.
 * To save the order of the list, the data type, which will be on the list,
 * requires the operators for elements:
 * 1) `<=` - less or equal.
 * 2) `>=` - greater or equal.
 *
 * By default, the `<=` operator is used to compare elements.
 * If the list is reverse, the `>=` operator is used.
 */
template<typename Num>
class sorted_list
{

	using custom_func = std::function<bool(Num, Num, Num)>;

	/*
	 * Sets the friend function for the overloaded operator `<<`.
	 */
	template<typename T>
	friend std::ostream& operator<<(std::ostream& stream,
	                                const sorted_list<T>& list);

public:

	/*
	 * Constructor.
	 * @param func - a custom function to compare elements.
	 */
	explicit sorted_list(const custom_func& func = nullptr);

	/*
	 * Constructor, creates the `sorted_list` class from another
	 * `sorted_list` class.
	 * @param orig - another `sorted_list` class.
	 */
	sorted_list(const sorted_list<Num>& orig);

	/*
	 * The operator `=`.
	 */
	sorted_list<Num>& operator=(const sorted_list<Num>& orig);

	/*
	 * Move constructor.
	 */
	sorted_list(sorted_list<Num>&& orig);

	/*
	 * Constructor, for the style `sorted_list list = {3, 2, 1}`.
	 * @param func - a custom function to compare elements.
	 */
	sorted_list(std::initializer_list<Num> lst, const custom_func& func = nullptr);

	/*
	 * Destructor.
	 */
	virtual ~sorted_list();

	/*
	 * The `push` function.
	 * Inserts an element into the list in a special position,
	 * to save the order of the list.
	 * Returns the position of this element.
	 * @param element - an element.
	 */
	uint push(Num&& element);

	/*
	 * The same `insert` function, but for l-value.
	 */
	uint push(const Num& element);

	/*
	 * The `pop_back` function.
	 * Removes the last element of the list and returns it.
	 * If the list is empty, the result has an undefined behavior.
	 */
	Num pop_back() noexcept;

	/*
	 * The `pop_front` function.
	 * Removes the first element of the list and returns it.
	 * If the list is empty, the result has an undefined behavior.
	 */
	Num pop_front() noexcept;

	/*
	 * The `remove` function.
	 * Removes the element from a special position and returns it.
	 * This function checks the range of the list. If the range
	 * is invalid or the list is empty, throws the `out_of_range` error.
	 * @param pos - the position from which the element will be deleted.
	 */
	Num remove(int pos);

	/*
	 * Returns the first element of the list.
	 * If the list is empty, the result has undefined behavior.
	 */
	Num front() const noexcept;

	/*
	 * Returns the back element of the list.
	 * If the list is empty, the result has undefined behavior.
	 */
	Num back() const noexcept;

	/*
	 * Returns `true` if the order of the list is reversed, otherwise returns `false`.
	 */
	bool is_reversed() const noexcept
	{
		return reversed;
	}

	/*
	 * Returns `true` if the list is empty, otherwise returns `false`.
	 */
	bool is_empty() const noexcept
	{
		return empty;
	}

	/*
	 * The `reverse` function.
	 * Changes the order of the list on reverse.
	 * For example: `{1, 2, 3}` --> `{3, 2, 1}`.
	 */
	void reverse() noexcept;

	/*
	 * Returns the number of elements.
	 */
	uint count() const noexcept
	{
		return _count;
	}

	/*
	 * The `clear` function.
	 * Clears the list.
	 */
	void clear() noexcept;

	/*
	 * The `at` function.
	 * Returns an element from the position.
	 * This function checks the range of the list. If the range
	 * is invalid or the list is empty, throws the `out_of_range` error.
	 * @param pos - a position.
	 */
	Num at(int pos) const;

	/*
	 * The operator `[]`.
	 * Returns an element from the position.
	 * This operator doesn`t checks the range of the list. If the range
	 * is invalid, the result has an undefined behavior.
	 * @param pos - a position.
	 */
	Num operator[](int pos) const noexcept;

private:

	/*
	 * Returns a result which will have an undefined behavior.
	 */
	Num undefined_behavior() const noexcept
	{
		return Num();
	}

	/*
	 * Returns `true` if out of range, otherwise `false`.
	 */
	bool is_out_of_range(int pos) const
	{
		return (pos < 0 || static_cast<uint>(pos) > _count)
		       || !(_count);
	}

	/*
	 * Calls a custom function for comparison elements.
	 * Increments the position.
	 * @param element - an element.
	 * @param pos - a pointer to the position.
	 * The custom function must get 3 arguments and must return `true` or `false`.
	 * For example: `[](a, b, c) {  return (a <= b && b <= c); }`.
	 */
	void push_with_custom_func(Num&& element, uint * pos);

	/*
	 * A linked list structure.
	 * Used to represent elements in memory.
	 */
	struct Node {
		friend class sorted_list<Num>;

		friend class iterator;

		template<typename T>
		friend std::ostream& operator<<(std::ostream& stream,
		                                const sorted_list<T>& list);

		Num value; // a value.
	private:
		std::shared_ptr<Node> next; // a pointer to the next node.
		std::shared_ptr<Node> prev; // a pointer to the previous node.

		/*
		 * Constructor.
		 */
		Node(Num&& e, std::shared_ptr<Node> n,
		     std::shared_ptr<Node> p) :
			value(e),
			next(n),
			prev(p)
		{}

	public:
		Node() :
			value(),
			next(nullptr),
			prev(nullptr)
		{}
		~Node() {}
	};

	using sptr = std::shared_ptr<Node>;

	/*
	 * Pseudonym for code: `std::make_shared<Node>(Node(...))`.
	 */
	template<typename... Args>
	auto make_sptr(Args&& ... args)
	-> decltype(std::make_shared<Node>(std::forward<Args>(args)...))
	{
		return std::make_shared<Node>(std::forward<Args>(args)...);
	}

	sptr _front; // a pointer to the first element.
	sptr _back; // a pointer to the last element.
	uint _count; // the numbers of elements.
	bool empty;
	bool reversed;
	custom_func cmp_func;
	sptr last_node; // the last inserted node.
	uint last_pos; // the last position.

private:

	/*
	 * Enumeration for selecting elements.
	 * Used in the comparison function `cmp_operator`.
	 */
	enum class index {
		FIRST, // the first element.
		LAST, // the last element.
		MIDDLE // any element between the first and last.
	};

	/*
	 * The comparison function.
	 * Compares the current element with a new element.
	 * Used to sort elements in the list.
	 * @param head - the current node
	 * @param element - a new element
	 * @param ind - a selected element, first, last, or middle.
	 */
	bool cmp_operator(const sptr& head, const Num& element,
	                  index ind = index::MIDDLE) const noexcept
	{
		if (ind == index::LAST) {
			// compares the last element.
			return (reversed ? _back->value >= element : _back->value <= element);
		} else if (ind == index::FIRST) {
			// compares the first element.
			return (reversed ? _front->value <= element : _front->value >= element);
		} else {
			// compares the middle element.
			// Calls the function `greater` if the order of the list is reversed,
			// otherwise calls the function `less`.
			return (reversed ? greater(head, element) : less(head, element));
		}
	}

	/*
	 * The comparison function.
	 * Used when the order of the list isn`t reversed.
	 * @param head - the current node.
	 * @param element - a new element.
	 */
	bool less(const sptr& head, const Num& element) const
	{
		return (head->value <= element &&
		        head->next &&
		        head->next->value >= element);
	}

	/*
	 * The comparison function.
	 * Used when the order of the list is reversed.
	 * @param head - the current node.
	 * @param element - a new element.
	 */
	bool greater(const sptr& head, const Num& element) const
	{
		return (head->value >= element &&
		        head->next &&
		        head->next->value <= element);
	}

	/*
	 * Creates a new node, with a new value and inserts this node in
	 * the special position to save the sorted order.
	 */
	void create_new_node(const sptr& head, Num&& element,
	                     index i = index::MIDDLE)
	{
		switch (i) {
		// Before the first element.
		case index::FIRST: {
			sptr new_node = make_sptr(Node(std::move(element), _front, NULL));
			_front->prev = new_node; // sets the old first element.
			_front = new_node; // changes the first element.
			break;
		}
		// After the las element.
		case index::LAST: {
			sptr new_node = make_sptr(Node(std::move(element), NULL, _back));
			_back->next = new_node; // sets the old last element.
			_back = new_node; // changes the last element.
			break;
		}
		case index::MIDDLE: {
			/*
			     * Creates a new node with arguments:
			     * 1) element - a new element.
			     * 2) head->next - a pointer to the next node.
			     * 3) head - a pointer to the previous node.
			     */
			sptr new_node = make_sptr(Node(std::move(element), head->next, head));
			head->next->prev = new_node;
			head->next = new_node;
			break;
		}
		default:
			break;
		}
	}

	/*
	 * Sets the last node which was inserted.
	 */
	void set_last_node(sptr&& last, uint pos)
	{
		last_node = last;
		last_pos = pos;
	}

public:
	class iterator;

	/*
	 * The `iterator` class.
	 * Implements the iterator for the sorted list.
	 * The iterator is `bidirectional_iterator`.
	 */
	class iterator : public std::iterator<std::bidirectional_iterator_tag, Num>
	{

		friend class sorted_list<Num>;

	private:
		/*
		 * Constructor.
		 */
		explicit iterator(sptr node, sptr end) : m_node(node), _end(end) {}

	public:
		// value type.
		typedef Num value_type;
		// iterator category
		typedef std::bidirectional_iterator_tag iterator_category;

		/*
		 * Constructor.
		 */
		iterator() : m_node(nullptr), _end(nullptr) {}

		/*
		 * Destructor.
		 */
		~iterator() {}

		/*
		 * The prefix operator `++`.
		 * Increases the pointer and returns it.
		 */
		iterator& operator++() noexcept
		{
			m_node = m_node->next;
			return *this;
		}

		/*
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 */
		iterator operator++([[maybe_unused]] int j) noexcept
		{
			m_node = m_node->next;
			return *this;
		}

		/*
		 * The prefix operator `--`.
		 * Reduces the pointer and returns it.
		 */
		iterator& operator--() noexcept
		{
			if (m_node == nullptr ||
			        m_node == NULL) {
				m_node = _end;
			} else {
				m_node = m_node->prev;
			}
			return *this;
		}

		/*
		 * The postfix operator `--`.
		 * Reduces the pointer and returns it.
		 */
		iterator operator--(int j) noexcept
		{
			if (m_node == nullptr ||
			        m_node == NULL) {
				m_node = _end;
			} else {
				m_node = m_node->prev;
			}
			return *this;
		}

		/*
		 * The operator `*`.
		 * Returns a value from the pointer.
		 */
		Num& operator*() const noexcept
		{
			return m_node->value;
		}

		/*
		 * The operator `->`.
		 * Returns a pointer to the Node.
		 */
		Node * operator->() const noexcept
		{
			return m_node.get();
		}

		/*
		 * The operator `!=`.
		 * Compares two iterators. Returns `true` if
		 * iterators aren`t the same. Otherwise returns `false`.
		 */
		bool operator!=(const iterator& rhs) const noexcept
		{
			return m_node != rhs.m_node;
		}

		/*
		 * The operator `!=`.
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same. Otherwise returns `false`.
		 */
		bool operator!=(std::nullptr_t) const noexcept
		{
			return m_node != nullptr;
		}

		/*
		 * The operator `==`.
		 * Compares two iterators. Returns `true` if
		 * iterators are the same. Otherwise returns `false`.
		 */
		bool operator==(const iterator& rhs) const noexcept
		{
			return m_node == rhs.m_node;
		}

		/*
		 * The operator `==`.
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same. Otherwise returns `false`.
		 */
		bool operator==(std::nullptr_t) const noexcept
		{
			return m_node == nullptr;
		}

	private:
		sptr m_node; // a pointer to a Node.
		sptr _end;
	};

	/*
	 * Returns the iterator to the first element of the sorted list.
	 */
	iterator begin() const noexcept
	{
		return iterator(_front, _back);
	}

	/*
	 * Returns the iterator to the end of the sorted list.
	 * The iterator points to the element after the
	 * last element from the list.
	 */
	iterator end() const noexcept
	{
		return _back ? iterator(_back->next, _back) : iterator(_back, _back);
	}
};

/*
 * Constructor.
 * Creates a new `sorted_list` class.
 */
template<typename Num> sorted_list<Num>::sorted_list(const custom_func& func) :
	_front(sptr(NULL)),
	_back(sptr(NULL)),
	_count(0),
	empty(true),
	reversed(false),
	cmp_func(func),
	last_node(sptr(NULL)),
	last_pos(0)
{
}

/*
 * Constructor.
 * Creates a new `sorted_list` class from another `sorted_list` class.
 */
template<typename Num> sorted_list<Num>::sorted_list(const sorted_list<Num>& orig) :
	_front(sptr(NULL)),
	_back(sptr(NULL)),
	_count(orig._count),
	empty(false),
	reversed(false),
	cmp_func(orig.cmp_func),
	last_node(sptr(NULL)),
	last_pos(0)
{
	/*
	 * If an original class is empty, returns from constructor.
	 */
	if (orig.empty) {
		empty = true;
		return ;
	}
	sptr t = orig._front; // copy a pointer to the first element.
	_front = make_sptr(Node(std::move(t->value), NULL, NULL)); // creates a new pointer.
	_back = _front;
	t = t->next; // gets a pointer to the next element.
	while (t) {
		sptr new_node = make_sptr(Node(std::move(t->value), NULL, _back));
		_back->next = new_node;
		_back = new_node;
		t = t->next;
	}
}

/*
 * The operator `=`.
 */
template<typename Num>
sorted_list<Num>& sorted_list<Num>::operator=(const sorted_list<Num>& orig)
{
	if (this == &orig) {
		return *this;
	}
	_front = orig._front;
	_back = orig._back;
	_count = orig._count;
	empty = orig.empty;
	reversed = orig.reversed;
	cmp_func = orig.cmp_func;
	last_node = sptr(NULL);
	last_pos = 0;
	return *this;
}

/*
 * Move constructor.
 */
template<typename Num> sorted_list<Num>::sorted_list(sorted_list<Num>&& orig) :
	_front(orig._front),
	_back(orig._back),
	_count(orig._count),
	empty(orig.empty),
	reversed(orig.reversed),
	cmp_func(orig.cmp_func),
	last_node(sptr(NULL)),
	last_pos(0)
{
	orig._front = sptr(NULL);
	orig._back = sptr(NULL);
	orig._count = 0;
	orig.empty = true;
	orig.reversed = false;
	orig.cmp_func = nullptr;
	orig.last_node = sptr(NULL);
	orig.last_pos = 0;
}

/*
 * Constructor for the style `sorted_list list = {3, 5, 1}`.
 */
template<typename Num> sorted_list<Num>::sorted_list(std::initializer_list<Num> lst,
        const custom_func& func) :
	_front(sptr(NULL)),
	_back(sptr(NULL)),
	_count(0),
	empty(true),
	reversed(false),
	cmp_func(func),
	last_node(sptr(NULL)),
	last_pos(0)
{
	/*
	 * Just copy all the elements.
	 */
	for (auto element : lst) {
		push(element);
	}
}

/*
 * Destructor.
 * Removes all the elements from memory.
 */
template<typename Num> sorted_list<Num>::~sorted_list()
{
	while (_front) {
		sptr old = _front; // a pointer to the current element.
		_front = _front->next; // a pointer to the next element.
		old.reset();
	}
}

/*
 * The `push` function.
 * Inserts an element to the list in a special position
 * to save the order of the list.
 * Returns a position of this element.
 */
template<typename Num>
uint sorted_list<Num>::push(Num&& element)
{
	uint pos = 0;
	if (!empty) {
		if (cmp_func != nullptr) {
			push_with_custom_func(std::move(element), &pos);
			return pos;
		}
		/*
		 * Compare the first element of the list with a new element.
		 * if a new element `<` (`>` if the list is reverse)
		 * than the first element, a new element inserts in the position `0`.
		 */
		if (cmp_operator(sptr(NULL), std::move(element), index::FIRST)) {
			create_new_node(sptr(NULL), std::move(element), index::FIRST);
			set_last_node(std::move(_front), pos);
			/*
			 * Compare the last element from the list with a new element.
			 * if a new element `>` (`<` if the list is reverse)
			 * than the last element, a new element inserts in the last position.
			 */
		} else if (cmp_operator(sptr(NULL), std::move(element), index::LAST)) {
			create_new_node(sptr(NULL), std::move(element), index::LAST);
			pos = _count - 1;
			set_last_node(std::move(_back), pos);
		} else {
			/*
			 * Compare all the elements from the list with a new element.
			 * if a new element `<` (`>` if the list is reverse)
			 * than any element, a new element inserts in this position.
			 */
			sptr head = last_node; // the last inserted element.
			pos = last_pos;

			while (head) {
				if (cmp_operator(head, element)) {
					create_new_node(head, std::move(element));
					set_last_node(std::move(head->next), pos);
					break;
				}
				/*
				 * If the last inserted element less than a new element,
				 * the insertion position located in the right side:
				 * (the last inserted element ... end of the list)
				 * Otherwise the insertion position located in the left side:
				 * (beginning of the list ... the last inserted element).
				 */
				head = (last_node->value <= element) ? head->next : head->prev;
				pos++;
			}
		}
	} else {
		sptr new_node = make_sptr(Node(std::move(element), NULL, NULL));
		_front = new_node;
		_back = new_node;
		empty = false;
	}
	_count++;
	return pos;
}

template<typename Num>
uint sorted_list<Num>::push(const Num& element)
{
	return push(std::move(std::remove_const_t<Num>(element)));
}

/*
 * Calls the user function to compare elements.
 * Increments a position.
 */
template<typename Num>
void sorted_list<Num>::push_with_custom_func(Num&& element, uint * pos)
{
	/*
	 * Compare the first element from the list with a new element.
	 * Call the custom function with 3 parameters:
	 * `func(a new element, the first element, the first element)`.
	 * If a new element less than the first element,
	 * a new element inserts in the position `0`.
	 */
	if (cmp_func(element, _front->value, _front->value)) {
		create_new_node(sptr(NULL), std::move(element), index::FIRST);
		set_last_node(std::move(_front), *pos);
		/*
		 * Compare the last element from the list with a new element.
		 * Call the custom function with 3 parameters:
		 * `func(the last element, a new element, a new element)`.
		 * If a new element more than the last element,
		 * a new element inserts in the last position.
		 */
	} else if (cmp_func(_back->value, element, element)) {
		create_new_node(sptr(NULL), std::move(element), index::LAST);
		set_last_node(std::move(_back), *pos);
		*pos = _count - 1;
	} else {
		/*
		 * Compare all the elements of the list with a new element.
		 * A new element must be more/equal(less/equal if the order of the list is reversed)
		 * than the prevoius element, and
		 * less/equal(more/equal) than the next element. For example: 2 <= 3 <= 4,
		 * or if the order of the list is reversed: 4 => 3 >= 2.
		 * Call the custom function with 3 parameters:
		 * `func(the previous element, a new element, the next element)`.
		 */
		sptr head = last_node; // the last inserted element.
		*pos = last_pos;
		/*
		 * If the last inserted element less than a new element,
		 * the insertion position located in the right side:
		 * (the last inserted element ... end of the list)
		 * Otherwise the insertion position located in the left side:
		 * (beginning of the list ... the last inserted element).
		 */
		bool right = cmp_func(last_node->value, element, _back->value);
		sptr next = right ? last_node->next : last_node->prev; // sets the next element.

		while (head && next) {
			if (cmp_func(head->value, element, head->next->value)) {
				create_new_node(head, std::move(element));
				set_last_node(std::move(head->next), *pos);
				break;
			}

			head = right ? head->next : head->prev;
			next = right ? next->next : next->prev;
			(*pos)++;
		}
	}
	_count++;
}

/*
 * The `pop_back` function.
 * Removes the last element of the list and returns it.
 * If the list is empty, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::pop_back() noexcept
{
	if (!empty) {
		Num value;
		sptr old = _back;
		if (_back == _front) {
			// Gets the value of the last element.
			if (_back) {
				value = _back->value;
			}
			// Removes the element from memory.
			_back = sptr(NULL);
			_front = sptr(NULL);
			old.reset();
		} else {
			value = _back->value;
			/*
			 * Changes the pointer to the next element.
			 */
			_back->prev->next = sptr(NULL);
			_back = _back->prev;
			old.reset();
		}
		_count--;
		empty = _count == 0 ? true : false;
		return value;
	}
	// Returns it, is the list is empty.
	return undefined_behavior();
}

/*
 * The `pop_front` function.
 * Removes the first element of the list and returns it.
 * If the list is empty, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::pop_front() noexcept
{
	if (!empty) {
		Num value;
		sptr old = _front;
		if (_front == _back) {
			// Gets the value of the last element.
			if (_front) {
				value = _back->value;
			}
			// Removes the element from memory.
			_front = sptr(NULL);
			_back = sptr(NULL);
			old.reset();
		} else {
			value = _front->value;
			/*
			 * Changes the pointer to the previous element.
			 */
			_front->next->prev = sptr(NULL);
			_front = _front->next;
			old.reset();
		}
		_count--;
		empty = _count == 0 ? true : false;
		return value;
	}
	// Returns it, is the list is empty.
	return undefined_behavior();
}

/*
 * The `remove` function.
 * Removes the element from a special position and returns it.
 * This function checks the range of the list. If the range
 * is invalid or the list is empty, throws the `out_of_range` error.
 */
template<typename Num>
Num sorted_list<Num>::remove(int pos)
{
	// Checks the range of the list.
	// If the range is invalid, throws the `out_of_range` error.
	if (is_out_of_range(pos)) {
		throw std::out_of_range("Error: list index out of range.");
	}
	sptr head = _front;
	// Gets element from the position.
	while (head && pos--) {
		head = head->next;
	}
	sptr old = head;
	// Gets a value from the element.
	Num value = head->value;
	// Changes the pointer to the next element.
	if (head->prev) {
		head->prev->next = head->next;
		// if the list has only one element.
	} else {
		_front = head->next;
	}
	// Changes the pointer to the previous element.
	if (head->next) {
		head->next->prev = head->prev;
		// if the list has only one element.
	} else {
		_back = head->prev;
	}
	old.reset();
	_count--;
	return value;
}

/*
 * Returns the first element of the list.
 * If the list is empty, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::front() const noexcept
{
	return _front ? _front->value : undefined_behavior();
}

/*
 * Returns the last element of the list.
 * If the list is empty, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::back() const noexcept
{
	return _back ? _back->value : undefined_behavior();
}

/*
 * The `reverse` function.
 * Changes the order of the list.
 */
template<typename Num>
void sorted_list<Num>::reverse() noexcept
{
	if (!empty) {
		sptr t = _back;
		sptr old = _back;
		// Creates the first element from the last element.
		_front = make_sptr(Node(std::move(t->value), NULL, NULL));
		// Removes the last element.
		old.reset();
		_back = _front;
		// Sets the previous element.
		t = t->prev;
		while (t) {
			sptr new_node = make_sptr(Node(std::move(t->value), NULL, _back));
			old = t;
			_back->next = new_node;
			// Sets the last element.
			_back = new_node;
			t = t->prev;
			old.reset();
		}
	}
	reversed = reversed ? false : true;
}

/*
 * The `clear` function.
 * Clears the list.
 */
template<typename Num>
void sorted_list<Num>::clear() noexcept
{
	while (_front) {
		sptr old = _front;
		_front = _front->next;
		old.reset();
	}
	_front = sptr(NULL);
	_back = sptr(NULL);
	_count = 0;
	empty = true;
	reversed = false;
}

/*
 * The `at` function.
 * Returns an element from the position.
 * This function checks the range of the list. If the range
 * is invalid or the list is empty, throws the `out_of_range` error.
 */
template<typename Num>
Num sorted_list<Num>::at(int pos) const
{
	// Checks the range of the list.
	// If the range is invalid, throws the `out_of_range` error.
	if (is_out_of_range(pos)) {
		throw std::out_of_range("Error: list index out of range.");
	}
	sptr head = _front;
	// Gets element from the position.
	while (head && pos--) {
		head = head->next;
	}
	return head->value;
}

/*
 * The operator `[]`.
 * Returns an element from the position.
 * This function doesn`t checks the range of list. If the range
 * is invalid, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::operator[](int pos) const noexcept
{

	sptr head = _front;
	while (head && pos--) {
		head = head->next;
	}
	return pos <= 0 ? head->value : undefined_behavior();
}

/*
 * The overloaded `<<` operator for the sorted list.
 * Prints all the elements of the sorted list in the format: `[1, ...,100]`.
 * Returns ostream.
 */
template<typename Num>
std::ostream& operator<<(std::ostream& stream, const sorted_list<Num>& list)
{
	auto t = list._front;
	stream << "[";
	while (t) {
		stream << t->value << ", ";
		t = t->next;
	}
	stream << "\b\b";
	stream << "";
	stream << "]";
	return stream;
}

#endif /* __cplusplus */

#endif /* SORTED_LIST_H */
