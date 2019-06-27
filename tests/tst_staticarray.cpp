#include <catch.hpp>
#include <staticarray.h>
#include <extensions.h>


using namespace constexpr_extensions;

TEST_CASE("[static array] Testing the initialization of the static array.", "[static array]") {
	SECTION("Testing the initialiation №1.") {
		constexpr StaticArray<int, 20> array;
		static_assert(array[Index<0>()] == 0);
		static_assert(array[Index<1>()] == 0);
		static_assert(array[Index<2>()] == 0);
		static_assert(array[Index<3>()] == 0);
		static_assert(array[Index<4>()] == 0);
		static_assert(array[Index<5>()] == 0);
		static_assert(array[Index<6>()] == 0);
		static_assert(array[Index<7>()] == 0);
		static_assert(array[Index<8>()] == 0);
		static_assert(array[Index<9>()] == 0);
		static_assert(array[Index<10>()] == 0);
		static_assert(array[Index<11>()] == 0);
		static_assert(array[Index<12>()] == 0);
		static_assert(array[Index<13>()] == 0);
		static_assert(array[Index<14>()] == 0);
		static_assert(array[Index<15>()] == 0);
		static_assert(array[Index<16>()] == 0);
		static_assert(array[Index<17>()] == 0);
		static_assert(array[Index<18>()] == 0);
		static_assert(array[Index<19>()] == 0);
		static_assert(array[0] == 0);
		static_assert(array[1] == 0);
		static_assert(array[2] == 0);
		static_assert(array[3] == 0);
		static_assert(array[4] == 0);
		static_assert(array[5] == 0);
		static_assert(array[6] == 0);
		static_assert(array[7] == 0);
		static_assert(array[8] == 0);
		static_assert(array[9] == 0);
		static_assert(array[10] == 0);
		static_assert(array[11] == 0);
		static_assert(array[12] == 0);
		static_assert(array[13] == 0);
		static_assert(array[14] == 0);
		static_assert(array[15] == 0);
		static_assert(array[16] == 0);
		static_assert(array[17] == 0);
		static_assert(array[18] == 0);
		static_assert(array[19] == 0);

		REQUIRE(array.capacity() == 20);
		REQUIRE(array.count() == 0);
	}
	SECTION("Testing the initialization №2.") {
		constexpr StaticArray<int, 10> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
		static_assert(array[Index<0>()] == 1);
		static_assert(array[Index<1>()] == 2);
		static_assert(array[Index<2>()] == 3);
		static_assert(array[Index<3>()] == 4);
		static_assert(array[Index<4>()] == 5);
		static_assert(array[Index<5>()] == 6);
		static_assert(array[Index<6>()] == 7);
		static_assert(array[Index<7>()] == 8);
		static_assert(array[Index<8>()] == 9);
		static_assert(array[Index<9>()] == 0);
		static_assert(array[0] == 1);
		static_assert(array[1] == 2);
		static_assert(array[2] == 3);
		static_assert(array[3] == 4);
		static_assert(array[4] == 5);
		static_assert(array[5] == 6);
		static_assert(array[6] == 7);
		static_assert(array[7] == 8);
		static_assert(array[8] == 9);
		static_assert(array[9] == 0);

		REQUIRE(array.capacity() == 10);
		REQUIRE(array.count() == 10);
	}
	SECTION("Testing the initialization №3.") {
		constexpr StaticArray<int, 10> array{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
		static_assert(array[Index<0>()] == 1);
		static_assert(array[Index<1>()] == 2);
		static_assert(array[Index<2>()] == 3);
		static_assert(array[Index<3>()] == 4);
		static_assert(array[Index<4>()] == 5);
		static_assert(array[Index<5>()] == 6);
		static_assert(array[Index<6>()] == 7);
		static_assert(array[Index<7>()] == 8);
		static_assert(array[Index<8>()] == 9);
		static_assert(array[Index<9>()] == 0);
		static_assert(array[0] == 1);
		static_assert(array[1] == 2);
		static_assert(array[2] == 3);
		static_assert(array[3] == 4);
		static_assert(array[4] == 5);
		static_assert(array[5] == 6);
		static_assert(array[6] == 7);
		static_assert(array[7] == 8);
		static_assert(array[8] == 9);
		static_assert(array[9] == 0);

		REQUIRE(array.capacity() == 10);
		REQUIRE(array.count() == 10);
	}
}

TEST_CASE("[static array] Testing the operators of StaticArray.", "[static array]") {
	SECTION("Testing the getting operators.") {
		constexpr StaticArray<unsigned, 10> array = {9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};
		static_assert(array[Index<0>()] == 9);
		static_assert(array[Index<1>()] == 8);
		static_assert(array[Index<2>()] == 7);
		static_assert(array[Index<3>()] == 6);
		static_assert(array[Index<4>()] == 5);
		static_assert(array[Index<5>()] == 4);
		static_assert(array[Index<6>()] == 3);
		static_assert(array[Index<7>()] == 2);
		static_assert(array[Index<8>()] == 1);
		static_assert(array[Index<9>()] == 0);
		static_assert(array[0] == 9);
		static_assert(array[1] == 8);
		static_assert(array[2] == 7);
		static_assert(array[3] == 6);
		static_assert(array[4] == 5);
		static_assert(array[5] == 4);
		static_assert(array[6] == 3);
		static_assert(array[7] == 2);
		static_assert(array[8] == 1);
		static_assert(array[9] == 0);

		// See: https://stackoverflow.com/questions/56409068/why-is-this-a-non-constant-condition-for-g8
#if __GNUC__ != 8
		constexpr std::array<unsigned, 10> checker = {9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

		CONSTEXPR_LOOP<10>([&](auto i) constexpr {
			static_assert(array[Index<i>()] == checker[i]);
			static_assert(array[i] == checker[i]);
		});
#endif
	}
}

TEST_CASE("[static array] Testing the `make_sequence` method.", "[static array]") {
	SECTION("Section №1.") {
		constexpr auto array = StaticArray<unsigned, 15>::make_sequence();
		static_assert(array[Index<0>()] == 0);
		static_assert(array[Index<1>()] == 1);
		static_assert(array[Index<2>()] == 2);
		static_assert(array[Index<3>()] == 3);
		static_assert(array[Index<4>()] == 4);
		static_assert(array[Index<5>()] == 5);
		static_assert(array[Index<6>()] == 6);
		static_assert(array[Index<7>()] == 7);
		static_assert(array[Index<8>()] == 8);
		static_assert(array[Index<9>()] == 9);
		static_assert(array[Index<10>()] == 10);
		static_assert(array[Index<11>()] == 11);
		static_assert(array[Index<12>()] == 12);
		static_assert(array[Index<13>()] == 13);
		static_assert(array[Index<14>()] == 14);
		static_assert(array[0] == 0);
		static_assert(array[1] == 1);
		static_assert(array[2] == 2);
		static_assert(array[3] == 3);
		static_assert(array[4] == 4);
		static_assert(array[5] == 5);
		static_assert(array[6] == 6);
		static_assert(array[7] == 7);
		static_assert(array[8] == 8);
		static_assert(array[9] == 9);
		static_assert(array[10] == 10);
		static_assert(array[11] == 11);
		static_assert(array[12] == 12);
		static_assert(array[13] == 13);
		static_assert(array[14] == 14);

		REQUIRE(array.capacity() == 15);
		REQUIRE(array.count() == 15);
	}
}
