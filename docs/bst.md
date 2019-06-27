# Binary search tree

Binary search tree - a sorted binary tree, stores objects in memory, can find, insert and delete objects.
Elements insert in the sorted order. The first element is the root of the tree.
All the elements, what less than the root of the tree will insert in the left side of the tree, 
and elements what more than the root of the tree will insert in the right side of the tree.

More information - [Wiki](https://en.wikipedia.org/wiki/Binary_search_tree)

**Note**: To add a custom classes, objects, etc in the list, 
you must override the operators `>`, `<`, `==` for these classes, objects, etc.


## Header

The binary search tree is implemented in the `bst.h` header file, which is located in the category `bst`. To include the header file:

```cpp
#include <containers/bst/bst.h>
```

## Create a binary search tree

The binary search tree is implemented using C++ templates. 
To create a binary search tree, pass the data type, which will be in the tree, in the constructor.

Default constructor:

```cpp
bst<int> tree;
```
 
Using initializer list:
 
```cpp
bst<int> tree = {2, 4, -1, 10}; // 2 is the root of the tree
```
 
## Insert elements
 
To insert elements into the tree, use the `insert` method. 
The `insert` method inserts a new element to the left side, if this element less than the root of the tree, 
and to the right side, if this element more than the root of the tree.
If the tree is empty, the inserted element becomes the root of the tree.
 
```cpp
bst<int> tree;
...
tree.insert(1); // the root of the tree
tree.insert(5);
tree.insert(-10);
```
 
## Remove elements
 
To remove elements from the tree, use the `remove` method. 
The `remove` method removes the element from the tree, if the tree has this element.
If the tree does not have this element, the `remove` method just stops executing, without any errors.
If the tree is empty, throws the `bst_is_empty` exception.

```cpp
bst<int> tree;
...
tree.insert(1);
tree.insert(5);
...
tree.remove(5);
...
tree.remove(7); // just stop executing
```

But

```cpp
bst<int> tree;
tree.temove(5); // throws the `bst_is_empty` error.
```
 
## Get the minimum element(leftmost element)
 
To get the minimum element of the tree, use the `min` method. Returns the minimum element of the tree.
If the tree is empty, throws the `bst_is_empty` exception.

```cpp
bst<int> tree = {4, 5, 6, 1, 2, -1};
...
tree.min(); // returns -1
```
 
## Get the maximum element(rightmost element)

To get the maximum element of the tree, use the `max` method. Returns the maximum element of the tree.
If the tree is empty, throws the `bst_is_empty` exception.

```cpp
bst<int> tree = {4, 5, 6, 1, 2, -1};
...
tree.max(); // returns 6
```
 
## Get the root 

To get the root of the tree, use the `root` method. Returns the root of the tree.
If the tree is empty, throws the `bst_is_empty` error.

```cpp
bst<int> tree = {4, 5, 6, 1, 2, -1};
...
tree.root(); // returns 4
```

## Find elements(if the tree has this element)

To find an element in the tree, use the `find` method. Return `true` is the tree has this element, otherwise returns `false`.
If the tree is empty, returns `false`.

```cpp
bst<int> tree = {1, 6, 38, 9, 5};
...
tree.find(1); // true
...
tree.find(10); // false
```

## Extra methods

### The number of elements

To get the number of elements in the tree, use the `count` method. Returns the number of elements.

```cpp
bst<int> tree = {1, 6, 5, 3, 8};
...
tree.count(); // returns 5
```

### Check if the tree is empty

To check if the tree is empty or not, use the `is_empty` method. Returns `true` if the tree is empty, otherwise `false`.

```cpp
bst<int> tree = {1, 6, 5, 3, 8};
...
tree.is_empty(); // false
```

### Clear the tree

To clear the tree, use the `clear` method. 

```cpp
bst<int> tree = {1, 6, 5, 3, 8};
...
tree.clear(); 
tree.is_empty(); // true
```

## Iterators 

The `bst` class has iterators. The iterators have a `forward_iterator` type. 
You can only increase the iterator.

### Use iterators

To get the iterator to the first element of the tree, use the `begin()` method. 
Returns the iterator to the minimum element of the tree (the leftmost element). 
You can increase this iterator. But, do not reduce this iterator!

To get the iterator to the last of the tree, use the `end()` method. 
Returns the iterator to the maximum element of the tree (the rightmost element). 
Do not increase and reduce this iterator!

To get the type of iterators, use `bst<...>::iterator` or `auto`.

```cpp
bst<int> tree = {1, 6, 3, 8, -8, 23};
...
for (auto it = tree.begin(), it != tree.end(); it++) { ... }
...
auto it = tree.begin();
int a = *it; // a = -8
...
