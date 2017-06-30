/*!
 * @headerfile logger.h
 * @brief logging facilities
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>

namespace erebos {

	/*!
	 * @namespace erebos::logger
	 * @brief event logging utilities
	 */
	namespace logger {

		/*!
		 * @enum erebos::logger::log_type
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
		 * @enum erebos::logger::log_level
		 * @brief which type of event is this?
		 * constants are self-explainatory
		 */
		enum class log_level {
			LOG_INFO,
			LOG_ERROR,
			LOG_WARNING
		};

		/*!
		 * @fn erebos::logger::set_stream(std::ostream&)
		 * @param stream : an std::ostream based class
		 * (in most cases std::cout or std::cerr)
		 * !! DO NOT USE THIS OVERLOAD WITH FILES !!
		 */
		void set_stream(std::ostream& stream);
		/*!
		 * @fn erebos::logger::set_stream(const std::string&)
		 * @param filename : file name string
		 */
		void set_stream(const std::string& filename);
		/*!
		 * @fn erebos::logger::reset_stream()
		 * @brief reset the stream, log() will fail and return false
		 */
		void reset_stream();
		/*!
		 * @fn erebos::logger::set_data_format(const std::string&)
		 * @param format : Time format (refer to erebos::Time struct)
		 * @refitem erebos::Time
		 */
		void set_data_format(const std::string& format);

		/*!
		 * @fn erebos::logger::log(const std::string&, const log_level&, const log_type&)
		 * @param message
		 * @param level : event type (refer to erebos::logger::log_level enum)
		 * @param type : logging informatios (default = LOG_TYPE_NORMAL)(refer to erebos::logger::log_type enum)
		 * @return fails ONLY if stream not set
		 */
		bool log(const std::string& message,
				 const log_level& level,
				 const log_type& type = log_type::LOG_TYPE_NORMAL);

	}
}

#endif //LOGGER_H
