#ifndef SORTED_LIST_PERF_H
#define SORTED_LIST_PERF_H

#include "sorted_list.h"
#include "performance.h"
#include <vector>
#include <random>
#include <algorithm>

class SortedListPerfomance : public Perfomance, public perf_clock::Timer, public print::Output
{
public:
	enum ACTION {
		INSERT,
		DELETE,
		CLEAR,
		REVERSE
	};
private:
	std::vector<ACTION> actions{};
	int number{10000};
public:
	SortedListPerfomance() = default;
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
			case ACTION::CLEAR:
				clear(number);
				break;
			case ACTION::REVERSE:
				reverse(number);
				break;
			}
		}
	}
private:
	void print_name() final
	{
		std::cout << "Sorted list:\n" << std::endl;
	}
	void print_ms() final
	{
		std::cout << cast_to<perf_clock::ms>() << " milliseconds.\n" << std::endl;
	}
private:
	void insert(int num)
	{
		print_line_separator();
		print_name();
		std::cout << "Insert " << num << " values. Perfomance: ";
		sorted_list<int> list;

		std::vector<int> random_elements(num);
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> dist(5 * -num, 5 * num);
		std::iota(random_elements.begin(), random_elements.end(), -num / 2);
		std::shuffle(random_elements.begin(), random_elements.end(), gen);

		start_timer();
		for (int i : random_elements) {
			list.push(i);
		}
		finish_timer();

		if (list.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: sorted_list.count() != " << num << std::endl;
			print_line_separator();
			return;
		}

		print_ms();
		print_line_separator();
	}

	void remove(int num)
	{
		print_line_separator();
		print_name();
		std::cout << "Delete " << num << " values. Wait for inserting values ...";
		sorted_list<int> list;

		for (int i = 0; i < num; i++) {
			list.push(i);
		}

		if (list.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: sorted_list.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		std::cout << "done.\nPerfomance: ";

		srand(static_cast<uint>(time(nullptr)));

		start_timer();
		try {
			for (unsigned int i = 0; i != list.count();) {
				list.remove(static_cast<int>(rand() % static_cast<int>(list.count())));
			}
		} catch (std::out_of_range& e) {
			std::cout << "Error: " << e.what() << std::endl;
			return;
		}
		finish_timer();
		print_ms();
		print_line_separator();
	}

	void clear(int num)
	{
		print_line_separator();
		print_name();
		std::cout << "Clear " << num << " values. Wait for inserting values ...";
		sorted_list<int> list;

		for (int i = 0; i < num; i++) {
			list.push(i);
		}

		if (list.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: sorted_list.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		std::cout << "done.\nPerfomance: ";

		start_timer();
		list.clear();
		finish_timer();
		print_ms();
		print_line_separator();
	}

	void reverse(int num)
	{
		print_line_separator();
		print_name();
		std::cout << "Reverse " << num << " values. Wait for inserting values ...";
		sorted_list<int> list;

		for (int i = 0; i < num; i++) {
			list.push(i);
		}

		if (list.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: sorted_list.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		std::cout << "done.\nPerfomance: ";

		start_timer();
		list.reverse();
		finish_timer();
		print_ms();
		print_line_separator();
	}
};

#endif /* SORTED_LIST_PERF_H */

