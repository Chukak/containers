# Queue 
Queue - an abstract data type, has an implementation of access to elements by the principle FIFO(First-In-First-Out). 
In this library, the queue is implemented as a linked list. 

## Header
The `Queue` class is implemented in the `queue.h` header file, which is located in the category `queue`. To include the header file:
```cpp
#include "containers/queue/queue.h"
```

## Create an queue
The `Queue` class is implemented using C++ templates. To create an queue, pass the data type, 
which will be in the queue in the constructor.

Standard initialization:
```cpp
Queue<int> q;
```


Initialization with braces:
```cpp
Queue<int> q = {1, 2, 3, 4, 5};
```

Initialization an queue from another queue:
```cpp
Queue<int> orig = {1, 2, 3};
Queue<int> q(orig);
```

## Add elements
To add elements in the queue, use the `enqueue` method. The `enqueue` method adds elements using the principle 
FIFO(First-In-First-Out). The function returns nothing.
```cpp
Queue<int> q;
...
q.enqueue(1)
q.enqueue(2)
```

## Remove elements
To remove elements from the queue, use the `dequeue` method. The `dequeue` method removes the first element 
from the queue. Returns the deleted element.
```cpp
Queue<int> q = {1, 2, 3};
...
q.dequeue(); // returns 1
q.dequeue(); // returns 2
```
If the queue is empty, the result of the `dequeue` method has an undefined behavior. Be careful when using this method.
```cpp
Queue<int> q;
...
int a = q.dequeue(); // ???
```

## Get the first element
The `Queue` class has the `front` method, which returns the first element in the queue at the moment.
```cpp
Queue<int> q = {1, 2, 3};
...
q.front(); // returns 1
```
If the queue is empty, the result of the `front` method has an undefined behavior. Be careful when using this method.

## Get the last element
Also, the `Queue` class has the `back` method which returns the first element in the queue at the moment.
```cpp
Queue<int> q = {1, 2, 3};
...
q.back(); // returns 3
```
If the queue is empty, the result of the `back` method has an undefined behavior. Be careful when using this method.

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
To clear the queue, use the `clear` method. The method returns nothing.
```cpp
Queue<int> q = {1, 2, 3};
...
q.clear();
q.is_empty(); // true
```

## Iterators
The `Queue` class has iterators of queue. The iterators have the type `forward_iterator`. 
You can only increment the iterator.
### Use iterators
To get the iterator on the first element of the queue, use the `begin()` method. 
Returns the iterator to the first element of queue. You can increase the iterator.
To get the iterator to the end of the queue, use the `end()` method. 
Don\`t increase the `end()` iterator!
To get the type of iterators, use `Queue<...>::iterator` or use `auto`.
For example:
```cpp
Queue<int> q = {1, 2, 3, 4, 5};
for (auto it = q.begin(), it != q.end(); it++) { ... }
```
You can use iterators in STL algorithms, but it is not guaranteed that the iterators will work in all algorithms

<br>

# Queue (C)
Also, the `queue.h` header file has a implementation of queue as a C-code.
To store the queue use the type `queue`. Note: all the C functions in the `queue.h` header have the prefix `q_`.

## `queue`
The type `queue` is the structure. Initialized it as a pointer, using `q_create_queue()` function. 
The `queue` structure has some members:
* `queue->count` - the number of elements.
* `queue->empty` - `1` if the queue is empty, otherwise `0`.
* `queue->_front` - a pointer to the first element. It is not recommended to use. Use the `q_front()` function.
* `queue->_back` - a pointer to the last element. It is not recommended to use. Use the `q_back()` function.

## Create an queue
To create an queue, call the `q_create_queue` function without any arguments. Returns a pointer to the queue.
```c
queue *q = q_create_queue();
```

## Add elements
To add elements in the queue, use the `q_enqueue` function, pass the pointer to the queue as the first argument, 
the pointer to an element as the second argument. 
The `q_enqueue` function adds elements using the principle FIFO(First-In-First-Out). 
The function returns nothing.
```c
queue *q = q_create_queue();
...
int a = 1;
q_enqueue(q, &a);
```

## Remove elements
To remove elements from the queue, used the `q_dequeue` function, pass the pointer to the queue as the first argument. 
The `q_dequeue` function removes the first element from the queue. 
Returns the pointer to the deleted element.
```c
queue *q = q_create_queue();
...
int a = 1;
q_enqueue(q, &a);
int *r = (int *)q_dequeue(q); // returns the pointer 
if (*r == 1) // true
```
If the queue is empty, the result of the `q_dequeue` function has the `NULL` pointer. 
```c
queue *q = q_create_queue();
...
int a = 1;
q_enqueue(q, &a);
int *r = (int *)q_dequeue(q); // returns the pointer 
int *r2 = (int *)q_dequeue(q); // returns the NULL pointer
if (r2 == NULL) // true
```

## Get the first element
To get the first element from the queue, use the `q_front` function, pass the pointer to the queue as the first argument.
Returns the pointer to the first element.
```c
queue *q = q_create_queue();
...
int a = 1;
q_enqueue(q, &a);
...
int *r = (int *)q_front(q); // returns the pointer
if (*r == 1) // true
```
If the queue is empty, the result of the `q_front` function has the `NULL` pointer.

## Get the last element
To get the last element fron the queue, use the `q_back` function, pass the pointer to the queue as the first argument.
Returns the pointer to the last element.
```c
queue *q = q_create_queue();
...
int a = 1;
q_enqueue(q, &a);
...
int *r = (int *)q_back();
if (*r == 1) // true
```
If the queue is empty, the result of the `q_back` function has the `NULL` pointer.
## Delete the queue
To delete the queue, use `q_delete_queue` function, pass the pointer to the queue as the first argument.
The function returns nothing.
Don\`t forget to delete the queue, when you don\`t use it.
```c
queue *q = q_create_queue();
...
q_delete_queue(q);
```

## Extra methods
### The number of elements
To get the number of elements in the queue, use the `q_count` function, pass the pointer to the queue as the first parameter. 
Returns the number of elements. 
Use this function, if necessary or instead this function, use `queue->count`.
```c
queue *q = s_create_queue();
...
q_count(q); // returns 0
```
<br>
