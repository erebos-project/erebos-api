#include "test.h"
#include "framework.h"
#include "input.h"

using namespace erebos;

int main(int argc, char const *argv[]) {

	// The functions in the input namespace must be manually tested

	NEW_MODULE_TEST("input");

#ifdef WINDOWS

	BEGIN_TEST PRE_CALL(input::get_key);
		// Empty test
	END_TEST();

	BEGIN_TEST PRE_CALL(input::fake_put);
		// Empty test
	END_TEST();

#elif defined(LINUX)

	BEGIN_TEST PRE_CALL(input::getev_physical_keyboard);
		// Empty test
	END_TEST();

	BEGIN_TEST PRE_CALL(input::get_key);
		// Empty test
	END_TEST();

	BEGIN_TEST PRE_CALL_OVERLOAD(input::fake_put, bool, const int&, const Key&, const KeyPressType&);
		// Empty test
	END_TEST();

	BEGIN_TEST PRE_CALL_OVERLOAD(input::fake_put, bool, const int&, const Key&);
		// Empty test
	END_TEST();

	BEGIN_TEST PRE_CALL(input::destroy_virtual_kb_device);
		// Empty test
	END_TEST();

#endif

	END_MODULE_TEST();

	return 0;
}
