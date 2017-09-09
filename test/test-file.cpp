#include "test.h"
#include "framework.h"

using namespace erebos;

int main(int argc, char const *argv[]) {

	NEW_MODULE_TEST("file");


	BEGIN_TEST PRE_CALL(file::get_path);

		WITH_RETV CALLBACK("");
		TEST_EQUALS("");

		WITH_RETV CALLBACK("/dir/file.ext");
		TEST_EQUALS("/dir/");

		WITH_RETV CALLBACK("/h/file.ext");
		TEST_EQUALS("/h/");

		WITH_RETV CALLBACK("/file.ext");
		TEST_EQUALS("/");

	END_TEST();

	/* 
	BEGIN_TEST PRE_CALL(file::get_extension);

		WITH_RETV CALLBACK("");
		TEST_EQUALS("");

		WITH_RETV CALLBACK("/dir/file.ext");
		TEST_EQUALS("ext");

		WITH_RETV CALLBACK("file.ext");
		TEST_EQUALS("ext");

		WITH_RETV CALLBACK("/file.ext");
		TEST_EQUALS("ext");

		WITH_RETV CALLBACK("/file.ext1.ext2");
		TEST_EQUALS("ext2");

	END_TEST();*/

	BEGIN_TEST PRE_CALL(file::get_name);

		WITH_RETV CALLBACK("");
		TEST_EQUALS("");

		WITH_RETV CALLBACK("/dir/file.ext");
		TEST_EQUALS("file.ext");

		WITH_RETV CALLBACK("file.ext");
		TEST_EQUALS("file.ext");

		WITH_RETV CALLBACK("file.ext1.ext2");
		TEST_EQUALS("file.ext1.ext2");

		WITH_RETV CALLBACK("/file.ext");
		TEST_EQUALS("file.ext");

	END_TEST();


	BEGIN_TEST PRE_CALL(file::get_basename);

		WITH_RETV CALLBACK("");
		TEST_EQUALS("");

		WITH_RETV CALLBACK("/dir/file.ext");
		TEST_EQUALS("file");

		WITH_RETV CALLBACK("file.ext");
		TEST_EQUALS("file");

		WITH_RETV CALLBACK("file.ext1.ext2");
		TEST_EQUALS("file");

		WITH_RETV CALLBACK("/file.ext");
		TEST_EQUALS("file");

	END_TEST();


	BEGIN_TEST PRE_CALL(file::write);

		WITH_RETV CALLBACK("testfile.txt", "Test", false);
		TEST_EQUALS(true);

	END_TEST();


	BEGIN_TEST PRE_CALL(file::read);

		WITH_RETV CALLBACK("testfile.txt");
		TEST_EQUALS("Test");

	END_TEST();


	BEGIN_TEST PRE_CALL(file::get_exists);

		WITH_RETV CALLBACK("testfile.txt");
		TEST_EQUALS(true);

	END_TEST();


	BEGIN_TEST PRE_CALL(file::remove);

		WITH_RETV CALLBACK("testfile.txt");
		TEST_EQUALS(true);

	END_TEST();


	END_MODULE_TEST();

	return 0;
}
