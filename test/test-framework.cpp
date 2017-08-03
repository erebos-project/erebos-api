#include "test.h"
#include "framework.h"

int main(int argc, char const *argv[]) {

	NEW_MODULE_TEST("framework");


	BEGIN_TEST PRE_CALL(hex_to_int);

		WITH_RETV CALLBACK("FF");
		TEST_EQUALS(255);

		WITH_RETV CALLBACK("00");
		TEST_EQUALS(0);

		WITH_RETV CALLBACK("");
		TEST_EQUALS(0);

		WITH_RETV CALLBACK("FFFF");
		TEST_EQUALS(65535);

		WITH_RETV CALLBACK("DEDE");
		TEST_EQUALS(57053);

	END_TEST();


	BEGIN_TEST PRE_CALL_OVERLOAD(byte_to_hex, std::string, unsigned char);

		WITH_RETV CALLBACK(255);
		TEST_EQUALS("ff");

		WITH_RETV CALLBACK(0);
		TEST_EQUALS("00");

		WITH_RETV CALLBACK(42);
		TEST_EQUALS("2a");

	END_TEST();


	BEGIN_TEST PRE_CALL_OVERLOAD(byte_to_hex, std::string, unsigned char* array, unsigned int size);

		unsigned char array[2] = {255, 255};

		WITH_RETV CALLBACK(array, 2);
		TEST_EQUALS("ffff");

		array[0] = 0; array[1] = 0;
		TEST_EQUALS("0000");

	END_TEST();


	BEGIN_TEST PRE_CALL_OVERLOAD(byte_to_hex, std::string, int);

		int i = 0xffffffff;
		WITH_RETV CALLBACK(i);
		TEST_EQUALS("ffffffff");

		i = 0;
		WITH_RETV CALLBACK(i);
		TEST_EQUALS(00000000);

		i = 3735928559;
		WITH_RETV CALLBACK(i);
		TEST_EQUALS("efbeadde");

	END_TEST();


	BEGIN_TEST PRE_CALL(var_to_string);

		WITH_RETV CALLBACK(10);
		TEST_EQUALS("10");

		WITH_RETV CALLBACK("");
		TEST_EQUALS("");

		WITH_RETV CALLBACK(10.1f);
		TEST_EQUALS("10.1");

	END_TEST();


	BEGIN_TEST PRE_CALL(to_unix_slash);

		WITH_RETV CALLBACK("");
		TEST_EQUALS("");

		WITH_RETV CALLBACK("my\\path");
		TEST_EQUALS("my/path");

		WITH_RETV CALLBACK("\\\\");
		TEST_EQUALS("//");

		WITH_RETV CALLBACK("my\\path\\is\\really\\long");
		TEST_EQUALS("my/path/is/really/long");

		WITH_RETV CALLBACK("nothing here");
		TEST_EQUALS("nothing here");

	END_TEST();


	BEGIN_TEST PRE_CALL(parse_quotes);

		WITH_RETV CALLBACK("");
		TEST_EQUALS("");

		WITH_RETV CALLBACK("\"my quoted string\"");
		TEST_EQUALS("my quoted string");

		WITH_RETV CALLBACK("no quotes here");
		TEST_EQUALS("no quotes here");

		WITH_RETV CALLBACK("\"some quotes\" \"some other quotes\"");
		TEST_EQUALS("some quotes");

	TEST_END();


	BEGIN_TEST PRE_CALL(parse_arg);

		std::vector<std::string> res;

		WITHOUT_RETV CALLBACK("Param1 Param2 \"Param 3\" ", res);

		// TEST_CHECK_EQUAL(res[0], "Param1");
		// TEST_CHECK_EQUAL(res[1], "Param2");
		// TEST_CHECK_EQUAL(res[2], "Param 3");

		std::vector<std::string> res_2;

		WITHOUT_RETV CALLBACK("", res_2);
		// TEST_CHECK_EQUAL(res_2.size(), 0);

	TEST_END();


	BEGIN_TEST PRE_CALL(cmd, int, std::string, int*);

		// Special case

	TEST_END();


	BEGIN_TEST PRE_CALL(cmd, int, std::string, std::string&, int*);

		// Special case

	TEST_END();


	BEGIN_TEST PRE_CALL(get_random_secure);

		// Special case, this functions must not return 0

	TEST_END();


	END_MODULE_TEST();

	return 0;
}

