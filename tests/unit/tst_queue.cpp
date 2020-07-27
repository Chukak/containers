#include <catch.hpp>
#include "queue.h"

TEST_CASE("[Queue] Testing the initialization the queue.", "[queue]") {
	SECTION("Testing the default constructor.") {
		Queue<int> q;
		CHECK(q.is_empty());
		REQUIRE(q.count() == 0);
	}
	SECTION("Testing the initializer list.") {
		Queue<int> q = {1, 2, 3, 4, 5, 6};
		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 6);
		REQUIRE(q.back() == 6);
		REQUIRE(q.front() == 1);
	}
	SECTION("Testing the copy constructor.") {
		Queue<int> orig = {1, 2, 3};
		Queue<int> q(orig);
		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 3);
		REQUIRE(q.back() == 3);
		REQUIRE(q.front() == 1);
	}
	SECTION("Testing the move constructor.") {
		Queue<int> orig = {1, 2, 3};
		Queue<int> q(std::move(orig));

		REQUIRE(orig.count() == 0);
		CHECK(orig.is_empty());
		REQUIRE_FALSE(orig.front() == 1);
		REQUIRE_FALSE(orig.back() == 3);

		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 3);
		REQUIRE(q.back() == 3);
		REQUIRE(q.front() == 1);
	}
}

TEST_CASE("[Queue] Testing the insertion into the queue.", "[queue]") {
	SECTION("Testing the insertion №1.") {
		Queue<int> q;

		for (int i = 2; i < 520; i = i * 2) {
			q.enqueue(i);
		}

		REQUIRE(q.front() == 2);
		REQUIRE(q.back() == 512);
		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 9);
	}
	SECTION("Testing the insertion №2.") {
		Queue<int> q = {2, 4, 8};

		for (int i = q.back() * 2; i < 520; i = i * 2) {
			q.enqueue(i);
		}

		REQUIRE(q.front() == 2);
		REQUIRE(q.back() == 512);
		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 9);
	}
}

TEST_CASE("[Queue] Testing the removing from the queue.", "[queue]") {
	SECTION("Testing the removing №1.") {
		Queue<int> q;

		for (int i = 2; i < 520; i = i * 2) {
			q.enqueue(i);
		}

		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 9);

		for (int i = 2; i < 520; i = i * 2) {
			REQUIRE(q.dequeue() == i);
		}

		CHECK(q.is_empty());
		REQUIRE(q.count() == 0);
	}
	SECTION("Testing the removing №2.") {
		Queue<int> q = {2, 4, 8};

		REQUIRE(q.dequeue() == 2);
		REQUIRE(q.dequeue() == 4);
		REQUIRE(q.dequeue() == 8);

		for (int i = 2; i < 520; i = i * 2) {
			q.enqueue(i);
		}

		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 9);

		for (int i = 2; i < 520; i = i * 2) {
			REQUIRE(q.dequeue() == i);
		}

		CHECK(q.is_empty());
		REQUIRE(q.count() == 0);
	}
}

TEST_CASE("[Queue] Testing the getting front and back elements from the queue.", "[queue]") {
	SECTION("Testing the getting front element.") {
		Queue<int> q;

		for (int i = 2; i < 520; i = i * 2) {
			q.enqueue(i);
		}

		REQUIRE(q.front() == 2);
		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 9);

		for (int i = 2; i < 512; i = i * 2) {
			REQUIRE(q.front() == i);
			q.dequeue();
			REQUIRE(q.front() == (i * 2));
		}

		REQUIRE(q.front() == 512);
		REQUIRE(q.dequeue() == 512);

		CHECK(q.is_empty());
		REQUIRE(q.count() == 0);
	}
	SECTION("Testing the getting back element.") {
		Queue<int> q;

		for (int i = 2; i < 520; i = i * 2) {
			q.enqueue(i);
		}

		REQUIRE(q.back() == 512);
		CHECK_FALSE(q.is_empty());
		REQUIRE(q.count() == 9);

		for (int i = 2; i < 520; i = i * 2) {
			REQUIRE(q.back() == 512);
			q.dequeue();
		}

		CHECK(q.is_empty());
		REQUIRE(q.count() == 0);
	}
}

TEST_CASE("[Queue] Testing the iterators of the queue.", "[queue]") {
	SECTION("Testing the iterators.") {
		Queue<int> q = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		Queue<int>::iterator iter = q.begin();
		REQUIRE_FALSE(iter == nullptr);
		REQUIRE(iter != nullptr);

		unsigned test_var = 0;
		for (auto it = q.begin(); it != q.end(); ++it) {
			test_var++;
			REQUIRE(*it == test_var);
		}
		REQUIRE(test_var == 10);

		test_var = 0;
		for (auto it = q.begin(); it != q.end(); it++) {
			test_var++;
			REQUIRE(it->value == test_var);
		}
		REQUIRE(test_var == 10);

		REQUIRE_FALSE(q.begin() == q.end());
		REQUIRE(q.begin() != q.end());
	}
	SECTION("Testing that the iterators and nullptr are the same.") {
		Queue<int> q;

		REQUIRE(q.begin() == q.end());
		REQUIRE(q.begin() == nullptr);
		REQUIRE(q.end() == nullptr);
	}
}
