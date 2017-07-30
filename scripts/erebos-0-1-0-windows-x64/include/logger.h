/*!
 * @file logger.h
 * @brief logging facilities
 */
#ifndef EREBOS_LOGGER_H
#define EREBOS_LOGGER_H

#include <ostream>

namespace erebos {

	/*!
	 * @brief event logging utilities
	 */
	namespace logger {

		/*!
		 * @brief how many information the log should bring?
		 * constants are self-explainatory
		 */
		enum class log_type {
			LOG_TYPE_NORMAL,
			LOG_TYPE_ERROR_STRING,
			LOG_TYPE_ERROR_NUMBER,
			LOG_TYPE_ERROR_STRNUM
		};

		/*!
		 * @brief which type of event is this?
		 * constants are self-explainatory
		 */
		enum class log_level {
			LOG_INFO,
			LOG_ERROR,
			LOG_WARNING
		};

		/*!
		 * @param stream : an std::ostream based class
		 * (in most cases std::cout or std::cerr)
		 * @brief this overload should not be used with files (ofstream)
		 */
		void set_stream(std::ostream &stream);

		/*!
		 * @brief this overload enable logging to file!
		 * @param filename : file name string
		 */
		void set_stream(const std::string &filename);

		/*!
		 * @brief reset the stream, log() will fail and return false
		 */
		void reset_stream();

		/*!
		 * @brief change logging data format
		 * @param format : Time format (refer to erebos::Time struct)
		 */
		void set_data_format(const std::string &format);

		/*!
		 * @brief logging facility function
		 * @param message
		 * @param level : event type (refer to erebos::logger::log_level enum)
		 * @param type : logging informatios (default = LOG_TYPE_NORMAL)(refer to erebos::logger::log_type enum)
		 * @return fails ONLY if stream not set
		 */
		bool log(const std::string &message,
				 const log_level &level,
				 const log_type &type = log_type::LOG_TYPE_NORMAL);

	}
}

#endif //LOGGER_H
