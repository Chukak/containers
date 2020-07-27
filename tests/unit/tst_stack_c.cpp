#include <catch.hpp>
#include <stack.h>
#include <stdexcept>

using namespace pure_c;

TEST_CASE("[Stack] Testing the initialization of the stack in C code.", "[stack_c]")
{
    SECTION("Testing the initialization 1.")
    {
        stack *s = stack_create();

	REQUIRE(s != NULL);
	REQUIRE(s->empty == 1);
	REQUIRE(s->count == 0);

        stack_delete(s);
    }
}

TEST_CASE("[Stack] Testing the insertion into the stack and removing from the stack in C.", "[stack_c]")
{
    SECTION("Testing the insertion.")
    {
        stack *s = stack_create();

	for(int i = 2; i < 520; i = i * 2) {
	    stack_push(s, &i, sizeof(i));
	}

	REQUIRE(s->count == 9);
	REQUIRE(s->empty == 0);
	int *front = (int *)stack_front(s);
	REQUIRE(512 == *front);
	free(front);

        stack_delete(s);
    }
    SECTION("Testing the removing.")
    {
        stack *s = stack_create();

	for(int i = 2; i < 520; i = i * 2) {
	    stack_push(s, &i, sizeof(i));
	}

	REQUIRE(s->empty == 0);
	REQUIRE(s->count == 9);

	int *result = ((int *)0);
	for(int i = 512; i > 1; i = i / 2) {
	    result = (int *)stack_pop(s);
	    REQUIRE(*result == i);
	    free(result);
	}

	CHECK(s->empty == 1);
	REQUIRE(s->count == 0);

        stack_delete(s);
    }
}

TEST_CASE("[Stack] Testing the getting front element from the stack in C.", "[stack_c]")
{
    SECTION("Testiong the getting front element.")
    {
        stack *s = stack_create();

	for(int i = 2; i < 520; i = i * 2) {
	    stack_push(s, &i, sizeof(i));
	}

	int *front = (int *)stack_front(s);
	REQUIRE(512 == *front);
	free(front);

	REQUIRE(s->empty == 0);
	REQUIRE(s->count == 9);

	for(int i = 512; i > 2; i = i / 2) {
	    front = (int *)stack_front(s);
	    REQUIRE(i == *front);
	    free(front);

	    int *result = (int *)stack_pop(s);
	    REQUIRE(i == *result);
	    free(result);

	    front = (int *)stack_front(s);
	    REQUIRE((i / 2) == *front);
	    free(front);
	}

	front = (int *)stack_front(s);
	REQUIRE(2 == *front);
	free(front);

	int *temp = (int *)stack_pop(s);
	REQUIRE(*temp == 2);
	free(temp);

	front = (int *)stack_front(s);
	REQUIRE(front == NULL);
	free(front);

	REQUIRE(s->empty == 1);
	REQUIRE(s->count == 0);

        stack_delete(s);
    }
}
