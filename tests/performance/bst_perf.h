#ifndef BST_PERF_H
#define BST_PERF_H

#include "../../src/bst.h"
#include "performance.h"
#include <vector>
#include <iostream>

class BSTPerformance : public Performance {
public:
    explicit BSTPerformance()
    {}
    
private:
    
    enum class ACTION {
        INSERTION,
        DELETION,
        CLEARING,
        SEARCH
    };
    
    void insertions(const uint& num)
    {
        bst<int> tree;
        
        srand(time(0));
        
        std::vector<int> random_elements;
        
        for (uint i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        start_timer();
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        finish_timer();
        
        assert(tree.count() > 0 && tree.count() <= num);
        
        tree.~bst();
    }
    
    void deletions(const uint& num)
    {
        bst<int> tree;
        
        std::vector<int> random_elements;
        
        for (uint i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        
        assert(tree.count() > 0 && tree.count() <= num);
        
        start_timer();
        try {
            for (uint j = 0; j < random_elements.size(); j++) {
                tree.remove(random_elements[j]);
            } 
        } catch (const bst_exception::BSTIsEmpty& e) {
            
        }
        finish_timer();
        
        tree.~bst();
    }
    
    void search(const uint& num)
    {
        bst<int> tree;
        
        std::vector<int> random_elements;
        
        for (uint i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        
        assert(tree.count() > 0 && tree.count() <= num);
        
        start_timer();
        for (uint j = 0; j < random_elements.size(); j++) {
            tree.find(random_elements[j]);
        }
        finish_timer();
        
        tree.~bst();
    }
    
    void clearing(const uint& num)
    {
        bst<int> tree;
        
        std::vector<int> random_elements;
        
        for (uint i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        
        assert(tree.count() > 0 && tree.count() <= num);
        
        start_timer();
        tree.clear();
        finish_timer();
        
        tree.~bst();
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
            case ACTION::SEARCH:
                search(number); break;
            case ACTION::CLEARING:
                clearing(number); break;
        }
    }
    
    static const ACTION INSERTION = ACTION::INSERTION;
    
    static const ACTION DELETION = ACTION::DELETION;
    
    static const ACTION SEARCH = ACTION::SEARCH;
    
    static const ACTION CLEARING = ACTION::CLEARING;
};


#endif /* BST_PERF_H */

