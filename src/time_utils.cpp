#include "platform_defs.h"
#include "time_utils.h"
#include "stringutils.h"
#include "misc.h"


erebos::etime::etime(std::tm *right_now) :
		year(0), month(0), day(0),
		hour(0), min(0), sec(0) {

	if (right_now) {
		year = right_now->tm_year + 1900;
		month = right_now->tm_mon + 1;
		day = right_now->tm_mday;
		hour = right_now->tm_hour;
		min = right_now->tm_min;
		sec = right_now->tm_sec;
	}
}

std::string erebos::etime::to_string(std::string format) const {
    strutil::replace(format, "YY", std::to_string(year));
    strutil::replace(format, "MM", std::to_string(month));
    strutil::replace(format, "DD", std::to_string(day));
    strutil::replace(format, "hh", std::to_string(hour));
    strutil::replace(format, "mm", std::to_string(min));
    strutil::replace(format, "ss", std::to_string(sec));

	return format;
}

erebos::etime erebos::get_localtime() {

	const std::time_t time_now = std::time(nullptr);

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)

#ifdef WINDOWS
    return erebos::etime(localtime(&time_now));
#else
	std::tm now;
	localtime_r(&time_now, &now);
    return erebos::etime(&now);
#endif

#elif defined(_COMPILER_MSVC)
	std::tm now;
	localtime_s(&now, &time_now);
    return erebos::etime(&now);
#else
    return erebos::etime();
#endif
}
