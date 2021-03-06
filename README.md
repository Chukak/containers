# Containers
[![Build Status](https://travis-ci.com/Chukak/containers.png)](https://travis-ci.com/Chukak/containers)

## Documentation 
* [Queue](https://github.com/Chukak/containers/blob/master/docs/queue.md)
* [Stack](https://github.com/Chukak/containers/blob/master/docs/stack.md)
* [Sorted list](https://github.com/Chukak/containers/blob/master/docs/sorted_list.md)
* [Binary search tree](https://github.com/Chukak/containers/blob/master/docs/bst.md)
* [Counter](https://github.com/Chukak/containers/blob/master/docs/counter.md)
* [Static array](https://github.com/Chukak/containers/blob/master/docs/staticarray.md)

### Python
* [Python module](https://github.com/Chukak/containers/blob/master/python/README.md)

## How to compile
In Linux, you need `g++` version 7 or newer, CMake version 3.7.2 or newer for branch `master`. Also `g++` version 5 or newer, CMake version 3.4 or newer for btanch `old`, **but** theese branches not updated at the moment.

Clone this repository. You can compile the library using the `CMake` command or the `build_library.sh` script.
* Run make:
```bash
mkdir build && cd build
cmake ../
```

* Run `build_library.sh`:

```bash
./build_library.sh --inplace
```

OR

```bash
./build_library.sh /path/to/library
```

To get more information:

```bash
./build_library.sh --help
```

## Tests
For testing check this [page](https://github.com/Chukak/containers/blob/master/tests/README.md).

## Performance 
To show the performance of containers check this [page](https://github.com/Chukak/containers/tree/master/tests/performance).

