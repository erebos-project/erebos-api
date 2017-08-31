/*!
 * @file time_utils.h
 * @brief time utilities
 */
#ifndef EREBOS_TIME_UTILS_H
#define EREBOS_TIME_UTILS_H

#include <string>
#include <ctime>
#include "platform_defs.h"

namespace erebos {

	/*!
	 * @brief contains year, month, day, hour, min, sec, refer to the constructor
	 */
	struct Time {
	public:
		int year;
		int month;
		int day;
		int hour;
		int min;
		int sec;

		/*!
		 * @param right_now : tm structure
		 * @brief parses right_now and then sets fields.
		 * If nullptr, fields are initialized to 0
		 */
		ERAPI explicit Time(std::tm *right_now);

		/*!
		 * @param format : A format string like: "YY/MM/DD @ hh:mm:ss"
		 * @return new string containing formatted string
		 * @brief formats are:
		 *   - YY year
		 *   - MM month
		 *   - DD day
		 *   - hh hour
		 *   - mm minute
		 *   - ss second
		 */
		ERAPI std::string to_string(std::string format) const;

	};

	/*!
	 * @brief new Time-ready structure with current time
	 * @return Time structure with current time values
	 */
	ERAPI Time get_localtime();

}

#endif