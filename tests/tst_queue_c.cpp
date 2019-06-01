#include <catch.hpp>
#include "queue.h"
#include <stdexcept>

using namespace pure_c;

TEST_CASE("[queue] Initialization of the queue in C.", "[queue_c]") {
	SECTION("Initialization 1.") {
		queue * q = queue_create();

		REQUIRE(q != NULL);
		REQUIRE(q->empty == 1);
		REQUIRE(q->count == 0);

		queue_delete(q);
	}
	SECTION("Initialization the NULL pointer.") {
		queue * q = (queue *)NULL;

		REQUIRE(q == NULL);
		REQUIRE_THROWS_AS(queue_delete(q), std::runtime_error);
		REQUIRE_THROWS_WITH(queue_front(q), "The pointer to `queue` is NULL. ");
	}
}

TEST_CASE("[queue] Testing of insertion in the queue and removing from the queue in C.", "[queue_c]") {
	SECTION("Testing of insertion.") {
		queue * q = queue_create();

		for (int i = 2; i < 520; i = i * 2) {
			queue_enqueue(q, &i);
		}

		REQUIRE(q->count == 9);
		REQUIRE(q->empty == 0);
		int * front = (int *)queue_front(q);
		REQUIRE(2 == *front);
		int * back = (int *)queue_back(q);
		REQUIRE(512 == *back);

		queue_delete(q);
		delete front;
		delete back;
	}
	SECTION("Testing of removing.") {
		queue * q = queue_create();

		for (int i = 2; i < 520; i = i * 2) {
			queue_enqueue(q, &i);
		}

		REQUIRE(q->empty == 0);
		REQUIRE(q->count == 9);

		int * result = ((int *)0);
		for (int i = 2; i < 520; i = i * 2) {
			result = (int *)queue_dequeue(q);
			REQUIRE(*result == i);
		}

		CHECK(q->empty == 1);
		REQUIRE(q->count == 0);

		queue_delete(q);
		delete result;
	}
}

TEST_CASE("[queue] Testing of front and back elements from the queue in C.", "[queue_c]") {
	SECTION("Testiong of front element.") {
		queue * q = queue_create();

		for (int i = 2; i < 520; i = i * 2) {
			queue_enqueue(q, &i);
		}

		int * front = (int *)queue_front(q);
		REQUIRE(2 == *front);
		REQUIRE(q->empty == 0);
		REQUIRE(q->count == 9);

		for (int i = 2; i < 512; i = i * 2) {
			front = (int *)queue_front(q);
			REQUIRE(i == *front);
			queue_dequeue(q);
			front = (int *)queue_front(q);
			REQUIRE((i * 2) == *front);
		}

		front = (int *)queue_front(q);
		REQUIRE(512 == *front);
		int * temp = (int *)queue_dequeue(q);
		REQUIRE(*temp == 512);

		front = (int *)queue_front(q);
		REQUIRE(front == NULL);

		REQUIRE(q->empty == 1);
		REQUIRE(q->count == 0);

		queue_delete(q);
		delete front;
		delete temp;
	}
	SECTION("Testing of back element.") {
		queue * q = queue_create();

		for (int i = 2; i < 520; i = i * 2) {
			queue_enqueue(q, &i);
		}

		int * back = (int *)queue_back(q);
		REQUIRE(*back == 512);
		REQUIRE(q->empty == 0);
		REQUIRE(q->count == 9);

		for (int i = 2; i < 520; i = i * 2) {
			back = (int *)queue_back(q);
			REQUIRE(*back == 512);
			queue_dequeue(q);
		}

		back = (int *)queue_back(q);
		REQUIRE(back == NULL);

		REQUIRE(q->empty == 1);
		REQUIRE(q->count == 0);

		queue_delete(q);
		delete back;
	}
}

TEST_CASE("[queue] Testing situations, where pointers is NULL.", "[queue_c]") {
	SECTION("Testing of NULL pointers.") {
		queue * qq = queue_create();

		REQUIRE_THROWS_AS(queue_enqueue(qq, NULL), std::runtime_error);
		REQUIRE_THROWS_WITH(queue_enqueue(qq, NULL), "The pointer to an element is NULL.");

		queue_delete(qq);

		queue * q = (queue *)NULL;
		REQUIRE(q == NULL);

		REQUIRE_THROWS_AS(queue_dequeue(q), std::runtime_error);
		REQUIRE_THROWS_WITH(queue_dequeue(q), "The pointer to `queue` is NULL. ");

		REQUIRE_THROWS_AS(queue_front(q), std::runtime_error);
		REQUIRE_THROWS_WITH(queue_front(q), "The pointer to `queue` is NULL. ");

		REQUIRE_THROWS_AS(queue_back(q), std::runtime_error);
		REQUIRE_THROWS_WITH(queue_back(q), "The pointer to `queue` is NULL. ");
	}
}
