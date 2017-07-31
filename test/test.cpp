#include "test.h"

int sym_sum(int a)
{
	return a + 1;
}

void sym_sum(int a, int b)
{
	std::cout << "lololol <" << a + b;
}

int main()
{
	NEW_MODULE_TEST("mymodule");

	BEGIN_OVERLOAD(sym_sum,int,int);
	WITH_RETV CALLBACK(1);
	END();

	BEGIN_VOID(sym_sum, int, int);
	WITHOUT_RETV CALLBACK(1, 2);
	END();

	END_MODULE_TEST();
}