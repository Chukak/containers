#ifndef STACK_PERF_H
#define STACK_PERF_H

#include "stack.h"
#include "performance.h"
#include <vector>

class StackPerfomance : public Perfomance, public perf_clock::Timer, public print::Output
{
public:
	enum ACTION
	{
		INSERT,
		DELETE
	};
private:
	std::vector<ACTION> actions{};
	int number{1000};
public:
	StackPerfomance() = default;
	inline void set_number(int n) noexcept {
		number = n;
	}
	template<typename ... Args>
	inline void add_actions(Args&& ... acts) noexcept {
		(actions.push_back(std::forward<Args>(acts)), ...);
	}

	void run() final
	{
		reset_timer();
		for (auto act : actions) {
			switch (act) {
			case ACTION::INSERT:
				insert(number);
				break;
			case ACTION::DELETE:
				remove(number);
				break;
			}
		}
	}
private:
	void print_name() final
	{
		std::cout << "Stack:\n" << std::endl;
	}
	void print_ms() final
	{
		std::cout << cast_to<perf_clock::ms>() << " milliseconds.\n" << std::endl;
	}
private:
	inline void insert(int num) noexcept
	{
		print_line_separator();
		print_name();
		std::cout << "Insert " << num << " values. Perfomance: ";
		Stack<int> stack;

		start_timer();
		for (int i = 0; i < num; i++) {
			stack.push(i);
		}
		finish_timer();

		if (stack.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: Stack.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		print_ms();
		print_line_separator();
	}
	inline void remove(int num) noexcept
	{
		print_line_separator();
		print_name();
		std::cout << "Delete " << num << " values. Wait for inserting values ...";
		Stack<int> stack;

		for (int i = 0; i < num; i++) {
			stack.push(i);
		}
		if (stack.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: Stack.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		std::cout << "done.\nPerfomance: ";

		start_timer();
		while (stack.count()) {
			stack.pop();
		}
		finish_timer();
		print_ms();
		print_line_separator();
	}
};

#endif /* STACK_PERF_H */
