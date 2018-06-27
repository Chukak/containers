#include "stack_perf.h"
#include "queue_perf.h"
#include "sorted_list_perf.h"
#include "bst_perf.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char **args) 
{
    string lines = string(70, '-');
    
    cout << "1. Stack:" << "\n";
    cout << lines << "\n";
            
    StackPerformance s;
    
    unsigned int num_stack = 1'000'000;
    cout << "Insertion performance " << num_stack << " values: ";
    s.run(StackPerformance::INSERTION, num_stack);
    cout << s.milliseconds() << " milliseconds." << "\n";

    cout << "Deletion performance " << num_stack << " values: ";
    s.run(StackPerformance::DELETION, num_stack);
    cout << s.milliseconds() << " milliseconds." << "\n";
    
    cout << lines << "\n";
    
    cout << "2. Queue:" << "\n";
    cout << lines << "\n";
            
    QueuePerformance q;
    
    unsigned int num_queue = 1'000'000;
    cout << "Insertion performance " << num_queue << " values: ";
    q.run(QueuePerformance::INSERTION, num_queue);
    cout << q.milliseconds() << " milliseconds." << "\n";

    cout << "Deletion performance " << num_queue << " values: ";
    q.run(QueuePerformance::DELETION, num_queue);
    cout << q.milliseconds() << " milliseconds." << "\n";
    
    cout << "Clearing performance " << num_queue << " values: ";
    q.run(QueuePerformance::CLEARING, num_queue);
    cout << q.milliseconds() << " milliseconds." << "\n";
    
    cout << lines << "\n";
    
    cout << "3. Sorted list:" << "\n";
    cout << lines << "\n";
    
    SListPerformance list;
    
    unsigned int num_slist = 10'000;
    cout << "Insertion performance " << num_slist << " values: ";
    list.run(SListPerformance::INSERTION, num_slist);
    cout << list.milliseconds() << " milliseconds." << "\n";

    cout << "Deletion performance " << (num_slist / 2) 
            << " values in the sorted list with " 
            << num_slist << " values: ";
    list.run(SListPerformance::DELETION, num_slist);
    cout << list.milliseconds() << " milliseconds." << "\n";
    
    cout << "Clearing performance " << num_slist << " values: ";
    list.run(SListPerformance::CLEARING, num_slist);
    cout << list.milliseconds() << " milliseconds." << "\n";
    
    cout << lines << "\n";
    
    cout << "4. Binary search tree:" << "\n";
    cout << lines << "\n";
    
    BSTPerformance tree;
    
    unsigned int num_tree = 1'000'000;
    cout << "Insertion performance " << 1 << " - " << num_tree << " values: ";
    tree.run(BSTPerformance::INSERTION, num_tree);
    cout << tree.milliseconds() << " milliseconds." << "\n";

    cout << "Deletion performance " << 1 << " - " << num_tree  
            << " values in the binary search tree with " 
            << 1 << " - " << num_tree << " values: ";
    tree.run(BSTPerformance::DELETION, num_tree);
    cout << tree.milliseconds() << " milliseconds." << "\n";
    
    cout << "Search performance " << 1 << " - " << num_tree  
            << " values in the binary search tree with " 
            << 1 << " - " << num_tree << " values: ";
    tree.run(BSTPerformance::SEARCH, num_tree);
    cout << tree.milliseconds() << " milliseconds." << "\n";
    
    cout << "Clearing performance " << 1 << " - " << num_tree << " values: ";
    tree.run(BSTPerformance::CLEARING, num_tree);
    cout << tree.milliseconds() << " milliseconds." << "\n";
    
    cout << lines << "\n";
    
    return 0;
}