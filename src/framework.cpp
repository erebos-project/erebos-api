#include <ctime>
#include <fstream>

#include "framework.h"

using namespace erebos;
using namespace strutil;

std::string erebos::get_exe_path() {
	return file::get_path(get_exe_path_());
}

// ::file

std::string erebos::file::get_path(std::string s) {
	size_t index = 0;
	s = to_unix_slash(s);
	const size_t size = s.size();

	for(size_t i = size - 1; i > 0; --i) {
		if(s[i] == '/') {
			index = i + 1;
			break;
		}
	}
	std::string buff;
	if(index) {
		for(size_t i = 0; i < index; ++i)
			buff += s[i];
		return buff;
	}
	return "";
}


std::string erebos::file::get_extension(const std::string& filename) {
	size_t index = 0;
	
	for (size_t i = 0; i < filename.size(); ++i)
		if(filename[i] == '.') index = i;

	return strutil::cut(filename, index + 1, filename.size() - index - 1);
}


std::string erebos::file::get_name(std::string s) {
	size_t index = 0;

	s = to_unix_slash(s);

	for (size_t i = 0; i < s.size(); ++i)
		if(s[i] == '/') index = i;

	if(index)
		return strutil::cut(s, index + 1, s.size() - index);

	return s;
}

std::string erebos::file::get_basename(std::string filename) {

	filename = file::get_name(filename);

	size_t index = 0;
	for (size_t i = 0; i < filename.size(); ++i)
		if(filename[i] == '.')
			index = i;

	if(index)
		filename = strutil::cut(filename, 0, index);

	return filename;
}


bool erebos::file::get_exists(const std::string& filename) {
	FILE* file = nullptr;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	fopen(filename.c_str(), "r");
#elif defined(_COMPILER_MSVC)
	errno_t err = fopen_s(&file, filename.c_str(), "r");
	if (err != 0)
		return false;
#endif

	if (file) {
		fclose(file);
		return true;
	} else
		return false;
}

std::string erebos::to_unix_slash(const std::string& s) {
	std::string from = s;
	strutil::replace(from, '\\', '/');
	return from;
}


std::string erebos::file::read(const std::string& filename) {
	std::ifstream stream(filename);

	if(!stream.is_open()) 
		return "";

	std::stringstream ss;
	ss << stream.rdbuf();

	return ss.str();
}


data_t erebos::file::read_bin(const std::string& filename, unsigned long long* bytecount) {
	data_t data;

	data.size = file::get_size(filename);
	data.data = new char[data.size];

	FILE* fd = nullptr;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	fopen(filename.c_str(), "rb");
#elif defined(_COMPILER_MSVC)
	errno_t err = fopen_s(&fd, filename.c_str(), "rb");
	if (err != 0)
		return data; //handle this situation
#endif

	if(!fd) {
		delete[] data.data;
		return data_t(nullptr, 0); // Return an empty data structure.
	}

	size_t res = fread(data.data, 1, data.size, fd);

	if(bytecount)
		*bytecount = res;

	fclose(fd);

	return data;
}


bool erebos::file::write(const std::string& filename, const std::string& data, bool truncate) {
	std::ofstream stream;
	if(truncate) stream.open(filename, std::ofstream::trunc);
	else stream.open(filename);
	if(!stream.is_open()) return false;
	stream << data;
	return true;
}


bool erebos::file::write_bin(const std::string& filename, const data_t& data, bool truncate) {

	std::string flags = "wb";

	if(truncate)
		flags += "+";

	FILE* fd = nullptr;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	fopen(filename.c_str(), flags.c_str());
#elif defined(_COMPILER_MSVC)
	errno_t err = fopen_s(&fd, filename.c_str(), flags.c_str());
	if (err != 0)
		return false;
#endif

	if(!fd)
		return false;

	fwrite(data.data, 1, data.size, fd);
	fclose(fd);

	return true;
}

//replacement
void erebos::cmd(const std::string& command) {
	system(command.c_str());
}

//replacement
void erebos::term_clear() {
#ifdef LINUX
	cmd("clear");
#else
	cmd("cls");
#endif
}


bool erebos::file::remove(const std::string& filename) {

	return !std::remove(filename.c_str());
}


bool erebos::get_prompt_answer(const std::string& message, const std::string& error_message, bool exit_on_error) {
	print(message, " [Y/n]");
	char res;
	std::cin >> res;
	if(res == 'y' || res == 'Y')
		return true;
	else if(res == 'n' || res == 'N')
		return false;
	else {
		println(error_message);
		if(exit_on_error) 
			exit(-10);
		return false;
	}
}


std::string erebos::parse_quotes(const std::string& s) {
	if(s[0] != '\"' && s[0] != '\'') return s;
	std::string res;
	const size_t size = s.size();
	for(size_t i = 1; i < size; ++i) {
		if(s[i] != '\"' && s[i] != '\'') 
			res += s[i];
		else 
			break;
	}
	return res;
}


void erebos::parse_arg(const std::string& input, std::vector<std::string>& output) {
	for (size_t i = 0; i < input.size(); ++i) {
		std::string curr;

		if(input[i] == '\n' && input[i] == '\0') 
			break;

		if(is_quotes(input[i])) {
			i++;
			while(!is_quotes(input[i]) && input[i] != '\n' && input[i] != '\0') {
				curr += input[i];
				i++;
			}
		} else {
			while(!is_quotes(input[i]) && input[i] != ' ' && input[i] != '\n' && input[i] != '\0') {
				curr += input[i];
				i++;
			}
		}

		output.emplace_back(curr);
	}
}

Time erebos::get_localtime() {
	std::time_t time_now = std::time(nullptr);
	std::tm* now = nullptr;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	now = localtime(&time_now);
#elif defined(_COMPILER_MSVC)
	localtime_s(now, &time_now);
#endif

	Time t;
	t.year = now->tm_year + 1900;
	t.month = now->tm_mon + 1;
	t.day = now->tm_mday;
	t.hour = now->tm_hour;
	t.min = now->tm_min;
	t.sec = now->tm_sec;

	return t;
}

