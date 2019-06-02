#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include <utility>
#include <memory>

namespace _helpers_extensions
{
/*
 * Call constexpr function N time at compile time.
 */
template<class F,
         std::size_t ... Is>
constexpr void _loop(F&& func, std::index_sequence<Is ...>) noexcept
{
	(func(std::integral_constant<std::size_t, Is> {}), ...);
}
}
/*
 * Pseudonym for code: `std::make_shared<T>(T(...))`.
 */
template<typename T,
         typename ... Args>
inline auto make_shared_ptr(Args&& ... args)
- > decltype(std::make_shared<T>(std::forward<Args>(args)...))
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
/*
 * Makes short rvalue with literal.
 * For example: 2_16b.
 */
inline constexpr short operator "" _16b(unsigned long long value) noexcept
{
	return static_cast<short>(value);
}
/*
 * Makes double rvalue with literal.
 * For example: 2_dbl
 */
inline constexpr double operator "" _dbl(long double value) noexcept
{
	return static_cast<double>(value);
}
#pragma GCC diagnostic pop

namespace constexpr_extensions
{
/*
 * Pseudonym for code: std::integral_constant<std::size_t, I>
 */
template<std::size_t I>
using Index = std::integral_constant<std::size_t, I>;
/*
 * Makes integral constant for custom type.
 */
template<typename T,
         T Val>
using IntegralVar = std::integral_constant<T, Val>;
/*
 * Constexpr loop.
 */
template<std::size_t N,
         typename F>
constexpr void CONSTEXPR_LOOP(F&& func) noexcept
{
	_helpers_extensions::_loop(std::forward<F>(func), std::make_index_sequence<N>());
}
/*
 *
 */
template<std::size_t N>
using Size = std::integral_constant<std::size_t, N>;
}

#endif // EXTENSIONS_H
