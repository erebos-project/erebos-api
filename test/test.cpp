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


	TEST_START("to_unix_slash");
	#define FUNCNAME to_unix_slash

		TEST_EXEC_STR("");
		TEST_CHECK_EQUAL_STR("");

		TEST_EXEC_STR("my\\path");
		TEST_CHECK_EQUAL_STR("my/path");

		TEST_EXEC_STR("\\\\");
		TEST_CHECK_EQUAL_STR("//");

		TEST_EXEC_STR("my\\path\\is\\really\\long");
		TEST_CHECK_EQUAL_STR("my/path/is/really/long");

		TEST_EXEC_STR("nothing here");
		TEST_CHECK_EQUAL_STR("nothing here");

	TEST_END();


	TEST_START("parse_quotes");
	#define FUNCNAME parse_quotes

		TEST_EXEC_STR("");
		TEST_CHECK_EQUAL_STR("");

		TEST_EXEC_STR("\"my quoted string\"");
		TEST_CHECK_EQUAL_STR("my quoted string");

		TEST_EXEC_STR("no quotes here");
		TEST_CHECK_EQUAL_STR("no quotes here");

		TEST_EXEC_STR("\"some quotes\" \"some other quotes\"");
		TEST_CHECK_EQUAL_STR("some quotes");

	TEST_END();

	TEST_START("parse_arg");
	#define FUNCNAME parse_arg

	std::vector<std::string> res;

	TEST_EXEC("Param1 Param2 \"Param 3\" ", res);

	TEST_CHECK_EQUAL(res[0], "Param1");
	TEST_CHECK_EQUAL(res[1], "Param2");
	TEST_CHECK_EQUAL(res[2], "Param 3");

	std::vector<std::string> res_2;

	TEST_EXEC("", res_2);
	TEST_CHECK_EQUAL(res_2.size(), 0);


	TEST_END();


	TEST_START("cmd(std::string, int*)");
	#define FUNCNAME cmd

		int exitvalue;

		TEST_EXEC_INT("echo Test Echo", &exitvalue);
		TEST_CHECK_EQUAL(exitvalue, 0);
		TEST_CHECK_EQUAL_INT(0);

		TEST_EXEC_INT("");
		TEST_CHECK_EQUAL_INT(0);

	TEST_END();


	TEST_START("cmd(std::string, std::string&, int*)");

		int exitvalue;
		std::string output;

		TEST_EXEC_INT("echo Test Echo", output, &exitvalue);
		TEST_CHECK_EQUAL(exitvalue, 0);
		TEST_CHECK_EQUAL(output, "Test Echo");
		TEST_CHECK_EQUAL_INT(0);

		TEST_EXEC_INT("");
		TEST_CHECK_EQUAL_INT(0);

	TEST_END();

	TEST_START("get_random_secure");
	#define FUNCNAME get_random_secure

		TEST_EXEC_INT();
		if(int_res == 0)
			TEST_ERROR();

	TEST_END();



	#endif

	std::cin.get();

	return final_res;
}

