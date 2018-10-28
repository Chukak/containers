#ifndef BST_PERF_H
#define BST_PERF_H

#include "bst.h"
#include "performance.h"
#include <vector>
#include <iostream>
#include <cassert>

class BSTPerformance : public Performance {
public:
    explicit BSTPerformance()
    {}
    
public:
    enum ACTION {
        INSERTION,
        DELETION,
        CLEARING,
        SEARCH
    };
private:
    void insertions(const int& num)
    {
        bst<int> tree;
        
        srand(static_cast<uint>(time(nullptr)));
        
        std::vector<int> random_elements;
        
        for (int i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        start_timer();
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        finish_timer();
        
        assert(tree.count() > 0 && tree.count() <= static_cast<uint>(num));
        
        tree.~bst();
    }
    
    void deletions(const int& num)
    {
        bst<int> tree;
        
        std::vector<int> random_elements;
        
        for (int i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        
        assert(tree.count() > 0 && tree.count() <= static_cast<uint>(num));
        
        start_timer();
        try {
            for (uint j = 0; j < random_elements.size(); j++) {
                tree.remove(random_elements[j]);
            } 
        } catch (const bst_exception::BSTIsEmpty& e) {
            std::cerr << e.what() << "\n";
        }
        finish_timer();
        
        tree.~bst();
    }
    
    void search(const int& num)
    {
        bst<int> tree;
        
        std::vector<int> random_elements;
        
        for (int i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        
        assert(tree.count() > 0 && tree.count() <= static_cast<uint>(num));
        
        start_timer();
        for (uint j = 0; j < random_elements.size(); j++) {
            tree.find(random_elements[j]);
        }
        finish_timer();
        
        tree.~bst();
    }
    
    void clearing(const int& num)
    {
        bst<int> tree;
        
        std::vector<int> random_elements;
        
        for (int i = 0; i < num; i++) {
            random_elements.push_back((rand() % (num * 10) + 1) + (-50000));
        }
        
        for (uint s = 0; s < random_elements.size(); s++) {
            tree.insert(random_elements[s]);
        }
        
        assert(tree.count() > 0 && tree.count() <= static_cast<uint>(num));
        
        start_timer();
        tree.clear();
        finish_timer();
        
        tree.~bst();
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
            case ACTION::SEARCH:
                search(number); break;
            case ACTION::CLEARING:
                clearing(number); break;
        }
    }
};


#endif /* BST_PERF_H */

