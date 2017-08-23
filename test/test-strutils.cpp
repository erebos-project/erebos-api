#include "../src/stringutils.h"
#include "test.h"

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

	END_MODULE_TEST();
}

