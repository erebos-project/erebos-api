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
		for(int i = 0; i < index; ++i)
			buff += s[i];
		return buff;
	}
	return "";
}


std::string erebos::file::get_extension(std::string filename) {
	size_t index = 0;

	for (int i = 0; i < filename.size(); ++i)
		if(filename[i] == '.') index = i;

	return strutil::cut(filename, index + 1, filename.size() - index - 1);
}


std::string erebos::file::get_name(std::string s) {
	size_t index = 0;

	s = to_unix_slash(s);

	for (int i = 0; i < s.size(); ++i)
		if(s[i] == '/') index = i;

	if(index)
		return strutil::cut(s, index + 1, s.size() - index);

	return s;
}

std::string erebos::file::get_basename(std::string filename) {

	filename = file::get_name(filename);

	int index = 0;
	for (int i = 0; i < filename.size(); ++i)
		if(filename[i] == '.')
			index = i;

	if(index)
		filename = strutil::cut(filename, 0, index);

	return filename;
}


bool erebos::file::get_exists(std::string filename) {
	FILE* file = fopen(filename.c_str(), "r");
	if (file) {
		fclose(file);
		return true;
	} else
		return false;
}

std::string erebos::to_unix_slash(std::string s) {
	return strutil::replace(s, '\\', '/');
}


std::string erebos::file::read(std::string filename) {
	std::ifstream stream(filename);
	if(!stream.is_open()) return "";
	std::stringstream ss;
	ss << stream.rdbuf();
	return ss.str();
}


data_t erebos::file::read_bin(std::string filename, unsigned long long* bytecount) {

	data_t data;

	data.size = file::get_size(filename);
	data.data = new char[data.size];

	FILE* fd = fopen(filename.c_str(), "rb");

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


bool erebos::file::write(std::string filename, std::string data, bool truncate) {
	std::ofstream stream;
	if(truncate) stream.open(filename, std::ofstream::trunc);
	else stream.open(filename);
	if(!stream.is_open()) return false;
	stream << data;
	return true;
}


bool erebos::file::write_bin(std::string filename, data_t data, bool truncate) {

	std::string flags = "wb";

	if(truncate)
		flags += "+";

	FILE* fd = fopen(filename.c_str(), flags.c_str());
	if(!fd)
		return false;

	fwrite(data.data, 1, data.size, fd);
	fclose(fd);

	return true;
}


void erebos::cmd(const std::string& command) {
	system(command.c_str());
}


void erebos::term_clear() {
#ifdef LINUX
	cmd("clear");
#else
	cmd("cls");
#endif
}


bool erebos::file::remove(std::string filename) {

	return !std::remove(filename.c_str());
}


bool erebos::get_prompt_answer(std::string message, std::string error_message, bool exit_on_error) {
	print(message, " [Y/n]");
	char res;
	std::cin >> res;
	if(res == 'y' || res == 'Y')
		return true;
	else if(res == 'n' || res == 'N')
		return false;
	else {
		println(error_message);
		if(exit_on_error) exit(-10);
		return false;
	}
}


std::string erebos::parse_quotes(std::string s) {
	if(s[0] != '\"' && s[0] != '\'') return s;
	std::string res;
	const size_t size = s.size();
	for(int i = 1; i < size; ++i) {
		if(s[i] != '\"' && s[i] != '\'') res += s[i];
		else break;
	}
	return res;
}


void erebos::parse_arg(std::string input, std::vector<std::string>& output) {
	for (int i = 0; i < input.size(); ++i) {
		std::string curr;

		if(input[i] == '\n' && input[i] == '\0') break;

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

		output.push_back(curr);
	}
}

Time erebos::get_localtime() {

	time_t time_now = time(0);
	tm* now = localtime(&time_now);

	Time t;
	t.year = now->tm_year + 1900;
	t.month = now->tm_mon + 1;
	t.day = now->tm_mday;
	t.hour = now->tm_hour;
	t.min = now->tm_min;
	t.sec = now->tm_sec;

	return t;
}

