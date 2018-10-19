#include <catch.hpp>
#include "queue.h"
#include <stdexcept>

TEST_CASE("[queue] Initialization of the queue in C.", "[queue_c]") {
    SECTION("Initialization 1.") {
        queue *q = q_create_queue();
        
        REQUIRE(q != NULL); 
        REQUIRE(q->empty == 1);
        REQUIRE(q->count == 0);
        
        q_delete_queue(q);
    }
    SECTION("Initialization the NULL pointer.") {
        queue *q = (queue *)NULL;
        
        REQUIRE(q == NULL); 
        REQUIRE_THROWS_AS(q_delete_queue(q), std::runtime_error);
        REQUIRE_THROWS_WITH(q_front(q), "The pointer to `queue` is NULL. ");
    }
}

TEST_CASE("[queue] Testing of insertion in the queue and removing from the queue in C.", "[queue_c]") {
    SECTION("Testing of insertion.") {
        queue *q = q_create_queue();
        
        for (int i = 2; i < 520; i = i * 2) {
            q_enqueue(q, &i);
        }
        
        REQUIRE(q->count == 9);
        REQUIRE(q->empty == 0);
        int *front = (int *)q_front(q);
        REQUIRE(2 == *front);
        int *back = (int *)q_back(q);
        REQUIRE(512 == *back);
        
        q_delete_queue(q);
        delete front;
        delete back;
    }
    SECTION("Testing of removing.") {
        queue *q = q_create_queue();
        
        for (int i = 2; i < 520; i = i * 2) {
            q_enqueue(q, &i);
        }
        
        REQUIRE(q->empty == 0);
        REQUIRE(q->count == 9);
        
        int *result = ((int *)0);
        for (int i = 2; i < 520; i = i * 2) {
            result = (int *)q_dequeue(q);
            REQUIRE(*result == i);
        }
        
        CHECK(q->empty == 1);
        REQUIRE(q->count == 0);
        
        q_delete_queue(q);
        delete result;
    }
}

TEST_CASE("[queue] Testing of front and back elements from the queue in C.", "[queue_c]") {
    SECTION("Testiong of front element.") {
        queue *q = q_create_queue();
        
        for (int i = 2; i < 520; i = i * 2) {
            q_enqueue(q, &i);
        }
        
        int *front = (int *)q_front(q);
        REQUIRE(2 == *front);
        REQUIRE(q->empty == 0);
        REQUIRE(q->count == 9);
        
        for (int i = 2; i < 512; i = i * 2) {
            front = (int *)q_front(q);
            REQUIRE(i == *front);
            q_dequeue(q);
            front = (int *)q_front(q);
            REQUIRE((i * 2) == *front);
        }
        
        front = (int *)q_front(q);
        REQUIRE(512 == *front);
        int *temp = (int *)q_dequeue(q);
        REQUIRE(*temp == 512);
        
        front = (int *)q_front(q);
        REQUIRE(front == NULL);
        
        REQUIRE(q->empty == 1);
        REQUIRE(q->count == 0);
        
        q_delete_queue(q);
        delete front;
        delete temp;
    }
    SECTION("Testing of back element.") {
        queue *q = q_create_queue();
        
        for (int i = 2; i < 520; i = i * 2) {
            q_enqueue(q, &i);
        }
        
        int *back = (int *)q_back(q);
        REQUIRE(*back == 512);
        REQUIRE(q->empty == 0);
        REQUIRE(q->count == 9);
        
        for (int i = 2; i < 520; i = i * 2) {
            back = (int *)q_back(q);
            REQUIRE(*back == 512); 
            q_dequeue(q);
        }
        
        back = (int *)q_back(q);
        REQUIRE(back == NULL);
        
        REQUIRE(q->empty == 1);
        REQUIRE(q->count == 0);
        
        q_delete_queue(q);
        delete back;
    }
}

TEST_CASE("[queue] Testing situations, where pointers is NULL.", "[queue_c]") {
    SECTION("Testing of NULL pointers.") {
        queue *qq = q_create_queue();
        
        REQUIRE_THROWS_AS(q_enqueue(qq, NULL), std::runtime_error);
        REQUIRE_THROWS_WITH(q_enqueue(qq, NULL), "The pointer to an element is NULL.");
        
        q_delete_queue(qq);
        
        queue *q = (queue *)NULL;
        REQUIRE(q == NULL);
        
        REQUIRE_THROWS_AS(q_dequeue(q), std::runtime_error);
        REQUIRE_THROWS_WITH(q_dequeue(q), "The pointer to `queue` is NULL. ");
        
        REQUIRE_THROWS_AS(q_front(q), std::runtime_error);
        REQUIRE_THROWS_WITH(q_front(q), "The pointer to `queue` is NULL. ");
        
        REQUIRE_THROWS_AS(q_back(q), std::runtime_error);
        REQUIRE_THROWS_WITH(q_back(q), "The pointer to `queue` is NULL. ");
    }
}
