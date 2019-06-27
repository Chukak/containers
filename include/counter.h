/**
 * @file counter.h
 *
 * Contains the class `Counter`.
 */
#ifndef COUNTER_H
#define COUNTER_H

#ifdef __cplusplus
#include <initializer_list>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <ostream>

/**
 * This class counts number of elements from a some sequence
 * @tparam T type of the sequence.
 * @tparam SortFirst sort by first element or not.
 */
template<typename T,
         bool SortFirst = true>
class Counter
{
	/**
	 * Makes the overloaded operator `<<` friend.
	 */
	template<typename Type>
	friend std::ostream& operator<<(std::ostream& stream, const Counter<Type>& c);
public:
	/**
	 * Pair type: first - the element from a some sequence, second - the number of such elements
	 */
	using pair_t = std::pair<T, unsigned int>;
	/**
	 * Vector type. Contains `pair_t` pairs.
	 */
	using vector_t = std::vector<pair_t>;
	/**
	 * Map type: key - the element from a some sequence, value - the number of these elements
	 */
	using map_t = std::unordered_map<T, unsigned int>;
public:
	/**
	 * Constructor.
	 * @param _begin the iterator to the beginning of the sequence.
	 * @param _end the iterator to the end of the sequence.
	 */
	template<typename IteratorBegin,
	         typename IteratorEnd>
	explicit Counter(IteratorBegin _begin, IteratorEnd _end);
	/**
	 * Destructor.
	 */
	virtual ~Counter() = default;
	/**
	 * Counts the number of elements in the sequence.
	 * Return the vector of pairs. The pairs contains two
	 * values: (the element in the sequence, the number of such elements).
	 * @code
	 * For example: sequence - ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
	 * -> {('a', 4), ('c', 3), ('b', 2), ('d', 1)}.
	 * @endcode
	 * The vector of pairs is sorted by the greater number of elements.
	 * If you want to get some number of elements, you must pass a
	 * number as the first argument.
	 * @param n the number of the first elements, by default is -1.
	 * @return the vector of pairs.
	 */
	vector_t most_common(int n = -1);
	/**
	 * The alternative `most_common` function.
	 * Counts the number of elements in the sequence and
	 * sorts this by the greater number of elements.
	 * After this, this function writes result in the array,
	 * which was passed as the first argument, but this function
	 * writes only elements in the sequence, without the number of elements.
	 * @code
	 * For example: sequence - ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
	 * -> {'a', 'c', 'b', 'd'}.
	 * @endcode
	 * Your array must have a type. For example: vector<T>.
	 * @param list your array.
	 * @param n the number of the first elements, by default is -1.
	 */
	template<typename Array>
	void most_common(Array& list, int n = -1);
	/**
	 * Adds new element to this result and recounts result.
	 * @param begin the iterator to the beginning of the sequence.
	 * @param end the iterator to the end of the sequence.
	 */
	template<typename IteratorBegin,
	         typename IteratorEnd>
	void update(IteratorBegin begin, IteratorEnd end);
	/**
	 * This function is static.
	 * Takes two iterators on the sequence.
	 * Counts the number of elements in the sequence.
	 * Return `std::unordered_map<T, int>`: T - the elements, int - the number of such elements.
	 * @code
	 * For example: ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
	 * -> {'a': 4, 'c': 3, 'b': 2, 'd': 1}.
	 * @endcode
	 * @param _begin the iterator to the beginning of the sequence.
	 * @param _end the iterator to the end of the sequence.
	 * @return map with results (`map_t` type).
	 */
	template<typename IteratorBegin,
	         typename IteratorEnd>
	static map_t map(IteratorBegin _begin, IteratorEnd _end);
	/**
	 * @return size of the counted sequence.
	 */
	inline long unsigned int size() const noexcept
	{
		return _elements.size();
	}
private:
	/**
	 * Iterator of vector type.
	 */
	using vc_it = typename vector_t::const_iterator;
	/**
	 * The private `count` function.
	 * Return the pair of iterators to the sorted vector.
	 */
	auto count(int& n) -> std::pair<vc_it, vc_it>;
	/**
	 * The private `update` function.
	 * Updates the vector of the pairs and sorts this.
	 */
	void update();
	/**
	 * Compares two pair
	 */
	constexpr static inline bool sort_pair(const pair_t& a, const pair_t& b) noexcept
	{
		return SortFirst && a.second == b.second ? a.first < b.first : a.second > b.second;
	}

	map_t _elements; //! map of elements.
	vector_t _current; //! a sorted vector of elements.
public:
	/**
	 * Implements the iterator for the `Counter` class.
	 * The iterator is `forward_iterator`.
	 */
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
		friend class Counter<T>;
	private:
		/**
		 * Constructor.
		 */
		explicit iterator(vc_it it, vc_it end);
	public:
		using value_type = T; //! iterator value type.
		using iterator_category = std::forward_iterator_tag; //! iterator category
		/**
		 * Default constrctor.
		 */
		iterator() = default;
		/**
		 * The prefix operator `++`.
		 * Increases the pointer and returns it.
		 * @return incremented iterator.
		 */
		inline iterator& operator++() noexcept
		{
			_begin++;
			return *this;
		}
		/**
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 * @return incremented iterator.
		 */
		inline iterator operator++([[maybe_unused]]int j) noexcept
		{
			_begin++;
			return *this;
		}
		/**
		 * Returns a value from the pair.
		 * @return a value
		 */
		inline T operator*() const noexcept
		{
			return (*_begin).first;
		}
		/**
		 * Returns a pointer to the node.
		 * @return the node.
		 */
		inline const pair_t * operator->() const noexcept
		{
			return &(*_begin);
		}
		/**
		 * Compares two iterators. Returns `true` if
		 * iterators aren`t the same, otherwise `false`.
		 * @param rhs another iterator
		 * @return result of comparison.
		 */
		inline bool operator!=(const iterator& rhs) const noexcept
		{
			return _begin != rhs._begin;
		}
		/**
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same, otherwise `false`.
		 * @return result of comparison.
		 */
		inline bool operator!=(std::nullptr_t) const noexcept
		{
			return _begin != _end;
		}
		/**
		 * Compares two iterators. Returns `true` if
		 * iterators are the same, otherwise `false`.
		 * @return result of comparison.
		 */
		inline bool operator==(const iterator& rhs) const noexcept
		{
			return _begin == rhs._begin;
		}
		/**
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same, otherwise `false`.
		 * @return result of comparison.
		 */
		inline bool operator==(std::nullptr_t) const noexcept
		{
			return _begin == _end;
		}
	private:
		vc_it _begin; //! the iterator of the beginning.
		vc_it _end; //! the iterator of the end.
	};
	/**
	 * This function is static.
	 * Counts the number of elements in the sequence and
	 * sorts it by the greater number of elements.
	 * Return your array of the pairs.
	 * Your array must supported by functions `std::transform` and `std::inserter`.
	 * @code
	 * For example: sequence - ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
	 * ```
	 * std::vector<Counter<std::string>::pair_t> vec = Counter<std::string>::count<std::vector>(begin(...), end(...));
	 * ```
	 * or use just
	 * ```
	 * auto vec = Counter<std::string>::count<std::vector>(begin(...), end(...));
	 * ```
	 * or use another container
	 * ```
	 * std::set<Counter<std::string>::pair_t set = Counter<std::string>::count<std::set>(begin(...), end(...));
	 * ```
	 * @endcode
	 * @param _begin - the iterator to the beginning of the sequence.
	 * @param _end - the iterator to the end of the sequence.
	 * @return your array of the pairs.
	 */
	template<template <class ... > class Array,
	         typename IteratorBegin,
	         typename IteratorEnd>
	static constexpr Array<pair_t> count(IteratorBegin _begin, IteratorEnd _end);
	/**
	 * @return the iterator to the first element of the `Counter` class.
	 */
	inline iterator begin() noexcept
	{
		return iterator(_current.cbegin(), _current.cend());
	}
	/**
	 * @return the iterator to the end of the `Counter` class.
	 */
	inline iterator end() const noexcept
	{
		return iterator(_current.cend(), _current.cend());
	}
};

/*
 * Constructor.
 * @param _begin - the iterator to the beginning of the sequence.
 * @param _end - the iterator to the end of the sequence.
 */
template<typename T,
         bool SortFirst>
template<typename IteratorBegin,
         typename IteratorEnd>
Counter<T, SortFirst>::Counter(IteratorBegin _begin, IteratorEnd _end) :
	_elements(),
	_current()
{
	for (auto it = _begin; it != _end; it++) {
		_elements[*it]++;
	}
	update();
}

/*
 * The static `map` function.
 * Takes two iterators to the sequence.
 * Counts number of elements in the sequence and
 * sorts this by the greater number of elements.
 * Return `std::map<T, int>`: T - element, int - number of this element.
 * For example: ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
 * -> {'a': 4, 'c': 3, 'b': 2, 'd': 1}.
 */
template<typename T,
         bool SortFirst>
template<typename IteratorBegin,
         typename IteratorEnd>
typename Counter<T, SortFirst>::map_t Counter<T, SortFirst>::map(IteratorBegin _begin, IteratorEnd _end)
{
	map_t result;
	for (auto it = _begin; it != _end; it++) {
		result[*it]++;
	}
	return result;
}

/*
 * The static `count` function.
 * Counts number of elements in the sequence and
 * sorts it by the greater number of elements.
 * Return your array of pairs.
 * Your array must supported by functions `std::transform` and `std::inserter`.
 * For example: sequence - ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
 * ```
 * std::vector<Counter<std::string>::pair_t> vec = Counter<std::string>::count<std::vector>(begin(...), end(...));
 * or use just
 * auto vec = Counter<std::string>::count<std::vector>(begin(...), end(...));
 * or use another container
 * std::set<Counter<std::string>::pair_t set = Counter<std::string>::count<std::set>(begin(...), end(...));
 * ```
 */
template<typename T,
         bool SortFirst>
template<template <class ... > class Array,
         typename IteratorBegin,
         typename IteratorEnd>
constexpr Array<typename Counter<T, SortFirst>::pair_t> Counter<T, SortFirst>::count(IteratorBegin _begin, IteratorEnd _end)
{
	map_t map;
	for (auto it = _begin; it != _end; it++) {
		map[*it]++;
	}
	vector_t vec(map.begin(), map.end());
	std::sort(vec.begin(), vec.end(), sort_pair);

	Array<pair_t> result;
	std::transform(std::make_move_iterator(vec.begin()),
	               std::make_move_iterator(vec.end()),
	               std::inserter(result, std::begin(result)),
	[](pair_t&& p) {
		return p;
	});
	return result;
}

/*
 * The private `update` function.
 * Updates the vector of pairs and sorts this.
 */
template<typename T,
         bool SortFirst>
auto Counter<T, SortFirst>::count(int& n) -> std::pair<Counter<T, SortFirst>::vc_it, Counter<T, SortFirst>::vc_it>
{
	vc_it end = _current.end();
	if (n != -1 && static_cast<unsigned int>(n) <= _elements.size()) {
		end = _current.begin() + n;
	}
	return std::pair<vc_it, vc_it>(_current.begin(), end);
}

/*
 * Updates the `Counter` class.
 */
template<typename T,
         bool SortFirst>
void Counter<T, SortFirst>::update()
{
	_current.clear();
	std::copy(_elements.begin(), _elements.end(), std::back_inserter(_current));
	std::sort(_current.begin(), _current.end(), sort_pair);
}

/*
 * The `most_common` function.
 * Counts number of elements in the sequence.
 * Return the vector of pairs. The pairs contains two
 * values: (the element in the sequence, the number of such elements).
 * For example: sequence - ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
 * -> {('a', 4), ('c', 3), ('b', 2), ('d', 1)}.
 * The vector of pairs is sorted by the greater number of elements.
 * If you want to get some number of elements, you must pass a
 * number as the first argument.
 */
template<typename T,
         bool SortFirst>
typename Counter<T, SortFirst>::vector_t Counter<T, SortFirst>::most_common(int n)
{
	auto iterators = count(n);
	return vector_t(iterators.first, iterators.second);
}

/*
 * The alternative `most_common` function.
 * Counts number of elements in the sequence and
 * sorts it by the greater number of elements.
 * After it, this function writes result in the array,
 * which was passed as the first argument, but this function
 * writes only elements in the sequence, without number of elements.
 * For example: sequence - ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
 * -> {'a', 'c', 'b', 'd'}.
 * Your array must have a type. For example: vector<T>.
 */
template<typename T,
         bool SortFirst>
template<typename Array>
void Counter<T, SortFirst>::most_common(Array& list, int n)
{
	auto iterators = count(n);
	std::transform(iterators.first, iterators.second,
	               std::inserter(list, std::begin(list)),
	[](const pair_t& p) {
		return p.first;
	});
}

/*
 * Update the `Counter` class
 */
template<typename T,
         bool SortFirst>
template<typename IteratorBegin,
         typename IteratorEnd>
void Counter<T, SortFirst>::update(IteratorBegin _begin, IteratorEnd _end)
{
	for (auto it = _begin; it != _end; it++) {
		_elements[*it]++;
	}
	update();
}

/*
 * Constructor.
 */
template<typename T,
         bool SortFirst>
Counter<T, SortFirst>::iterator::iterator(vc_it it, vc_it end) :
	_begin(it),
	_end(end)
{}

/**
 * The overloaded `<<` operator for the `Counter` class.
 * Prints all the elements in the format: `{(a, 10), (b, 8) ... (h, 1)}`.
 * @param stream std::ostream.
 * @param c the `Counter` class.
 * @return std::ostream.
 */
template<typename Type,
         bool SortFirst>
std::ostream& operator<<(std::ostream& stream, Counter<Type, SortFirst>& c)
{
	stream << "{";
	std::size_t i = 0;
	for (auto it = c.begin(); it != c.end(); ++it) {
		stream << "(" << it->first << ": " << it->second << ")" ;
		stream << (i + 1 < c._current.size() ? ", " : "");
		++i;
	}
	stream << "}";
	return stream;
}

#endif

#endif /* COUNTER_H */
