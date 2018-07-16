#include "catch/catch.hpp"
#include "../src/stack.h"

/*
 * Testing the initialization of the stack.
 */
TEST_CASE("[Stack] Initialization stack.", "[stack]") {
    /*
     * Testing the standart initialization.
     */
    SECTION("Testing the initialization №1.") {
        Stack<int> s; 
        
        REQUIRE(&s != nullptr); 
        CHECK(s.is_empty());
        REQUIRE(s.count() == 0); 
        
        s.~Stack();
    }
    /*
     * Testing the initialization `Stack s = {1,2,3}`.
     */
    SECTION("Testing the initialization №2.") {
        Stack<int> s = {1, 2, 3, 4, 5, 6};
        
        REQUIRE(&s != nullptr); 
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 6);
        REQUIRE(s.front() == 6);
        
        s.~Stack();
    }
    /*
     * Testing the initialization of the stack from another stack.
     */
    SECTION("Testing the initialization №3.") {
        Stack<int> orig = {1, 2, 3};
        REQUIRE(&orig != nullptr); 
        
        Stack<int> s(orig);
        orig.~Stack();
        
        REQUIRE(&s != nullptr); 
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 3);
        REQUIRE(s.front() == 3);
        
        s.~Stack();
    }
    /*
     * Testing the initialization of the stack from another stack.
     */
    SECTION("Testing the initialization №4.") {
        Stack<int> orig = {1, 2, 3};
        REQUIRE(&orig != nullptr); 
        
        Stack<int> s(std::move(orig));
        
        REQUIRE(orig.count() == 0);
        CHECK(orig.is_empty());
        REQUIRE_FALSE(orig.front() == 3);
        
        REQUIRE(&s != nullptr); 
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 3);
        REQUIRE(s.front() == 3);
        
        orig.~Stack();
        s.~Stack();
    } 
}

/*
 * Testing the insertion in the stack.
 */
TEST_CASE("[Stack] Testing the insertion in the stack.", "[stack]") {
    SECTION("Testing the insertion №1.") {
        Stack<int> s;
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        REQUIRE(s.front() == 512);
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 9);
        
        s.~Stack();
    }
    SECTION("Testing the insertion №2.") {
        Stack<int> s = {2, 4, 8};
        
        for (int i = 16; i < 520; i = i * 2) {
            s.push(i);
        }
        
        REQUIRE(s.front() == 512);
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 9);
        
        s.~Stack();
    }
}

/*
 * Testing the removing from the stack.
 */
TEST_CASE("[Stack] Testing the removing from the stack.", "[stack]") {
    SECTION("Testing the removing №1.") {
        Stack<int> s;
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 9);
        
        for (int i = 512; i > 1; i = i / 2) {
            REQUIRE(s.pop() == i);
        }
        
        CHECK(s.is_empty());
        REQUIRE(s.count() == 0);
        
        s.~Stack();
    }
    SECTION("Testing the removing №2.") {
        Stack<int> s = {2, 4, 8};
        
        REQUIRE(s.pop() == 8);
        REQUIRE(s.pop() == 4);
        REQUIRE(s.pop() == 2);
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 9);
        
        for (int i = 512; i > 1; i = i / 2) {
            REQUIRE(s.pop() == i);
        }
        
        CHECK(s.is_empty());
        REQUIRE(s.count() == 0);
        
        s.~Stack();
    }
}

/*
 * Testing the front element from the stack.
 */
TEST_CASE("[Stack] Testing the front element from the stack.", "[stack]") {
    SECTION("Testing the front element.") {
        Stack<int> s;
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        REQUIRE(s.front() == 512);
        CHECK_FALSE(s.is_empty());
        REQUIRE(s.count() == 9);
        
        for (int i = 512; i > 2; i = i / 2) {
            REQUIRE(s.front() == i);
            s.pop();
            REQUIRE(s.front() == (i / 2));
        }
        
        REQUIRE(s.front() == 2);
        REQUIRE(s.pop() == 2);
        
        CHECK(s.is_empty());
        REQUIRE(s.count() == 0);
        
        s.~Stack();
    }
}

/*
 * Testing the iterators of the stack.
 */
TEST_CASE("[Stack] Testing the iterators of the stack.", "[stack]") {
    SECTION("Testing the iterators.") {
        Stack<int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        
        Stack<int>::iterator iter = s.begin();
        CHECK_FALSE(iter == nullptr);
        CHECK(iter != nullptr);
        
        unsigned test_var = 10;
        for (auto it = s.begin(); it != s.end(); ++it) {
            REQUIRE(*it == test_var);
            test_var--;
        }
        REQUIRE(test_var == 0);
        
        test_var = 10;
        for (auto it = s.begin(); it != s.end(); it++) {
            REQUIRE(it->value == test_var);
            test_var--;
        }
        REQUIRE(test_var == 0);
        
        CHECK_FALSE(s.begin() == s.end());
        CHECK(s.begin() != s.end());
        
        s.~Stack();
    }
    SECTION("Testing that the iterators and nullptr are the same.") {
        Stack<int> s;
        
        REQUIRE(s.begin() == s.end());
        REQUIRE(s.begin() == nullptr);
        REQUIRE(s.end() == nullptr);
        
        s.~Stack();
    }
}
