#include "catch/catch.hpp"
#include "../src/stack.h"

TEST_CASE("[Stack] Initialization stack.", "[stack]") {
    SECTION("Initialization testing №1.") {
        Stack<int> s; 
        
        REQUIRE(&s != nullptr); 
        CHECK(s.empty());
        REQUIRE(s.count() == 0); 
        
        s.~Stack();
    }
    SECTION("Initialization testing №2.") {
        Stack<int> s = {1, 2, 3, 4, 5, 6};
        
        REQUIRE(&s != nullptr); 
        CHECK_FALSE(s.empty());
        REQUIRE(s.count() == 6);
        REQUIRE(s.front() == 6);
        
        s.~Stack();
    }
    SECTION("Initialization testing №3.") {
        Stack<int> orig = {1, 2, 3};
        REQUIRE(&orig != nullptr); 
        
        Stack<int> s(orig);
        orig.~Stack();
        
        REQUIRE(&s != nullptr); 
        CHECK_FALSE(s.empty());
        REQUIRE(s.count() == 3);
        REQUIRE(s.front() == 3);
        
        s.~Stack();
    }
}

TEST_CASE("[Stack] Testing of insertion in the stack.", "[stack]") {
    SECTION("Testing of insertion №1.") {
        Stack<int> s;
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        REQUIRE(s.front() == 512);
        CHECK_FALSE(s.empty());
        REQUIRE(s.count() == 9);
        
        s.~Stack();
    }
    SECTION("Testing of insertion №2.") {
        Stack<int> s = {2, 4, 8};
        
        for (int i = 16; i < 520; i = i * 2) {
            s.push(i);
        }
        
        REQUIRE(s.front() == 512);
        CHECK_FALSE(s.empty());
        REQUIRE(s.count() == 9);
        
        s.~Stack();
    }
}

TEST_CASE("[Stack] Testing of removing from the stack.", "[stack]") {
    SECTION("Testing of removing №1.") {
        Stack<int> s;
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        CHECK_FALSE(s.empty());
        REQUIRE(s.count() == 9);
        
        for (int i = 512; i > 1; i = i / 2) {
            REQUIRE(s.pop() == i);
        }
        
        CHECK(s.empty());
        REQUIRE(s.count() == 0);
        
        s.~Stack();
    }
    SECTION("Testing of removing №2.") {
        Stack<int> s = {2, 4, 8};
        
        REQUIRE(s.pop() == 8);
        REQUIRE(s.pop() == 4);
        REQUIRE(s.pop() == 2);
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        CHECK_FALSE(s.empty());
        REQUIRE(s.count() == 9);
        
        for (int i = 512; i > 1; i = i / 2) {
            REQUIRE(s.pop() == i);
        }
        
        CHECK(s.empty());
        REQUIRE(s.count() == 0);
        
        s.~Stack();
    }
}

TEST_CASE("[Stack] Testing of front element from the stack.", "[stack]") {
    SECTION("Testing of front element.") {
        Stack<int> s;
        
        for (int i = 2; i < 520; i = i * 2) {
            s.push(i);
        }
        
        REQUIRE(s.front() == 512);
        CHECK_FALSE(s.empty());
        REQUIRE(s.count() == 9);
        
        for (int i = 512; i > 2; i = i / 2) {
            REQUIRE(s.front() == i);
            s.pop();
            REQUIRE(s.front() == (i / 2));
        }
        
        REQUIRE(s.front() == 2);
        REQUIRE(s.pop() == 2);
        
        CHECK(s.empty());
        REQUIRE(s.count() == 0);
        
        s.~Stack();
    }
}
