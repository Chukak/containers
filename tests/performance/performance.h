#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <chrono>
#include <cstdint>
#include <iostream>

namespace perf_clock
{

using ms = std::chrono::duration<int64_t, std::milli>;
using mic = std::chrono::duration<int64_t, std::micro>;
using sec = std::chrono::duration<int64_t>;
using t_point = std::chrono::steady_clock::time_point;


class Timer {
public:
	Timer() = default;
	Timer(Timer&&) = delete;
	Timer(const Timer&) = delete;
	virtual ~Timer() = default;
	Timer& operator=(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;

	template<typename C>
	inline auto cast_to() const noexcept
	{
		return std::chrono::duration_cast<C>(end - start).count();
	}
	inline auto now() const noexcept {
		return std::chrono::steady_clock::now();
	}
private:
	t_point start{};
	t_point end{};
protected:
	inline void reset_timer() noexcept {
		start = end = {};
	}

	inline void start_timer() noexcept {
		start = now();
	}

	inline void finish_timer() noexcept {
		end = now();
	}
};

}

class Perfomance
{
public:
	Perfomance() = default;
	Perfomance(Perfomance&&) = delete;
	Perfomance(const Perfomance&) = delete;
	virtual ~Perfomance() = default;
	Perfomance& operator=(Perfomance&&) = delete;
	Perfomance& operator=(const Perfomance&) = delete;

	virtual void run() = 0;
};

namespace print
{

class Output
{
	const std::string separator;
public:
	Output() : separator(80, '-') {}
	Output(Output&&) = delete;
	Output(const Output&) = delete;
	virtual ~Output() = default;
	Output& operator=(Output&&) = delete;
	Output& operator=(const Output&) = delete;
protected:
	inline void print_line_separator() noexcept {
		std::cout << separator << std::endl;
	}
	virtual void print_name() = 0;
	virtual void print_ms() = 0;
};

}
#endif /* PERFORMANCE_H */

