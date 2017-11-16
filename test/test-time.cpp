#include <sstream>
#include "test.h"
#include "time_utils.h"

using namespace erebos;

int main(int argc, char const *argv[]) {

	NEW_MODULE_TEST("time");
	
	BEGIN_TEST PRE_CALL(erebos::get_localtime);

	WITH_RETV CALLBACK();
	CUSTOM_TEST_DISEQUALS(retv.year,0);
	CUSTOM_TEST_DISEQUALS(retv.month,0);
	CUSTOM_TEST_DISEQUALS(retv.day,0);
	CUSTOM_TEST_DISEQUALS(retv.hour,0);
	CUSTOM_TEST_DISEQUALS(retv.min,0);
	CUSTOM_TEST_DISEQUALS(retv.sec,0);
	
	std::stringstream expected;
	expected << retv.year << "/" << retv.month << "/"
		<< retv.day << " @ " << retv.hour << ":" << retv.min
		<< ":" << retv.sec;

	CUSTOM_TEST_EQUALS(retv.to_string("YY/MM/DD @ hh:mm:ss"), expected.str());

	Time t = Time();

	CUSTOM_TEST_EQUALS(t.year,0);
	CUSTOM_TEST_EQUALS(t.month,0);
	CUSTOM_TEST_EQUALS(t.day,0);
	CUSTOM_TEST_EQUALS(t.hour,0);
	CUSTOM_TEST_EQUALS(t.min,0);
	CUSTOM_TEST_EQUALS(t.sec,0);

	const std::time_t time_now = std::time(nullptr);
#ifndef _COMPILER_MSVC
	std::tm now;
	localtime_r(&time_now, &now);
	t = Time(&now);
#else
	std::tm* now = nullptr;
	localtime_s(now, &time_now);
	t = Time(now);
#endif
	END_TEST();

	END_MODULE_TEST();

	return 0;
}
