#include "test.h"
#include "../src/stringutils.h"

int main()
{
	NEW_MODULE_TEST("stringutils");

	//chomp test
	BEGIN_TEST PRE_CALL(erebos::strutil::chomp);

	std::string lol { "lol\n" };
	WITH_RETV CALLBACK(lol);
	TEST_EQUALS(true);

	END_TEST();

	//is_literal test
	BEGIN_TEST PRE_CALL_OVERLOAD(erebos::strutil::is_literal,bool,const char&);

	WITH_RETV CALLBACK('a');
	TEST_EQUALS(true);

	WITH_RETV CALLBACK('A');
	TEST_EQUALS(true);

	WITH_RETV CALLBACK('0');
	TEST_EQUALS(false);

	END_TEST();

	//is_numeral test
	BEGIN_TEST PRE_CALL_OVERLOAD(erebos::strutil::is_numeral,bool,const char&);

	WITH_RETV CALLBACK('a');
	TEST_EQUALS(false);

	WITH_RETV CALLBACK('A');
	TEST_EQUALS(false);

	WITH_RETV CALLBACK('0');
	TEST_EQUALS(true);

	END_TEST();

	//is_quote test
	BEGIN_TEST PRE_CALL(erebos::strutil::is_quotes);

	WITH_RETV CALLBACK('\'');
	TEST_EQUALS(true);

	WITH_RETV CALLBACK('\"');
	TEST_EQUALS(true);

	WITH_RETV CALLBACK('a');
	TEST_EQUALS(false);

	END_TEST();

	//is_literal string overload test
	BEGIN_TEST PRE_CALL_OVERLOAD(erebos::strutil::is_literal,bool, const std::string&);

	WITH_RETV CALLBACK("eREbostest");
	TEST_EQUALS(true);

	WITH_RETV CALLBACK("3r3b0st3st");
	TEST_EQUALS(false);

	END_TEST();

	//is_numeral string overload test
	BEGIN_TEST PRE_CALL_OVERLOAD(erebos::strutil::is_numeral,bool, const std::string&);

	WITH_RETV CALLBACK("0123456789");
	TEST_EQUALS(true);

	WITH_RETV CALLBACK("3r3b0st3st");
	TEST_EQUALS(false);

	END_TEST();

#if defined(LINUX)
	BEGIN_TEST PRE_CALL(erebos::strutil::stderr_to_stdout);

	WITH_RETV CALLBACK("command_test");
	TEST_EQUALS("command_test 2>&1");

	END_TEST();
#endif

	//split test
	BEGIN_TEST PRE_CALL_VOID(erebos::strutil::split,const std::string&, const char&, std::vector<std::string>&);

	std::vector<std::string> test_out;
	CALLBACK("string1 string2",' ', test_out);

	RUN_CUSTOM_TEST();
	CUSTOM_TEST_EQUALS("string1",test_out.at(0));
	CUSTOM_TEST_EQUALS("string2",test_out.at(1));

	CALLBACK("string1_string2",'_',test_out);

	RUN_CUSTOM_TEST();
	CUSTOM_TEST_EQUALS("string1",test_out.at(0));
	CUSTOM_TEST_EQUALS("string2",test_out.at(1));

	END_TEST();

	//index_of overloads
	BEGIN_TEST PRE_CALL_OVERLOAD(erebos::strutil::index_of,
			erebos::strutil::ssize,
			const char*,const char&);

	char arr[5] = { 'a','b','c','d' };

	WITH_RETV CALLBACK(arr,'b');
	TEST_EQUALS(1);

	WITH_RETV CALLBACK(arr,'d');
	TEST_EQUALS(3);

	WITH_RETV CALLBACK(arr,'e');
	TEST_EQUALS(-1);

	END_TEST();

	//index_of with specified length
	BEGIN_TEST PRE_CALL_OVERLOAD(erebos::strutil::index_of,
			erebos::strutil::ssize,
			const char*, const char&, const erebos::strutil::ssize&);

	char arr[] = { 'a','b','c','d' };

	WITH_RETV CALLBACK(arr,'b', 4);
	TEST_EQUALS(1);

	WITH_RETV CALLBACK(arr,'d', 4);
	TEST_EQUALS(3);

	WITH_RETV CALLBACK(arr,'e', 4);
	TEST_EQUALS(-1);

	END_TEST();

	//replace
	BEGIN_TEST PRE_CALL_VOID(erebos::strutil::replace,
								std::string&, const std::string&,
								const std::string&, const size_t&);
	std::string str = "Szechuan sauce";
	WITHOUT_RETV CALLBACK(str, " sauce", "", 1);
	CUSTOM_TEST_EQUALS(str, "Szechuan");

	str = "AaAaAa";
	WITHOUT_RETV CALLBACK(str, "A", "B", 2);
	CUSTOM_TEST_EQUALS(str, "BaBaAa");

	WITHOUT_RETV CALLBACK(str, "B", "A", 0);
	CUSTOM_TEST_EQUALS(str,"AaAaAa");

	END_TEST();

	BEGIN_TEST PRE_CALL_VOID(erebos::strutil::replace,
								std::string&, const char&,
								const char&, const size_t&);

	std::string str = "replace MeM";

	WITHOUT_RETV CALLBACK(str, 'M',' ',0);
	CUSTOM_TEST_EQUALS(str,"replace  e ");

	str = "replace AeA";
	WITHOUT_RETV CALLBACK(str, 'A','m',1);
	CUSTOM_TEST_EQUALS(str,"replace meA");


	str = "replace AeA";
	WITHOUT_RETV CALLBACK(str,'A','m',2);
	CUSTOM_TEST_EQUALS(str,"replace mem");

	END_TEST();

	//remaining
	//
	//cut
	//mul
	//encode_base64_*
	//decode_base64_*
	

	END_MODULE_TEST();
}

