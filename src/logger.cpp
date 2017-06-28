#include <fstream>
#include <sstream>
#include <cstring>
#include <errno.h>

#include "logger.h"
#include "time.h"
#include "native.h"
#include "framework.h"
#include "stringutils.h"

static bool is_file = false;
static std::ostream* stream = nullptr;
static std::ofstream* file_stream = nullptr;
static std::string format_string = "hh:mm:ss";

void erebos::logger::set_stream(std::ostream& new_stream) {
	if (stream)
		stream->flush();

	stream = &new_stream;
	is_file = false;
	if(file_stream)
		file_stream->close();
}

void erebos::logger::set_stream(std::string filename) {

	if (stream)
		stream->flush();
	stream = nullptr;
	is_file = true;

	file_stream = new std::ofstream();
	file_stream->open(filename, std::ofstream::out | std::ofstream::app);
}

void erebos::logger::reset_stream() {

	if (stream)
		stream->flush();
	if(file_stream)
		file_stream->close();

	stream = nullptr;
	file_stream = nullptr;
	is_file = false;
}

bool erebos::logger::log(const std::string& message, const log_level level, const log_type& type) {

	if(!stream && !file_stream)
		return false;

	std::stringstream full_log;

	if (level == log_level::LOG_ERROR)
		full_log << "[ERROR] ";
	else if (level == log_level::LOG_INFO)
		full_log << "[INFO] ";
	else if (level == log_level::LOG_WARNING)
		full_log << "[WARNING] ";

	if (type == log_type::LOG_TYPE_ERROR_NUMBER)
		full_log << " - Errno: " << errno;
	else if (type == log_type::LOG_TYPE_ERROR_STRING)
		full_log << " - Error: " << string_from_errno(errno);
	else if (type == log_type::LOG_TYPE_ERROR_STRNUM)
		full_log << " - Error: " << string_from_errno(errno) << " (errno:" << errno <<  ")";

	Time now = get_localtime();
	std::string time_string = format_string;

	strutil::replace(time_string, "yy", var_to_string(now.year));
	strutil::replace(time_string, "mm", var_to_string(now.month));
	strutil::replace(time_string, "dd", var_to_string(now.day));
	strutil::replace(time_string, "hh", var_to_string(now.hour));
	strutil::replace(time_string, "mm", var_to_string(now.min));
	strutil::replace(time_string, "ss", var_to_string(now.sec));

	full_log << time_string << " " << message << '\n';

	const std::string log_string = full_log.str();

	if(!is_file)
		stream->write(log_string.c_str(), log_string.size());
	else {
		file_stream->write(log_string.c_str(), log_string.size());
		file_stream->flush();
	}

	return true;
}


void erebos::logger::set_format(std::string format) {

	format_string = format;
}


