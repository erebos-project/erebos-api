[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/erebos-project/erebos-api/blob/master/LICENSE)
[![GitHub tag](https://img.shields.io/github/tag/erebos-project/erebos-api.svg)](https://github.com/erebos-project/erebos-api/tags)
[![Travis](https://img.shields.io/travis/erebos-project/erebos-api.svg)](https://travis-ci.org/erebos-project/erebos-api)
[![AppVeyor](https://img.shields.io/appveyor/ci/erebos/erebos-api.svg)](https://ci.appveyor.com/project/erebos/erebos-api)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/371dbc485a0345f3956bb9632728cd4a)](https://www.codacy.com/app/StefanoBelli/erebos-api?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=erebos-project/erebos-api&amp;utm_campaign=Badge_Grade)
[![Coverage Status](https://coveralls.io/repos/github/erebos-project/erebos-api/badge.svg?branch=master)](https://coveralls.io/github/erebos-project/erebos-api?branch=master)

# Erebos
A C++ library providing cross-platform low-level functions for string manipulation, file handling, working with processes, networking and keyboard input through command line interface.

### Why use Erebos
Erebos provides simple to use and cross-platform utilities that many programs need to use and usually re-implement or use giant libraries that take in more dependencies and slow down compilation time (and sometimes performance).
This library solves this problem, as it is light-weight and really easy and straightforward to use.
We support file operations (like writing, reading and deleting files and folders), miscellaneous functionalities like changing font color and
concatenated printing to the screen (`println`), string manipulation and functions to work on processes.

### Compiling from source
It is not advised to use clang, as we are not testing this library with LLVM compiler.

This project uses CMake as build system.

You can setup by command line with the following commands:

 * Create a new directory inside the repo directory
 * `cd` into the new directory
 * Run the following commands based on your compiler

**Note:** to specify your own flags you may use
~~~
-DCMAKE_CXX_FLAGS:string=""
~~~

*See recommended compilation flags below*

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

### Note for Windows users
If you want to compile on Windows, read the following.
Basically, I tried to do the following:

~~~
erebos-api/build> cmake .. -G "Visual Studio 14 2015" -DCMAKE_BUILD_TYPE="Release" -DCMAKE_CXX_FLAGS="/O2 /EHsc /W2" -DMAKE_TESTS="yes"
erebos-api/build> msbuild ALL_TESTS.vcsxproj
~~~

At the end, I got very strange errors, about some debugging features, **I did not request**.

At this point, you have 4 ways:

  * Use **MinGW**
  * Use **NMake**
  * Use directly a **Visual Studio 15 2017** environment with **CMake**
  * Still use MSBuild, but specifying _/p:Configuration=Release_

I would prefer the NMake method (less bloat), as shown up.

### Header-only
If you just need simple functionality and don't want to link the library, you can use a header-only version.
All you have to do is including `erebos.h` like this:
~~~
#define EREBOS_HEADERONLY
#include "erebos.h"
~~~
This will give you access to inline functions defined in headers without the need to compile the library.
NOTE: You may need to rename `version.h.in` to `version.h` and change the version constants in the file.

### Recommended compilation flags

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
If you want to run tests, just add *-DMAKE_TESTS="yes"* switch to the CMake command line, then compile the project with chosen method, after success, run *ctest*. If using GCC/LLVM and GCOV is available, then coverage reports will be generated, so you can use gcov and lcov to perform coverage test if necessary.

(*See scripts/coverage.sh script*)

### License
See LICENSE file.
