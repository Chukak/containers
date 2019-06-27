## Testing C++/C code

### Requirements 
To build all the tests, you need CMake version 3.7.2 or newer, 
[Catch2](https://github.com/catchorg/Catch2) header file. 
You need to create a `Makefile` file using CMake and create tests using Make.

### Add Catch2 library

```bash
git submodule init
git submodule update
```

### Create tests

* Run cmake with `CMakeLists.txt`:

```bash
cmake CMakeLists.txt
```

* Run make with `Makefile`:

```bash
make -f Makefile
```

* Run the executable file `tests`:

```bash
./tests
```
### Test files

The test for some classes has two test files. 
The `tst_name.cpp` file has tests for C++ code, for example: `tst_queue.cpp`.
The `tst_name_c.cpp` file has tests for C code, for example: `tst_queue_c.cpp`.
The `main.cpp` file has `CATCH_CONFIG_MAIN` macro.

## Coverage
If you want to see coverage of tests, you need `lcov 1.10` or newer. 
You need to create a `Makefile` file using CMake and create tests using Make.
```bash
cmake -DCMAKE_BUILD_TYPE="Coverage" CMakeLists.txt
```

<hr>
