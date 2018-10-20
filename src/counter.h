#ifndef COUNTER_H
#define COUNTER_H

#ifdef __cplusplus
	#ifndef NULL
		#define NULL nullptr
	#endif
#endif

#ifdef __cplusplus
#include <initializer_list>
#include <map>
#include <vector>
#include <set>
#include <ostream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <ostream>


using uint = unsigned int;
using long_uint = long unsigned int;

/*
 * The `Counter` class.
 * Counts number of elements from a some sequence.
 */
template<typename T>
class Counter
{

	/*
	 * Sets the friend function for the overloaded operator `<<`.
	 */
	template<typename Type>
	friend std::ostream& operator<<(std::ostream& stream, const Counter<Type>& c);

public:

	/*
	 */
	typedef std::vector<std::pair<T, uint>> vector_t;

	/*
	 */
	typedef std::map<T, uint> map_t;

	/*
	 */
	typedef std::pair<T, uint> pair_t;

	/*
	 * Constructor.
	 * @param _begin - the iterator to the beginning of the sequence.
	 * @param _end - the iterator to the end of the sequence.
	 */
	template<typename IteratorBegin, typename IteratorEnd>
	explicit Counter(IteratorBegin _begin, IteratorEnd _end);

	/*
	 * Destructor.
	 */
	virtual ~Counter();

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
	 * @paran n - number.
	 */
	std::vector<std::pair<T, uint>> most_common(int n = -1);

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
	template<typename IteratorBegin, typename IteratorEnd>
	void update(IteratorBegin begin, IteratorEnd end);

	/*
	 * The static `map` function.
	 * Gets two iterators on the sequence.
	 * Counts number of elemnts in the sequence.
	 * Return `std::map<T, int>`: T - element, int - number of this element.
	 * For example: ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
	 * -> {'a': 4, 'c': 3, 'b': 2, 'd': 1}.
	 * @param _begin - the iterator to the beginning of the sequence.
	 * @param _end - the iterator to the end of the sequence.
	 */
	template<typename IteratorBegin, typename IteratorEnd>
	static std::map<T, uint> map(IteratorBegin _begin, IteratorEnd _end);

	/*
	 * The `size` function.
	 * Returns size of the original sequence.
	 */
	long_uint size() const noexcept
	{
		return _elements.size();
	}

private:

	/*
	 */
	using vc_it = typename std::vector<std::pair<T, uint>>::const_iterator;

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

	std::map<T, uint> _elements; // map of elements.
	std::vector<std::pair<T, uint>> _current; // a sorted vector of elements.

public:
	class iterator;

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
		explicit iterator(vc_it it, vc_it end) : _begin(it), _end(end)
		{}

	public:

        typedef T value_type; // value type.
        typedef std::forward_iterator_tag iterator_category; // iterator category

		/*
		 * Constrctor.
		 */
		iterator() : _begin(NULL) {}

		/*
		 * The prefix operator `++`.
		 * Increases the pointer and returns it.
		 */
		iterator& operator++() noexcept
		{
			_begin++;
			return *this;
		}

		/*
		 * The postfix operator `++`.
		 * Increases the pointer and returns it.
		 */
		iterator operator++(int j) noexcept
		{
			_begin++;
			return *this;
		}

		/*
		 * The operator `*`.
		 * Returns a value from the pair.
		 */
		T operator*() const noexcept
		{
			return (*_begin).first;
		}

		/*
		 * The operator `->`.
		 * Returns a pointer to the pair.
		 */
		const std::pair<T, uint> * operator->() const noexcept
		{
			return &(*_begin);
		}

		/*
		 * The operator `!=`.
		 * Compares two iterators. Returns `true` if
		 * iterators aren`t the same. Otherwise returns `false`.
		 */
		bool operator!=(const iterator& rhs) const noexcept
		{
			return _begin != rhs._begin;
		}

		/*
		 * The operator `!=`.
		 * Returns `true` if the current iterator and `nullptr`
		 * aren`t the same. Otherwise returns `false`.
		 */
		bool operator!=(std::nullptr_t) const noexcept
		{
			return _begin != _end;
		}

		/*
		 * The operator `==`.
		 * Compares two iterators. Returns `true` if
		 * iterators are the same. Otherwise returns `false`.
		 */
		bool operator==(const iterator& rhs) const noexcept
		{
			return _begin == rhs._begin;
		}

		/*
		 * The operator `==`.
		 * Returns `true` if the current iterator and `nullptr`
		 * are the same. Otherwise returns `false`.
		 */
		bool operator==(std::nullptr_t) const noexcept
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
	constexpr static Array<std::pair<T, uint>> count(IteratorBegin _begin, IteratorEnd _end);

	/*
	 * Returns the iterator to the first element of the `Counter` class.
	 */
	iterator begin() noexcept
	{
		update();
		return iterator(_current.cbegin(), _current.cend());
	}

	/*
	 * Returns the iterator to the end of the `Counter` class.
	 */
	iterator end() const noexcept
	{
		return iterator(_current.cend(), _current.cend());
	}

};

/*
 * Constructor.
 * @param _begin - the iterator to the beginning of the sequence.
 * @param _end - the iterator to the end of the sequence.
 */
template<typename T>
template<typename IteratorBegin, typename IteratorEnd> Counter<T>::Counter(IteratorBegin _begin, IteratorEnd _end) :
	_elements(),
	_current()
{
	for (auto it = _begin; it != _end; it++) {
		_elements[*it]++;
	}
}

/*
 * Destructor.
 */
template<typename T> Counter<T>::~Counter()
{
}

/*
 * The static `map` function.
 * Gets two iterators on the sequence.
 * Countes number of eleemnts in the sequence and
 * sorts it by the greater number of elements.
 * Return `std::map<T, int>`: T - element, int - number of this element.
 * For example: ('a', 'b', 'c', 'a', 'c', 'd', 'a', 'a', 'b', 'c')
 * -> {'a': 4, 'c': 3, 'b': 2, 'd': 1}.
 */
template<typename T>
template<typename IteratorBegin, typename IteratorEnd>
std::map<T, uint> Counter<T>::map(IteratorBegin _begin, IteratorEnd _end)
{
	std::map<T, uint> result;
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
template<typename T>
template<template <class ... > class Array,
         typename IteratorBegin,
         typename IteratorEnd>
constexpr Array<std::pair<T, uint>> Counter<T>::count(IteratorBegin _begin, IteratorEnd _end)
{
	std::map<T, uint> map;
	for (auto it = _begin; it != _end; it++) {
		map[*it]++;
	}
	std::vector<std::pair<T, uint>> vec;

	std::copy(map.begin(), map.end(), std::back_inserter(vec));

	constexpr auto sort_func = [](const std::pair<T, uint>& a, const std::pair<T, uint>& b) -> bool {
		return a.second > b.second;
	};

	std::sort(vec.begin(), vec.end(), sort_func);

	Array<std::pair<T, uint>> result;

	constexpr auto insert_func = [](std::pair<T, uint>&& p) -> std::pair<T, uint> {
		return p;
	};

	std::transform(std::make_move_iterator(vec.begin()),
	               std::make_move_iterator(vec.end()),
	               std::inserter(result, std::begin(result)),
	               insert_func);

	return result;
}

/*
 * The private `update` function.
 * Updates the vector of pairs and sorts it.
 */
template<typename T>
auto Counter<T>::count(int& n) -> std::pair<Counter<T>::vc_it, Counter<T>::vc_it>
{
	update();
	vc_it end = _current.end();
	if (n != -1 && static_cast<uint>(n) <= _elements.size()) {
		end = _current.begin() + n;
	}

	return std::pair<vc_it, vc_it>(_current.begin(), end);
}

/*
 */
template<typename T>
void Counter<T>::update()
{
	_current.clear();
	std::copy(_elements.begin(), _elements.end(),
	          std::back_inserter(_current));
	std::sort(_current.begin(), _current.end(),
	[](std::pair<T, uint>& a, std::pair<T, uint>& b) -> bool {
		return a.second > b.second;
	});
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
template<typename T>
std::vector<std::pair<T, uint>> Counter<T>::most_common(int n)
{
	auto iterators = count(n);
	return std::vector<std::pair<T, uint>>(iterators.first, iterators.second);
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
template<typename T>
template<typename Array>
void Counter<T>::most_common(Array& list, int n)
{
	auto iterators = count(n);
	std::transform(iterators.first, iterators.second,
	               std::inserter(list, std::begin(list)),
	[](const std::pair<T, uint>& p) -> T {
		return p.first;
	});
}

/*
 * Update the `Counter` class
 */
template<typename T>
template<typename IteratorBegin, typename IteratorEnd>
void Counter<T>::update(IteratorBegin _begin, IteratorEnd _end)
{
	for (auto it = _begin; it != _end; it++) {
		_elements[*it]++;
	}
}

/*
 * The overloaded `<<` operator for the `Counter` class.
 * Prints all the elements in the format: `{(a, 10), (b, 8) ... (h, 1)}`.
 * Returns ostream.
 */
template<typename Type>
std::ostream& operator<<(std::ostream& stream, Counter<Type>& c)
{
	stream << "{";
	for (auto it = c.begin(); it != c.end(); ++it) {
		stream << "(" << it->first << ", " << it->second << "), ";
	}
	stream << "\b\b";
	stream << "";
	stream << "}";
	return stream;
}


#endif

#endif /* COUNTER_H */
