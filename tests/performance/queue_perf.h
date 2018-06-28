#ifndef QUEUE_PERF_H
#define QUEUE_PERF_H

#include "../../src/queue.h"
#include "performance.h"

class QueuePerformance : public Performance {
public:
    explicit QueuePerformance()
    {}
    
private:
    
    enum class ACTION {
        INSERTION,
        DELETION,
        CLEARING
    };
    
    void insertions(const uint& num)
    {
        Queue<int> queue;
    
        start_timer();
        for (uint i = 0; i < num; i++) {
            queue.enqueue(i);
        }
        finish_timer();
        
        assert(queue.count() == num);

        queue.~Queue();
    }
    
    void deletions(const uint& num)
    {
        Queue<int> queue;
        
        for (uint i = 0; i < num; i++) {
            queue.enqueue(i);
        }
        
        assert(queue.count() == num);
        
        start_timer();
        while (queue.count()) {
            queue.dequeue();
        }
        finish_timer();
        
        queue.~Queue();
    }
    
    void clearing(const uint& num)
    {
        Queue<int> queue;
        
        for (uint i = 0; i < num; i++) {
            queue.enqueue(i);
        }
        
        assert(queue.count() == num);
        
        start_timer();
        queue.clear();
        finish_timer();
        
        queue.~Queue();
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
            case ACTION::CLEARING:
                clearing(number); break;
        }
    }
    
    static const ACTION INSERTION = ACTION::INSERTION;
    
    static const ACTION DELETION = ACTION::DELETION;
    
    static const ACTION CLEARING = ACTION::CLEARING;
};


#endif /* QUEUE_PERF_H */

