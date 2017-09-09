#include <fstream>

#include "file.h"
#include "stringutils.h"
#include "framework.h"

std::string erebos::file::get_path(std::string s) {
	size_t index = 0;
	s = to_unix_slash(s);
	const size_t size = s.size();
	bool set = false;

	if(!size)
		return "";

	for (size_t i = size - 1; i >= 0; --i) {
		if (s[i] == '/') {
			index = i + 1;
			set = true;
			break;
		}
	}

	if (set)
		return strutil::cut(s, 0, index ? index : 1);

	return "";
}


std::string erebos::file::get_extension(const std::string &filename) {
	size_t index = 0;
	const size_t size = filename.size();
	bool set = false;

	if(!size)
		return "";

	for (size_t i = 0; i < size; ++i) {
		if (filename[i] == '.') {
			index = i;
			set = true;
		}
	}

	if (set)
		return strutil::cut(filename, index + 1, size - index - 1);

	return "";
}


std::string erebos::file::get_name(std::string s) {
	size_t index = 0;

	s = to_unix_slash(s);
	const size_t size = s.size();
	bool set = false;

	if(!size)
		return "";

	for (size_t i = 0; i < size; ++i) {
		if (s[i] == '/') {
			index = i;
			set = true;
		}
	}

	if (set)
		return strutil::cut(s, index + 1, size - index - 1);

	return s;
}

std::string erebos::file::get_basename(std::string filename) {

	filename = file::get_name(filename);
	const size_t size = filename.size();
	size_t index = 0;

	if(!size)
		return "";

	for (size_t i = 0; i < size; ++i)
		if (filename[i] == '.') {
			index = i;
			break;
		}

	if (index)
		filename = strutil::cut(filename, 0, index);

	return filename;
}


bool erebos::file::get_exists(const std::string &filename) {
	FILE *file;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	file = fopen(filename.c_str(), "r");
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

std::string erebos::file::read(const std::string &filename) {
	std::ifstream stream(filename);

	if (!stream.is_open())
		return "";

	std::stringstream ss;
	ss << stream.rdbuf();

	return ss.str();
}


erebos::Data erebos::file::read_bin(const std::string &filename, std::uint64_t *bytecount) {
	Data data { filename };

	FILE *fd;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	fd = fopen(filename.c_str(), "rb");
#elif defined(_COMPILER_MSVC)
	errno_t err = fopen_s(&fd, filename.c_str(), "rb");
	if (err != 0)
		return Data(nullptr, 0);
#endif

	if (!fd)
		return Data(nullptr, 0); // Return an empty data structure.

	size_t res = fread(data.data, 1, data.size, fd);

	if (bytecount)
		*bytecount = res;

	fclose(fd);

	return data;
}


bool erebos::file::write(const std::string &filename, const std::string &data, bool truncate) {
	std::ofstream stream;
	if (truncate)
		stream.open(filename, std::ofstream::out | std::ofstream::trunc);
	else
		stream.open(filename);

	if (!stream.is_open())
		return false;

	stream << data;
	return true;
}


bool erebos::file::write_bin(const std::string &filename, const Data &data, bool truncate) {

	FILE *fd;

#if defined(_COMPILER_GCC) || defined(_COMPILER_CLANG)
	fd = fopen(filename.c_str(), (truncate) ? "wb+" : "wb");
#elif defined(_COMPILER_MSVC)
	errno_t err;
	err = fopen_s(&fd, filename.c_str(), (truncate) ? "wb+" : "wb");

	if (err != 0)
		return false;
#endif

	if (!fd)
		return false;

	fwrite(data.data, 1, data.size, fd);
	fclose(fd);

	return true;
}
