[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/erebos-project/erebos-api/blob/master/LICENSE)
[![GitHub tag](https://img.shields.io/github/tag/erebos-project/erebos-api.svg)](https://github.com/erebos-project/erebos-api/tags)
[![Travis](https://img.shields.io/travis/erebos-project/erebos-api.svg)](https://travis-ci.org/erebos-project/erebos-api)
[![AppVeyor](https://img.shields.io/appveyor/ci/erebos/erebos-api.svg)](https://ci.appveyor.com/project/erebos/erebos-api)

# erebos-api
A C++ library providing cross-platform low-level functions.

### NOTE for Windows users
So, you decide to build this library on a Windows platform, right? Then, read below.

Basically, I tried to do the following:

~~~
erebos-api/build> cmake .. -G "Visual Studio 14 2015" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_FLAGS="/O2 /EHsc /W2" -DMAKE_TESTS="yes"
erebos-api/build> msbuild ALL_TESTS.vcsxproj
~~~

At the end, I got very strange errors, about some debugging features, I DID NOT REQUEST.

This will not work.

At this point, you have 4 ways:

  * Use **MinGW** (I would not on Windows, but anyway...)
  * Use **NMake** (My own preferred way)
  * Use directly a Visual Studio **15 2017** (important) environment with **CMAKE**!!!
  * Always use MSBuild, but specifying _/p:Configuration=Release_

I would prefer the NMake method (less bloat, less output shit), as shown below.

### Why use Erebos
Erebos provides simple to use and cross-platform utilities that many programs need to use and usually re-implement or use giant libraries that take in more dependencies and slow down compilation time (and sometimes performance).
This library solves this problem, as it is light-weight and really easy and straightforward to use.
For example, if you want to read a file's entire content into a string, you can just write `std::string stringdata = file::read("filename")`, if you want to read binary data you can use `data_t binarydata = file::read_bin("filename")` and Erebos writes the file's content into a handy `data_t` structure and so on.
We support file operations (like writing, reading and deleting files and folders), misc functionalities like changing font color and
concatenated printing to the screen (`println`), an easy to use Logger class and functions to work on processes.

### Compiling from source
Currently, it is not advised to use clang, as we are not testing this library with LLVM compiler.

This project uses CMake as build system.

You can setup by command line with the following commands:

 * Create a new directory inside the repo directory
 * `cd` into the new directory
 * Run the following commands based on your compiler

**Note:** you may want to run tests? *See below*
**Note:** you may want to specify your own flags for compilation, right?
~~~
-DCMAKE_CXX_FLAGS:string=""
~~~

Is what you are looking for ;)

*See reccomended compilation flags below*

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


#### Windows/MSVC/NMake
~~~
erebos-api/build> cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE="Release"
erebos-api/build> nmake
~~~


To compile as a shared library add the `-DLIBRARY="shared"` argument to CMake.

If you want to enable colored output on Windows add the `-D_WINDOWS_SHELL_COLOR` argument to CMake.

### Reccomended compilation flags

 * Under GCC/LLVM (ignoring platform)
 
 ~~~
 -W -finline-functions -funroll-loops -O2
 ~~~

 If you want to save space by stripping the library, add *-s* switch

 * Using MSVC

 ~~~
 /O2 /EHsc /W2
 ~~~

### Running tests
If you want to run tests, just add *-DMAKE_TESTS="yes"* switch to the CMake command line, then compile the project with chosen method, after success, run *ctest*. If using GCC/LLVM and GCOV is availible, then coverage reports will be generated, so you can use gcov and lcov to perform coverage test if necessary.

(*See scripts/coverage.sh script*)

### Using the library
* Create a source file
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
VERSIONFUNC(args, "toolname")
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
