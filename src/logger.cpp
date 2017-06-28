#include <fstream>
#include <sstream>
#include <cstring>
#include <memory>
#include <errno.h>

#include "logger.h"
#include "time.h"
#include "native.h"

static bool is_file = false;
static std::unique_ptr<std::ostream> stream;
static std::string format_string = "hh:mm:ss";

void erebos::logger::set_stream(std::ostream& new_stream) {

	std::ostream* ost = stream.get();

	if (ost) {
		ost->flush();
		if (is_file) {
			std::ofstream* filestream = dynamic_cast<std::ofstream*>(stream.get());
			if (filestream->is_open())
				filestream->close();
		}
		stream.release();
	}

	is_file = false;
	stream = std::unique_ptr<std::ostream>(&new_stream);
}

void erebos::logger::set_stream(const std::string& filename) {

	std::ostream* ost = stream.get();
	if (ost) {
		ost->flush();
		if (is_file) {
			std::ofstream* filestream = dynamic_cast<std::ofstream*>(stream.get());
			if (filestream->is_open())
				filestream->close();
		}
		stream.release();
	}

	is_file = true;
	stream = std::unique_ptr<std::ostream>(new std::ofstream);
	dynamic_cast<std::ofstream*>(stream.get())->open(filename, std::ofstream::out | std::ofstream::app);
}

void erebos::logger::reset_stream() {

	std::ostream* ost = stream.get();

	if (ost) {
		ost->flush();
		if (is_file) {
			std::ofstream* filestream = dynamic_cast<std::ofstream*>(stream.get());
			if (filestream->is_open())
				filestream->close();
		}
		stream.release();
	}

	is_file = false;
}

void erebos::logger::set_data_format(const std::string& format) {

	format_string = format;
}

bool erebos::logger::log(const std::string& message, const log_level level, const log_type& type) {

	std::ostream* local_stream = stream.get();
	if (!local_stream)
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
		full_log << " - Error: " << string_from_errno(errno) << " (errno:" << errno << ")";

	full_log << get_localtime().to_string(format_string) << " " << message << '\n';

	const std::string log_string = full_log.str();

	if (!is_file)
		stream.get()->write(log_string.c_str(), log_string.size());
	else {
		std::ofstream* file_stream = dynamic_cast<std::ofstream*>(stream.get());
		file_stream->write(log_string.c_str(), log_string.size());
		file_stream->flush();
	}

	return true;
}

