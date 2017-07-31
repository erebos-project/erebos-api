//#define TEST_ABORT_IF_FAIL
#include "test.h"

bool lol()
{
	return true;
}

bool islol(bool a)
{
	return !a;
}

int sym_sum(int a)
{
	return a + 1;
}

int sym_sum(int a, int b)
{
	return a + b;
}

void more()
{

}

void little_more(int a)
{

}

void little_more_ov(int a, int b)
{

}

void little_more_ov(bool a)
{

}

int main()
{
	NEW_MODULE_TEST("mymodule");

	BEGIN_TEST PRE_CALL(lol);
	WITH_RETV CALLBACK();
	TEST_EQUALS(true);
	END_TEST();

	BEGIN_TEST PRE_CALL(islol);
	WITH_RETV CALLBACK(false);
	TEST_EQUALS(true);
	END_TEST();

	BEGIN_TEST PRE_CALL_OVERLOAD(sym_sum, int, int);
	WITH_RETV CALLBACK(1);
	TEST_EQUALS(1);
	END_TEST();

	BEGIN_TEST PRE_CALL_OVERLOAD(sym_sum, int, int, int);
	WITH_RETV CALLBACK(1, 2);
	TEST_EQUALS(3);
	END_TEST();

	BEGIN_TEST PRE_CALL_VOID(more,void);
	CALLBACK();
	END_TEST();

	BEGIN_TEST PRE_CALL_VOID(little_more, int);
	WITHOUT_RETV CALLBACK(2);
	END_TEST();

	BEGIN_TEST PRE_CALL_VOID(little_more_ov, int, int);
	CALLBACK(1, 2);
	END_TEST();

	BEGIN_TEST PRE_CALL_VOID(little_more_ov, bool);
	CALLBACK(true);
	END_TEST();

	END_MODULE_TEST();
}