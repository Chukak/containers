#include "catch/catch.hpp"
#include "../src/queue.h"

TEST_CASE("[Queue] Initialization an queue.", "[queue]") {
    SECTION("Initialization testing №1.") {
        Queue<int> q; 
        
        REQUIRE(&q != nullptr); 
        CHECK(q.empty());
        REQUIRE(q.count() == 0); 
        
        q.~Queue();
    }
    SECTION("Initialization testing №2.") {
        Queue<int> q = {1, 2, 3, 4, 5, 6};
        
        REQUIRE(&q != nullptr); 
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 6);
        REQUIRE(q.back() == 6);
        REQUIRE(q.front() == 1);
        
        q.~Queue();
    }
    SECTION("Initialization testing №3.") {
        Queue<int> orig = {1, 2, 3};
        REQUIRE(&orig != nullptr); 
        
        Queue<int> q(orig);
        orig.~Queue();
        
        REQUIRE(&q != nullptr); 
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 3);
        REQUIRE(q.back() == 3);
        REQUIRE(q.front() == 1);
        
        q.~Queue();
    }
}

TEST_CASE("[Queue] Testing of insertion in the queue.", "[queue]") {
    SECTION("Testing of insertion №1.") {
        Queue<int> q;
        
        for (int i = 2; i < 520; i = i * 2) {
            q.enqueue(i);
        }
        
        REQUIRE(q.front() == 2);
        REQUIRE(q.back() == 512);
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 9);
        
        q.~Queue();
    }
    SECTION("Testing of insertion №2.") {
        Queue<int> q = {2, 4, 8};
        
        for (int i = q.back() * 2; i < 520; i = i * 2) {
            q.enqueue(i);
        }
        
        REQUIRE(q.front() == 2);
        REQUIRE(q.back() == 512);
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 9);
        
        q.~Queue();
    }
}

TEST_CASE("[Queue] Testing of removing from the queue.", "[queue]") {
    SECTION("Testing of removing №1.") {
        Queue<int> q;
        
        for (int i = 2; i < 520; i = i * 2) {
            q.enqueue(i);
        }
        
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 9);
        
        for (int i = 2; i < 520; i = i * 2) {
            REQUIRE(q.dequeue() == i);
        }
        
        CHECK(q.empty());
        REQUIRE(q.count() == 0);
        
        q.~Queue();
    }
    SECTION("Testing of removing №2.") {
        Queue<int> q = {2, 4, 8};
        
        REQUIRE(q.dequeue() == 2);
        REQUIRE(q.dequeue() == 4);
        REQUIRE(q.dequeue() == 8);
        
        for (int i = 2; i < 520; i = i * 2) {
            q.enqueue(i);
        }
        
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 9);
        
        for (int i = 2; i < 520; i = i * 2) {
            REQUIRE(q.dequeue() == i);
        }
        
        CHECK(q.empty());
        REQUIRE(q.count() == 0);
        
        q.~Queue();
    }
}

TEST_CASE("[Queue] Testing of front and back elements from the queue.", "[queue]") {
    SECTION("Testing of front element.") {
        Queue<int> q;
        
        for (int i = 2; i < 520; i = i * 2) {
            q.enqueue(i);
        }
        
        REQUIRE(q.front() == 2);
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 9);
        
        for (int i = 2; i < 512; i = i * 2) {
            REQUIRE(q.front() == i);
            q.dequeue();
            REQUIRE(q.front() == (i * 2));
        }
        
        REQUIRE(q.front() == 512);
        REQUIRE(q.dequeue() == 512);
        
        CHECK(q.empty());
        REQUIRE(q.count() == 0);
        
        q.~Queue();
    }
    SECTION("Testing of back element.") {
        Queue<int> q;
        
        for (int i = 2; i < 520; i = i * 2) {
            q.enqueue(i);
        }
        
        REQUIRE(q.back() == 512);
        CHECK_FALSE(q.empty());
        REQUIRE(q.count() == 9);
        
        for (int i = 2; i < 520; i = i * 2) {
            REQUIRE(q.back() == 512); 
            q.dequeue();
        }
        
        CHECK(q.empty());
        REQUIRE(q.count() == 0);
        
        q.~Queue();
    }
}
