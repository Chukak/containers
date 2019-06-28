#ifndef BST_PERF_H
#define BST_PERF_H

#include "bst.h"
#include "performance.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

class BinarySearchTreePerfomance : public Perfomance, public perf_clock::Timer, public print::Output
{
public:
	enum ACTION
	{
		INSERT,
		DELETE,
		CLEAR,
		SEARCH
	};
private:
	std::vector<ACTION> actions{};
	int number{1000};
public:
	BinarySearchTreePerfomance() = default;
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
			case ACTION::SEARCH:
				search(number);
				break;
			}
		}
	}
private:
	void print_name() final
	{
		std::cout << "Binary search tree:\n" << std::endl;
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
		bst<int> tree;

		std::vector<int> random_elements(num);
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> dist(5 * -num, 5 * num);
		std::iota(random_elements.begin(), random_elements.end(), -num / 2);
		std::shuffle(random_elements.begin(), random_elements.end(), gen);

		start_timer();
		for (int i : random_elements) {
			tree.insert(i);
		}
		finish_timer();

		if (tree.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: bst.count() != " << num << std::endl;
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
		bst<int> tree;

		std::vector<int> random_elements(num);
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> dist(5 * -num, 5 * num);
		std::iota(random_elements.begin(), random_elements.end(), -num / 2);
		std::shuffle(random_elements.begin(), random_elements.end(), gen);

		for (int i : random_elements) {
			tree.insert(i);
		}

		if (tree.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: bst.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		std::cout << "done.\nPerfomance: ";

		start_timer();
		try {
			for (int i : random_elements) {
				tree.remove(i);
			}
		} catch (const bst_exception::bst_is_empty& e) {
			std::cerr << "Error: " << e.what() << "\n";
			print_line_separator();
			return;
		}
		finish_timer();
		print_ms();
		print_line_separator();
	}

	void search(int num)
	{
		print_line_separator();
		print_name();
		std::cout << "Search " << num << " values. Wait for inserting values ...";
		bst<int> tree;

		std::vector<int> random_elements(num);
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> dist(5 * -num, 5 * num);
		std::iota(random_elements.begin(), random_elements.end(), -num / 2);
		std::shuffle(random_elements.begin(), random_elements.end(), gen);

		for (int i : random_elements) {
			tree.insert(i);
		}

		if (tree.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: bst.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		std::cout << "done.\nPerfomance: ";

		start_timer();
		for (int i :  random_elements) {
			if (!tree.find(i)) {
				std::cout << "Error: bst.find() != true" << std::endl;
				print_line_separator();
				return;
			}
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
		bst<int> tree;

		std::vector<int> random_elements(num);
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<> dist(5 * -num, 5 * num);
		std::iota(random_elements.begin(), random_elements.end(), -num / 2);
		std::shuffle(random_elements.begin(), random_elements.end(), gen);

		for (int i : random_elements) {
			tree.insert(i);
		}

		if (tree.count() != static_cast<unsigned int>(num)) {
			std::cout << "Error: bst.count() != " << num << std::endl;
			print_line_separator();
			return;
		}
		std::cout << "done.\nPerfomance: ";

		start_timer();
		tree.clear();
		finish_timer();
		print_ms();
		print_line_separator();
	}
};

#endif /* BST_PERF_H */

