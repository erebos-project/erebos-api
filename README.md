[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](github.com/erebos-project/erebos-api)
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

#### GCC

~~~
erebos-build> cmake ../erebos-api "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_COMPILER="g++"
erebos-build> make
~~~

#### MinGW

~~~
erebos-build> cmake ../erebos-api -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_COMPILER="g++"
erebos-build> make
~~~

#### NMake
~~~
erebos-build> cmake ../erebos-api -G "NMake Makefiles" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_FLAGS="/EHsc"
erebos-build> nmake
~~~

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

DEFVERSION(1, 0, 0)

int main(int argc, char* argv[]) {
	Args args(argc, argv);
	VERSIONFUNC("toolname");

	// Code

}

```

### License
See LICENSE file.
