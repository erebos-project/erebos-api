#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>

namespace erebos {

	namespace logger {

		enum class log_type {
			LOG_TYPE_NORMAL,
			LOG_TYPE_ERROR_STRING,
			LOG_TYPE_ERROR_NUMBER,
			LOG_TYPE_ERROR_STRNUM
		};

		enum class log_level {
			LOG_INFO,
			LOG_ERROR,
			LOG_WARNING
		};

		void set_stream(std::ostream& stream);
		void set_stream(const std::string& filename);
		void reset_stream();
		void set_data_format(const std::string& format);

		bool log(const std::string& message,
				 const log_level& level,
				 const log_type& type = log_type::LOG_TYPE_NORMAL);

	}
}

#endif //LOGGER_H
