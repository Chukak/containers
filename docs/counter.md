# Counter

Counter - a class for counting the number of elements in some sequences. If you have a sequence, 
and if you want to count the number of elements in this sequence, you can use this class. 


## Header 

The `Counter` class is implemented in the `counter.h` header file, which is located in the category `counter`. 
To include the header file:

```cpp
#include <containers/counter/counter.h>
```

## Create a counter 

The counter is implementing using C++ tempaltes. 
To create a counter, pass the iterators to the sequence and data type, in the constructor. For example:

```cpp
vector<int> v = {1, 2, 3, 2, 1, 1, 1, 2, 4};
...
Counter<int> c(v.begin(), v.end()); // int - type of elements in vector
```

## Get most common elements 

To get most common elements, use the `most_common` method. The counter has two such methods.

### 1.`std::vector<std::pair<T, unsigned int>> most_common(int n = -1)`

Counts number of elements in the sequence. Return the vector of pairs. 

The pairs contains two values: 1. the element in the sequence, 2. the number of such elements.
For example: 

```cpp
vector<char> v = {'a', 'a', 'c', 'c', 'd', 'a', 'a', 'b', 'a', 'c', 'a', 'd'};
...
Counter<char> c(v.begin(), v.end());
auto result = c.most_common(); // {('a', 6), ('c', 3), ('d', 2), ('b', 1)}
// or 
Counter<char>::vector_t result = c.most_common(); // {('a', 6), ('c', 3), ('d', 2), ('b', 1)}
```

If you want to get the certain number of elements, pass a number as the first parameter.

```cpp
auto result = c.most_common(2); // {('a', 6), ('c', 3)}
```

### 2. `void most_common(Array& list, int n = -1)`

Counts number of elements in the sequence sorts it by the greater number of elements.
After this, this function writes result in the array, which was passed as the first argument, but this function
writes only the elements in the sequence, without number of elements.

For example:

```cpp
vector<char> v = {'a', 'a', 'c', 'c', 'd', 'a', 'a', 'b', 'a', 'c', 'a', 'd'};
...
Counter<char> c(v.begin(), v.end());
vector<char> result;
c.most_common(result); // {'a', 'c', 'd', 'b'}
```

If you want to get the certain number of elements, pass a number as the second parameter.

```cpp
c.most_common(result, 2); // {'a', 'c'}
```

## Update the counter

To update the counter, use the `update` method.

```cpp
vector<char> v = {'a', 'a', 'c', 'c', 'd', 'a', 'a', 'b', 'a', 'c', 'a', 'd'};
...
Counter<char> c(v.begin(), v.end()); // {('a', 6), ('c', 3), ('d', 2), ('b', 1)}
...
vector<char> v2 = {'g', 'g', 'h', 't', 'h'};
...
c.update(v2.begin(), v2.end()); // {('a', 6), ('c', 3), ('d', 2), ('g', 2), ('h', 2), ('b', 1) ('t', 1)}
```

## Static function

### Get `std::map`

To get `std::map`, use the static `map` method. Counts the number of elemnts in the sequence. 
Returns `std::map<T, int>`, where `T` - type of elements. 

For example:

```cpp
vector<char> v = {'a', 'a', 'c', 'c', 'd', 'a', 'a', 'b', 'a', 'c', 'a', 'd'};
...
auto m = Counter<char>::map(v.begin(), v.end()); // {('a', 6), ('c', 3), ('d', 2), ('b', 1)}
// or
Counter<char>::map_t m = map(v.begin(), v.end());
```

### Count the elements

To count the elements in the sequence, use the static `count` method. 
This method gets three argument - your array/container, and iterators.
Counts number of elements in the sequence and sorts it by the greater number of elements. 
Return your array of pairs.

For example:

```cpp
vector<char> v = {'a', 'a', 'c', 'c', 'd', 'a', 'a', 'b', 'a', 'c', 'a', 'd'};
...
std::vector<Counter<std::string>::pair_t> v2 = Counter<std::string>::count<std::vector>(v.begin(), v.end());
// or 
auto v2 = Counter<std::string>::count<std::vector>(v.begin(), v.end()); // vector{('a', 6), ('c', 3), ('d', 2), ('b', 1)}
...

...
std::set<Counter<std::string>::pair_t> set = Counter<std::string>::count<std::set>(v.begin(), v.end()); // set{('a', 6), ('c', 3), ('d', 2), ('b', 1)}
// or 
auto v2 = Counter<std::string>::count<std::set>(v.begin(), v.end());
```
Just pass your array/container type as template argument.

## Iterators

To get the iterator to the first pair of the counter, use the `begin()` method. 
Returns the iterator to the first pair of the counter. 
You can increase the iterator. But, do not reduce this iterator!

For example:

```cpp
vector<char> v = {'a', 'a', 'c', 'c', 'd', 'a', 'a', 'b', 'a', 'c', 'a', 'd'};
...
Counter<char> c(v.begin(), v.end());
...
for (auto it = c.begin(); it != c.end(); it++) {
  it->first; // element ('a', 'c', 'd' ...)
  it->second; // the number (6, 3, 2 ...)
}
```
