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

		class Logger {
		public:
			static inline void set_stream(std::ostream& stream) {
				current_stream->flush();
				current_stream = &stream;
			}

			static void error(const std::string& message,
				const log_type& ty_log = log_type::LOG_TYPE_ERROR_STRNUM);

			static void warn(const std::string& message,
				const log_type& ty_log = log_type::LOG_TYPE_NORMAL);

			static void info(const std::string& message,
				const log_type& ty_log = log_type::LOG_TYPE_NORMAL);

		private:
			static std::ostream* current_stream;
		};
	}
}
#endif //LOGGER_H
