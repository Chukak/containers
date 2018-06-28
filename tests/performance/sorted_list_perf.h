#ifndef SORTED_LIST_PERF_H
#define SORTED_LIST_PERF_H

#include "../../src/sorted_list.h"
#include "performance.h"
#include <vector>

class SListPerformance : public Performance {
public:
    explicit SListPerformance()
    {}
    
private:
    
    enum class ACTION {
        INSERTION,
        DELETION,
        CLEARING,
        REVERSE
    };
    
    void insertions(const uint& num)
    {
        sorted_list<int> list;
        
        srand(time(0));
        
        std::vector<int> random_elements;
        
        for (uint i = 0; i < num; i++) {
            random_elements.push_back((rand() % num + 1));// - (50000));
        }
        
        start_timer();
        for (uint s = 0; s < random_elements.size(); s++) {
            list.push(random_elements[s]);
        }
        finish_timer();
        
        assert(list.count() == num);
        
        list.~sorted_list();
    }
    
    void deletions(const uint& num)
    {
        sorted_list<uint> list;
        
        for (uint i = 0; i < num; i++) {
            list.push(i);
        }
        
        assert(list.count() == num);
        
        srand(time(0));
        
        start_timer();
        try {
            for (uint i = 0; i != list.count();) {
                list.remove(rand() % list.count());
            } 
        } catch (std::out_of_range& e) {
            
        }
        finish_timer();
        
        list.~sorted_list();
    }
    
    void clearing(const uint& num)
    {
        sorted_list<int> list;
        
        for (uint i = 0; i < num; i++) {
            list.push(i);
        }
        
        assert(list.count() == num);
        
        start_timer();
        list.clear();
        finish_timer();
        
        assert(list.count() == 0);
        
        list.~sorted_list();
    }
    
    void reverse(const uint& num)
    {
        sorted_list<uint> list;
        
        for (uint i = 0; i < num; i++) {
            list.push(i);
        }
        
        assert(list.count() == num);
        
        start_timer();
        list.reverse();
        finish_timer();
        
        assert(list.front() == (num - 1));
        
        list.~sorted_list();
    }
    
public:
    
    void run(ACTION action, const uint& number) 
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
    
    static const ACTION INSERTION = ACTION::INSERTION;
    
    static const ACTION DELETION = ACTION::DELETION;
    
    static const ACTION CLEARING = ACTION::CLEARING;
    
    static const ACTION REVERSE = ACTION::REVERSE;
};

#endif /* SORTED_LIST_PERF_H */

