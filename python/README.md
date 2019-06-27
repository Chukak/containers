# Python 3

## How to compile module

This library can be compiled as a python module. You need `Boost` 1.52 or newer.

Commands:
```bash
apt-get install python3-dev
apt-get install libboost-all-dev

mkdir build && cd build
cmake ../python/
make
```
And put `containers.so` in place with your *.py files

## How to use

### Import module

In python:

```python
import containers
```

Or:

```python
from containers import queue, stack
```

## Containers

### Stack

Stack - an abstract data type, representing a list of elements, organized by the principle LIFO(Last-In-First-Out).

#### Methods 

##### Create a stack
To create a stack, use the class `stack`.

```python
s = stack()
```

##### Add elements

To add elements into the stack, use the `push` method. 

```python
s = stack()
...
s.push(1)
s.push(2)
s.push(3)
```

##### Remove elements

To remove elements from the stack, use the `pop` method. 
The method returns the deleted element. If the stack is empty, the method returns `None`.

```python
s = stack()
...
s.push(1)
s.push(2)
...
a = s.pop() # a = 2
b = s.pop() # b = 1
c = s.pop() # c = None
```

#### Members

* `stack.count` - the numbers of elements.
* `stack.empty` - `True` if the stack is empty, otherwise `False`.
* `stack.front` - the first element of the stack.`

### Queue

Queue - an abstract data type, has an implementation of access to elements by the principle FIFO(First-In-First-Out).

##### Methods 

##### Create an queue

To create a queue, use the class `queue`.

```python
q = queue()
```

##### Add elements

To add elements into the queue, use the `enqueue` method. 

```python
q = queue()
...
q.enqueue(1)
q.enqueue(2)
q.enqueue(3)
```

##### Remove elements

To remove elements from the queue, use the `dequeue` method. 
The method returns the deleted element. If the queue is empty, the method returns `None`.

```python
q = queue()
...
q.enqueue(1)
q.enqueue(2)
...
a = q.dequeue() # a = 1
b = q.dequeue() # b = 2
c = q.dequeue() # c = None
```

##### Clear the queue

To clear the queue, use the `clear` method. 

```python
q = queue();
...
...
q.enqueue(1)
q.enqueue(2)
...
q.clear();
q.is_empty(); # True
```

#### Members

* `queue.count` - the numbers of elements.
* `queue.empty` - `True` if the queue is empty, otherwise `False`.
* `queue.front` - the first element of the queue.
* `back` - the last element of the queue.


## Binary search tree

Binary search tree - a sorted binary tree, stores objects in memory, can find, insert and delete objects. Elements insert in the sorted order.

#### Methods

##### Create a binary search tree

To create a binary search tree, use the class `bst`.

```python
tree = bst()
```

##### Insert elements

To insert elements into the tree, use the `insert` method. 
 
```python
tree = bst();
...
tree.insert(1); # the root of the tree
tree.insert(5);
tree.insert(-10);
```

##### Remove elements

To remove elements from the tree, use the `remove` method. 

```python
tree = bst();
...
tree.insert(1);
tree.insert(5);
...
tree.remove(5);
...
tree.remove(7); # RuntimeError, because tree has not 7
```

##### Find elements(if the tree has this element)

To find an element in the tree, use the `find` method. Return `True` is the tree has this element, otherwise returns `False`.
If the tree is empty, returns `False`.

```python
tree = bst();
...
tree.insert(1);
tree.insert(5);
...
tree.find(1); # True
...
tree.find(10); # False
```

### Clear the tree

To clear the tree, use the `clear` method. 

```python
tree = bst();
...
tree.insert(1);
tree.insert(5);
...
tree.clear(); 
tree.is_empty(); # True
```

### Get the minimum element(the leftmost element)

To get the minimum element of the tree, use the `min` method. Returns the minimum element of the tree.

```python
tree.min()
```
### Get the maximum element(the rightmost element)

To get the maximum element of the tree, use the `max` method. Returns the maximum element of the tree.

```python
tree.max()
```

#### Members

* `bst.count` - the number of elements.
* `bst.is_empty` - `True` if the queue is empty, otherwise `False`.
* `bst.root` - the root of the tree.


## Testing the python module

To test the `containers` module, put `containers.so` in `python/tests` directory and run command:

```bash
python3 -m unittest discover -s ./ -p "tst_*.py"
```

Also, in files `python/tests/tst_*.py` you will find examples of use.

<hr>

