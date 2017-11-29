#include "test.h"
#include "file.h"
#include "native.h"

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

	END_TEST();

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
	
	BEGIN_TEST PRE_CALL(file::write_bin);

		WITH_RETV CALLBACK("testbinary.bin", "test", 0, false);
		TEST_EQUALS(4);

		WITH_RETV CALLBACK("testbinary.bin", "testaa", 6, false);
		TEST_EQUALS(6);

		WITH_RETV CALLBACK("testbinary.bin", "testaa", 5, false);
		TEST_EQUALS(5);

		WITH_RETV CALLBACK("testbinary.bin", "test\0aa", 7, false);
		TEST_EQUALS(7);

		WITH_RETV CALLBACK("testbinary.bin", "test\0aa",0, false);
		TEST_EQUALS(4);

		WITH_RETV CALLBACK("testbinary.bin", "test\0aab", 8, true);
		TEST_EQUALS(8);

		WITH_RETV CALLBACK("testbinary-empty.bin","",0, false);
		TEST_EQUALS(0);

	END_TEST();

	BEGIN_TEST PRE_CALL(file::read_bin);

	{
		WITH_RETV CALLBACK("testbinary.bin", nullptr);
		CUSTOM_TEST_EQUALS(retv.operator bool(), true);
	}

	{
		std::size_t bytes;
		WITH_RETV CALLBACK("testbinary.bin", &bytes);
		CUSTOM_TEST_EQUALS(retv.operator bool(), true);
		CUSTOM_TEST_EQUALS(bytes, 8);
	}

	{
		WITH_RETV CALLBACK("this-file-does-not-exist", nullptr);
		CUSTOM_TEST_EQUALS(retv.operator bool(), false);
	}
	{
		std::size_t bytes;
		WITH_RETV CALLBACK("testbinary-empty.bin", &bytes);
		CUSTOM_TEST_EQUALS(retv.operator bool(), true);
		CUSTOM_TEST_EQUALS(bytes, 0);
	}
	END_TEST();

	BEGIN_TEST PRE_CALL(file::remove);

		WITH_RETV CALLBACK("testbinary.bin");
		TEST_EQUALS(true);

		WITH_RETV CALLBACK("testbinary-empty.bin");
		TEST_EQUALS(true);

		WITH_RETV CALLBACK("non-existant-file.test");
		TEST_EQUALS(false);

	END_TEST();
	
	END_MODULE_TEST();

	return 0;
}
