# Python 

## How to compile module
This library can be compiled as a python module. You need to set the path to the files `Python.h` and `structmember.h`.
By default used the following paths are used: `/usr/include/python*.*`, `/usr/local/include/python*.*`, `/usr/lib/python*.*`, 
`/usr/local/lib/python*.*`, where `*.*` - python of version. For example: `/usr/include/python3.5`. 
To use a special path to the files `Python.h` and `structmember.h` set the variable `PY_HEADER_PATH`.

For example with default paths, in Linux:
```bash
python setup.py built_ext --inplace
```
With a special path:
```bash
PY_HEADER_PATH=/path/to/files python setup.py build_ext --inplace
```
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
This python module used version of stack, written in C.

#### Methods 

##### Create a stack
To create a stack, just call the class `stack`.
```python
s = stack()
```

##### Add elements
To add elements to the stack, call the `push` method of the `stack` class. 
The method returns `True` if successful, otherwise `False`.
```python
s = stack()
...
s.push(1)
s.push(2)
s.push(3)
```

##### Remove elements
To remove elements from the stack, call the `pop` method of the `stack` class. 
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

##### Get the first element from the stack
To get the fisrt element from the stack, call the `front` method of the `stack` class. 
The method returns the first element. If the stack is empty, the method returns `None`.
```python
s = stack()
...
s.push(1)
...
a = s.front() # a = 1
b = s.pop() # b = 1
c = s.front() # c = None
```

### Members
* `stack.count` - the numbers of elements.
* `stack.empty` - `0` if the stack is empty, otherwise `1`.

### Queue
Queue - an abstract data type, has an implementation of access to elements by the principle FIFO(First-In-First-Out).
This python module used version of queue, written in C.

#### Methods 

##### Create an queue
To create a stack, just call the class `queue`.
```python
q = queue()
```

##### Add elements
To put elements to the queue, call the `enqueue` method of the `queue` class. 
The method returns `True` if successful, otherwise `False`.
```python
q = queue()
...
q.enqueue(1)
q.enqueue(2)
q.enqueue(3)
```

##### Remove elements
To remove elements from the queue, call the `dequeue` method of the `queue` class. 
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

##### Get the first element from the queue
To get the fisrt element from the queue, call the `front` method of the `queue` class. 
The method returns the first element. If the queue is empty, the method returns `None`.
```python
q = queue()
...
q.enqueue(1)
...
a = q.front() # a = 1
b = q.dequeue() # b = 1
c = q.front() # c = None
```

##### Get the last element from the queue
To get the last element from the queue, call the `back` method of the `queue` class. 
The method returns the last element. If the queue is empty, the method returns `None`.
```python
q = queue()
...
q.enqueue(1)
q.enqueue(2)
...
a = q.back() # a = 2
b = q.dequeue() # b = 1
a = q.back() # a = 2
b = q.dequeue() # b = 2
c = q.back() # c = None
```

### Members
* `queue.count` - the numbers of elements.
* `queue.empty` - `0` if the queue is empty, otherwise `1`.

## Testing the python module
To test the `containers` module, call `pytests.py` to run all the tests:
```bash
cd tests && python pytests.py
```

<hr>

