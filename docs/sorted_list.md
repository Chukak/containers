# Sorted list

Sorted list - a list, in which each element is sorted in a special order. 
When you add a new element into the list, this element will be insert in a special position, to keep the order in the list. 
A new element inserts between two elements, without moving other elements.
In this library, the sorted list implement as a two linked list. 
To declare a sorted list use the `sorted_list` class.

**Note**: To add a custom classes, object, etc in the list, you must override the operators `>=`, `<=` 
for these classes, objects, etc. 

**Note**: You can pass a custom function to compare elements in the list. 
It can be used instead of overrided operators.

**Note**: By default the operator `<=` is used for the comparison. If the list is reversed, the operator `>=` 
is used for the comparison.

## Header

The sorted list is implemented in the `sorted_list.h` header file, which is located in the category `sorted_list`. 
To include the header file:

```cpp
#include <containers/sorted_list/sorted_list.h>
```

## Create a sorted list

The sorted list is implemented using C++ templates. To create a sorted list, pass the data type, 
which will be in the sorted list, in the constructor.

Default constructor:

```cpp
sorted_list<int> list;
```

Using initializer list:

```cpp
sorted_list<int> list = {3, 5, 1, 4, 2}; // list - [1, 2, 3, 4, 5]
```

If you want to compare elements using a custom function, pass a custom function in constructor:

```cpp
auto f = [](int a, int b) {
  return a <= b;
};
sorted_list<int> list(f);
```
**Note**: Use it only with default constructor, when the list is empty.

## Add elements

To add elements into the list, use the `push` method. The `push` method adds a new element to a special position.
The order in the list is saved when the element inserted. Returns a position.

```cpp 
sorted_list<int> list;
...
list.push(27); // list - [27] 
list.push(-45); // list - [-45, 27]
list.push(1); // list - [-45, 1, 27]
```

If a new element less(or more if the list is reversed) than the first element of the list or more(or less if the list is reversed) than the last element of the list, the insertion will be executed instantly. Otherwise, the `push` method will find a special position for this element, the insertion will have a linear complexity. 

## Remove elements

To remove the `sorted_list` class has three methods: `pop_front`, `pop_back`, `remove`.

### Remove the first element

To remove the first element from the list, use the `pop_front` method. The `pop_front` method removes the 
first element of the list. Returns the deleted element.

```cpp
sorted_list<int> list = {2, 3, 1};
...
list.pop_front(); // returns 1
list.pop_front(); // returns 2
```

**Note**: At the moment if the list is empty, the result of the `pop_front` method has an undefined behavior. 
Be careful when using this method.

### Remove the last element

To remove the last element of the list, use the `pop_back` method. The `pop_back` method removes the 
last element of the list. Returns the deleted element.

```cpp
sorted_list<int> list = {2, 3, 1};
...
list.pop_back(); // returns 3
list.pop_back(); // returns 2
```

**Note**: At the moment if the list is empty, the result of the `pop_back` method has an undefined behavior. 
Be careful when using this method.

### Remove from the position

To remove an element from a position, use the `remove` method. The `remove` method, checks an available range. 
If the position, from which you want to remove an element is less than zero, or outside of the range of the list, 
the `remove` method throws the `out_of_range` exception. This method is safe, can be use when the list is empty.
Returns the deleted element.

```cpp
sorted_list<int> list = {2, 3, 1};
...
list.remove(1); // returns 2
list.remove(1); // returns 3
list.remove(-1); // out of range
list.remove(0); // returns 1
list.remove(0); // out of range
```

## Get the first element

To get the first element of the list, use the `front` method. Returns the first element of the list.

```cpp
sorted_list<int> list = {2, 1};
...
list.front(); // returns 1
```

**Note**: At the moment if the list is empty, the result of the `front` method has an undefined behavior. 
Be careful when using this method.

## Get the last element

To get the last element of the list, use the `back` method. Returns the last element of the list.

```cpp
sorted_list<int> list = {2, 1};
...
list.last(); // returns 2
```

**Note**: At the moment if the list is empty, the result of the `back` method has an undefined behavior. 
Be careful when using this method.

## Get elements from the position

### the `at` method

To get an element from the position, use the `at` method. The `at` method, checks an available range.
If the position, from which you want to get an element is less than zero, or outside of the range of the list, 
the `at` method throws the `out_of_range` exception. This method is safe, can be use when the list is empty.
Returns an element from the position.

```
sorted_list<int> list = {2, 1};
...
list.at(0); // returns 1
list.at(-3); // out of range
...
sorted_list<int> list2;
...
list2.at(0); // out of range
```

### the operator `[]`

Also, you can use the operator `[]` to get an element from the position. But this method does not check an available range.
Returns an element from the position.

**Note**: If the list is empty or the position less than zero or the position more size of list, the result has an undefined behavior. Be careful when using this method.

```cpp
sorted_list<int> list = {3, 1, 2};
...
list[0]; // returns 1
list[-1]; // ????
```

## Extra methods

### The number of elements

To get the number of elements in the list, use the `count` method. Returns the number of elements.

```cpp
sorted_list<int> list = {1, 2, 3};
...
list.count(); // returns 3
```

### Check if the list is empty

To check if the list is empty or not, use the `is_empty` method. Returns `true` if the list is empty, otherwise `false`.

```cpp
sorted_list<int> list;
...
list.is_empty(); // true
...
list.push(1);
list.is_empty(); // false
```

### Change the order of the list

To change the order of the list, use the `reverse` method. 
Changes the order of the list and the operator for the comparison. If the operator for comparison is a custom function, 
changes only the order of the list. 

```cpp
sorted_list<int> = {3, 1, 2}; // [1, 2, 3]
...
list.push(-1); // [-1, 1, 2, 3]
list.reverse(); // [3, 2, 1]
...
list.push(-5); // [3, 2, 1, -1, -5]
list.push(5); // [5, 3, 2, 1, -1, -5]
```

### Check the order of the list

To check the order of the list, use the `is_reversed` method. Returns `true` if the order of the list is reversed, 
otherwise `false`.

```cpp
sorted_list<int> list = {3, 2, 1}; // [1, 2, 3]
...
list.is_reversed(); // false
...
list.reverse(); // [3, 2, 1]
list.is_reversed(); // true
...
list.reverse(); // [1, 2, 3]
list.is_reversed(); // false
```

### Clear the list

To clear the list, use the `clear` method. 

```cpp
sorted_list<int> list = {3, 4, 1, 2, 5};
...
list.clear();
list.is_empty(); // true
```

## Custom comparison functions

You can use a custom function to compare elements and to keep the order in the list. You must follow the following rules:
* the function must have 2 parameters! Like the standatd comparison function, it must compare the previous element
with a new element. 
For example, we want to add `3` in the list `[1, 2, 4, 5]`. We must compare `3` with other elements, 
in our list, until the right position is found. In this case, the function must be get 2 arguments `2` and `3`, 
and must return `true` in this statement: `2 <= 3`. For example:

```cpp
auto = [](int a, int b) {
  return a <= b;
}; 
```

**Note**: Instead of a custom function you can override the operators `>=`, `<=`. 

* the function must return `true` or `false`

The `push` method checks 3 different situations:
* when the added element must be added before the first element in the list (constant complexity)
* when the added element must be added after the last element in the list (constant complexity)
* when the added element must be added to the middle of the list (linear complexity)


## Iterators

The `sorted_list` class has iterators. The iterators have a `bidirectional_iterator` type. 
You can increase and reduce the iterators.

### Use iterators

To get the iterator to the first element of the list, use the `begin()` method. 
Returns the iterator to the first element of the list. You can increase the iterator. 
But, do not reduce this iterator!

To get the iterator to the end of the list, use the `end()` method. 
Returns the iterator to the end of the list. You can reduce the iterator. 
But, do not increase this iterator! 

For example: 
```
for (auto it = list.end(); it != list.begin(); it--) { ... }
```

But, in this case, you can not get the first element of the list. 
Maybe, in the future, this problem will be solved. Be careful when you reduce this iterator.

To get the type of iterators, use `sorted_list<...>::iterator` or `auto`.

```cpp
sorted_list<int> l = {5, 3, 2, 4, 1};
for (auto it = l.begin(), it != l.end(); it++) { ... }
...
auto it = l.end();
int a = *it; // 5
it--;
int b = *it; // 4
it--;
// or use ->
int c = it->value; // 3
```

You can use iterators in STL algorithms, but it is not guaranteed that the iterators will work correct in all algorithms

<br>
