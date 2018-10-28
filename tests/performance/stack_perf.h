#ifndef STACK_PERF_H
#define STACK_PERF_H

#include "stack.h"
#include "performance.h"
#include <cassert>

class StackPerformance : public Performance {
public:
    explicit StackPerformance() 
    {}
    
public:
    enum ACTION {
        INSERTION,
        DELETION
    };
private:
    void insertions(const int& num)
    {
        Stack<int> stack;
    
        start_timer();
        for (int i = 0; i < num; i++) {
            stack.push(i);
        }
        finish_timer();
        
        assert(stack.count() == static_cast<uint>(num));

        stack.~Stack();
    }
    
    void deletions(const int& num)
    {
        Stack<int> stack;
        
        for (int i = 0; i < num; i++) {
            stack.push(i);
        }
        
        assert(stack.count() == static_cast<uint>(num));
        
        start_timer();
        while (stack.count()) {
            stack.pop();
        }
        finish_timer();
        
        stack.~Stack();
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
        }
    }
};

#endif /* STACK_PERF_H */
