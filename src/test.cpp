#include "framework.h"
#include "test.h"

#ifndef TEST_SELECT_MISC
#define TEST_SELECT_MISC 1
#endif

#ifndef TEST_SELECT_FILE
#define TEST_SELECT_FILE 1
#endif

#ifndef TEST_SELECT_PROC
#define TEST_SELECT_PROC 1
#endif

#ifndef TEST_SELECT_STRUTIL
#define TEST_SELECT_STRUTIL 1
#endif

#ifndef TEST_SELECT_INPUT
#define TEST_SELECT_INPUT 1
#endif

#ifndef TEST_SELECT_CLASSES
#define TEST_SELECT_CLASSES 1
#endif


using namespace erebos;

int main(int argc, char const *argv[]) {

	// This program tests the library functions
	// You can customize the execution by defining TEST_SELECT_* macros


	// HOW-TO

	/*
	TEST_START("function_name"); // Start testing a function
	#define FUNCNAME function_name

		TEST_EXEC_INT(param1, param2, param3); // INT is the return type (can be integer or string)
		TEST_CHECK_EQUAL_INT(10); // Check if the function returned 10

	TEST_END(); // End testing
	*/


	TEST_CONFIG();


	#if TEST_SELECT_MISC == 1


	TEST_START("hex_to_int");
	#define FUNCNAME hex_to_int

		TEST_EXEC_INT("FF");
		TEST_CHECK_EQUAL_INT(255);

		TEST_EXEC_INT("00");
		TEST_CHECK_EQUAL_INT(0);

		TEST_EXEC_INT("");
		TEST_CHECK_EQUAL_INT(0);

		TEST_EXEC_INT("FFFF");
		TEST_CHECK_EQUAL_INT(65535);

		TEST_EXEC_INT("DEDE");
		TEST_CHECK_EQUAL_INT(57054);

	TEST_END();


	TEST_START("byte_to_hex(unsigned char)");
	#define FUNCNAME byte_to_hex

		TEST_EXEC_STR((unsigned char) 255);
		TEST_CHECK_EQUAL_STR("ff");

		TEST_EXEC_STR((unsigned char) 0);
		TEST_CHECK_EQUAL_STR("00");

		TEST_EXEC_STR((unsigned char) 42);
		TEST_CHECK_EQUAL_STR("2a");

	TEST_END();


	TEST_START("byte_to_hex(unsigned char*, unsigned int)");

		unsigned char array[2] = {255, 255};

		TEST_EXEC_STR(array, 2);
		TEST_CHECK_EQUAL_STR("ffff");

		array[0] = 0;
		array[1] = 0;

		TEST_EXEC_STR(array, 2);
		TEST_CHECK_EQUAL_STR("0000");

	TEST_END();


	TEST_START("byte_to_hex(T)");

		int i = 0xffffffff;

		TEST_EXEC_STR(i);
		TEST_CHECK_EQUAL_STR("ffffffff");

		i = 0;

		TEST_EXEC_STR(i);
		TEST_CHECK_EQUAL_STR("00000000");

		i = 3735928559;

		TEST_EXEC_STR(i);
		TEST_CHECK_EQUAL_STR("efbeadde");

	TEST_END();


	TEST_START("var_to_string");
	#define FUNCNAME var_to_string

		TEST_EXEC_STR(10);
		TEST_CHECK_EQUAL_STR("10");

		TEST_EXEC_STR("");
		TEST_CHECK_EQUAL_STR("");

		TEST_EXEC_STR(10.1f);
		TEST_CHECK_EQUAL_STR("10.1");

	TEST_END();


	#endif

	std::cin.get();

	return final_res;
}

