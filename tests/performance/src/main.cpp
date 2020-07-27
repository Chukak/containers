#include "stack_perf.h"
#include "queue_perf.h"
#include "sorted_list_perf.h"
#include "bst_perf.h"

int main()
{
    StackPerfomance stack_perf;
    stack_perf.set_number(1'000'000);
    stack_perf.add_actions(StackPerfomance::INSERT, StackPerfomance::DELETE);
    stack_perf.run();

    QueuePerformance queue_perf;
    queue_perf.set_number(1'000'000);
    queue_perf.add_actions(QueuePerformance::INSERT, QueuePerformance::DELETE, QueuePerformance::CLEAR);
    queue_perf.run();

    SortedListPerfomance sorted_list_perf;
    sorted_list_perf.set_number(20000);
    sorted_list_perf.add_actions(SortedListPerfomance::INSERT,
                                 SortedListPerfomance::DELETE,
                                 SortedListPerfomance::CLEAR,
                                 SortedListPerfomance::CLEAR);
    sorted_list_perf.run();

    BinarySearchTreePerfomance binary_search_tree_perf;
    binary_search_tree_perf.set_number(1'000'000);
    binary_search_tree_perf.add_actions(BinarySearchTreePerfomance::INSERT,
                                        BinarySearchTreePerfomance::DELETE,
                                        BinarySearchTreePerfomance::CLEAR,
                                        BinarySearchTreePerfomance::SEARCH);
    binary_search_tree_perf.run();

    return 0;
}
