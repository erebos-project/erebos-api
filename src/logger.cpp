#include <fstream>
#include <sstream>
#include <cstring>
#include <errno.h>

#include "logger.h"
#include "time.h"
#include "native.h"

static bool is_file = false;
static char* filename = nullptr;
static std::ostream* stream = nullptr;

void erebos::logger::set_stream(std::ostream& new_stream) {
	if (stream)
		stream->flush();

	stream = &new_stream;
	is_file = false;
	if (filename) {
		delete[] filename;
		filename = nullptr;
	}
}

void erebos::logger::set_stream(const char* fname) {
	if (stream)
		stream->flush();

	stream = nullptr;
	is_file = true;
	if (filename) {
		delete[] filename;
		filename = nullptr;
	}

	const size_t fname_size = strlen(fname) + 1;

	filename = new char[fname_size];
	snprintf(filename, fname_size, "%s", fname);
}

void erebos::logger::set_stream()
{
	if (stream)
		stream->flush();

	stream = nullptr;
	is_file = false;

	if (filename) {
		delete[] filename;
		filename = nullptr;
	}
}

bool erebos::logger::logev(const std::string& message,
	const log_level level, const log_type& type) {

	if (!stream && !is_file)
		return false;
	else if (is_file && !filename)
		return false;

	std::stringstream full_log;
	if (level == log_level::LOG_ERROR)
		full_log << "[ERROR] ";
	else if (level == log_level::LOG_INFO)
		full_log << "[INFO] ";
	else if (level == log_level::LOG_WARNING)
		full_log << "[WARNING] ";

	erebos::time::Time now = erebos::time::get_localtime();
	full_log << now.year << "/" << now.month << "/"
		<< now.day << " " << now.hour << ":" << now.min << ":" << now.sec << " - "
		<< message;

	if (type == log_type::LOG_TYPE_ERROR_NUMBER)
		full_log << " - Errno: " << errno;
	else if (type == log_type::LOG_TYPE_ERROR_STRING)
		full_log << " - Error: " << string_from_errno(errno);
	else if (type == log_type::LOG_TYPE_ERROR_STRNUM)
		full_log << " - Error: " << string_from_errno(errno) << " (errno:" << errno <<  ")";

	full_log << '\n';

	const std::string& log_string = full_log.str();

	if(!is_file)
		stream->write(log_string.c_str(), log_string.size());
	else {
		std::ofstream file_stream;
		file_stream.open(filename, std::ofstream::out | std::ofstream::app);
		file_stream.write(log_string.c_str(), log_string.size());
		file_stream.close();
	}

	return true;
}