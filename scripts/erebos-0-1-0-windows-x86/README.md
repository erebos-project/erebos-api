[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/erebos-project/erebos-api/blob/master/LICENSE)
[![GitHub tag](https://img.shields.io/github/tag/erebos-project/erebos-api.svg)](https://github.com/erebos-project/erebos-api/tags)
[![Travis](https://img.shields.io/travis/erebos-project/erebos-api.svg)](https://travis-ci.org/erebos-project/erebos-api)
[![AppVeyor](https://img.shields.io/appveyor/ci/erebos/erebos-api.svg)](https://ci.appveyor.com/project/erebos/erebos-api)

# erebos-api
A C++ library providing cross-platform low-level functions.

### Compiling from source
This project uses CMake as build system.

You can setup by command line with the following commands:

* Create a new directory inside the repo directory
* `cd` into the new directory
* Run the following commands based on your compiler

#### Linux/GCC

~~~
erebos-api/build> cmake .. -DCMAKE_BUILD_TYPE="Release"
erebos-api/build> make
~~~

#### Windows/MinGW

~~~
erebos-api/build> cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_COMPILER="g++"
erebos-api/build> make
~~~

On some MinGW installations you might have to add the `-DCMAKE_MAKE_PROGRAM="mingw32-make"` argument to CMake and use `mingw32-make` instead of `make`.


#### Windows/MSVC
~~~
erebos-api/build> cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_FLAGS="/EHsc"
erebos-api/build> nmake
~~~


To compile as a shared library add the `-DLIBRARY="shared"` argument to CMake.

If you want to enable colored output on Windows add the `-D_WINDOWS_SHELL_COLOR` argument to CMake.


### Using the library
* Create a file named `toolname.cpp`
* Include `framework.h`
* Define the program's initial version like this:
```
DEFVERSION(1, 0, 0) // or whatever version you want
```
* Declare `main`
* Declare the argument list like this:
```
Args args(argc, argv);
```
* Declare the version function using the `VERSIONFUNC` macro like this:
```
VERSIONFUNC("toolname")
```
* Write your code from there as usual, you might also want to `using namespace erebos`.

Example:
```
#include "framework.h"

using namespace erebos;

DEFVERSION(1, 0, 0);

int main(int argc, char* argv[]) {
	Args args(argc, argv);
	VERSIONFUNC(args, "toolname");

	// Code

}

```

### License
See LICENSE file.
