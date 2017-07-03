/*!
 * @file time.h
 * @brief time utilities
 */
#ifndef EREBOS_TIME_H
#define EREBOS_TIME_H

#include <string>
#include <ctime>

namespace erebos {

    /*!
     * @brief contains year,month,day,hour,min,sec, refer to the constructor
     */
    struct Time {
    public:
        /*!
         * @param right_now : tm structure
         * @brief parses right_now and then sets fields.
         * If nullptr, fields are initialized to 0
         */
        explicit Time(std::tm *right_now);

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
        std::string to_string(std::string format) const;

        int year;
        int month;
        int day;
        int hour;
        int min;
        int sec;
    };

    /*!
     * @brief new Time-ready structure with current time
     * @return Time structure with current time values
     */
    Time get_localtime();

}

#endif
