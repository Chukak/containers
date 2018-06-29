# Stack

Stack - an abstract data type, has an implementation of access to elements by the principle LIFO(Last-In-First-Out). 
In this library, the stack is implemented as a linked list.

## Header
The `Stack` class is implemented in the `stack.h` header file, which is located in the category `stack`. 
To include the header file:
```cpp
#include "containers/stack/stack.h"
```

## Create a stack
The `Stack` class is implemented using C++ templates. 
To create a stack, pass the data type, which will be in the stack in the constructor.

Standard initialization:
```cpp
Stack<int> s;
```

Initialization with braces:
```cpp
Stack<int> s = {1, 2, 3};
```

Initialization a stack from another stack:
```cpp
Stack<int> orig = {1, 2, 3};
Stack<int> s(orig);
```

## Add elements
To add elements in the stack, use the `push` method. The `push` method adds elements using the principle LIFO(Last-In-First-Out). 
The function returns nothing.
```cpp
Stack<int> s;
...
s.push(1);
s.push(2);
```

## Remove elements
To remove elements from the stack, use the `pop` method. The `pop` method removes the first element of the stack.
Returns the deleted element.
```cpp
Stack<int> s = {1, 2, 3};
...
s.pop(); // returns 3
```
If the stack is empty, the result of the `pop` method has an undefined behavior. Be careful when using this method.
```cpp
Stack<int> s;
...
s.pop(); // ???
```

## Get the first element
To get the first element of the stack, use the `front` method. The `front` method returns the first element of the stack
at the moment.
```cpp
Stack<int> s = {1, 2, 3};
...
s.front(); // returns 3
```
If the stack is empty, the result of the `front` method has an undefined behavior. Be careful when using this method.

## Extra methods

### The number of elements
To get the number of elements in the stack, use the `count` method. Returns the number of elements.
```cpp
Stack<int> s = {1, 2, 3};
...
s.count(); // returns 3
```

### Check if the stack is empty
To check if the stack is empty or not, use the `is_empty` method. Returns `true` if the stack is empty, otherwise `false`.
```cpp
Stack<int> s;
...
s.is_empty(); // true
...
s.push(1);
s.is_empty(); // false
```

## Iterators
The `Stack` class has iterators of stack. The iterators are `forward_iterator`. 
You can only increase the iterator.

### Use iterators
To get the iterator on the first element of the stack, use the `begin()` method. 
Returns the iterator to the first element of stack. You can only increase the iterator.
To get the iterator to the end of the stack, use the `end()` method. 
Don\`t increase and reduce the `end()` iterator! 

To get the type of iterators, use `Stack<...>::iterator` or use `auto`. 
For example:
```cpp
Stack<int> s = {1, 2, 3, 4, 5};
for (auto it = s.begin(); it != s.end(); ++it) { ... }
```
You can use iterators in STL algorithms, but it is not guaranteed that the iterators will work in all algorithms

<br>

# Stack (C-code)
Also, the `stack.h` header file has an implementation of the stack as a C-code. 

Note: all the C functions in the `stack.h` header have the prefix `s_`.

## `stack`
The type `stack` is the structure. 
Initialized it as a pointer, using `s_create_stack()` function. 
The `stack` structure has some members:
* `stack->count` - the numbers of elements.
* `stack->empty` - `1` if the stack is empty, otherwise `0`.
* `stack->front` -  a pointer to the first element. It is not recommended to use. Use the `s_front()` function.

## Create a stack
To create a stack, use the `s_create_stack` function without any arguments. Returns a pointer to the stack.
```c
stack *s = s_create_stack();
```

## Add elements
To add elements in the stack, use the `s_push` function, pass the pointer to the stack as the first argument, 
the pointer to an element as the second argument. 
The `s_push` function adds elements using the principle LIFO(Last-In-First-Out). 
The function returns nothing.
```c
stack *s = s_create_stack();
...
int a = 1;
s_push(s, &a);
```

## Remove elements
To remove elements from the stack, use the `s_pop` function, pass the pointer to the stack as the first argument. 
The `s_pop` function removes the first element of the stack. 
Returns the pointer to the deleted element.
```c
stack *s = s_create_stack();
...
int a = 1;
s_push(s, &a);
int *r = (int *)s_pop(s); // returns the pointer
if (*r == 1) // true
```
If the stack is empty, the result of the `s_pop` function has the `NULL` pointer.
```c
stack *s = s_create_stack();
...
int a = 1;
s_push(s, &a);
int *r = (int *)s_pop(s); // returns the pointer
int *r2 = (int *)s_pop(s); // returns the NULL pointer
if (r2 == NULL) // true
```

## Get the first element
To get the first element of the stack, use the `s_front` function, pass the pointer to the stack as the first argument. 
Returns the pointer to the first element.
```c
stack *s = s_create_stack();
...
int a = 1;
s_push(s, &a);
...
int *r = (int *)s_front(s);
if (*r == 1) // true
```
If the stack is empty, the result of the `s_front` function has the `NULL` pointer.

## Delete the stack
To delete the stack, use `s_delete_stack` function, pass the pointer to the stack as the first argument. 
The function returns nothing. 
Don\`t forget to delete the stack, when you don\`t use it.
```c
stack *s = s_create_stack();
...
s_delete_stack(s);
```

## Extra functions

### The number of elements
To get the number of elements in the stack, use the `s_count` function, pass the pointer to the stack as the first parameter. 
Returns the number of elements. 
Use this function, if necessary or instead this function, use `stack->count`.
```c
stack *s = s_create_stack();
...
s_count(s); // returns 0
```

