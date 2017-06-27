#ifndef EREBOS_TIME_H
#define EREBOS_TIME_H

#include <ctime>

namespace erebos {

	namespace time {

		struct Time {
		public:
			explicit Time(std::tm* right_now);

			size_t year;
			size_t month;
			size_t day;
			size_t hour;
			size_t min;
			size_t sec;
		};

		Time get_localtime();
	}
}

#endif
