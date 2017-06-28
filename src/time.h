#ifndef EREBOS_TIME_H
#define EREBOS_TIME_H

#include <string>
#include <ctime>

namespace erebos {

		struct Time {
		public:
			explicit Time(std::tm* right_now);
			std::string to_string(std::string format) const;

			int year;
			int month;
			int day;
			int hour;
			int min;
			int sec;
		};

		Time get_localtime();

}

#endif
