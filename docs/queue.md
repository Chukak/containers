# Queue 

Queue - an abstract data type, has an implementation of access to elements by the principle FIFO(First-In-First-Out). 
In this library, the queue is implemented as a linked list. 

## Header

The `Queue` class is implemented in the `queue.h` header file, which is located in the category `queue`. To include the header file:
```cpp
#include <containers/queue/queue.h>
```

## Create a queue

The queue is implemented using C++ templates. To create a queue, pass the data type, 
which will be in the queue in the constructor.

Default constructor:

```cpp
Queue<int> q;
```

Using initializer list:

```cpp
Queue<int> q = {1, 2, 3, 4, 5};
```

## Add elements

To add elements into the queue, use the `enqueue` method. The `enqueue` method adds elements using the principle 
FIFO(First-In-First-Out).

```cpp
Queue<int> q;
...
q.enqueue(1)
q.enqueue(2)
```

## Remove elements

To remove elements from the queue, use the `dequeue` method. The `dequeue` method removes the first element 
of the queue. Returns the deleted element.

```cpp
Queue<int> q = {1, 2, 3};
...
int a = q.dequeue(); // returns 1
int b = q.dequeue(); // returns 2
```

**Note**: At the moment, if the queue is empty, the result of the `dequeue` method has an undefined behavior. 
Be careful when using this method.

```cpp
Queue<int> q;
...
int a = q.dequeue(); // ???
```

## Get the first element

The queue has the `front` method, which returns the first element of the queue.

```cpp
Queue<int> q = {1, 2, 3};
...
q.front(); // returns 1
```

**Note**: At the moment, if the queue is empty, the result of the `front` method has an undefined behavior. 
Be careful when using this method.

## Get the last element

Also, the queue has the `back` method which returns the last element of the queue.

```cpp
Queue<int> q = {1, 2, 3};
...
q.back(); // returns 3
```

**Note**: At the moment, if the queue is empty, the result of the `back` method has an undefined behavior. Be careful when using this method.

## Extra methods

### The number of elements

To get the number of elements in the queue, use the `count` method. Returns the number of elements.

```cpp
Queue<int> q = {1, 2, 3};
...
q.count(); // returns 3
```

### Check if the queue is empty

To check if the queue is empty or not, use the `is_empty` method. Returns `true` if the queue is empty, otherwise `false`.

```cpp
Queue<int> q;
...
q.is_empty(); // true
...
q.enqueue(1);
q.is_empty(); // false
```

### Clear the queue

To clear the queue, use the `clear` method. 

```cpp
Queue<int> q = {1, 2, 3};
...
q.clear();
q.is_empty(); // true
```

## Iterators

The `Queue` class has iterators of the queue. The iterators have a `forward_iterator` type. 
You can only increase the iterator.

### Use iterators

To get the iterator to the first element of the queue, use the `begin()` method. 
Returns the iterator to the first element of the queue. You can increase the iterator.
But, do not reduce this iterator! 

To get the iterator to the end of the queue, use the `end()` method. 
Do not increase the `end()` iterator!
To get the type of iterators, use `Queue<...>::iterator` or `auto`.
For example:

```cpp
Queue<int> q = {1, 2, 3, 4, 5};
for (auto it = q.begin(), it != q.end(); it++) { ... }
```

You can use iterators in STL algorithms, but it is not guaranteed that the iterators will work correct in all the algorithms.

<br>

# Queue (namespace pure_c)

Also, the `queue.h` header file has a implementation of the queue as a C-code. It implementes in namespace `pure_c`.

**Note**: all the C functions in the `queue.h` header have the prefix `queue_`.

## `queue`

The type `queue` is the structure. Creates a new queue using the `queue_create()` function. 
The `queue` structure has some members:
* `queue->count` - the number of elements.
* `queue->empty` - `1` if the queue is empty, otherwise `0`.
* `queue->_front` - a pointer to the first element. It is not recommended to use. Use the `queue_front()` function.
* `queue->_back` - a pointer to the last element. It is not recommended to use. Use the `queue_back()` function.

## Create a queue

To create a queue, use the `q_create_queue` function without any arguments. Returns a pointer to the queue.
```c
queue * q = queue_create();
```

## Add elements

To add elements into the queue, use the `queue_enqueue` function, pass the pointer to the queue as the first argument, 
the pointer to an element as the second argument. 
The `queue_enqueue` function adds elements using the principle FIFO(First-In-First-Out). 

```c
queue * q = queue_create();
...
int a = 1;
queue_enqueue(q, &a);
```

## Remove elements

To remove elements from the queue, used the `queue_dequeue` function, pass the pointer to the queue as the first argument. 
The `queue_dequeue` function removes the first element of the queue. 
Returns the pointer to the deleted element.

```c
queue * q = queue_create();
...
int a = 1;
queue_enqueue(q, &a);
int * r = (int *)queue_dequeue(q); // returns the pointer 
if (*r == 1) // true
```

If the queue is empty, the result of the `queue_dequeue` function has the `NULL` pointer. 

```c
queue * q = queue_create();
...
int a = 1;
queue_enqueue(q, &a);
int * r = (int *)queue_dequeue(q); // returns the pointer 
int * r2 = (int *)queue_dequeue(q); // returns the NULL pointer
if (r2 == NULL) // true
```

## Get the first element

To get the first element of the queue, use the `queue_front` function, pass the pointer to the queue as the first argument.
Returns the pointer to the first element.

```c
queue * q = queue_create();
...
int a = 1;
queue_enqueue(q, &a);
...
int * r = (int *)queue_front(q); // returns the pointer
if (*r == 1) // true
```

If the queue is empty, the result of the `queue_front` function has the `NULL` pointer.

## Get the last element

To get the last element of the queue, use the `queue_back` function, pass the pointer to the queue as the first argument.
Returns the pointer to the last element.

```c
queue * q = queue_create();
...
int a = 1;
queue_enqueue(q, &a);
...
int * r = (int *)queue_back();
if (*r == 1) // true
```

If the queue is empty, the result of the `queue_back` function has the `NULL` pointer.

## Delete the queue

To delete the queue, use the `queue_delete` function, pass the pointer to the queue as the first argument.
Do not forget to delete the queue, when you do not use it.

```c
queue * q = queue_create();
...
queue_delete(q);
```

## Extra functions

### The number of elements

To get the number of elements in the queue, use the `queue_count` function, pass the pointer to the queue as the first parameter. 
Returns the number of elements. 
Use this function or, if necessary, use `queue->count`.

```c
queue * q = queue_create();
...
queue_count(q); // returns 0
```
<br>
