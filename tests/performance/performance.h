#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <chrono>
#include <cstdint>

using uint = unsigned int;

using ms = std::chrono::duration<int64_t, std::milli>;
using mic = std::chrono::duration<int64_t, std::micro>;
using sec = std::chrono::duration<int64_t>;
using t_point = std::chrono::steady_clock::time_point;


class Performance {
public:
	explicit Performance() : start(), end()
	{}

	auto milliseconds()
	{
		return std::chrono::duration_cast<ms>(end - start).count();
	}

	auto seconds()
	{
		return std::chrono::duration_cast<sec>(end - start).count();
	}

	auto microseconds()
	{
		return std::chrono::duration_cast<mic>(end - start).count();
	}
private:
	t_point start;
	t_point end;

protected:

	void reset()
	{
		start = end = {};
	}

	t_point now()
	{
		return std::chrono::steady_clock::now();
	}

	void start_timer()
	{
		start = now();
	}

	void finish_timer()
	{
		end = now();
	}
};

#endif /* PERFORMANCE_H */

