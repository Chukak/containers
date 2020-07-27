/**
 * @file sorted_list.h
 *
 * Contains the class `sorted_list`.
 */
#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#ifdef __cplusplus
#include "extensions.h"
#include <initializer_list>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <functional>
#include <memory>

/**
 * This class implements a sorted list.
 * Saves elements in sort order.
 * To save the order of the list, the data type, which will be on the list,
 * requires the operators for elements:
 * 1) `<=` - less or equal.
 * 2) `>=` - greater or equal.
 *
 * By default, the `<=` operator is used to compare elements.
 * If the list is reverse, the `>=` operator is used.
 * @tparam Num type of elements.
 */
template<typename Num>
class sorted_list
{
    /**
     * THe node structure.
     * Used to represent elements in memory.
     */
    struct Node
    {
        friend class sorted_list<Num>;
        friend class iterator;
	template<typename T>
	friend std::ostream& operator<<(std::ostream& stream, const sorted_list<T>& list);
	/**
	 * Constructor.
	 */
	Node(Num&& e, std::shared_ptr<Node> n, std::shared_ptr<Node> p);
	Node(const Num& e, std::shared_ptr<Node> n, std::shared_ptr<Node> p);

        Num value; //! a value.
      private:
        std::shared_ptr<Node> next; //! a pointer to the next node.
        std::shared_ptr<Node> prev; //! a pointer to the previous node.
    };

  private:
    using node_ptr = std::shared_ptr<Node>;

  private:
    using custom_func = std::function<bool(Num, Num)>;
    /**
     * Makes the overloaded operator `<<` friend.
     */
    template<typename T>
    friend std::ostream& operator<<(std::ostream& stream, const sorted_list<T>& list);

  public:
    /**
     * Constructor.
     * @param func a custom function to compare elements.
     */
    explicit sorted_list(const custom_func& func = nullptr);
    /**
     * Constructor, creates the `sorted_list` class from another
     * `sorted_list` class.
     * @param orig another sorted list.
     */
    sorted_list(const sorted_list<Num>& orig);
    /**
     * Move constructor.
     * @param orig another sorted list.
     */
    sorted_list(sorted_list<Num>&& orig) noexcept;
    /**
     * Constructor.
     * @param lst initializer list.
     * @param func a custom function to compare elements.
     */
    sorted_list(std::initializer_list<Num> lst, const custom_func& func = nullptr);
    /**
     * Destructor.
     */
    virtual ~sorted_list();
    /**
     * The operator `=`.
     * @param orig the `sorted_list` class, l-value.
     * @return this class.
     */
    sorted_list<Num>& operator=(const sorted_list<Num>& orig);
    /**
     * The move operator `=`.
     * @param orig the `sorted_list` class, r-value.
     * @return this class.
     */
    sorted_list<Num>& operator=(sorted_list<Num>&& orig) noexcept;
    /**
     * Inserts a new element into the list in a special position,
     * to save the order of the list.
     * Returns the position of this element.
     * @param element - a new element.
     * @return position.
     */
    unsigned int push(Num&& element);
    /**
     * The same `insert` function, but for l-value.
     * @param element - a new element.
     * @return position.
     */
    unsigned int push(const Num& element);
    /**
     * Removes the last element from the list and returns it.
     * If the list is empty, the result has an undefined behavior.
     * @result the last element.
     */
    Num pop_back() noexcept;
    /**
     * Removes the first element from the list and returns it.
     * If the list is empty, the result has an undefined behavior.
     * @result the first element.
     */
    Num pop_front() noexcept;
    /**
     * Removes the element from a special position and returns it.
     * This function checks the range of the list. If the range
     * is invalid or the list is empty, throws the `out_of_range` exception.
     * @param pos - the position from which the element will be deleted.
     * @return an element from the position.
     */
    Num remove(int pos);
    /**
     * Returns the first element in the list.
     * If the list is empty, the result has undefined behavior.
     * @return the first element.
     */
    Num front() const noexcept;
    /**
     * Returns the back element in the list.
     * If the list is empty, the result has undefined behavior.
     * @return the last element.
     */
    Num back() const noexcept;
    /**
     * @return `true` if the order of the list is reversed, otherwise returns `false`.
     */
    inline bool is_reversed() const noexcept { return reversed; }
    /**
     * @return `true` if the list is empty, otherwise returns `false`.
     */
    inline bool is_empty() const noexcept { return _empty; }
    /**
     * Changes the order of the list on reverse.
     * For example: `{1, 2, 3}` --> `{3, 2, 1}`.
     */
    void reverse() noexcept;
    /**
     * @return the number of elements.
     */
    inline unsigned int count() const noexcept { return _count; }
    /**
     * Clears the list.
     */
    void clear() noexcept;
    /**
     * Returns an element from the position.
     * This function checks the range of the list. If the range
     * is invalid or the list is empty, throws the `out_of_range` error.
     * @param pos - a position.
     * @return an element from the position.
     */
    Num at(int pos) const;
    /**
     * Returns an element from the position.
     * This operator doesn`t checks the range of the list. If the range
     * is invalid, the result has an undefined behavior.
     * @param pos - a position.
     * @return an element from the position.
     */
    Num operator[](int pos) const noexcept;

  private:
    /**
     * Returns `true` if out of range, otherwise `false`.
     */
    inline bool is_out_of_range(int pos) const { return (pos < 0 || static_cast<unsigned int>(pos) > _count) || !(_count); }
    /**
     * Calls a custom function for comparison elements.
     * Increments the position.
     * The custom function must get 2 arguments and must return `true` or `false`.
     * For example: `[](a, b) {  return (a <= b); }`.
     */
    void push_with_custom_func(Num&& element, unsigned int& pos);
    /**
     * Copy all the elements to this list.
     */
    void assign(node_ptr front);

  private:
    node_ptr _front;        //! a pointer to the first element.
    node_ptr _back;         //! a pointer to the last element.
    unsigned int _count{0}; //! the numbers of elements.
    bool _empty{true};
    bool reversed{false};
    custom_func cmp_func;
    node_ptr last_node;       //! the last inserted node.
    unsigned int last_pos{0}; //! the last position.
  private:
    /**
     * Enumeration for selecting elements.
     * Used in the comparison function `cmp_operator`.
     */
    enum class index
    {
        FIRST, //! the first element.
        LAST,  //! the last element.
        MIDDLE //! any element between the first and last.
    };
    /**
     * The comparison function.
     * Compares the current element with a new element.
     * Used to sort elements in the list.
     */
    inline bool cmp_operator(const node_ptr& head, const Num& element, index ind = index::MIDDLE) const noexcept
    {
        switch(ind) {
        case index::LAST:
            // compares the last element.
            return (reversed ? _back->value >= element : _back->value <= element);
        case index::FIRST:
            // compares the first element.
            return (reversed ? _front->value <= element : _front->value >= element);
        case index::MIDDLE:
        default:
            // compares the middle element.
            // Calls the function `greater` if the order of the list is reversed,
            // otherwise calls the function `less`.
            return (reversed ? greater(head, element) : less(head, element));
        }
    }
    /**
     * The comparison function.
     * Used when the order of the list isn`t reversed.
     */
    inline bool less(const node_ptr& head, const Num& element) const
    {
        return (head->value <= element && head->next && head->next->value >= element);
    }
    /**
     * The comparison function.
     * Used when the order of the list is reversed.
     */
    inline bool greater(const node_ptr& head, const Num& element) const
    {
        return (head->value >= element && head->next && head->next->value <= element);
    }
    /**
     * Creates a new node, with a new value and inserts this node in
     * the special position to save the sorted order.
     */
    inline void create_new_node(const node_ptr& head, Num&& element, index i = index::MIDDLE)
    {
        switch(i) {
        // Before the first element.
        case index::FIRST: {
            node_ptr new_node = make_shared_ptr<Node>(std::forward<Num>(element), _front, nullptr);
            _front->prev = new_node; // sets the old first element.
            _front = new_node;       // changes the first element.
            break;
        }
        // After the last element.
        case index::LAST: {
            node_ptr new_node = make_shared_ptr<Node>(std::forward<Num>(element), nullptr, _back);
            _back->next = new_node; // sets the old last element.
            _back = new_node;       // changes the last element.
            break;
	}
	case index::MIDDLE:
	default: {
	    /*
	     * Creates a new node with arguments:
	     * 1) element - a new element.
	     * 2) head->next - a pointer to the next node.
	     * 3) head - a pointer to the previous node.
	     */
	    node_ptr new_node = make_shared_ptr<Node>(std::forward<Num>(element), head->next, head);
	    head->next->prev = new_node;
	    head->next = new_node;
	    break;
	}
	}
    }
    /**
     * Sets the last node which was inserted.
     */
    inline void set_last_node(const node_ptr& last, unsigned int pos) { last_node = last, last_pos = pos; }

  public:
    /**
     * Implements the iterator of the sorted list.
     * The iterator is `bidirectional_iterator`.
     */
    class iterator : public std::iterator<std::bidirectional_iterator_tag, Num>
    {
        /**
         * Makes the `sorted_list` class friend.
	 */
	friend class sorted_list<Num>;

      private:
	/**
	 * Constructor.
	 */
	explicit iterator(node_ptr node, node_ptr end);

      public:
        using value_type = Num;                                    //! iterator value type.
        using iterator_category = std::bidirectional_iterator_tag; //! iterator category
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
	 * The prefix operator `--`.
	 * Reduces the pointer and returns it.
	 * @return reduced iterator.
	 */
	inline iterator& operator--() noexcept
	{
	    _node = _node ? _node->prev : _end;
	    return *this;
	}
	/**
	 * The postfix operator `--`.
	 * Reduces the pointer and returns it.
	 * @return reduced iterator.
	 */
	inline iterator operator--([[maybe_unused]] int j) noexcept
	{
	    _node = _node ? _node->prev : _end;
	    return *this;
	}
	/**
	 * Returns a value from the pointer.
	 * @return a value.
	 */
	inline Num& operator*() const noexcept { return _node->value; }
	/**
	 * Returns a pointer to the Node.
	 * @return the node.
	 */
	inline Node* operator->() const noexcept { return _node.get(); }
	/**
	 * Compares two iterators. Returns `true` if
	 * iterators aren`t the same, otherwise `false`.
	 * @param rhs another iterator.
	 * @return result of comparison.
	 */
	inline bool operator!=(const iterator& rhs) const noexcept { return _node != rhs._node; }
	/**
	 * Returns `true` if the current iterator and `nullptr`
	 * aren`t the same, otherwise `false`.
	 * @return result of comparison.
	 */
	inline bool operator!=(std::nullptr_t) const noexcept { return _node != nullptr; }
	/**
	 * Compares two iterators. Returns `true` if
	 * iterators are the same, otherwise `false`.
	 * @param rhs another iterator.
	 * @return result of comparison.
	 */
	inline bool operator==(const iterator& rhs) const noexcept { return _node == rhs._node; }
	/**
	 * Returns `true` if the current iterator and `nullptr`
	 * are the same, otherwise `false`.
	 * @return result of comparison.
	 */
	inline bool operator==(std::nullptr_t) const noexcept { return _node == nullptr; }

      private:
        node_ptr _node; //! a pointer to a Node.
        node_ptr _end;
    };
    /**
     * Returns the iterator to the first element in the sorted list.
     * @return iterator
     */
    inline iterator begin() const noexcept { return iterator(_front, _back); }
    /**
     * Returns the iterator to the end of the sorted list.
     * The iterator points to the element after the
     * last element from the list.
     * @return iterator
     */
    inline iterator end() const noexcept { return _back ? iterator(_back->next, _back) : iterator(_back, _back); }
};

/*
 * Constructor.
 */
template<typename Num>
sorted_list<Num>::Node::Node(Num&& e, std::shared_ptr<Node> n, std::shared_ptr<Node> p) :
    value(std::forward<Num>(e)), next(n), prev(p)
{}

/*
 * Constructor.
 */
template<typename Num>
sorted_list<Num>::Node::Node(const Num& e, std::shared_ptr<Node> n, std::shared_ptr<Node> p) : value(e), next(n), prev(p)
{}

/*
 * Constructor.
 */
template<typename Num>
sorted_list<Num>::sorted_list(const custom_func& func) : _front(nullptr), _back(nullptr), cmp_func(func), last_node(nullptr)
{}

/*
 * Copy constructor.
 */
template<typename Num>
sorted_list<Num>::sorted_list(const sorted_list<Num>& orig) :
    _front(nullptr), _back(nullptr), _count(orig._count), _empty(orig._empty), cmp_func(orig.cmp_func), last_node(nullptr)
{
    assign(orig._front);
}

/*
 * Move constructor.
 */
template<typename Num>
sorted_list<Num>::sorted_list(sorted_list<Num>&& orig) noexcept :
    _front(orig._front), _back(orig._back), _count(orig._count), _empty(orig._empty), reversed(orig.reversed),
    cmp_func(orig.cmp_func), last_node(orig.last_node), last_pos(orig.last_pos)
{
    orig._front = nullptr, orig._back = nullptr;
    orig._count = 0;
    orig._empty = true, orig.reversed = false;
    orig.cmp_func = nullptr;
    orig.last_node = nullptr, orig.last_pos = 0;
}

/*
 * Constructor using initializer list.
 */
template<typename Num>
sorted_list<Num>::sorted_list(std::initializer_list<Num> lst, const custom_func& func) :
    _front(nullptr), _back(nullptr), cmp_func(func), last_node(nullptr)
{
    /*
     * Just copy all the elements.
     */
    for(auto element : lst) {
        push(element);
    }
}
/*
 * Destructor.
 * Removes all the elements from memory.
 */
template<typename Num>
sorted_list<Num>::~sorted_list()
{
    while(_front) {
        node_ptr old = _front; // a pointer to the current element.
        _front = _front->next; // a pointer to the next element.
        old->prev.reset();
        old->next.reset();
        old.reset();
    }
}

/*
 * The operator `=`.
 */
template<typename Num>
sorted_list<Num>& sorted_list<Num>::operator=(const sorted_list<Num>& orig)
{
    clear();
    assign(orig._front);
    return *this;
}

/*
 * The move operator `=`.
 */
template<typename Num>
sorted_list<Num>& sorted_list<Num>::operator=(sorted_list<Num>&& orig) noexcept
{
    _front = orig._front, _back = orig._back;
    _count = orig._count;
    _empty = orig._empty, reversed = orig.reversed;
    cmp_func = orig.cmp_func;
    last_node = nullptr, last_pos = 0;

    orig._front = nullptr, orig._back = nullptr;
    orig._count = 0;
    orig._empty = true, orig.reversed = false;
    orig.cmp_func = nullptr;
    orig.last_node = nullptr, orig.last_pos = 0;
    return *this;
}

/*
 * The `push` function.
 * Inserts a n element to the list in a special position
 * to save the order of the list.
 * Returns a position of this element.
 */
template<typename Num>
unsigned int sorted_list<Num>::push(Num&& element)
{
    unsigned int pos = 0;
    if(!_empty) {
        if(cmp_func != nullptr) {
            push_with_custom_func(std::move(element), pos);
            return pos;
        }
        /*
         * Compare the first element of the list with a new element.
         * If a new element `<` (`>` if the list is reverse)
         * than the first element, then a new element is inserted in the position `0`.
         */
        if(cmp_operator(nullptr, element, index::FIRST)) {
            create_new_node(nullptr, std::forward<Num>(element), index::FIRST);
            set_last_node(_front, pos);
        } else if(cmp_operator(nullptr, element, index::LAST)) {
            /*
             * Compare the last element from the list with a new element.
             * if a new element `>` (`<` if the list is reverse)
             * than the last element, then a new element is inserted in the last position.
             */
            create_new_node(nullptr, std::forward<Num>(element), index::LAST);
            pos = _count - 1;
            set_last_node(_back, pos);
        } else {
            /*
             * Compare all the elements from the list with a new element.
             * if a new element `<` (`>` if the list is reversed)
             * than any element, a new element is inserted in this position.
             */
            node_ptr head = last_node; // the last inserted element.
            pos = last_pos;
            while(head) {
                if(cmp_operator(head, element)) {
                    create_new_node(head, std::forward<Num>(element));
                    set_last_node(head->next, pos);
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
		++pos;
	    }
	}
    } else {
        _front = _back = make_shared_ptr<Node>(std::forward<Num>(element), nullptr, nullptr);
        _empty = false;
    }
    _count++;
    return pos;
}

template<typename Num>
unsigned int sorted_list<Num>::push(const Num& element)
{
    return push(Num(element));
}

/*
 * Calls the user function to compare elements.
 * Increments a position.
 */
template<typename Num>
void sorted_list<Num>::push_with_custom_func(Num&& element, unsigned int& pos)
{
    /*
     * Compares the first element from the list with a new element.
     * Call the custom function with 2 parameters:
     * `func(a new element, the first element)`.
     * If a new element less than the first element,
     * a new element is inserted in the position `0`.
     */
    if(cmp_func(element, _front->value)) {
        create_new_node(nullptr, std::forward<Num>(element), index::FIRST);
        set_last_node(_front, pos);
    } else if(cmp_func(_back->value, element)) {
        /*
         * Compares the last element from the list with a new element.
         * Call the custom function with 2 parameters:
         * `func(the last element, a new element)`.
         * If a new element more than the last element,
         * a new element is inserted in the last position.
         */
        create_new_node(nullptr, std::forward<Num>(element), index::LAST);
        set_last_node(_back, pos);
        pos = _count - 1;
    } else {
        /*
         * Compares all the elements of the list with a new element.
         * A new element must be more(less if the order of the list is reversed)
         * than the prevoius element. For example: 2 <= 3,
         * or if the order of the list is reversed: 3 >= 2.
	 * Call the custom function with 2 parameters:
	 * `func(the previous element, a new element)`.
	 */
	node_ptr head = last_node; // the last inserted element.
	pos = last_pos;
	/*
	 * If the last inserted element less than a new element,
	 * the insertion position located in the right side:
	 * (the last inserted element ... end of the list)
	 * Otherwise the insertion position located in the left side:
	 * (beginning of the list ... the last inserted element).
	 */
	bool right = cmp_func(last_node->value, element);
	node_ptr next = right ? last_node->next : last_node->prev; // sets the next element.

	while(head && next) {
	    if(cmp_func(head->value, element)) {
		create_new_node(head, std::forward<Num>(element));
		set_last_node(head->next, pos);
		break;
	    }

	    head = right ? head->next : head->prev;
	    next = right ? next->next : next->prev;
	    ++pos;
	}
    }
    _count++;
}

/*
 * The `pop_back` function.
 * Removes the last element from the list and returns it.
 * If the list is empty, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::pop_back() noexcept
{
    if(!_empty) {
        Num value;
        node_ptr old = _back;
        if(_back == _front) {
            if(_back) {
                value = _back->value; // gets the value of the last element.
            }
            _back = _front = nullptr;
            old.reset();
        } else {
            value = _back->value;
            /*
             * Changes the pointer to the next element.
             */
            _back->prev->next = nullptr;
            _back = _back->prev;
            old.reset();
	}
	_count--;
	_empty = _count == 0;
	return value;
    }
    return Num();
}

/*
 * The `pop_front` function.
 * Removes the first element from the list and returns this element.
 * If the list is empty, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::pop_front() noexcept
{
    if(!_empty) {
        Num value;
        node_ptr old = _front;
        if(_front == _back) {
            if(_front) {
                value = _back->value; // Gets the value of the last element.
            }
            _front = _back = nullptr;
            old.reset();
        } else {
            value = _front->value;
            /*
             * Changes the pointer to the previous element.
             */
            _front->next->prev = node_ptr(nullptr);
            _front = _front->next;
            old.reset();
	}
	_count--;
	_empty = _count == 0;
	return value;
    }
    return Num();
}

/*
 * The `remove` function.
 * Removes the element from the special position and returns it.
 * This function checks the range of the list. If the range
 * is invalid or the list is empty, throws the `out_of_range` exception.
 */
template<typename Num>
Num sorted_list<Num>::remove(int pos)
{
    // Checks the range of the list.
    // If the range is invalid, throws the `out_of_range` exception.
    if(is_out_of_range(pos)) {
        throw std::out_of_range("Error: list index out of range.");
    }
    node_ptr head = _front;
    // Gets element from the position.
    while(head && pos--) {
        head = head->next;
    }
    if(!head) {
        throw std::out_of_range("Error: list index out of range.");
    }
    node_ptr old = head;
    // Gets a value from the node.
    Num value = head->value;
    // Changes the pointer to the next element.
    if(head->prev) {
        head->prev->next = head->next;
        // if the list has only one element.
    } else {
        _front = head->next;
    }
    // Changes the pointer to the previous element.
    if(head->next) {
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
    return _front ? _front->value : Num();
}

/*
 * Returns the last element of the list.
 * If the list is empty, the result has an undefined behavior.
 */
template<typename Num>
Num sorted_list<Num>::back() const noexcept
{
    return _back ? _back->value : Num();
}

/*
 * The `reverse` function.
 * Changes the order of the list.
 */
template<typename Num>
void sorted_list<Num>::reverse() noexcept
{
    if(!_empty) {
        node_ptr t = _back, old = _back;
        // Sets the previous element.
        t = t->prev;

	// Creates the first element from the last element.
	_front = _back = make_shared_ptr<Node>(std::move(_back->value), nullptr, nullptr);
	while(t) {
	    node_ptr new_node = make_shared_ptr<Node>(std::move(t->value), nullptr, _back);
	    old = t;
	    _back->next = new_node;
	    // Sets the last element.
	    _back = new_node;
	    t = t->prev;
	    // reset left element
	    old->next.reset();
	}
    }
    reversed = !reversed;
}

/*
 * Copy all the elements to this list.
 */
template<typename Num>
void sorted_list<Num>::assign(node_ptr front)
{
    if(!_empty) {
        _front = _back = make_shared_ptr<Node>(front->value, nullptr, nullptr); // creates a new pointer.
        node_ptr t = front->next;                                               // gets a pointer to the next element.
        while(t) {
            node_ptr new_node = make_shared_ptr<Node>(t->value, nullptr, _back);
            _back->next = new_node;
            _back = new_node;
            t = t->next;
	}
    }
}

/*
 * The `clear` function.
 * Clears the list.
 */
template<typename Num>
void sorted_list<Num>::clear() noexcept
{
    while(_front) {
        node_ptr old = _front;
        _front = _front->next;
        old->prev.reset();
        old.reset();
    }
    _front = _back = nullptr;
    _count = 0;
    _empty = true, reversed = false;
    last_pos = 0, last_node = nullptr;
}

/*
 * The `at` function.
 * Returns an element from the position.
 * This function checks the range of the list. If the range
 * is invalid or the list is empty, throws the `out_of_range` exception.
 */
template<typename Num>
Num sorted_list<Num>::at(int pos) const
{
    // Checks the range of the list.
    // If the range is invalid, throws the `out_of_range` exception.
    if(is_out_of_range(pos)) {
        throw std::out_of_range("Error: list index out of range.");
    }
    node_ptr head = _front;
    // Gets element from the position.
    while(head && pos--) {
        head = head->next;
    }
    return head ? head->value : Num();
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
    node_ptr head = _front;
    while(head && pos--) {
        head = head->next;
    }
    return pos <= 0 ? head->value : Num();
}

/*
 * Constructor.
 */
template<typename Num>
sorted_list<Num>::iterator::iterator(node_ptr node, node_ptr end) : _node(node), _end(end)
{}

/**
 * The overloaded `<<` operator for the sorted list.
 * Prints all the elements of the sorted list in the format: `[1, ...,100]`.
 * @param stream std::ostream.
 * @param list the sorted list.
 * @return std::ostream.
 */
template<typename T>
std::ostream& operator<<(std::ostream& stream, const sorted_list<T>& list)
{
    auto t = list._front;
    stream << "[";
    std::size_t i = 0;
    for(auto it = list.begin(); it != list.end(); ++it) {
        stream << it->value << (i + 1 < list._count ? ", " : "");
    }
    stream << "]";
    return stream;
}

#endif /* __cplusplus */

#endif /* SORTED_LIST_H */
