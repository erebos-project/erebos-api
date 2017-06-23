# erebos-api
A C++ library providing cross-platform low-level functions.

### Guidelines for contribution
* Use tabs, do not use spaces for indentation
* If you use these utilities frequently please consider contributing
* Use snake case for functions

### Using the library
* Create a file named `toolname.cpp` in `erebos-tools/src` folder or wherever you want
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
VERSIONFUNC(toolname) // toolname without quotes
```
* Write your code from there as usual, you might also want to `using namespace erebos`.

Example:
```
#include "framework.h"

using namespace erebos;

DEFVERSION(1, 0, 0)

int main(int argc, char* argv[]) {
	Args args(argc, argv);
	VERSIONFUNC(toolname);

	// Code

}

```

### License
See LICENSE file.
