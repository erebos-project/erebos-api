#include "platform_defs.h"
#include "time.h"


erebos::Time::Time(std::tm *right_now) {

	if (right_now) {
		year = right_now->tm_year + 1900;
		month = right_now->tm_mon + 1;
		day = right_now->tm_mday;
		hour = right_now->tm_hour;
		min = right_now->tm_min;
		sec = right_now->tm_sec;
	} else {
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		min = 0;
		sec = 0;
	}
}

erebos::Time erebos::get_localtime() {

	std::time_t time_now = std::time(nullptr);
	std::tm* now;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	now = std::localtime(&time_now);

#elif defined(_COMPILER_MSVC)
	now = nullptr;
	localtime_s(now, &time_now);

#endif

	return erebos::Time(now);
}
