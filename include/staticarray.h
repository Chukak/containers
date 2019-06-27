/**
 * @file staticarray.h
 *
 * Contains the class `StaticArray`.
 */
#ifndef STATICARRAY_H
#define STATICARRAY_H

#ifdef __cplusplus
#include "extensions.h"
#include <type_traits>
#include <utility>

/**
 * The `StaticArray` class.
 * This class a bit like std::array, which you can use at compile time.
 * @tparam T type of elements.
 * @tparam Size size of array.
 */
template<typename T,
         std::size_t Size>
class StaticArray
{
	static_assert(std::disjunction_v <
	              std::is_default_constructible<T>,
	              std::is_nothrow_default_constructible<T>
	              >,
	              "Type must have a trivial constructor.");
public:
	/**
	 * Constructor.
	 */
	constexpr StaticArray() noexcept;
	/**
	 * Constructor with arguments. Use this by default.
	 * @code
	 * For example: constexpr StaticArray<int, 2> a = {1, 2};.
	 * @endcode
	 */
	template<typename ... Args,
	         std::enable_if_t<
	             std::conjunction_v<
	                 std::is_same<T, Args>...
	                 >
	             > * = nullptr
	         >
	constexpr StaticArray(Args && ... list) noexcept;
	constexpr StaticArray(const StaticArray& a) = delete;
	constexpr StaticArray(StaticArray&& a) = delete;
	/**
	 * Destructor.
	 */
	~StaticArray() noexcept = default;

	constexpr StaticArray& operator=(const StaticArray& a) = delete;
	constexpr StaticArray& operator=(StaticArray&& a) = delete;
	/**
	 * The `operator[]`. Takes an integral constant with std::size_t type.
	 * This method will check ranges!
	 * @param i index. For example: array[Index<I>()].
	 * @return a value from the position.
	 */
	template<std::size_t I>
	constexpr const T& operator[](constexpr_extensions::Index<I> i) const noexcept;
	/**
	 * The `operator[]`.
	 * This method will not check ranges!
	 * @param i index.
	 * @return a value from the position.
	 */
	constexpr const T& operator[](std::size_t i) const noexcept;
	/**
	 * @return numbers of elements.
	 */
	constexpr inline std::size_t count() const noexcept
	{
		return _count;
	}
	/**
	 * Returns a capacity of this array.
	 * For example: If you create an empty array with size = 10.
	 * capacity will equall 20, and each element will have undefined behavior.
	 * @return a capacity of this array.
	 */
	constexpr inline std::size_t capacity() const noexcept
	{
		return _capacity;
	}
	/**
	 * Creates an array with the sequence.
	 * @code
	 * For example: constexpr auto a = StaticArray<int, 5>::make_sequence(); // {1, 2, 3, 4, 5}
	 * @endcode
	 * @return an array with the sequence.
	 */
	static constexpr StaticArray<T, Size> make_sequence() noexcept;
private:
	/**
	 * Makes sequence.
	 */
	template<T... Is>
	static constexpr auto make_sequence_p(std::integer_sequence<T, Is ...>) noexcept;
private:
	T _data[Size]; //! array
	std::size_t _capacity;
	std::size_t _count;
	/**
	 * Sets data to array.
	 */
	template<typename Arg,
	         std::size_t I>
	constexpr void set_data(constexpr_extensions::Index<I> i, Arg&& arg) noexcept;
	/**
	 * Unpacks arguments from constructor.
	 */
	template<typename ... Args,
	         std::size_t ... Indices>
	constexpr void unpack(std::index_sequence<Indices ...>, Args&& ... args) noexcept;
	/**
	 * Creates indexes.
	 */
	template<typename ... Args>
	constexpr void create_indexes(Args&& ... args) noexcept;
};

/*
 * Constructor.
 */
template<typename T,
         std::size_t Size>
constexpr StaticArray<T, Size>::StaticArray() noexcept :
	_data {
	T{}
},
_capacity{Size},
_count{0}
{
}
/*
 * Constructor with arguments.
 * For example: constexpr StaticArray<int, 2> a = {1, 2};.
 */
template<typename T,
         std::size_t Size>
template<typename ... Args,
         std::enable_if_t<
             std::conjunction_v<
                 std::is_same<T, Args>...
                 >
             > *
         >
constexpr StaticArray<T, Size>::StaticArray(Args&& ... list) noexcept :
	_data {
	T{}
},
_capacity{Size},
_count{Size}
{
	static_assert(Size == sizeof ... (list), "Size of array not equal number of elements in the list");
	static_assert(std::conjunction_v<std::is_same<T, Args>... >, "Parameter must be the same type as StaticArray<T>.");
	create_indexes(std::forward<Args>(list) ...);
}
/*
 * The `operator[]`. Takes a integral constant with std::size_t type.
 * This method will check ranges!
 */
template<typename T,
         std::size_t Size>
template<std::size_t I>
constexpr const T& StaticArray<T, Size>::operator[](constexpr_extensions::Index<I> i) const noexcept
{
	static_assert(std::conjunction_v < std::bool_constant<(i < Size)>>, "Index must be less than size of array");
	return _data[i];
}
/*
 * The `operator[]`.
 * This method will not check ranges!
 */
template<typename T,
         std::size_t Size>
constexpr const T& StaticArray<T, Size>::operator[](std::size_t i) const noexcept
{
	return _data[i];
}
/*
 * Makes sequence.
 */
template<typename T,
         std::size_t Size>
constexpr StaticArray<T, Size> StaticArray<T, Size>::make_sequence() noexcept
{
	return make_sequence_p(std::make_integer_sequence<T, Size> {});
}
/*
 * Makes sequence.
 */
template<typename T,
         std::size_t Size>
template<T... Is>
constexpr auto StaticArray<T, Size>::make_sequence_p(std::integer_sequence<T, Is ...>) noexcept
{
	return StaticArray<T, Size>(Is ...);
}
/*
 * Sets data to array.
 */
template<typename T,
         std::size_t Size>
template<typename Arg,
         std::size_t I>
constexpr void StaticArray<T, Size>::set_data(constexpr_extensions::Index<I> i, Arg&& arg) noexcept
{
	_data[i.value] = arg;
}
/*
 * Unpacks arguments from constructor.
 */
template<typename T,
         std::size_t Size>
template<typename ... Args,
         std::size_t ... Indices>
constexpr void StaticArray<T, Size>::unpack(std::index_sequence<Indices ...>, Args&& ... args) noexcept
{
	(set_data(constexpr_extensions::Index<Indices> {}, args), ...);
}
/*
 * Creates indexes.
 */
template<typename T,
         std::size_t Size>
template<typename ... Args>
constexpr void StaticArray<T, Size>::create_indexes(Args&& ... args) noexcept
{
	unpack(std::make_index_sequence<Size> {}, std::forward<Args>(args)...);
}

#endif /* __cplusplus */

#endif // STATICARRAY_H
