#include <catch.hpp>
#include "queue.h"
#include <stdexcept>

using namespace pure_c;

TEST_CASE("[queue] Testing the initialization of the queue in C code.", "[queue_c]")
{
    SECTION("Testing the initialization 1.")
    {
        queue *q = queue_create();

	REQUIRE(q != NULL);
	REQUIRE(q->empty == 1);
	REQUIRE(q->count == 0);

        queue_delete(q);
    }
}

TEST_CASE("[queue] Testing the insertion into the queue and removing from the queue in C code.", "[queue_c]")
{
    SECTION("Testing the insertion.")
    {
        queue *q = queue_create();

	for(int i = 2; i < 520; i = i * 2) {
	    queue_enqueue(q, &i, sizeof(i));
	}

	REQUIRE(q->count == 9);
	REQUIRE(q->empty == 0);
	int *front = (int *)queue_front(q);
	REQUIRE(2 == *front);
	int *back = (int *)queue_back(q);
	REQUIRE(512 == *back);

	queue_delete(q);
	free(front);
	free(back);
    }
    SECTION("Testing the removing.")
    {
        queue *q = queue_create();

	for(int i = 2; i < 520; i = i * 2) {
	    queue_enqueue(q, &i, sizeof(i));
	}

	REQUIRE(q->empty == 0);
	REQUIRE(q->count == 9);

	int *result = ((int *)0);
	for(int i = 2; i < 520; i = i * 2) {
	    result = (int *)queue_dequeue(q);
	    REQUIRE(*result == i);
	    free(result);
	}

	CHECK(q->empty == 1);
	REQUIRE(q->count == 0);

        queue_delete(q);
    }
}

TEST_CASE("[queue] Testing the getting front and back elements from the queue in C.", "[queue_c]")
{
    SECTION("Testiong the getting front element.")
    {
        queue *q = queue_create();

	for(int i = 2; i < 520; i = i * 2) {
	    queue_enqueue(q, &i, sizeof(i));
	}

	int *front = (int *)queue_front(q);
	REQUIRE(2 == *front);
	REQUIRE(q->empty == 0);
	REQUIRE(q->count == 9);
	free(front);

	for(int i = 2; i < 512; i = i * 2) {
	    front = (int *)queue_front(q);
	    REQUIRE(i == *front);
	    free(front);

	    int *result = (int *)queue_dequeue(q);
	    REQUIRE(i == *result);
	    free(result);

	    front = (int *)queue_front(q);
	    REQUIRE((i * 2) == *front);
	    free(front);
	}

	front = (int *)queue_front(q);
	REQUIRE(512 == *front);
	free(front);

	int *temp = (int *)queue_dequeue(q);
	REQUIRE(*temp == 512);
	free(temp);

	front = (int *)queue_front(q);
	REQUIRE(front == NULL);
	free(front);

	REQUIRE(q->empty == 1);
	REQUIRE(q->count == 0);

	queue_delete(q);
    }
    SECTION("Testing the getting back element.")
    {
        queue *q = queue_create();

	for(int i = 2; i < 520; i = i * 2) {
	    queue_enqueue(q, &i, sizeof(i));
	}

	int *back = (int *)queue_back(q);
	REQUIRE(*back == 512);
	REQUIRE(q->empty == 0);
	REQUIRE(q->count == 9);
	free(back);

	for(int i = 2; i < 520; i = i * 2) {
	    back = (int *)queue_back(q);
	    REQUIRE(*back == 512);
	    free(back);

	    int *result = (int *)queue_dequeue(q);
	    REQUIRE(i == *result);
	    free(result);
	}

	back = (int *)queue_back(q);
	REQUIRE(back == NULL);
	free(back);

	REQUIRE(q->empty == 1);
	REQUIRE(q->count == 0);

        queue_delete(q);
    }
}
