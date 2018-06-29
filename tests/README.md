## Testing C++/C code

### Requirements 
To build all the tests, you need CMake version 3 or newer, Make version 4.0 or newer, 
[Catch2](https://github.com/catchorg/Catch2) header file. 
You need to create a `Makefile` file using CMake and create tests using Make.

### Set the header file `catch.hpp`
To test C++/C code, [Catch2](https://github.com/catchorg/Catch2) header file is used. 
The header file must be in the `catch` folder. In tests this header file is included as `"catch/catch.hpp"`.
You must be in the `tests` folder. The possible command will look like this (`catch.hpp` is uploaded):
```bash
user@user:.../containers/tests/$ mkdir catch
cp /path/to/catch.hpp catch/catch.cpp
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
The `main.cpp` file is a main test file, has `CATCH_CONFIG_MAIN` macro.
<hr>
