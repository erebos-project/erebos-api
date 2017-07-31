//#define TEST_ABORT_IF_FAIL
#include "test.h"

int sym_sum(int a)
{
	return a + 1;
}

int main()
{
	NEW_MODULE_TEST("mymodule");

	BEGIN_TEST PRE_CALL(sym_sum);
	WITH_RETV CALLBACK(1);
	TEST_EQUALS(1);
	END_TEST();

	END_MODULE_TEST();
}