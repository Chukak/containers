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

/*
 * The `Counter` class.
 * Counts number of elements from a some sequence.
 */
template<typename T,
         bool SortFirst = true>
class Counter
{
	/*
	 * Makes the overloaded operator `<<` friend.
	 */
	template<typename Type>
	friend std::ostream& operator<<(std::ostream& stream, const Counter<Type>& c);
public:
	/*
	 * Pair type - first - element from a some sequence, second - number of such elements
	 */
	using pair_t = std::pair<T, unsigned int>;
	/*
	 * Vector type. Contains pairs.
	 */
	using vector_t = std::vector<pair_t>;
	/*
	 * Map type. key - element from a some sequence, value - number of these elements
	 */
	using map_t = std::unordered_map<T, unsigned int>;
public:
	/*
	 * Constructor.
	 * @param _begin - the iterator to the beginning of the sequence.
	 * @param _end - the iterator to the end of the sequence.
	 */
	template<typename IteratorBegin,
	         typename IteratorEnd>
	explicit Counter(IteratorBegin _begin, IteratorEnd _end);
	/*
	 * Destructor.
	 */
	virtual ~Counter() = default;
	/*
	 * The `most_common` function.
	 * Counts number of elements in the sequence.
	 * Return vector of pairs. The pairs contains two
	 * values: (the element in the sequence, the number of such elements).
	 * For example: sequence - ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
	 * -> {('a', 4), ('c', 3), ('b', 2), ('d', 1)}.
	 * The vector of pairs is sorted by the greater number of elements.
	 * If you want to get some number of elements, you must pass a
	 * number as the first argument.
	 * @param n - number.
	 */
	vector_t most_common(int n = -1);
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
	 * @param array - your array.
	 * @param n - number.
	 */
	template<typename Array>
	void most_common(Array& list, int n = -1);
	/*
	 * Update the `Counter` class.
	 */
	template<typename IteratorBegin,
	         typename IteratorEnd>
	void update(IteratorBegin begin, IteratorEnd end);
	/*
	 * The static `map` function.
	 * Gets two iterators on the sequence.
	 * Counts number of elemnts in the sequence.
	 * Return `std::unordered_map<T, int>`: T - element, int - number of such elements.
	 * For example: ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
	 * -> {'a': 4, 'c': 3, 'b': 2, 'd': 1}.
	 * @param _begin - the iterator to the beginning of the sequence.
	 * @param _end - the iterator to the end of the sequence.
	 */
	template<typename IteratorBegin,
	         typename IteratorEnd>
	static map_t map(IteratorBegin _begin, IteratorEnd _end);
	/*
	 * The `size` function.
	 * Returns size of the counted sequence.
	 */
	inline long unsigned int size() const noexcept
	{
		return _elements.size();
	}
private:
	/*
	 * Iterator of vector type.
	 */
	using vc_it = typename vector_t::const_iterator;
	/*
	 * The private `count` function.
	 * Return pair of iterators on a sorted vector.
	 */
	auto count(int& n) -> std::pair<vc_it, vc_it>;
	/*
	 * The private `update` function.
	 * Updates the vector of pairs and sorts it.
	 */
	void update();
	/*
	 * Compares two pair
	 */
	constexpr static inline bool sort_pair(const pair_t& a, const pair_t& b) noexcept
	{
		return SortFirst && a.second == b.second ? a.first < b.first : a.second > b.second;
	}

	map_t _elements; // map of elements.
	vector_t _current; // a sorted vector of elements.
public:
	/*
	 * The `iterator` class.
	 * Implements the iterator for the `Counter` class.
	 * The iterator is `forward_iterator`.
	 */
	class iterator : public std::iterator<std::forward_iterator_tag, T>
	{
		friend class Counter<T>;
	private:
		/*
		 * Constructor.
		 */
		explicit iterator(vc_it it, vc_it end);
	public:
		using value_type = T; // value type.
		using iterator_category = std::forward_iterator_tag; // iterator category
		/*
		 * Default constrctor.
		 */
		iterator() = default;
		/*
		 * The prefix operator `++`.
		 * Increases the pointer and returns it.
		 */
		inline iterator& operator++() noexcept
		{
			_begin++;
			return *this;
		}
		/*
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 */
		inline iterator operator++([[maybe_unused]]int j) noexcept
		{
			_begin++;
			return *this;
		}
		/*
		 * The operator `*`.
		 * Returns a value from the pair.
		 */
		inline T operator*() const noexcept
		{
			return (*_begin).first;
		}
		/*
		 * The operator `->`.
		 * Returns a pointer to the pair.
		 */
		inline const pair_t * operator->() const noexcept
		{
			return &(*_begin);
		}
		/*
		 * The operator `!=`.
		 * Compares two iterators. Returns `true` if
		 * iterators aren`t the same. Otherwise returns `false`.
		 */
		inline bool operator!=(const iterator& rhs) const noexcept
		{
			return _begin != rhs._begin;
		}
		/*
		 * The operator `!=`.
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same. Otherwise returns `false`.
		 */
		inline bool operator!=(std::nullptr_t) const noexcept
		{
			return _begin != _end;
		}
		/*
		 * The operator `==`.
		 * Compares two iterators. Returns `true` if
		 * iterators are the same. Otherwise returns `false`.
		 */
		inline bool operator==(const iterator& rhs) const noexcept
		{
			return _begin == rhs._begin;
		}
		/*
		 * The operator `==`.
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same. Otherwise returns `false`.
		 */
		inline bool operator==(std::nullptr_t) const noexcept
		{
			return _begin == _end;
		}
	private:
		vc_it _begin; // the iterator of the beginning.
		vc_it _end; // the iterator of the end.
	};
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
	 * @param _begin - the iterator to the beginning of the sequence.
	 * @param _end - the iterator to the end of the sequence.
	 */
	template<template <class ... > class Array,
	         typename IteratorBegin,
	         typename IteratorEnd>
	constexpr static Array<pair_t> count(IteratorBegin _begin, IteratorEnd _end);
	/*
	 * Returns the iterator to the first element of the `Counter` class.
	 */
	inline iterator begin() noexcept
	{
		return iterator(_current.cbegin(), _current.cend());
	}
	/*
	 * Returns the iterator to the end of the `Counter` class.
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
 * Gets two iterators on the sequence.
 * Countes number of elemnts in the sequence and
 * sorts it by the greater number of elements.
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
 * Updates the vector of pairs and sorts it.
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
 * Return vector of pairs. The pairs contains two
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

/*
 * The overloaded `<<` operator for the `Counter` class.
 * Prints all the elements in the format: `{(a, 10), (b, 8) ... (h, 1)}`.
 * Returns ostream.
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
