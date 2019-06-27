# Static array

Static array - a class, with like bit as `std::array` and can be used at compile time. 

## Header

The `StaticArray` class is implemented in the `staticarray.h` header file, which is located in the `staticarray` category.

```cpp
#include <containers/staticarray/staticarray.h>
```

## Create a static array

To create `StaticArray` class pass a data type and size of array to the constructor. For example: 
```cpp
constexpr StaticArray<unsigned, 10> array = {9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};
```

## Get element from a position

To get an element from a specific position use `operator[]`. 

### `operator[std::integral_constant<std::size_t, N>]`

This operator takes `std::integral_constant` as element index. This operator checks ranges, and should be safe!. 
```cpp
constexpr StaticArray<int, 2> array = {1, 2};
static_assert(array[std::integral_constant<std::size_t, 0>{}] == 1);
static_assert(array[std::integral_constant<std::size_t, 1>{}] == 2);
```
Also, you can use pseudonym to create index: `Index<N>{}`.
```cpp
#include <extensions.h>
...
constexpr StaticArray<int, 2> array = {1, 2};
static_assert(array[Index<0>{}] == 1);
static_assert(array[Index<1>{}] == 2);
```

### `operator[std::size_t]`

This operator takes `std::size_t` as element index and will not check ranges! 
```cpp
constexpr StaticArray<int, 2> array = {1, 2};
static_assert(array[0] == 1);
static_assert(array[1] == 2);
```

## Make sequence

To make sequence use `make_sequence()` method. Returns an array filed with elements.
```cpp
constexpr auto array = StaticArray<int, 6>::make_sequence();
static_assert(array[0] == 1);
static_assert(array[1] == 2);
static_assert(array[2] == 3);
static_assert(array[3] == 4);
static_assert(array[4] == 5);
static_assert(array[5] == 6);
```
## Extensions

Some extensions located in the `extensions.h` header file.

### Constexpr loop

For-loop at compile time! But, at the moment it does not work in `g++-8` compiler. See problem: [Stackoverflow](https://stackoverflow.com/questions/56409068/why-is-this-a-non-constant-condition-for-g8) 

```cpp
constexpr StaticArray<unsigned, 10> array = {9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};
constexpr std::array<unsigned, 10> checker = {9u, 8u, 7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

CONSTEXPR_LOOP<10>([&](auto i) constexpr 
{
    static_assert(array[i] == checker[i]);
});
```

