#ifndef STACK_PERF_H
#define STACK_PERF_H

#include "../../src/stack.h"
#include "performance.h"

class StackPerformance : public Performance {
public:
    explicit StackPerformance() 
    {}
    
private:
    
    void insertions(const uint& num)
    {
        Stack<int> stack;
    
        start_timer();
        for (uint i = 0; i < num; i++) {
            stack.push(i);
        }
        finish_timer();
        
        assert(stack.count() == num);

        stack.~Stack();
    }
    
    void deletions(const uint& num)
    {
        Stack<int> stack;
        
        for (uint i = 0; i < num; i++) {
            stack.push(i);
        }
        
        assert(stack.count() == num);
        
        start_timer();
        while (stack.count()) {
            stack.pop();
        }
        finish_timer();
        
        stack.~Stack();
    }
    
public:
    
    void run(ACTION action, uint number) 
    {
        reset();
        switch (action) {
            case ACTION::INSERTION:
                insertions(number); break;
            case ACTION::DELETION:
                deletions(number); break;
            default:
                break;
        }
    }
    
    static const ACTION INSERTION = ACTION::INSERTION;
    
    static const ACTION DELETION = ACTION::DELETION;
};

#endif /* STACK_PERF_H */
