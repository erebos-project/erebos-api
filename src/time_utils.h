/*!
 * @file time_utils.h
 * @brief time utilities
 */
#ifndef EREBOS_TIME_UTILS_H
#define EREBOS_TIME_UTILS_H

#include "platform_defs.h"
#include <ctime>
#include <string>

namespace erebos {

/*!
 * @brief contains year, month, day, hour, min, sec, refer to the constructor
 */
struct etime {
		public:
			int year;
			int month;
			int day;
			int hour;
			int min;
			int sec;

			/*!
			 * @brief Creates empty Time instance
			 */
            ERAPI inline etime() : year(0), month(0), day(0), hour(0), min(0), sec(0) {}

			/*!
			 * @param right_now : tm structure
			 * @brief parses right_now and then sets fields.
			 * If nullptr, fields are initialized to 0
			 */
            ERAPI explicit etime(std::tm *right_now);

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
    ERAPI etime get_localtime();

} // namespace erebos

#endif
