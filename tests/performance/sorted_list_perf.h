#ifndef SORTED_LIST_PERF_H
#define SORTED_LIST_PERF_H

#include "sorted_list.h"
#include "performance.h"
#include <vector>
#include <cassert>
#include <iostream>

class SListPerformance : public Performance {
public:
    explicit SListPerformance()
    {}
    
public:
    enum ACTION {
        INSERTION,
        DELETION,
        CLEARING,
        REVERSE
    };
private:
    void insertions(const int& num)
    {
        sorted_list<int> list;
        
        srand(static_cast<uint>(time(nullptr)));
        
        std::vector<int> random_elements;
        
        for (int i = 0; i < num; i++) {
            random_elements.push_back((rand() % num + 1));// - (50000));
        }
        
        start_timer();
        for (uint s = 0; s < random_elements.size(); s++) {
            list.push(random_elements[s]);
        }
        finish_timer();
        
        assert(list.count() == static_cast<uint>(num));
        
        list.~sorted_list();
    }
    
    void deletions(const int& num)
    {
        sorted_list<int> list;
        
        for (int i = 0; i < num; i++) {
            list.push(i);
        }
        
        assert(list.count() == static_cast<uint>(num));
        
        srand(static_cast<uint>(time(nullptr)));
        
        start_timer();
        try {
            for (int i = 0; static_cast<uint>(i) != list.count();) {
                list.remove(static_cast<int>(rand() % static_cast<int>(list.count())));
            } 
        } catch (std::out_of_range& e) {
            std::cerr << e.what() << "\n";
        }
        finish_timer();
        
        list.~sorted_list();
    }
    
    void clearing(const int& num)
    {
        sorted_list<int> list;
        
        for (int i = 0; i < num; i++) {
            list.push(i);
        }
        
        assert(list.count() == static_cast<uint>(num));
        
        start_timer();
        list.clear();
        finish_timer();
        
        assert(list.count() == 0);
        
        list.~sorted_list();
    }
    
    void reverse(const int& num)
    {
        sorted_list<int> list;
        
        for (int i = 0; i < num; i++) {
            list.push(i);
        }
        
        assert(list.count() == static_cast<uint>(num));
        
        start_timer();
        list.reverse();
        finish_timer();
        
        assert(list.front() == (num - 1));
        
        list.~sorted_list();
    }
    
public:
    
    void run(const ACTION& action, const int& number)
    {
        reset();
        switch (action) {
            case ACTION::INSERTION:
                insertions(number); break;
            case ACTION::DELETION:
                deletions(number); break;
            case ACTION::CLEARING:
                clearing(number); break;
            case ACTION::REVERSE:
                reverse(number); break;
        }
    }
};

#endif /* SORTED_LIST_PERF_H */

