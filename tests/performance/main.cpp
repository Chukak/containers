#include "stack_perf.h"
#include "queue_perf.h"
#include "sorted_list_perf.h"
#include "bst_perf.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string lines = string(70, '-');

	cout << "1. Stack:" << "\n" << std::flush;
	cout << lines << "\n" << std::flush;

	StackPerformance s;

	int num_stack = 1'000'000;
	cout << "Insertion performance " << num_stack << " values: " << std::flush;
	s.run(StackPerformance::INSERTION, num_stack);
	cout << s.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Deletion performance " << num_stack << " values: " << std::flush;
	s.run(StackPerformance::DELETION, num_stack);
	cout << s.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << lines << "\n" << std::flush;

	cout << "2. Queue:" << "\n" << std::flush;
	cout << lines << "\n" << std::flush;

	QueuePerformance q;

	int num_queue = 1'000'000;
	cout << "Insertion performance " << num_queue << " values: " << std::flush;
	q.run(QueuePerformance::INSERTION, num_queue);
	cout << q.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Deletion performance " << num_queue << " values: " << std::flush;
	q.run(QueuePerformance::DELETION, num_queue);
	cout << q.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Clearing performance " << num_queue << " values: " << std::flush;
	q.run(QueuePerformance::CLEARING, num_queue);
	cout << q.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << lines << "\n" << std::flush;

	cout << "3. Sorted list:" << "\n" << std::flush;
	cout << lines << "\n" << std::flush;

	SListPerformance list;

	int num_slist = 50'000;
	cout << "Insertion performance " << num_slist << " values: " << std::flush;
	list.run(SListPerformance::INSERTION, num_slist);
	cout << list.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Deletion performance " << num_slist
	     << " values in the sorted list with "
	     << num_slist << " values: " << std::flush;
	list.run(SListPerformance::DELETION, num_slist);
	cout << list.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Clearing performance " << num_slist << " values: " << std::flush;
	list.run(SListPerformance::CLEARING, num_slist);
	cout << list.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Reverse performance " << num_slist << " values: " << std::flush;
	list.run(SListPerformance::REVERSE, num_slist);
	cout << list.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << lines << "\n" << std::flush;

	cout << "4. Binary search tree:" << "\n" << std::flush;
	cout << lines << "\n" << std::flush;

	BSTPerformance tree;

	int num_tree = 1'000'000;
	cout << "Insertion performance " << 1 << " - " << num_tree << " values: " << std::flush;
	tree.run(BSTPerformance::INSERTION, num_tree);
	cout << tree.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Deletion performance " << 1 << " - " << num_tree
	     << " values in the binary search tree with "
	     << 1 << " - " << num_tree << " values: " << std::flush;
	tree.run(BSTPerformance::DELETION, num_tree);
	cout << tree.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Search performance " << 1 << " - " << num_tree
	     << " values in the binary search tree with "
	     << 1 << " - " << num_tree << " values: " << std::flush;
	tree.run(BSTPerformance::SEARCH, num_tree);
	cout << tree.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << "Clearing performance " << 1 << " - " << num_tree << " values: " << std::flush;
	tree.run(BSTPerformance::CLEARING, num_tree);
	cout << tree.milliseconds() << " milliseconds." << "\n" << std::flush;

	cout << lines << "\n" << std::flush;

	return 0;
}
