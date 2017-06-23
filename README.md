# erebos-api
A C++ library providing cross-platform low-level functions.

### Guidelines for contribution
* Use tabs, do not use spaces for indentation
* If a program needs more than 1 file, create a folder and place only the main in `src`
* You can place unmaintained/undocumented code into `misc` folder
* If you use these utilities frequently please consider contributing
* Use snake case for functions

### Using the library
* Create a file named `toolname.cpp` in `erebos-tools/src` folder or wherever you want
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
VERSIONFUNC(toolname) // toolname without quotes
```
* Write your code from there as usual, you might also want to `using namespace erebos`.

### License
See LICENSE file.
