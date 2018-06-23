# Sorted list

Sorted list - abstract data type, in which each element is sorted in a special order. 
When you add an element in the list, the element is inserted in a special position, to keep the order in the list. 
A new element inserts between two elements, without moving any other elements.
In this library, the sorted list implement as a two linked list. 
To declare a sorted list use the `sorted_list` class.

<strong>Note</strong>: to add a custom classes, object, etc in the list, you must override the operators `>`, `<`, `>=`, `<=` 
for these classes, objects, etc. 

<strong>Note</strong>: You can pass a custom function to compare elements in the list. 
It can be used instead of overrided operators.

<strong>Note</strong>: By default the operators `<`, `<=` are used for the comparison. If the list is reversed, the operators `>`, `>=` 
are used for the comparison.

## Header
The sorted list is implemented in the `sorted_list.h` header file, which is located in the category `sorted_list`. 
To include the header file:
```cpp
#include "containers/sorted_list/sorted_list.h"
```

## Create a sorted list
The sorted list is implemented using C++ templates. To create a sorted list, pass the data type, 
which will be in the sorted list, in constructor.


Standard initialization:
```cpp
sorted_list<int> list;
```

Initialization with braces:
```cpp
sorted_list<int> list = {3, 5, 1, 4, 2}; // list - [1, 2, 3, 4, 5]
```

Initialization a sorted list fron another sorted list:
```cpp
sorted_list<int> orig = {3, 1, 2};
sorted_list<int> list(orig);
```

If you want to compare elements using a custom function, pass a custom function in constructor:
```cpp
auto f = [](int a, int b, int c) {
  return a < b && b <= c;
};
sorted_list<int> list(f);
```
Note: Use it only with standart initialization, an empty list.

## Add elements
To add elements in the sorted list, use the `push` method. The `push` method adds an element to a special position.
The order in the list is saved when the element inserted. Returns a position.
```cpp 
sorted_list<int> list;
...
list.push(27); // list - [27] 
list.push(-45); // list - [-45, 27]
list.push(1); // list - [-45, 1, 27]
```
If the inserted element must be inserted before the first element in the list or after the last element in the list, 
the insertion will be done instantly. Otherwise, the `push` method will find a special position for the inserted element, 
the insertion can be take some time. Depends on the nubers of elements. If the list is large, the performance can be slow. 

## Remove elements
To remove the `sorted_list` class has three methods: `pop_front`, `pop_back`, `remove`

### Remove the first element
To remove the first element from the list, use the `pop_front` method. The `pop_front` method removes the 
first element from the list. Returns the deleted element.
```cpp
sorted_list<int> list = {2, 3, 1};
...
list.pop_front(); // returns 1
list.pop_front(); // returns 2
```
If the list is empty, the result of the `pop_front` method has an undefined behavior. Be careful when using this method.

### Remove the last element
To remove the last element from the list, use the `pop_back` method. The `pop_back` method removes the 
last element fron the list. Returns the deleted element.
```cpp
sorted_list<int> list = {2, 3, 1};
...
list.pop_back(); // returns 3
list.pop_back(); // returns 2
```
If the list is empty, the result of the `pop_back` method has an undefined behavior. Be careful when using this method.

### Remove from the position
To remove an element from a position, use the `remove` method. The `remove` method, checks an available range. 
If the position, from which you want to remove an element is less than zero, or outside of the range of the list, 
the `remove` method throws an `out_of_range` exception. This method is safe, can be use in an empty list.
Returns the deleted element, or throws an `out_of_range` exception.
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
To get the first element from the list, use the `front` method. Returns the first element from the list.
```cpp
sorted_list<int> list = {2, 1};
...
list.front(); // returns 1
```
If the list is empty, the result of the `front` method has an undefined behavior. Be careful when using this method.

## Get the last element
To get the last element from the list, use the `back` method. Returns the last element from the list.
```cpp
sorted_list<int> list = {2, 1};
...
list.last(); // returns 2
```
If the list is empty, the result of the `back` method has an undefined behavior. Be careful when using this method.

## Get elements from the position
### the `at` method
To get an element from the position, use the `at` method. The `at` method, checks an available tange.
If the position, from which you want to get an element is less than zero, or outside of the range of the list, 
the `at` method throws an `out_of_range` exception. This method is safe, can be use in an empty list.
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
Also, you can use the operator `[]` to get an element from the position. But this method doesn\`t check an available range.
Returns an element from the position.
If the list is empty or the position less than zero, the result has an undefined behavior. 
Be careful when using this method.
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

### Reverse the list
To reverse the order of the list, use the `reverse` method. 
Change the order of the list and the operator for the comparison.
```cpp
sorted_list<int> = {3, 1, 2}; // [1, 2, 3]
...
list.push(-1); // [-1, 1, 2, 3]
list.reverse(); // [3, 2, 1]
...
list.push(-5); // [3, 2, 1, -1, -5]
list.push(5); // [5, 3, 2, 1, -1, -5]
```

### Check if the list if reversed
To check if the list is reversed or not, use the `is_reversed` method. Returns `true` if the list is reversed, otherwise `false`.
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
To clear the list, use the `clear` method. The method returns nothing.
```cpp
sorted_list<int> list = {3, 4, 1, 2, 5};
...
list.clear();
list.is_empty(); // true
```

## Custom comparison functions
You can use a custom function to compare elements and to store the order in the list. You must follow the following rules:
* the function must have 3 parameters! Like the standatd comparison function, it must compare the previous element
with the new element and the next element with the new element. 
For example, we want to add `3` in the list `[1, 2, 4, 5]`. We must compare `3` with two other elements, 
in our list it will be `2` and `4`. In this case, the function must be get 3 arguments `2`, `3` and `4`, 
and must return `true` or `false` in this statement: `2 < 3 <= 4`. For example:
```cpp
auto = [](int a, int b, int c) {
  return a < b && b <= c;
}; 
```

* the function must have the operator `<=` or `>=`, when to comparing the second parameter with the third parameter.
It need for comparing the same elements in the list. For example, we want to add `3` in the list `[1, 2, 3]`. 
The result is `[1, 2, 3, 3]`.

* the function must return `true` or `false`

If an element must be added before the first element or after the last element. 
For example, we want to add `1` in the list `[2, 3, 4]`. The function gets 3 arguments `1`, `2`, `2`, compares them
and adds `1` before `2`. The result is `[1, 2, 3, 4]`.

This behavior used, that we do not declare 3 different functions for 3 different situations:
* when the added element must be added before the first element in the list
* when the added element must be added after the last element in the list
* when the added element must be added to the middle of the list

Instead, used only one function with 3 arguments. For example:
```cpp 
bool custom_function(type a, type b, type c) {
  ...
}
auto f = custom_function;
```
Or:
```cpp
auto f = [](type a, type b, type c) {
  ...
};
```



## Iterators
The `sorted_list` class has iterators of list. The iterators have the type `bidirectional_iterator`. 
You can increase and reduce the iterator.

### Use iterators
To get the iterator on the first element in the list, use the `begin()` method. 
Returns the iterator to the first element in the list. You can increase the iterator. 
But, don\`t reduce this iterator!

To get the iterator to the end of the list, use the `end()` method. 
Returns the iterator to the end of the list. You can reduce the iterator.
But, don\`t increase this iterator! Be careful when you reduce this iterator.

To get the type of iterators, use `sorted_list<...>::iterator` or use `auto`.
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

You can use iterators in STL algorithms, but it is not guaranteed that the iterators will work in all algorithms

<br>
