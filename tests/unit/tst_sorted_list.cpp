#include <catch.hpp>
#include "sorted_list.h"

TEST_CASE("[sorted_list] Testing the initialization of the sorted list.", "[sorted list]")
{
    SECTION("Testing the default constructor.")
    {
        sorted_list<int> list;
        CHECK(list.is_empty());
        REQUIRE(list.count() == 0);
    }
    SECTION("Testing the initializer list.")
    {
        sorted_list<int> list = {1, 5, 2, 6, 3, 4};
        CHECK_FALSE(list.is_empty());
        REQUIRE(list.count() == 6);
        REQUIRE(list.back() == 6);
        REQUIRE(list.front() == 1);
    }
    SECTION("Testing the copy constructor.")
    {
        sorted_list<int> orig = {3, 2, 1};
        sorted_list<int> list(orig);
        CHECK_FALSE(list.is_empty());
        REQUIRE(list.count() == 3);
        REQUIRE(list.back() == 3);
        REQUIRE(list.front() == 1);
    }
    SECTION("Testing the move constructor.")
    {
        sorted_list<int> orig = {3, 2, 1};
        sorted_list<int> list(std::move(orig));

	REQUIRE(orig.count() == 0);
	CHECK(orig.is_empty());
	REQUIRE_FALSE(orig.front() == 1);
	REQUIRE_FALSE(orig.back() == 3);
	CHECK_FALSE(list.is_empty());
	REQUIRE(list.count() == 3);
	REQUIRE(list.back() == 3);
	REQUIRE(list.front() == 1);
    }
}

TEST_CASE("[sorted_list] Testing the insertion into the sorted list.", "[sorted list]")
{
    SECTION("Testing the insertion №1.")
    {
        sorted_list<int> list;

	list.push(1);
	list.push(-1);
	list.push(12);
	list.push(-5);
	list.push(2);
	list.push(19);
	list.push(109);
	list.push(-54);
	list.push(0);

	REQUIRE(list.front() == -54);
	REQUIRE(list.back() == 109);
	CHECK_FALSE(list.is_empty());
	REQUIRE(list.count() == 9);
    }
    SECTION("Testing the insertion №2.")
    {
        sorted_list<int> list = {-75, 1, 865};

	list.push(1);
	list.push(-1);
	list.push(12);
	list.push(-5);
	list.push(2);
	list.push(19);
	list.push(109);
	list.push(-54);
	list.push(0);

	REQUIRE(list.front() == -75);
	REQUIRE(list.back() == 865);
	CHECK_FALSE(list.is_empty());
	REQUIRE(list.count() == 12);
    }
}

TEST_CASE("[sorted_list] Testing the removing from the sorted_list.", "[sorted list]")
{
    SECTION("Testing the removing №1.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	REQUIRE(list.front() == -25);
	REQUIRE(list.back() == 20);
	CHECK_FALSE(list.is_empty());
	REQUIRE(list.count() == 10);

	int t = -25;
	while(list.count()) {
	    REQUIRE(t == list.pop_front());
	    t += 5;
	}

	CHECK(list.is_empty());
	REQUIRE(list.count() == 0);
    }
    SECTION("Testing the removing №2.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	REQUIRE(list.front() == -25);
	REQUIRE(list.back() == 20);
	CHECK_FALSE(list.is_empty());
	REQUIRE(list.count() == 10);

	int t = 20;
	while(list.count()) {
	    REQUIRE(t == list.pop_back());
	    t -= 5;
	}

	CHECK(list.is_empty());
	REQUIRE(list.count() == 0);
    }
}

TEST_CASE("[sorted_list] Testing the getting front and back elements from the sorted list.", "[sorted list]")
{
    SECTION("Testing the getting front element.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	REQUIRE(list.front() == -25);
	REQUIRE(list.back() == 20);
	CHECK_FALSE(list.is_empty());
	REQUIRE(list.count() == 10);

	int t = -25;
	while(list.count()) {
	    REQUIRE(t == list.front());
	    list.pop_front();
	    t += 5;
	}

	CHECK(list.is_empty());
	REQUIRE(list.count() == 0);
    }
    SECTION("Testing the getting back element.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	REQUIRE(list.front() == -25);
	REQUIRE(list.back() == 20);
	CHECK_FALSE(list.is_empty());
	REQUIRE(list.count() == 10);

	int t = 20;
	while(list.count()) {
	    REQUIRE(t == list.back());
	    list.pop_back();
	    t -= 5;
	}

	CHECK(list.is_empty());
	REQUIRE(list.count() == 0);
    }
}

TEST_CASE("[sorted_list] Testing the getting an element from a position from the sorted list.", "[sorted list]")
{
    SECTION("Testing the operator [].")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	int t = -25;
	for(unsigned int i = 0; i < list.count(); i++) {
	    REQUIRE(t == list[static_cast<int>(i)]);
	    t += 5;
	};
    }
    SECTION("Testing the function `at()`.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	int t = -25;
	for(unsigned int i = 0; i < list.count(); i++) {
	    REQUIRE(t == list.at(static_cast<int>(i)));
	    t += 5;
	}
    }
}

TEST_CASE("[sorted_list] Testing the removing an element from the position from the sorted list.", "[sorted list]")
{
    SECTION("Testing the function `remove` №1.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	int t = -25;
	for(std::size_t i = 0; i != list.count();) {
	    REQUIRE(t == list.remove(0));
	    t += 5;
	}
    }
    SECTION("Testing the function `remove` №2.")
    {
        sorted_list<int> list;

	list.push(10);
	list.push(-5);
	list.push(0);
	list.push(5);
	list.push(-10);

	REQUIRE(0 == list.remove(2));
	REQUIRE(-10 == list.remove(0));
	REQUIRE(10 == list.remove(2));
	REQUIRE(-5 == list.remove(0));
	REQUIRE(5 == list.remove(0));
    }
}

TEST_CASE("[sorted_list] Testing the iterators of the sorted list.", "[sorted list]")
{
    SECTION("Testing the iterators №1.")
    {
        sorted_list<int> list = {10, -8, 6, 0, 8, -10, -2, 2, 4, -4, -6};

	sorted_list<int>::iterator iter = list.begin();
	REQUIRE_FALSE(iter == nullptr);
	REQUIRE(iter != nullptr);

	int test_var = -12;
	for(auto it = list.begin(); it != list.end(); ++it) {
	    test_var += 2;
	    REQUIRE(*it == test_var);
	}
	REQUIRE(test_var == 10);

	test_var = -12;
	for(auto it = list.begin(); it != list.end(); it++) {
	    test_var += 2;
	    REQUIRE(it->value == test_var);
	}
	REQUIRE(test_var == 10);

	REQUIRE_FALSE(list.begin() == list.end());
	REQUIRE(list.begin() != list.end());
    }
    SECTION("Testing the iterators №2.")
    {
        sorted_list<int> list = {10, -8, 6, 0, 8, -10, -2, 2, 4, -4, -6};

	sorted_list<int>::iterator iter = list.end();
	REQUIRE(iter == nullptr);
	REQUIRE_FALSE(iter != nullptr);

	unsigned test_var = 12;
	auto it = list.end();
	while(--it != list.begin()) {
	    test_var -= 2;
	    REQUIRE(*it == test_var);
	}
	REQUIRE(test_var == -8);
	REQUIRE(*list.begin() == -10);

	test_var = 12;
	it = list.end();
	while(--it != list.begin()) {
	    test_var -= 2;
	    REQUIRE(it->value == test_var);
	}
	REQUIRE(test_var == -8);
	REQUIRE(*list.begin() == -10);

	REQUIRE_FALSE(list.begin() == list.end());
	REQUIRE(list.begin() != list.end());
    }
    SECTION("Testing that the iterators and nullptr are the same.")
    {
        sorted_list<int> list;

	REQUIRE(list.begin() == list.end());
	REQUIRE(list.begin() == nullptr);
	REQUIRE(list.end() == nullptr);
    }
}

TEST_CASE("[sorted_list] Testing the reverse the sorted list.", "[sorted list]")
{
    SECTION("Testing the function `reverse` №1.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	REQUIRE(list.count() == 10);
	REQUIRE(list.front() == -25);
	REQUIRE(list.back() == 20);
	list.reverse();
	REQUIRE(list.count() == 10);

	REQUIRE(list.front() == 20);
	REQUIRE(list.back() == -25);
    }
    SECTION("Testing the function `reverse` №2.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	REQUIRE(list.count() == 10);
	list.reverse();
	REQUIRE(list.count() == 10);

	REQUIRE(list.front() == 20);
	REQUIRE(list.back() == -25);

	list.push(25);
	REQUIRE(list.front() == 25);
	list.push(-30);
	REQUIRE(list.back() == -30);
	list.push(15);
	REQUIRE(list.count() == 13);
    }
}

TEST_CASE("[sorted_list] Testing the cleaning of the sorted list.", "[sorted list]")
{
    SECTION("Testing the function `clear`.")
    {
        sorted_list<int> list;

	list.push(-15);
	list.push(10);
	list.push(-5);
	list.push(20);
	list.push(0);
	list.push(5);
	list.push(-10);
	list.push(-20);
	list.push(-25);
	list.push(15);

	REQUIRE(list.count() == 10);

	list.clear();

        REQUIRE(list.count() == 0);
    }
}

TEST_CASE("[sorted_list] Testing the custom function to compare elements in the list.", "[sorted list]")
{
    SECTION("Testing the custom function.")
    {
        auto f = [](int a, int b) { return a <= b; };
        sorted_list<int> list(f);

	list.push(10);
	list.push(-5);
	list.push(0);
	list.push(5);
	list.push(-10);

	REQUIRE(list.count() == 5);

	REQUIRE(-10 == list.pop_front());
	REQUIRE(-5 == list.pop_front());
	REQUIRE(0 == list.pop_front());
	REQUIRE(5 == list.pop_front());
	REQUIRE(10 == list.pop_front());

	auto f2 = [](int a, int b) { return a > b; };
	sorted_list<int> list2({6, 8, -12}, f2);

	REQUIRE(8 == list2.pop_front());
	REQUIRE(6 == list2.pop_front());
	REQUIRE(-12 == list2.pop_front());
    }
}
