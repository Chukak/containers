#include <catch.hpp>
#include <stack.h>
#include <stdexcept>

using namespace pure_c;

TEST_CASE("[Stack] Testing the initialization of the stack in C code.", "[stack_c]") {
	SECTION("Testing the initialization 1.") {
		stack * s = stack_create();

		REQUIRE(s != NULL);
		REQUIRE(s->empty == 1);
		REQUIRE(s->count == 0);

		stack_delete(s);
	}
	SECTION("Testing the initialization the NULL pointer.") {
		stack * s = (stack *)NULL;

		REQUIRE(s == NULL);
		REQUIRE_THROWS_AS(stack_delete(s), std::runtime_error);
		REQUIRE_THROWS_WITH(stack_front(s), "The pointer to `stack` is NULL. ");
	}
}

TEST_CASE("[Stack] Testing the insertion into the stack and removing from the stack in C.", "[stack_c]") {
	SECTION("Testing the insertion.") {
		stack * s = stack_create();

		for (int i = 2; i < 520; i = i * 2) {
			stack_push(s, &i);
		}

		REQUIRE(s->count == 9);
		REQUIRE(s->empty == 0);
		int * front = (int *)stack_front(s);
		REQUIRE(512 == *front);

		stack_delete(s);
		delete front;
	}
	SECTION("Testing the removing.") {
		stack * s = stack_create();

		for (int i = 2; i < 520; i = i * 2) {
			stack_push(s, &i);
		}

		REQUIRE(s->empty == 0);
		REQUIRE(s->count == 9);

		int * result = ((int *)0);
		for (int i = 512; i > 1; i = i / 2) {
			result = (int *)stack_pop(s);
			REQUIRE(*result == i);
		}

		CHECK(s->empty == 1);
		REQUIRE(s->count == 0);

		stack_delete(s);
		delete result;
	}
}

TEST_CASE("[Stack] Testing the getting front element from the stack in C.", "[stack_c]") {
	SECTION("Testiong the getting front element.") {
		stack * s = stack_create();

		for (int i = 2; i < 520; i = i * 2) {
			stack_push(s, &i);
		}

		int * front = (int *)stack_front(s);
		REQUIRE(512 == *front);
		REQUIRE(s->empty == 0);
		REQUIRE(s->count == 9);

		for (int i = 512; i > 2; i = i / 2) {
			front = (int *)stack_front(s);
			REQUIRE(i == *front);
			stack_pop(s);
			front = (int *)stack_front(s);
			REQUIRE((i / 2) == *front);
		}

		front = (int *)stack_front(s);
		REQUIRE(2 == *front);
		int * temp = (int *)stack_pop(s);
		REQUIRE(*temp == 2);

		front = (int *)stack_front(s);
		REQUIRE(front == NULL);

		REQUIRE(s->empty == 1);
		REQUIRE(s->count == 0);

		stack_delete(s);
		delete front;
		delete temp;
	}
}

TEST_CASE("[Stack] Testing situations, where pointers is NULL.", "[stack_c]") {
	SECTION("Testing of NULL pointers.") {
		stack * ss = stack_create();

		REQUIRE_THROWS_AS(stack_push(ss, NULL), std::runtime_error);
		REQUIRE_THROWS_WITH(stack_push(ss, NULL), "The pointer to an element is NULL.");

		stack_delete(ss);

		stack * s = (stack *)NULL;
		REQUIRE(s == NULL);

		REQUIRE_THROWS_AS(stack_pop(s), std::runtime_error);
		REQUIRE_THROWS_WITH(stack_pop(s), "The pointer to `stack` is NULL. ");

		REQUIRE_THROWS_AS(stack_front(s), std::runtime_error);
		REQUIRE_THROWS_WITH(stack_front(s), "The pointer to `stack` is NULL. ");
	}
}
