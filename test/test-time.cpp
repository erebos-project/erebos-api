#include <sstream>
#include "test.h"
#include "time_utils.h"

using namespace erebos;

int main(int argc, char const *argv[]) {

	NEW_MODULE_TEST("time");

	BEGIN_TEST PRE_CALL(erebos::get_localtime);

	//Unapplyable checks
	WITH_RETV CALLBACK();

	std::stringstream expected;
	expected << retv.year << "/" << retv.month << "/"
		<< retv.day << " @ " << retv.hour << ":" << retv.min
		<< ":" << retv.sec;

	CUSTOM_TEST_EQUALS(retv.to_string("YY/MM/DD @ hh:mm:ss"), expected.str());

    etime t;

	CUSTOM_TEST_EQUALS(t.year, 0);
	CUSTOM_TEST_EQUALS(t.month, 0);
	CUSTOM_TEST_EQUALS(t.day, 0);
	CUSTOM_TEST_EQUALS(t.hour, 0);
	CUSTOM_TEST_EQUALS(t.min, 0);
	CUSTOM_TEST_EQUALS(t.sec, 0);

	const std::time_t time_now = std::time(nullptr);
#ifndef _COMPILER_MSVC
	std::tm now;
	localtime_r(&time_now, &now);
    t = etime(&now);
#else
	std::tm now;
	localtime_s(&now, &time_now);
    t = etime(&now);
#endif

	END_TEST();

	END_MODULE_TEST();

	return 0;
}
