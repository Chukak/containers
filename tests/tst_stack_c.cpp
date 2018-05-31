#include "catch/catch.hpp"
#include "../src/stack.h"
#include <stdexcept>

TEST_CASE("[Stack] Initialization of the stack in C.", "[stack_c]") {
    SECTION("Initialization 1.") {
        stack *s = s_create_stack();
        
        REQUIRE(s != NULL); 
        REQUIRE(s->empty == 1);
        REQUIRE(s->count == 0);
        
        s_delete_stack(s);
    }
    SECTION("Initialization the NULL pointer.") {
        stack *s = (stack *)NULL;
        
        REQUIRE(s == NULL); 
        REQUIRE_THROWS_AS(s_delete_stack(s), std::runtime_error);
        REQUIRE_THROWS_WITH(s_front(s), "The pointer to `stack` is NULL. ");
    }
}

TEST_CASE("[Stack] Testing of insertion in the stack and removing from the stack in C.", "[stack_c]") {
    SECTION("Testing of insertion.") {
        stack *s = s_create_stack();
        
        for (int i = 2; i < 520; i = i * 2) {
            s_push(s, &i);
        }
        
        REQUIRE(s->count == 9);
        REQUIRE(s->empty == 0);
        int *front = (int *)s_front(s);
        REQUIRE(512 == *front);
        
        s_delete_stack(s);
        delete front;
    }
    SECTION("Testing of removing.") {
        stack *s = s_create_stack();
        
        for (int i = 2; i < 520; i = i * 2) {
            s_push(s, &i);
        }
        
        REQUIRE(s->empty == 0);
        REQUIRE(s->count == 9);
        
        int *result = ((int *)0);
        for (int i = 512; i > 1; i = i / 2) {
            result = (int *)s_pop(s);
            REQUIRE(*result == i);
        }
        
        CHECK(s->empty == 1);
        REQUIRE(s->count == 0);
        
        s_delete_stack(s);
        delete result;
    }
}

TEST_CASE("[Stack] Testing of front element from the stack in C.", "[stack_c]") {
    SECTION("Testiong of front element.") {
        stack *s = s_create_stack();
        
        for (int i = 2; i < 520; i = i * 2) {
            s_push(s, &i);
        }
        
        int *front = (int *)s_front(s);
        REQUIRE(512 == *front);
        REQUIRE(s->empty == 0);
        REQUIRE(s->count == 9);
        
        for (int i = 512; i > 2; i = i / 2) {
            front = (int *)s_front(s);
            REQUIRE(i == *front);
            s_pop(s);
            front = (int *)s_front(s);
            REQUIRE((i / 2) == *front);
        }
        
        front = (int *)s_front(s);
        REQUIRE(2 == *front);
        int *temp = (int *)s_pop(s);
        REQUIRE(*temp == 2);
        
        front = (int *)s_front(s);
        REQUIRE(front == NULL);
        
        REQUIRE(s->empty == 1);
        REQUIRE(s->count == 0);
        
        s_delete_stack(s);
        delete front;
        delete temp;
    }
}

TEST_CASE("[Stack] Testing situations, where pointers is NULL.", "[stack_c]") {
    SECTION("Testing of NULL pointers.") {
        stack *ss = s_create_stack();
        
        REQUIRE_THROWS_AS(s_push(ss, NULL), std::runtime_error);
        REQUIRE_THROWS_WITH(s_push(ss, NULL), "The pointer to an element is NULL.");
        
        s_delete_stack(ss);
        
        stack *s = (stack *)NULL;
        REQUIRE(s == NULL);
        
        REQUIRE_THROWS_AS(s_pop(s), std::runtime_error);
        REQUIRE_THROWS_WITH(s_pop(s), "The pointer to `stack` is NULL. ");
        
        REQUIRE_THROWS_AS(s_front(s), std::runtime_error);
        REQUIRE_THROWS_WITH(s_front(s), "The pointer to `stack` is NULL. ");
    }
}
