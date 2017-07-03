#include <fstream>
#include <sstream>
#include <cstring>

#include "logger.h"
#include "time.h"
#include "native.h"

static bool is_file = false;
static std::ostream *stream = nullptr;
static std::string format_string = "hh:mm:ss";

void erebos::logger::set_stream(std::ostream &new_stream) {

    if (stream) {
        stream->flush();
        if (is_file) {
            std::ofstream *filestream = dynamic_cast<std::ofstream *>(stream);
            if (filestream) {
                if (filestream->is_open())
                    filestream->close();
                delete stream;
            }
        }
        stream = nullptr;
    }

    is_file = false;
    stream = &new_stream;
}

void erebos::logger::set_stream(const std::string &filename) {

    if (stream) {
        stream->flush();
        if (is_file) {
            std::ofstream *filestream = dynamic_cast<std::ofstream *>(stream);
            if (filestream) {
                if (filestream->is_open())
                    filestream->close();
                delete stream;
            }
        }
        stream = nullptr;
    }

    is_file = true;
    stream = new std::ofstream;
    dynamic_cast<std::ofstream *>(stream)->open(filename, std::ofstream::out | std::ofstream::app);
}

void erebos::logger::reset_stream() {

    if (stream) {
        stream->flush();
        if (is_file) {
            std::ofstream *filestream = dynamic_cast<std::ofstream *>(stream);
            if (filestream) {
                if (filestream->is_open())
                    filestream->close();
                delete stream;
            }
        }
        stream = nullptr;
    }

    is_file = false;
}

void erebos::logger::set_data_format(const std::string &format) {

    format_string = format;
}

bool erebos::logger::log(const std::string &message, const log_level &level, const log_type &type) {

    if (!stream)
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
        stream->write(log_string.c_str(), log_string.size());
    else {
        stream->write(log_string.c_str(), log_string.size());
        stream->flush();
    }

    return true;
}

