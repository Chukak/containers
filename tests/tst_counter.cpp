#include <catch.hpp>
#include "counter.h"

#include <string>
#include <list>
#include <set>

/*
 * Testing the `Counter` class.
 */
TEST_CASE("[Counter] The `Counter` class.", "[counter]") {
	/*
	 * Testing the `Counter` class № 1.
	 */
	SECTION("Testing the `Counter` class № 1.") {
		std::vector<std::string> v = {
			"v1", "v2", "v3", "v4", "v5",
			"v6", "v7", "v7", "v7", "v7",
			"v7", "v6", "v8", "v6", "v1",
			"v9", "v9", "v11", "v4", "v2",
			"v8", "v11", "v2", "v1", "v5",
			"v3", "v1", "v2", "v1", "v5",
			"v8", "v1", "v3", "v5", "v1",
			"v8", "v1", "v1", "v4", "v1",
			"v1", "v1", "v1", "v2", "v2"
		};

		Counter<std::string> c(v.begin(), v.end());
		REQUIRE(c.size() == 10);
		Counter<std::string>::vector_t v2 = c.most_common(4);
		REQUIRE(v2.at(0).first == "v1");
		REQUIRE(v2.at(0).second == 13);
		REQUIRE(v2.at(1).first == "v2");
		REQUIRE(v2.at(1).second == 6);
		REQUIRE(v2.at(2).first == "v7");
		REQUIRE(v2.at(2).second == 5);
		REQUIRE(v2.at(3).first == "v5");
		REQUIRE(v2.at(3).second == 4);

		Counter<std::string>::vector_t v3 = c.most_common(4);
		REQUIRE(v3.at(0).first == "v1");
		REQUIRE(v3.at(0).second == 13);
		REQUIRE(v3.at(1).first == "v2");
		REQUIRE(v3.at(1).second == 6);
		REQUIRE(v3.at(2).first == "v7");
		REQUIRE(v3.at(2).second == 5);
		REQUIRE(v3.at(3).first == "v5");
		REQUIRE(v3.at(3).second == 4);

	}

	/*
	 * Testing the `Counter` class № 2.
	 */
	SECTION("Testing the `Counter` class № 2.") {
		std::vector<std::string> v = {
			"v1", "v2", "v3", "v4", "v5",
			"v6", "v7", "v7", "v7", "v7",
			"v7", "v6", "v8", "v6", "v1",
			"v9", "v9", "v11", "v4", "v2",
			"v8", "v11", "v2", "v1", "v5",
			"v3", "v1", "v2", "v1", "v5",
			"v8", "v1", "v3", "v5", "v1",
			"v8", "v1", "v1", "v4", "v1",
			"v1", "v1", "v1", "v2", "v2"
		};

		Counter<std::string> c(v.begin(), v.end());
		REQUIRE(c.size() == 10);
		//std::vector<std::string> v2;
		std::list<std::string> v2;
		c.most_common(v2);
		REQUIRE(v2.size() == 10);
		REQUIRE(v2.front() == "v1");
		v2.pop_front();
		REQUIRE(v2.front() == "v2");
		v2.pop_front();
		REQUIRE(v2.front() == "v7");
		v2.pop_front();
		REQUIRE(v2.front() == "v5");
		v2.pop_front();
		REQUIRE(v2.front() == "v8");
		v2.pop_front();
		REQUIRE(v2.front() == "v3");
		v2.pop_front();
		REQUIRE(v2.front() == "v4");
		v2.pop_front();
		REQUIRE(v2.front() == "v6");
		v2.pop_front();
		REQUIRE(v2.front() == "v11");
		v2.pop_front();
		REQUIRE(v2.front() == "v9");
		v2.pop_front();

		std::list<std::string> v3;
		c.most_common(v3, 4);
		REQUIRE(v3.size() == 4);
		REQUIRE(v3.front() == "v1");
		v3.pop_front();
		REQUIRE(v3.front() == "v2");
		v3.pop_front();
		REQUIRE(v3.front() == "v7");
		v3.pop_front();
		REQUIRE(v3.front() == "v5");
		v3.pop_front();

	}

	/*
	 * Testing the `Counter` class № 4.
	 */
	SECTION("Testing the `Counter` class № 4.") {
		std::vector<std::string> v = {
			"v1", "v2", "v3", "v4", "v5",
			"v6", "v7", "v7", "v7", "v7",
			"v7", "v6", "v8", "v6", "v1",
			"v9", "v9", "v11", "v4", "v2",
			"v8", "v11", "v2", "v1", "v5",
			"v3", "v1", "v2", "v1", "v5",
			"v8", "v1", "v3", "v5", "v1",
			"v8", "v1", "v1", "v4", "v1",
			"v1", "v1", "v1", "v2", "v2"
		};

		Counter<std::string> c(v.begin(), v.end());
		REQUIRE(c.size() == 10);
		std::vector<std::string> v2 = {
			"v1", "v2", "v7", "v5", "v8", "v3", "v4", "v6", "v11", "v9"
		};
		int i = 0;
		for (Counter<std::string>::iterator it = c.begin(); it != c.end(); ++it) {
			REQUIRE(*it == v2.at(i));
			i++;
		}

		i = 0;
		for (Counter<std::string>::iterator it = c.begin(); it != c.end(); ++it) {
			REQUIRE(it->first == v2.at(i));
			i++;
		}

		Counter<std::string>::vector_t v3 = c.most_common();
		i = 0;
		for (Counter<std::string>::iterator it = c.begin(); it != c.end(); ++it) {
			REQUIRE(it->first == v3.at(i).first);
			REQUIRE(it->second == v3.at(i).second);
			i++;
		}
	}

	/*
	 * Testing the `Counter` class № 5.
	 */
	SECTION("Testing the `Counter` class № 5.") {
		std::vector<std::string> v = {
			"v1", "v2", "v3", "v4", "v5",
			"v6", "v7", "v7", "v7", "v7",
			"v7", "v6", "v8", "v6", "v1",
			"v9", "v9", "v11", "v4", "v2",
			"v8", "v11", "v2", "v1", "v5",
			"v3", "v1", "v2", "v1", "v5",
			"v8", "v1", "v3", "v5", "v1",
			"v8", "v1", "v1", "v4", "v1",
			"v1", "v1", "v1", "v2", "v2"
		};

		std::vector<Counter<std::string>::pair_t> v2 = Counter<std::string>::count<std::vector>(v.begin(), v.end());
		REQUIRE(v2.size() == 10);
		REQUIRE(v2.at(0).first == "v1");
		REQUIRE(v2.at(0).second == 13);
		REQUIRE(v2.at(1).first == "v2");
		REQUIRE(v2.at(1).second == 6);
		REQUIRE(v2.at(2).first == "v7");
		REQUIRE(v2.at(2).second == 5);
		REQUIRE(v2.at(3).first == "v5");
		REQUIRE(v2.at(3).second == 4);
		REQUIRE(v2.at(4).first == "v8");
		REQUIRE(v2.at(4).second == 4);
		REQUIRE(v2.at(5).first == "v3");
		REQUIRE(v2.at(5).second == 3);
		REQUIRE(v2.at(6).first == "v4");
		REQUIRE(v2.at(6).second == 3);
		REQUIRE(v2.at(7).first == "v6");
		REQUIRE(v2.at(7).second == 3);
		REQUIRE(v2.at(8).first == "v11");
		REQUIRE(v2.at(8).second == 2);
		REQUIRE(v2.at(9).first == "v9");
		REQUIRE(v2.at(9).second == 2);

		Counter<std::string> c(v.begin(), v.end());
		Counter<std::string>::vector_t v3 = c.most_common();
		int i = 0;
		for (const std::pair<std::string, unsigned int>& p : v3) {
			REQUIRE(p.first == v2.at(i).first);
			REQUIRE(p.second == v2.at(i).second);
			i++;
		}

	}
}
