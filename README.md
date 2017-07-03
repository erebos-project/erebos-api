[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/erebos-project/erebos-api/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/erebos-project/erebos-api.svg)](https://github.com/erebos-project/erebos-api/releases)
[![Travis](https://img.shields.io/travis/erebos-project/erebos-api.svg)](https://travis-ci.org/erebos-project/erebos-api)
[![AppVeyor](https://img.shields.io/appveyor/ci/erebos/erebos-api.svg)](https://ci.appveyor.com/project/erebos/erebos-api)

# erebos-api
A C++ library providing cross-platform low-level functions.

### Compiling from source
This project uses CMake as build system.

You can setup by command line with the following commands:

* Create a new directory in the same folder as the repo
* `cd` into the new directory
* Run the following commands based on your compiler

#### Linux/GCC

~~~
erebos-build> cmake ../erebos-api -DCMAKE_BUILD_TYPE="Release"
erebos-build> make
~~~

#### Windows/MinGW

~~~
erebos-build> cmake ../erebos-api -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_COMPILER="g++"
erebos-build> make
~~~

On some MinGW installations you might have to add the `-DCMAKE_MAKE_PROGRAM="mingw32-make"` argument to CMake and use `mingw32-make` instead of `make`.


#### Windows/MSVC
~~~
erebos-build> cmake ../erebos-api -G "NMake Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_FLAGS="/EHsc"
erebos-build> nmake
~~~


To compile as a shared library (DLL) add the `-DLIBRARY="shared"` argument to CMake.


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
