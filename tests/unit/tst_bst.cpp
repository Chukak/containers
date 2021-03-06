#include <catch.hpp>
#include "bst.h"

TEST_CASE("[bst] Testing the initialization the binary search tree.", "[binary search tree]")
{
    SECTION("Testing the default constructor.")
    {
        bst<int> tree;
        CHECK(tree.is_empty());
        REQUIRE(tree.count() == 0);
    }
    SECTION("Testing the initializer list.")
    {
        bst<int> tree = {1, 5, 2, 6, 3, 4};
        CHECK_FALSE(tree.is_empty());
        REQUIRE(tree.count() == 6);
        REQUIRE(tree.root() == 1);
    }

    SECTION("Testing the copy constructor.")
    {
        bst<int> orig = {1, 5, 2, 6, 3, 4};
        bst<int> tree(orig);
        CHECK_FALSE(tree.is_empty());
        REQUIRE(tree.count() == 6);
        REQUIRE(tree.root() == 1);
    }
    SECTION("Testing the move constructor.")
    {
        bst<int>&& orig = {1, 5, 2, 6, 3, 4};
        bst<int> tree(std::forward<bst<int>>(orig));
        CHECK_FALSE(tree.is_empty());
        REQUIRE(tree.count() == 6);
        REQUIRE(tree.root() == 1);
    }
    SECTION("Testing the copy operator =.")
    {
        bst<int> orig = {1, 5, 2, 6, 3, 4};
        bst<int> tree = orig;
        CHECK_FALSE(tree.is_empty());
        REQUIRE(tree.count() == 6);
        REQUIRE(tree.root() == 1);
    }
    SECTION("Testing the move operator =.")
    {
        bst<int>&& orig = {1, 5, 2, 6, 3, 4};
        bst<int> tree = std::forward<bst<int>>(orig);
        CHECK_FALSE(tree.is_empty());
        REQUIRE(tree.count() == 6);
        REQUIRE(tree.root() == 1);
    }
}

TEST_CASE("[bst] Testing the insertion into the binary search tree.", "[binary search tree]")
{
    SECTION("Testing the insertion №1.")
    {
        bst<int> tree;

	tree.insert(10);
	tree.insert(1);
	tree.insert(7);
	tree.insert(12);
	tree.insert(24);
	tree.insert(2);
	tree.insert(100);
	tree.insert(-50);
	tree.insert(-1);

	REQUIRE(tree.root() == 10);
	REQUIRE(tree.min() == -50);
	REQUIRE(tree.max() == 100);
	CHECK_FALSE(tree.is_empty());
	REQUIRE(tree.count() == 9);
    }
    SECTION("Testing the insertion №2.")
    {
        bst<int> tree = {-75, 1, 865};

	tree.insert(1);
	tree.insert(-1);
	tree.insert(12);
	tree.insert(-5);
	tree.insert(2);
	tree.insert(19);
	tree.insert(109);
	tree.insert(-54);
	tree.insert(0);

	REQUIRE(tree.root() == -75);
	REQUIRE(tree.min() == -75);
	REQUIRE(tree.max() == 865);
	CHECK_FALSE(tree.is_empty());
	REQUIRE(tree.count() == 11);
    }
}

TEST_CASE("[bst] Testing the removing from the binary search tree.", "[binary search tree]")
{
    SECTION("Testing the removing №1.")
    {
        bst<int> tree;

	tree.insert(-15);
	tree.insert(10);
	tree.insert(-5);
	tree.insert(20);
	tree.insert(0);

	tree.insert(5);
	tree.insert(-10);
	tree.insert(-20);
	tree.insert(-25);
	tree.insert(15);

	REQUIRE(tree.min() == -25);
	REQUIRE(tree.max() == 20);
	CHECK_FALSE(tree.is_empty());
	REQUIRE(tree.count() == 10);

	int t = -25;
	while(tree.count()) {
	    tree.remove(t);
	    t += 5;
	}

	CHECK(tree.is_empty());
	REQUIRE(tree.count() == 0);
    }
    SECTION("Testing the removing №2.")
    {
        bst<int> tree;

	tree.insert(-15);
	tree.insert(10);
	tree.insert(-5);
	tree.insert(20);
	tree.insert(0);
	tree.insert(5);
	tree.insert(-10);
	tree.insert(-20);
	tree.insert(-25);
	tree.insert(15);

	int t = -25;
	for(unsigned int i = 0; i != tree.count();) {
	    REQUIRE(t == tree.min());
	    tree.remove(t);
	    t += 5;
	}
    }
}

TEST_CASE("[bst] Testing the getting min and max elements from the binary search tree.", "[binary search tree]")
{
    SECTION("Testing the getting min and max elements.")
    {
        bst<int> tree;

	tree.insert(-15);
	tree.insert(10);
	tree.insert(-5);
	tree.insert(20);
	tree.insert(0);
	tree.insert(5);
	tree.insert(-10);
	tree.insert(-20);
	tree.insert(-25);
	tree.insert(15);

	REQUIRE(tree.min() == -25);
	REQUIRE(tree.max() == 20);
	CHECK_FALSE(tree.is_empty());
	REQUIRE(tree.count() == 10);

	int t = -25;
	while(tree.count()) {
	    REQUIRE(20 == tree.max());
	    REQUIRE(t == tree.min());
	    tree.remove(t);
	    t += 5;
	}

	CHECK(tree.is_empty());
	REQUIRE(tree.count() == 0);
    }
}

TEST_CASE("[bst] Testing the searching in the binary search tree.", "[binary search tree]")
{
    SECTION("Testing the function `find` №1.")
    {
        bst<int> tree;

	tree.insert(-15);
	tree.insert(10);
	tree.insert(-5);
	tree.insert(20);
	tree.insert(0);
	tree.insert(5);
	tree.insert(-10);
	tree.insert(-20);
	tree.insert(-25);
	tree.insert(15);

	CHECK(tree.find(10));
	CHECK(tree.find(0));
	CHECK(tree.find(-20));
	CHECK(tree.find(-15));

	CHECK_FALSE(tree.find(40));
	CHECK_FALSE(tree.find(-11));
	CHECK_FALSE(tree.find(100));
	CHECK_FALSE(tree.find(-4));
    }
    SECTION("Testing the function `find` №2.")
    {
        bst<int> tree;

	CHECK_FALSE(tree.find(11));
	CHECK_FALSE(tree.find(-10));

	tree.insert(4);

	CHECK(tree.find(4));

	tree.remove(4);

        CHECK_FALSE(tree.find(4));
    }
}

TEST_CASE("[bst] Testing the exceptions.", "[binary search tree]")
{
    SECTION("Testing the errors.")
    {
        bst<int> tree;

	REQUIRE_THROWS_AS(tree.remove(5), bst_exception::bst_is_empty);
	REQUIRE_THROWS_WITH(tree.remove(5), "The binary search tree is empty.");

	REQUIRE_THROWS_AS(tree.root(), bst_exception::bst_is_empty);
	REQUIRE_THROWS_WITH(tree.root(), "The binary search tree is empty.");

	REQUIRE_THROWS_AS(tree.min(), bst_exception::bst_is_empty);
	REQUIRE_THROWS_WITH(tree.min(), "The binary search tree is empty.");

	REQUIRE_THROWS_AS(tree.max(), bst_exception::bst_is_empty);
	REQUIRE_THROWS_WITH(tree.max(), "The binary search tree is empty.");
    }
}

TEST_CASE("[bst] Testing the iterators of the binary search tree.", "[binary search tree]")
{
    SECTION("Testing the iterators.")
    {
        bst<int> tree = {10, -8, 6, 0, 8, -10, -2, 2, 4, -4, -6};

	bst<int>::iterator iter = tree.begin();
	REQUIRE_FALSE(iter == nullptr);
	REQUIRE(iter != nullptr);

	int test_var = -12;
	for(auto it = tree.begin(); it != tree.end(); ++it) {
	    test_var += 2;
	    REQUIRE(*it == test_var);
	}
	REQUIRE(test_var == 10);

	test_var = -12;
	for(auto it = tree.begin(); it != tree.end(); it++) {
	    test_var += 2;
	    REQUIRE(it->data == test_var);
	}
	REQUIRE(test_var == 10);

	REQUIRE_FALSE(tree.begin() == tree.end());
	REQUIRE(tree.begin() != tree.end());
    }
    SECTION("Testing that the iterators and nullptr are the same.")
    {
        bst<int> tree;

	REQUIRE(tree.begin() == tree.end());
	REQUIRE(tree.begin() == nullptr);
	REQUIRE(tree.end() == nullptr);
    }
}

TEST_CASE("[bst] Testing the cleaning of the binary search tree.", "[binary search tree]")
{
    SECTION("Testing the cleaning №1.")
    {
        bst<int> tree;

	tree.insert(-15);
	tree.insert(10);
	tree.insert(-5);
	tree.insert(20);
	tree.insert(0);
	tree.insert(5);
	tree.insert(-10);
	tree.insert(-20);
	tree.insert(-25);
	tree.insert(15);

	REQUIRE(tree.count() == 10);

	tree.clear();

        REQUIRE(tree.count() == 0);
    }
}
