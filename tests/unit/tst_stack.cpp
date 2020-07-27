#include <catch.hpp>
#include "stack.h"

TEST_CASE("[Stack] Testing the initialization of the stack.", "[stack]") {
	SECTION("Testing the default constructor.") {
		Stack<int> s;
		CHECK(s.is_empty());
		REQUIRE(s.count() == 0);
	}
	SECTION("Testing the initializer list.") {
		Stack<int> s = {1, 2, 3, 4, 5, 6};
		CHECK_FALSE(s.is_empty());
		REQUIRE(s.count() == 6);
		REQUIRE(s.front() == 6);
	}
	SECTION("Testing the copy constructor.") {
		Stack<int> orig = {1, 2, 3};
		Stack<int> s(orig);
		orig.~Stack();
		CHECK_FALSE(s.is_empty());
		REQUIRE(s.count() == 3);
		REQUIRE(s.front() == 3);
	}
	SECTION("Testing the move constructor.") {
		Stack<int> orig = {1, 2, 3};
		Stack<int> s(std::move(orig));

		REQUIRE(orig.count() == 0);
		CHECK(orig.is_empty());
		REQUIRE_FALSE(orig.front() == 3);
		CHECK_FALSE(s.is_empty());
		REQUIRE(s.count() == 3);
		REQUIRE(s.front() == 3);
	}
}

TEST_CASE("[Stack] Testing the insertion into the stack.", "[stack]") {
	SECTION("Testing the insertion №1.") {
		Stack<int> s;

		for (int i = 2; i < 520; i = i * 2) {
			s.push(i);
		}

		REQUIRE(s.front() == 512);
		CHECK_FALSE(s.is_empty());
		REQUIRE(s.count() == 9);
	}
	SECTION("Testing the insertion №2.") {
		Stack<int> s = {2, 4, 8};

		for (int i = 16; i < 520; i = i * 2) {
			s.push(i);
		}

		REQUIRE(s.front() == 512);
		CHECK_FALSE(s.is_empty());
		REQUIRE(s.count() == 9);
	}
}

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
	}
}

TEST_CASE("[Stack] Testing the getting front element from the stack.", "[stack]") {
	SECTION("Testing the getting front element.") {
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
	}
}

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
	}
	SECTION("Testing that the iterators and nullptr are the same.") {
		Stack<int> s;

		REQUIRE(s.begin() == s.end());
		REQUIRE(s.begin() == nullptr);
		REQUIRE(s.end() == nullptr);
	}
}
